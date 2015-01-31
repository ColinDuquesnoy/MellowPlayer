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
    m_trayIcon(new KStatusNotifierItem())
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
#ifdef __kde_support__
    m_trayIcon->setToolTipSubTitle(message);
    m_trayIcon->showMessage("MellowPlayer", message, icon);
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
