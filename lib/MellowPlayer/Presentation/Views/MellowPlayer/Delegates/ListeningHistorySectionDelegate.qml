import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."
import "../DateCategoryTranslator.js" as DateCategoryTranslator

Pane {
    id: root

    property bool expanded: false

    height: 64
    width: ListView.view.width
    padding: 0

    Material.elevation: 2
    Material.background: _theme.background
    Material.theme: _theme.isDark(_theme.background) ? Material.Dark : Material.Light

    ItemDelegate {
       anchors.fill: parent
       hoverEnabled: true

       ColumnLayout {
           anchors.fill: parent
           anchors.leftMargin: parent.leftPadding
           anchors.rightMargin: parent.rightPadding
           anchors.topMargin: parent.topPadding
           anchors.bottomMargin: parent.bottomPadding

           RowLayout {
               Layout.fillWidth: true
               spacing: 0

               Item {
                   Layout.fillWidth: true
                   Layout.margins: 12

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
                           text: DateCategoryTranslator.translate(section)
                           font.weight: Font.Bold
                           verticalAlignment: "AlignVCenter"

                           Layout.fillHeight: true
                           Material.foreground: _theme.accent
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
                           _listeningHistory.removeByDateCategory(section)
                   }

                   Layout.fillHeight: true
               }
           }

           Rectangle {
               color: _theme.accent
               width: parent.width
               height: 3

               Layout.fillWidth: true
           }
       }

       onClicked: root.ListView.view.toggleSection(section)
    }
}
