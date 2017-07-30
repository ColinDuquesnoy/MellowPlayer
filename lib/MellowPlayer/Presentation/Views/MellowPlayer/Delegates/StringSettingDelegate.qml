import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0
import ".."
import "../SettingsTranslator.js" as Translator

Pane {
    bottomPadding: 3; topPadding: 3
    enabled: model.enabled
    width: parent.width

    RowLayout {
        spacing: 16

        Label {
            text: Translator.translateName(model.name)
            font.pixelSize: 16
        }

        TextField {
            hoverEnabled: true
            onTextChanged: model.qtObject.value = text
            placeholderText: model.name
            text: model.qtObject.value

            Tooltip {
                text: Translator.translateToolTip(model.toolTip)
            }

            Layout.fillWidth: true
        }
    }
}
