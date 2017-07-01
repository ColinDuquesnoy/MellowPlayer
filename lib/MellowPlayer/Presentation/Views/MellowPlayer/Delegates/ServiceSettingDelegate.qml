import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

Pane {
    padding: 2

    Pane {
        padding: 8
        anchors.fill: parent
        Material.elevation: 2

        RowLayout {
            anchors.fill: parent

            Pane {
                padding: 4
                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout {
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

                            Material.accent: style.accent === "#ffc107" ? style.primary : style.accent

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
                                    id: labelEditUrl
                                    text: MaterialIcons.icon_edit
                                    font.family: MaterialIcons.family
                                    font.pixelSize: 20
                                    visible: mouseAreaUrl.containsMouse
                                }

                                Label {
                                    font.italic: true
                                    text: model.url

                                    MouseArea {
                                        id: mouseAreaUrl
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: containsMouse ? "PointingHandCursor" : "ArrowCursor"
                                        onClicked: stack.currentIndex = 1
                                    }
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
    }
}

