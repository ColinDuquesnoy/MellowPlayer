import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Pane {
   id: root

   height: 64
   padding: 0

   Material.background: style.background
   Material.elevation: 2

   ColumnLayout {
       anchors.fill: parent

       RowLayout {
           Layout.fillWidth: true
           spacing: 0

           Pane {
               Layout.fillWidth: true

               Label {
                   text: section
                   font.weight: Font.Bold
                   verticalAlignment: "AlignVCenter"

                   Material.foreground: style.accent
                   anchors.fill: parent
               }
           }

           ToolButton {
               text: MaterialIcons.icon_delete
               font.pixelSize: 16
               font.family: MaterialIcons.family
               hoverEnabled: true
               onClicked: listeningHistory.removeByDateCategory(section)

               Layout.fillHeight: true
           }
       }

       Rectangle {
           color: style.accent
           width: parent.width
           height: 3

           Layout.fillWidth: true
       }
   }
}
