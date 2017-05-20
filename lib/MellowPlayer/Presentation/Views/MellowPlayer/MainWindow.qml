import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import MellowPlayer 3.0

ApplicationWindow {
    id: mainWindow

    property QtObject applicationRoot: ApplicationRoot { }

    title: streamingServices.currentService !== null ? streamingServices.currentService.name : ""
    minimumWidth: 1280
    minimumHeight: 720

    Material.accent: style.accent
    Material.background: style.background
    Material.foreground: style.foreground
    Material.primary: style.primary
    Material.theme: style.theme == "light" ? Material.Light : Material.Dark

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
}
