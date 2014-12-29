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

#include "mellowplayer/services.h"
#include "mellowplayer/cloudservicesmanager.h"
#include <QMainWindow>
#include <QtWebKitWidgets/QWebView>

//---------------------------------------------------------
CloudServicesManager* Services::_cloudServicesManager = NULL;
QMainWindow* Services::_mainWindow= NULL;
QWebView* Services::_webView = NULL;

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
void Services::_setCloudServicesManager(CloudServicesManager *manager)
{
    Services::_cloudServicesManager = manager;
}

//---------------------------------------------------------
CloudServicesManager *Services::cloudServicesManager()
{
    return Services::_cloudServicesManager;
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
