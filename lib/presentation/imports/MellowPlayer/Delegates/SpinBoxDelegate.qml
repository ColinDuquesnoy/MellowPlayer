import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Controls.Material.impl 2.2

ItemDelegate {
    id: root

    property string label: ""
    property int value: 0
    property int from: 0
    property int to: 65535

    property var valueFromText: function(text, locale) { return Number.fromLocaleString(locale, text); }
    property var textFromValue: function(value, locale) { return Number(value).toLocaleString(locale, 'f', 0); }

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
            id: spinBox
            enabled: root.enabled
            editable: true
            value: root.value
            from: root.from
            to: root.to
            valueFromText: root.valueFromText
            textFromValue: root.textFromValue

            onValueChanged: root.value = value;

            Component.onCompleted: {
                contentItem.selectByMouse = true;
                contentItem.selectionColor = _theme.accent;
                contentItem.selectedTextColor = Material.primaryHighlightedTextColor;
            }

            Connections {
                target: _theme
                onAccentChanged: spinBox.contentItem.selectionColor = _theme.accent
            }
        }
    }
}
