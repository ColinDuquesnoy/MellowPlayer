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

class StreamingServicesManager;
class ExtensionsManager;
class PlayerInterface;
class QAction;
class QMainWindow;
class QWebView;
class TrayIcon;

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
    /*!
     * \brief Gets a pointer to the application's main window
     */
    static QMainWindow* mainWindow();

    /*!
     * \brief Raises and shows the main window
     */
    static void raiseMainWindow();

    /*!
     * \brief Gets a pointer to the music streaming services plugin manager.
     */
    static StreamingServicesManager* streamingServices();

    /*!
     * \brief Returns a pointer to the extensions plugin manager.
     */
    static ExtensionsManager* extensions();

    /*!
     * \brief Gets a pointer to the webview.
     */
    static QWebView* webView();

    /*!
     * \brief Returns a pointer to the player interface that you can
     * use to control the streaming service's media player programmatically and
     * connect to the player events (songChanged,...).
     */
    static PlayerInterface* player();

    /*!
     * \brief Gets an action by name (only the control actions can be
     * retrieved).
     *
     * \param actionText Name of the action (objectName()).
     */
    static QAction* action(const QString& actionText);

    /*!
     * \brief Gets the trayIcon object.
     *
     * You may want use it to show notifications,...
     * \return
     */
    static TrayIcon *trayIcon();

private:
    friend class MellowPlayerApp;
    friend class MainWindow;

    static void _setMainWindow(QMainWindow* _mainWindow);
    static void _setServicesManager(StreamingServicesManager* manager);
    static void _setExtensionsManager(ExtensionsManager* manager);
    static void _setWebView(QWebView* _webView);
    static void _setPlayer(PlayerInterface* player);
    static void _setTrayIcon(TrayIcon *icon);

    static QMainWindow* _mainWindow;
    static QWebView* _webView;
    static StreamingServicesManager* _services;
    static ExtensionsManager* _extensions;
    static PlayerInterface* _player;
    static TrayIcon* _trayIcon;
};

#endif // SERVICES_H
