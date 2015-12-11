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
    var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    var volume = 1.0;
    if (Spotify.Shuttle._initContext != null) {
        var playerContext = Spotify.Shuttle._initContext.contextPlayer;
        var player = playerContext._player._player;
        if (player.isPaused) {
            playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
        } else if (player.isStopped) {
            playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
        }
        volume = player.getVolume();
    }
    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": true,
        "CanAddToFavorites": false,
        "Volume": volume
    }
}

function updateSongInfo() {
    if (Spotify.Shuttle._initContext != null) {
        var playerContext = Spotify.Shuttle._initContext.contextPlayer;
        var player = playerContext._player._player;
        var track = playerContext.getCurrentTrack();
        if (track != null) {
            return {
                "SongId": track._pid,
                "SongTitle": track.name,
                "ArtistName": track.artistName,
                "AlbumTitle": track.albumTitle,
                "ArtUrl": playerContext.getCurrentTrack().image.replace('https://d3rt1990lpmkn.cloudfront.net/unbranded/', 'https://i.scdn.co/image/'),
                "Favorite": false,
                "Duration": track.duration / 1000,
                "Position": player.position() / 1000
            }
        }
    }
    return {
        "SongId": '0',
        "SongTitle": '',
        "ArtistName": '',
        "AlbumTitle": '',
        "ArtUrl": '',
        "Favorite": false,
        "Duration": 0,
        "Position": 0
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


function addToFavorites(add) {
    // not supported
}

function seekToPosition(position) {
    var playerContext = playerContext = Spotify.Shuttle._initContext.contextPlayer;
    var player = playerContext._player._player;
    player.seek(position * 1000) // spotify works with milliseconds
}