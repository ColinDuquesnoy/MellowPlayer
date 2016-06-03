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

//-----------------------------------------------------------------------------
// Lots of hints here from https://github.com/ColinDuquesnoy/MellowPlayer
//-----------------------------------------------------------------------------

function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getButtons() {
    return {
        playpause: document.getElementById("player-bar-play-pause"),
        skip: document.getElementById("player-bar-forward"),
        back: document.getElementById("player-bar-rewind"),
    };
}

function updatePlayerInfo() {
    var controlClassName = document.querySelector("#player div.material-player-middle").children[3].className;
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (controlClassName == "x-scope paper-icon-button-0 playing")
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (controlClassName == "x-scope paper-icon-button-0")
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

    return {
        "PlaybackStatus": playbackStatus,
        "CanSeek": true,
        "CanGoNext": true,
        "CanGoPrevious": true,
        "CanAddToFavorites": false,
        "Volume": 1,
    }
}
    
//-----------------------------------------------------------------------------
// Much of this was adapted from: https://github.com/tiliado/nuvola-app-google-play-music
//-----------------------------------------------------------------------------

function updateSongInfo() {
    var elm;
    
    try
    {
        ArtUrl = document.querySelector("#playerSongInfo #playerBarArt").src.replace("=s90-", "=s500-");
    }
    catch(e)
    {
        ArtUrl =  null;
    }
    
    try
    {
        elm = document.querySelector("#playerSongInfo #currently-playing-title");
        songTitle = elm.innerText || elm.textContent;
    }
    catch(e)
    {
        songTitle = null;
    }
    
    try
    {
        elm = document.getElementById('player-artist').firstChild;
        ArtistName = elm.innerText || elm.textContent;
    }
    catch (e)
    {
        ArtistName = null;
    }
    
    try
    {
        elm = document.querySelector("#playerSongInfo .player-album");
        AlbumTitle = elm.innerText || elm.textContent;
    }
    catch (e)
    {
        AlbumTitle = null;
    }
    
    duration = document.querySelector("#material-player-right-wrapper #time_container_duration").innerText;
    position = document.querySelector("#material-player-right-wrapper #time_container_current").innerText;

    //-----------------------------------------------------------------------------
    // Credit for this code to http://stackoverflow.com/questions/13437796/convert-any-string-time-to-seconds
    //-----------------------------------------------------------------------------
    
    try
    {
        Duration = document.querySelector("#material-player-right-wrapper #time_container_duration").innerText
        var dtimes = Duration.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        Duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    }
    catch (e)
    {
        Duration = null;
    }
    
    try
    {
        Position = document.querySelector("#material-player-right-wrapper #time_container_current").innerText;
        var ptimes = Position.split(":");
        var pminutes = ptimes[0];
        var pseconds = ptimes[1];
        Position = parseInt(pseconds, 10) + (parseInt(pminutes, 10) * 60);
    }
    catch (e)
    {
        Position = null;
    }
        
    return {
        "SongId": getHashCode(songTitle),
        "SongTitle": songTitle,
        "ArtistName": ArtistName,
        "AlbumTitle": AlbumTitle,
        "ArtUrl": ArtUrl,
        "Favorite": false,
<<<<<<< HEAD
        "Duration": Duration,
        "Position": Position
=======
        "Duration": duration, 
        "Position": position
>>>>>>> ca8e97a4299b9fb44c89adad03602b7427b4f648
    }
}

function play() {
    
    getButtons().playpause.click()
    
}

function pause() {
    
    getButtons().playpause.click()
    
}

function goNext() {
    
    getButtons().skip.click()
    
}

function goPrevious() {
    
    getButtons().back.click()
    
}

function setVolume(volume) {
    
 // not currently supported
    
}


function addToFavorites() {
    
 // not currently supported
    
}

function removeFromFavorites() {
    
 // not currently supported
    
}

function seekToPosition(position) {
    
 // not currently supported
    
}
