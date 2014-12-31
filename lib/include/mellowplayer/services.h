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

#ifndef SERVICES_H
#define SERVICES_H

class QMainWindow;
class CloudServicesManager;
class PlayerInterface;
class QWebView;

/*!
 * \brief The Services class shares the main application objects.
 *
 * This is a static class whose only purpose is to share the application
 * objects easily. All the objects are setup by the application class and can
 * be accessed by any part of the application (as long as they link with this
 * lib). That way plugins can access the main window, the player interface,...
 *
 */
class Services
{
public:
    static void _setMainWindow(QMainWindow* _mainWindow);
    static QMainWindow* mainWindow();

    static void _setCloudServices(CloudServicesManager* manager);
    static CloudServicesManager* cloudServices();

    static void _setWebView(QWebView* _webView);
    static QWebView* webView();

    static void _setPlayer(PlayerInterface* player);
    static PlayerInterface* player();

private:
    static QMainWindow* _mainWindow;
    static QWebView* _webView;
    static CloudServicesManager* _cloudServices;
    static PlayerInterface* _player;
};

#endif // SERVICES_H
