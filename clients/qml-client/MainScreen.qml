import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

import "login"
import "dialogs"

Frame {
    id: mainScreen
    width: 800
    height: 600

    readonly property bool compactMode: contentRoot.width < 520

    property alias currentPeer: dialogView.currentPeer
    property bool hasCurrentPeer: currentPeer && currentPeer.isValid()
    onCurrentPeerChanged: {
        console.log("Activated dialog (" + currentPeer.type + ", " + currentPeer.id + ")")
    }

    Telegram.UserInfo {
        id: currentUserInfo
        client: telegramClient
        userId: currentPeer.type === Telegram.Peer.User ? currentPeer.id : 0
    }

    Telegram.ChatInfo {
        id: currentChatInfo
        client: telegramClient
        peer: currentPeer
    }

    Telegram.MessageSender {
        id: sender
        peer: currentPeer
        client: telegramClient
    }

    RowLayout {
        id: contentRoot
        anchors.fill: mainScreen.contentItem
        DialogView {
            id: dialogView
            Layout.preferredWidth: 320
            visible: compactMode ? !hasCurrentPeer : true
            Layout.fillHeight: true
            Layout.fillWidth: compactMode
        }

        Item {
            id: rightColumn
            visible: hasCurrentPeer || !compactMode
            Layout.fillHeight: true
            Layout.fillWidth: true

            PeerHeader {
                id: messagePageHeader
                width: parent.width
                height: 64
                peer: currentPeer
                spacing: rightPadding
                peerInfo: peer.type === Telegram.Peer.User ? currentUserInfo : currentChatInfo
            }

            MessageView {
                id: messageView
                width: parent.width
                anchors.top: messagePageHeader.bottom
                anchors.bottom: messageEditor.top
                peer: currentPeer
            }

            MessageEditor {
                id: messageEditor
                width: parent.width
                height: 64
                anchors.bottom: rightColumn.bottom
            }
        }
    }
}
