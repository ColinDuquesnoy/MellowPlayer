import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0
import ".."

Pane {
    bottomPadding: 3; topPadding: 3
    enabled: model.enabled
    width: parent.width

    RowLayout {
        spacing: 16

        Label {
            text: model.name
            font.pixelSize: 16

            Layout.preferredWidth: 150
        }

        TextField {
            id: keySequenceEdit

            property int nbKeyPressed: 0
            property int newKey: 0
            property int newMofifiers: 0
            property string memText: text

            onTextChanged: model.qtObject.value = text
            text: model.qtObject.value

            Keys.onPressed: {
                nbKeyPressed += 1

                if (nbKeyPressed > 3) {
                    nbKeyPressed = 3
                }

                if( nbKeyPressed == 1) {
                    startRecording()
                }
                placeholderText = model.qtObject.keySequenceToString(event.key, event.modifiers);
                newKey = event.key;
                newMofifiers = event.modifiers
                event.accepted = true;
                timerRecording.restart();
            }
            Keys.onReleased: {
                nbKeyPressed -= 1;
                if (event.key === Qt.Key_Escape)
                    cancelRecording();
                else if( nbKeyPressed == 0)
                    finishRecording();
                event.accepted = true;
            }

            function startRecording() {
                memText = text;
                text = ""
                placeholderText = ""
            }

            function cancelRecording() {
                placeholderText = ""
                text = memText;
                nbKeyPressed = 0;
                timerRecording.stop();
            }

            function finishRecording() {
                if (model.qtObject.isValidKeySequence(newKey, newMofifiers))
                    text = placeholderText
                else
                    text = memText;
                placeholderText = ""
                nbKeyPressed = 0;
                timerRecording.stop();
            }

            Tooltip {
                text: model.toolTip
            }

            Component.onCompleted: {
                try {
                    hoverEnabled = true
                }
                catch (e) {
                    // not available with Qt < 5.8
                }
            }

            Layout.fillWidth: true
        }
    }

    Timer {
        id: timerRecording
        running: true
        interval: 2000
//        onTriggered: keySequenceEdit.finishRecording();
    }
}
