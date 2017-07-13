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
    signal newViewRequested(var request, var profile)
    signal fullScreenRequested(var request)
    signal openListeningHistoryRequested()
    signal openSettingsRequested()
    signal openAboutDialogRequested()

    function showWebView() {
        body.showWebView();
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
        hasRunningServices: _streamingServices.hasRunningServices

        onShowOverviewRequested: webViewStack.updatePreviewImage(body.showOverview)
        onShowWebViewRequested: root.showWebView()
        onGoBackRequested: root.goBack()
        onGoHomeRequested: root.goHome()
        onGoForwardRequested: root.goForward()
        onReloadRequested: root.reload()
        onOpenListeningHistoryRequested: root.openListeningHistoryRequested()
        onOpenSettingsRequested: root.openSettingsRequested()
        onOpenAboutDialogRequested: root.openAboutDialogRequested()
    }

    Item {
        id: body
        anchors.fill: parent
        anchors.margins: 0

        property var previewImage

        function showWebView() {
            state = "between";
            previewImage.state = "selected";
        }

        function showOverview() {
            state = "between";
            previewImage.state = "";
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
                    visible: true
                    enabled: true
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
                    visible: true
                    enabled: true
                }

                PropertyChanges {
                    target: _style
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
                    visible: true
                }
            }
        ]
        state: "overview"

        WebViewStack {
            id: webViewStack

            anchors.fill: parent
            onNewViewRequested: root.newViewRequested(request, profile)
            onFullScreenRequested: {
                toolBar.visible = !request.toggleOn
                notif.visible = true;
                root.fullScreenRequested(request);
            }

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
    }
}

