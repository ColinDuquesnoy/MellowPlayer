import QtQuick 2.9
import QtWebEngine 1.5

import MellowPlayer 3.0

MessageBoxDialog {
    id: dialog

    property JavaScriptDialogRequest request

    title: request.title
    message: request.message;
    standardButtons: MessageBoxDialog.Ok

    onAccepted: request.dialogAccept()
    onRejected: request.dialogReject()
}
