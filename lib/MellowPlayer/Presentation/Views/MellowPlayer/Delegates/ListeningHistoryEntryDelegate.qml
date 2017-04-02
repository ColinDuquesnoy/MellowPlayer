import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Pane {
    id: root

    property string section: ListView.section

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

    Material.elevation: 4
    Material.background: Qt.darker(style.background, 1.1)

    Timer {
        id: delayTimer
        interval: 250
        onTriggered: stackLayout.currentIndex = 1
    }


    RowLayout {
        anchors.fill: parent
        spacing: 8

        Image {
            source: model.artUrl

            Layout.preferredHeight: 48
            Layout.preferredWidth: 48
        }

        Label {
            Layout.fillHeight: true
            text: "<b>" + model.title + "</b><br><i>by " + model.artist + "<br>on " + model.service + "</i>"
        }

        Item {
            Layout.fillWidth: true
        }

        StackLayout {
            id: stackLayout
            // currentIndex: root.hovered ? 1 : 0
            anchors.fill: parent

            Label {
                verticalAlignment: "AlignVCenter"
                horizontalAlignment:"AlignRight"
                anchors.fill: parent

                text: {
                    if (model.dateCategory === qsTr("Today") || model.dateCategory === qsTr("Yesterday"))
                        return model.time
                    else
                        return model.date + "\n" + model.time
                }
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
}
