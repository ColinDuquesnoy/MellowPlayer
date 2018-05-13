import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

import MellowPlayer 3.0

Drawer {
    id: drawer

    clip: true
    edge: Qt.RightEdge
    dragMargin: 0

    onPositionChanged: if (position == 0) toolBar.searchChecked = false

    Page {
        anchors.fill: parent
        padding: 0

        header: ListeningHistoryToolBar { id: toolBar; onQuitRequested: drawer.close() }

        Item {
            anchors.fill: parent

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                ListeningHistorySearchPane {
                    id: searchPane

                    isOpen: toolBar.searchChecked

                    Layout.fillWidth: true
                    Layout.preferredHeight: searchPane.height
                }

                ListeningHistoryBody {
                    id: mainPane

                    searching: toolBar.searchChecked

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

            ListeningHistoryClipboardConfirmation {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.rightMargin: 8
                anchors.leftMargin: 8
                anchors.bottomMargin: 4
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmDelete

        standardButtons: Dialog.Yes | Dialog.No
        x: drawer.width / 2 - width / 2
        y: drawer.height / 2 - height / 2
    }
}

