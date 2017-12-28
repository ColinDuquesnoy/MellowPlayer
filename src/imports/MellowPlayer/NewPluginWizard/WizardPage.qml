import QtQuick 2.7

FocusScope {
    property string title: ""
    property string description: ""
    property bool goBackVisible: true
    property bool goNextVisible: true
    property bool goNextEnabled: true
    property bool finishVisible: false
    property bool openPluginDirectoryVisible: false
    property bool showDocVisible: false
    property Component previous: null
    property Component next: null
}
