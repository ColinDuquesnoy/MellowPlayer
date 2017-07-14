import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

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
                anchors.centerIn: parent
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

                cellWidth: width / 3
                cellHeight: cellWidth / 16 * 9
                model: _streamingServices.enabledServices
                delegate: ServiceOverviewDelegate {
                    transitionItem: root.transitionItem
                    webView: webViews[_streamingServices.getWebViewIndex(model.name)]
                }
            }
        }
    }
}

