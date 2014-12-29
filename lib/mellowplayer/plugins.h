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

#ifndef PLUGINS
#define PLUGINS

#include <QtWebKitWidgets/QWebView>
#include <QtPlugin>


//! Plugin interface for adding cloud music service integration.
class ServiceIntegrationInterface
{
public:
    //! Sets the plugin up, gives it a pointer to the web view.
    /*!
      This function takes a pointer to the application's web view. The view
      is used to inject some javascript to control a cloud music service
      throught it's JS API.

      \param webView A pointer to the appliction's web view.
    */
    void setUp(QWebView* webView);

    //! Starts playing the current song
    virtual void play() = 0;

    //! Pauses the current song
    virtual void pause() = 0;

    //! Stops the current song
    virtual void stop() = 0;

    //! Skips to the next song
    virtual void next() = 0;

    //! Skips to the previous song
    virtual void previous() = 0;

protected:
    QWebView* webView;  ///< A pointer to the appliction's web view.
};

#define ServiceIntegrationInterface_iid "org.MellowPlayer.ServiceIntegrationInterface"
Q_DECLARE_INTERFACE(ServiceIntegrationInterface, ServiceIntegrationInterface_iid)

#endif // PLUGINS

