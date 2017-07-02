import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Pane {
    id: root

    property bool isOpen: false

    clip: true

    onIsOpenChanged: searchField.text = ""

    Material.elevation: 2

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: searchField

            focus: true
            placeholderText: qsTr("Search by title or by artist")
            onEnabledChanged: {
                if (enabled) {
                    focus = true;
                    forceActiveFocus();
                }
            }
            selectByMouse: true
            onTextChanged: _listeningHistory.setSearchFilter(text)

            Tooltip {
                text: qsTr("Filter song by title or by artist")
            }

            Layout.fillWidth: true
        }

        Flow {
            id: filters
            spacing: 3

            width: parent.width

            Repeater {
                z: 1
                model: _streamingServices.model

                Button {
                    id: filter

                    flat: true
                    checkable: true; checked: true
                    hoverEnabled: true
                    text: model.name
                    onCheckedChanged: {
                        _listeningHistory.disableService(model.name, !checked)
                    }

                    Tooltip {
                        text: filter.checked ? qsTr("Click to remove songs from")  + model.name : qsTr("Click to add songs from ") + model.name
                    }

                    Connections {
                        target: filters
                        onEnabledChanged: filter.checked = true;
                    }
                }
            }
        }
    }

    state: "closed"
    states: [
        State {
            name: "closed"
            when: !root.isOpen

            PropertyChanges {
                target: root
                height: 0
            }

            PropertyChanges {
                target: searchField
                enabled: false
            }

            PropertyChanges {
                target: filters
                enabled: false
            }
        },
        State {
            name: "open"
            when: root.isOpen

            PropertyChanges {
                target: root
                height: root.implicitHeight
            }

            PropertyChanges {
                target: searchField
                enabled: true

            }

            PropertyChanges {
                target: filters
                enabled: true
            }
        }
    ]

    transitions: Transition {
        from: "open"
        to: "closed"
        reversible: true

        PropertyAnimation { properties: "height"; easing.type: "InOutCubic" }
    }
}
