import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Item {
    anchors { fill: parent; margins: 16 }
    clip: true

    ColumnLayout {
        anchors.fill: parent
        clip: true
        spacing: 8

        Button {
            text: "Clear cookies"
            onClicked: {
                paneRestart.state = "visible"
                qtApp.clearCookies();
            }
        }

        Button {
            text: "Clear cache"
            onClicked: {
                paneRestart.state = "visible"
                qtApp.clearCache()
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }


    Pane {
        id: paneRestart

        clip: true
        width: parent.width

        Material.background: style.primary
        Material.elevation: 8
        Material.foreground: style.primaryForeground
        Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            spacing: 8

            Label {
                text: MaterialIcons.icon_info
                font {
                    family: MaterialIcons.family
                    pixelSize: 32
                }
            }

            Label {
                text: "You need to restart MellowPlayer for the change to be applied."
                font.pixelSize: 16
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: "Restart now"
                onClicked: qtApp.restart()
            }
        }

        state: "hidden"
        states: [
            State {
                name: "hidden"

                PropertyChanges { target: paneRestart; y: parent.height }
            },
            State {
                name: "visible"

                PropertyChanges { target: paneRestart; y: parent.height - paneRestart.implicitHeight }
            }
        ]
        transitions: Transition {
            from: "hidden"
            to: "visible"

            PropertyAnimation { properties: "y" }
        }
    }
}
