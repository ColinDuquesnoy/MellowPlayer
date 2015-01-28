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

#include <QtCore>
#include <mellowplayer.h>

class GroovesharkmobilePlugin:
        public QObject,
        public IStreamingService
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IStreamingService_iid
                      FILE "groovesharkmobile.json")
#endif
    Q_INTERFACES(IStreamingService)

public:
    GroovesharkmobilePlugin();
    virtual const PluginMetaData& metaData() const;
    //! Returns the GroovesharkmobilePlugin URL
    virtual QUrl url() const;
    //! Plays the current song
    void play();
    //! Pauses the current song
    void pause();
    //! Stops the current song
    void stop();
    //! Skips to the next song
    void next();
    //! Skips to the previous song
    void previous();
    //! Seeks to the indicated position
    void seekToPosition(int position);
    //! Gets the current song info
    SongInfo currentSongInfo();
    //! Gets the player's playback status
    PlaybackStatus playbackStatus();
    //! Gets the player's volume
    float volume();
    //! Sets the player's volume
    void setVolume(float volume);
};
