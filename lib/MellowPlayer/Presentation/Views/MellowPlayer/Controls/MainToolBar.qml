import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

ToolBar {
    id: toolBar

    property int iconSize: 22
    Material.primary: style.primary
    Material.foreground: style.primaryForeground
    Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light
    

    RowLayout {
        anchors.fill: parent
        spacing: 0

        ToolButton {
            text: body.state == "webview" ? MaterialIcons.icon_apps : MaterialIcons.icon_arrow_back
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.previewImage !== undefined || body.state == "webview"

            onClicked:  {
                if (body.previewImage.state === "selected") {
                    // to overview
                    webViewStack.currentWebView().updateImageFinished.connect(switchToOverview);
                    webViewStack.currentWebView().updateImage();
                } else {
                    // back
                    body.state = "between";
                    body.previewImage.state = "selected";
                }
            }

            function switchToOverview() {
                body.state = "between";
                body.previewImage.state = "";
                webViewStack.currentWebView().updateImageFinished.disconnect(switchToOverview);
            }


            Tooltip {
                y: toolBar.implicitHeight
                text: body.state == "webview" ? qsTr("Select another service") :
                      streamingServices.currentService != null ?
                      qsTr("Go back to ") + streamingServices.currentService.name : ""
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }

            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_left
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"

            onClicked: webViewStack.currentWebView().goBack()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Go back")
            }
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_right
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: webViewStack.currentWebView().goForward()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Go forward")
            }
        }

        ToolButton {
            text: MaterialIcons.icon_refresh
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: webViewStack.currentWebView().reload()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Reload this page")
            }
        }

        ToolButton {
            text: MaterialIcons.icon_home
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: {
                webViewStack.currentWebView().url = webViewStack.currentWebView().urlToLoad
                webViewStack.currentWebView().isRunning = true;
            }

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Go to the homepage")
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible: btFavorite.visible

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        ToolButton {
            id: btFavorite
            text: player.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            enabled: body.state == "webview" && player.canAddToFavorites
            visible: body.state == "webview"

            onClicked: player.toggleFavoriteSong()

            Tooltip {
                y: toolBar.implicitHeight
                text: player.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
            }
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            id: btPrevious

            text: MaterialIcons.icon_fast_rewind
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            enabled: player.canGoPrevious && (player.currentSong !== null && player.currentSong.isValid())

            onClicked: player.previous()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Skip to previous song")
            }
        }

        ToolButton {
            id: btPlay

            text: player.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            enabled: !player.isStopped || (player.currentSong !== null && player.currentSong.isValid())

            onClicked: player.togglePlayPause()

            Tooltip {
                y: toolBar.implicitHeight
                text:  player.isPlaying ? qsTr("Pause") : qsTr("Play")
            }
        }

        ToolButton {
            id: btNext

            text: MaterialIcons.icon_fast_forward
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            enabled: player.canGoNext && (player.currentSong !== null && player.currentSong.isValid())

            onClicked: player.next()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Skip to next song")
            }
        }

        ToolButton {
            id: btEnableNotifications

            Layout.fillHeight: true
            Material.accent: style.accent == style.primary ? style.primaryForeground : style.accent

            text: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            checkable: true
            checked: true

            Tooltip {
                y: toolBar.implicitHeight
                text: btEnableNotifications.checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }

            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_history
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            onClicked: listeningHistoryDrawer.open()

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Listening history")
            }
        }

        ToolButton {
            text: MaterialIcons.icon_more_vert
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            onClicked: menu.open()

            Menu {
                id: menu
                y: parent.implicitHeight

                MenuIconItem {
                    icon: MaterialIcons.icon_settings
                    onClicked: stackView.push(settingsPageComponent)
                    text: "Settings"
                }

                MenuIconItem {
                    icon: MaterialIcons.icon_info_outline
                    text: "About"
                    onClicked: aboutDialog.visible = true
                }

                Rectangle {
                    color: style.isDark(style.background) ? Qt.lighter(style.background) : Qt.darker(style.background, 1.1)
                    height: 1
                    width: parent.width
                }

                MenuIconItem {
                    icon: MaterialIcons.icon_power_settings_new
                    text: "Quit"
                    onClicked: Qt.quit();
                }
            }

            Tooltip {
                y: toolBar.implicitHeight
                text: qsTr("Main menu")
            }
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        height: toolBar.height
        width: 300
        visible: body.state == "webview"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 9
            spacing: 0

            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: getText()
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: sliderGroup.visible ? "AlignTop" : "AlignVCenter"
                elide: "ElideMiddle"
                font.pixelSize: sliderGroup.visible ? 12 : 14

                function getText() {
                    if (webViewStack.currentWebView() !== null && webViewStack.currentWebView().loading)
                        return "Loading " + streamingServices.currentService.name;

                    var currentSong = player.currentSong;
                    if (currentSong.title && currentSong.artist)
                        return "<b>" + currentSong.title + "</b><i> by " + currentSong.artist;
                    else if (currentSong.title)
                        return "<b>" + currentSong.title + "</b>";
                    else if (streamingServices.currentService !== null)
                        return streamingServices.currentService.name;
                    return "";
                }
            }

            Item {
                id: sliderGroup
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? slider.implicitHeight : 0
                Layout.margins: 0
                visible: player.canSeek

                RowLayout {
                    anchors.fill: parent

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(player.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return text;
                        }
                        font.pixelSize: 11
                    }

                    Slider {
                        id: slider

                        Layout.fillWidth: true
                        hoverEnabled: true

                        from: 0
                        value: player.position
                        to: player.currentSong.duration

                        onValueChanged: if (player.position != value) player.seekToPosition(value)

                    }

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(player.currentSong.duration - player.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return "-" + text;
                        }
                        font.pixelSize: 11
                    }
                }
            }
        }
    }
}
