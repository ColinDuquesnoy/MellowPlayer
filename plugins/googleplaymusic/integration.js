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

//-----------------------------------------------------------------------------
// Lots of hints here from https://github.com/ColinDuquesnoy/MellowPlayer
//-----------------------------------------------------------------------------

function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getButtons() {
    return {
        playpause: document.getElementById("player-bar-play-pause"),
        skip: document.getElementById("player-bar-forward"),
        back: document.getElementById("player-bar-rewind")
    };
}

//-----------------------------------------------------------------------------
// Much of this was adapted from: https://github.com/tiliado/nuvola-app-google-play-music
//-----------------------------------------------------------------------------
function update() {
    var controlClassName = document.querySelector("#player div.material-player-middle").children[3].className;
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (controlClassName === "x-scope paper-icon-button-0 playing")
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (controlClassName === "x-scope paper-icon-button-0")
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

    var elm;

    var artUrl = null;
    try {
        artUrl = document.querySelector("#playerSongInfo #playerBarArt").src.replace("=s90-", "=s500-");
    } catch (e) {}

    var songTitle = null;
    try {
        elm = document.querySelector("#playerSongInfo #currently-playing-title");
        songTitle = elm.innerText || elm.textContent;
    } catch (e) {}

    var songID = null;
    try {
        songID = getHashCode(songTitle);
    } catch (e) {}

    var artistName = null;
    try {
        elm = document.getElementById('player-artist').firstChild;
        artistName = elm.innerText || elm.textContent;
    } catch (e) {}

    var albumTitle = null;
    try {
        elm = document.querySelector("#playerSongInfo .player-album");
        albumTitle = elm.innerText || elm.textContent;
    } catch (e) {}

    //-----------------------------------------------------------------------------
    // Credit for this code to http://stackoverflow.com/questions/13437796/convert-any-string-time-to-seconds
    //-----------------------------------------------------------------------------
    var duration = 0;
    try {
        duration = document.querySelector("#material-player-right-wrapper #time_container_duration").innerText;
        var dtimes = duration.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {}

    var position = 0;
    try {
        position = document.querySelector("#material-player-right-wrapper #time_container_current").innerText;
        var ptimes = position.split(":");
        var pminutes = ptimes[0];
        var pseconds = ptimes[1];
        position = parseInt(pseconds, 10) + (parseInt(pminutes, 10) * 60);
    } catch (e) {}

    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": duration,
        "position": position,
        "songId": songID,
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": false
    }
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