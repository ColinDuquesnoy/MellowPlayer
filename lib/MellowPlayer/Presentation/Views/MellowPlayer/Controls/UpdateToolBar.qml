import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

ToolBar {
    id: updateToolBar

    height: 0
    transform: Scale {
        id: scaleTransform

        origin.x: 0
        origin.y: updateToolBar.height
        xScale: 1
        yScale: 0
    }

    Material.background: _theme.accent
    Material.foreground: _theme.isDark(_theme.accent) ?  "white" : "#303030"
    Material.theme: _theme.isDark(_theme.accent) ?  Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent
        spacing: 8

        Item {
            width: 4
        }

        Label {
            text: MaterialIcons.icon_update
            font {
                family: MaterialIcons.family
                pixelSize: 24
            }
        }

        Label {
            text: "A <b>new version of MellowPlayer</b> is available..."
            font.pixelSize: 16
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            hoverEnabled: true
            text: "See release notes"
        }

        ToolButton {
            hoverEnabled: true
            text: "Install"
        }

        ToolButton {
            hoverEnabled: true
            text: MaterialIcons.icon_close
            font {
                family: MaterialIcons.family
                pixelSize: 24
            }
            onClicked: _updater.close()
        }
    }
    states: [
        State {
            when: _updater.visible

            PropertyChanges {
                target: updateToolBar
                height: updateToolBar.implicitHeight
            }

            PropertyChanges {
                target: scaleTransform
                yScale: 1
            }
        },
        State {
            when: !_updater.visible

            PropertyChanges {
                target: updateToolBar
                height: 0
            }

            PropertyChanges {
                target: scaleTransform
                yScale: 0
            }
        }
    ]
    transitions: Transition {
        from: "*"; to: "*"; reversible: true

        PropertyAnimation {
            properties: "yScale, height"
            duration: 200
        }
    }
}
