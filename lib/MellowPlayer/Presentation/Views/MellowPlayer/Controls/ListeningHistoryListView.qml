import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import MellowPlayer 3.0



Item {
    ListView {
       id: listView

       anchors.fill: parent
       clip: true
       spacing: 12
       model: listeningHistory.model
       delegate: ListeningHistoryEntryDelegate {
           width: listView.width
       }

       Component.onCompleted: console.log(model.count)

       ScrollBar.vertical: ScrollBar {
           parent: listView.parent
           anchors.top: listView.top
           anchors.left: listView.right
           anchors.bottom: listView.bottom
           anchors.margins: 2
           active: hovered
           hoverEnabled: true

       }

       add: Transition {
           NumberAnimation { property: "opacity"; from: 0; to: 1.0; easing.type: Easing.InOutCubic }
           NumberAnimation { property: "scale"; from: 0; to: 1.0; easing.type: Easing.InOutCubic }
       }

       displaced: Transition {
           NumberAnimation { properties: "x,y"; easing.type: Easing.InOutCubic }
       }

       section.property: "date"
    }
}


