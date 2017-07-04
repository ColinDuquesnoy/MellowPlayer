import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQml 2.2

import MellowPlayer 3.0
import ".."

Dialog {
    id: wizard

    property Item currentPage: stackView.currentItem
    property string svName
    property string svUrl
    property string authorName
    property string authorUrl
    property string directory

    title: currentPage.title
    onAccepted: restart()
    onRejected: restart()

    function restart() {
        while (stackView.depth > 1)
            stackView.pop()
    }

    function next() {
        stackView.push(currentPage.next)
    }

    function previous() {
        stackView.pop();
    }

    Component {
        id: startPage

        StartPage {
            next: detailsPage
            previous: null
        }
    }

    Component {
        id: detailsPage

        DetailsPage {
            next: creatingPage
            previous: startPage

            onSvNameChanged: wizard.svName = svName
            onSvUrlChanged: wizard.svUrl = svUrl
            onAuthorNameChanged: wizard.authorName = authorName
            onAuthorUrlChanged: wizard.authorUrl = authorUrl
        }
    }

    Component {
        id: creatingPage

        CreatingPage {
            next: finishPage
            previous: detailsPage
            svName: wizard.svName
            svUrl: wizard.svUrl
            authorName: wizard.authorName
            authorUrl: wizard.authorUrl

            onGoNextRequested: wizard.next()
            onDirectoryChanged: wizard.directory = directory
        }
    }


    Component {
        id: finishPage

        FinishPage {
            next: null
            previous: creatingPage
            directory: wizard.directory
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: currentPage.description
            font.italic: true

            Layout.leftMargin: 24
        }

        Item {
            Layout.preferredHeight: 4
        }

        Rectangle {
            color: _style.foreground
            opacity: 0.5

            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        Item {
            Layout.preferredHeight: 4
        }

        StackView {
            id: stackView

            initialItem: startPage
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    footer: Pane {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 8
            anchors.topMargin: 8

            Button {
                id: openPluginDirectory

                highlighted: true
                text: "Open plugin directory"
                visible: currentPage.openPluginDirectoryVisible
                flat: true

                onClicked: Qt.openUrlExternally("file://" + wizard.directory)
            }

            Button {
                highlighted: true
                flat: true
                text: "Read API documentation"
                visible: currentPage.showDocVisible

                onClicked: Qt.openUrlExternally("http://mellowplayer.readthedocs.org/en/latest/developers/plugins.html#functions-to-implement")
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                id: previousButton

                highlighted: true
                text: "Previous"
                visible: currentPage.goBackVisible
                flat: true

                onClicked: wizard.previous()
            }
            Button {
                id: nextButton

                highlighted: true
                flat: true
                text: "Next"
                enabled: currentPage.goNextEnabled
                visible: currentPage.goNextVisible

                onClicked: wizard.next()
            }
            Button {
                id: cancelButton

                highlighted: true
                flat: true
                text: "Cancel"
                visible: !currentPage.finishVisible

                onClicked: wizard.reject()
            }
            Button {
                id: finishButton

                highlighted: true
                flat: true
                text: "Finish"
                visible: currentPage.finishVisible
                onClicked: wizard.accept()
            }
        }
    }
}
