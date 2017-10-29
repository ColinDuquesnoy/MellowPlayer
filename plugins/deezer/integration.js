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
function getLoveButton() {
    return document.querySelector("#player-cover > div.player-actions.clearfix > span:nth-child(2) > button");
}

function update() {
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (dzPlayer.isPlaying())
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (dzPlayer.isPaused())
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    else if (dzPlayer.isLoading())
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;

    return {
        "playbackStatus": playbackStatus,
        "canSeek": dzPlayer.control.canSeek(),
        "canGoNext": dzPlayer.getNextSong() !== null,
        "canGoPrevious": dzPlayer.getPrevSong() !== null,
        "canAddToFavorites": true,
        "volume": dzPlayer.volume,
        "position": dzPlayer.getPosition(),
        "duration": dzPlayer.getDuration(),
        "isFavorite": isFavorite(),
        "songId": dzPlayer.getSongId(),
        "songTitle": dzPlayer.getSongTitle(),
        "artistName": dzPlayer.getArtistName(),
        "albumTitle": dzPlayer.getAlbumTitle(),
        "artUrl": 'http://e-cdn-images.deezer.com/images/cover/' + dzPlayer.getCover() + '/250x250.jpg'
    }
}

function isFavorite() {
    try {
        return getLoveButton().className.indexOf("is-active") !== -1
    }
    catch (e) {
        return false;
    }
}

function play() {
    dzPlayer.control.play();
}

function pause() {
    dzPlayer.control.pause();
}

function goNext() {
    dzPlayer.control.nextSong();
}

function goPrevious() {
    dzPlayer.control.prevSong();
}

function setVolume(volume) {
    dzPlayer.control.setVolume(volume);
}

function addToFavorites() {
    getLoveButton().click();
}

function removeFromFavorites() {
    getLoveButton().click();
}

function seekToPosition(position) {
    // (0 = beginning, 1 = end)
    var normalizedPos = position / dzPlayer.getDuration();
    dzPlayer.control.seek(normalizedPos)
}