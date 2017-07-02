import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

Pane {
    id: root

    property string customUrl

    signal reloadRequested()

    function open() {
        state = "visible";
    }

    Material.background: _style.primary
    Material.foreground: _style.primaryForeground
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
                text: customUrl
                onEditingFinished: save()

                function save() {
                    customUrl = text;
                    root.state = "hidden";
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
                target: root
                y: -root.implicitHeight - 16
            }
        },
        State {
            name: "visible"

            PropertyChanges {
                target: root
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
            if (root.state == "hidden" && !running)
                root.reloadRequested()
        }

    }
}
