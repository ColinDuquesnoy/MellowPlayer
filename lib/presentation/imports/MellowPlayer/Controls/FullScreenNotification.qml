import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Pane {
    id: notif

    x: parent.width / 2 - width / 2; y: 12
    visible: false
    onVisibleChanged: if (visible) disappearTimer.running = true

    Material.elevation: 4
    Material.background: "#303030"
    Material.foreground: "#ffffff"
    Material.theme: Material.Dark

    Label {
        text: qsTr("<p>You are now in <b>fullscreen</b> mode.</p>Press <b>ESC</b> to quit!")
        font.pixelSize: 16
        horizontalAlignment: "AlignHCenter"
    }

    Timer {
        id: disappearTimer
        interval: 3000
        onTriggered: notif.visible = false;
    }

    Behavior on opacity { NumberAnimation { duration: 100 } }

    states: [
        State {
            when: notif.visible

            PropertyChanges {
                target: notif
                opacity: 0.8
            }
        },
        State {
            when: !notif.visible

            PropertyChanges {
                target: notif
                opacity: 0.0
            }
        }
    ]
}
