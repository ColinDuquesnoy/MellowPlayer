//-----------------------------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

var player;

function update() {
    // If the player is not currently playing a video
    if(!document.getElementsByTagName('ytd-app')[0].attributes['is-watch-page']) {
        return {
            "playbackStatus": mellowplayer.PlaybackStatus.STOPPED,
            "volume": 0,
            "duration": 0,
            "position": 0,
            "songId": 0,
            "songTitle": "",
            "artistName": "",
            "artUrl": "",
            "canSeek": false,
            "canGoNext": false,
            "canGoPrevious": false,

            "albumTitle": "",
            "canAddToFavorites": false,
            "isFavorite": false
        };
    }

    player = document.getElementById("movie_player");

    // An ad is currently played
    var adContainer = document.getElementsByClassName('videoAdUiSkipContainer')[0];
    if( adContainer ) {

        // If the ad can't be skipped, the sound is muted
        if( adContainer.style.display == "none" ) {
            if (pluginSettings.muteAds)
                player.mute();

        // If the ad can be skipped, the sound is unmuted and the ad skipped
        } else if( document.getElementsByClassName('videoAdUiSkipButton')[0] ) {
            if (pluginSettings.skipAds)
                document.getElementsByClassName('videoAdUiSkipButton')[0].click();
            if (pluginSettings.muteAds)
                player.unMute();
        }
    }

    // Playback status
    switch(player.getPlayerState()) {
        case 1:
            var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
            break;

        case 2:
            var playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
            break;

        case 3:
            var playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
            break;

        default:
            var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    }

    // Song title
    var songTitle = document.getElementsByTagName('h1')[0].innerText;

    // Artist name
    var artistName = document.getElementById('owner-container').innerText;

    // Art URL
    var artUrl = "https://img.youtube.com/vi/"+ player.getVideoData().video_id + "/hqdefault.jpg"

    return {
        "playbackStatus": playbackStatus,
        "volume": player.getVolume()/100,
        "duration": Math.floor(player.getDuration()),
        "position": Math.floor(player.getCurrentTime()),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "artUrl": artUrl,
        "canSeek": true,
        "canGoNext": true,

        // Check if the video is in a playlist
        "canGoPrevious": document.getElementById('playlist-actions') ? true : false,

        "albumTitle": "",
        "canAddToFavorites": false,
        "isFavorite": false
    };
}

function play() {
    player.playVideo();
}

function pause() {
    player.pauseVideo()
}

function goNext() {
    player.nextVideo()
}

function goPrevious() {
    player.previousVideo()
}

function setVolume(volume) {
    player.setVolume(volume*100);
}

function seekToPosition(position) {
    player.seekTo(position, true);
}

function addToFavorites() {}
function removeFromFavorites() {}
