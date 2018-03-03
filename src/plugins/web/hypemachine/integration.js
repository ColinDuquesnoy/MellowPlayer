function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": readTime("player-time-total"),
        "position": readTime("player-time-position"),
        "songId": getSongId(),
        "songTitle": getSongTitle(),    
        "artistName": getArtistName(),
        "albumTitle": getAlbumTitle(),
        "artUrl": getAlbumArt(),
        "isFavorite": isFavorite()
    };
}

function isFavorite() {
    return hasClass(document.getElementById("playerFav"), "fav-on");
}

function hasClass(elem, className) {
	try {
		return elem.classList.contains(className);
	}
	catch (e) {
        return false
    }
}

function getPlaybackStatus() {
    if (hasClass(document.getElementById("playerPlay"), "pause")) {
        return mellowplayer.PlaybackStatus.PLAYING;
    }
    else {
        return mellowplayer.PlaybackStatus.STOPPED;
    }
}

function clickButton(buttonName) {
    document.getElementById(buttonName).click();
}

function play() {
    clickButton("playerPlay");
}

function pause() {
    play();
}

function goNext() {
    clickButton("playerNext");
}

function goPrevious() {
    clickButton("playerPrev");
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
    clickButton("playerFav");
}

function removeFromFavorites() {
	clickButton("playerFav");
}

function seekToPosition(position) {
	// not supported
}

function readTime(elementClassName) {
	try {
	    var time = document.getElementById(elementClassName).innerHTML;
	    return toSeconds(time);
	}
	catch (e) {
        return 0;
    }
}

function getAlbumTitle() {
    return "";
}

function getArtistName() {
    try {
        return document.querySelectorAll("#player-nowplaying > a:nth-child(1)")[0].innerHTML.trim();
    }
    catch (e) {
        return ""
    }
}

function getSongTitle() {
    try {
        return document.querySelectorAll("#player-nowplaying > a:nth-child(3)")[0].innerHTML.trim();
    }
    catch (e) {
        return ""
    }
}

function getAlbumArt() {
    return "";
}

function getSongId() {
	var songName = getSongTitle();
	if (songName != "") {
		return getHashCode(songName);
	}
	return ""
}