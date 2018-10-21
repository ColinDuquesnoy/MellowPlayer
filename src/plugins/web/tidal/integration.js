var previousID = -1;

function getItemByTestID(buttonName, parent) {
    parent = parent || document;
    return parent.querySelectorAll("[data-test-id=\""+buttonName+"\"]")[0];
}

function isPaused() {
    return getItemByTestID("play");
}

function getAlbumTitle() {
    var links = document.getElementsByClassName("infoTable--22VxO")[0].getElementsByTagName('a');
    for(var link = 0; link < links.length; link++)
        if(links[link].href.indexOf("/album/") !== -1)
            return links[link].innerHTML;
    return "";
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
    sendMouseEventToElement(element, 'mouseenter', relativeX, relativeY);
    sendMouseEventToElement(element, 'mousedown', relativeX, relativeY);
    sendMouseEventToElement(element, 'click', relativeX, relativeY);
    sendMouseEventToElement(element, 'mouseup', relativeX, relativeY);
    sendMouseEventToElement(element, 'mouseleave', relativeX, relativeY);
}

function update() {
    var results = {
        "playbackStatus": mellowplayer.PlaybackStatus.STOPPED,
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": 0,
        "songTitle": '',
        "artistName": '',
        "albumTitle": '',
        "artUrl": '',
        "isFavorite": false
    };

    // If player is loaded
    if(getItemByTestID("footer-player")) {
        var infoDiv = getItemByTestID("footer-player");
        results.songTitle = getItemByTestID("footer-track-title", infoDiv).children[0].innerHTML;
        results.songId = getHashCode(getItemByTestID("footer-track-title", infoDiv).children[0].href);
        
        results.playbackStatus = isPaused() ? mellowplayer.PlaybackStatus.PAUSED : mellowplayer.PlaybackStatus.PLAYING;
        if(window.getComputedStyle(getItemByTestID("loading-indicator", infoDiv)).getPropertyValue("display") !== "none") {
            results.playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
            previousID = results.songId;
        }
        
        results.artUrl = getItemByTestID("current-media-imagery", infoDiv).children[0].src;
        
        // On the initial song, there is no buffering, so we can accept the first valid album art
        if(previousID == -1)
            previousID = results.songId;
        
        
        // We skip the default album image placeholder, it loads before the first album loads, so on start there won't
        // be a album on MPRIS as it will be cached for the first loaded song, also it doesn't show up as it is svg
        if(results.artUrl.indexOf("defaultAlbumImage.78c633.svg") !== -1)
            results.artUrl = "";

        // also don't allow to load the art if we still hasn't started buffering.
        // We drop the status about the song until we find the art, so it won't create multiple item in the listening history
        if(results.songId != previousID || results.playbackStatus == mellowplayer.PlaybackStatus.BUFFERING) {
            results.songTitle = "";
            results.songId = 0;
            results.artUrl = "";
            
            return results;
        }

        results.canGoNext = !getItemByTestID("next", infoDiv).disabled;
        results.canGoPrevious = !getItemByTestID("previous", infoDiv).disabled;
        results.artistName = getItemByTestID("grid-item-detail-text-title-artist", infoDiv).innerHTML;
        // If it is paused, we use the seekbar's value, as if we seek, only that will be updated
        results.position = isPaused() ? getItemByTestID("progress-bar", infoDiv).getAttribute("aria-valuenow") : toSeconds(getItemByTestID("duration", infoDiv).children[0].innerHTML);
        results.duration = toSeconds(getItemByTestID("duration", infoDiv).children[1].innerHTML);
        results.volume = infoDiv.getElementsByClassName("nativeRange--EDim6")[0].value / 100;
        results.isFavorite = infoDiv.getElementsByClassName("mediaActions--3gVRx")[0].getElementsByClassName("button--1GSBa")[0].classList.contains("favorite--3ptX1");
        results.albumTitle = getAlbumTitle();
        results.canSeek = true;
        results.canAddToFavorites = true;
    }
    
    return results;
}

function play() {
    getItemByTestID("play").click();
}

function pause() {
    getItemByTestID("pause").click();
}

function goNext() {
    getItemByTestID("next").click();
}

function goPrevious() {
    getItemByTestID("previous").click();
}

function setVolume(volume) {
    if(volume == 0)
        getItemByTestID("volume", getItemByTestID("footer-player")).click();
    else{
        var volumeSlider = getItemByTestID("footer-player").getElementsByClassName("nativeRange--EDim6")[0];
        volumeSlider.value = volume * 100;
        volumeSlider.dispatchEvent(new Event('input', {
            'bubbles': true
        }));
    }
}

function addToFavorites() {
    getItemByTestID("footer-player").getElementsByClassName("mediaActions--3gVRx")[0].getElementsByClassName("button--1GSBa")[0].click();
}

function removeFromFavorites() {
    addToFavorites();
}

function seekToPosition(position) {
    var positionAsFraction = position / update().duration;   
    sendMouseClickToElement(getItemByTestID("interaction-layer", getItemByTestID("footer-player")), positionAsFraction, 0.5);   
}
