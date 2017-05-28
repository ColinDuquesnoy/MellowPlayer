import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.3

import MellowPlayer 3.0

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
                    target: style
                    usePluginStyle: false
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
                    target: style
                    usePluginStyle: true
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

        WebViewStack {
            id: webViewStack
            anchors.fill: parent
        }

        Pane { id: mask; anchors.fill: parent }

        Loader { id: overviewLoader; anchors.fill: parent; visible: false }

        Component { id: overviewComponent; ServicesOverview { } }
    }
}
