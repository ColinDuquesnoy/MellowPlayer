import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

WebEngineView {
    id: root

    property QtObject player: object.player
    property string urlToLoad: object.url
    property string toolBarColor: object.toolbarColor !== "" ? object.toolbarColor : Material.background
    property var image: null
    property bool ready: image != null || url == ""
    signal updateImageFinished();

    settings.pluginsEnabled : true
    visible: webViewStack.visible && webViewStack.currentIndex == index;
    enabled: visible

    onLoadingChanged: if (!loading) player.initialize()

    onNewViewRequested: {
        if (!request.userInitiated)
            console.warn("Blocked a popup window")
        else {
            var dialog = applicationRoot.createDialog(root.profile);
            request.openIn(dialog.currentWebView);
        }
    }


    function updateImage() {
        root.grabToImage(function(result) { image = result; updateImageFinished(); }, Qt.size(root.width, root.height));
    }

    Connections {
        target: player
        onRunJavascriptRequested: if(!loading) runJavaScript(script, function(result) {})
        onUpdateRequested: if(!loading) runJavaScript(script, function(results) { player.setUpdateResults(results); })
    }

    Timer {
        interval: 100
        onTriggered: player.refresh()
        running: root.enabled && !root.loading
        repeat: true
    }
}
