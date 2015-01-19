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

#ifndef SONG
#define SONG

#include <QString>

/*!
 * \brief The PlaybackStatus enum enumerates the possible playback status of
 * a song.
 */
enum PlaybackStatus
{
    /*!
      Song is loading
      */
    Loading,
    /*!
      Song is playing
      */
    Playing,
    /*!
      Song has been paused
      */
    Paused,
    /*!
      Song has been stopped
      */
    Stopped
};


/*!
 * \brief Converts a playback status value to a string
 * \param status Status to convert
 * \return String representation of the playback status
 */
QString playbackStatusToString(PlaybackStatus status, bool allowLoading=true);
QString playbackStatusToStringTr(PlaybackStatus status, bool allowLoading=true);


/*!
 * \brief The Song struct contains the song current song information
 */
struct SongInfo
{
    QString         songId;          /*!< Id of the song */
    QString         songName;        /*!< Name of the song */
    QString         artistName;      /*!< Name of the artist */
    QString         albumName;       /*!< Name of the album */
    QString         artUrl;          /*!< Art url*/
    PlaybackStatus  playbackStatus;  /*!< Playback status of the song */
    qlonglong       duration;        /*!< Song duration given in microseconds */
    qlonglong       position;        /*!< Song position given in microseconds */

    /*!
     * \brief Checks if the song info is valid (i.e. has at least songName
     * defined)
     *
     * \return True if the song is valid.
     */
    bool isValid() const;

    /*!
     * @brief Returns a string representation of the song using the
     * following format: SONG_NAME by ARTIST_NAME on ALBUM_NAME.
     *
     * @return return a string representatin of the song
     */
    QString toString() const;
};

#endif // SONG

