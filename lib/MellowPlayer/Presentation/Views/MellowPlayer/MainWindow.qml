import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Qt.labs.platform 1.0 as Platform

import MellowPlayer 3.0

ApplicationWindow {
    id: root

    property int previousVisibility: ApplicationWindow.Windowed
    property QtObject applicationRoot: ApplicationRoot { }

    function restoreWindow() {
        root.raise();
        root.show();
    }

    title: _streamingServices.currentService !== null ? _streamingServices.currentService.name : ""
    minimumWidth: 1280
    minimumHeight: 720
    onClosing: {
        var closeToTray = _settings.get(SettingKey.MAIN_CLOSE_TO_TRAY).value
        if (closeToTray) {
            var showMessageSetting = _settings.get(SettingKey.PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE)
            if (showMessageSetting.value) {
                showMessageSetting.value = false;
                messageBoxExitToTray.open();
            }
            else {
                _window.visible = false;
            }
            close.accepted = false;
        }
    }

    Material.accent: _style.accent
    Material.background: _style.background
    Material.foreground: _style.foreground
    Material.primary: _style.primary
    Material.theme: _style.theme == "light" ? Material.Light : Material.Dark

    Connections {
        target: _window
        onVisibleChanged: {
            if (_window.visible) {
                restoreWindow();
            }
            else {
                root.hide();
            }
        }
    }

    Connections {
        target: _app
        onQuitRequested: {
            var confirmExit = _settings.get(SettingKey.MAIN_CONFIRM_EXIT).value;
            if (confirmExit) {
                restoreWindow();
                messageBoxConfirmQuit.open();
            }
            else
                _app.quit();
        }
    }

    Shortcut {
        sequence: "Escape"
        onActivated: {
            if (root.visibility === ApplicationWindow.FullScreen) {
                root.visibility = root.previousVisibility;
                mainPage.exitFullScreen();
            }
            else if (!mainPage.isWebViewMode)
                mainPage.showWebView();
        }
    }

    Platform.MenuBar {
        id: menuBar

        Platform.Menu {
            id: fileMenu
            title: qsTr("File")
            // ...
        }

        Platform.Menu {
            id: editMenu
            title: qsTr("&Edit")
            // ...
        }

        Platform.Menu {
            id: viewMenu
            title: qsTr("&View")
            // ...
        }

        Platform.Menu {
            id: helpMenu
            title: qsTr("&Help")
            // ...
        }
    }

    MainPage {
        id: mainPage

        anchors.fill: parent
        mainWindowWidth: root.width
        onNewViewRequested: {
            if (request.userInitiated) {
                var dialog = applicationRoot.createDialog(profile);
                request.openIn(dialog.currentWebView);
            }
        }
        onFullScreenRequested: {
            if (request.toggleOn)
                root.showFullScreen();
            else
                root.visibility = root.previousVisibility;
            request.accept();
        }
        onOpenListeningHistoryRequested: listeningHistoryDrawer.open()
        onOpenSettingsRequested: settingsDrawer.open()
        onOpenAboutDialogRequested: aboutDialog.open()
    }

    Drawer {
        id: settingsDrawer

        clip: true
        width: root.width
        height: root.height
        edge: Qt.RightEdge
        interactive: false
        closePolicy: Popup.CloseOnPressOutside

        Shortcut {
            sequence: "Escape"
            onActivated: settingsDrawer.close()
        }

        SettingsPage {
            id: settingsPage

            anchors.fill: parent
            onCloseRequested: settingsDrawer.close()
        }
    }

    ListeningHistoryDrawer {
        id: listeningHistoryDrawer
        height: root.height;
        width: 450
    }

    AboutDialog {
        id: aboutDialog

        x: root.width / 2 - width / 2
        y: root.height / 2 - height / 2
        visible: false
    }

    MessageBoxDialog {
        id: messageBoxConfirmQuit

        standardButtons: Dialog.Ok | Dialog.Cancel
        message: qsTr("Are you sure you want to quit MellowPlayer?")
        title: qsTr("Confirm quit")
        onAccepted: _app.quit()
        x: root.width / 2 - width / 2
        y: root.height / 2 - height / 2
    }

    MessageBoxDialog {
        id: messageBoxExitToTray

        title: qsTr("Closing to system tray")
        message: qsTr("<p>MellowPlayer will continue to run in background.<br>" +
                      "You can quit the application or restore the main window via the system tray icon menu.</p>")
        standardButtons: Dialog.Ok
        onAccepted: _window.visible = false
        x: root.width / 2 - width / 2
        y: root.height / 2 - height / 2
    }
}
