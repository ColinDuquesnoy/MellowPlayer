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
function getButtons() {
    return {
        playpause: document.getElementById("player-bar-play-pause"),
        skip: document.getElementById("player-bar-forward"),
        back: document.getElementById("player-bar-rewind"),
        thumbUp: document.querySelector('#player .player-rating-container [icon^="sj:thumb-"][data-rating="5"]'),
        seekBar: document.getElementById('progressContainer')
    };
}
// The two functions below can be used to control playback position and volume level
// See https://www.martin-brennan.com/simulating-mouse-click-event-javascript/ , 
// https://developer.mozilla.org/en-US/docs/Web/API/Element/getBoundingClientRect
// and https://developer.mozilla.org/en-US/docs/Web/API/MouseEvent for details
/**
 * @param element    (HTMLElement) Element to send events to. 
 * @param eventName  (String) type of the MouseEvent to send. 
 * @param relativeX  (Float) relative x position within the boundaries of the element, 
 * as a fraction of the element's width(0..1). 
 * @param relativeY  (Float) relative y position within the boundaries of the element,
 * as a fraction of the element's height(0..1).
*/
function sendMouseEventToElement(element, eventName, relativeX, relativeY) {
    var clientRect = element.getBoundingClientRect();   
    var event = new MouseEvent(eventName, {
        'view': window,
        'bubbles': true,
        'cancelable': true,
        'clientX': clientRect.left + (clientRect.width * relativeX),
        'clientY': clientRect.top + (clientRect.height * relativeY)
    });
    element.dispatchEvent(event);
}
/**
 * Emulates mouse click on the specified position of the given element
 * @param element    (HTMLElement) Element to send click to. 
 * @param relativeX  (Float) relative x position within the boundaries of the element, 
 * as a fraction of the element's width(0..1). 
 * @param relativeY  (Float) relative y position within the boundaries of the element,
 * as a fraction of the element's height(0..1).
*/
function sendMouseClickToElement(element, relativeX, relativeY) {
    sendMouseEventToElement(element, 'mouseover', relativeX, relativeY);
    sendMouseEventToElement(element, 'mousedown', relativeX, relativeY);
    sendMouseEventToElement(element, 'mouseup', relativeX, relativeY);
}

//-----------------------------------------------------------------------------
// Much of this was adapted from: https://github.com/tiliado/nuvola-app-google-play-music
//-----------------------------------------------------------------------------
function update() {
    var pp = getButtons().playpause;
    var playbackStatus;

    if (!pp || pp.disabled)
        playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    else if (pp.className.indexOf("playing") != -1)
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

    var elm;

    var artUrl = null;
    try {
        artUrl = document.querySelector("#playerSongInfo #playerBarArt").src.replace("=s90-", "=s500-");
    } catch (e) {}

    var songTitle = null;
    try {
        elm = document.querySelector("#playerSongInfo #currently-playing-title");
        songTitle = elm.innerText || elm.textContent;
    } catch (e) {}

    var songID = null;
    try {
        songID = getHashCode(songTitle);
    } catch (e) {}

    var artistName = null;
    try {
        elm = document.getElementById('player-artist').firstChild;
        artistName = elm.innerText || elm.textContent;
    } catch (e) {}

    var albumTitle = null;
    try {
        elm = document.querySelector("#playerSongInfo .player-album");
        albumTitle = elm.innerText || elm.textContent;
    } catch (e) {}

    //-----------------------------------------------------------------------------
    // Credit for this code to http://stackoverflow.com/questions/13437796/convert-any-string-time-to-seconds
    //-----------------------------------------------------------------------------
    var duration = 0;
    try {
        duration = document.querySelector("#material-player-right-wrapper #time_container_duration").innerText;
        var dtimes = duration.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {}

    var position = 0;
    try {
        position = document.querySelector("#material-player-right-wrapper #time_container_current").innerText;
        var ptimes = position.split(":");
        var pminutes = ptimes[0];
        var pseconds = ptimes[1];
        position = parseInt(pseconds, 10) + (parseInt(pminutes, 10) * 60);
    } catch (e) {}

    elm = getButtons().skip;
    var canGoNext = elm != null && !elm.disabled;

    elm = getButtons().back;
    var canGoPrevious = elm != null && !elm.disabled;

    var canSeek = getButtons().seekBar != null && duration != 0;

    // Adapted from gmusic.js
    // please see https://github.com/gmusic-utils/gmusic.js/blob/master/src/namespaces/RatingNamespace.js
    // and https://github.com/gmusic-utils/gmusic.js/blob/master/src/constants/selectors.js

    elm = getButtons().thumbUp;
    var canAddToFavorites = elm != null && playbackStatus != mellowplayer.PlaybackStatus.STOPPED;
    var isFavorite = false;    
    try {
        isFavorite = elm.__data__.icon === 'thumb-up';
    } catch (e) {
        canAddToFavorites = false;
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": canSeek,
        "canGoNext": canGoNext,
        "canGoPrevious": canGoPrevious,
        "canAddToFavorites": canAddToFavorites,
        "volume": 1,
        "duration": duration,
        "position": position,
        "songId": songID,
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": isFavorite
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

    getButtons().thumbUp.click();

}

function removeFromFavorites() {

    getButtons().thumbUp.click();

}

function seekToPosition(position) {
    var positionAsFraction =  position  / update().duration;    
    sendMouseClickToElement(getButtons().seekBar, positionAsFraction, 0.5);   
}
