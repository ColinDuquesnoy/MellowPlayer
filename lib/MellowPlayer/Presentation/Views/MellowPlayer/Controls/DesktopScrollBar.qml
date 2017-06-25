import QtQuick 2.9
import QtQuick.Controls 2.2

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
