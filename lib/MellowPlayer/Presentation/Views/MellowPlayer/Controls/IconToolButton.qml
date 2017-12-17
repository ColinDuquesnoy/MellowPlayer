import QtQuick 2.9
import QtQuick.Controls 2.2

import ".."

ToolButton {
    id: root

    property string shortcut: ""
    property string tooltip: ""
    property string iconChar: ""
    property int iconSize: 22

    signal triggered()

    text: iconChar
    font { family: MaterialIcons.family; pixelSize: iconSize }
    hoverEnabled: true

    onClicked: if (!checkable) triggered()

    Tooltip {
        y: parent.implicitHeight
        text: root.tooltip
        shortcut: root.shortcut
    }

    Shortcut {
        sequence: root.shortcut
        onActivated: root.triggered()
    }
}
