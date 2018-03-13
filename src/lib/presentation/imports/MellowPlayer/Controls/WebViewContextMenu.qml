import QtQuick 2.9
import QtQuick.Controls 2.2

Menu {
    id: root

    property bool canCopy: false
    property bool canPaste: false
    property bool canUnselect: false
    property bool canGoBack: false
    property bool canGoForward: false
    property bool hasLink: false

    signal copyRequested()
    signal pasteRequested()
    signal unselectRequested()
    signal copyLinkRequested()
    signal openLinkRequested()
    signal goBackRequested()
    signal goForwardRequested()
    signal reloadRequested()
    signal viewPageSourceRequested()
    signal openWebDeveloperTools()

    width: 250

    function show() {
        openTimer.running = true;
    }

    Timer {
        id: openTimer
        interval: 200
        onTriggered: root.open()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        visible: canCopy
        text: qsTr("Copy")
        onClicked: copyRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Paste")
        visible: canPaste
        onClicked: pasteRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Unselect")
        visible: canUnselect
        onClicked: unselectRequested()
    }

    MenuSeparator {
        visible: canCopy || canPaste || canUnselect
        height: visible ? implicitHeight : 0
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Copy link")
        visible: hasLink
        onClicked: copyLinkRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Open link")
        visible: hasLink
        onClicked: openLinkRequested()
    }

    MenuSeparator {
        visible: hasLink
        height: visible ? implicitHeight : 0
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Back")
        visible: canGoBack
        onClicked: goBackRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Forward")
        visible: canGoForward
        onClicked: goForwardRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Reload")
        onClicked: reloadRequested()
    }

    MenuItem {
        text: qsTr("View Page Source")
        onClicked: viewPageSourceRequested()
    }

    MenuItem {
        text: qsTr("Open web developer tools")
        onClicked: _devTools.showDevTools()
    }
}
