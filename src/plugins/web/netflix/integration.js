var player, playerAPI, epid, serieid;
var artUrl= '';

function update() {

    player = document.querySelector('video');

    if(player && document.querySelector('.nf-kb-nav-wrapper')) {

        // Get API
        var videoPlayer = netflix.appContext.state.playerApp.getAPI().videoPlayer;

        // Getting player id
        var playerSessionId = videoPlayer.getAllPlayerSessionIds()[0];

        // Getting player API
        playerAPI = videoPlayer.getVideoPlayerBySessionId(playerSessionId)

        // Episode ID
        epid = player.parentElement.id;

        // Skip credits
        var credits = document.getElementsByClassName('skip-credits')[0];
        if( pluginSettings.skipCredits && credits)
            credits.children[0].click();

        // Serie informations
        if( document.querySelectorAll('.video-title span').length > 1 ) {
            artistName = document.querySelector('.video-title h4').innerHTML;
            albumTitle = document.querySelectorAll('.video-title span')[0].innerHTML;
            songTitle  = document.querySelectorAll('.video-title span')[1].innerHTML;

        // Movie informations
        } else {
            artistName = "";
            albumTitle = "";
            songTitle  = document.querySelector('.video-title h4').innerHTML;
        }

        // ToDo: Fix the artURL
        artUrl = "";

        // Pause or not
        if( player.paused )
            var playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

        else
            var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;

        return {
            "playbackStatus": playbackStatus,
            "canSeek": true,
            "canGoNext": (document.querySelector('.button-nfplayerNextEpisode') ? true : false),
            "canGoPrevious": false,
            "canAddToFavorites": false,
            "volume": player.volume,
            "duration": player.duration,
            "position": Math.round( playerAPI.getCurrentTime() / 1000 ),
            "songId": getHashCode(songTitle),
            "songTitle": songTitle,
            "artistName": artistName,
            "albumTitle": albumTitle,
            "artUrl": artUrl,
            "isFavorite": false
        };
    }

    // Reset
    artUrl = '';

    return {
        "playbackStatus": mellowplayer.PlaybackStatus.STOPPED,
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "songId": 0,
        "songTitle": '',
        "artistName": '',
        "albumTitle": '',
        "artUrl": '',
        "isFavorite": false
    };
}

function play() {
    if(player)
        player.play();
}

function pause() {
    if(player)
        player.pause();
}

function goNext() {
    if(player)
        document.querySelector('.button-nfplayerNextEpisode').click();
}

function setVolume(volume) {
    if(player)
        player.volume = volume;
}

function seekToPosition(position) {
    playerAPI.seek( position * 1000 );
}

function goPrevious() {}
function addToFavorites() {}
function removeFromFavorites() {}
