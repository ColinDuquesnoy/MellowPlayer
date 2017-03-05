import QtQuick 2.7
import "qrc:/MellowPlayer/Presentation/resources"
import "controls"

MainWindow {
    id: mainWindow
    visible: true

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
        context: Qt.ApplicationShortcut
    }
}
