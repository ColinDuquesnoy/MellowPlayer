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

    Page {
        anchors.fill: parent
        header: ToolBar {
            id: toolBarListeningHistoru
            Material.primary: style.primary
            Material.foreground: style.primaryForeground
            Material.elevation: 0

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

                ToolButton {
                    id: btShowFilters
                    checkable: true
                    checked: false
                    text: MaterialIcons.icon_filter_list
                    font { family: MaterialIcons.family; pixelSize: 22 }
                    Material.accent: style.accent == style.primary ? style.primaryForeground : style.accent

                    onCheckedChanged: {
                        if (checked)
                            flowFilter.state = "open"
                        else
                            flowFilter.state = "closed"
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
            anchors.margins: 12

            ColumnLayout {
                anchors.fill: parent
                spacing: 8

                Pane {
                    id: searchPane
                    padding: 0
                    Layout.fillWidth: true
                    Layout.preferredHeight: height
                    Layout.minimumHeight: 0

                    TextField {
                        id: searchField
                        anchors.fill: parent
                        placeholderText: "Search"

                        onVisibleChanged: {
                            focus = true
                            forceActiveFocus();
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
                                visible: false
                                focus: false
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
                                visible: true
                                focus: true
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

                ListeningHistoryListView {
                    id: listeningHistoryListView

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Flow {
                    id: flowFilter

                    spacing: 3
                    Layout.fillWidth: true
                    Layout.preferredHeight: height

                    Repeater {
                        model: streamingServices.model

                        Button {
                            flat: true
                            checkable: true; checked: true
                            text: model.object.name
                        }
                    }

                    state: "closed"
                    states: [
                        State {
                            name: "closed"

                            PropertyChanges {
                                target: flowFilter
                                height: 0
                            }
                        },
                        State {
                            name: "open"

                            PropertyChanges {
                                target: flowFilter
                                height: flowFilter.implicitHeight
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
            }
        }
    } 
}
