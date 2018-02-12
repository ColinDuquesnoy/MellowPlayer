function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": hasNext(),
        "canGoPrevious": hasPrevious(),
        "canAddToFavorites": false,
        "volume": 1,
        "duration": readTime("time_total"),
        "position": readTime("time_elapsed"),
        "songId": getSongId(),
        "songTitle": getSongTitle(),    
        "artistName": getArtistName(),
        "albumTitle": getAlbumTitle(),
        "artUrl": getAlbumArt(),
        "isFavorite": false
    };
}

function hasNext() {
    return ! hasClass(document.getElementsByClassName("nextbutton")[0], "hiddenelem");
}

function hasPrevious() {
    return ! hasClass(document.getElementsByClassName("prevbutton")[0], "hiddenelem");
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
    if (hasClass(document.getElementsByClassName("playbutton")[0], "playing")) {
        return mellowplayer.PlaybackStatus.PLAYING;
    }
    else {
        return mellowplayer.PlaybackStatus.STOPPED;
    }
}

function clickButton(buttonName) {
    document.getElementsByClassName(buttonName)[0].click();
}

function play() {
    clickButton("playbutton");
}

function pause() {
    play();
}

function goNext() {
    clickButton("nextbutton");
}

function goPrevious() {
    clickButton("prevbutton");
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
	// not supported
}

function removeFromFavorites() {
	// not supported
}

function seekToPosition(position) {
	// not supported
}

function readTime(elementClassName) {
	try {
	    var time = document.getElementsByClassName(elementClassName)[0].innerHTML.split(":");
	    var minutes = 0;
	    var seconds = 0;
	    minutes = parseInt(time[0]);
	    seconds = parseInt(time[1]);
	    return minutes * 60 + seconds;
	}
	catch (e) {
        return 0;
    }
}

function getAlbumTitle() {
    try {
        return document.getElementsByClassName("trackTitle")[0].innerHTML.trim();
    }
    catch (e) {
        return ""
    }
}

function getArtistName() {
    try {
        return document.querySelectorAll("#band-name-location > span:nth-child(1)")[0].innerHTML.trim();
    }
    catch (e) {
        return ""
    }
}

function getSongTitle() {
    try {
        return document.querySelectorAll(".title_link > span:nth-child(1)")[0].innerHTML.trim();
    }
    catch (e) {
        return ""
    }
}

function getAlbumArt() {
    try {
        return document.querySelectorAll("#tralbumArt > a:nth-child(1)")[0].href;
    }
    catch (e) {
        return ""
    }
}

function getSongId() {
	var songName = getSongTitle();
	if (songName != "") {
		return getHashCode(songName);
	}
	return ""
}