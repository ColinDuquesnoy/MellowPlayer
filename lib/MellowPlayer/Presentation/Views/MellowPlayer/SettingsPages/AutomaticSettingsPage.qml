import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

ColumnLayout {
    id: page

    ScrollView {
        id: root

        property var settingsModel: model.settings

        contentHeight: listView.contentHeight
        contentWidth: width
        clip: true

        Layout.fillHeight: true
        Layout.fillWidth: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded

        ListView {
            id: listView

            anchors {
                fill: parent;
                rightMargin: parent.ScrollBar.vertical.size != 1 ? 16 : 0
            }
            clip: true
            delegate: ColumnLayout {
                width: ListView.view.width
                spacing: 0

                Loader {
                    id: loader
                    source: model.qmlComponent

                    Layout.fillWidth: true
                    Layout.preferredHeight: 56
                }

                Rectangle {
                    color: _style.isDark(_style.background) ? Qt.lighter(_style.background) : Qt.darker(_style.background, 1.1)
                    visible: model.index != parent.ListView.view.count - 1

                    Layout.preferredHeight: 1
                    Layout.fillWidth: true
                }
            }
            model: root.settingsModel
            spacing: 0
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.rightMargin: 24
        Layout.bottomMargin: 8

        Item { Layout.fillWidth: true }

        Button {
            highlighted: true
            hoverEnabled: true
            text: "Restore defaults"
            onClicked: messageBoxConfirmRestore.open()

            Material.accent: _style.accent === "#ffc107" ? _style.primary : _style.accent

            Tooltip {
                text: 'Restore <b>' + model.name.toLowerCase() + '</b> _settings to their <b>default values</b>.'
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        standardButtons: Dialog.Yes | Dialog.No
        message: qsTr("Are you sure you want to restore all " + model.name.toLowerCase() + " _settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: page.width / 2 - width / 2
        y: page.height / 2 - height / 2

        onAccepted: model.qtObject.restoreDefaults()
    }
}
