import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."
import "../Dialogs"

ItemDelegate {
    id: root

    function enterEditMode() {
        stack.currentIndex = 1
        textField.forceActiveFocus()
    }

    padding: 0
    hoverEnabled: true
    onClicked: switchEnabled.toggle()

    Material.elevation: 2

    width: layout.implicitWidth
    height: layout.implicitHeight

    ColumnLayout {
        id: layout

        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 8
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            spacing: 16

            Image {
                antialiasing: true
                mipmap: true
                smooth: true
                source: model.logo

                Layout.preferredHeight: 64
                Layout.preferredWidth: 64
                Layout.alignment: Qt.AlignVCenter
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter

                Label {
                    font.bold: true
                    font.pixelSize: 20
                    text: model.name

                    Layout.alignment: Qt.AlignVCenter
                }

                RowLayout {
                    spacing: 0

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Material.accent: _theme.accent === "#ffc107" ? _theme.primary : _theme.accent

                    Label {
                        font.italic: true
                        font.pixelSize: 12
                        text: qsTr("Version ") + model.version + qsTr(" by ")
                    }

                    Link {
                        font.italic: true
                        font.pixelSize: 12
                        name: model.authorName
                        url: model.authorWebsite
                    }

                    Item {
                        Layout.fillWidth: true
                    }
                }

                TextField {
                    id: textField

                    selectByMouse: true
                    text: model.url
                    padding: 0

                    onEditingFinished: model.url = text

                    Layout.preferredWidth: 512
                }
            }

            ColumnLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Switch {
                    id: switchEnabled
                    checked: model.isEnabled
                    onCheckedChanged: {
                        model.isEnabled = checked;
                        _streamingServices.enabledServices.update()
                    }

                    Layout.alignment: Qt.AlignRight
                }

                Button {
                    id: userScriptsButton

                    flat: true
                    highlighted: true
                    text: qsTr("User scripts")

                    onClicked: {
                        userScriptsDialog.serviceName = model.name;
                        userScriptsDialog.viewModel = model.userScripts;
                        userScriptsDialog.open();
                    }
                }
            }
        }

        Rectangle {
            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
            height: 1
            visible: model.index != (root.ListView.view.count - 1)

            Layout.fillWidth: true
        }
    }
}

