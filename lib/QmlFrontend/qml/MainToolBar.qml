import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/MellowPlayer/QmlFrontend"

ToolBar {
    id: toolBar
    Material.primary: Material.background

    property int iconSize: 16

    RowLayout {
        anchors.fill: parent

        ToolButton {
            text: MaterialIcons.icon_apps
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.previewImage !== undefined

            onClicked:  {
                if (body.previewImage.state === "selected") {
                    // to overview
                    webViewStack.itemAt(webViewStack.currentIndex).updateImageFinished.connect(switchToOverview);
                    webViewStack.itemAt(webViewStack.currentIndex).updateImage();
                } else {
                    // back
                    body.state = "between";
                    body.previewImage.state = "selected";
                }
            }

            function switchToOverview() {
                body.state = "between";
                body.previewImage.state = "";
                webViewStack.itemAt(webViewStack.currentIndex).updateImageFinished.disconnect(switchToOverview);
            }
        }

        Item { Layout.preferredWidth: 5 }

        ToolButton {
            text: MaterialIcons.icon_chevron_left
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_right
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_refresh
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_home
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_favorite_border
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            text: MaterialIcons.icon_fast_rewind
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_play_arrow
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_fast_forward
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        Item { Layout.preferredWidth: 5 }

        ToolButton {
            text: MaterialIcons.icon_notifications
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_more_vert
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
            hoverEnabled: true
        }
    }

    Label {
        text: "Get Lucky by Daft Punks on XXXAlbum"
        anchors.centerIn: parent
        visible: body.state == "webview"
    }
}
