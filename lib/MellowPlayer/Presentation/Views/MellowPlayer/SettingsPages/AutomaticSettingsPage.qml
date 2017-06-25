import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

ColumnLayout {
    id: page
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
            onClicked: messageBoxConfirmRestore.open()

            Material.accent: style.accent === "#ffc107" ? style.primary : style.accent

            Tooltip {
                text: 'Restore <b>' + model.name.toLowerCase() + '</b> settings to their <b>default values</b>.'
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        buttonTexts: [qsTr("Yes"), qsTr("No")]
        message: qsTr("Are you sure you want to restore all " + model.name.toLowerCase() + " settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: page.width / 2 - width / 2
        y: page.height / 2 - height / 2

        onAccepted: model.qtObject.restoreDefaults()
    }
}
