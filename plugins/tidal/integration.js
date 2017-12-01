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
        var playerInfoDiv = document.getElementsByClassName("player")[0].children[1].children[0];

        results.playbackStatus = isPaused() ? mellowplayer.PlaybackStatus.PAUSED : mellowplayer.PlaybackStatus.PLAYING;
        results.canGoNext = !getButtons().next.disabled;
        results.canGoPrevious = !getButtons().previous.disabled;
        results.songTitle = playerInfoDiv.children[1].children[0].text;
        results.artistName = playerInfoDiv.children[1].children[1].textContent;
        results.songId = getHashCode(results.songTitle);
        results.duration = toSeconds(document.getElementsByClassName("js-duration")[0].lastChild.nodeValue);
        results.position = toSeconds(document.getElementsByClassName("js-progress")[0].lastChild.nodeValue);
        results.artUrl = playerInfoDiv.children[0].children[1].children[0].src;
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
