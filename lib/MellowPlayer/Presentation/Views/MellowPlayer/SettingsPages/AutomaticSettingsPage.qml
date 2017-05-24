import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Flickable {
    id: root

    property var settingsModel: model.settings

    contentHeight: pane.implicitHeight
    contentWidth: parent.width

    Pane {
        id: pane

        anchors.fill: parent
        padding: 16

        ColumnLayout {

            anchors.fill: parent
            spacing: 0

            Repeater {
                model: root.settingsModel

                Loader {
                    source: model.qmlComponent
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
    ScrollBar.vertical: ScrollBar { }
}
