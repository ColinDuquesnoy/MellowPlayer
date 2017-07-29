import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0
import ".."

Page {
    id: root

    property int mainWindowWidth
    property alias isWebViewModel: toolBar.isWebViewMode

    signal newViewRequested(var request, var profile)
    signal fullScreenRequested(var request)
    signal openListeningHistoryRequested()
    signal openSettingsRequested()
    signal openAboutDialogRequested()
    signal createPluginRequested()

    function showWebView() {
        d.showWebView();
    }

    function exitFullScreen() {
        webViewStack.exitFullScreen();
        notif.visible = false;
    }

    function goBack() {
        webViewStack.goBack()
    }

    function goHome() {
        webViewStack.goHome()
    }

    function goForward() {
        webViewStack.goForward()
    }

    function reload() {
        webViewStack.reload()
    }

    header: MainToolBar {
        id: toolBar

        isWebViewMode: body.state === "webview"
        isCurrentServiceRunning: _streamingServices.isCurrentServiceRunning

        onShowOverviewRequested: webViewStack.updatePreviewImage(d.showOverview)
        onShowWebViewRequested: root.showWebView()
        onGoBackRequested: root.goBack()
        onGoHomeRequested: root.goHome()
        onGoForwardRequested: root.goForward()
        onReloadRequested: root.reload()
        onOpenListeningHistoryRequested: root.openListeningHistoryRequested()
        onOpenSettingsRequested: root.openSettingsRequested()
        onOpenAboutDialogRequested: root.openAboutDialogRequested()
        onCreatePluginRequested: root.createPluginRequested()
    }
    footer: UpdateToolBar { width: parent.width }

    Item {
        id: body

        property var previewImage

        anchors { fill: parent; margins: 0 }

        Component.onCompleted: d.startCurrentService()

        WebViewStack {
            id: webViewStack

            anchors.fill: parent

            onNewViewRequested: root.newViewRequested(request, profile)
            onFullScreenRequested: d.handleFullScreenRequest(request)
            onCurrentIndexChanged: if (currentIndex === -1) body.showOverview()

            Component.onCompleted: servicesOverview.sourceComponent = overviewComponent;
        }

        FullScreenNotification {
            id: notif

            x: parent.width / 2 - width / 2; y: 12
        }

        Pane { id: mask; anchors.fill: parent }

        Loader { id: servicesOverview; anchors.fill: parent; visible: false }

        Component {
            id: overviewComponent

            ServicesOverview {
                height: parent.height; width: parent.width
                mainWindowWidth: root.mainWindowWidth
                transitionItem: body
                webViews: webViewStack.toList();
            }
        }

        states: [
            State {
                name: "overview"

                PropertyChanges {
                    target: mask
                    visible: true
                }

                PropertyChanges {
                    target: servicesOverview
                    visible: true
                    enabled: true
                }

                PropertyChanges {
                    target: webViewStack
                    x: -root.width
                    enabled: false
                }
            },
            State {
                name: "webview"

                PropertyChanges {
                    target: mask
                    visible: false
                }

                PropertyChanges {
                    target: servicesOverview
                    visible: false
                    enabled: false
                }

                PropertyChanges {
                    target: webViewStack
                    enabled: true
                    x: 0
                }
            },
            State {
                name: "between"

                PropertyChanges {
                    target: mask
                    visible: true
                }

                PropertyChanges {
                    target: servicesOverview
                    visible: false
                }

                PropertyChanges {
                    target: webViewStack
                    enabled: true
                }
            }
        ]
        state: "overview"
    }

    QtObject {
        id: d

        function showWebView() {
            if (body.state == "overview") {
                body.state = "between";
                try {
                    body.previewImage.state = "selected";
                }
                catch (e) {
                    body.state = "webview";
                }
            }
        }

        function showOverview() {
            if (body.state == "webview") {
                try {
                    body.state = "between";
                    body.previewImage.state = "";
                }
                catch (e) {
                    body.state = "overview";
                }
            }
        }

        function startCurrentService() {
            if (_streamingServices.currentIndex != -1) {
                body.state = "webview"
                webViewStack.currentWebView().start();
            }
        }

        function handleFullScreenRequest(request) {
            toolBar.visible = !request.toggleOn
            notif.visible = true;
            root.fullScreenRequested(request);
        }
    }
}

