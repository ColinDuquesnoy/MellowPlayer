import QtQuick 2.7
import QtQuick.Controls 2.0

ToolTip {
    id: tooltip

    visible: parent !== undefined ? parent.hovered : false
    delay: 1000
    timeout: 5000
    y: parent.implicitHeight

    contentItem: Text {
        text: tooltip.text
        font: tooltip.font
        color: "white"
    }

    background: Rectangle {
        color: "#606060"
        opacity: 0.9
        radius: 2
    }
}
