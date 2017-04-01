import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Pane {
    id: root
    Material.elevation: 4
    Material.background: Qt.darker(style.background, 1.1)
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

    Timer {
        id: delayTimer
        interval: 600
        onTriggered: stackLayout.currentIndex = 1
    }


    RowLayout {
        anchors.fill: parent
        spacing: 8

        Image {
            source: model.object.artUrl

            Layout.preferredHeight: 48
            Layout.preferredWidth: 48
        }

        Label {
            Layout.fillHeight: true
            text: "<b>" + model.object.title + "</b><br><i>by " + model.object.artist + "<br>on " + model.object.service + "</i>"
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
                    var date = new Date();
                    var dateString = date.toISOString().split('T')[0]
                    if (model.object.date === dateString)
                        return model.object.time
                    else
                        return model.object.date + "\n" + model.object.time
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
