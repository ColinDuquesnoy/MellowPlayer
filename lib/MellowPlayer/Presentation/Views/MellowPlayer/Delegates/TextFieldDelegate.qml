import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ItemDelegate {
    id: root

    property string label: ""
    property string value: ""
    property int textFieldPreferredWidth: 320

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

        TextField {
            enabled: root.enabled
            selectByMouse: true
            text: root.value

            onTextChanged: root.value = text;

            Layout.preferredWidth: root.textFieldPreferredWidth
        }
    }
}
