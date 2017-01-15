import QtQuick 2.7
import QtQuick.Controls 2.0
import QtWebEngine 1.3


ApplicationWindow {
    visible: true
    visibility: "Maximized"
    title: "MellowPlayer"

    WebEngineView {
        id: webEngineView
        url: "https://www.deezer.com/"
        anchors.fill: parent
        settings.pluginsEnabled : true
    }
}
