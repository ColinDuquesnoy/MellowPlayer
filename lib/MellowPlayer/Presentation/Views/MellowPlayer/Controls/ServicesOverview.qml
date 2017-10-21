import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQml.Models 2.1

import MellowPlayer 3.0
import ".."

Item {
    id: root

    property int mainWindowWidth
    property int mainWindowHeight
    property Item transitionItem
    property var webViews

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50

        Label {
            Layout.fillWidth: true
            text: qsTr("Which service would you like to listen to ?")
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
        }

        ScrollView {
            id: scrollView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 50

            ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

            GridView {
                id: gridView

                property bool dragActive: false

                anchors.fill: parent
                focus: true
                width: {
                    if (mainWindowWidth <= 1680 )
                        return 0.80 * mainWindowWidth;
                    else if( mainWindowWidth < 1920)
                        return 0.70 * mainWindowWidth;
                    else
                        return 0.60 * mainWindowWidth;
                }
                height: parent.height
                clip: true

                cellWidth: 340
                cellHeight: 192

                model: DelegateModel {
                    id: visualModel

                    model: _streamingServices.enabledServices

                    delegate: Item {
                        id: delegateRoot

                        property int visualIndex: DelegateModel.itemsIndex
                        property var service: model.qtObject

                        width: gridView.cellWidth; height: gridView.cellHeight

                        ServiceOverviewDelegate {
                            id: item

                            anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
                            height: gridView.cellHeight - 4; width: gridView.cellWidth - 4
                            hovered: mouseArea.containsMouse
                            index: delegateRoot.visualIndex
                            transitionItem: root.transitionItem
                            webView: root.webViews[_streamingServices.webViewIndex(model.name)]

                            Drag.active: mouseArea.drag.active
                            Drag.source: delegateRoot
                            Drag.hotSpot.x: gridView.cellWidth / 2
                            Drag.hotSpot.y: gridView.cellHeight / 2
                            Drag.onActiveChanged: gridView.dragActive = Drag.active

                            states: State {
                                when: item.Drag.active

                                ParentChange {
                                    target: item
                                    parent: root
                                }

                                PropertyChanges {
                                    target: item
                                    z: 1
                                }

                                AnchorChanges {
                                    target: item;
                                    anchors.horizontalCenter: undefined;
                                    anchors.verticalCenter: undefined
                                }
                            }
                        }

                        MouseArea {
                            id: mouseArea

                            anchors.fill: parent
                            drag.target: item
                            hoverEnabled: true

                            onClicked: item.activate()
                            onReleased: item.Drag.drop()
                        }

                        DropArea {
                            anchors { fill: parent; margins: 15 }

                            onEntered: visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex)
                        }

                        RoundButton {
                            id: btOff

                            anchors { top: parent.top; right: parent.right; margins: 2 }
                            hoverEnabled: true
                            visible: !item.Drag.active && model.qtObject.player.isRunning
                            padding: 0

                            Material.background: Material.color(Material.Red)
                            Material.foreground: "white"

                            text: MaterialIcons.icon_close
                            font.family: MaterialIcons.family
                            font.bold: true
                            font.pixelSize: 22

                            onClicked: item.webView.stop()
                        }
                    }
                }

                displaced: Transition {
                    NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
                }
            }
        }
    }

    Pane {
        id: removedLabel

        property var service: null

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 16
        visible: false

        onServiceChanged: {
            if (service != null) {
                visible = true
                timer.running = true;
                timer.restart();
            }
        }

        Material.background: _theme.primary
        Material.foreground: _theme.primaryForeground
        Material.elevation: 4

        RowLayout {
            anchors.centerIn: parent

            Label {
                text: removedLabel.service !== null ? removedLabel.service.name + qsTr(" has been removed from overview.") : ""
                font.bold: true
                font.pixelSize: 16
            }

            Label {
                text: '<a href="https://action/undo">' + qsTr("UNDO") + '</a>'
                font.bold: true
                font.pixelSize: 16

                onLinkActivated: {
                    removedLabel.service.isEnabled = true
                    removedLabel.service = null;
                    removedLabel.visible = false;
                    _streamingServices.enabledServices.update()
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
            }
        }

        Timer {
            id: timer
            interval: 3000
            repeat: false
            running: false

            onTriggered: removedLabel.visible = false
        }
    }

    Label {
        id: trashLabel

        anchors { bottom: parent.bottom; right: parent.right; rightMargin: 16; bottomMargin: 16}
        text: MaterialIcons.icon_delete
        font.family: MaterialIcons.family
        font.pixelSize: 64
        opacity: trashDropArea.containsDrag ? 1 : gridView.dragActive ? 0.5 : 0
        color: trashDropArea.containsDrag ? Material.color(Material.Red) : Material.foreground
        z: 50

        DropArea {
            id: trashDropArea

            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height/ 2
            width: gridView.cellWidth
            height: gridView.cellHeight

            onDropped: {
                var position = scrollView.ScrollBar.vertical.position;
                gridView.dragActive = false;
                drag.source.service.isEnabled = false;
                _streamingServices.enabledServices.update()
                removedLabel.service = drag.source.service;
                scrollView.ScrollBar.vertical.position = position;
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }
}

