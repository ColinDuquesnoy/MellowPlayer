import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQml 2.2

import MellowPlayer 3.0
import ".."

Popup {
    id: popup

    padding: 20
    modal: true
    height: 460
    width: height

    onVisibleChanged: if (!visible) btCredits.checked = false

    Material.accent: _style.accent === "#ffc107" ? _style.primary : _style.accent

    ColumnLayout {
        anchors.fill: parent
        spacing: 8

        Item {
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent
                spacing: 12

                Image {
                    source: "qrc:/MellowPlayer/Presentation/Resources/icons/mellowplayer.png"
                    fillMode: Image.PreserveAspectFit

                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredHeight: 128
                }

                Label {
                    font.bold: true
                    font.pixelSize: 32
                    text: "MellowPlayer"

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    font.pixelSize: 16
                    text: Qt.application.version

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    font.pixelSize: 16
                    text: "Cloud music integration for your desktop"



                    Layout.alignment: Qt.AlignCenter
                }

                Link {
                    name: 'Website'
                    url: 'https://colinduquesnoy.github.io/MellowPlayer'

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    text: "Copyright 2014-2017 Colin Duquesnoy"

                    Layout.alignment: Qt.AlignCenter
                }

                ColumnLayout {
                    spacing: 0

                    Layout.alignment: Qt.AlignCenter

                    Label {
                        font.pixelSize: 12
                        text: 'This program comes with absolutely no warranty.'

                        Layout.alignment: Qt.AlignCenter
                    }

                    Label {
                        font.pixelSize: 12
                        onLinkActivated: Qt.openUrlExternally(link)
                        text: 'See the <a href="https://www.gnu.org/licenses/old-licenses/lgpl-2.1">GNU Lesser General Public License</a>,'

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.NoButton
                            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                        }

                        Layout.alignment: Qt.AlignCenter
                    }

                    Label {
                        font.pixelSize: 12
                        text: 'version 2.1 or later for details.'

                        Layout.alignment: Qt.AlignCenter
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }

            Item {
                id: creditsPane

                readonly property int yPos: parent.height

                height: 150; width: parent.width

                Pane {
                    anchors.fill: parent
                    anchors.topMargin: 2
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    anchors.bottomMargin: 0  // hide bottom elevation

                    padding: 16

                    Material.elevation: 8

                    ColumnLayout {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        spacing: 9

                        RowLayout {
                            spacing: 9

                            ColumnLayout {
                                Label {
                                    text: "Created by"
                                }

                                Item { Layout.fillHeight: true }
                            }

                            ColumnLayout {
                                Link {
                                    name: '@ColinDuquesnoy'
                                    url: "https://github.com/ColinDuquesnoy"
                                }

                                Item { Layout.fillHeight: true }
                            }
                        }

                        RowLayout {
                            spacing: 9

                            ColumnLayout {
                                Label {
                                    text: "Artwork by"
                                }

                                Item { Layout.fillHeight: true }
                            }

                            ColumnLayout {
                                Link {
                                    name: '@CelineThiry'
                                    url: "https://github.com/CelineThiry"
                                }

                                Item { Layout.fillHeight: true }
                            }
                        }

                        RowLayout {
                            spacing: 9

                            ColumnLayout {
                                Label {
                                    text: "Contributors"
                                }

                                Item { Layout.fillHeight: true }
                            }

                            ColumnLayout {
                                Link {
                                    name: '@ConorIA'
                                    url: "https://github.com/ConorIA"
                                }

                                Item { Layout.fillHeight: true }
                            }
                        }
                    }
                }

                state: btCredits.checked && popup.visible ? "open" : "closed"
                states: [
                    State {
                        name: "open"

                        PropertyChanges {
                            target: creditsPane

                            y: creditsPane.yPos - creditsPane.height
                        }
                    },
                    State {
                        name: "closed"

                        PropertyChanges {
                            target: creditsPane

                            y: creditsPane.yPos
                        }
                    }
                ]

                transitions: Transition {
                    from: "open"; to: "closed"
                    reversible: true

                    PropertyAnimation {
                        properties: "y"
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                id: btCredits
                checkable: true
                checked: false
                highlighted: checked
                flat: true
                text: "Credits"
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                flat: true
                highlighted: true
                onClicked: popup.close()
                text: "Close"
            }
        }
    }
}
