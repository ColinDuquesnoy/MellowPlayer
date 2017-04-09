import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import MellowPlayer 3.0

Drawer {
    id: listeningHistoryDrawer
    dragMargin: 0
    edge: Qt.RightEdge
    height: mainWindow.height; width: 450
    clip: true

    Page {
        anchors.fill: parent
        header: ToolBar {
            id: toolBarListeningHistoru
            Material.primary: style.primary
            Material.foreground: style.primaryForeground
            Material.elevation: 0
            Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light

            RowLayout {
                anchors.fill: parent

                ToolButton {
                    id: btBackFromListeningHistory
                    Layout.fillHeight: true
                    text: MaterialIcons.icon_exit_to_app
                    font { family: MaterialIcons.family; pixelSize: 22 }
                    hoverEnabled: true

                    onClicked: listeningHistoryDrawer.close()

                    Tooltip {
                        y: toolBarListeningHistoru.implicitHeight
                        text: qsTr("Back")
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: btSearch
                    checkable: true
                    checked: false
                    text: MaterialIcons.icon_search
                    font { family: MaterialIcons.family; pixelSize: 22 }
                    Material.accent: style.accent == style.primary ? style.primaryForeground : style.accent

                    onCheckedChanged: {
                        if (checked)
                            searchPane.state = "open"
                        else
                            searchPane.state = "closed"
                    }
                }
            }

            Label {
                anchors.centerIn: parent
                text: "Listening history"
            }
        }

        Item {
            anchors.fill: parent

            ColumnLayout {
                anchors.fill: parent
                spacing: 8

                Pane {
                    id: searchPane

                    Layout.fillWidth: true
                    Layout.preferredHeight: height
                    Layout.minimumHeight: 0
                    Material.elevation: 2

                    ColumnLayout {
                        anchors.fill: parent

                        TextField {
                            id: searchField

                            placeholderText: qsTr("Search")
                            onEnabledChanged: {
                                if (enabled) {
                                    focus = true;
                                    forceActiveFocus();
                                }
                            }
                            Layout.fillWidth: true
                        }

                        Flow {
                            id: filters
                            spacing: 3

                            width: parent.width

                            Repeater {
                                z: 1
                                model: streamingServices.model

                                Button {
                                    flat: true
                                    checkable: true; checked: true
                                    text: model.name
                                }
                            }
                        }
                    }

                    state: "closed"
                    states: [
                        State {
                            name: "closed"

                            PropertyChanges {
                                target: searchPane
                                height: 0
                            }

                            PropertyChanges {
                                target: searchField
                                enabled: false
                            }
                        },
                        State {
                            name: "open"

                            PropertyChanges {
                                target: searchPane
                                height: searchPane.implicitHeight
                            }

                            PropertyChanges {
                                target: searchField
                                enabled: true

                            }
                        }
                    ]

                    transitions: Transition {
                        from: "*"
                        to: "*"

                        PropertyAnimation {
                            properties: "height"
                            easing.type: "InOutCubic"
                        }
                    }
                }
                Pane {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    ListeningHistoryListView {
                        id: listeningHistoryListView

                        anchors.fill: parent
                    }
                }

//                Rectangle {
//                    color: style.primary

//                    Layout.fillWidth: true
//                    Layout.preferredHeight: filters.height
//                    height: filters.height
//                }
            }
        }
    } 
}
