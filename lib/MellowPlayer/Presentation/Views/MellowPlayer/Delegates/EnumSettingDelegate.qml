import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0
import ".."
import "../SettingsTranslator.js" as Translator

ItemDelegate {
    property var values: model.qtObject.values
    property var qtObject: model.qtObject

    bottomPadding: 3; topPadding: 3
    hoverEnabled: true
    enabled: model.enabled
    onClicked: comboBox.popup.open()

    contentItem: RowLayout {
        Label {
            text: Translator.translateName(model.name)
            font.pixelSize: 16

            Layout.fillWidth: true
        }

        ComboBox {
            id: comboBox

            hoverEnabled: true
            model: values
            currentIndex: values.indexOf(qtObject.value)
            onCurrentTextChanged: qtObject.value = currentText

            Layout.preferredWidth: 250

            Tooltip {
                text: Translator.translateToolTip(model.toolTip)
            }
        }
    }
}
