import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/MellowPlayer/QmlFrontend"

ToolBar {
    id: toolBar
//    Material.primary: "#273a4b"
    Material.primary: Material.background

    property int iconSize: 16
    signal selectServiceTriggered()

    RowLayout {
        anchors.fill: parent

        ToolButton {
            text: MaterialIcons.icon_apps
            font.family: MaterialIcons.family
            font.pointSize: 22

            onClicked:  body.currentWebView.state == "selected" ? body.currentWebView.state = "overview" : body.currentWebView.state = "selected"
        }

        // todo add separator (need Qt 5.8)

        ToolButton {
            text: MaterialIcons.icon_chevron_left
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_right
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_refresh
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_home
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_favorite_border
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            text: MaterialIcons.icon_fast_rewind
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_play_arrow
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_fast_forward
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        // todo add separator (need Qt 5.8)

        ToolButton {
            text: MaterialIcons.icon_notifications
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }

        ToolButton {
            text: MaterialIcons.icon_more_vert
            font.family: MaterialIcons.family
            font.pointSize: toolBar.iconSize
        }
    }

    Label {
        text: "Get Lucky by Daft Punks on XXXAlbum"
        anchors.centerIn: parent
    }
}
