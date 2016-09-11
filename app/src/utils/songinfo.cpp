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
#include "utils/songinfo.h"
#include <QtCore>

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
bool SongInfo::isValid() const { return !SongTitle.isEmpty(); }

//--------------------------------------
QString SongInfo::toString() const {
  if (!ArtistName.isEmpty())
    return QObject::tr("%1 by %2").arg(SongTitle).arg(ArtistName);
  else
    return SongTitle;
}

//--------------------------------------
QString SongInfo::toPrettyString() const {
  if (!ArtistName.isEmpty())
    return QObject::tr("<b>%1</b> <i>by %2</i>").arg(SongTitle).arg(ArtistName);
  else
    return QObject::tr("<b>%1</b>").arg(SongTitle);
}

//--------------------------------------
SongInfo songFromQVariantMap(const QVariantMap &map) {
  SongInfo song;

  song.SongId = map.value("SongId").toString();
  song.SongTitle = map.value("SongTitle").toString();
  song.ArtistName = map.value("ArtistName").toString();
  song.AlbumTitle = map.value("AlbumTitle").toString();
  song.ArtUrl = map.value("ArtUrl").toString();
  song.Duration = map.value("Duration").toDouble();
  song.Position = map.value("Position").toDouble();
  song.Favorite = map.value("Favorite").toBool();

  return song;
}

//--------------------------------------
bool operator==(const SongInfo &lhs, const SongInfo &rhs) {
  return lhs.SongTitle == rhs.SongTitle;
}

//--------------------------------------
bool operator!=(const SongInfo &lhs, const SongInfo &rhs) {
  return !(lhs == rhs);
}
