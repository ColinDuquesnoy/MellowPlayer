import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtWebEngine 1.5

import ".."
import "../Controls"

Dialog {
    id: dialog

    property AuthenticationDialogRequest request

    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    padding: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ItemDelegateSeparator { Layout.fillWidth: true }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 12
            Layout.leftMargin: d.sidePadding
            Layout.rightMargin: d.sidePadding
            spacing: 12

            Label {
                text: MaterialIcons.icon_vpn_lock
                font.pixelSize: 48

                Layout.alignment: Qt.AlignVCenter
            }

            Label {
                id: messageLabel
                font.pixelSize: 16

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
            }
        }

        ColumnLayout {
            Layout.leftMargin: d.sidePadding; Layout.rightMargin: d.sidePadding; Layout.bottomMargin: 12

            TextField {
                id: userNameTextField

                placeholderText: qsTr("User name")
                selectByMouse: true

                Keys.onPressed: {
                    if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
                        dialog.accept();
                }
                Layout.fillWidth: true
            }

            TextField {
                id: passwordTextField

                echoMode: showPasswordButton.checked ? TextField.Normal : TextField.Password
                placeholderText: qsTr("Password")
                selectByMouse: true

                Keys.onPressed: {
                    if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
                        dialog.accept();
                }
                Layout.fillWidth: true

                ToolButton {
                    id: showPasswordButton

                    anchors { right: parent.right; top: parent.top; bottom: parent.bottom }
                    checkable: true; checked: false
                    font.family: MaterialIcons.family
                    text: MaterialIcons.icon_remove_red_eye
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }

        ItemDelegateSeparator { Layout.fillWidth: true }
    }

    onAccepted: request.dialogAccept(userNameTextField.text, passwordTextField.text)
    onRejected: request.dialogReject()

    Component.onCompleted: {
        switch (request.type) {
            case  AuthenticationDialogRequest.AuthenticationTypeHTTP:
                if (request.realm)
                    messageLabel.text = qsTr('<b>%1</b> is requesting your username and password.<br>The site says: <b>"%2"</b>.').arg(request.url).arg(request.realm);
                else
                    messageLabel.text = qsTr('<b>%1</b> is requesting your username and password.').arg(request.url);
                dialog.title = qsTr("Authentication Required")
                break;
            case  AuthenticationDialogRequest.AuthenticationTypeProxy:
                messageLabel.text= qsTr('Proxy <b>%1</b> is requesting authentication').arg(request.proxyHost);
                dialog.title = qsTr("Proxy Authentication Required");
                break;
        }

        try {
            dialog.standardButton(Dialog.Ok).text = qsTr("Login");
        }
        catch (e) {
        }

        userNameTextField.forceActiveFocus();
    }

    QtObject {
        id: d

        property int sidePadding: 32
    }
}

