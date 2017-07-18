import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Dialog {
    id: root
    readonly property int dialogAccepted: 0
    readonly property int dialogRejected: 1

    property int dialogResult: dialogRejected
    property string message: ""

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    onAccepted: dialogResult = dialogAccepted
    onRejected: dialogResult = dialogRejected

    Label {
        text: root.message
    }

    Shortcut {
        sequence: "Return"
        onActivated: accept()
    }

    Shortcut {
        sequence: "Enter"
        onActivated: accept()
    }
}
