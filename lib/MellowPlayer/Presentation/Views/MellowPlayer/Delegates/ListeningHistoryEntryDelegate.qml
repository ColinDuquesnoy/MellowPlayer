import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Frame {
    id: root

    property string section: ListView.section

    height: 72
    width: ListView.view.width

    background: Rectangle {
        color: "transparent"
        visible: index != listView.count - 1

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: style.isDark(style.background) ? Qt.lighter(style.background) : Qt.darker(style.background, 1.1)
            height: 1
        }
    }
    clip: true
    padding: 1
    hoverEnabled: true
    onHoveredChanged: {
        if (hovered) {
            delayTimer.start();
        }
        else {
            delayTimer.stop();
            controlPane.visible = false
        }
    }

    ListView.onRemove: SequentialAnimation {
        PropertyAction { target: root; property: "ListView.delayRemove"; value: true }
        NumberAnimation { target: root; property: "x"; to: 950; duration: 200 ; easing.type: Easing.InOutQuad }
        PropertyAction { target: root; property: "ListView.delayRemove"; value: false }
    }

    Timer {
        id: delayTimer
        interval: 400
        onTriggered: controlPane.visible = true
    }

    Pane {
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            spacing: 8

            Image {
                source: model.artUrl

                Layout.preferredHeight: 48
                Layout.preferredWidth: 48
            }

            Column {
                Label {
                    text: model.title
                    elide: "ElideMiddle"
                    font.bold: true
                    width: 250
                }

                Label {
                    text: "by " + model.artist
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 250
                }

                Label {
                    text: "on " + model.service
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 250
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
                text: {
                    if (model.dateCategory === qsTr("Today") || model.dateCategory === qsTr("Yesterday"))
                        return model.dateCategory + "\n" + model.time
                    else
                        return model.date + "\n" + model.time
                }
                verticalAlignment: "AlignVCenter"
                horizontalAlignment:"AlignRight"
            }
        }
    }

    Pane {
        id: controlPane

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        opacity: 0.9
        visible: false

        RowLayout {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ToolButton {
                id: btDelete
                hoverEnabled: true
                text: MaterialIcons.MaterialIcons.icon_delete
                font { family: MaterialIcons.family; pixelSize: 16 }
                onClicked: {
                    messageBoxConfirmDelete.message = qsTr('Are you sure you want to remote that song from the history?')
                    messageBoxConfirmDelete.title = qsTr("Confirm remove")
                    messageBoxConfirmDelete.closed.connect(onActivated);
                    messageBoxConfirmDelete.open()
                }

                function onActivated() {
                    messageBoxConfirmDelete.closed.disconnect(onActivated);
                    if (messageBoxConfirmDelete.dialogResult === messageBoxConfirmDelete.dialogAccepted)
                        listeningHistory.removeById(model.entryId)
                }

                Layout.fillHeight: true
            }

            ToolButton {
                id: btCopy
                hoverEnabled: true
                text: MaterialIcons.MaterialIcons.icon_content_copy
                font { family: MaterialIcons.family; pixelSize: 16 }
                onClicked: {
                    clipboard.setText(model.title)
                    clipBoardCopyConfirmation.text = model.title
                }

                Layout.fillHeight: true
            }
        }
    }
}
