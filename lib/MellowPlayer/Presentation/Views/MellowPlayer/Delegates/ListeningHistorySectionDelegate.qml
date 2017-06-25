import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Pane {
    id: root

    property bool expanded: false

    height: 64
    width: ListView.view.width
    padding: 0

    ItemDelegate {
       anchors.fill: parent
       hoverEnabled: true

       Material.background: style.background
       Material.elevation: 2

       contentItem: ColumnLayout {
           anchors.fill: parent

           RowLayout {
               Layout.fillWidth: true
               spacing: 0

               Item {
                   Layout.fillWidth: true
                   Layout.leftMargin: 12

                   RowLayout {
                       anchors.fill: parent
                       spacing: 8

                       Label {
                           text: root.expanded ? MaterialIcons.icon_keyboard_arrow_down : MaterialIcons.icon_keyboard_arrow_right
                           font.family: MaterialIcons.family
                           font.pixelSize: 22
                           verticalAlignment: "AlignVCenter"

                           Layout.fillHeight: true
                       }

                       Label {
                           text: section
                           font.weight: Font.Bold
                           verticalAlignment: "AlignVCenter"

                           Layout.fillHeight: true
                           Material.foreground: style.accent
                       }

                       Item {
                           Layout.fillWidth: true
                       }
                   }
               }

               ToolButton {
                   text: MaterialIcons.icon_delete
                   font.pixelSize: 16
                   font.family: MaterialIcons.family
                   hoverEnabled: true

                   onClicked: {
                       messageBoxConfirmDelete.message = qsTr('Are you sure you want to remote history of ' + section + '?')
                       messageBoxConfirmDelete.title = qsTr("Confirm remove")
                       messageBoxConfirmDelete.closed.connect(onActivated);
                       messageBoxConfirmDelete.open()
                   }

                   function onActivated() {
                       messageBoxConfirmDelete.closed.disconnect(onActivated);
                       if (messageBoxConfirmDelete.dialogResult === messageBoxConfirmDelete.dialogAccepted)
                           listeningHistory.removeByDateCategory(section)
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

       onClicked: root.ListView.view.toggleSection(section)
    }
}
