import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ItemDelegate {
    id: root

    property string label: ""
    property int value: 0
    property int from: 0
    property int to: 65535

    hoverEnabled: true

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 16
        spacing: 12

        Label {
            text: root.label
            enabled: root.enabled
        }

        Item {
            Layout.fillWidth: true
        }

        SpinBox {
            enabled: root.enabled
            editable: true
            value: root.value
            from: root.from
            to: root.to

            onValueChanged: root.value = value;
        }
    }
}
