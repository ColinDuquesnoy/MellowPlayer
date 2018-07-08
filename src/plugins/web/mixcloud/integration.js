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
/**
 * Controller for the old mixloud frontend (which might still be used)
 */
class AngularController {
    getMixcloudPlayer() {
        return $(document.querySelector('.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
    }

    update() {
        // hide header ad
        $("body > div.cf > div:nth-child(1)").hide();

        // Get a reference to the mixcloud's player queue controller
        var M = this.getMixcloudPlayer();

        // Get next/previous cloudcasts
        var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
        var previous = M.playerQueue.queue.cloudcastList.get(currentIndex - 1);
        var cloudcast = M.player.currentCloudcast;

        var playback_status = mellowplayer.PlaybackStatus.STOPPED;

        if (M.player.buffering) {
            playback_status = mellowplayer.PlaybackStatus.BUFFERING;
        } else if (M.player.playing) {
            playback_status = mellowplayer.PlaybackStatus.PLAYING;
        } else if (cloudcast.title) {
            playback_status = mellowplayer.PlaybackStatus.PAUSED;
        }

        return {
            "playbackStatus": playback_status,
            "canSeek": true,
            "canGoNext": true,
            "canGoPrevious": typeof previous !== "undefined",
            "canAddToFavorites": true,
            "volume": M.player.volume,
            "duration": M.player.audioLength,
            "position": M.player.audioPosition,
            "songId": cloudcast.id,
            "songTitle": cloudcast.title,
            "artistName": cloudcast.owner,
            "albumTitle": '',
            "artUrl": M.player.currentCloudcast.widgetImage,
            "isFavorite": false
        }
    }

    play() {
        // Get a reference to the mixcloud's player queue controller
        var M = this.getMixcloudPlayer();
        M.player.togglePlayClick();
    }

    pause() {
        // Get a reference to the mixcloud's player queue controller
        var M = $(document.querySelector(
            '.ng-scope[ng-controller="PlayerQueueCtrl"]')).scope();
        M.player.togglePlayClick();
    }

    goNext() {
        // Get a reference to the mixcloud's player queue controller
        var M = this.getMixcloudPlayer();
        var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
        var next = M.playerQueue.queue.cloudcastList.get(currentIndex + 1);
        if (typeof next !== "undefined") {
            M.playerQueue.playFromQueue(next);
        } else {
            M.playerQueue.playUpNext();
        }
    }

    goPrevious() {
        // Get a reference to the mixcloud's player queue controller
        var M = this.getMixcloudPlayer();
        var currentIndex = M.playerQueue.queue.getNowPlayingIndex();
        var previous = M.playerQueue.queue.cloudcastList.get(currentIndex + -1);
        if (typeof previous !== "undefined") {
            M.playerQueue.playFromQueue(previous);
        }
    }

    setVolume(volume) {
        // Get a reference to the mixcloud's player queue controller
        var M = this.getMixcloudPlayer();
        M.player.volume = volume;
    }

    addToFavorites() {
        document.querySelector("span.player-icons.favorite").click();
    }

    removeFromFavorites() {
        document.querySelector("span.player-icons.favorite").click();
    }

    seekToPosition(position) {
        // Get a reference to the mixcloud's player queue controller
        var M = getMixcloudPlayer();
        M.$emit("slider:stop", position)
    }
}

/**
 * Controller for the new mixloud frontend (it seems like only a few users have this frontend)
 *
 * -> seeking not supported
 */
class ReactController {
    getButtons() {
        return {
            'play': document.querySelector('div.player-control > span.playing'),
            'pause': document.querySelector('div.player-control > span.pause'),
            'loading': document.querySelector('div.player-control > span.loading')
        };
    }

    isElementVisible(element) {
        try {
            return element.offsetWidth > 0 && element.offsetHeight > 0;
        }
        catch (e) {
            return false;
        }
    }

    getCloudcastQueue() {
        try {
            var queue = [].slice.call(document.querySelector("div.up-next-area").children);
            // first item is not a cloudcast
            queue.shift();

            return queue;
        }
        catch (e) {
            return [];
        }
    }

    getCurrentCloudcastIndex() {
        var cloudcastQueue = this.getCloudcastQueue();

        for (var index = 0; index < cloudcastQueue.length; index++) {
            if (cloudcastQueue[index].className.endsWith("now-playing"))
                return index;
        }

        return -1;
    }

    getNextCloudcast() {
        var cloudcastQueue = this.getCloudcastQueue();
        var currentIndex = this.getCurrentCloudcastIndex();
        var nextIndex =  currentIndex + 1;

        if (nextIndex < cloudcastQueue.length)
            return cloudcastQueue[nextIndex];
        return null;
    }

     getPrecedingCloudcast() {
        var cloudcastQueue = this.getCloudcastQueue();
        var precedingIndex = this.getCurrentCloudcastIndex() - 1;

        if (precedingIndex >= 0)
            return cloudcastQueue[precedingIndex];
        return null;
    }

    getPlaybackStatus() {
        var buffering = this.isElementVisible(this.getButtons().loading);
        var paused = this.isElementVisible(this.getButtons().play);
        var playing = this.isElementVisible(this.getButtons().pause);
        var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
        if (buffering) {
            playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
        }
        else if (playing) {
            playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
        }
        else if (paused) {
            playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
        }
        return playbackStatus;
    }

    getCurrentCloudcastTitle() {
        try {
            return document.querySelector("a.player-cloudcast-title").innerText
        }
        catch(e) {
            return ""
        }
    }

    getArtistName() {
        try {
            return document.querySelector("a.player-cloudcast-author-link").innerText;
        }
        catch (e) {
            return "";
        }
    }

    getPosition() {
        try {
            return toSeconds(document.querySelector("div.player-time").innerText);
        }
        catch(e) {
            return 0;
        }
    }

    getDuration() {
        var remaining = 0;
        try {
            var remainString = document.querySelector("div.end-time").innerText.replace("-", "");
            remaining = toSeconds(remainString);
        }
        catch(e) {
        }

        return this.getPosition() + remaining;
    }

    getAlbumArt() {
        try {
            return document.querySelector("div.player-cloudcast-image").children[0].src.replace("52x52", "512x512");
        }
        catch (e) {
            return "";
        }
    }

    isFavorite() {
        try {
            var favoriteToolTip = document.querySelector("span.player-icons.favorite").children[0];
            var tooltipValue = favoriteToolTip.attributes["data-tooltip"].value;
            return tooltipValue !== "Favorite";
        }
        catch (e) {
            return false;
        }
    }

    update() {
        return {
            "playbackStatus": this.getPlaybackStatus(),
            "canSeek": false,
            "canGoNext": this.getNextCloudcast() !== null,
            "canGoPrevious": this.getPrecedingCloudcast() !== null,
            "canAddToFavorites": true,
            "volume": 1,
            "duration": this.getDuration(),
            "position": this.getPosition(),
            "songId": getHashCode(this.getCurrentCloudcastTitle()),
            "songTitle": this.getCurrentCloudcastTitle(),
            "artistName": this.getArtistName(),
            "albumTitle": '',
            "artUrl": this.getAlbumArt(),
            "isFavorite": this.isFavorite()
        }
    }

    play() {
        this.getButtons().play.click();
    }

    pause() {
        this.getButtons().pause.click();
    }

    goNext() {
        this.getNextCloudcast().children[0].click();
    }

    goPrevious() {
        this.getPrecedingCloudcast().children[0].click();
    }

    setVolume(volume) { }

    addToFavorites() {
        document.querySelector("span.player-icons.favorite").click();
    }

    removeFromFavorites() {
        document.querySelector("span.player-icons.favorite").click();
    }

    seekToPosition(position) {
        // not supported
    }
}

function getController() {
    try {
        var controller = new AngularController();
        controller.getMixcloudPlayer();
        return controller;
    }
    catch (e) {
        return new ReactController();
    }
}

function update() {
    return getController().update();
}

function play() {
    getController().play();
}

function pause() {
    getController().pause();
}

function goNext() {
    getController().goNext();
}

function goPrevious() {
    getController().goPrevious();
}

function setVolume(volume) {
    getController().setVolume(volume);
}

function addToFavorites() {
    getController().addToFavorites();
}

function removeFromFavorites() {
    getController().removeFromFavorites();
}

function seekToPosition(position) {
    getController().seekToPosition(position);
}
