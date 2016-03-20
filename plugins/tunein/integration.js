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

function getPlaybackStatus() {
    var retVal = mellowplayer.PlaybackStatus.STOPPED;
    var stateStr = TuneIn.app.getPlayState();
    if(stateStr === 'playing')
        retVal = mellowplayer.PlaybackStatus.PLAYING;
    else if(stateStr === 'stopped')
        retVal = mellowplayer.PlaybackStatus.PAUSED;
    return retVal;
}


function updatePlayerInfo() {
    return {
        "PlaybackStatus": getPlaybackStatus(),
        "CanSeek": false,
        "CanGoNext": false,
        "CanGoPrevious": false,
        "CanAddToFavorites": true,
        "Volume": 1,
    }
}

function updateSongInfo() {
    var broadcast = TuneIn.app.getNowPlaying();
    var stopped = getPlaybackStatus() === mellowplayer.PlaybackStatus.STOPPED;
    var retVal = {
        "SongId": 0,
        "SongTitle": '',
        "ArtistName": '',
        "AlbumTitle": '',
        "ArtUrl": '',
        "Favorite": false,
        "Duration": 0,
        "Position": 0
    };   
    if(broadcast == undefined) {
        if(!stopped && oldSongInfo != null) {
            retVal = oldSongInfo;
        }
    } else {
        retVal.SongId = broadcast.GuideId;
        retVal.SongTitle = broadcast.Title;
        retVal.AlbumTitle = broadcast.Subtitle;
        retVal.ArtUrl = broadcast.Image;
        retVal.Favorite = $(".in").length > 0;
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
