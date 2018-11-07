import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

import "login"
import "dialogs"

Frame {
    id: mainScreen
    width: 800
    height: 600

    Telegram.MessageSender {
        id: sender
        client: telegramClient
    }

    Row {
        id: contentRoot
        anchors.fill: mainScreen.contentItem
        DialogView {
            id: dialogView
            width: 320
            height: parent.height
            onActivateDialog: {
                console.log("Activate dialog peer(" + peer.type + ", " + peer.id + ")")
                messageView.peer = peer
                sender.peer = peer
            }
        }

        Item {
            id: rightColumn
            visible: width > 200
            width: parent.width - dialogView.width
            height: parent.height
            MessageView {
                id: messageView
                width: rightColumn.width
                anchors.top: rightColumn.top
                anchors.bottom: messageEditor.top
            }
            MessageEditor {
                id: messageEditor
                peer: messageView.peer
                width: rightColumn.width
                height: 64
                anchors.bottom: rightColumn.bottom
            }
        }
    }
}
