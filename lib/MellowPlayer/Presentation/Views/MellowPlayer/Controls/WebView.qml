import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0
import ".."

WebEngineView {
    id: root

    property QtObject player
    property string urlToLoad
    property var service
    property var image: null
    property bool isRunning: false
    property bool hasProprietaryCodecs: true

    signal updateImageFinished()
    signal customUrlSet(var customUrl)

    function start() {
        if (isRunning)
            return;
        isRunning = true;
        url = urlToLoad
        d.checkForCustomUrlRequired()
        player.start()
    }

    function stop() {
        root.triggerWebAction(WebEngineView.Stop);
        image = null;
        isRunning = false;
        url = "about:blank";
        reload();
        player.stop();
    }

    function updateImage() {
        root.grabToImage(function(result) { image = result; updateImageFinished(); }, Qt.size(root.width, root.height));
    }

    function exitFullScreen() {
        root.triggerWebAction(WebEngineView.ExitFullScreen);
    }

    userScripts: getUserScripts()

    function getUserScripts() {
        var scripts = [];

        for (var i = 0; i < service.userScripts.model.count; i++) {
            var userScript = service.userScripts.model.get(i);
            var webEngineScript = Qt.createQmlObject("import QtWebEngine 1.5; WebEngineScript {}", root, "webEngineScript.js");
            webEngineScript.name = userScript.name;
            webEngineScript.sourceCode = userScript.code;
            webEngineScript.injectionPoint = WebEngineScript.DocumentReady;
            scripts.push(webEngineScript);
        }

        reload();

        return scripts;
    }

    url: "about:blank"
    settings.pluginsEnabled : true
    settings.fullScreenSupportEnabled: true
    settings.autoLoadImages: true
    settings.javascriptEnabled: true
    settings.errorPageEnabled: true
    settings.autoLoadIconsForPage: true

    onContextMenuRequested: {
        request.accepted = true;
        contextMenu.x = request.x;
        contextMenu.y = request.y;
        contextMenu.canCopy = request.selectedText !== "";
        contextMenu.canPaste = request.isContentEditable && _clipboard.canPaste();
        contextMenu.canUnselect = request.selectedText !== "";
        contextMenu.canGoBack = root.canGoBack;
        contextMenu.canGoForward = root.canGoForward;
        contextMenu.hasLink = request.linkText !== "";
        contextMenu.show();
    }
    onLoadingChanged: {
        if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus && url != "about:blank") {
            player.loadPlugin();
            d.checkForProprietaryCodecs();
        }
        else
            d.checkForCustomUrlRequired();
    }

    Connections {
        target: player
        onRunJavascriptRequested: runJavaScript(script, function(result) { })
        onUpdateRequested: runJavaScript(script, function(results) { root.player.setUpdateResults(results); })
        onIsRunningChanged: if (!player.isRunning && root.isRunning) root.stop()
    }

    CustomUrlPane {
        id: customUrlPane

        customUrl: urlToLoad
        x: root.width / 2 - width / 2; y: -2; z: 1
        width: 500

        onReloadRequested: root.reload()        
        onCustomUrlChanged: if (customUrl != urlToLoad) root.customUrlSet(customUrl)
    }

    WebViewContextMenu {
        id: contextMenu

        onCopyRequested: root.triggerWebAction(WebEngineView.Copy)
        onPasteRequested: root.triggerWebAction(WebEngineView.Paste)
        onUnselectRequested: root.triggerWebAction(WebEngineView.Unselect)

        onCopyLinkRequested: root.triggerWebAction(WebEngineView.CopyLinkToClipboard)
        onOpenLinkRequested: root.triggerWebAction(WebEngineView.OpenLinkInNewTab)

        onGoBackRequested: root.goBack()
        onGoForwardRequested: root.goForward()
        onReloadRequested: root.reload()
        onViewPageSourceRequested: root.triggerWebAction(WebEngineView.ViewSource)
    }

    QtObject {
        id: d

        function checkForCustomUrlRequired() {
            var match = urlToLoad.match("(@.*@)");
            if (match !== null) {
                customUrlPane.open()
            }
        }

        function checkForProprietaryCodecs() {
            runJavaScript("var a = document.createElement('audio'); !!(a.canPlayType && a.canPlayType('audio/mpeg;').replace(/no/, ''));", function(result) {
                hasProprietaryCodecs = result;
            })
        }
    }
}
