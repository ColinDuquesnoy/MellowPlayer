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
function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getButtons() {
    return {
        play: document.getElementById("player_play_button"),
        pause: document.getElementById("player_pause_button"),
        skip: document.getElementById("player_skip_button"),
    };
}

function updatePlayerInfo() {
    try {
        var buttons = getButtons();
        var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
        if (buttons.play.style.display == "block")
            playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
        return {
            "PlaybackStatus": playbackStatus,
            "CanSeek": false,
            "CanGoNext": buttons.skip && buttons.skip.style.display != "none",
            "CanGoPrevious": false,
            "CanAddToFavorites": false,
            "Volume": 1,
        };
    } catch (e) {
        return {
            "PlaybackStatus": mellowplayer.PlaybackStatus.STOPPED,
            "CanSeek": false,
            "CanGoNext": false,
            "CanGoPrevious": false,
            "CanAddToFavorites": false,
            "Volume": 1,
        };
    }
}

function updateSongInfo() {
    try {
        var songTitle = document.querySelector(".track.now_playing .title_artist .t").innerText;
        return {
            "SongId": getHashCode(songTitle),
            "SongTitle": songTitle,
            "ArtistName": document.querySelector(".track.now_playing .title_artist .a").innerText,
            "AlbumTitle": document.querySelector(".track.now_playing .album .detail").innerText,
            "ArtUrl": document.querySelector("#player_mix img.cover").src.replace(/w=\d+&h=\d+/, 'w=500&h=500'),
            "Favorite": false,
            "Duration": 0,
            "Position": 0
        };
    } catch (e) {
        console.warn(e);
        return {
            "SongId": 0,
            "SongTitle": '',
            "ArtistName": '',
            "AlbumTitle": '',
            "ArtUrl": '',
            "Favorite": false,
            "Duration": 0,
            "Position": 0
        };
    }
}

function play() {
    getButtons().play.click()
}

function pause() {
    getButtons().play.click()
}

function goNext() {
    getButtons().skip.click()
}

function goPrevious() {
    // not supported
}

function setVolume(volume) {
    // not supported
}


function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function seekToPosition(position) {
    // not supported
}
