function getPlaybackStatus() {
    var playIcon = document.getElementById("play-icon").className;
    if (playIcon === "glyphicon glyphicon-play") {
        return mellowplayer.PlaybackStatus.PAUSED;
    }
    else {
        return mellowplayer.PlaybackStatus.PLAYING;
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
        "duration": current_song.totalTime,
        "position": toSeconds(document.getElementById("counter").innerText.split("/")[0].trim()),
        "songId": current_song.currentSongId,
        "songTitle": $('#currenttrack').text(),
        "artistName": $('#artist').text(),
        "albumTitle": $('#album').text(),
        "artUrl": 'https://colinduquesnoy.github.io/MellowPlayer/img/img_mellow-icon.svg',
        "isFavorite": false
    };
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
