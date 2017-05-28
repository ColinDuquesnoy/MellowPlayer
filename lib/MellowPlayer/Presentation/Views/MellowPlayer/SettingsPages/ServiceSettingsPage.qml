import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0


Pane {
    padding: 24
    clip: true
    anchors.fill: parent

    ListView {
        id: listView

        anchors.fill: parent
        clip: true
        delegate: ServiceSettingDelegate { width: listView.width; }
        model: streamingServices.model
        spacing: 8

        ScrollBar.vertical: DesktopScrollBar {
            anchors { top: listView.top; left: listView.right; bottom: listView.bottom; leftMargin: 8 }
            parent: listView.parent
            visible: size != 1
        }
    }
}
