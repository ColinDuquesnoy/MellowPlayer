MellowPlayer = {
    ready: false,
    webChannel: null,
    player: null,
    refreshInterval: 100,
    refresh: function() {
        if (MellowPlayer.ready && MellowPlayer.player.isRunning) {
            var updateResults = update();
            try {
                if(updateResults.songId == 0)
                    updateResults.songId = getHashCode(updateResults.songTitle);
            } catch (e) {
                updateResults.songId = -1;
            }
            MellowPlayer.player.updateResults = updateResults;
        }
    },
    initialize: function() {
        console.log("Connecting to MellowPlayer's WebChannel...");
        try {
            MellowPlayer.webChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
                console.log("Connected to MellowPlayer's WebChannel, ready to send/receive messages!");
                MellowPlayer.player = channel.objects.player;

                // connect events to integration script functions
                MellowPlayer.player.play.connect(play);
                MellowPlayer.player.pause.connect(pause);
                MellowPlayer.player.next.connect(goNext);
                MellowPlayer.player.previous.connect(goPrevious);
                MellowPlayer.player.addToFavorites.connect(addToFavorites);
                MellowPlayer.player.removeFromFavorites.connect(removeFromFavorites);
                MellowPlayer.player.seekToPosition.connect(seekToPosition);
                MellowPlayer.player.changeVolume.connect(setVolume);

                MellowPlayer.ready = true;
                window.setInterval(MellowPlayer.refresh, MellowPlayer.refreshInterval);
            });
        }
        catch (e)
        {
            console.warn(e);
        }
    }
};

MellowPlayer.initialize();
