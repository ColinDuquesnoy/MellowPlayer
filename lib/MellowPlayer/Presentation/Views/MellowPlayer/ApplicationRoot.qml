import QtQuick 2.7
import QtWebEngine 1.3
import MellowPlayer 3.0

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
