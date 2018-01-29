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
function getButtons() {
    return {
        play: document.getElementById("youtube_play_button"),
        pause: document.getElementById("youtube_pause_button"),
        skip: document.getElementById("youtube_skip_button")
    };
}

function isPlaying() {
    var mix = document.getElementById("mix_youtube");
    var index = mix.className.indexOf("playing");
    return index !== -1;
}

function update() {
    try {
        var buttons = getButtons();
        var playbackStatus = isPlaying() ? mellowplayer.PlaybackStatus.PLAYING : mellowplayer.PlaybackStatus.PAUSED;
        var songTitle = document.querySelector(".title_artist .t").innerText;
        return {
            "playbackStatus": playbackStatus,
            "canSeek": false,
            "canGoNext": true,
            "canGoPrevious": false,
            "canAddToFavorites": false,
            "volume": 1,
            "duration": 0,
            "position": 0,
            "songId": getHashCode(songTitle),
            "songTitle": songTitle,
            "artistName": document.querySelector(".title_artist .a").innerText,
            "albumTitle": document.querySelector(".album .detail").innerText,
            "artUrl": document.querySelector("#player_mix img.cover").src.replace(/w=\d+&h=\d+/, 'w=500&h=500'),
            "isFavorite": false
        };
    } catch (e) {
        return {
            "playbackStatus": mellowplayer.PlaybackStatus.STOPPED,
            "canSeek": false,
            "canGoNext": false,
            "canGoPrevious": false,
            "canAddToFavorites": false,
            "volume": 1,
            "duration": 0,
            "position": 0,
            "songId": 0,
            "songTitle": '',
            "artistName": '',
            "albumTitle": '',
            "artUrl": '',
            "isFavorite": false
        };
    }
}

function play() {
    getButtons().play.click()
}

function pause() {
    getButtons().pause.click()
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