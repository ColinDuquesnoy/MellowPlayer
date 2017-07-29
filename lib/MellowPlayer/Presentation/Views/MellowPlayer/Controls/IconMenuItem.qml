import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0
import ".."

MenuItem {
    id: root

    property string icon
    property string shortcut

    hoverEnabled: true
    contentItem: RowLayout {
        spacing: 8

        Label {
            text: root.icon
            font { family: MaterialIcons.family; pixelSize: 22 }
        }

        Label {
            text: root.text
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            horizontalAlignment: "AlignRight"
            text: shortcut
            font.italic: true

            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
        }
    }
}
