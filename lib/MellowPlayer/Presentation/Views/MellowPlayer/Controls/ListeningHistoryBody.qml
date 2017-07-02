import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

StackLayout {
    property bool searching: toolBar.searchChecked

    currentIndex: {
        if (d.historyEnabledSetting && !d.historyEnabledSetting.value)
            return d.pageDisabled;

        if (d.listIsEmpty) {
            if (searching)
                return d.pageNoMatchFound;
            return d.pageEmpty;
        }

        return d.pageList;
    }

    ListeningHistoryListView {
        id: listView

        anchors.fill: parent
    }

    Pane {
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            spacing: 20

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Label {
                text: MaterialIcons.icon_block
                font.pixelSize: 48
                font.family: MaterialIcons.family
                color: Material.color(Material.Red)

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: "No match found"
                font.bold: true
                font.pixelSize: 20

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    Pane {
        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Label {
                text: MaterialIcons.icon_history
                font.pixelSize: 48
                font.family: MaterialIcons.family
                color: Material.accent

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: "Nothing in history"
                font.bold: true
                font.pixelSize: 32

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: "The songs you listened to will appear here..."
                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    Pane {
        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Label {
                text: MaterialIcons.icon_history
                font.pixelSize: 48
                font.family: MaterialIcons.family
                color: Material.accent

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: "Nothing in history"
                font.bold: true
                font.pixelSize: 32

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: "Enable listening history and the songs you \nlistened to will appear here..."
                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Button {
                text: "Enable listening history"
                highlighted: true
                hoverEnabled: true
                onClicked: _settings.get(SettingKey.PRIVACY_ENABLE_LISTENING_HISTORY).value = true

                Tooltip {
                    text: qsTr("Click to enable listening history")
                }

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    QtObject {
        id: d

        readonly property int pageList: 0
        readonly property int pageNoMatchFound: 1
        readonly property int pageEmpty: 2
        readonly property int pageDisabled: 3

        property bool listIsEmpty: listView.count == 0
        property var historyEnabledSetting: _settings.get(SettingKey.PRIVACY_ENABLE_LISTENING_HISTORY)
    }
}
