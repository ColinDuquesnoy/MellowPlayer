var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;

function update() {
    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getSongId(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getAlbumArt(),
        "isFavorite": false
    };
}

function toSeconds(string) {
    try {
        var dtimes = string.split(":");
        var dminutes = dtimes[0];
        var dseconds = dtimes[1];
        var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);
    } catch (e) {
        var duration = 0;
    }
    return duration
}

function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getDuration() {
    var remaining = $('#player .duration').innerText.substr(2);
    var position = $('#player .position').innerText;
    return toSeconds(remaining) + toSeconds(position)
}

function getPosition() {
    var position = $('#player .position').innerText;
    return toSeconds(duration)
}

function getSongId(argument) {
   return getHashCode(getTitle());
}

function getAlbumArt() {
    return $('.cover-art img').attr('src')
}

function getTitle() {
    return $('#player .track-title a')
}

function getArtist() {
    return $('#player .track-artist')
}

function play() {
    $('#player .icon-play').click();
    playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
}

function pause() {
    $('#player .icon-pause-2').click();
    playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
}

function goNext() {
    $('#player .icon-next-1').click();
}

function goPrevious() {
    $('#player .icon-previous-1').click();
}

function setVolume(volume) {

}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {

}
