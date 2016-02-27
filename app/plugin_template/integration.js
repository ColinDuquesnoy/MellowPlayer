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
function updatePlayerInfo() {
    return {
        "PlaybackStatus": mellowplayer.PlaybackStatus.STOPPED,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": true,
        "CanAddToFavorites": false,
        "Volume": 1,
    }
}

function updateSongInfo() {
    return {
        "SongId": 0,
        "SongTitle": '',
        "ArtistName": '',
        "AlbumTitle": '',
        "ArtUrl": '',
        "Favorite": false,
        "Duration": 0,
        "Position": 0
    }
}

function play() {

}

function pause() {

}

function goNext() {

}

function goPrevious() {

}

function setVolume(volume) {

}


function addToFavorites(add) {

}

function seekToPosition(position) {

}
