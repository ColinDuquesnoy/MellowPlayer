import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

Dialog {
    id: root

    property JavaScriptDialogRequest request

    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    title: request.message

    onAccepted: request.dialogAccept(textField.text)
    onRejected: request.dialogReject()

    Material.accent: _theme.accent === _theme.background ? _theme.foreground : _theme.accent

    TextField {
        id: textField
        anchors.fill: parent
        text: request.defaultText
        selectByMouse: true
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
