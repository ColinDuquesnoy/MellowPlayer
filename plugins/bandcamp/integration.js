function update() {
    if (document.location.toString().endsWith("feed")) {
        return {
            "playbackStatus": getPlaybackStatusOnHome(),
            "canSeek": false,
            "canGoNext": false,
            "canGoPrevious": false,
            "canAddToFavorites": false,
            "volume": 1,
            "duration": readTotalOnFeed(),
            "position": readElapsedOnFeed(),
            "songId": getSongIdOnFeed(),
            "songTitle": getSongOnFeed(),    
            "artistName": getArtistNameOnFeed(),
            "albumTitle": getAlbumOnFeed(),
            "artUrl": getAlbumArtOnFeed(),
            "isFavorite": false
        };
    }
    else if (document.location.host === "bandcamp.com" || document.location.host ==="daily.bandcamp.com") {
        return {
            "playbackStatus": getPlaybackStatusOnHome(),
            "canSeek": false,
            "canGoNext": false,
            "canGoPrevious": false,
            "canAddToFavorites": false,
            "volume": 1,
            "duration": "",
            "position": "",
            "songId": getSongIdOnHome(),
            "songTitle": getSongTitleOnHome(),    
            "artistName": getArtistNameOnHome(),
            "albumTitle": getAlbumTitleOnHome(),
            "artUrl": getAlbumArtOnHome(),
            "isFavorite": false
        };
    }
    else {
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

function getPlaybackStatusOnHome() {
    var miniPlayer=document.getElementsByClassName("playbutton playing");
    var a=document.getElementsByClassName("playing");
    if (miniPlayer.length > 0 || a.length > 0) {
            return mellowplayer.PlaybackStatus.PLAYING;
    }
    else {
        return mellowplayer.PlaybackStatus.STOPPED;
    }
}

function clickButton(buttonName) {
    document.getElementsByClassName(buttonName)[0].click();
}

function clickOnHome() {
    try {
        var parent=document.getElementsByClassName("playing");
        var button = parent[0].getElementsByClassName("plb-btn")[0];
        button.click();    
    }
    catch (e) {

    }
}

function play() {
    if (document.location.toString().endsWith("feed")) {
        var m=document.getElementsByClassName("playing");
        m[1].getElementsByClassName("play-button")[0].click();
    }
    else if (document.location.host === "bandcamp.com" || document.location.host ==="daily.bandcamp.com") {
        clickButton("playbutton");
    }
    else {
        clickButton("playbutton");
    }
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

function readTimeString(stringTime) {
    try {
        var time = stringTime.split(":");
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

function readElapsedOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        var elapsed = m[1].getElementsByClassName("time_elapsed")[0];
        if (elapsed != undefined) {
            return readTimeString(elapsed.innerHTML);
        }
    } catch (e) {
        return 0;
    }
}

function readTotalOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        var total = m[1].getElementsByClassName("time_total")[0];
        if (total != undefined) {
            return readTimeString(total.innerHTML);
        }
    } catch (e) {
        return 0
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

function getAlbumTitleOnHome() {
    try {
        var miniPlayer=document.getElementsByClassName("playbutton playing");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".detail-album > a:nth-child(1)").innerHTML;
        }
        var a=document.getElementsByClassName("playing")[0].parentNode.parentNode.getElementsByClassName("item-title")[0];
        //console.log("a "+ a);
        if (a.tagName == "H4") {
            return a.firstElementChild.firstElementChild.innerHTML;
        }
        a = a.innerHTML.trim();
        if (a.search("span") != -1) {
            return a.substring(34,a.length - 7);
        }
        else if (a.startsWith("by ")) {
            return a.substring(3);
        }
        else {
            return a;
        }
    }
    catch (e) {
        return ""
    }
}

function getArtistName() {
    try {
        return document.querySelectorAll("#band-name-location > span:nth-child(1)")[0].innerHTML.trim();0
    }
    catch (e) {
        return ""
    }
}

function getArtistNameOnHome() {
    try {
        var miniPlayer=document.getElementsByClassName("playbutton playing");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".detail-artist > a:nth-child(1)").innerHTML;
        }
        var a=document.getElementsByClassName("playing")[0].parentNode.parentNode.getElementsByClassName("item-artist")[0].innerHTML.trim();
        //console.log("a "+ a);
        if (a.search("span") != -1) {
            return a.substring(34,a.length - 7);
        }
        else if (a.startsWith("by ")) {
            return a.substring(3);
        }
        else {
            return a;
        }
    }
    catch (e) {
        var miniPlayer=document.getElementsByClassName("playbutton");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".detail-artist > a:nth-child(1)").innerHTML;
        }
        return "";
    }
}

function getArtistNameOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        var longName = m[1].getElementsByClassName("collection-item-artist")[0].innerHTML;
        if (longName.startsWith("by ")) {
            return longName.substring(3);
        }
        return m[1].getElementsByClassName("collection-item-artist")[0].innerHTML;
    }
    catch (e) {
        return "";
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

function getSongTitleOnHome() {
    try {
        var miniPlayer=document.getElementsByClassName("playbutton playing");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".title").innerHTML;
        }
        //var a=document.getElementsByClassName("playing")[0].parentNode.parentNode.getElementsByClassName("item-title")[0].innerHTML.trim();
        var a=document.getElementsByClassName("playing")[0].parentNode.parentNode.getElementsByClassName("item-title")[0];
        if (a.tagName == "H4") {
            return a.firstElementChild.firstElementChild.innerHTML;
        }
        //console.log("a "+ a);
        a = a.innerHTML.trim();
        //console.log("a "+ a);
        if (a.search("span") != -1) {
            return a.substring(34,a.length - 7);
        }
        else if (a.startsWith("by ")) {
            return a.substring(3);
        }
        else {
            return a;
        }
    }
    catch (e) {
        var miniPlayer=document.getElementsByClassName("playbutton");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".title").innerHTML;
        }
        return "";
    }
}

function getAlbumOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        return m[1].getElementsByClassName("collection-item-title")[0].innerHTML;
    }
    catch (e) {
        return "";
    }
}

function getSongOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        var song = m[1].getElementsByClassName("fav-track-title")[0];
        if (song == undefined || song == "") {
            return getAlbumOnFeed();
        }
        else {
            return song.innerHTML;
        }
    }
    catch (e) {
        return "";
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

function getAlbumArtOnHome() {
    try {
        var miniPlayer=document.getElementsByClassName("playbutton playing");
        if (miniPlayer.length == 1) {
            //console.log("mini "+ miniPlayer);
            return document.querySelector(".detail-art").href;
        }
        var playing = document.getElementsByClassName("playing")[0];
        return playing.getElementsByTagName("img")[0].src;
    }
    catch (e) {
        return ""
    }
}

function getAlbumArtOnFeed() {
    try {
        var m=document.getElementsByClassName("playing");
        return m[1].getElementsByTagName("img")[0].src;
    }
    catch (e) {
        return "";
    }
}

function getSongId() {
	var songName = getSongTitle();
	if (songName != "") {
		return getHashCode(songName);
	}
	return ""
}

function getSongIdOnHome() {
    var songName = getSongTitleOnHome();
    if (songName != "") {
        return getHashCode(songName);
    }
    return ""
}

function getSongIdOnFeed() {
    var songName = getSongOnFeed();
    if (songName != "") {
        return getHashCode(songName);
    }
    return ""
}

