import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."
import "../Dialogs"

Item {
    clip: true

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Item {
                clip: true

                Layout.fillHeight: true
                Layout.fillWidth: true

                GridView {
                    id: grid

                    property int itemSpacing: 32

                    anchors.centerIn: parent
                    cellHeight: 256 + itemSpacing
                    cellWidth: 256 + itemSpacing
                    height: parent.height
                    width: Math.floor(parent.width / cellWidth) * cellWidth

                    delegate: ServiceSettingDelegate {
                        width: grid.cellWidth - grid.itemSpacing / 2;
                        height: grid.cellHeight - grid.itemSpacing / 2
                    }
                    model: _streamingServices.allServices

                    ScrollBar.vertical: scrollBar
                }
            }

            Item {
                id: scrollBarArea

                Layout.fillHeight: true
                Layout.preferredWidth: 16

                ScrollBar {
                    id: scrollBar
                    policy: size != 1 ? "AlwaysOn" : "AlwaysOff"

                    anchors.fill: parent
                }
            }
        }

        Pane {
            Layout.fillWidth: true
            Material.elevation: 2

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                }

                ToolButton {
                    highlighted: true
                    hoverEnabled: true
                    text: qsTr("Create plugin")
                    onClicked: wizardNewPlugin.open()
                }
            }
        }
    }
}
