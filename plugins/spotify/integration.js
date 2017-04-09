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
function update() {
    var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    var volume = 1.0;
    var songId = "";
    var songTitle = "";
    var artistName = "";
    var albumTitle = "";
    var artUrl = "";
    var duration = 0;
    var position = 0;

    if (Spotify.Shuttle._initContext != null) {
        var playerContext = Spotify.Shuttle._initContext.contextPlayer;
        var player = playerContext._player._player;
        var track = playerContext.getCurrentTrack();
        if (player.isPaused && !playerContext._fakePlayingState) {
            playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
        }
        else if (player.isStopped) {
            playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
        }

        volume = player.getVolume();

        if (track != null) {
            songId = track._pid;
            songTitle = track.name;
            artistName = track.artistName;
            albumTitle = track.albumTitle;
            artUrl = track.image.replace('https://d3rt1990lpmkn.cloudfront.net/unbranded/', 'https://i.scdn.co/image/');
            duration = track.duration / 1000;       // milliseconds to seconds
            position = player.position() / 1000;    // milliseconds to seconds
        }
    }

    return {
        "songId": songId,
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": false,
        "duration": duration,
        "position": position,
        "playbackStatus": playbackStatus,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": volume
    }
}

function play() {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    player.playpause();
}

function pause() {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    player.playpause();
}

function goNext() {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    playerContext.next('fwdbtn');
}

function goPrevious() {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    playerContext.previous('backbtn');
}

function setVolume(volume) {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    player.setVolume(volume);
}

function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function seekToPosition(position) {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    player.seek(position * 1000)  // spotify works with milliseconds
}
