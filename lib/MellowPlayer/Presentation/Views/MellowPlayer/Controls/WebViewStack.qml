import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0

StackLayout {
    id: root

    signal newViewRequested(var request, var profile)
    signal fullScreenRequested(var request)

    function currentWebView() {
        return root.itemAt(root.currentIndex);
    }
    function goBack() {
        currentWebView().goBack();
    }
    function goHome() {
        var webView = currentWebView();
        webView.url = webView.urlToLoad
        webView.reload();
    }
    function goForward() {
        currentWebView().goForward();
    }
    function reload() {
        currentWebView().reload();
    }
    function toList() {
        var list = []
        for(var i = 0; i < root.count; i++)
            list.push(root.itemAt(i));
        return list;
    }
    function updatePreviewImage(callback) {
        d.callback = callback
        currentWebView().updateImageFinished.connect(d.onUpdatePreviewImageFinished);
        currentWebView().updateImage();
    }
    function exitFullScreen() {
        currentWebView().exitFullScreen();
    }

    currentIndex: _streamingServices.currentIndex

    QtObject {
        id: d

        property var callback

        function onUpdatePreviewImageFinished() {
            currentWebView().updateImageFinished.disconnect(d.onUpdatePreviewImageFinished);
            callback()
        }
    }

    Repeater {
        id: repeater

        model: _streamingServices.model
        delegate: WebView {
            id: webView

            anchors.fill: parent
            visible: visible && root.currentIndex == index;
            enabled: visible
            player: model.player
            urlToLoad: model.url
            service: model.qtObject

            onCustomUrlSet: {
                model.url = customUrl
                start()
            }
            onFullScreenRequested: root.fullScreenRequested(request);
            onNewViewRequested: root.newViewRequested(request, webView.profile)
        }
    }

    Shortcut {
        property var setting: _settings.get(SettingKey.SHORTCUTS_SELECT_NEXT_SERVICE)

        sequence: setting.value
        onActivated: _streamingServices.next()
    }

    Shortcut {
        property var setting: _settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting.value
        onActivated: _streamingServices.previous()
    }
}
