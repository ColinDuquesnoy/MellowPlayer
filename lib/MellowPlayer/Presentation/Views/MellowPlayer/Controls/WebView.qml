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
    property var userAgentSetting: _settings.get(SettingKey.PRIVACY_USER_AGENT)

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

    function zoomIn() {
        var nextZoomFactor = d.zoomFactorIndex + 1
        if (nextZoomFactor >= d.zoomFactors.length)
            nextZoomFactor = d.zoomFactorIndex;
        d.zoomFactorIndex = nextZoomFactor;
        zoomPane.show()
    }

    function zoomOut() {
        var previousZoomFactor = d.zoomFactorIndex - 1
        if (previousZoomFactor < 0)
            previousZoomFactor = 0
        d.zoomFactorIndex = previousZoomFactor;
        zoomPane.show()
    }

    function resetZoom() {
        d.zoomFactorIndex = d.resetZoomFactorIndex;
        zoomPane.show()
    }

    settings {
        pluginsEnabled : true
        fullScreenSupportEnabled: true
        autoLoadImages: true
        javascriptEnabled: true
        errorPageEnabled: true
        autoLoadIconsForPage: true
    }
    userScripts: d.getUserScripts()
    url: "about:blank"
    zoomFactor: d.zoomFactors[d.zoomFactorIndex]

    profile.httpUserAgent: userAgentSetting.value

    Connections {
        target: userAgentSetting
        onValueChanged: { console.warn("new user agent: " + userAgentSetting.value); reload(); }
    }

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

    Pane {
        id: zoomPane

        anchors { top: parent.top; right: parent.right; margins: 2 }
        leftPadding: 6
        rightPadding: 6
        bottomPadding: 3
        topPadding: 3
        z: 1
        visible: false

        function show() {
            visible = true;
            hideTimer.running = true;
            hideTimer.restart();
        }

        Material.background: _theme.primary
        Material.foreground: _theme.primaryForeground
        Material.elevation: 2
        Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

        RowLayout {
            spacing: 8

            IconToolButton {
                icon: MaterialIcons.icon_remove
                iconSize: 16
                tooltip: qsTr("Zoom out")

                onTriggered: root.zoomOut()
            }

            Label {
                text: Math.round(root.zoomFactor * 100) + "%"
                opacity: 0.8
            }

            IconToolButton {
                icon: MaterialIcons.icon_add
                iconSize: 16
                tooltip: qsTr("Zoom in")

                onTriggered: root.zoomIn()
            }

            ToolButton {
                text: qsTr("Reset")

                onClicked: root.resetZoom()
            }
        }

        Timer {
            id: hideTimer

            interval: 2000
            onTriggered: zoomPane.visible = false
        }
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

        property var zoomFactors: [0.25, 0.33, 0.5, 0.67, 0.75, 0.8, 0.9, 1, 1.1, 1.25, 1.5, 1.75, 2, 2.5, 3, 4, 5]
        property int resetZoomFactorIndex: 7
        property int zoomFactorIndex: root.service.zoomFactor

        onZoomFactorIndexChanged: root.service.zoomFactor = zoomFactorIndex

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
    }
}
