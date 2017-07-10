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
        play: document.getElementsByClassName("ytp-play-button")[0],
        pause: document.getElementsByClassName("ytp-play-button")[0],
        skip: document.getElementsByClassName("ytp-next-button")[0],
    };
}

function toMilliseconds(string) {
    try {
        var dtimes = string.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {
        var duration = 0;
    }
    
    return duration
}

function update() {
    try {
        var rawPosition = document.getElementsByClassName("ytp-time-current")[0].innerText;
        var rawDuration = document.getElementsByClassName("ytp-time-duration")[0].innerText;
        var playbackStatus = getButtons().play.attributes["aria-label"].value == "Pause" ? mellowplayer.PlaybackStatus.PLAYING : mellowplayer.PlaybackStatus.PAUSED;
        var songTitle = document.getElementById("eow-title").innerText;
        var artistName = document.getElementsByClassName("yt-user-info")[0].innerText;
        try {
            var artUrl = document.getElementsByClassName("branding-img-container")[0].children[0].src;
        }
        catch (e) {
            var artUrl = "";
        }
    }
    catch (e) {
        var rawPosition = "00:00";
        var rawDuration = "00:00";
        var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
        var songTitle = "";
        var artistName = "";
        var artUrl = "";
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": toMilliseconds(rawDuration),
        "position": toMilliseconds(rawPosition),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": "",
        "artUrl": artUrl,
        "isFavorite": false
    };
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

}

function setVolume(volume) {

}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {

}
