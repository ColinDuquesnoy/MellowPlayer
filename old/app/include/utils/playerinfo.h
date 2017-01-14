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

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QVariantMap>

//---------------------------------------------------------
// Enumerations
//---------------------------------------------------------
/**
 * @brief Enumerates the possible playback status.
 */
enum class PlayerStatus {
  Playing,  ///< Web player is playing
  Paused,   ///< Web player has been paused
  Stopped,  ///< Web player has been stopped (no active song)
  Buffering ///< Web player is buffering a song tack.
};

//---------------------------------------------------------
// Structures
//---------------------------------------------------------
struct PlayerInfo {
  /**
   * @brief Specifies if the web player can seek to a particular position.
   */
  bool CanSeek;

  /**
   * @brief Specifies if the web player can skip to the next track.
   */
  bool CanGoNext;

  /**
   * @brief Specifies if the web player can skip to the previous track.
   */
  bool CanGoPrevious;

  /**
   * @brief Specifies if the web player supports favorites songs.
   */
  bool CanAddToFavorites;

  /**
   * @brief The playback status of the player (playing, paused,...).
   */
  PlayerStatus Status;

  /**
   * @brief Volume level of the web player [0-1]
   */
  float Volume;

  PlayerInfo() {
    Volume = -1;
    CanSeek = false;
    CanGoNext = false;
    CanGoPrevious = false;
    CanAddToFavorites = false;
    Status = PlayerStatus::Stopped;
  }
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
bool operator==(const PlayerInfo &lhs, const PlayerInfo &rhs);

/**
 * @brief Compares two songs. Songs are different if the SongTitle are
 * different.
 * @param lhs left hand side.
 * @param rhs right hand side.
 * @return true if songs are equal, false otherwise.
 */
bool operator!=(const PlayerInfo &lhs, const PlayerInfo &rhs);

/**
 * @brief Creates a song info instance from a QVariantMap
 * @param map Data source
 * @return SongInfo
 */
PlayerInfo playerInfoFromQVariantMap(const QVariantMap &map);

#endif // PLAYERINFO_H
