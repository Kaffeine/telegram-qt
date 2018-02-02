import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

Frame {
    id: dialogView
    width: 800
    height: 600

    signal activateDialog(var peer)
    property alias activatedPeer: contactsModel2.peer

    Telegram.MessageModel {
        id: contactsModel2
    }

    ListModel {
        id: contactsModel
        Component.onCompleted: {
            append({
                       firstName: "Albert",
                       lastName: "Einstein",
                       lastMessage: "Hello",
                       draft: "",
                       messageFlags: 0,
                       unreadMessageNumber: 21,
                       pinnedOrder: 1,
                       peer: Telegram.Namespace.peerFromUserId(4),
                   })
            append({
                       firstName: "David",
                       lastName: "Ed",
                       lastMessage: "Hi",
                       draft: "",
                       messageFlags: 0,
                       unreadMessageNumber: 0,
                       pinnedOrder: 2,
                       peer: Telegram.Namespace.peerFromUserId(5),
                   })
            append({
                       firstName: "Ernest",
                       lastName: "Hemingway",
                       lastMessage: "Hello",
                       draft: "",
                       messageFlags: Telegram.Namespace.MessageFlagOut,
                       unreadMessageNumber: 0,
                       pinnedOrder: -1,
                       peer: Telegram.Namespace.peerFromUserId(6),
                   })
            append({
                       firstName: "Hans",
                       lastName: "Gude",
                       lastMessage: "Hello",
                       draft: "",
                       messageFlags: Telegram.Namespace.MessageFlagOut|Telegram.Namespace.MessageFlagRead,
                       unreadMessageNumber: 0,
                       pinnedOrder: -1,
                       peer: Telegram.Namespace.peerFromUserId(7),
                   })
        }

        function indexOfPeer(peer) {
            return 1
            for (var i = 0; i < contactsModel.count; ++i) {
                if (contactsModel.get(i).peer == peer) {
                    return i;
                }
            }
            return -1
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: Theme.paddingMedium
        leftMargin: Theme.paddingMedium
        bottomMargin: Theme.paddingMedium
        rightMargin: Theme.paddingMedium
        spacing: Theme.paddingSmall
        model: contactsModel
        delegate: DialogDelegate {
            width: listView.width - listView.leftMargin - listView.rightMargin
            MouseArea {
                anchors.fill: parent
                onClicked: {
//                    contactsModel2.peer = model.peer
                    dialogView.activateDialog(model.peer)
                }
            }
        }
        ScrollBar.vertical: ScrollBar {
        }
    }

    Connections {
        target: messageSendStubProxy
        onDraftChanged: {
            var text = message
            var dateTime = new Date()
            var timeText = Qt.formatTime(dateTime, "h:mm AP")
            timeText = timeText.slice(0, -3)
            if (dateTime.getHours() >= 12) {
                timeText += " PM"
            } else {
                timeText += " AM"
            }

            var index = contactsModel.indexOfPeer(peer)
            if (index < 0) {
                return
            }
            contactsModel.set(index, { draft: text})

//            messageModel.append({
//                                    type: Telegram.MessageModel.MessageTypeText,
//                                    sender: "You",
//                                    senderPeer: Telegram.Namespace.peerFromUserId(1),
//                                    message: text,
//                                    time: timeText
//                                })
        }
    }
}
