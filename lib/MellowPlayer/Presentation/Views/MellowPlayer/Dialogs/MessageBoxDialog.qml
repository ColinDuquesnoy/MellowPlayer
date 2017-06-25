import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Popup {
    id: popup

    readonly property int acceptRole: 0
    readonly property int rejectRole: 1
    readonly property int dialogAccepted: 0
    readonly property int dialogRejected: 1

    property var buttonTexts: [qsTr("Ok"), qsTr("Cancel")]
    property var buttonRoles: [acceptRole, rejectRole]
    property var dialogResult: dialogRejected
    property string message: ""
    property string title: ""

    signal accepted()
    signal rejected()

    modal: true
    padding: 16

    Material.accent: style.accent === "#ffc107" ? style.primary : style.accent

    ColumnLayout {
        anchors.fill: parent
        spacing: 16

        Label {
            text: title
            font.bold: true
            font.pixelSize: 20
        }

        Label {
            text: message
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 20

            Item {
                Layout.fillWidth: true
            }

            Repeater {
                model: buttonTexts

                Button {
                    flat: true
                    highlighted: true
                    text: buttonTexts[index]
                    onClicked: buttonRoles[index] === acceptRole ? accept() : reject()
                }
            }
        }
    }

    Shortcut {
        sequence: "Return"
        onActivated: accept()
    }

    Shortcut {
        sequence: "Enter"
        onActivated: accept()
    }

    function accept() {
        dialogResult = dialogAccepted;
        accepted();
        close();
    }

    function reject() {
        dialogResult = dialogRejected;
        rejected();
        close();
    }
}
