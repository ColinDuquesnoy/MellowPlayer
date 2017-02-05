import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import "qrc:/MellowPlayer/Presentation"
import "MainView"

ApplicationWindow {
    id: mainWindow
    title: "MellowPlayer"
    minimumWidth: 1280
    minimumHeight: 720

    StackView {
        id: viewStack
        anchors.fill: parent
        initialItem: mainPageComponent

    }

    Component {
        id: mainPageComponent

        MainPage {

        }
    }

    Component {
        id: settingsPageComponent

        Page {
            header: ToolBar {
                Layout.fillWidth: true
                Material.primary: Material.background

                RowLayout {
                    anchors.fill: parent

                    ToolButton {
                        Layout.fillHeight: true
                        text: MaterialIcons.icon_arrow_back
                        font { family: MaterialIcons.family; pixelSize: 22 }
                        hoverEnabled: true

                        onClicked: viewStack.pop()
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "Settings"
                }
            }

            RowLayout {
                anchors.fill: parent

                Pane {
                    Layout.fillHeight: true
                    Layout.maximumWidth: 400
                    Layout.minimumWidth: 400
                    Material.elevation: 8
                    padding: 0


                    ListView {
                        id: settingsPageList
                        anchors.fill: parent

                        model: settingsPagesModel
                        delegate: settingsPageDelegate

                        ListModel {
                            id: settingsPagesModel

                            ListElement {
                                title: "General"
                                icon:  "\ue8b8"
                            }

                            ListElement {
                                title: "Notifications"
                                icon:  "\ue7f4"
                            }

                            ListElement {
                                title: "Plugins"
                                icon:  "\ue87b"
                            }
                        }

                        Component {
                            id: settingsPageDelegate

                            Rectangle {
                                color: mouseArea.containsMouse ? Qt.lighter(Material.background, 1.5) : settingsPageList.currentIndex == index  ?  Qt.lighter(Material.background, 1.4) :  Material.background
                                width: parent.width
                                height: 90

                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 20

                                    Label {
                                        Layout.fillWidth: true
                                        verticalAlignment: "AlignVCenter"
                                        text: icon
                                        font.family: MaterialIcons.family
                                        font.pixelSize: 26
                                    }

                                    Label {
                                        Layout.fillWidth: true
                                        verticalAlignment: "AlignVCenter"
                                        text: title
                                        font.pixelSize: 26
                                    }
                                }

                                MouseArea {
                                    id: mouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: containsMouse && settingsPageList.currentIndex != index ? "PointingHandCursor" : "ArrowCursor"

                                    onClicked: settingsPageList.currentIndex = index
                                }
                            }
                        }
                    }
                }

                StackLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    currentIndex: settingsPageList.currentIndex

                    Item {
                        id: generalSettingsPage

                        Label {
                            text: "General"
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        id: notificationsSettingsPage

                        Label {
                            text: "Notifications"
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        id: pluginsSettingsPage

                        Label {
                            text: "Plugins"
                            anchors.centerIn: parent
                        }
                    }
                }
            }
        }
    }
}
