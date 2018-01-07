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

function getPlayerScope() {
    var player = angular.element(document.getElementsByClassName("player-box1")[0]).scope();
    if (!player)
        throw "Null player";
}

function update() {
    try {
        var player = getPlayerScope();

        var audio = player.audio;
        var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
        if (audio.paused && !player.showLoadingSong)
            playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
        else if (!audio.paused && !player.showLoadingSong)
            playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
        else
            playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;

        return {
            "playbackStatus": playbackStatus,
            "canSeek": false,
            "canGoNext": true,
            "canGoPrevious": true,
            "canAddToFavorites": false,
            "volume": 1,
            "duration": toSeconds(document.getElementsByClassName("time")[1].innerText),
            "position": toSeconds(document.getElementsByClassName("time")[0].innerText),
            "songId": getHashCode(player.currentSong.title),
            "songTitle": player.currentSong.title,
            "artistName": player.currentSong.subtitleId,
            "albumTitle": player.currentSong.album,
            "artUrl": player.currentSong.largeImage,
            "isFavorite": false
        };
    }
    catch (e) {
        return  {}
    }
}

function play() {
    getPlayerScope().togglePlayer();
}

function pause() {
    getPlayerScope().togglePlayer();
}

function goNext() {
    getPlayerScope().next();
}

function goPrevious() {
    getPlayerScope().previous();
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