import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5
import QtGraphicalEffects 1.0

import MellowPlayer 3.0
import ".."

Item {
    id: root
    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    property string backgroundColor: Material.background
    property Item transitionItem
    property var webView

    Pane {
        id: highlight
        anchors.fill: parent
        anchors.margins: parent.width / 50
        Material.elevation: state == "hover" ? 6 : 4

        Image {
            id: preview
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            source: {
                return webView !== null && webView.image !== null ? webView.image.url : "qrc:/MellowPlayer/Presentation/Resources/images/home-background.png"
            }
            states: State {
                name: "selected"

                PropertyChanges {
                    target: root.transitionItem
                    state: "between"
                    // @disable-check M16
                    previewImage: preview
                }

                ParentChange {
                    target: preview
                    parent: root.transitionItem
                    width: root.transitionItem.width
                    height: root.transitionItem.height
                    x: 0
                    y: 0
                }
            }
            transitions: [
                Transition {
                    ParentAnimation {
                        via: root.transitionItem

                        PropertyAnimation {
                            properties: "x,y,width,height"
                            easing.type: Easing.InOutCubic
                        }
                    }

                    onRunningChanged: {
                        if(!running) {
                            root.transitionItem.state = preview.state == "selected" ? "webview" : "overview";
                            root.transitionItem.previewImage = preview;
                            preview.visible = preview.state != "selected";
                        }
                    }
                }
            ]
            onStateChanged: {
                preview.visible = true;
                webView.start()
            }
        }

        Desaturate {
            id: filter
            anchors.fill: preview
            source: preview
            desaturation: 1.0
        }

        ColorOverlay {
            id: overlay
            anchors.fill: preview
            source: preview
            color: "black"
            opacity: 0.3
        }

        state: mouseArea.containsMouse || btOff.hovered ? "hover" : ""

        states: State {
            name: "hover"

            PropertyChanges {
                target: filter
                desaturation: 0.0
            }

            PropertyChanges {
                target: overlay
                opacity: 0.0

            }
        }

        transitions: [
            Transition {
                PropertyAnimation { properties: "desaturation, opacity" }
            }
        ]

        Pane {
            anchors.centerIn: parent
            Material.background: "#404040"
            Material.elevation: 2
            opacity: 0.9

            RowLayout {
                anchors.fill: parent
                spacing: 9

                Image {
                    Layout.maximumWidth: 32
                    Layout.maximumHeight: 32
                    source: model.logo
                    antialiasing: true
                    mipmap: true
                }

                Text {
                    id: lblName
                    Layout.fillWidth: true

                    color: "white"
                    text: model.name
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: containsMouse ? "PointingHandCursor" : "ArrowCursor"

            onClicked: root.activate();
        }

    }

    function activate() {
        _streamingServices.currentService = model.qtObject;
        preview.state = "selected";
    }

    Component.onCompleted: {
        if (_streamingServices.currentIndex == index) {
            root.activate();
            preview.visible = false;
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        width: 32
        height: 32
        radius: 32
        color: Material.color(Material.Red)
        visible: preview.source != "qrc:/MellowPlayer/Presentation/Resources/images/home-background.png" && highlight.state == "hover"

        ToolButton {
            id: btOff
            hoverEnabled: true
            anchors.centerIn: parent
            Material.foreground: "white"

            text: MaterialIcons.icon_power_settings_new
            font.family: MaterialIcons.family
            font.pointSize: 22

            onClicked: webView.stop()
        }
    }
}
