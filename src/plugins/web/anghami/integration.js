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
var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;

function update() {
    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getSongId(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getAlbumArt(),
        "isFavorite": false
    };
}

function getDuration() {
    var remaining = $('#player .duration')[0];
    var position = $('#player .position')[0];
    if (remaining === undefined || position === undefined) {
        return 0
    }
    return toSeconds(remaining.innerText.substr(2)) + toSeconds(position.innerText)
}

function getPosition() {
    var position = $('#player .position')[0];
    if (position === undefined) {
        return 0
    }
    return toSeconds(position.innerText)
}

function getSongId() {
   var title = getTitle();
   if (title === undefined) {
       return 0
   }
   return getHashCode(title);
}

function getAlbumArt() {
    var albumArt = $('.cover-art img')[0];
    if (albumArt === undefined) {
        return ''
    }
    return albumArt.attributes.src.value
}

function getTitle() {
    var title = $('#player .track-title a')[0];
    if (title === undefined) {
        return ''
    }
    return title.innerText
}

function getArtist() {
    var artist = $('#player .track-artist')[0];
    if (artist === undefined) {
        return ''
    }
    return artist.innerText
}

function play() {
    $('#player .icon-play').click();
    playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
}

function pause() {
    $('#player .icon-pause-2').click();
    playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
}

function goNext() {
    $('#player .icon-next-1').click();
}

function goPrevious() {
    $('#player .icon-previous-1').click();
}

function setVolume(volume) {

}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {

}
