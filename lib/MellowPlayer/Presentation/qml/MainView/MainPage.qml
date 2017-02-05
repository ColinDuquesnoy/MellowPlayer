import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

Page {
    id: mainPage

    header: MainToolBar { id: toolBar }

    Item {
        id: body
        anchors.fill: parent
        anchors.margins: 0

        property var previewImage
        property string originalBackgroundColor: Material.background
        property string originalForegroundColor: Material.foreground

        EnabledServices { id: services }

        states: [
            State {
                name: "overview"

                PropertyChanges {
                    target: mask
                    visible: true
                }

                PropertyChanges {
                    target: overviewLoader
                    visible: true
                    enabled: true
                }

                PropertyChanges {
                    target: webViewStack
                    visible: true
                    enabled: true
                }

                PropertyChanges {
                    target: toolBar
                    Material.background: body.originalBackgroundColor
                }

            },
            State {
                name: "webview"

                PropertyChanges {
                    target: mask
                    visible: false
                }

                PropertyChanges {
                    target: overviewLoader
                    visible: false
                    enabled: false
                }

                PropertyChanges {
                    target: webViewStack
                    visible: true
                    enabled: true
                }

                PropertyChanges {
                    target: toolBar
                    Material.background: webViewStack.itemAt(webViewStack.currentIndex).color
                }
            },
            State {
                name: "between"

                PropertyChanges {
                    target: mask
                    visible: true
                }


                PropertyChanges {
                    target: overviewLoader
                    visible: false
                }

                PropertyChanges {
                    target: webViewStack
                    visible: true
                }
            }
        ]
        state: "overview"

        StackLayout {
            id: webViewStack
            anchors.fill: parent

            Component.onCompleted: overviewLoader.sourceComponent = overviewComponent

            Repeater {
                id: repeater
                model: services

                WebEngineView {
                    id: webEngineView
                    anchors.fill: parent
                    settings.pluginsEnabled : true
                    visible: webViewStack.visible && webViewStack.currentIndex == index;
                    enabled: visible

                    property string urlToLoad: serviceUrl
                    property string color: serviceColor != "" ? serviceColor : Material.background
                    property var image: null
                    property bool ready: image != null || url == ""
                    signal updateImageFinished();

                    function updateImage() {
                        webEngineView.grabToImage(function(result) { image = result; updateImageFinished(); },
                                                  Qt.size(webEngineView.width, webEngineView.height));
                    }
                }
            }
        }

        Pane {
            id: mask
            anchors.fill: parent
        }

        Loader { id: overviewLoader; anchors.fill: parent; anchors.margins: 50; visible: false }

        Component {
            id: overviewComponent

            ColumnLayout {
                id: overview
                width: parent.width
                height: parent.height

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

                        ScrollBar.vertical: ScrollBar {
                            parent: servicesGridView.parent
                            anchors.top: servicesGridView.top
                            anchors.left: servicesGridView.right
                            anchors.bottom: servicesGridView.bottom
                            active: hovered
                            hoverEnabled: true

                        }

                        cellWidth: servicesGridView.width / 3
                        cellHeight: cellWidth / 16 * 9
                        model: EnabledServices {}
                        delegate: ServiceOverviewDelegate {}
                    }
                }
            }
        }
    }
}
