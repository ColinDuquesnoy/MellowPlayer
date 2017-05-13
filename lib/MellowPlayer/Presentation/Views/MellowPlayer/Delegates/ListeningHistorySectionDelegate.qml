import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Rectangle {
   id: root

   property bool collapsed: listView.collapsedSections[section]

   height: 64
   color: style.background

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

               Layout.fillHeight: true
           }

           ToolButton {
               text: root.collapsed ? MaterialIcons.icon_expand_more : MaterialIcons.icon_expand_less
               font.pixelSize: 16
               font.family: MaterialIcons.family
               hoverEnabled: true
               onClicked: {
                   root.collapsed = !root.collapsed;
                   listView.collapsedSections[section] = root.collapsed;
                   listView.sectionCollapsedChanged(section, root.collapsed);
               }

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
