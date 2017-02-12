import QtQuick 2.7
import QtWebEngine 1.3

QtObject {
    id: root

    property Component browserDialogComponent: BrowserDialog {
        onClosing: destroy();
    }

    function createDialog(profile) {
        var newDialog = browserDialogComponent.createObject(root);
        newDialog.currentWebView.profile = profile;
        return newDialog;
    }
}