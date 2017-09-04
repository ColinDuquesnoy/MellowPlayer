import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

WizardPage {
    property alias svName: fieldSvName.text
    property alias svUrl: fieldSvUrl.text
    property alias authorName: fieldAuthor.text
    property alias authorUrl: fieldAuthorWebsite.text

    title: qsTr("Details")
    description: qsTr("Please fill in the details about your plugin")
    goBackVisible: true
    goNextVisible: true
    finishVisible: false
    goNextEnabled: fieldSvName.text != "" && fieldSvUrl.text != "" && fieldAuthor.text != "" && fieldAuthorWebsite.text != ""

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.fillWidth: true

            columns: 2
            rows: 4

            Label {
                text: qsTr("Service name:")
            }

            TextField {
                id: fieldSvName

                focus: true
                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Service URL:")
            }

            TextField {
                id: fieldSvUrl

                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Author:")
            }

            TextField {
                id: fieldAuthor

                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Author website:")
            }

            TextField {
                id: fieldAuthorWebsite

                selectByMouse: true

                Layout.fillWidth: true
            }

        }

        Item {
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: fieldSvName.forceActiveFocus()
}
