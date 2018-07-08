function getPlaybackStatus() {
    try {
        var playIcon = document.getElementById("play-icon").className;
        if (playIcon === "glyphicon glyphicon-play") {
            return mellowplayer.PlaybackStatus.PAUSED;
        }
        else {
            return mellowplayer.PlaybackStatus.PLAYING;
        }
    } catch (e) {
        return mellowplayer.PlaybackStatus.STOPPED;
    }
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getSongId(),
        "songTitle": getSongTitle(),
        "artistName": getArtistName(),
        "albumTitle": getAlbumTitle(),
        "artUrl": 'https://colinduquesnoy.github.io/MellowPlayer/img/img_mellow-icon.svg',
        "isFavorite": false
    };
}

function getDuration() {
    try {
        return current_song.totalTime;
    } catch (e) {
        return 0;
    }
}

function getPosition() {
    try {
        toSeconds(document.getElementById("counter").innerText.split("/")[0].trim());
    } catch (e) {
        return 0;
    }
}

function getSongId() {
    try {
        return current_song.currentSongId;
    } catch (e) {
        return "";
    }
}

function getSongTitle() {
    try {
        return $('#currenttrack').text();
    } catch (e) {
        return "";
    }
}

function getArtistName() {
    try {
        return $('#artist').text();
    } catch (e) {
        return "";
    }
}

function getAlbumTitle() {
    try {
        return $('#album').text();
    } catch (e) {
        return "";
    }
}

function play() {
    clickPlay();
}

function pause() {
    clickPlay();
}

function goNext() {
    socket.send('MPD_API_SET_NEXT');
}

function goPrevious() {
    socket.send('MPD_API_SET_PREV');
}

function setVolume(volume) {

}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {
    socket.send("MPD_API_SET_SEEK,"+current_song.currentSongId+","+position);
}
