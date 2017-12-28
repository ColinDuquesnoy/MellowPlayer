import QtQuick 2.9
import Qt.labs.platform 1.0 as Platform

import MellowPlayer 3.0

Platform.MenuBar {
    id: menuBar

    signal openSettingsRequested()
    signal goHomeRequested()
    signal goBackRequested()
    signal goForwardRequested()
    signal reloadRequested()
    signal openNewPluginWizardRequested()
    signal openAboutDialogRequested()

    Platform.Menu {
        id: appMenu
        title: qsTr("Application")

        Platform.MenuItem {
            text: qsTr("Preferences")

            property var shortcutSetting: _settings.get(SettingKey.SHORTCUTS_SETTINGS)

            shortcut: shortcutSetting.value
            onTriggered: menuBar.openSettingsRequested()
            role: Platform.MenuItem.PreferencesRole
        }
    }

    Platform.Menu {
        id: navigationMenu
        title: qsTr("Navigation")

        Platform.MenuItem {
            text: qsTr("Go Home")

            onTriggered: menuBar.goHomeRequested()
        }

        Platform.MenuItem {
            text: qsTr("Go Back")

            onTriggered: menuBar.goBackRequested()
        }

        Platform.MenuItem {
            text: qsTr("Go Forward")

            onTriggered: menuBar.goForwardRequested()
        }

        Platform.MenuSeparator { }

        Platform.MenuItem {
            text: qsTr("Reload page")

            onTriggered: menuBar.reloadRequested()
        }
    }

    Platform.Menu {
        id: playerMenu
        title: qsTr("Player")

        Platform.MenuItem {
            text: qsTr("Play/Pause")

            onTriggered: _player.togglePlayPause()
        }

        Platform.MenuItem {
            text: qsTr("Next")

            onTriggered: _player.next()
        }

        Platform.MenuItem {
            text: qsTr("Previous")

            onTriggered: _player.previous()
        }

        Platform.MenuSeparator { }

        Platform.MenuItem {
            text: qsTr("Add to favorites")

            onTriggered: _player.toggleFavoriteSong()
        }
    }

    Platform.Menu {
        id: devMenu
        title: qsTr("Developer")

        Platform.MenuItem {
            text: qsTr("Create new plugin")

            onTriggered: menuBar.openNewPluginWizardRequested()
        }
    }

    Platform.Menu {
        id: helpMenu
        title: qsTr("Help")

        Platform.MenuItem {
            text: qsTr("Preferences")

            property var shortcutSetting: _settings.get(SettingKey.SHORTCUTS_ABOUT)

            shortcut: shortcutSetting.value
            onTriggered: menuBar.openAboutDialogRequested()
            role: Platform.MenuItem.AboutRole
        }

        Platform.MenuItem {
            text: qsTr("Report issue")

            onTriggered: Qt.openUrlExternally("https://github.com/ColinDuquesnoy/MellowPlayer/issues/new")
            role: Platform.MenuItem.ApplicationSpecificRole
        }
    }
}
