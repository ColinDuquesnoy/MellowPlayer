var ready = false;
var qWebChannel = null;
var player = null;
var refreshInterval = 100;

function refresh() {
    if (ready && player.isRunning)
        player.updateResults = update();
}

function initialize() {
    console.log("Connecting to MellowPlayer's WebChannel...");
    try {
        qWebChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
            console.log("Connected to MellowPlayer's WebChannel, ready to send/receive messages!");
            player = channel.objects.player;

            // connect events to integration script functions
            player.play.connect(play);
            player.pause.connect(pause);
            player.next.connect(goNext);
            player.previous.connect(goPrevious);
            player.addToFavorites.connect(addToFavorites);
            player.removeFromFavorites.connect(removeFromFavorites);
            player.seekToPosition.connect(seekToPosition);
            player.changeVolume.connect(setVolume);

            ready = true;
            window.setInterval(refresh, refreshInterval);
        });
    }
    catch (e)
    {
        console.warn(e);
    }
}

initialize();
