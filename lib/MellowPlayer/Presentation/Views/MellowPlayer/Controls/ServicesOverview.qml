import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

Item {
    id: overview

    width: parent.width
    height: parent.height

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50

        Label {
            Layout.fillWidth: true
            text: "Which service would you like to listen to ?"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 50

            ScrollBar.vertical.policy: ScrollBar.vertical.size != 1 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

            GridView {
                id: servicesGridView
                anchors.centerIn: parent
                focus: true
                width: {
                    if (mainWindow.width <= 1680 )
                        return 0.80 * mainWindow.width;
                    else if( mainWindow.width < 1920)
                        return 0.70 * mainWindow.width;
                    else
                        return 0.60 * mainWindow.width;
                }
                height: parent.height
                clip: true

                cellWidth: servicesGridView.width / 3
                cellHeight: cellWidth / 16 * 9
                model: streamingServices.model
                delegate: ServiceOverviewDelegate {}
            }
        }
    }
}

