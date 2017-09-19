var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;

function update() {
    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": 0,
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getAlbumArt(),
        "isFavorite": false
    };
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
