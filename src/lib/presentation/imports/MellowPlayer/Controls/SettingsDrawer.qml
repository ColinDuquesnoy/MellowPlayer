import QtQuick 2.9
import QtQuick.Controls 2.2

import MellowPlayer 3.0

Drawer {
    id: root

    edge: Qt.RightEdge
    interactive: false

    Shortcut {
        sequence: "Escape"
        onActivated: close()
    }

    SettingsPage {
        anchors.fill: parent
        onCloseRequested: close()
    }
}
