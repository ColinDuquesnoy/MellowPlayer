import QtQuick 2.9
import QtQuick.Controls 2.2

import MellowPlayer 3.0

CheckDelegate {
    bottomPadding: 3; topPadding: 3
    checked: model.qtObject.value
    enabled: model.enabled
    hoverEnabled: true
    onCheckedChanged: model.qtObject.value = checked
    text: model.name

    Tooltip {
        text: model.toolTip
    }
}
