import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Page {
    header: ToolBar {
        id: toolBar

        Material.primary: style.primary
        Material.foreground: style.primaryForeground
        Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                id: btBack
                Layout.fillHeight: true
                text: MaterialIcons.icon_exit_to_app
                font { family: MaterialIcons.family; pixelSize: 22 }
                hoverEnabled: true

                onClicked: stackView.pop()

                Tooltip {
                    y: toolBar.implicitHeight
                    text: qsTr("Back")
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
            padding: 0

            Layout.fillHeight: true
            Layout.maximumWidth: 256
            Layout.minimumWidth: 256

            Material.background: style.secondary
            Material.foreground: style.secondaryForeground
            Material.elevation: 4

            ListView {
                id: settingsPageList
                anchors.fill: parent

                model: settings.categories
                delegate: settingsCategoryDelegate

                Component {
                    id: settingsCategoryDelegate

                    Rectangle {
                        property double colorFactor: style.getColorScaleFactor(style.secondary);

                        color: settingsPageList.currentIndex == index ||  mouseArea.containsMouse ? Qt.darker(style.secondary, colorFactor) : style.secondary
                        height: 60; width: parent.width


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
                                text: model.icon
                                font.family: MaterialIcons.family
                                font.pixelSize: 24
                            }

                            Label {
                                verticalAlignment: "AlignVCenter"
                                text: model.name
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
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: settings.categories

                Loader {
                    anchors.fill: parent
                    source: model.qmlComponent
                }
            }
        }
    }
}
