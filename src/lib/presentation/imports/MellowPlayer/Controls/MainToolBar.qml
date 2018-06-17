import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

ToolBar {
    id: root

    property bool isCurrentServiceRunning: false

    Material.primary: _theme.primary
    Material.foreground: _theme.primaryForeground
    Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent
        spacing: 0

        IconToolButton {
            iconChar: mainWindow.isOnRunningServicesPage ? MaterialIcons.icon_apps : MaterialIcons.icon_keyboard_arrow_left
            tooltip: mainWindow.isOnRunningServicesPage ?
                         qsTr("Select another service") :
                         mainWindow.hasRunningServices ? qsTr("Go back to ") + _streamingServices.currentService.name : ""
            visible: mainWindow.hasRunningServices

            onClicked: {
                if (!mainWindow.isOnRunningServicesPage && mainWindow.hasRunningServices)
                    stack.slideTransitions = true;
                else
                    stack.slideTransitions = false;
                mainWindow.toggleActivePage();
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible: mainWindow.isOnRunningServicesPage

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_chevron_left
            tooltip: qsTr("Go back")
            visible: mainWindow.isOnRunningServicesPage

            onTriggered: mainWindow.runningServices.goBack()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_chevron_right
            tooltip: qsTr("Go forward")
            visible: mainWindow.isOnRunningServicesPage

            onTriggered: mainWindow.runningServices.goForward()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_refresh
            tooltip: qsTr("Reload page")
            visible: mainWindow.isOnRunningServicesPage
            shortcut: _settings.get(SettingKey.SHORTCUTS_RELOAD).value

            onTriggered: mainWindow.runningServices.reload()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_home
            tooltip: qsTr("Go to home page")
            visible: mainWindow.isOnRunningServicesPage

            onTriggered: mainWindow.runningServices.goHome()
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible:  mainWindow.isOnRunningServicesPage && _player.canAddToFavorites

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        IconToolButton {
            visible: mainWindow.isOnRunningServicesPage && _player.canAddToFavorites
            iconChar: _player.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
            tooltip: _player.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
            shortcut: _settings.get(SettingKey.SHORTCUTS_FAVORITE).value

            onTriggered: _player.toggleFavoriteSong()
        }

        Item {
            Layout.fillWidth: true
        }

        IconToolButton {
            enabled: _player.canGoPrevious && d.isPlayerActive()
            iconChar: MaterialIcons.icon_fast_rewind
            tooltip: qsTr("Skip to previous song")
            visible: mainWindow.isOnRunningServicesPage
            shortcut: _settings.get(SettingKey.SHORTCUTS_PREVIOUS).value

            onTriggered: _player.previous()
        }

        IconToolButton {
            enabled: !_player.isStopped || d.isPlayerActive()
            iconChar: _player.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            tooltip: _player.isPlaying ? qsTr("Pause") : qsTr("Play")
            visible: mainWindow.isOnRunningServicesPage
            shortcut: _settings.get(SettingKey.SHORTCUTS_PLAY).value

            onTriggered: _player.togglePlayPause()
        }

        IconToolButton {
            enabled: _player.canGoNext && d.isPlayerActive()
            iconChar: MaterialIcons.icon_fast_forward
            tooltip: qsTr("Skip to next song")
            visible: mainWindow.isOnRunningServicesPage
            shortcut: _settings.get(SettingKey.SHORTCUTS_NEXT).value

            onTriggered: _player.next()
        }

        IconToolButton {
            property var setting: _settings.get(SettingKey.NOTIFICATIONS_ENABLED)

            checkable: true
            checked: setting.value
            iconChar: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off
            tooltip: checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
            shortcut: _settings.get(SettingKey.SHORTCUTS_NOTIFICATIONS).value

            onCheckedChanged: setting.value = checked;
            onTriggered: checked = !checked;

            Material.accent: _theme.accent === _theme.primary ? _theme.primaryForeground : _theme.accent
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

            visible: mainWindow.isOnRunningServicesPage
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_history
            tooltip: qsTr("Open listening history")
            shortcut: _settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY).value

            onTriggered: listeningHistoryDrawer.open()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_more_vert
            tooltip:  qsTr("Main menu")

            onTriggered: menu.open()

            Shortcut {
                id: shortcutSettings

                sequence: _settings.get(SettingKey.SHORTCUTS_SETTINGS).value

                onActivated: settingsDrawer.open()
            }

            Shortcut {
                id: shortcutCreatePlugin

                sequence: _settings.get(SettingKey.SHORTCUTS_CREATE_PLUGIN).value

                onActivated: newPluginWizard.open()
            }

            Shortcut {
                id: shortcutReportIssue

                sequence: _settings.get(SettingKey.SHORTCUTS_REPORT_ISSUE).value

                onActivated: Qt.openUrlExternally("https://github.com/ColinDuquesnoy/MellowPlayer/issues/new")
            }


            Shortcut {
                id: shortcutCheckForUpdates

                enabled: !_updater.busy
                sequence: _settings.get(SettingKey.SHORTCUTS_CHECK_FOR_UPDATE).value

                onActivated: _updater.check()
            }

            Shortcut {
                id: shortcutAbout

                sequence: _settings.get(SettingKey.SHORTCUTS_ABOUT).value

                onActivated: aboutDialog.open()
            }

            Shortcut {
                id: shortcutQuit

                sequence: _settings.get(SettingKey.SHORTCUTS_QUIT).value

                onActivated: _window.requestQuit()
            }

            Menu {
                id: menu
                y: parent.implicitHeight
                width: 300

                IconMenuItem {
                    id: menuItemSettings

                    iconChar: MaterialIcons.icon_settings
                    shortcut: shortcutSettings.sequence
                    text: qsTr("Settings")

                    onClicked: settingsDrawer.open()
                }

                IconMenuItem {
                    id: menuCreatePlugin

                    iconChar: MaterialIcons.icon_extension
                    shortcut: shortcutCreatePlugin.sequence
                    text: qsTr("Create plugin")

                    onClicked: newPluginWizard.open()
                }

                IconMenuItem {
                    id: menuReportIssue

                    iconChar: MaterialIcons.icon_bug_report
                    shortcut: shortcutReportIssue.sequence
                    text: qsTr("Report issue")

                    onClicked: Qt.openUrlExternally("https://github.com/ColinDuquesnoy/MellowPlayer/issues/new")
                }

                MenuSeparator { }

                IconMenuItem {
                    iconChar: MaterialIcons.icon_update
                    text: qsTr("Check for update")
                    enabled: !_updater.busy
                    shortcut: shortcutCheckForUpdates.sequence

                    onClicked: _updater.check()

                    ProgressBar {
                        anchors{ bottom: parent.bottom; horizontalCenter: parent.left; right: parent.right }
                        indeterminate: _updater.progress === -1
                        from: 0; to: 100
                        value: _updater.progress
                        visible: _updater.busy
                    }
                }

                IconMenuItem {
                    id: menuItemAbout

                    iconChar: MaterialIcons.icon_info_outline
                    shortcut: shortcutAbout.sequence
                    text: qsTr("About")

                    onClicked: aboutDialog.open()
                }

                IconMenuItem {
                    iconChar: MaterialIcons.icon_power_settings_new
                    shortcut: shortcutQuit.sequence
                    text: qsTr("Quit")

                    onClicked: _window.requestQuit()
                }
            }
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        height: root.height
        width: 500
        visible: mainWindow.isOnRunningServicesPage

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
                        return "<b>" + currentSong.title + qsTr("</b><i> by ") + currentSong.artist;
                    else if (currentSong.title)
                        return "<b>" + currentSong.title + "</b>";
                    else if (_streamingServices.currentService !== null)
                        return _streamingServices.currentService.name;
                    return "";
                }
            }

            Item {
                id: sliderGroup

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: layout.implicitWidth
                Layout.preferredHeight: visible ? slider.implicitHeight : 0
                Layout.margins: 0

                visible: _player.canSeek || _player.currentSong.duration !== 0

                RowLayout {
                    id: layout

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

                        function updateHandleVisibility() {
                            slider.handle.visible = _player.canSeek
                        }

                        hoverEnabled: true
                        from: 0; to: _player.currentSong.duration
                        value: _player.position

                        onMoved: {
                            if (_player.position !== value && _player.position < _player.currentSong.duration)
                                _player.seekToPosition(value)
                        }

                        Component.onCompleted: slider.updateHandleVisibility()
                        Layout.fillWidth: true
                        Material.accent: _theme.accent === _theme.primary ? _theme.primaryForeground : _theme.accent

                        Connections {
                            target: _player

                            onCanSeekChanged: slider.updateHandleVisibility()
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

    QtObject {
        id: d
        property int iconSize: 22

        function isPlayerActive() {
            return _player.currentSong !== null && _player.currentSong.isValid()
        }
    }

}
