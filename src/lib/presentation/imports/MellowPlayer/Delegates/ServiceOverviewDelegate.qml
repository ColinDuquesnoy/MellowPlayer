import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

Item {
    id: root

    property int index
    property string backgroundColor: Material.background
    property bool hovered: false
    property var service: model.qtObject

    onIndexChanged: model.sortOrder = root.index

    Component.onCompleted: model.sortOrder = root.index

    Pane {
        anchors.fill: parent
        anchors.margins: parent.width / 50

        Material.elevation: state == "hover" ? 8 : 4

        Image {
            id: preview
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            source: model.previewImageUrl
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

        state: root.hovered ? "hover" : ""

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
    }

    function activate() {
        mainWindow.activateService(service);
    }
}
