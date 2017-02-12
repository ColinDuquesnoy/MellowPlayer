import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

WebEngineView {
    id: root
    settings.pluginsEnabled : true
    visible: webViewStack.visible && webViewStack.currentIndex == index;
    enabled: visible

    property QtObject player: service.player
    property string urlToLoad: service.url
    property string toolBarColor: service.toolbarColor !== "" ? service.toolbarColor : Material.background
    property var image: null
    property bool ready: image != null || url == ""
    signal updateImageFinished();

    function updateImage() {
        root.grabToImage(function(result) { image = result; updateImageFinished(); }, Qt.size(root.width, root.height));
    }

    onLoadingChanged: if (!loading) player.initialize()

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
