//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <QDebug>
#include <QFile>
#include <QMainWindow>
#include <QProcess>
#include "mellowplayer/trayicon.h"
#include "mellowplayer/services.h"
#include "mellowplayer/player.h"

#ifdef __kde_support__
#include <kstatusnotifieritem.h>
#include <knotification.h>
#else
#include <QSystemTrayIcon>
#endif


//---------------------------------------------------------
TrayIcon::TrayIcon(QObject *parent):
    QObject(parent),
#ifdef __kde_support__
    m_trayIcon(new KStatusNotifierItem()),
    m_prevNotif(NULL)
#else
    m_trayIcon(new QSystemTrayIcon())
#endif
{
#ifdef __kde_support__
    connect (m_trayIcon, SIGNAL(activateRequested(bool, QPoint)),
             this, SLOT(onKF5IconActivated(bool, QPoint)) );
#else
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
#endif
}

//---------------------------------------------------------
TrayIcon::~TrayIcon()
{
#ifndef __kde_support__
    m_trayIcon->hide();
#endif
}

//---------------------------------------------------------
void TrayIcon::setIcon(const QIcon &icon)
{
#ifdef __kde_support__
    m_trayIcon->setIconByPixmap(icon);
    m_trayIcon->setToolTipIconByPixmap(icon);
    m_trayIcon->setTitle("MellowPlayer");
#else
    m_trayIcon->setIcon(icon);
    m_trayIcon->show();
#endif
}

//---------------------------------------------------------
void TrayIcon::setContextMenu(QMenu *menu)
{
    m_trayIcon->setContextMenu(menu);
}

//---------------------------------------------------------
void TrayIcon::setToolTip(const QString &toolTip)
{
#ifdef __kde_support__
    m_trayIcon->setTitle(toolTip);
#else
    m_trayIcon->setToolTip(toolTip);
#endif
}

//---------------------------------------------------------
void TrayIcon::showMessage(const QString &message, const QString& icon)
{
    qDebug() << "showing tray icon message: " << message << " (icon=" << icon << ")";
#ifdef __kde_support__
    if(m_prevNotif != NULL)
        m_prevNotif->close();
    KNotification *notification= new KNotification(
        "songChanged", Services::mainWindow(), KNotification::CloseWhenWidgetActivated);
    notification->setTitle(tr("MellowPlayer"));
    notification->setText(message);
    if(QFile(icon).exists())
        notification->setPixmap(QIcon(icon).pixmap(64, 64));
    else
        notification->setPixmap(QIcon::fromTheme(icon).pixmap(64, 64));

    QStringList actions;
    actions.append(tr("Open"));
    actions.append(tr("Next"));
    notification->setActions(actions);

    notification->sendEvent();
    connect(notification, SIGNAL(activated(unsigned int )), this, SLOT(notificationActionActivated(unsigned int)));
    connect(notification, SIGNAL(closed()), this, SLOT(onKNotificationClosed()));

    m_prevNotif = notification;
#elif defined(Q_OS_LINUX)
    QStringList args;
    args.append("--hint");
    args.append("int:transient:1");
    args.append("MellowPlayer");
    args.append(message);
    args.append(QString("--icon=%1").arg(icon));
    QProcess::startDetached("notify-send", args);
#else
    Q_UNUSED(icon);
    m_trayIcon->showMessage("MellowPlayer", message);
#endif
}

//---------------------------------------------------------
void TrayIcon::onKF5IconActivated(bool state, QPoint pos)
{
    Q_UNUSED(pos);
    emit activated(state);
}

//---------------------------------------------------------
void TrayIcon::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    bool active = false;
    if (reason == QSystemTrayIcon::DoubleClick)
        active = true;
    emit activated(active);
}

#ifdef __kde_support__
//---------------------------------------------------------
void TrayIcon::onKNotificationClosed()
{
    m_prevNotif = NULL;
}

//---------------------------------------------------------
void TrayIcon::notificationActionActivated(unsigned int actionIndex)
{
    Q_UNUSED(actionIndex);
    qDebug() << "Action Index" << actionIndex;
    switch (actionIndex)
    {
    case 1:
        Services::mainWindow()->show();
        Services::mainWindow()->raise();
        break;
    case 2:
        Services::player()->next();
        break;
    }
}
#endif
