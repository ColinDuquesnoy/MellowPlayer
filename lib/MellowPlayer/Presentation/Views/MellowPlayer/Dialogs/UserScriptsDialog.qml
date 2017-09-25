import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QtQuick.Dialogs 1.2 as NativeDialogs

import "."
import ".."
import "../Controls"

Dialog {
    id: root

    property var viewModel: null
    property var serviceName

    modal: true
    title: serviceName + qsTr(" - User Scripts")
    padding: 0
    spacing: 0

    header: ToolBar {
        padding: 0

        Material.background: _theme.primary
        Material.foreground: _theme.primaryForeground
        Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            spacing: 0

            IconToolButton {
                icon: MaterialIcons.icon_add
                iconSize: 24
                tooltip: qsTr("Add user script")

                onClicked: fileDialog.open()
            }

            Item {
                Layout.fillWidth: true
            }

            IconToolButton {
                icon: MaterialIcons.icon_done
                iconSize: 24
                tooltip: qsTr("Done")

                onClicked: root.accept()
            }
        }

        Label {
            font.bold: true
            text: title
            anchors.centerIn: parent
        }
    }

    StackLayout {
        anchors { fill: parent; margins: 0 }
        currentIndex: viewModel !== null && viewModel.hasScripts ? 1 : 0

        Pane {
            anchors.centerIn: parent

            ColumnLayout {
                anchors.fill: parent
                spacing: 20

                Item {
                    Layout.fillHeight: true
                }

                Label {
                    text: MaterialIcons.icon_code
                    font.pixelSize: 64
                    font.family: MaterialIcons.family
                    color: Material.accent

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("No user script found")
                    font.bold: true
                    font.pixelSize: 20

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Add user script")
                    highlighted: true
                    hoverEnabled: true
                    onClicked: fileDialog.open()

                    Tooltip {
                        text: qsTr("Click to add a user script")
                    }

                    Layout.alignment: Qt.AlignCenter
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }

        ScrollView {
            id: scrollView
            anchors.fill: parent

            ListView {
                id: listView

                anchors { fill: parent; rightMargin: parent.ScrollBar.vertical.size != 1 ? 16 : 0 }
                model: viewModel !== null ? viewModel.model : null
                spacing: 0
                clip: true

                remove: Transition {
                    NumberAnimation { property: "x"; to: root.width; duration: 1 ; easing.type: Easing.InOutQuad }
                }
                removeDisplaced: Transition {
                    NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
                }

                delegate: ItemDelegate {
                    id: delegate

                    width: listView.width; height: 72
                    hoverEnabled: true

                    ListView.onRemove: SequentialAnimation {
                        PropertyAction { target: delegate; property: "ListView.delayRemove"; value: true }
                        NumberAnimation { target: delegate; property: "x"; to: root.width; duration: 200 ; easing.type: Easing.InOutQuad }
                        PropertyAction { target: delegate; property: "ListView.delayRemove"; value: false }
                    }

                    RowLayout {
                        id: contentLayout

                        anchors {
                            left: parent.left
                            right: parent.right
                            verticalCenter: parent.verticalCenter
                            leftMargin: parent.leftPadding
                            rightMargin: parent.rightPadding
                            topMargin: parent.topPadding
                            bottomMargin: parent.bottomPadding
                        }
                        spacing: 16

                        Label {
                            text: MaterialIcons.icon_code
                            font.pixelSize: 22
                            font.family: MaterialIcons.family

                            Material.foreground: _theme.accent
                        }

                        Label {
                            text: model.name
                            font.bold: true
                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        IconToolButton {
                            icon: MaterialIcons.icon_delete
                            iconSize: 22
                            tooltip: qsTr("Remove script")

                            onClicked: {
                                messageBoxConfirmDelete.message = qsTr('Are you sure you want to remove user script ') + model.name + '?'
                                messageBoxConfirmDelete.closed.connect(onActivated);
                                messageBoxConfirmDelete.open()
                            }

                            function onActivated() {
                                messageBoxConfirmDelete.closed.disconnect(onActivated);
                                if (messageBoxConfirmDelete.dialogResult === messageBoxConfirmDelete.dialogAccepted)
                                    viewModel.remove(model.name)
                            }
                        }
                    }

                    Rectangle {
                        color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
                        height: 1
                        visible: model.index != (delegate.ListView.view.count - 1)

                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                }
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmDelete

        title: qsTr("Confirm remove user script")

        standardButtons: Dialog.Yes | Dialog.No
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
    }

    NativeDialogs.FileDialog {
        id: fileDialog

        nameFilters: [ qsTr("Javascript files") + " (*.js)" ]
        title: qsTr("Choose a user script")

        onAccepted: {
            viewModel.add(viewModel.generateUniqueName(fileUrl), fileUrl)
        }
    }
}
