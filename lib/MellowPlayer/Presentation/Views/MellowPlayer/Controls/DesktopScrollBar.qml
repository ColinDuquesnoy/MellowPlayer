import QtQuick 2.7
import QtQuick.Controls 2.0

ScrollBar {
    id: scrollBar

    hoverEnabled: true

    Timer {
        interval: 1
        repeat: Animation.Infinite
        running: true
        onTriggered: {
            scrollBar.active = scrollBar.size != 1;
        }
    }
}
