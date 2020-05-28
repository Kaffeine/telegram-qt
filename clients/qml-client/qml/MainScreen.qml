import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

import "login"
import "dialogs"

Item {
    id: mainScreen
    width: 800
    height: 600

    readonly property bool compactMode: contentRoot.width < 520

    property var currentPeer: Telegram.Namespace.emptyPeer()
    //property alias currentPeer: dialogView.currentPeer
    property bool hasCurrentPeer: currentPeer && currentPeer.isValid()
    onCurrentPeerChanged: {
        console.log("Activated dialog (" + currentPeer.type + ", " + currentPeer.id + ")")
    }

    Telegram.PeerInfo {
        id: currentPeerInfo_
        client: telegramClient_
        peer: currentPeer
    }

    Telegram.MessageSender {
        id: sender
        peer: currentPeer
        client: telegramClient_
    }

    RowLayout {
        id: contentRoot
        anchors.fill: mainScreen

        ColumnLayout {
            id: leftColumn_
            Layout.preferredWidth: 320
            visible: compactMode ? !hasCurrentPeer : true
            Layout.fillHeight: true
            Layout.fillWidth: compactMode

            TextField {
                id: searchInput_
                placeholderText: qsTr("Search")
                Layout.fillWidth: true
            }

            DialogView {
                id: dialogView
                Layout.fillWidth: true
                Layout.fillHeight: true

                onCurrentPeerChanged: {
                    telegramClient_.messagingApi.createChat2(searchInput_.text, currentPeer)
                }
            }
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
                spacing: rightPadding
                peerInfo: currentPeerInfo_
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
