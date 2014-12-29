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

#include <QtPlugin>


class MainWindow;


//! Plugin interface for adding cloud music service integration.
class IServiceIntegration
{
public:
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
};

#define IServiceIntegration_iid "org.MellowPlayer.IServiceIntegration"
Q_DECLARE_INTERFACE(IServiceIntegration, IServiceIntegration_iid)


//! Generic plugin interface for adding an extension to the application.
/*!
  To implement this interface, you must implement the setUp method which
  receives a pointer to the main application window. From there, it's up to
  you to add custom menus to the main window or custom tools (e.g. a lyrics
  fetcher).
*/
class IGenericExtension
{
public:
    //! Sets the plugin up.
    /*!
      This function takes a pointer to the application's main window so that you
      can setup any gui related object.

      \param mainWindow A pointer to the application main window.
    */
    virtual void setUp(MainWindow* mainWindow) = 0;

    //! Tears the plugin down.
    /*!
      Use this if you need to unregister services or to delete any custom
      object.
    */
    virtual void tearDown() = 0;
};

#define IGenericExtension_iid "org.MellowPlayer.IGenericExtension"
Q_DECLARE_INTERFACE(IGenericExtension, IGenericExtension_iid)

#endif // PLUGINS

