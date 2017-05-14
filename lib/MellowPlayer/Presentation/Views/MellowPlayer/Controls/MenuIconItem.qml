import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import MellowPlayer 3.0

MenuItem {
    id: root

    property string icon

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
    }
}
