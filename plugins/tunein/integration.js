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
var oldSongInfo = null;

function hashCode(str) {
    var hash = 0,
        i, chr, len;
    if (str.length === 0) return hash;
    for (i = 0, len = str.length; i < len; i++) {
        chr = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + chr;
        hash |= 0; // Convert to 32bit integer
    }
    return Math.abs(hash);
};

function getPlaybackStatus() {
    var stateStr = TuneIn.app.getPlayState();
    if (stateStr === 'playing') {
        return mellowplayer.PlaybackStatus.PLAYING;
    }
    else {
        if (stateStr === 'stopped') {
            return mellowplayer.PlaybackStatus.PAUSED;
        }
    }
    return mellowplayer.PlaybackStatus.STOPPED;
}

function update() {
    var retVal = {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": true,
        "volume": 1,
        "songId": 0,
        "songTitle": '',
        "artistName": 'TuneIn',
        "albumTitle": '',
        "artUrl": '',
        "isFavorite": false,
        "duration": 0,
        "position": 0
    };

    var broadcast = TuneIn.app.getNowPlaying();
    var stopped = getPlaybackStatus() === mellowplayer.PlaybackStatus.STOPPED;
    if (broadcast === undefined) {
        if (!stopped && oldSongInfo !== null) {
            retVal.songId = oldSongInfo.songId
            retVal.songTitle = oldSongInfo.songTitle
            retVal.artistName = oldSongInfo.artistName
            retVal.artUrl = oldSongInfo.artUrl
            retVal.isFavorite = oldSongInfo.isFavorite;
        }
    } else {
        retVal.songId = hashCode(broadcast.Title + broadcast.Subtitle);
        retVal.songTitle = broadcast.Title;
        retVal.artistName = broadcast.Subtitle;
        retVal.artUrl = broadcast.Image;
        retVal.isFavorite = $(".in").length > 0;
        oldSongInfo = retVal;
    }
    return retVal;
}

function play() {
    $(".playbutton-cont").click();
}

function pause() {
    play();
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
    $(".follow")[0].click()
}

function removeFromFavorites() {
    $(".follow")[0].click()
}

function seekToPosition(position) {
    // not supported
}