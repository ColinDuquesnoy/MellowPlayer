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
#include <QtWebKitWidgets/QWebView>
#include "mellowplayer/cloudservicesmanager.h"
#include "mellowplayer/player.h"
#include "mellowplayer/services.h"

//---------------------------------------------------------
CloudServicesManager* Services::_cloudServices = NULL;
ExtensionsManager* Services::_extensions = NULL;
QMainWindow* Services::_mainWindow= NULL;
QWebView* Services::_webView = NULL;
PlayerInterface* Services::_player = NULL;

//---------------------------------------------------------
void Services::_setMainWindow(QMainWindow *mainWindow)
{
    Services::_mainWindow = mainWindow;
}

//---------------------------------------------------------
QMainWindow *Services::mainWindow()
{
    return Services::_mainWindow;
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
void Services::_setCloudServicesManager(CloudServicesManager *manager)
{
    Services::_cloudServices = manager;
}

//---------------------------------------------------------
CloudServicesManager *Services::cloudServices()
{
    return Services::_cloudServices;
}

//---------------------------------------------------------
void Services::_setExtensionsManager(ExtensionsManager *manager)
{
    Services::_extensions = manager;
}

//---------------------------------------------------------
ExtensionsManager *Services::extensions()
{
    return Services::_extensions;
}

//---------------------------------------------------------
void Services::_setWebView(QWebView *_webView)
{
    Services::_webView = _webView;
}

//---------------------------------------------------------
QWebView *Services::webView()
{
    return Services::_webView;
}

//---------------------------------------------------------
void Services::_setPlayer(PlayerInterface *player)
{
    Services::_player = player;
}

//---------------------------------------------------------
PlayerInterface *Services::player()
{
    return Services::_player;
}

//---------------------------------------------------------
QAction *Services::action(const QString &actionText)
{
    QList<QAction*> actions = Services::_mainWindow->actions();
    foreach(QAction* a, actions){
        if(a->objectName() == actionText)
            return a;
    }
    return NULL;
}


