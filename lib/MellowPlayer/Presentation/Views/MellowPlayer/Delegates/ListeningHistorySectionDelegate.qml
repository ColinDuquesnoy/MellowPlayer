import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Pane {
   id: root

   height: 64
   width: ListView.view.width
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
               // onClicked: listeningHistory.removeByDateCategory(section)

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
}
