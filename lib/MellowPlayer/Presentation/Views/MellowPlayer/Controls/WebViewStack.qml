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
        onActivated: streamingServices.next()
    }

    Shortcut {
        property var setting: settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting != null ? setting.value : ""
        onActivated: streamingServices.previous()
    }
}
