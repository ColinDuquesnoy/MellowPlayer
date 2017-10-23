function update() {
    var controlClassName = document.getElementsByClassName('AudioVideoPlayerControls-controls-OwK1f')[0];
    // if controlClassName is undefined the audioplayer isn't opened yet
    if (!controlClassName)
        return;
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (document.querySelector('[aria-label=Pause]') !== null)
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (document.querySelector('[aria-label=Play]') !== null)
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    try {
        var artBlobUrl = document.getElementsByClassName('AudioVideoPlayerControls-buttonGroupLeft-3kwFX')[
        0].children[0].children[0].children[0].children[0].children[0].children[0].children[0].children[0]
        .style["background-image"];
        artBlobUrl = artBlobUrl.replace('url("', "").replace('")', "");
        // Get the data URL of the blob
        var request = new XMLHttpRequest();
        request.open('GET', artBlobUrl, true);
        request.responseType = 'blob';
        request.onload = function() {
            var reader = new FileReader();
            reader.readAsDataURL(request.response);
            reader.onload =  function(e){
                return artUrl = e.target.result;
            };
        };
        request.send();
    } catch (e) {
        var artUrl = '';
    }
    try {
        var songTitle = document.getElementsByTagName('title')[0].innerHTML;
    } catch (e) {
        var songTitle = '';
    }
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
        "songTitle": songTitle,
        "artistName": '',
        "albumTitle": '',
        "artUrl": artUrl,
        "isFavorite": false
    }
}

function clickButton(buttonName) {
    document.querySelector("[aria-label=" + buttonName + "]").click()
}

function play() {
    clickButton('Play');
}

function pause() {
    play();
}

function goNext() {
    clickButton('Next');
}

function goPrevious() {
    clickButton('Previous');
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
