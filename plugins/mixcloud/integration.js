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
function getMixcloudPlayer() {
    var M = $(document.querySelector(
        '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    return M;
}

function update() {
    // Get a reference to the mixcloud's player queue controller
    var M = getMixcloudPlayer();

    // Get next/previous cloudcasts
    var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
    var previous = M.playerQueue.queue.cloudcastList.get(currentIndex - 1);
    var cloudcast = M.player.currentCloudcast;

    if (M.player.buffering) {
        playback_status = mellowplayer.PlaybackStatus.BUFFERING;
    } else if (M.player.playing) {
        playback_status = mellowplayer.PlaybackStatus.PLAYING;
    } else if (cloudcast.title) {
        playback_status = mellowplayer.PlaybackStatus.PAUSED;
    } else {
        playback_status = mellowplayer.PlaybackStatus.STOPPED;
    }

    return {
        "playbackStatus": playback_status,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": typeof previous != "undefined",
        "canAddToFavorites": false,
        "volume": M.player.volume,
        "duration": M.player.audioLength,
        "position": M.player.audioPosition,
        "songId": cloudcast.id,
        "songTitle": cloudcast.title,
        "artistName": cloudcast.owner,
        "albumTitle": '',
        "artUrl": M.player.currentCloudcast.widgetImage,
        "isFavorite": false
    }
}

function play() {
    // Get a reference to the mixcloud's player queue controller
    var M = getMixcloudPlayer();
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
    var M = getMixcloudPlayer();
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
    var M = getMixcloudPlayer();
    var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
    var previous = M.playerQueue.queue.cloudcastList.get(currentIndex + -1);
    if (typeof previous != "undefined") {
        M.playerQueue.playFromQueue(previous);
    }
}

function setVolume(volume) {
    // Get a reference to the mixcloud's player queue controller
    var M = getMixcloudPlayer();
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
    var M = getMixcloudPlayer();
    M.$emit("slider:stop", position)
}
