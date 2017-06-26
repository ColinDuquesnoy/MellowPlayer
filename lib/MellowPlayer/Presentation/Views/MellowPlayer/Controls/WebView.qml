import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0

WebEngineView {
    id: root

    property QtObject player: model.player
    property string urlToLoad: model.url
    property var image: null
    property var service: model.qtObject
    property bool isRunning: false

    signal updateImageFinished();

    function start() {
        url = urlToLoad
        isRunning = true
        checkForCustomUrlRequired()
    }

    function stop() {
        url = "";
        reload();
        image = null;
        isRunning = false;
    }

    function setCustomUrl(customUrl) {
        model.url = customUrl
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

    settings.pluginsEnabled : true
    onLoadingChanged: {
        if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus && url != "about:blank")
            player.start()
        else {
            player.stop()
            checkForCustomUrlRequired();
        }
    }

    onNewViewRequested: {
        if (request.userInitiated) {
            var dialog = applicationRoot.createDialog(root.profile);
            request.openIn(dialog.currentWebView);
        }
    }

    Connections {
        target: player
        onRunJavascriptRequested: runJavaScript(script, function(result) { })
        onUpdateRequested: runJavaScript(script, function(results) { root.player.setUpdateResults(results); })
    }

    CustomUrlPane {
        id: customUrlPane

        y: -2
        x: root.width / 2 - width / 2
        width: 500
        z: 1
        onReloadRequested: root.reload()
        customUrl: urlToLoad
        onCustomUrlChanged: root.setCustomUrl(customUrl)
    }
}
