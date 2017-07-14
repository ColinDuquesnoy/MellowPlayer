import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

ToolBar {
    id: root

    property bool isWebViewMode: false
    property bool hasRunningServices: false

    signal showOverviewRequested()
    signal showWebViewRequested()
    signal goBackRequested()
    signal goHomeRequested()
    signal goForwardRequested()
    signal reloadRequested()
    signal openListeningHistoryRequested()
    signal openSettingsRequested()
    signal openAboutDialogRequested()

    Material.primary: _theme.primary
    Material.foreground: _theme.primaryForeground
    Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light


    QtObject {
        id: d
        property int iconSize: 22

        function isPlayerActive() {
            return _player.currentSong !== null && _player.currentSong.isValid()
        }
    }
    

    RowLayout {
        anchors.fill: parent
        spacing: 0

        ToolButton {
            id: btSelectService

            text: root.isWebViewMode ? MaterialIcons.icon_apps : MaterialIcons.icon_keyboard_arrow_left
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize + 2
            hoverEnabled: true
            visible: hasRunningServices || isWebViewMode

            onClicked: switchView()

            function switchView() {
                if (isWebViewMode)
                    root.showOverviewRequested()
                else
                    root.showWebViewRequested()
            }

            Shortcut {
                property var setting: _settings.get(SettingKey.SHORTCUTS_SELECT_SERVICE)

                sequence: setting.value
                onActivated: btSelectService.switchView()
            }

            Tooltip {
                y: root.implicitHeight
                text: root.isWebViewMode ? qsTr("Select another service") :
                      _streamingServices.currentService != null ?
                      qsTr("Go back to ") + _streamingServices.currentService.name : ""
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }

            visible: root.isWebViewMode
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_left
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode

            onClicked: root.goBackRequested()

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Go back")
            }
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_right
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            onClicked: root.goForwardRequested();

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Go forward")
            }
        }

        ToolButton {
            id: btReload

            text: MaterialIcons.icon_refresh
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            onClicked: root.reloadRequested()

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Reload this page")
            }

            Shortcut {
                property var setting: _settings.get(SettingKey.SHORTCUTS_RELOAD)

                sequence: setting.value
                onActivated: root.reloadRequested()
            }
        }

        ToolButton {
            text: MaterialIcons.icon_home
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            onClicked: root.goHomeRequested()

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Go to the homepage")
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible: btFavorite.visible

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        ToolButton {
            id: btFavorite
            text: _player.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            enabled: root.isWebViewMode && _player.canAddToFavorites
            visible: root.isWebViewMode

            onClicked: _player.toggleFavoriteSong()

            Tooltip {
                y: root.implicitHeight
                text: _player.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
            }
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            id: btPrevious

            text: MaterialIcons.icon_fast_rewind
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            enabled: _player.canGoPrevious && d.isPlayerActive()

            onClicked: _player.previous()

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Skip to previous song")
            }
        }

        ToolButton {
            id: btPlay

            text: _player.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            enabled: !_player.isStopped || d.isPlayerActive()

            onClicked: _player.togglePlayPause()

            Tooltip {
                y: root.implicitHeight
                text:  _player.isPlaying ? qsTr("Pause") : qsTr("Play")
            }
        }

        ToolButton {
            id: btNext

            text: MaterialIcons.icon_fast_forward
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            visible: root.isWebViewMode
            enabled: _player.canGoNext && d.isPlayerActive()

            onClicked: _player.next()

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Skip to next song")
            }
        }

        ToolButton {
            id: btEnableNotifications

            property var setting: _settings.get(SettingKey.NOTIFICATIONS_ENABLED)

            checkable: true
            checked: setting.value
            font { family: MaterialIcons.family; pixelSize: d.iconSize }
            hoverEnabled: true
            onClicked: setting.value = checked
            text: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off

            Layout.fillHeight: true
            Material.accent: _theme.accent == _theme.primary ? _theme.primaryForeground : _theme.accent

            Tooltip {
                y: root.implicitHeight
                text: btEnableNotifications.checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
            }

            Shortcut {
                property var shortcut: _settings.get(SettingKey.SHORTCUTS_NOTIFICATIONS)

                sequence: shortcut.value
                onActivated: btEnableNotifications.setting.value = !btEnableNotifications.setting.value
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }

            visible: root.isWebViewMode
        }

        ToolButton {
            text: MaterialIcons.icon_history
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize
            hoverEnabled: true
            onClicked: root.openListeningHistoryRequested()

            Tooltip {
                y: parent.implicitHeight
                text: qsTr("Listening history")
            }

            Shortcut {
                property var shortcut: _settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY)

                sequence: shortcut.value
                onActivated: root.openListeningHistoryRequested()
            }
        }

        ToolButton {
            text: MaterialIcons.icon_more_vert
            font.family: MaterialIcons.family
            font.pixelSize: d.iconSize + 2
            hoverEnabled: true
            onClicked: menu.open()

            Shortcut {
                property var shortcut: _settings.get(SettingKey.SHORTCUTS_SETTINGS)

                sequence: shortcut.value
                onActivated: root.openSettingsRequested()
            }

            Shortcut {
                property var shortcut: _settings.get(SettingKey.SHORTCUTS_ABOUT)

                sequence: shortcut.value
                onActivated: root.openAboutDialogRequested()
            }

            Shortcut {
                property var shortcut: _settings.get(SettingKey.SHORTCUTS_QUIT)

                sequence: shortcut.value
                onActivated: _app.requestQuit();
            }

            Menu {
                id: menu
                y: parent.implicitHeight

                MenuIconItem {
                    id: menuItemSettings

                    icon: MaterialIcons.icon_settings
                    onClicked: root.openSettingsRequested()
                    text: "Settings"
                }

                MenuIconItem {
                    id: menuItemAbout

                    icon: MaterialIcons.icon_info_outline
                    text: "About"
                    onClicked: root.openAboutDialogRequested()
                }

                MenuIconItem {
                    id: menuReportIssue

                    icon: MaterialIcons.icon_bug_report
                    text: "Report issue"
                    onClicked: Qt.openUrlExternally("https://github.com/ColinDuquesnoy/MellowPlayer/issues/new")
                }

                Rectangle {
                    color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
                    height: 1
                    width: parent.width
                }

                MenuIconItem {
                    icon: MaterialIcons.icon_power_settings_new
                    text: "Quit"
                    onClicked: _app.requestQuit()
                }
            }

            Tooltip {
                y: root.implicitHeight
                text: qsTr("Main menu")
            }
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        height: root.height
        width: 300
        visible: root.isWebViewMode

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 9
            spacing: 0

            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: getText()
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: sliderGroup.visible ? "AlignTop" : "AlignVCenter"
                elide: "ElideMiddle"
                font.pixelSize: sliderGroup.visible ? 12 : 14

                function getText() {
                    var currentSong = _player.currentSong;
                    if (currentSong.title && currentSong.artist)
                        return "<b>" + currentSong.title + "</b><i> by " + currentSong.artist;
                    else if (currentSong.title)
                        return "<b>" + currentSong.title + "</b>";
                    else if (_streamingServices.currentService !== null)
                        return _streamingServices.currentService.name;
                    return "";
                }
            }

            Item {
                id: sliderGroup
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? slider.implicitHeight : 0
                Layout.margins: 0
                visible: _player.canSeek

                RowLayout {
                    anchors.fill: parent

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(_player.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return text;
                        }
                        font.pixelSize: 11
                    }

                    Slider {
                        id: slider

                        Layout.fillWidth: true
                        hoverEnabled: true

                        from: 0
                        value: _player.position
                        to: _player.currentSong.duration

                        onValueChanged: {
                            if (_player.position !== value && _player.position < _player.currentSong.duration)
                                _player.seekToPosition(value)
                        }

                    }

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(_player.currentSong.duration - _player.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return "-" + text;
                        }
                        font.pixelSize: 11
                    }
                }
            }
        }
    }
}
