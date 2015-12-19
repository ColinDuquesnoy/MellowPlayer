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
    var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    var volume = mMain.getSoundVolume();
    if (volume == 0)
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": false,
        "CanGoNext": false,
        "CanGoPrevious": false,
        "CanAddToFavorites": false,
        "Volume": volume,
    }
}

function updateSongInfo() {
    var track = mMain._track;
    return {
        "SongId": track.id,
        "SongTitle": track.title,
        "ArtistName": track.artist,
        "AlbumTitle": '',
        "ArtUrl": track.pictures[0],
        "Favorite": false,
        "Duration": track.duration,
        "Position": 0
    }
}

function play() {
    // the playback cannot be interrupted but we can fake it by muting the player
    mMain.onClickSound()
}

function pause() {
    // the playback cannot be resumed but we can fake it by unmuting the player
    mMain.onClickSound()
}

function goNext() {
    // not supported
}

function goPrevious() {
    // not supported
}

function setVolume(volume) {
    mMain.setSoundVolume(volume)
}


function addToFavorites(add) {
    // not supported
}

function seekToPosition(position) {

}
