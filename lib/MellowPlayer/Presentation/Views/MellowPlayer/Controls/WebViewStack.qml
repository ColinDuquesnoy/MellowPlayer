import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0

StackLayout {
    id: root

    function currentWebView() {
        return root.itemAt(root.currentIndex);
    }

    currentIndex: streamingServices.currentIndex

    Repeater {
        id: repeater

        model: streamingServices.model

        WebView {
            id: webView

            anchors.fill: parent
            visible: visible && root.currentIndex == index;
            enabled: visible
        }
    }

    Shortcut {
        property var setting: settings.get(SettingKey.SHORTCUTS_SELECT_NEXT_SERVICE)

        sequence: setting != null ? setting.value : ""
        onActivated: goToNextLoadedWebView()

        function goToNextLoadedWebView() {
            var index = getNextIndex(root.currentIndex);

            while(index != root.currentIndex) {
                var webView = root.itemAt(index);
                if (webView.url != "" && webView.isRunning) {
                    streamingServices.currentService = webView.service;
                    break;
                }
                index = getNextIndex(index);
            }
        }

        function getNextIndex(index) {
            var nextIndex = index + 1;
            if (nextIndex >= root.count)
                nextIndex = 0;
            return nextIndex;
        }
    }

    Shortcut {
        property var setting: settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting != null ? setting.value : ""
        onActivated: goToPreviousLoadedWebView()

        function goToPreviousLoadedWebView() {
            var index = getPreviousIndex(root.currentIndex);

            while(index != root.currentIndex) {
                var webView = root.itemAt(index);
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
                previousIndex = root.count - 1;
            return previousIndex;
        }
    }
}
