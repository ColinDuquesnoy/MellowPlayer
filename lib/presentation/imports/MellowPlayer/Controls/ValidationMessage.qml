import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Pane {
    property alias text: label.text

    visible: false
    z: 1

    Material.background: _theme.primary
    Material.foreground: _theme.primaryForeground
    Material.elevation: 4

    Label {
        id: label

        anchors.fill: parent
    }
}

