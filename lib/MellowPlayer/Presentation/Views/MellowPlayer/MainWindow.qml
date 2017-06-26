import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0

ApplicationWindow {
    id: mainWindow

    property QtObject applicationRoot: ApplicationRoot { }

    title: streamingServices.currentService !== null ? streamingServices.currentService.name : ""
    minimumWidth: 1280
    minimumHeight: 720
    onClosing: {
        var closeToTray = settings.get(SettingKey.MAIN_CLOSE_TO_TRAY).value
        if (closeToTray) {
            var showMessageSetting = settings.get(SettingKey.PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE)
            if (showMessageSetting.value) {
                showMessageSetting.value = false;
                messageBoxExitToTray.open();
            }
            else {
                windowModel.visible = false;
            }
            close.accepted = false;
        }
    }

    Material.accent: style.accent
    Material.background: style.background
    Material.foreground: style.foreground
    Material.primary: style.primary
    Material.theme: style.theme == "light" ? Material.Light : Material.Dark

    function restoreWindow() {
        mainWindow.raise();
        mainWindow.show();
    }

    Connections {
        target: windowModel
        onVisibleChanged: {
            if (windowModel.visible) {
                restoreWindow();
            }
            else {
                mainWindow.hide();
            }
        }
    }

    Connections {
        target: qtApp
        onQuitRequested: {
            var confirmExit = settings.get(SettingKey.MAIN_CONFIRM_EXIT).value;
            if (confirmExit) {
                restoreWindow();
                messageBoxConfirmQuit.open();
            }
            else
                qtApp.quit();
        }
    }

    StackView {
        id: stackView

        anchors.fill: parent
        initialItem: mainPage
    }

    Component {
        id: mainPage

        MainPage { }
    }

    Component {
        id: settingsPageComponent

        SettingsPage { }
    }

    ListeningHistoryDrawer { id: listeningHistoryDrawer }

    AboutDialog {
        id: aboutDialog

        x: mainWindow.width / 2 - width / 2
        y: mainWindow.height / 2 - height / 2
        visible: false
    }

    MessageBoxDialog {
        id: messageBoxConfirmQuit

        standardButtons: Dialog.Ok | Dialog.Cancel
        message: qsTr("Are you sure you want to quit MellowPlayer?")
        title: qsTr("Confirm quit")
        onAccepted: qtApp.quit()
        x: mainWindow.width / 2 - width / 2
        y: mainWindow.height / 2 - height / 2
    }

    MessageBoxDialog {
        id: messageBoxExitToTray

        title: qsTr("Closing to system tray")
        message: qsTr("<p>MellowPlayer will continue to run in background.<br>" +
                      "You can quit the application or restore the main window via the system tray icon menu.</p>")
        standardButtons: Dialog.Ok
        onAccepted: windowModel.visible = false
        x: mainWindow.width / 2 - width / 2
        y: mainWindow.height / 2 - height / 2
    }
}
