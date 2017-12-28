import QtQuick 2.9
import QtQuick.Controls 2.2

import MellowPlayer 3.0

SwitchDelegate {
    bottomPadding: 3; topPadding: 3
    anchors.fill: parent
    checked: model.qtObject.value
    enabled: model.enabled
    hoverEnabled: true
    onCheckedChanged: model.qtObject.value = checked
    text: SettingsTranslator.translateName(model.name)

    Tooltip {
        text: SettingsTranslator.translateToolTip(model.toolTip)
    }
}
