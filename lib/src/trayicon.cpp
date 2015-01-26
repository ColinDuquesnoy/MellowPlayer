#include "mellowplayer/trayicon.h"

#ifdef __kde_support__
#include <kstatusnotifieritem.h>
#else
#include <QSystemTrayIcon>
#endif


//---------------------------------------------------------
TrayIcon::TrayIcon(QObject *parent):
    QObject(parent),
#ifdef __kde_support__
    trayIcon(new KStatusNotifierItem())
#else
    trayIcon(new QSystemTrayIcon())
#endif
{
#ifdef __kde_support__
    connect (trayIcon, SIGNAL(activateRequested(bool, QPoint)),
             this, SLOT(onKF5IconActivated(bool, QPoint)) );
#else
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
#endif
}

//---------------------------------------------------------
TrayIcon::~TrayIcon()
{
#ifndef __kde_support__
    trayIcon->hide();
#endif
}

//---------------------------------------------------------
void TrayIcon::setIcon(const QIcon &icon)
{
#ifdef __kde_support__
    trayIcon->setIconByPixmap(icon);
    trayIcon->setToolTipIconByPixmap(icon);
    trayIcon->setTitle("MellowPlayer");
#else
    trayIcon->setIcon(icon);
    trayIcon->show();
#endif
}

//---------------------------------------------------------
void TrayIcon::setContextMenu(QMenu *menu)
{
    trayIcon->setContextMenu(menu);
}

//---------------------------------------------------------
void TrayIcon::setToolTip(const QString &toolTip)
{
#ifdef __kde_support__
    trayIcon->setTitle(toolTip);
#else
    trayIcon->setToolTip(toolTip);
#endif
}

//---------------------------------------------------------
void TrayIcon::showMessage(const QString &message, const QString& icon)
{
#ifdef __kde_support__
    trayIcon->setToolTipSubTitle(message);
    trayIcon->showMessage("MellowPlayer", message, icon);
#else
    Q_UNUSED(icon);
    trayIcon->showMessage("MellowPlayer", message);
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
