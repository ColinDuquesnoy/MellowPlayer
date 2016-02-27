//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

#ifndef SONGINFO_H
#define SONGINFO_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QString>
#include <QVariantMap>

//---------------------------------------------------------
// Structures
//---------------------------------------------------------
/**
 * @brief The SongInfo struct contains the data that describe a song in the web
 * player.
 */
struct SongInfo {
  QString SongId;      ///< Song identifier
  QString SongTitle;   ///< Song title
  QString ArtistName;  ///< Artist name
  QString AlbumTitle;  ///< Album title
  QString ArtUrl;      ///< URL of the song/album art.
  QString LocalArtUrl; ///< Local URL of the downloaded song/album art.
  double Duration;     ///< Duration of the song, in seconds
  double Position;     ///< Positin of the song, in seconds
  bool Favorite; ///< Specifies whether the song is in the favorites songs.

  SongInfo() {
    SongId = -1;
    ArtistName = "";
    AlbumTitle = "";
    ArtUrl = "";
    LocalArtUrl = "";
    Duration = 0;
    Position = 0;
    Favorite = false;
  }

  /**
   * @brief Checks if a song is valid. A song is valid as long as the song title
   * is not empty.
   * @return
   */
  bool isValid() const;

  /**
   * @brief Retuns the song as a string (SongName by ArtistName on AlbumName).
   */
  QString toString() const;

  /**
   * @brief Same as toString except the song info are wrapped into html tags
   * (bold/italic).
   */
  QString toPrettyString() const;
};

//---------------------------------------------------------
// Functions
//---------------------------------------------------------
/**
 * @brief Compares two songs. Songs are equals if the SongTitle are equal.
 * @param lhs left hand side.
 * @param rhs right hand side.
 * @return true if songs are equal, false otherwise.
 */
bool operator==(const SongInfo &lhs, const SongInfo &rhs);

/**
 * @brief Compares two songs. Songs are different if the SongTitle are
 * different.
 * @param lhs left hand side.
 * @param rhs right hand side.
 * @return true if songs are equal, false otherwise.
 */
bool operator!=(const SongInfo &lhs, const SongInfo &rhs);

/**
 * @brief Creates a song info instance from a QVariantMap
 * @param map Data source
 * @return SongInfo
 */
SongInfo songFromQVariantMap(const QVariantMap &map);

#endif // SONGINFO_H
