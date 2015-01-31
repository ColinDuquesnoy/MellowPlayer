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

#include <QAction>
#include <QMainWindow>
#include <QWebView>
#include "mellowplayer/streamingservicesmanager.h"
#include "mellowplayer/player.h"
#include "mellowplayer/services.h"
#include "mellowplayer/trayicon.h"

//---------------------------------------------------------
StreamingServicesManager* Services::m_services = NULL;
ExtensionsManager* Services::m_extensions = NULL;
QMainWindow* Services::m_mainWindow= NULL;
QWebView* Services::m_webView = NULL;
PlayerInterface* Services::m_player = NULL;
TrayIcon* Services::m_trayIcon = NULL;

//---------------------------------------------------------
void Services::_setMainWindow(QMainWindow *mainWindow)
{
    Services::m_mainWindow = mainWindow;
}

//---------------------------------------------------------
QMainWindow *Services::mainWindow()
{
    return Services::m_mainWindow;
}

//---------------------------------------------------------
void Services::raiseMainWindow()
{
    QMainWindow* window = Services::mainWindow();
    window->show();
    window->raise();
    window->activateWindow();
}

//---------------------------------------------------------
void Services::_setServicesManager(StreamingServicesManager *manager)
{
    Services::m_services = manager;
}

//---------------------------------------------------------
StreamingServicesManager *Services::streamingServices()
{
    return Services::m_services;
}

//---------------------------------------------------------
void Services::_setExtensionsManager(ExtensionsManager *manager)
{
    Services::m_extensions = manager;
}

//---------------------------------------------------------
ExtensionsManager *Services::extensions()
{
    return Services::m_extensions;
}

//---------------------------------------------------------
void Services::_setWebView(QWebView *_webView)
{
    Services::m_webView = _webView;
}

//---------------------------------------------------------
QWebView *Services::webView()
{
    return Services::m_webView;
}

//---------------------------------------------------------
void Services::_setPlayer(PlayerInterface *player)
{
    Services::m_player = player;
}

//---------------------------------------------------------
PlayerInterface *Services::player()
{
    return Services::m_player;
}

//---------------------------------------------------------
QAction *Services::action(const QString &actionText)
{
    QList<QAction*> actions = Services::m_mainWindow->actions();
    foreach(QAction* a, actions){
        if(a->objectName() == actionText)
            return a;
    }
    return NULL;
}

//---------------------------------------------------------
void Services::_setTrayIcon(TrayIcon *icon)
{
    Services::m_trayIcon = icon;
}

//---------------------------------------------------------
TrayIcon *Services::trayIcon()
{
    return Services::m_trayIcon;
}


