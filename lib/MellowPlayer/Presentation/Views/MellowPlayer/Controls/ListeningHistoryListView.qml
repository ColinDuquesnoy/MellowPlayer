import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

ListView {
    id: listView

    property bool filtersEnabled
    property real transitionDuration: 200

    cacheBuffer: 500
    clip: true
    model: listeningHistory.model
    delegate: ListeningHistoryEntryDelegate { width: listView.width; }
    section.criteria: ViewSection.FullString
    section.delegate: ListeningHistorySectionDelegate { width: listView.width; }
    section.property: "dateCategory"
    section.labelPositioning: ViewSection.CurrentLabelAtStart | ViewSection.NextLabelAtEnd | ViewSection.InlineLabels

    add: Transition {
        enabled: !filtersEnabled

        SequentialAnimation {
            NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
            PauseAnimation { duration: listView.transitionDuration / 2 }
            NumberAnimation { properties: "x"; duration: listView.transitionDuration ; from: 950; to: 0; easing.type: Easing.InOutQuad }
        }
    }
    addDisplaced: Transition {
        enabled: !filtersEnabled

        NumberAnimation { properties: "x,y"; duration: listView.transitionDuration; easing.type: Easing.InOutQuad }
    }

    ScrollBar.vertical: DesktopScrollBar {
        anchors { top: listView.top; left: listView.right; bottom: listView.bottom }
        parent: listView.parent
    }
}
