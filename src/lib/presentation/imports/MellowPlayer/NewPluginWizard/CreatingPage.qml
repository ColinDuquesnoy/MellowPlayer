import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

WizardPage {
    id: root

    property string svName
    property string svUrl
    property string authorName
    property string authorUrl
    property bool allPlatforms
    property bool linuxPlatform
    property bool appImagePlatform
    property bool osxPlatform
    property bool windowsPlatform

    property string directory: ""

    signal goNextRequested()

    title: qsTr("Creating plugin")
    description: qsTr("Please wait...")
    goBackVisible: false
    goNextVisible: true
    finishVisible: false
    goNextEnabled: !busyIndicator.running

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: root.directory == ""
    }

    Component.onCompleted: {
        _streamingServices.createService(svName, svUrl, authorName, authorUrl, allPlatforms, linuxPlatform, appImagePlatform, osxPlatform, windowsPlatform)
    }

    Connections {
        target: _streamingServices
        onServiceCreated: {
            root.directory = directory
            root.goNextRequested()
        }
    }
}
