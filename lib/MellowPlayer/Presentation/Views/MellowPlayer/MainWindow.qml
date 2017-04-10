import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import MellowPlayer 3.0

ApplicationWindow {
    id: mainWindow

    property QtObject applicationRoot: ApplicationRoot { }

    title: streamingServices.currentService !== null ? streamingServices.currentService.name : ""
    minimumWidth: 1280
    minimumHeight: 720

    Material.accent: style.accent
    Material.background: style.background
    Material.foreground: style.foreground
    Material.primary: style.primary
    Material.theme: style.theme == "light" ? Material.Light : Material.Dark

    overlay.modal: Rectangle {
        color: "#Af" + style.primary.replace("#", "")
    }

    overlay.modeless: Rectangle {
        color: "#2f" + style.primary.replace("#", "")
    }

    MainPage { anchors.fill: parent }

    ListeningHistoryDrawer { id: listeningHistoryDrawer }

    Drawer {
        id: settingsDrawer

        edge: Qt.RightEdge
        dragMargin: 0
        height: mainWindow.height; width: mainWindow.width

        Page {
            anchors.fill: parent
            header: ToolBar {
                id: toolBar
                Material.primary: style.primary
                Material.foreground: style.primaryForeground
                Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light

                RowLayout {
                    anchors.fill: parent

                    ToolButton {
                        id: btBack
                        Layout.fillHeight: true
                        text: MaterialIcons.icon_exit_to_app
                        font { family: MaterialIcons.family; pixelSize: 22 }
                        hoverEnabled: true

                        onClicked: settingsDrawer.close()

                        Tooltip {
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

                        Tooltip {
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
                    Layout.maximumWidth: 256
                    Layout.minimumWidth: 256
                    Material.elevation: 8
                    padding: 0
                    Material.background: style.secondary
                    Material.foreground: style.secondaryForeground

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
                                title: "Shortcuts"
                                icon:  "\ue312"
                            }

                            ListElement {
                                title: "Notifications"
                                icon:  "\ue7f4"
                            }

                            ListElement {
                                title: "Plugins"
                                icon:  "\ue87b"
                            }

                            ListElement {
                                title: "Cache"
                                icon:  "\ue16c"
                            }
                        }

                        Component {
                            id: settingsPageDelegate

                            Rectangle {
                                property double colorFactor: style.getColorScaleFactor(style.secondary);
                                color: settingsPageList.currentIndex == index ||  mouseArea.containsMouse ? Qt.darker(style.secondary, colorFactor) : style.secondary
                                width: parent.width
                                height: 60

                                Rectangle {
                                    anchors.top: parent.top
                                    anchors.left: parent.left
                                    anchors.bottom: parent.bottom

                                    width: 3
                                    color: settingsPageList.currentIndex == index ? style.accent : "transparent"
                                }

                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 20
                                    spacing: 10

                                    Label {
                                        text: icon
                                        font.family: MaterialIcons.family
                                        font.pixelSize: 22
                                    }

                                    Label {
                                        verticalAlignment: "AlignVCenter"
                                        text: title
                                        font.pixelSize: 20
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

                        CheckBox {
                            text: "General"
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        id: shortcutsSettingsPage

                        Switch {
                            text: "Shortcuts"
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        id: notificationsSettingsPage

                        TextField {
                            text: "Notifications"
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        id: pluginsSettingsPage

                        Switch {
                            text: "Plugins"
                            anchors.centerIn: parent
                        }
                    }


                    Item {
                        id: cacheSettingsPage

                        Switch {
                            text: "Cache"
                            anchors.centerIn: parent
                        }
                    }
                }
            }
        }
    }
}
