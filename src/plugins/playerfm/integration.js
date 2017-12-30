function update() {
    return {
        "playbackStatus": player.isPlaying() ? mellowplayer.PlaybackStatus.PLAYING : mellowplayer.PlaybackStatus.PAUSED,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": player.getVolume(),
        "duration": Math.round(player.getDuration()),
        "position": Math.round(player.getCurrentTime()),
        "songTitle": player.currentEpisode ? player.currentEpisode.title : '',
        "artistName": player.currentEpisode ? player.currentEpisode.series.title : '',
        "albumTitle": '',
        "artUrl": player.currentEpisode ? player.currentEpisode.series.imageModel.url : '',
        "isFavorite": false
    };
}

function play() {
    player.togglePlayback();
}

function pause() {
    player.togglePlayback();
}

function goNext() {
    player.gotoNext();
}

function goPrevious() {
    player.gotoPrev();
}

function setVolume(volume) {
    player.setVolume(volume);
}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {
    player.seek(position);
}
