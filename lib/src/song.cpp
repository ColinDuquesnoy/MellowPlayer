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

#include <QObject>
#include "mellowplayer/song.h"


//---------------------------------------------------------
bool SongInfo::isValid() const
{
    return songName != "";
}

//---------------------------------------------------------
QString SongInfo::toString() const
{
    if(albumName != "" && artistName != "")
        return QObject::tr("%1 by %2 from %3")
                .arg(songName).arg(artistName).arg(albumName);
    else if(albumName == "" && artistName != "")
        return QObject::tr("%1 by %2")
                .arg(songName).arg(artistName);
    else if(albumName != "" && artistName == "")
        return QObject::tr("%1 from %2")
                .arg(songName).arg(artistName);
    else
        return songName;
}

//---------------------------------------------------------
SongInfo::SongInfo()
{
    songName = "";
    position = 0;
}
