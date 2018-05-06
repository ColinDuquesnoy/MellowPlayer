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
var player;

function update() {

    // Get the player when available once
    if(!player)
        player = document.getElementById("movie_player");

    // Playback status
    switch(player.getPlayerState()) {
        case 1:
            var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
            break;

        case 2:
            var playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
            break;

        case 3:
            var playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
            break;

        default:
            var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    }

    // Song title
    var songTitle = document.getElementsByTagName('h1')[0].innerText;

    // Artist name
    var artistName = document.getElementById('owner-container').innerText;

    // Art URL
    var artUrl = document.getElementById('avatar').getElementsByTagName('img')[0].src;

    return {
        "playbackStatus": playbackStatus,
        "volume": player.getVolume()/100,
        "duration": Math.floor(player.getDuration()),
        "position": Math.floor(player.getCurrentTime()),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "artUrl": artUrl,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,

        "albumTitle": "",
        "canAddToFavorites": false,
        "isFavorite": false
    };
}

function play() {
    player.playVideo();
}

function pause() {
    player.pauseVideo()
}

function goNext() {
    player.nextVideo()
}

function goPrevious() {
    player.previousVideo()
}

function setVolume(volume) {
    player.setVolume(volume*100);
}

function seekToPosition(position) {
    player.seekTo(position, true);
}

function addToFavorites() {}
function removeFromFavorites() {}
