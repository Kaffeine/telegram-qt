import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

Frame {
    id: messageView
    width: 800
    height: 600
    property alias peer: messageModel2.peer

    ListModel {
        id: messageModel
        Component.onCompleted: {
            append({
                       type: Telegram.MessageModel.MessageTypeNewDay,
                       text: "January 14",
                   })
            append({
                       type: Telegram.MessageModel.MessageTypeText,
                       sender: "Andy Hall",
                       senderPeer: Telegram.Namespace.peerFromUserId(3),
                       message: "Well, I don't know about that.",
                       time: "3:57 PM",
                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
                   })
            append({
                       type: Telegram.MessageModel.MessageTypeServiceAction,
                       sender: "Andy Hall",
                       users: "Daniel Ash",
                       time: "4:33 PM",
                   })
            append({
                       type: Telegram.MessageModel.MessageTypeText,
                       sender: "Daniel Ash",
                       senderPeer: Telegram.Namespace.peerFromUserId(2),
                       message: "It's a joke we were joking around, you see? We totally got you!",
                       time: "4:34 PM",
                       messageFlags: 1, // Telegram.Namespace.MessageFlagRead
                   })
            append({
                       type: Telegram.MessageModel.MessageTypeNewDay,
                       text: "January 16",
                   })
            append({
                       sender: "You",
                       senderPeer: Telegram.Namespace.peerFromUserId(1),
                       message: "We work hard, we play hard",
                       time: "2:27 PM",
                       messageFlags: 3,//Telegram.Namespace.MessageFlagOut|Telegram.Namespace.MessageFlagRead
                   })

        }
    }
    Connections {
        target: messageSendStubProxy
        onMessageSent: {
            var text = message
            var dateTime = new Date()
            var timeText = Qt.formatTime(dateTime, "h:mm AP")
            timeText = timeText.slice(0, -3)
            if (dateTime.getHours() >= 12) {
                timeText += " PM"
            } else {
                timeText += " AM"
            }

            messageModel.append({
                                    type: Telegram.MessageModel.MessageTypeText,
                                    sender: "You",
                                    senderPeer: Telegram.Namespace.peerFromUserId(1),
                                    message: text,
                                    time: timeText
                                })
        }
    }

    Component {
        id: messageDelegate
        MessageDelegate {
        }
    }

    Component {
        id: newDayDelegate
        ServiceMessageDelegate {
            text: model.text
        }
    }
    Component {
        id: serviceActionDelegate
        ServiceMessageDelegate {
            text: mkLinkToPeer(model.sender) + " added " + mkLinkToPeer(model.users)
            plainText: model.sender + " added " + model.users
            textFormat: Text.StyledText
            linkColor: textColor
            function mkLinkToPeer(peer) {
                return "<a href=\"" + peer + "\">" + peer + "</a>"
            }
            onLinkActivated: {
                console.log("Link activated: " + link)
            }
        }
    }

    Telegram.MessageModel {
        id: messageModel2
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: Theme.paddingMedium
        leftMargin: Theme.paddingMedium
        bottomMargin: Theme.paddingMedium
        rightMargin: Theme.paddingMedium
        spacing: Theme.paddingSmall
        model: messageModel
        delegate: Loader {
            property var model: listView.model.get(index)
            width: listView.width - listView.leftMargin - listView.rightMargin
            sourceComponent: {
                switch (model.type) {
                case Telegram.MessageModel.MessageTypeNewDay:
                    return newDayDelegate
                case Telegram.MessageModel.MessageTypeServiceAction:
                    return serviceActionDelegate
                default:
                    return messageDelegate
                }
            }
        }
    }
}
