import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

ListView {
    id: listView

    property var collapsedSections: { return {
            "Today": false,
            "Yesterday": false,
            "Last week": false,
            "Last month": false,
            "Last year": false,
            "Years ago": false
        }
    }
    property bool filtersEnabled
    property real transitionDuration: 200
    property real noDuration: 1

    signal sectionCollapsedChanged(var sectionName, var sectionIsCollapsed)

    clip: true
    spacing: 0
    model: listeningHistory.model
    delegate: ListeningHistoryEntryDelegate { width: listView.width; }
    section.criteria: ViewSection.FullString
    section.delegate: ListeningHistorySectionDelegate { width: listView.width; }
    section.property: filtersEnabled ? "dateCategory" : ""

    add: Transition {
        id: addTrans

        SequentialAnimation {
            NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
            PauseAnimation { duration: filtersEnabled ? listView.transitionDuration / 2 : listView.noDuration }
            NumberAnimation { properties: "x"; duration: filtersEnabled ? listView.transitionDuration : listView.noDuration ; from: 950; to: 0 }
        }
    }
    addDisplaced: Transition {
        id: addDispTrans

        NumberAnimation { properties: "x, y"; duration: filtersEnabled ? listView.transitionDuration : listView.noDuration }
    }

    remove: Transition {
        id: rmTrans

        NumberAnimation { properties: "x"; duration: filtersEnabled ? listView.transitionDuration : listView.noDuration ; from: 0; to: 950 }
    }
    removeDisplaced: Transition {
        id: rmDispTrans

        SequentialAnimation {
            PauseAnimation { duration: filtersEnabled ? listView.transitionDuration / 2 : listView.noDuration }
            NumberAnimation { properties: "x, y"; duration: filtersEnabled ? listView.transitionDuration : listView.noDuration }
        }
    }

    ScrollBar.vertical: ScrollBar {
        id: scrollBar

        parent: listView.parent
        anchors { top: listView.top; left: listView.right; bottom: listView.bottom; margins: 2 }
        hoverEnabled: true

        Timer {
            interval: 1
            repeat: Animation.Infinite
            running: true
            onTriggered: scrollBar.active = true;
        }
    }
}


