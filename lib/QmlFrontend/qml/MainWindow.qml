import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

ApplicationWindow {
    id: mainWindow
    title: "MellowPlayer"
    minimumWidth: 1280
    minimumHeight: 720

    header: MainToolBar {
        onSelectServiceTriggered: console.log("selectServiceTriggered")
    }


    Item {
        id: body
        anchors.fill: parent
        anchors.margins: 0
        property bool overviewVisible: true
        property Item currentWebView

        ColumnLayout{
            id: overview
            anchors.fill: parent
            anchors.margins: 50
            visible: body.overviewVisible

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
                            return 0.90 * mainWindow.width;
                        else if( mainWindow.width < 1920)
                            return 0.80 * mainWindow.width;
                        else
                            return 0.70 * mainWindow.width;
                    }
                    height: parent.height

                    clip: true

                    ScrollBar.vertical: ScrollBar { }

                    cellWidth: width / 3
                    cellHeight: cellWidth * 0.75

                    model: EnabledServices {}
                    delegate: ServiceDelegate {}

                    onCellWidthChanged: console.log(width, height)
                }
            }
        }

    }
}
