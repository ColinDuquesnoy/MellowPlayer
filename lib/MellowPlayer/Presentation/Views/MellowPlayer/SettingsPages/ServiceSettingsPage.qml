import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."


Item {
    clip: true

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView {
                id: listView

                anchors.fill: parent
                anchors.rightMargin: 16
                clip: true
                delegate: ServiceSettingDelegate {
                    width: listView.width;
                }
                model: _streamingServices.allServices
                spacing: 0
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
