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
#include "mellowplayer/song.h"


//---------------------------------------------------------
QString playbackStatusToString(PlaybackStatus status, bool allowLoading)
{
    switch (status) {
    case Loading:
        if(allowLoading)
            return "Loading";
        else
            return "Playing";
    case Playing:
        return "Playing";
    case Paused:
        return "Paused";
    case Stopped:
        return "Stopped";
    }
    return "";
}

//---------------------------------------------------------
bool SongInfo::isValid() const
{
    return songName != "";
}

//---------------------------------------------------------
QString SongInfo::toString() const
{
    return QString("%1 by %2 on %3").arg(songName, artistName, albumName);
}
