import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

ScrollView {
    id: scrollView

    property alias count: listView.count

    anchors.fill: parent
    contentHeight: listView.contentHeight
    contentWidth: listView.contentWidth

    ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded

    ListView {
        id: listView

        anchors {
            fill: parent
            rightMargin: scrollView.ScrollBar.vertical.size != 1 ? 16 : 0
        }
        clip: true
        cacheBuffer: 500 * 72
        model: listeningHistory.filteredModel
        delegate: ListeningHistoryEntryDelegate { }
        section.criteria: ViewSection.FullString
        section.delegate: ListeningHistorySectionDelegate { }
        section.property: "dateCategory"
        add: Transition {
            SequentialAnimation {
                NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
                PauseAnimation { duration: 100 }
                NumberAnimation { properties: "x"; duration: 200; from: 950; to: 0; easing.type: Easing.InOutQuad }
            }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
        }
        remove: Transition {
            NumberAnimation { property: "x"; to: 950; duration: 1 ; easing.type: Easing.InOutQuad }
        }
        removeDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
        }
    }
}

