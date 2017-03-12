import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import "qrc:/MellowPlayer/Presentation/resources"
import ".."
import "../pages"

ApplicationWindow {
    id: mainWindow

    property QtObject applicationRoot: ApplicationRoot { }

    title: streamingServices.currentService !== null ? streamingServices.currentService.name : ""
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
                id: toolBar
                Layout.fillWidth: true
                Material.primary: Material.background

                RowLayout {
                    anchors.fill: parent

                    ToolButton {
                        id: btBack
                        Layout.fillHeight: true
                        text: MaterialIcons.icon_exit_to_app
                        font { family: MaterialIcons.family; pixelSize: 22 }
                        hoverEnabled: true

                        onClicked: viewStack.pop()

                        ToolTip {
                            visible: parent.hovered
                            delay: 1000
                            timeout: 5000
                            y: toolBar.implicitHeight
                            text: qsTr("Back")
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    ToolButton {
                        Layout.fillHeight: true
                        text: MaterialIcons.icon_power_settings_new
                        font { family: MaterialIcons.family; pixelSize: 22 }
                        hoverEnabled: true

                        onClicked: Qt.quit();

                        ToolTip {
                            visible: parent.hovered
                            delay: 1000
                            timeout: 5000
                            y: toolBar.implicitHeight
                            text: qsTr("Quit the application")
                        }
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
                    Layout.maximumWidth: 450
                    Layout.minimumWidth: 450
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
                                    spacing: 10

                                    Label {
                                        text: icon
                                        font.family: MaterialIcons.family
                                        font.pixelSize: 26
                                    }

                                    Label {
                                        verticalAlignment: "AlignVCenter"
                                        text: title
                                        font.pixelSize: 26
                                    }

                                    Item { Layout.fillWidth: true; }
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

    Component.onCompleted: console.log("application font: " + font.family);
}
