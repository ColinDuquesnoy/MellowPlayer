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
    var controlClassName = document.getElementsByClassName('playControl')[0].className;
    var playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    if (controlClassName.indexOf("playing") != -1)
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (controlClassName.indexOf("disabled") != -1)
        playbackStatus = mellowplayer.PlaybackStatus.STOPPED;

    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": true,
        "CanAddToFavorites": false,
        "Volume": 1,
    }
}

function readTime(elementClassName) {
    var html = document.getElementsByClassName(
        elementClassName)[0].innerHTML;
    var hours = 0;
    var minutes = 0;
    var seconds = 0;
    var m = html.match("<span .*>(\\d+:\\d+:\\d+)<\/span>");
    if (m != null) {
        var data = m[1].split(':');
        hours = parseInt(data[0]);
        minutes = parseInt(data[1]);
        seconds = parseInt(data[2]);
    } else {
        var m = html.match("<span .*>(\\d+:\\d+)<\/span>");
        if (m != null) {
            var data = m[1].split(':');
            console.log(data);
            minutes = parseInt(data[0]);
            seconds = parseInt(data[1]);
        }
    }
    var total = hours * 3600 + minutes * 60 + seconds;
    return total;
}

function updateSongInfo() {
    try {
        var artUrl = document.getElementsByClassName('playbackSoundBadge')[
            0].children[0].children[0].children[0].style["background-image"];
        artUrl = artUrl.replace("url(", "").replace(")", "").replace('50x50', '250x250');
        var songId = artUrl.match('-(\\d*)-')[1];
    } catch (e) {
        var songId = 0;
        var artUrl = '';
    }
    try {
        var songTitle = document.getElementsByClassName('playbackSoundBadge__title')[0].title;
    } catch (e) {
        songTitle = '';
    }
    return {
        "SongId": songId,
        "SongTitle": songTitle,
        "ArtistName": '',
        "AlbumTitle": '',
        "ArtUrl": artUrl,
        "Favorite": false,
        "Duration": readTime('playbackTimeline__duration'),
        "Position": readTime('playbackTimeline__timePassed')
    }
}

function clickButton(buttonName) {
    document.getElementsByClassName(buttonName)[0].click()
}

function play() {
    clickButton('playControl');
}

function pause() {
    play();
}

function goNext() {
    clickButton('skipControl__next');
}

function goPrevious() {
    clickButton('skipControl__previous');
}

function setVolume(volume) {
    // not supported
}


function addToFavorites(add) {
    // not supported
}

function seekToPosition(position) {

}