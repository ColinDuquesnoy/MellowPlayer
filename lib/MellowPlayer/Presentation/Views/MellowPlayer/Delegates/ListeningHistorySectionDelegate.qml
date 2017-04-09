import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Rectangle {
   id: root

   property bool collapsed: false

   height: 64
   color: style.background

   ColumnLayout {
       anchors.fill: parent
       anchors.margins: 3

       RowLayout {
           Layout.fillWidth: true

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

           Label {
               text: root.collapsed ? MaterialIcons.icon_expand_more : MaterialIcons.icon_expand_less
               font.pixelSize: 22
               font.family: MaterialIcons.family
           }

//           ToolButton {
//               text: root.collapsed ? MaterialIcons.icon_expand_more : MaterialIcons.icon_expand_less
//               font.pixelSize: 22
//               font.family: MaterialIcons.family
//               hoverEnabled: true

//               Layout.fillHeight: true
//           }
       }

       Rectangle {
           color: style.accent
           width: parent.width
           height: 3

           Layout.fillWidth: true
       }
   }

   MouseArea {
       anchors.fill: parent
       hoverEnabled: true
       cursorShape: containsMouse ? "PointingHandCursor" : "ArrowCursor"

       onClicked: {
           root.collapsed = !root.collapsed;
           listView.collapsedSections[section] = root.collapsed;
           listView.sectionCollapsedChanged(section, root.collapsed);
       }
   }
}
