class PlayList {
    constructor() {
        this.tracks = playlist.info;
    }

    currentIndex() {
        for (var trackIndex in this.tracks) {
            if(this.tracks[trackIndex]) {
                var track = this.tracks[trackIndex];
                if (track.id == intCurrentTrack)
                    return parseInt(trackIndex);
            }
        }
        return 0;
    }

    itemAt(index) {
        return this.tracks[index];
    }

    currentItem() {
        return this.itemAt(this.currentIndex());
    }

    count() {
        return this.tracks.length;
    }

    previousItem() {
        var previousIndex = this.currentIndex() - 1;
        if (previousIndex >= 0 )
            return this.itemAt(previousIndex);
        return null;
    }

    nextItem() {
        var nextIndex = this.currentIndex() + 1;
        if (nextIndex < this.count() )
            return this.itemAt(nextIndex);
        return null;
    }
}

function getCurrentTrack() {
    var track = findTrack(intCurrentTrack);
    return track;
}

function safeGetter(getter) {
    try {
        return getter();
    }
    catch (e)
    {
        return 0;
    }
}

function getDuration() {
    return safeGetter(function () {
        return getCurrentTrack().duration / 1000
    }, 0);
}

function getPosition() {
    return safeGetter(function () {
        return Math.ceil(getCurrentTrack().position) / 1000
    }, 0);
}

function getVolume() {
    return safeGetter(function () {
        return getCurrentTrack().volume / 100.0
    }, 1);
}

function getTitle() {
    return safeGetter(function () {
        var pl = new PlayList();
        var currentItem = pl.currentItem();
        return currentItem.title;
    }, "");
}

function getArtist() {
    return safeGetter(function () {
        var pl = new PlayList();
        var currentItem = pl.currentItem();
        return currentItem.artist;
    }, "");
}

function getAlbumArtUrl() {
    return safeGetter(function () {
        if (getCurrentTrack() === false)
            return "";
        var pl = new PlayList();
        var currentItem = pl.currentItem();
        return currentItem.img.replace("w50_h50_", "w512_h512_");
    }, "")
}

function getPlaybackStatus() {
    var track = getCurrentTrack();

    if (track === false)
        return mellowplayer.PlaybackStatus.STOPPED;

    if (track.isBuffering === true)
        return mellowplayer.PlaybackStatus.BUFFERING;
    if (track.paused === true)
        return mellowplayer.PlaybackStatus.PAUSED;
    else
        return mellowplayer.PlaybackStatus.PLAYING;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": getVolume(),
        "duration": getDuration(),
        "position": getPosition(),
        "songId": intCurrentTrack,
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getAlbumArtUrl(),
        "isFavorite": false
    };
}

function play(id) {
    soundManager.pauseAll();
    var track, sndObj;
    if(id>0) {
        track=$('li[data-trackid='+id+']>a');
        sndObj = findPaused();
        if(track.length){
            pagePlayer.handleClick({target:track[0]});
        } else if(sndObj&&findTrack(id)==sndObj) {
            pagePlayer.handleClick({target:sndObj._data.oLink});
        } else {
            $.post( "/track_ajax_player.php",{id:id}).success(function(track){
                track=$(track);
                var a = track.find("a");
                //a.attr({'href': a.attr('data-mp3')});
                $('.playlist').first().prepend($('<div/>').css({'display':'none'}).append(track));
                pagePlayer.handleClick({target:$('li[data-trackid='+id+']>a.player-link')[0]});
            });
        }
    } else {
        if($('li.sm2_paused').length) {
            pagePlayer.handleClick({target:$('li.sm2_paused > a')[0]});
        } else if (sndObj=findPaused()) {
            pagePlayer.handleClick({target:sndObj._data.oLink});
        } else if(playlist && playlist.tracks.length > 0) {
            var trackIndex = $("#play_queue").find("li.active").index();
            if(trackIndex > 0) {
                id = playlist.tracks[trackIndex];
            } else {
                id = $("#play_queue").find("li:last").data("trackid");
                var els = $("#play_queue").find("li");
                els.removeClass("active");
                $("#play_queue").find("li:last").addClass("active");
            }
            play(id);
        } else {
            var els = $("#play_queue").find("li");
            els.removeClass("active");
            track = $('.playlist a')[0];
            id = $(track).parent('li').attr('data-trackid');
            pagePlayer.handleClick({target:track});
        }
    }
}

function pause() {
    soundManager.pauseAll();
}

function goNext() {
    var pl = new PlayList();
    play(pl.nextItem().id);
}

function goPrevious() {
    var pl = new PlayList();
    play(pl.previousItem().id);
}

function setVolume(volume) {
    soundManager.setVolume(volume * 100);
}

function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function seekToPosition(position) {
    var track = getCurrentTrack();
    if (track)
        track.setPosition(position * 1000)
}
