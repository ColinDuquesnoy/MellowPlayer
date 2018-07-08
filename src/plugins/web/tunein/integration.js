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

function getPlaybackStatus() {
    var audio = jp_audio_0;

    if (audio === null)
        return mellowplayer.PlaybackStatus.STOPPED;
    else if (audio.paused)
        return mellowplayer.PlaybackStatus.PAUSED;
    else
        return mellowplayer.PlaybackStatus.PLAYING;
}

function getSongInfos() {
    try {
        return document.getElementById("playerTitle").innerText;
    } catch(e) {
        return "";
    }
}

function getArtist() {
    var tokens = getSongInfos().split("-");
    if (tokens.length > 2)
        return [0].trim();
    return "";
}

function getTitle() {
    var tokens = getSongInfos().split("-");
    if (tokens.length > 2)
        return getSongInfos().split("-")[1].trim();
    return getSongInfos();
}

function getArtUrl() {
    try {
        return document.getElementById("playerArtwork").src;
    } catch(e) {
        return "";
    }
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "songId": getHashCode(getTitle()),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getArtUrl(),
        "isFavorite": false,
        "duration": 0,
        "position": 0
    };
}

function play() {
    jp_audio_0.play()
}

function pause() {
    jp_audio_0.pause()
}

function goNext() {
    // not supported
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
