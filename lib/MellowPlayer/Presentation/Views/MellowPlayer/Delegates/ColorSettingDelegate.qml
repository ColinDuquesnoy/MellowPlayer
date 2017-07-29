import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

import MellowPlayer 3.0
import ".."

ItemDelegate {
    bottomPadding: 3; topPadding: 3
    enabled: model.enabled
    hoverEnabled: true
    onClicked: colorDialog.open()

    contentItem: RowLayout {
        Label {
            text: model.name
            font.pixelSize: 16
            Layout.fillWidth: true
        }

        Button {
            hoverEnabled: true
            text: model.qtObject.value
            onTextChanged: model.qtObject.value = text
            onClicked: colorDialog.open()

            Material.background: model.qtObject.value
            Material.foreground: _theme.isDark(model.qtObject.value) ? "white" : "#303030"

            Tooltip {
                text: model.toolTip
            }

            ColorDialog {
                id: colorDialog

                title: qsTr("Please choose a color")
                color: model.qtObject.value
                onColorChanged: model.qtObject.value = color
            }
        }
    }
}
