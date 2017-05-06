import QtQuick 2.7
import MellowPlayer 3.0

MainWindow {
    id: mainWindow
    visible: true

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
        context: Qt.ApplicationShortcut
    }
}
