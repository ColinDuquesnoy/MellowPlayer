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

var defaultArray = {
    "playbackStatus": mellowplayer.PlaybackStatus.STOPPED,
    "volume": 0,
    "duration": 0,
    "position": 0,
    "songId": 0,
    "songTitle": "",
    "albumTitle": "",
    "artistName": "",
    "artUrl": "",
    "canSeek": false,
    "canGoNext": false,
    "canGoPrevious": false,
    "canAddToFavorites": false,
    "isFavorite": false
};

function update() {
    player = document.querySelector('video');

    // If the player is not currently playing a video
    if(!player) {
        return defaultArray;
    }

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
    if( player.paused ) {
        var playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    } else {
        var playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    }

    var songTitle = "", artistName = "", artUrl = "";

    // Song title
    var songTitle = document.querySelector('.title.ytmusic-player-bar').innerText;

    if(songTitle == "")
	return defaultArray;

    // Artist name
    var artistName = document.querySelector('.subtitle.ytmusic-player-bar .yt-formatted-string').innerText.trim();

    // Art URL
    var artUrl = document.querySelector('img.ytmusic-player-bar').src;

    return {
        "playbackStatus": playbackStatus,
        "volume": player.volume,
        "duration": Math.floor(player.getDuration()),
        "position": Math.floor(player.getCurrentTime()),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "artUrl": artUrl,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "isFavorite": document.querySelector('.like.ytmusic-like-button-renderer').getAttribute("aria-pressed") == "true",

        "albumTitle": ""
    };
}

function play() {
    player.play();
}

function pause() {
    player.pause();
}

function goNext() {
    document.querySelector('.next-button').click();
}

function goPrevious() {
    document.querySelector('.previous-button').click();
}

function setVolume(volume) {
    player.volume = volume;
}

function seekToPosition(position) {
    player.currentTime = position;
}

function addToFavorites() {
    document.querySelector('.like.ytmusic-like-button-renderer').click();
}

function removeFromFavorites() {
    document.querySelector('.like.ytmusic-like-button-renderer').click();
}
