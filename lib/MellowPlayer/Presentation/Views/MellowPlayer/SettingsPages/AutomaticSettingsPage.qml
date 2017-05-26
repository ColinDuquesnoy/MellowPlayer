import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

ColumnLayout {
    anchors.fill: parent

    Flickable {
        id: root

        property var settingsModel: model.settings

        contentHeight: pane.implicitHeight
        contentWidth: parent.width

        Layout.fillHeight: true

        Pane {
            id: pane

            anchors.fill: parent
            padding: 16

            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                clip: true

                Repeater {
                    model: root.settingsModel

                    Loader {
                        source: model.qmlComponent
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
        ScrollBar.vertical: ScrollBar { }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.rightMargin: 16
        Layout.bottomMargin: 8

        Item { Layout.fillWidth: true }

        Button {
            highlighted: true
            hoverEnabled: true
            text: "Restore defaults"
            onClicked: model.qtObject.restoreDefaults()

            Tooltip {
                text: 'Reset <b>' + model.name.toLowerCase() + '</b> settings to their <b>default value</b>.'
            }
        }
    }
}
