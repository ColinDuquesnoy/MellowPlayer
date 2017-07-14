import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0

WebEngineView {
    id: root

    property QtObject player
    property string urlToLoad
    property var service
    property var image: null
    property bool isRunning: false

    signal updateImageFinished()
    signal customUrlSet(var customUrl)

    function start() {
        console.warn("start", model.name)
        isRunning = true;
        url = urlToLoad
        checkForCustomUrlRequired()
        player.start()
    }

    function stop() {
        console.warn("stop", model.name)
        isRunning = false;
        url = "";
        reload();
        image = null;
        player.stop();
    }

    function checkForCustomUrlRequired() {
        var match = urlToLoad.match("(@.*@)");
        if (match !== null) {
            customUrlPane.open()
        }
    }

    function updateImage() {
        root.grabToImage(function(result) { image = result; updateImageFinished(); }, Qt.size(root.width, root.height));
    }

    function exitFullScreen() {
        root.triggerWebAction(WebEngineView.ExitFullScreen);
    }

    settings.pluginsEnabled : true
    settings.fullScreenSupportEnabled: true
    settings.autoLoadImages: true
    settings.javascriptEnabled: true
    settings.errorPageEnabled: true
    settings.autoLoadIconsForPage: true

    onLoadingChanged: {
        if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus && url != "about:blank") {
            player.loadPlugin();
            updateImage();
        }
        else
            checkForCustomUrlRequired();
    }

    Connections {
        target: player
        onRunJavascriptRequested: runJavaScript(script, function(result) { })
        onUpdateRequested: runJavaScript(script, function(results) { root.player.setUpdateResults(results); })
        onIsRunningChanged: {
            console.error("on is running changed", root.isRunning)
            if (!player.isRunning && root.isRunning) root.stop()
        }
    }

    CustomUrlPane {
        id: customUrlPane

        y: -2
        x: root.width / 2 - width / 2
        width: 500
        z: 1
        onReloadRequested: root.reload()
        customUrl: urlToLoad
        onCustomUrlChanged: if (customUrl != urlToLoad) root.customUrlSet(customUrl)
    }
}
