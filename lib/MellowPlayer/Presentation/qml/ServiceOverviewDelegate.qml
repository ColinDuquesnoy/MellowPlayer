import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3
import QtGraphicalEffects 1.0

import "qrc:/MellowPlayer/Presentation"

Item {
    id: root
    width: servicesGridView.cellWidth
    height: servicesGridView.cellHeight

    property string backgroundColor: Material.background
    property var webView: webViewStack.itemAt(index)

    Pane {
        id: highlight
        anchors.fill: parent
        anchors.margins: parent.width / 50
        Material.background: state == "hover" ? Qt.lighter(backgroundColor) : backgroundColor
        Material.elevation: 5

        Image {
            id: preview
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            source: {
                return webView !== null && webView.image !== null ? webView.image.url : "qrc:/MellowPlayer/Presentation/images/home-background.png"
            }
            states: State {
                name: "selected"

                PropertyChanges {
                    target: body
                    state: "between"
                    previewImage: preview
                }

                ParentChange {
                    target: preview
                    parent: body
                    width: body.width
                    height: body.height
                    x: 0
                    y: 0
                }
            }
            transitions: [
                Transition {
                    ParentAnimation {
                        via: body

                        PropertyAnimation {
                            properties: "x,y,width,height"
                            easing.type: Easing.InOutCubic
                        }
                    }

                    onRunningChanged: {
                        if(!running) {
                            body.state = preview.state == "selected" ? "webview" : "overview";
                            body.previewImage = preview;
                            preview.visible = preview.state != "selected";
                        }
                    }
                }
            ]
            onStateChanged: {
                preview.visible = true;
                if (webView.url == "" )
                    webView.url = webView.urlToLoad;
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

            RowLayout {
                anchors.fill: parent
                spacing: 9

                Image {
                    Layout.maximumWidth: 32
                    Layout.maximumHeight: 32
                    source: service.logo
                    antialiasing: true
                    mipmap: true
                }

                Label {
                    id: lblName
                    Layout.fillWidth: true
                    text: service.name
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

        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
            width: 32
            height: 32
            radius: 32
            color: Material.background
            visible: preview.source != "qrc:/MellowPlayer/Presentation/images/home-background.png" && highlight.state == "hover"

            ToolButton {
                id: btOff
                hoverEnabled: true
                anchors.centerIn: parent

                text: MaterialIcons.icon_power_settings_new
                font.family: MaterialIcons.family
                font.pointSize: 22

                onClicked: {
                    webView.url = "";
                    webView.reload();
                    webView.image = null;
                }
            }
        }
    }

    function activate() {
        streamingServices.currentService = service;
        preview.state = "selected";
    }

    Component.onCompleted: {
        if (streamingServices.currentIndex == index) {
            root.activate();
            preview.visible = false;
        }
    }
}
