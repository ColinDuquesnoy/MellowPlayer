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

#include <QtCore>
#include <QtPlugin>
#include "mellowplayer/pluginmetadata.h"
#include "mellowplayer/playbackstatus.h"
#include "mellowplayer/song.h"

class QWebView;
class QWidget;


/*!
 * \brief Interface for adding music streaming service integration.
 */
class IStreamingService
{
public:
    /*!
     * \brief Returns the plugin's meta data.
     */
    virtual const PluginMetaData& metaData() const = 0;

    //! Returns the music streaming service URL
    virtual QUrl url() const = 0;

    //! Whether the client can control the playback position using
    //! seekToPosition.
    virtual bool canSeek() = 0;

    //! Whether the client can call the next method on this interface and
    //! expect the current track to change.
    virtual bool canGoNext() = 0;

    //! Whether the client can call the previsou method on this interface and
    //! expect the current track to change.
    virtual bool canGoPrevious() = 0;

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

    //! Seeks to the indicated position [µs]
    virtual void seekToPosition(int position) = 0;

    //! Gets the player volume [0.0-1.0]
    virtual float volume() = 0;

    //! Sets the player volume [0.0-1.0]
    virtual void setVolume(float value) = 0;

    //! Gets the current song information
    virtual SongInfo currentSongInfo() = 0;

    //! Gets the player's playback status
    virtual PlaybackStatus playbackStatus() = 0;

    //! Checks whether the service support adding a song to the user's favorite
    virtual bool canFavorite() = 0;

    //! Checks whether the song is part of the user's favorite songs.
    virtual bool isFavorite() = 0;

    /*!
     * \brief Adds the current song to the user's favorite songs.
     *
     * \param add True to addd, False to remove.
     */
    virtual void addToFavorite(bool add) = 0;

protected:
    /*!
     * Evaluates the JavaScript defined by ``scriptSource`` using the main web
     * frame as context and returns the result of the last executed statement.
     *
     * \param scriptSource JavaScript source to evaluate.
     * \return The result of the last JavaScript statement.
     */
    QVariant runJavaScript(const QString& scriptSource);

    /*!
     * \brief Utility method that checks whether the page has finished
     * loading or not.
     *
     * \returns true if the page has finished loading, otherwise returns false
     */
    bool isPageLoaded() const;
};

#define IStreamingService_iid "org.MellowPlayer.IStreamingService"
Q_DECLARE_INTERFACE(IStreamingService, IStreamingService_iid)


/*!
 * \brief Inteface for adding a generic extension to the application.
 *
 * An extension plugin can be anything. Since you can access any parts of the
 * application (logic, gui, other plugins), you're free to setup any kind of
 * extension. You can add your own menu or dock widget,...
 *
 * Each plugin may have a settings widgets that will automatically appear in the
 * application settings.
 *
 * To create a new IExtension, you **must implement the following methods**:
 *
 *    - metaData
 *    - setup
 *
 * The following methods are optional. Implement them if you have a
 * specific teardown procedure to execute:
 *
 *   - teardown
 *
 * Or if you wish to expose some settings to the user through the
 * preferences dialog:
 *
 *   - settingsWidget
 *   - resetSettings
 *   - restoreSettings
 *   - applySettings
 */
class IExtension
{
public:
    /*!
     * \brief Returns the plugin's meta data.
     */
    virtual const PluginMetaData& metaData() const = 0;

    /*!
     * \brief Initalizes the extension.
     *
     * You must implement this method to perform your extension setup.
     *
     * Hint: You can use the Services static class to get access to the most
     * important parts of your application to perform your own specific setup.
     */
    virtual void setup() = 0;

    /*!
     * \brief Destroys the extension.
     *
     * This method is called on application exit.
     *
     * Implement this method if you need to unregister some services or to
     * delete custom allocated objects.
     */
    virtual void teardown() { }

    /*!
     * \brief Returns the settings widget associated with the extension.
     *
     * Implement this method if you need to show a settings widget in the
     * application preferences dialog. Return NULL if you don't need to show
     * any settings. If you return a non-null widget, you will also need to
     * implement: resetSettings, restoreDefaultSettings and applySettings.
     */
    virtual QWidget* settingsWidget() const { return NULL; }

    /*!
     * \brief Reset the plugin settings
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    virtual void resetSettings(QWidget* widget) const { Q_UNUSED(widget) }

    /*!
     * \brief Restore the plugin settings to their default values.
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    virtual void restoreDefaultSettings(QWidget* widget) const { Q_UNUSED(widget) }

    /*!
     * \brief Apply plugin settings.
     *
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    virtual void applySettings(QWidget* widget) const { Q_UNUSED(widget) }
};

#define IExtension_iid "org.MellowPlayer.IExtension"
Q_DECLARE_INTERFACE(IExtension, IExtension_iid)

#endif // PLUGINS

