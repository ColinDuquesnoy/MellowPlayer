import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import MellowPlayer 3.0

Drawer {
    id: listeningHistoryDrawer

    property bool filtering: false

    dragMargin: 0
    edge: Qt.RightEdge
    height: mainWindow.height; width: 450
    clip: true

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor
    }

    Page {
        anchors.fill: parent
        header: ToolBar {
            id: toolBarListeningHistoru
            Material.primary: style.primary
            Material.foreground: style.primaryForeground
            Material.elevation: 4
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
                    hoverEnabled: true

                    onCheckedChanged: {
                        if (checked) {
                            listeningHistoryListView.filtersEnabled = true;
                            searchPane.state = "open"
                        }
                        else {
                            searchField.text = ""
                            filters.enabled = false;
                            searchPane.state = "closed"
                            disableListViewFiltersTimer.running = true;
                        }
                    }

                    Material.accent: style.accent == style.primary ? style.primaryForeground : style.accent

                    Tooltip {
                        text: qsTr("Search/filter")
                    }

                    Timer {
                        id: disableListViewFiltersTimer

                        interval: 200
                        onTriggered: listeningHistoryListView.filtersEnabled = false;
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

                    Connections {
                        target: listeningHistoryDrawer
                        onPositionChanged: if (position == 0) btSearch.checked = false
                    }

                    ColumnLayout {
                        anchors.fill: parent

                        TextField {
                            id: searchField

                            focus: true
                            placeholderText: qsTr("Search by title or by artist")
                            onEnabledChanged: {
                                if (enabled) {
                                    focus = true;
                                    forceActiveFocus();
                                }
                            }
                            selectByMouse: true
                            onTextChanged: listeningHistory.setSearchFilter(text)

                            Tooltip {
                                text: qsTr("Filter song by title or by artist")
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
                                    id: filter

                                    flat: true
                                    checkable: true; checked: true
                                    hoverEnabled: true
                                    text: model.name
                                    onCheckedChanged: {
                                        listeningHistory.disableService(model.name, !checked)
                                    }

                                    Tooltip {
                                        text: filter.checked ? qsTr("Click to remove songs from")  + model.name : qsTr("Click to add songs from ") + model.name
                                    }

                                    Connections {
                                        target: filters
                                        onEnabledChanged: filter.checked = true;
                                    }
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

                            PropertyChanges {
                                target: filters
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

                            PropertyChanges {
                                target: filters
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
                    padding: 0

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    StackLayout {
                        anchors.fill: parent
                        currentIndex: listeningHistoryListView.count > 0 ? 0 : 1

                        RowLayout {
                            id: listViewLayout

                            anchors.fill: parent

                            ListeningHistoryListView {
                                id: listeningHistoryListView

                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }
                        }

                        Pane {
                            ColumnLayout {
                                anchors.centerIn: parent
                                spacing: 20

                                Item {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                }

                                Label {
                                    text: MaterialIcons.icon_history
                                    font.pixelSize: 48
                                    font.family: MaterialIcons.family
                                    color: Material.accent

                                    horizontalAlignment: "AlignHCenter"

                                    Layout.fillWidth: true
                                }

                                Label {
                                    text: "Nothing in history"
                                    font.bold: true
                                    font.pixelSize: 32

                                    horizontalAlignment: "AlignHCenter"

                                    Layout.fillWidth: true
                                }

                                Label {
                                    text: "Enable listening history and the songs you \nlistened to will appear here..."

                                    horizontalAlignment: "AlignHCenter"

                                    Layout.fillWidth: true
                                }

                                Button {
                                    text: "Enable listening history"
                                    highlighted: true
                                    hoverEnabled: true

                                    Tooltip {
                                        text: qsTr("Click to enable listening history")
                                    }

                                    Layout.fillWidth: true
                                }

                                Item {
                                    Layout.fillHeight: true
                                }
                            }
                        }

                    }
                }
            }
        }
    }
}
