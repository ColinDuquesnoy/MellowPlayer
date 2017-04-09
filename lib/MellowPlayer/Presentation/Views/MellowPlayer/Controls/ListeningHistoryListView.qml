import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Item {
    ListView {
       id: listView

       anchors.fill: parent
       clip: true
       spacing: 12
       model: listeningHistory.model
       delegate: ListeningHistoryEntryDelegate { width: listView.width; }
       section.criteria: ViewSection.FullString
       section.delegate: Pane {
           id: sectionHeader
           property bool collapsed: false

           width: parent.width
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
       section.labelPositioning: ViewSection.InlineLabels | ViewSection.CurrentLabelAtStart
       section.property: "dateCategory"

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
            SequentialAnimation {
                NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
                PauseAnimation { duration: 250; }
                NumberAnimation { properties: "x"; duration: 300; from: 950; to: 0 }
            }
       }

       displaced: Transition {
           NumberAnimation { properties: "x, y"; duration: 300 }
       }       
    }
}


