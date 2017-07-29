import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

ToolBar {
    id: root

    property bool searchEnabled: true
    property alias searchChecked: btSearch.checked

    signal quitRequested()

    Material.primary: _theme.primary
    Material.foreground: _theme.primaryForeground
    Material.elevation: 4
    Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent

        ToolButton {
            id: btSearch

            checkable: true
            checked: false
            font { family: MaterialIcons.family; pixelSize: 22 }
            text: MaterialIcons.icon_search

            hoverEnabled: true
            enabled: root.enabled

            Material.accent: _theme.accent == _theme.primary ? _theme.primaryForeground : _theme.accent

            Tooltip {
                text: qsTr("Search/filter")
            }
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            id: btBackFromListeningHistory

            font { family: MaterialIcons.family; pixelSize: 22 }
            hoverEnabled: true
            onClicked: quitRequested()
            text: MaterialIcons.icon_keyboard_arrow_right

            Layout.fillHeight: true

            Tooltip {
                text: qsTr("Back")
            }

            Shortcut {
                sequence: _settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY)
                onActivated: quitRequested()
            }
        }
    }

    Label {
        anchors.centerIn: parent
        text: qsTr("Listening history")
    }
}
