import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import MellowPlayer 3.0

StackLayout {
    id: webViewStack

    property int loadProgress: 0
    function currentWebView() {
        return webViewStack.itemAt(webViewStack.currentIndex);
    }

    currentIndex: streamingServices.currentIndex
    Component.onCompleted: overviewLoader.sourceComponent = overviewComponent;

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
        function goToNextLoadedWebView() {
            var index = getNextIndex(webViewStack.currentIndex);

            while(index != webViewStack.currentIndex) {
                var webView = webViewStack.itemAt(index);
                if (webView.url != "" && webView.isRunning) {
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

        sequence: "Ctrl+Tab"
        onActivated: goToNextLoadedWebView()
    }

    Shortcut {
        function goToPreviousLoadedWebView() {
            var index = getPreviousIndex(webViewStack.currentIndex);

            while(index != webViewStack.currentIndex) {
                var webView = webViewStack.itemAt(index);
                if (webView.url != "" && webView.isRunning) {
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

        sequence: "Ctrl+Shift+Tab"
        onActivated: goToPreviousLoadedWebView()
    }
}
