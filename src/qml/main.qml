import QtQuick 2.7
import QtQuick.Controls 2.0
import QtWebEngine 1.3

import "qrc:/MellowPlayer/QmlFrontend"

ApplicationWindow {
    visible: true
    visibility: "Maximized"
    title: "MellowPlayer"
    minimumWidth: 800
    minimumHeight: 600

    WebEngineView {
        id: webEngineView
        url: "https://www.deezer.com/"
        anchors.fill: parent
        settings.pluginsEnabled : true

        onLoadProgressChanged: {
            console.log("Loading " + loadProgress + "%");
        }
    }

    ToolButton {
        text: MaterialIcons.icon_apps
        font.family: MaterialIcons.family
        font.pointSize: 22
        anchors.left: parent.left
        anchors.top: parent.top
    }

}
