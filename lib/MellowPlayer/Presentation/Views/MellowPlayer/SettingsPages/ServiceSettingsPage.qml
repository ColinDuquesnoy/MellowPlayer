import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."


ScrollView {
    anchors.fill: parent
    ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: 24
        anchors.rightMargin: parent.ScrollBar.vertical.size !== 1 ? 32 : 24
        clip: true
        delegate: ServiceSettingDelegate {
            width: listView.width;
        }
        model: _streamingServices.model
        spacing: 0
    }
}