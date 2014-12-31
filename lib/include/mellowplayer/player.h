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

#ifndef PLAYER
#define PLAYER

#include <QObject>
#include "mellowplayer/song.h"


/*!
 * \brief The PlayerInterface provides an interface to the cloud music player
 */
class PlayerInterface: public QObject
{
    Q_OBJECT
public:
    explicit PlayerInterface(QObject* parent=NULL);

    /*!
     * \brief Resumes/Pauses playback depending on the current playback status.
     */
    void playPause();

    /*!
     * \brief Stops play
     */
    void stop();

    /*!
     * \brief Plays next song
     */
    void next();

    /*!
     * \brief Plays previous song
     */
    void previous();

    /*!
     * \brief Gets the current song info
     */
    SongInfo getCurrentSong();

    /*!
     * \brief Update the player (and emit status changed signals)
     *
     * This method must be called periodically to ensure proper refresh of the
     * player status.
     *
     * \return the current song infos.
     */
    SongInfo update();

signals:
    /*!
     * \brief Signal emitted when the current song status changed
     *
     * E.g. when the user paused the current song or resumed playback
     *
     * \param newStatus The new playback status.
     */
    void playbackStatusChanged(PlaybackStatus newStatus);

    /*!
     * \brief Signal emitted when the current song changed.
     *
     * \param song The new song info
     */
    void songChanged(const SongInfo& song);

    /*!
     * \brief Signal emitted when an art file has been downloaded and is
     * ready to use.
     *
     * \param artFilePathUrl Art file path (usually in a temporary directory).
     */
    void artReady(QString artFilePathUrl);

private:
    void checkPlaybackStatusChange(SongInfo& song);
    void checkSongChange(SongInfo& song);

    SongInfo currentSong;
    PlaybackStatus currentStatus;
};

#endif // PLAYER

