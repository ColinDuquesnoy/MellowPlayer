import QtQuick 2.9
import QtWebEngine 1.5

import MellowPlayer 3.0

MessageBoxDialog {
    id: dialog

    property JavaScriptDialogRequest request

    title: qsTr("Do you want to reload this site?")
    message: qsTr("Changes that you made may not be saved.")
    standardButtons: MessageBoxDialog.Ok | MessageBoxDialog.Cancel

    onAccepted: request.dialogAccept()
    onRejected: request.dialogReject()

    Component.onCompleted: {
        try {
            dialog.standardButton(MessageBoxDialog.Ok).text = qsTr("Reload");
            dialog.standardButton(MessageBoxDialog.Cancel).text = qsTr("Don't reload");
        }
        catch (e) { }
    }
}
