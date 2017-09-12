function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

class PlayList {
    constructor() {
        this.tracks = playlist.info;
    }

    currentIndex() {
        return $("#play_queue").find("li.active").index();
    }

    itemAt(index) {
        return this.tracks[index];
    }

    currentTrack() {
        return this.itemAt(this.currentIndex());
    }

    count() {
        return this.tracks.length;
    }

    previousTrack() {
        var previousIndex = this.currentIndex() - 1;
        if (previousIndex >= 0 )
            return this.itemAt(previousIndex);
        return null;
    }

    nextTrack() {
        var nextIndex = this.currentIndex() + 1;
        if (nextIndex < this.count() )
            return this.itemAt(nextIndex);
        return null;
    }
}

function isCurrentTrackInPlaylist() {
    return $("#play_queue").find("li.active").index() !== -1;
}

function getCurrentTrack() {
    if (isCurrentTrackInPlaylist())
        return new PlayList().currentTrack();
    return null;
}

function safeGetter(getter, defaultValue) {
    try {
        return getter();
    }
    catch (e)
    {
        return defaultValue;
    }
}

function getDuration() {
    return safeGetter(function () {
        var track = findTrack(intCurrentTrack);
        return track.duration / 1000
    }, 0);
}

function getPosition() {
    return safeGetter(function () {
        var track = findTrack(intCurrentTrack);
        return track.position / 1000
    }, 0);
}

function getVolume() {
    return safeGetter(function () {
        var track = findTrack(intCurrentTrack);
        return track.volume / 100.0
    }, 1);
}

function getTitle() {
    return safeGetter(function () {
        return getCurrentTrack().title;
    }, "");
}

function getArtist() {
    return safeGetter(function () {
        return getCurrentTrack().artist;
    }, "");
}

function getAlbumArtUrl() {
    return safeGetter(function () {
        return getCurrentTrack().img.replace("w50_h50_", "w512_h512_");
    }, "")
}

function getPlaybackStatus() {
    var track = findTrack(intCurrentTrack);

    if (track === false)
        return mellowplayer.PlaybackStatus.STOPPED;

    if (!isCurrentTrackInPlaylist() || track.isBuffering === true)
        return mellowplayer.PlaybackStatus.BUFFERING;
    if (track.paused === true)
        return mellowplayer.PlaybackStatus.PAUSED;
    else
        return mellowplayer.PlaybackStatus.PLAYING;
}

function getSongId() {
    if (isCurrentTrackInPlaylist())
        return getHashCode(getTitle());
    return 0;
}

function update() {
    var data = {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": getVolume(),
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getSongId(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getAlbumArtUrl(),
        "isFavorite": false
    };
    return data;
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
    play(pl.nextTrack().id);
}

function goPrevious() {
    var pl = new PlayList();
    play(pl.previousTrack().id);
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
