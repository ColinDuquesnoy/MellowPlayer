import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import MellowPlayer 3.0
import ".."

Page {
    id: mainPage

    header: MainToolBar {
        id: toolBar;
        isWebViewMode: body.state == "webview"
    }

    Item {
        id: body
        anchors.fill: parent
        anchors.margins: 0

        property var previewImage

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
                    target: style
                    useServiceStyle: false
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
                    target: style
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

            Component.onCompleted: servicesOverview.sourceComponent = overviewComponent;
        }

        Pane { id: mask; anchors.fill: parent }

        Loader { id: servicesOverview; anchors.fill: parent; visible: false }

        Component { id: overviewComponent; ServicesOverview { } }
    }
}
