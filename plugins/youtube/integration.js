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
var previousSongTitle = "";
var previousArtUrl = "";

function getButtons() {
    return {
        play: document.getElementsByClassName("ytp-play-button")[0],
        pause: document.getElementsByClassName("ytp-play-button")[0],
        skip: document.getElementsByClassName("ytp-next-button")[0]
    };
}

function update() {
    var rawPosition = "00:00";
    var rawDuration = "00:00";
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    var songTitle = "";
    var artistName = "";
    var artUrl = "";

    if (document.URL.indexOf("watch") !== -1) {
        try {
            var rawPosition = document.getElementsByClassName("ytp-time-current")[0].innerText;
            var rawDuration = document.getElementsByClassName("ytp-time-duration")[0].innerText;
            var playbackStatus = getButtons().play.attributes["aria-label"].value === "Pause" ? mellowplayer.PlaybackStatus.PLAYING : mellowplayer.PlaybackStatus.PAUSED;
            var songTitle = document.querySelector("#container > h1").innerText;
            var artistName = document.getElementById('owner-name').children[0].innerText
            try {
                var artUrl = document.querySelector("#meta-contents #avatar #img").src
            } catch (e) {
                var artUrl = "";
            }
        } catch (e) { }

        // prevent duplicate notifications while while loading new art url (previous art url remains)
        if (songTitle !== previousSongTitle && artUrl === previousArtUrl) {
            artUrl = "";
        }
        else {
            previousArtUrl = artUrl;
            previousSongTitle = songTitle;
        }
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": toSeconds(rawDuration),
        "position": toSeconds(rawPosition),
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