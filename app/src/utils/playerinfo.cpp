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

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include "utils/playerinfo.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
bool operator==(const PlayerInfo &lhs, const PlayerInfo &rhs) {
  return lhs.CanGoNext == rhs.CanGoNext &&
         lhs.CanGoPrevious == rhs.CanGoPrevious && lhs.CanSeek == rhs.CanSeek;
}

//--------------------------------------
bool operator!=(const PlayerInfo &lhs, const PlayerInfo &rhs) {
  return lhs.CanGoNext != rhs.CanGoNext ||
         lhs.CanGoPrevious != rhs.CanGoPrevious || lhs.CanSeek != rhs.CanSeek;
}

//--------------------------------------
PlayerInfo playerInfoFromQVariantMap(const QVariantMap &map) {
  PlayerInfo player;

  player.CanAddToFavorites = map.value("CanAddToFavorites").toBool();
  player.CanGoNext = map.value("CanGoNext").toBool();
  player.CanGoPrevious = map.value("CanGoPrevious").toBool();
  player.CanSeek = map.value("CanSeek").toBool();
  player.Status = (PlayerStatus)map.value("PlaybackStatus").toInt();
  player.Volume = map.value("Volume").toFloat();

  return player;
}
