import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Frame {
    id: root

    property string section: ListView.section

    background: Rectangle {
        color: "transparent"
        visible: index != listView.count - 1

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: style.isDark(style.background) ? Qt.lighter(style.background) : Qt.darker(style.background, 1.1)
            height: 1
        }
    }
    clip: true
    hoverEnabled: true
    onHoveredChanged: {
        if (hovered) {
            delayTimer.start();
        }
        else {
            delayTimer.stop();
            stackLayout.currentIndex = 0
        }
    }

    Material.background: Qt.darker(style.background, 1.1)


    Connections {
        target: listView
        onSectionCollapsedChanged: {
            if (sectionName === model.dateCategory)
                state = sectionIsCollapsed ? "collapsed" : "visible";
        }
    }

    Timer {
        id: delayTimer
        interval: 250
        onTriggered: stackLayout.currentIndex = 1
    }


    RowLayout {
        anchors.fill: parent
        spacing: 8
        visible: root.state == "visible"

        Image {
            source: model.artUrl
            visible: root.state == "visible"

            Layout.preferredHeight: 48
            Layout.preferredWidth: 48
        }

        Label {
            text: "<b>" + model.title + "</b><br><i>by " + model.artist + "<br>on " + model.service + "</i>"
            visible: root.state == "visible"

            Layout.fillHeight: true
        }

        Item {
            Layout.fillWidth: true
        }

        StackLayout {
            id: stackLayout

            Label {
                anchors.fill: parent
                text: {
                    if (model.dateCategory === qsTr("Today") || model.dateCategory === qsTr("Yesterday"))
                        return model.time
                    else
                        return model.date + "\n" + model.time
                }
                verticalAlignment: "AlignVCenter"
                horizontalAlignment:"AlignRight"
                visible: root.state == "visible"
            }

            RowLayout {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                ToolButton {
                    id: btCopy
                    hoverEnabled: true
                    text: MaterialIcons.MaterialIcons.icon_content_copy
                    font { family: MaterialIcons.family; pixelSize: 16 }
                    Layout.fillHeight: true
                }

                ToolButton {
                    id: btPlay
                    hoverEnabled: true
                    text: MaterialIcons.MaterialIcons.icon_play_arrow
                    font { family: MaterialIcons.family; pixelSize: 16 }
                    Layout.fillHeight: true
                }

                ToolButton {
                    id: btClose
                    hoverEnabled: true
                    text: MaterialIcons.MaterialIcons.icon_close
                    font { family: MaterialIcons.family; pixelSize: 16 }
                    Layout.fillHeight: true
                }
            }
        }
    }

    state: "visible"
    states: [
        State {
            name: "visible"

            PropertyChanges {
                target: root
                visible: true
                height: implicitHeight
            }
        },
        State {
            name: "collapsed"

            PropertyChanges {
                target: root
                visible: false
                height: 0
            }
        }
    ]

    Component.onCompleted: {
        var collapsed = listView.collapsedSections[model.dateCategory];
        var isVisible = collapsed === undefined || !collapsed;
        if (!isVisible)
            state = "collapsed";
        else
            state = "visible";
    }
}
