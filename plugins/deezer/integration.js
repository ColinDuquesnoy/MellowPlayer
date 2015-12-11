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
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (dzPlayer.isPlaying())
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (dzPlayer.isPaused())
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    else if (dzPlayer.isLoading())
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;

    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": dzPlayer.control.canSeek(),
        "CanGoNext": dzPlayer.getNextSong() != null,
        "CanGoPrevious": dzPlayer.getPrevSong() != null,
        "CanAddToFavorites": false,
        "Volume": dzPlayer.volume,
    }
}

function updateSongInfo() {
    return {
        "SongId": dzPlayer.getSongId(),
        "SongTitle": dzPlayer.getSongTitle(),
        "ArtistName": dzPlayer.getArtistName(),
        "AlbumTitle": dzPlayer.getAlbumTitle(),
        "ArtUrl": 'http://e-cdn-images.deezer.com/images/cover/' +
            dzPlayer.getCover() + '/250x250.jpg',
        "Favorite": false,
        "Duration": dzPlayer.getDuration(),
        "Position": dzPlayer.getPosition()
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

function addToFavorites(add) {
    // not supported
}

function seekToPosition(position) {
    // (0 = beginning, 1 = end)
    var normalizedPos = position / dzPlayer.getDuration();
    dzPlayer.control.seek(normalizedPos)
}