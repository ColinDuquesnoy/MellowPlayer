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
// Updates service information
function updatePlayerInfo() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();

    // Get next/previous cloudcasts
    var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
    var previous = M.playerQueue.queue.cloudcastList.get(currentIndex - 1);

    if (M.player.buffering) {
        playback_status = mellowplayer.PlaybackStatus.BUFFERING;
    } else if (M.player.playing) {
        playback_status = mellowplayer.PlaybackStatus.PLAYING;
    } else if (updateSongInfo()["SongTitle"]) {
        playback_status = mellowplayer.PlaybackStatus.PAUSED;
    } else {
        playback_status = mellowplayer.PlaybackStatus.STOPPED;
    }

    return {
        "PlaybackStatus": playback_status,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": typeof previous != "undefined",
        "CanAddToFavorites": true,
        "Volume": M.player.volume,
    }
}

function updateSongInfo() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    var cloudcast = M.player.currentCloudcast;
    return {
        "SongId": cloudcast.id,
        "SongTitle": cloudcast.title,
        "ArtistName": cloudcast.owner,
        "AlbumTitle": '',
        "ArtUrl": M.player.currentCloudcast.widgetImage,
        "Favorite": $('.icon-favorite-inner').get(0).getAttribute('class').match("ng-hide") == null,
        "Duration": M.player.audioLength,
        "Position": M.player.audioPosition
    }
}

function play() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    M.player.togglePlayClick();
}

function pause() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    M.player.togglePlayClick();
}

function goNext() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
    var next = M.playerQueue.queue.cloudcastList.get(currentIndex + 1);
    if (typeof next != "undefined") {
        M.playerQueue.playFromQueue(next);
    } else {
        M.playerQueue.playUpNext();
    }
}

function goPrevious() {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
    var previous = M.playerQueue.queue.cloudcastList.get(currentIndex + -1);
    if (typeof previous != "undefined") {
        M.playerQueue.playFromQueue(previous);
    }
}

function setVolume(volume) {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    M.player.volume = volume;
}

function addToFavorites() {
    // simulate a click on favorite button
    $('.icon-favorite-inner').get(0).click()
}

function removeFromFavorites() {
    // simulate a click on favorite button
    $('.icon-favorite-inner').get(0).click()
}

function seekToPosition(position) {
    // Get a reference to the mixcloud's player queue controller
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    M.$emit("slider:stop", position)
}
