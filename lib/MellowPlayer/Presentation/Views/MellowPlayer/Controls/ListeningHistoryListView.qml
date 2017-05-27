import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Flickable {
    id: listView

    property bool filtersEnabled
    property real transitionDuration: 200
    property int count: listWithSectionsAndAnims.count
    readonly property int pageSourceList: 0
    readonly property int pageFilteredList: 1
    readonly property int pageNoMatchFound: 2

    clip: true
    contentHeight: stack.currentIndex == 0 ? listWithSectionsAndAnims.contentHeight : listViewSimple.contentHeight
    contentWidth: stack.currentIndex == 0 ? listWithSectionsAndAnims.contentWidth : listViewSimple.contentWidth

    StackLayout {
        id: stack

        anchors.fill: parent
        currentIndex: filtersEnabled ? listViewSimple.count  == 0 ? pageNoMatchFound : pageFilteredList : pageSourceList

        ListView {
            id: listWithSectionsAndAnims

            anchors.fill: parent
            cacheBuffer: 500
            clip: true
            model: listeningHistory.sourceModel
            delegate: ListeningHistoryEntryDelegate { width: listView.width; }
            section.criteria: ViewSection.FullString
            section.delegate: ListeningHistorySectionDelegate { width: listView.width; }
            section.property: "dateCategory"
            section.labelPositioning: ViewSection.CurrentLabelAtStart | ViewSection.NextLabelAtEnd | ViewSection.InlineLabels

            add: Transition {
                SequentialAnimation {
                    NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
                    PauseAnimation { duration: listView.transitionDuration / 2 }
                    NumberAnimation { properties: "x"; duration: listView.transitionDuration ; from: 950; to: 0; easing.type: Easing.InOutQuad }
                }
            }
            addDisplaced: Transition {
                NumberAnimation { properties: "x,y"; duration: listView.transitionDuration; easing.type: Easing.InOutQuad }
            }
        }

        ListView {
            id: listViewSimple

            anchors.fill: parent
            clip: true
            model: listeningHistory.filteredModel
            delegate: ListeningHistoryEntryDelegate { width: listView.width; }
        }

        Pane {
            anchors.fill: parent

            ColumnLayout {
                anchors.fill: parent
                spacing: 20

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Label {
                    text: MaterialIcons.icon_block
                    font.pixelSize: 48
                    font.family: MaterialIcons.family
                    color: Material.color(Material.Red)

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Label {
                    text: "No match found"
                    font.bold: true
                    font.pixelSize: 20

                    horizontalAlignment: "AlignHCenter"

                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }

    ScrollBar.vertical: DesktopScrollBar {
        anchors { top: listView.top; left: listView.right; bottom: listView.bottom }
        parent: listView.parent
        visible: size != 1
    }
}

