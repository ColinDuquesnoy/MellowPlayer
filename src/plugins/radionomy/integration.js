function playPauseButton() {
    return document.getElementsByClassName("jp-pause")[0];
}

function getPlaybackStatus() {
    try {
        var displayType = playPauseButton().style.display;
        
        if (displayType === "block")
            return mellowplayer.PlaybackStatus.PLAYING;
        else
            return mellowplayer.PlaybackStatus.PAUSED;
    }
    catch (e)
    {
        return mellowplayer.PlaybackStatus.STOPPED;
    }
}

function getArtistAndTitle() {
    return document.querySelector("#jp_container_1 > div > div.rad-tracks > ul > li").innerText;
}

function getArtist() {
    try {
        return getArtistAndTitle().split("-")[0].trim();
    }
    catch (e) {
        return "";
    }
}

function getSongTitle() {
    try {
        return getArtistAndTitle().split("-")[1].trim();
    }
    catch (e) {
        return getRadioName();
    }
}

function getRadioName() {
    try {
        return document.querySelector("#jp_container_1 > div > div.jp-details > ul > li > a").innerText;
    }
    catch(e) {
        return "";
    }
}

function getArtUrl() {
    return document.querySelector("#jp_container_1 > div > div.jp-details > ul > li > img").src;
}

function isFavorite() {
    src = document.querySelector("#jp_container_1 > div > div.rad-actions > ul > li.fav > a > img").src;
    return src.indexOf("Unfav") === -1;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": getHashCode(getArtistAndTitle()),
        "songTitle": getSongTitle(),
        "artistName": getArtist(),
        "albumTitle": getRadioName(),
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite()
    };
}

function play() {
    playPauseButton().click();
}

function pause() {
    playPauseButton().click();
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
    document.querySelector("#jp_container_1 > div > div.rad-actions > ul > li.fav > a").click();
}

function removeFromFavorites() {
    addToFavorites();
}

function seekToPosition(position) {
    // not supported
}
