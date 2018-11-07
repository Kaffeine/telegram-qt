import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

import Client 1.0

Frame {
    id: dialogView
    width: 300
    height: 600
    padding: 1

    signal activateDialog(var peer)
    property alias model: listView.model

    DialogsModel {
        id: dialogsModel
        client: telegramClient
        Component.onCompleted: {
            populate()
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 4
        delegate: DialogDelegate {
            width: listView.width// - listView.leftMargin - listView.rightMargin
            onClicked: {
                dialogView.activateDialog(peer)
            }
            displayName: model.displayName
            //displayName: model.displayName ? model.displayName : model.firstName + " " + model.lastName
            unreadMessageCount: model.unreadMessageCount
            timestamp: typeof(model.lastMessage) != "undefined" ? model.lastMessage.timestamp : undefined
            lastMessage: model.lastMessage
            peer: model.peer
        }
        ScrollBar.vertical: ScrollBar {}

        model: dialogsModel
    }
}
