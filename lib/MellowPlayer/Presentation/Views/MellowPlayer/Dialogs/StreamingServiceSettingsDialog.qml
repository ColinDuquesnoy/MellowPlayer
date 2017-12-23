import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QtQuick.Dialogs 1.2 as NativeDialogs
import QtQuick.Controls 1.2 as QuickControls1

import ".."
import "../Controls"

Dialog {
    id: root

    property var service: nullService

    clip: true
    modal: true
    title: service.name
    padding: 0; spacing: 0
    onVisibleChanged: {
        if (!visible) {
            tabBar.currentIndex = 0
            service = nullService
        }
    }

    footer: RowLayout {
        Item {
            width: 12
        }

        RowLayout {
            spacing: 0

            Layout.alignment: Qt.AlignCenter
            Material.accent: _theme.accent === "#ffc107" ? _theme.primary : _theme.accent

            Label {
                font.italic: true
                font.pixelSize: 12
                text: qsTr("Version ") + service.version + qsTr(" by ")
            }

            Link {
                font.italic: true
                font.pixelSize: 12
                name: service.authorName
                url: service.authorWebsite
            }
        }

        DialogButtonBox {
            standardButtons: Dialog.Close

            onAccepted: root.accept()
            onRejected: root.reject()

            Layout.fillWidth: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 3
        spacing: 0
        clip: true

        Rectangle {
            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 1
            Layout.fillWidth: true
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            Layout.preferredHeight: tabBar.implicitHeight

            TabButton {
                text: "General"
            }

            TabButton {
                text: "User scripts"
            }

            TabButton {
                text: "Network Proxy"
            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex

            Layout.fillWidth: true
            Layout.fillHeight: true

            Item {
                id: generalPage
                anchors.fill: parent

                Pane {
                    anchors.centerIn: parent
                    padding: 0
                    width: parent.width / 2
                    height: parent.height * 0.75

                    Material.background: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background, 1.05) : Qt.darker(_theme.background, 1.05)
                    Material.elevation: 2

                    ColumnLayout {
                        spacing: 0
                        anchors.fill: parent

                        SwitchDelegate {
                            checked: service.isEnabled
                            hoverEnabled: true
                            text: "Enabled"

                            onCheckedChanged: {
                                service.isEnabled = checked;
                                _streamingServices.enabledServices.update();
                            }

                            Layout.fillWidth: true
                        }

                        Rectangle {
                            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
                            Layout.preferredHeight: 1
                            Layout.fillWidth: true
                        }

                        SwitchDelegate {
                            checked: service.notificationsEnabled
                            hoverEnabled: true
                            text: "Notifications"

                            onCheckedChanged: {
                                service.notificationsEnabled = checked
                            }

                            Layout.fillWidth: true
                        }

                        Rectangle {
                            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
                            Layout.preferredHeight: 1
                            Layout.fillWidth: true
                        }

                        ItemDelegate {
                            hoverEnabled: true

                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 16
                                anchors.rightMargin: 16
                                spacing: 12

                                Label {
                                    text: qsTr("URL: ")
                                }

                                Item {
                                    Layout.fillWidth: true
                                }

                                TextField {
                                    selectByMouse: true
                                    text: service.url

                                    Layout.preferredWidth: 320
                                }
                            }
                        }

                        Item {
                            Layout.fillHeight: true
                        }
                    }
                }
            }

            StackLayout {
                anchors.fill: parent
                currentIndex: service !== null && service.userScripts.hasScripts ? 1 : 0

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

                Item {
                    anchors.fill: parent

                    Pane {
                        id: userScriptListPane

                        padding: 0
                        anchors.centerIn: parent
                        width: parent.width / 2
                        height: parent.height * 0.75

                        Material.background: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background, 1.05) : Qt.darker(_theme.background, 1.05)
                        Material.elevation: 2

                        ScrollView {
                            id: scrollView

                            anchors.fill: parent

                            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                            ListView {
                                id: listView

                                anchors { fill: parent; rightMargin: parent.ScrollBar.vertical.size != 1 ? 16 : 0 }
                                model: service !== null ? service.userScripts.model : null
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

                                    onClicked: deleteToolButton.onClicked()
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
                                            id: deleteToolButton

                                            iconChar: MaterialIcons.icon_delete
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
                                                    service.userScripts.remove(model.name)
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

                    ToolButton {
                        anchors { top: userScriptListPane.bottom; horizontalCenter: userScriptListPane.horizontalCenter }
                        font { family: MaterialIcons.family; pixelSize: 24 }
                        flat: true
                        highlighted: true
                        hoverEnabled: true
                        text: MaterialIcons.icon_add

                        onClicked: fileDialog.open()
                    }
                }
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 20

                Item {
                    Layout.fillHeight: true
                }

                Label {
                    text: MaterialIcons.icon_build
                    font.pixelSize: 64
                    font.family: MaterialIcons.family
                    color: Material.color(Material.Orange)

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Coming soon!")
                    font.bold: true
                    font.pixelSize: 20

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }

        Rectangle {
            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 1
            Layout.fillWidth: true
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
            service.userScripts.add(service.userScripts.generateUniqueName(fileUrl), fileUrl)
        }
    }

    QtObject {
        id: nullService

        property string name: ""
        property string url: ""
        property string authorName: ""
        property string authorWebsite: ""
        property bool notificationsEnabled: true
        property bool isEnabled: true

        property QtObject userScripts: QtObject {

        }
    }
}

