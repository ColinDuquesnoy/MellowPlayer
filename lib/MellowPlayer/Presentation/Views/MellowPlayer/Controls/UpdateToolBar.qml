import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

ToolBar {
    id: updateToolBar

    enabled: !_updater.busy
    height: 0
    transform: Scale {
        id: scaleTransform

        origin.x: 0
        origin.y: updateToolBar.height
        xScale: 1
        yScale: 0
    }

    Material.background: _theme.secondary
    Material.foreground: _theme.secondaryForeground
    Material.accent: _theme.accent
    Material.theme: _theme.isDark(_theme.secondary) ?  Material.Dark : Material.Light

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            spacing: 8

            Item {
                width: 4
            }

            Label {
                text: MaterialIcons.icon_update
                font {
                    family: MaterialIcons.family
                    pixelSize: 26
                }
            }

            Label {
                text: _updater.message
                font.pixelSize: 16
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: "See release notes"
                onClicked: Qt.openUrlExternally(_updater.url)
            }

            ToolButton {
                highlighted: true
                text: "Install"
                onClicked: _updater.install()
                visible: _updater.installEnabled
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

        ProgressBar {
            anchors{ bottom: parent.bottom; left: parent.left; right: parent.right }
            indeterminate: _updater.progress == -1
            visible: _updater.progressVisible
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
