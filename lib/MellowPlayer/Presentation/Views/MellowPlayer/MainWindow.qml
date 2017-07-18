import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Qt.labs.platform 1.0 as Platform

import MellowPlayer 3.0

ApplicationWindow {
    id: root

    minimumWidth: 1280; minimumHeight: 720
    title: _streamingServices.currentService !== null ? _streamingServices.currentService.name : ""

    onClosing: d.handleCloseEvent(close);

    Material.accent: _theme.accent
    Material.background: _theme.background
    Material.foreground: _theme.foreground
    Material.primary: _theme.primary
    Material.theme: _theme.dark ? Material.Dark : Material.Light

    MainPage {
        id: mainPage

        anchors.fill: parent
        mainWindowWidth: root.width

        onNewViewRequested: d.openWebPopup(request)
        onFullScreenRequested: d.toggleFullScreen(request)
        onOpenListeningHistoryRequested: listeningHistoryDrawer.open()
        onOpenSettingsRequested: settingsDrawer.open()
        onOpenAboutDialogRequested: aboutDialog.open()
        onCreatePluginRequested: newPluginWizard.open()
    }

    SettingsDrawer {
        id: settingsDrawer;

        width: root.width; height: root.height
    }

    ListeningHistoryDrawer {
        id: listeningHistoryDrawer;

        height: root.height; width: 450
    }

    AboutDialog {
        id: aboutDialog
    }

    MessageBoxDialog {
        id: confirmQuitMsgBox

        standardButtons: Dialog.Ok | Dialog.Cancel
        message: qsTr("Are you sure you want to quit MellowPlayer?")
        title: qsTr("Confirm quit")

        onAccepted: _app.quit()
    }

    MessageBoxDialog {
        id: exitToTrayMsgBox

        title: qsTr("Closing to system tray")
        message: qsTr("<p>MellowPlayer will continue to run in background.<br>" +
                      "You can quit the application or restore the main window via the system tray icon menu.</p>")
        standardButtons: Dialog.Ok

        onAccepted: _window.visible = false
    }

    NewPluginWizard {
        id: newPluginWizard

        height: 540; width: 960
        x: root.width / 2 - width / 2; y: root.height / 2 - height / 2
    }

    NativeMenuBar {
        onOpenSettingsRequested: settingsDrawer.open()
        onGoHomeRequested: mainPage.goHome()
        onGoBackRequested: mainPage.goBack()
        onGoForwardRequested: mainPage.goForward()
        onReloadRequested: mainPage.reload()
        onOpenNewPluginWizardRequested: newPluginWizard.open();
        onOpenAboutDialogRequested: aboutDialog.open()
    }

    Connections {
        target: _window;

        onVisibleChanged: _window.visible ? d.restoreWindow() : root.hide()
    }

    Connections {
        target: _app;

        onQuitRequested: d.quit()
    }

    Shortcut {
        sequence: "Escape";

        onActivated: d.handleEscapeKey()
    }

    QtObject {
        id: d

        property int previousVisibility: ApplicationWindow.Windowed
        property QtObject applicationRoot: ApplicationRoot { }

        function restoreWindow() {
            root.raise();
            root.show();
        }

        function openWebPopup(request) {
            if (request.userInitiated) {
                var dialog = d.applicationRoot.createDialog(profile);
                request.openIn(dialog.currentWebView);
            }
        }

        function toggleFullScreen(request) {
            if (request.toggleOn)
                root.showFullScreen();
            else
                root.visibility = d.previousVisibility;
            request.accept();
        }

        function handleEscapeKey() {
            if (root.visibility === ApplicationWindow.FullScreen) {
                root.visibility = d.previousVisibility;
                mainPage.exitFullScreen();
            }
            else if (!mainPage.isWebViewMode)
                mainPage.showWebView();
        }

        function handleCloseEvent(close) {
            var closeToTray = _settings.get(SettingKey.MAIN_CLOSE_TO_TRAY).value
            if (closeToTray) {
                var showMessageSetting = _settings.get(SettingKey.PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE)
                if (showMessageSetting.value) {
                    showMessageSetting.value = false;
                    exitToTrayMsgBox.open();
                }
                else {
                    _window.visible = false;
                }
                close.accepted = false;
            }
        }

        function quit() {
            var confirmExit = _settings.get(SettingKey.MAIN_CONFIRM_EXIT).value;
            if (confirmExit) {
                d.restoreWindow();
                confirmQuitMsgBox.open();
            }
            else
                _app.quit();
        }
    }
}
