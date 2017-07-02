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
    signal newViewRequested(var request)
    signal openListeningHistoryRequested()
    signal openSettingsRequested()
    signal openAboutDialogRequested()

    header: MainToolBar {
        id: toolBar

        isWebViewMode: body.state === "webview"
        hasRunningServices: _streamingServices.hasRunningServices

        onShowOverviewRequested: webViewStack.updatePreviewImage(body.showOverview)
        onShowWebViewRequested: body.showWebView()
        onGoBackRequested: webViewStack.goBack()
        onGoHomeRequested: webViewStack.goHome()
        onGoForwardRequested: webViewStack.goForward()
        onReloadRequested: webViewStack.reload()
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

                PropertyChanges {
                    target: _style
                    useServiceStyle: true
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
                    useServiceStyle: true
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
            onNewViewRequested: root.newViewRequested(request)

            Component.onCompleted: servicesOverview.sourceComponent = overviewComponent;
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