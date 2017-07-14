import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

ItemDelegate {
    id: root

    function enterEditMode() {
        stack.currentIndex = 1
        textField.forceActiveFocus()
    }

    hoverEnabled: true
    padding: 0
    onClicked: enterEditMode()

    Material.elevation: 2

    contentItem: ColumnLayout {
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 16

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Material.background: "transparent"

                implicitWidth: layout.implicitWidth
                implicitHeight: layout.implicitHeight

                RowLayout {
                    id: layout
                    spacing: 16
                    anchors.fill: parent

                    Image {
                        antialiasing: true
                        mipmap: true
                        smooth: true
                        source: model.logo

                        Layout.preferredHeight: 64
                        Layout.preferredWidth: 64
                    }

                    ColumnLayout {
                        Layout.fillWidth: true

                        RowLayout {
                            spacing: 0

                            Material.accent: _theme.accent === "#ffc107" ? _theme.primary : _theme.accent

                            Label {
                                font.bold: true
                                font.pixelSize: 20
                                text: model.name
                            }

                            Item {
                                Layout.preferredWidth: 16
                            }

                            Label {
                                font.italic: true
                                font.pixelSize: 12
                                text: "Version " + model.version + " by "
                            }

                            Link {
                                font.italic: true
                                font.pixelSize: 12
                                name: model.authorName
                                url: model.authorWebsite
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        StackLayout {
                            id: stack

                            Layout.fillWidth: true

                            RowLayout {
                                anchors.fill: parent

                                Label {
                                    font.italic: true
                                    text: model.url
                                }

                                Item {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: textField.implicitHeight
                                }
                            }

                            RowLayout {
                                anchors.fill: parent

                                TextField {
                                    id: textField

                                    selectByMouse: true
                                    text: model.url

                                    onEditingFinished: save()

                                    function save() {
                                        model.url = text;
                                        stack.currentIndex = 0;
                                    }

                                    Layout.fillWidth: true
                                }

                                ToolButton {
                                    flat: true
                                    font.family: MaterialIcons.family
                                    font.pixelSize: 24
                                    text: MaterialIcons.icon_done

                                    onClicked: textField.save()
                                }

                            }
                        }
                    }
                }
            }

            ColumnLayout {
                Switch {
                    visible: false
                    Layout.alignment: Qt.AlignRight
                }

                Item {
                    Layout.fillHeight: true
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

