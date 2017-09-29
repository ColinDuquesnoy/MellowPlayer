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
function getPlayerScope() {
    return angular.element("#players").scope();
}

function update() {
    var scope = getPlayerScope();

    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (scope.mediaPlayer.buffering) {
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
    } else if (scope.mediaPlayer.remotePlayerState.playing) {
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    } else {
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": scope.mediaPlayer.player.getVolume(),
        "duration": scope.mediaPlayer.episode.duration,
        "position": Math.floor(scope.mediaPlayer.player.getCurrentTimeInSeconds()),
        "songId": getHashCode(scope.mediaPlayer.episode.title),
        "songTitle": scope.mediaPlayer.episode.title,
        "artistName": scope.mediaPlayer.podcast.author,
        "albumTitle": "",
        "artUrl": scope.mediaPlayer.remotePlayerState.albumArt,
        "isFavorite": scope.mediaPlayer.episode.starred
    };
}

function play() {
    getPlayerScope().playPause();
}

function pause() {
    getPlayerScope().playPause();
}

function goNext() {
    getPlayerScope().jumpForward();
}

function goPrevious() {
    getPlayerScope().jumpBack();
}

function setVolume(volume) {
    getPlayerScope().mediaPlayer.player.setVolume(volume);
}

function addToFavorites() {
}

function removeFromFavorites() {
}

function seekToPosition(position) {
    getPlayerScope().mediaPlayer.seekTo(position);
}
