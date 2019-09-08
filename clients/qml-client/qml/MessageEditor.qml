import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import TelegramQt 0.2
import TelegramQtTheme 1.0

Item {
    id: messageEditor
    height: 64
    width: 200

    Frame { anchors.fill: parent } // Decoration

    onActiveFocusChanged: {
        if (activeFocus) {
            textEditor.forceActiveFocus()
        }
    }

    RowLayout {
        id: rowLayout

        anchors.fill: messageEditor
        ToolButton {
            id: attachButton
            text: '\uE4A0' // '\uD83D\uDCCE' ?
            font.pixelSize: messageEditor.fontSize
        }
        TextArea {
            id: textEditor
            Layout.fillWidth: true
            placeholderText: qsTr("Write a message...")
            wrapMode: TextArea.Wrap
            Keys.onPressed: {
                if (event.key === Qt.Key_Return) {
                    if (event.modifiers & Qt.CtrlModifier) {
                        textEditor.append('\n')
                    } else {
                        sender.sendMessage(textEditor.text)
                        event.accepted = true
                        textEditor.clear()
                    }
                }
            }
            onTextChanged: sender.setText(text)
        }
        ToolButton {
            id: emojiButton
            text:'\u263A'
            font.pixelSize: messageEditor.fontSize
        }
//        ToolButton {
//            id: recordMessageButton
//            text:'\uD83D\uDCCE'
//        }
    }
}
