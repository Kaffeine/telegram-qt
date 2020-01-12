import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

import Client 1.0

Frame {
    id: dialogView
    width: 300
    height: 600
    padding: 1

    property alias model: listView.model
    property var currentPeer: Telegram.Namespace.emptyPeer()

    DialogsModel {
        id: dialogsModel
        client: telegramClient_
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
            onClicked: dialogView.currentPeer = peer
            displayName: model.displayName
            //displayName: model.displayName ? model.displayName : model.firstName + " " + model.lastName
            unreadMessageCount: model.unreadMessageCount
            timestamp: typeof(model.lastMessage) != "undefined" ? model.lastMessage.timestamp : undefined
            lastMessage: model.lastMessage
            peer: model.peer
            pictureFileId: model.pictureFileId
            highlighted: currentPeer === peer
            isPinned: model.isPinned
            chatType: model.chatType
        }
        ScrollBar.vertical: ScrollBar {}

        model: dialogsModel
    }
}
