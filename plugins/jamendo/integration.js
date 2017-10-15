function getButtons() {
    return {
        "playPause": document.getElementsByClassName("player-controls_play")[0],
        "next": document.getElementsByClassName("player-controls_next")[0],
        "previous": document.getElementsByClassName("player-controls_previous")[0],
        "favorite": document.querySelector("#skeleton-player-mini > ul.player-mini_track-actions.list-button.hidden-xs.hidden-sm > li:nth-child(1) > button")
    }
}
function getPlaybackStatus() {
    var playButton = document.getElementsByClassName("player-controls_play")[0];

    if (playButton === undefined )
        return mellowplayer.PlaybackStatus.STOPPED;
    var playTitle = playButton.attributes["data-jam-title-play"].value;
    var pauseTitle = playButton.attributes["data-jam-title-pause"].value;

    if (playButton.title === playTitle)
        return mellowplayer.PlaybackStatus.PAUSED;
    else
        return mellowplayer.PlaybackStatus.PLAYING;
}

function getSongTitle() {
    try {
        return document.getElementsByClassName("player-mini_track_information_title")[0].innerText;
    }
    catch(e)
    {
        return ""
    }
}

function getArtist() {
    try {
        return document.getElementsByClassName("player-mini_track_information_artist")[0].innerText;
    }
    catch(e)
    {
        return ""
    }
}

function getTrackDurationAndPositionStrings() {
    var cleaned = document.getElementsByClassName("player-mini_track_duration")[0].innerText.replace("\n", "").replace(" ", "").replace(" ", "");
    return cleaned.split("/");
}

function getPosition() {
    try {
        return toSeconds(getTrackDurationAndPositionStrings()[0]);
    }
    catch(e)
    {
        return 0;
    }
}

function getDuration() {
    try {
        return toSeconds(getTrackDurationAndPositionStrings()[1]);
    }
    catch(e)
    {
        return 0;
    }
}

function getArtUrl() {
    try {
        return document.getElementsByClassName("js-full-player-cover-img")[0].src;
    }
    catch(e)
    {
        return "";
    }
}

function isFavorite() {
    try {
        return getButtons().favorite.className.indexOf("is-on") !== -1;
    }
    catch(e)
    {
        return false;
    }
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getHashCode(getSongTitle()),
        "songTitle": getSongTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite()
    };
}

function play() {
    getButtons().playPause.click();
}

function pause() {
    getButtons().playPause.click();
}

function goNext() {
    getButtons().next.click();
}

function goPrevious() {
    getButtons().previous.click();
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
    getButtons().favorite.click();
}

function removeFromFavorites() {
    getButtons().favorite.click();
}

function seekToPosition(position) {
    // not supported
}
