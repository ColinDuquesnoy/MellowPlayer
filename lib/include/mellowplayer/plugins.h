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

#include "mellowplayer/song.h"


/*!
 * \brief Plugin interface for adding cloud music service integration.
 */
class ICloudMusicService
{
public:
    /*!
     * Evaluates the JavaScript defined by ``scriptSource`` using the main web
     * frame as context and returns the result of the last executed statement.
     *
     * \param scriptSource JavaScript source to evaluate.
     * \return The result of the last JavaScript statement.
     */
    QVariant runJavaScript(const QString& scriptSource);

    //! Returns the cloud music service URL
    virtual QUrl url() = 0;

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

    virtual SongInfo currentSongInfo() = 0;

protected:
    QWebView* webView;  ///< A pointer to the appliction's web view.
};

#define ICloudMusicService_iid "org.MellowPlayer.ICloudMusicService"
Q_DECLARE_INTERFACE(ICloudMusicService, ICloudMusicService_iid)

#endif // PLUGINS

