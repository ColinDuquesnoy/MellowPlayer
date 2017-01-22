import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3
import QtGraphicalEffects 1.0

Item {
    id: root
    width: servicesGridView.cellWidth
    height: servicesGridView.cellHeight

    Rectangle {
        id: highlight
        anchors.fill: parent
        radius: 3
        color: mouseArea.containsMouse ? Qt.lighter(Material.background) : "transparent"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 9
            spacing: 15

            Label {
                Layout.fillWidth: true
                text: name
                horizontalAlignment: Text.AlignHCenter
            }

            Item {
                id: placeHolder
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 9

                WebEngineView {
                    id: webEngineView
                    x: 0
                    y: 0
                    width: body.width
                    height: body.height
                    transformOrigin: Item.TopLeft
                    scale: placeHolder.width / body.width
                    url: serviceUrl
                    settings.pluginsEnabled : true
                    enabled: root.state == "selected"
                }

                Desaturate {
                    id: filter
                    anchors.fill: parent
                    source: placeHolder
                    desaturation: 1.0
                }

                Image {
                    width: 64
                    height: 64
                    source: webEngineView.icon
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 10
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: switchAutoLoad.height
                Switch {
                    anchors.centerIn: parent
                    id: switchAutoLoad
                    text: "Load automatically"
                }
            }
        }

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
                PropertyAnimation { properties: "desaturation" }
            }
        ]
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: root.state != "selected"

        onContainsMouseChanged: containsMouse ? highlight.state = "hover" : highlight.state = ""

        onClicked: {
            body.currentWebView = root;
            root.state = "selected";
        }
    }



    states: State {
        name: "selected"
        PropertyChanges {
            target: body
            overviewVisible: false
        }
        ParentChange {
            target: webEngineView
            parent: body
            scale: 1.0
            x: 0
            y: 0
        }
    }

    transitions: [
        Transition {
            ParentAnimation {
                via: body
                PropertyAnimation { properties: "x,y,scale"; easing: Easing.InOutCubic; /*duration: 1000*/}
            }
        }
    ]
}
