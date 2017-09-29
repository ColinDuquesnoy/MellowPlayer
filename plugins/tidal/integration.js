function getButtons() {
    return {
        "pause": document.getElementsByClassName("play-controls__pause")[0],
        "play": document.getElementsByClassName("play-controls__play")[0],
        "next": document.getElementsByClassName("play-controls__next")[0],
        "previous": document.getElementsByClassName("play-controls__previous")[0],
        "main": document.getElementsByClassName("play-controls__main-button")[0]
    }
}

function isPaused() {
    return document.getElementsByClassName("play-controls__main-button--paused").length !== 0;
}

function isPlayerVisible() {
    return document.getElementsByClassName("player--audio").length > 0;
}

function update() {
    console.error("up");

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

    if (isPlayerVisible()) {
        results.playbackStatus = isPaused() ? mellowplayer.PlaybackStatus.PAUSED : mellowplayer.PlaybackStatus.PLAYING;
        results.canGoNext = !getButtons().next.disabled;
        results.canGoPrevious = !getButtons().previous.disabled;
        results.songTitle = document.getElementsByClassName("player__text")[0].children[0].innerText;
        results.artistName = document.getElementsByClassName("player__text")[0].children[1].innerText;
        results.songId = getHashCode(results.songTitle);
        results.position = toSeconds(document.getElementsByClassName("player__elapsed-time__progress")[0].innerText);
        results.duration = toSeconds(document.getElementsByClassName("player__elapsed-time__duration")[0].innerText);
        results.artUrl = document.getElementsByClassName("player__image-container")[0].children[0].src;
    }

    return results;
}

function play() {
    getButtons().play.click();
}

function pause() {
    getButtons().pause.click();
}

function goNext() {
    getButtons().next.click();
}

function goPrevious() {
    getButtons().previous.click();
}

function setVolume(volume) {

}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {

}