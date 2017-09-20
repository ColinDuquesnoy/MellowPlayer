function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getPlayerScope() {
    return angular.element("#players").scope();
}

function update() {
    var scope = getPlayerScope();

    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (scope.mediaPlayer.buffering) {
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
    } else if (scope.mediaPlayer.remotePlayerState.playing) {
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    } else {
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": scope.mediaPlayer.player.getVolume(),
        "duration": scope.mediaPlayer.episode.duration,
        "position": Math.floor(scope.mediaPlayer.player.getCurrentTimeInSeconds()),
        "songId": getHashCode(scope.mediaPlayer.episode.title),
        "songTitle": scope.mediaPlayer.episode.title,
        "artistName": scope.mediaPlayer.podcast.author,
        "albumTitle": "",
        "artUrl": scope.mediaPlayer.remotePlayerState.albumArt,
        "isFavorite": scope.mediaPlayer.episode.starred
    };
}

function play() {
    getPlayerScope().playPause();
}

function pause() {
    getPlayerScope().playPause();
}

function goNext() {
    getPlayerScope().jumpForward();
}

function goPrevious() {
    getPlayerScope().jumpBack();
}

function setVolume(volume) {
    getPlayerScope().mediaPlayer.player.setVolume(volume);
}

function addToFavorites() {
}

function removeFromFavorites() {
}

function seekToPosition(position) {
    getPlayerScope().mediaPlayer.seekTo(position);
}
