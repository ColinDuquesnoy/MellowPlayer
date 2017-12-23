import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."
import "../Controls"
import "../Dialogs"

Pane {
    id: root

    property var service: model
    padding: 0

    Material.elevation: 4
    Material.background: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background, 1.05) : Qt.darker(_theme.background, 1.05)

    ItemDelegate {
        anchors.fill: parent

        onClicked: {
            settingsDialog.service = root.service;
            settingsDialog.open()
        }

        Item {
            anchors.fill: parent

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16
                width: implicitWidth
                height: implicitHeight

                Label {
                    font.bold: true
                    horizontalAlignment: "AlignHCenter"
                    opacity: 0.66
                    text: model.name

                    Layout.fillWidth: true
                }

                Image {
                    mipmap: true; smooth: true
                    source: model.logo

                    Layout.preferredHeight: 128
                    Layout.preferredWidth: 128
                }

                Switch {
                    checked: model.isEnabled
                    onCheckedChanged: {
                        model.isEnabled = checked;
                        _streamingServices.enabledServices.update();
                    }

                    Layout.alignment: Qt.AlignHCenter
                }
            }

            Label {
                anchors{ bottom: parent.bottom; right: parent.right; margins: 12 }
                font { family: MaterialIcons.family; pixelSize: 24 }
                opacity: 0.66
                text: MaterialIcons.icon_settings
            }
        }
    }
}
