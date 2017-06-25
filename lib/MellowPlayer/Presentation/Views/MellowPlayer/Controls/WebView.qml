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
    property string color: model.color !== "" ? model.color : Material.background
    property var image: null
    property var service: model.qtObject
    property bool isRunning: false

    signal updateImageFinished();

    function setCustomUrl(customUrl) {
        model.url = customUrl
    }

    function checkForCustomUrlRequired() {
        var match = urlToLoad.match("(@.*@)");
        if (match !== null) {
            paneCustomUrl.state = "visible";
        }

    }

    settings.pluginsEnabled : true
    visible: webViewStack.visible && webViewStack.currentIndex == index;
    enabled: visible

    onLoadingChanged: {
        if (loadRequest.status === WebEngineLoadRequest.LoadSucceededStatus && url != "about:blank") {
            player.initialize()
            refreshTimer.start();
        }
        else {
            refreshTimer.stop();
            checkForCustomUrlRequired();
        }
    }

    onNewViewRequested: {
        if (request.userInitiated) {
            var dialog = applicationRoot.createDialog(root.profile);
            request.openIn(dialog.currentWebView);
        }
    }

    function updateImage() {
        root.grabToImage(function(result) { image = result; updateImageFinished(); }, Qt.size(root.width, root.height));
    }

    Connections {
        target: player

        onRunJavascriptRequested: {
            if (!loading)
                runJavaScript(script, function(result) { })
        }        
        onUpdateRequested: {
            if (!loading)
                runJavaScript(script, function(results) { root.player.setUpdateResults(results); })
        }
    }

    Timer {
        id: refreshTimer

        interval: 100
        onTriggered: player.refresh()
        repeat: true
    }

    Pane {
        id: paneCustomUrl

        y: -2
        x: root.width / 2 - width / 2
        width: 500
        z: 1

        Material.background: style.primary
        Material.foreground: style.primaryForeground
        Material.elevation: 4

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: "Custom url required"
                font.bold: true
                font.pixelSize: 16

                Layout.alignment: Qt.AlignCenter
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    id: textField

                    selectByMouse: true
                    text: urlToLoad
                    onEditingFinished: save()

                    function save() {
                        root.service.url = text;
                        paneCustomUrl.state = "hidden";
                    }

                    Layout.fillWidth: true
                }

                ToolButton {
                    flat: true
                    font.family: MaterialIcons.family
                    font.pixelSize: 24
                    text: MaterialIcons.icon_done

                    onClicked: textField.save()
                }
            }
        }

        state: "hidden"
        states: [
            State {
                name: "hidden"

                PropertyChanges {
                    target: paneCustomUrl
                    y: -paneCustomUrl.implicitHeight - 16
                }
            },
            State {
                name: "visible"

                PropertyChanges {
                    target: paneCustomUrl
                    y: -2
                }
            }
        ]
        transitions: Transition {
            from: "visible"
            to: "hidden"
            reversible: true

            PropertyAnimation {
                properties: "y"
            }

            onRunningChanged: {
                if (paneCustomUrl.state == "hidden" && !running)
                    root.reload();
            }

        }
    }
}
