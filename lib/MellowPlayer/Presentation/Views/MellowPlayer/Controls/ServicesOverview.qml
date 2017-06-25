import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

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

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 50

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

                ScrollBar.vertical: DesktopScrollBar {
                    anchors { top: servicesGridView.top; left: servicesGridView.right; bottom: servicesGridView.bottom }
                    parent: servicesGridView.parent
                    visible: active
                }

                cellWidth: servicesGridView.width / 3
                cellHeight: cellWidth / 16 * 9
                model: streamingServices.model
                delegate: ServiceOverviewDelegate {}
            }
        }
    }
}

