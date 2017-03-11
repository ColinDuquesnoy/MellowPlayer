import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import "../controls"

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
                    Material.background: webViewStack.currentWebView().color
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

            currentIndex: streamingServices.currentIndex
            anchors.fill: parent

            Component.onCompleted: overviewLoader.sourceComponent = overviewComponent;

            property int loadProgress: 0

            function currentWebView() { return webViewStack.itemAt(webViewStack.currentIndex); }

            Repeater {
                id: repeater
                model: streamingServices.model

                WebView {
                    id: webView
                    anchors.fill: parent

                    onLoadProgressChanged: {
                        webViewStack.loadProgress = loadProgress
                    }
                }
            }

            Shortcut {
                sequence: "Ctrl+Tab"
                onActivated: goToNextLoadedWebView()

                function goToNextLoadedWebView() {
                    var index = getNextIndex(webViewStack.currentIndex);

                    while(index != webViewStack.currentIndex) {
                        var webView = webViewStack.itemAt(index);
                        if (webView.url != "") {
                            streamingServices.currentService = webView.service;
                            break;
                        }
                        index = getNextIndex(index);
                    }
                }

                function getNextIndex(index) {
                    var nextIndex = index + 1;
                    if (nextIndex >= webViewStack.count)
                        nextIndex = 0;
                    return nextIndex;
                }
            }

            Shortcut {
                sequence: "Ctrl+Shift+Tab"
                onActivated: goToPreviousLoadedWebView()

                function goToPreviousLoadedWebView() {
                    var index = getPreviousIndex(webViewStack.currentIndex);

                    while(index != webViewStack.currentIndex) {
                        var webView = webViewStack.itemAt(index);
                        if (webView.url != "") {
                            streamingServices.currentService = webView.service;
                            break;
                        }
                        index = getPreviousIndex(index);
                    }
                }

                function getPreviousIndex(index) {
                    var previousIndex = index - 1;
                    if (previousIndex < 0)
                        previousIndex = webViewStack.count - 1;
                    return previousIndex;
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

            ServicesOverview { }

        }
    }
}
