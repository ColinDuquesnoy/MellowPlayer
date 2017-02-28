import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0
import MellowPlayer 1.0
import "qrc:/MellowPlayer/Presentation"

ToolBar {
    id: toolBar

    property int iconSize: 22

    RowLayout {
        anchors.fill: parent

        ToolButton {
            text: MaterialIcons.icon_apps
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
        }

        ToolButton {
            text: MaterialIcons.icon_chevron_right
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: webViewStack.currentWebView().goForward()
        }

        ToolButton {
            text: MaterialIcons.icon_refresh
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: webViewStack.currentWebView().reload()
        }

        ToolButton {
            text: MaterialIcons.icon_home
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            onClicked: webViewStack.currentWebView().url = webViewStack.currentWebView().urlToLoad
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
            visible: body.state == "webview" && player.canAddToFavorites

            onClicked: player.toggleFavoriteSong()
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
            enabled: player.canGoPrevious

            onClicked: player.previous()
        }

        ToolButton {
            id: btPlay

            text: player.playbackStatus === Player.Playing ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            enabled: webViewStack.loadProgress >= 100

            onClicked: player.togglePlayPause()
        }

        ToolButton {
            id: btNext

            text: MaterialIcons.icon_fast_forward
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
            enabled: player.canGoNext
            onClicked: player.next()
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
            text: MaterialIcons.icon_notifications
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            visible: body.state == "webview"
        }

        ToolButton {
            text: MaterialIcons.icon_settings
            font.family: MaterialIcons.family
            font.pixelSize: toolBar.iconSize
            hoverEnabled: true
            onClicked: viewStack.push(settingsPageComponent)
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
                            if (text.startsWith("00:"))
                                text = text.substr(3);
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
                            if (text.startsWith("00:"))
                                text = text.substr(3);
                            return "-" + text;
                        }
                        font.pixelSize: 11
                    }
                }
            }
        }
    }
}
