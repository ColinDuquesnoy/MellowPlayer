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
#include "mellowplayer/playbackstatus.h"
#include "mellowplayer/song.h"


/*!
 * \brief The PlayerInterface provides an interface to the music streaming
 * service's player.
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
     * \brief Seeks to the indicated position
     *
     * \param position position to reach [µs]
     */
    void seekToPosition(int position);

    /*!
     * \brief Whether playback can be started using playPause.
     */
    bool canPlay();

    /*!
     * \brief Whether the client can control the playback position using
     *  seekToPosition.
     */
    bool canSeek();

    /*!
     * \brief Whether the client can call the next method on this interface and
     * expect the current track to change.
     */
    bool canGoNext();
    /*!
     * \brief Whether the client can call the previous method on this interface
     * and expect the current track to change.
     */
    bool canGoPrevious();

    /*!
     * \brief Gets the current song info
     */
    SongInfo currentSong();

    /*!
     * \brief Update the player (and emit status changed signals)
     *
     * This method must be called periodically to ensure proper refresh of the
     * player status.
     *
     * \return the current song infos.
     */
    SongInfo update();

    /*!
     * \brief Gets the player volume.
     *
     * \return Volume [0-1.0]
     */
    float volume();

    /*!
     * \brief Sets the player volume
     *
     * \param value volume value between 0.0 and 1.0.
     */
    void setVolume(float value);

    /*!
     * \brief Gets the player's playback status
     *
     * \return PlaybackStatus
     */
    PlaybackStatus playbackStatus() const;

    /*!
     * \brief Checks whether the streaming service can favorite the current
     * song
     */
    bool canFavorite();

    /*!
     * \brief Checks whether the current song is part of the user's favorite
     * songs.
     */
    bool isFavorite();

    /*!
     * \brief Adds the current song to the favorites
     */
    void addToFavorites();

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
     * Note that the current song might change even if the player is not
     * playing. If you want to get notified when a song changed and is playing,
     * use the songStarted signal instead.
     *
     * \param song The new song info
     */
    void songChanged(const SongInfo& song);

    /*!
     * \brief Signal emitted when a new song changed and the song is currently
     * playing.
     *
     * \param song The new song info
     */
    void songStarted(const SongInfo& song);

    /*!
     * \brief Signal emitted when an art file has been downloaded and is
     * ready to use.
     *
     * \param artFilePathUrl Art file path (usually in a temporary directory).
     */
    void artReady(const QString& artFilePathUrl);

    /*!
     * \brief Signal emitted when the position of the current song changed.
     *
     * \param position New song position [µs]
     */
    void positionChanged(qlonglong position);

    /*!
     * \brief Signal emitted when the player's control capabilities changed
     * (e.g. canGoNext changed from true to false,...).
     */
    void controlCapsChanged();

private slots:
    void onArtReady(const QString& filePath);

private:
    void checkPlaybackStatusChange(SongInfo& song);
    void checkSongChange(SongInfo& song);
    void checkForPositionChange(SongInfo& song);
    void checkForControlCaps();
    void downloadSongArt(const QString &url);

    SongInfo        _currentSong;
    SongInfo        _startedSong;
    PlaybackStatus  currentStatus;
    int             currentPosition;

    bool _canSeek;
    bool _canPlay;
    bool _canGoNext;
    bool _canGoPrevious;
};

#endif // PLAYER

