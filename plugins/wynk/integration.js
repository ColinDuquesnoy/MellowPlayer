function readTime(timeString) {
    var hours = 0;
    var minutes = 0;
    var seconds = 0;
    var m = timeString.match("\\d+:\\d+:\\d+");
    if (m !== null) {
        var data = timeString.split(':');
        hours = parseInt(data[0]);
        minutes = parseInt(data[1]);
        seconds = parseInt(data[2]);
    } else {
        var m = timeString.match("\\d+:\\d+");
        if (m !== null) {
            var data = timeString.split(':');
            minutes = parseInt(data[0]);
            seconds = parseInt(data[1]);
        }
    }
    return hours * 3600 + minutes * 60 + seconds;
}

function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function update() {
    if (document.querySelector("#wynk-player > div > div > div.right-part.cssload-container > span").className === "sprite play") {
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    } else if (document.querySelector("#wynk-player > div > div > div.right-part.cssload-container > span").className === "sprite pause") {
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    } else {
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
    }
    duration = document.querySelector("#wynk-player > div > div > div.bottom-part > div.seek-bar > span.right.ng-binding").innerHTML;
    position = document.querySelector("#wynk-player > div > div > div.bottom-part > div.seek-bar > span.left.ng-binding").innerHTML;
    songTitle = document.querySelector("#wynk-player > div > div > div.left-part > div > p.head > a").innerHTML;
    albumTitle = document.querySelector("#wynk-player > div > div > div.left-part > div > p.sub > a").innerHTML;
    artUrl = document.querySelector("#wynk-player > div > div > div.left-part > span > img").src;
    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": readTime(duration),
        "position": readTime(position),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": '',
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": false
    };
}

function play() {
    document.querySelector("#wynk-player > div > div > div.right-part.cssload-container > span").click();
}

function pause() {
    play();
}

function goNext() {
    document.querySelector("#wynk-player > div > div > div.bottom-part > div.prev-next > span.next > a").click();
}

function goPrevious() {
    document.querySelector("#wynk-player > div > div > div.bottom-part > div.prev-next > span.prev > a").click();
}

function setVolume(volume) {
    //not implemented
}

function addToFavorites() {
    //not implemented
}

function removeFromFavorites() {
    //not implemented
}

function seekToPosition(position) {
    //not implemented	
}