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
        playpause: document.querySelector("a.sm2-inline-button.play-pause"),
        skip: document.querySelector("a.sm2-inline-button.next"),
        back: document.querySelector("a.sm2-inline-button.previous")
    };
}

function getArtUrl() {
    try {
        var elm = document.getElementsByClassName("sm2-playlist-cover")[0];
        return elm.baseURI;
    }
    catch (e) {
        return ""
    }
}

function getSongTitle() {
    try {
        var elm = document.getElementsByClassName("selected")[0].getElementsByClassName("title")[0];
        return elm.innerHTML;
    }
    catch (e) {
        return ""
    }
}

function getSongId() {
    try {
        return getHashCode(getSongTitle());
    }
    catch (e) {
        return "";
    }
}

function getArtist() {
    try {
        var elm = document.getElementsByClassName("selected")[0];
        return elm.getAttribute("data-artist");
    }
    catch (e) {
        return "";
    }
}

function getAlbum() {
    try {
        var elm = document.getElementsByClassName("selected")[0];
        return elm.getAttribute("data-album");
    }
    catch (e) {
        return "";
    }
}

//-----------------------------------------------------------------------------
// Credit for this code to http://stackoverflow.com/questions/13437796/convert-any-string-time-to-seconds
//-----------------------------------------------------------------------------
function parseTimeString(timeString) {
    try {
        var dtimes = timeString.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        return parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {
        return 0;
    }
}


function getDuration() {
    try {
        var duration = document.getElementsByClassName("sm2-inline-duration")[0].innerText;
        return parseTimeString(duration);
    } catch (e) {
        return 0;
    }
}

function getPosition() {
    try {
        var position = document.getElementsByClassName("sm2-inline-time")[0].innerText;
        return parseTimeString(position);
    } catch (e) {
        return 0;
    }
}

function getPlaybackStatus() {
    var controlClassName = document.getElementsByClassName("sm2-bar-ui")[0].className;
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (controlClassName === "sm2-bar-ui full-width playing")
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (controlClassName === "sm2-bar-ui full-width paused")
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    return playbackStatus;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "songId": getSongId(),
        "songTitle": getSongTitle(),
        "artistName": getArtist(),
        "albumTitle": getAlbum(),
        "artUrl": getArtUrl(),
        "isFavorite": false,
        "duration": getDuration(),
        "position": getPosition()

    };
}

function play() {
    getButtons().playpause.click()
}

function pause() {
    getButtons().playpause.click()
}

function goNext() {
    getButtons().skip.click()
}

function goPrevious() {
    getButtons().back.click()
}

function setVolume(volume) {
    // not currently supported
}

function addToFavorites() {
    // not currently supported
}

function removeFromFavorites() {
    // not currently supported
}

function seekToPosition(position) {
    // not currently supported
}
