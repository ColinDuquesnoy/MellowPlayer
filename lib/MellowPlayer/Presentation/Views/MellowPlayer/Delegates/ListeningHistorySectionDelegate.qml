import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Pane {
   id: sectionHeader
   property bool collapsed: false

   padding: 0

   Material.elevation: 2

   ColumnLayout {
       anchors.fill: parent

       RowLayout {
           Layout.fillWidth: true

           ToolButton {
               text: sectionHeader.collapsed ? MaterialIcons.icon_arrow_drop_down : MaterialIcons.icon_arrow_drop_up
               font.pixelSize: 22
               font.family: MaterialIcons.family

               onClicked: {
                   sectionHeader.collapsed = !sectionHeader.collapsed;
               }

               Layout.fillHeight: true
           }

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
               text: MaterialIcons.icon_clear
               font.pixelSize: 22
               font.family: MaterialIcons.family

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