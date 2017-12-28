import QtQuick 2.9
import QtQuick.Controls 2.2

import MellowPlayer 3.0
import ".."
import "../Controls"
import "../SettingsTranslator.js" as Translator

SwitchDelegate {
    bottomPadding: 3; topPadding: 3
    anchors.fill: parent
    checked: model.qtObject.value
    enabled: model.enabled
    hoverEnabled: true
    onCheckedChanged: model.qtObject.value = checked
    text: Translator.translateName(model.name)

    Tooltip {
        text: Translator.translateToolTip(model.toolTip)
    }
}
