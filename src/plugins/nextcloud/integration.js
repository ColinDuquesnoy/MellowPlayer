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
        playpause: document.querySelector("a.sm2-inline-button.play-pause"),
        skip: document.querySelector("a.sm2-inline-button.next"),
        back: document.querySelector("a.sm2-inline-button.previous"),
    };
}

function updatePlayerInfo() {
    var controlClassName = document.getElementsByClassName("sm2-bar-ui")[0].className;
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (controlClassName == "sm2-bar-ui full-width playing")
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (controlClassName == "sm2-bar-ui full-width paused")
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": true,
        "CanAddToFavorites": false,
        "Volume": 1,
    };
}

//-----------------------------------------------------------------------------
// Much of this was adapted from: https://github.com/tiliado/nuvola-app-google-play-music
//-----------------------------------------------------------------------------

function updateSongInfo() {
    var elm;

    try {
        elm = document.getElementsByClassName("sm2-playlist-cover")[0]
        ArtURL = elm.baseURI;
    } catch (e) {
        ArtUrl = null;
    }


    try {
        elm = document.getElementsByClassName("selected")[0].getElementsByClassName("title")[0];
        songTitle = elm.innerHTML;
    } catch (e) {
        songTitle = null;
    }

    try {
        songID = getHashCode(songTitle);
    } catch (e) {
        songID = null;
    }

    try {
        elm = document.getElementsByClassName("selected")[0];
        ArtistName = elm.getAttribute("data-artist");
    } catch (e) {
        ArtistName = null;
    }

    try {
        elm = document.getElementsByClassName("selected")[0];
        AlbumTitle = elm.getAttribute("data-album");
    } catch (e) {
        AlbumTitle = null;
    }

    //-----------------------------------------------------------------------------
    // Credit for this code to http://stackoverflow.com/questions/13437796/convert-any-string-time-to-seconds
    //-----------------------------------------------------------------------------

    try {
        Duration = document.getElementsByClassName("sm2-inline-duration")[0].innerText;
        var dtimes = Duration.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        Duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {
        Duration = null;
    }

    try {
        Position = document.getElementsByClassName("sm2-inline-time")[0].innerText;
        var ptimes = Position.split(":");
        var pminutes = ptimes[0];
        var pseconds = ptimes[1];
        Position = parseInt(pseconds, 10) + (parseInt(pminutes, 10) * 60);
    } catch (e) {
        Position = null;
    }

    return {
        "SongId": songID,
        "SongTitle": songTitle,
        "ArtistName": ArtistName,
        "AlbumTitle": AlbumTitle,
        "ArtUrl": ArtUrl,
        "Favorite": false,
        "Duration": Duration,
        "Position": Position

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
