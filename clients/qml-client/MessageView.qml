import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 0.2 as Telegram
import Client 1.0 as Telegram
import TelegramQtTheme 1.0

Frame {
    id: messageView
    width: 800
    height: 600
    property alias peer: messagesModel.peer
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0

    Telegram.MessagesModel {
        id: messagesModel
        client: telegramClient
    }

//    Telegram.PeerInfoProvider {
//        id: userInfoProvider
//        client: telegramClient
//    }

    Telegram.MessageSender {
        id: sender
        client: telegramClient
        peer: messagesModel.peer
    }

    Component {
        id: messageDelegate
        MessageDelegate {
        }
    }

    Component {
        id: newDayDelegate
        ServiceMessageDelegate {
            text: Qt.formatDate(model.timestamp, Qt.DefaultLocaleLongDate)
        }
    }
    Component {
        id: serviceActionDelegate
        ServiceMessageDelegate {
            text: mkLinkToPeer(model.actor) + " added " + mkLinkToPeer(model.users)
            plainText: model.actor + " added " + model.users
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

    MessageListView {
        id: listView
        anchors.fill: parent
        model: messagesModel
        delegate: Item {
            property var itemModel: model
            width: loader.width
            height: loader.height
            Loader {
                id: loader
                width: listView.width
                property var model: parent.itemModel // inject 'model' to the loaded item's context

//                Telegram.UserInfo {
//                    id: userInfo
//                    client: telegramClient
//                    provider: infoPull
//                    //contactId: model.message.sender
//                }

                sourceComponent: {
                    if (model.eventType == Telegram.Event.Type.NewDay) {
                        return newDayDelegate
                    } else if (model.eventType == Telegram.Event.Type.Message) {
                        return messageDelegate
                    } else if (model.eventType == Telegram.Event.Type.ServiceAction) {
                        return serviceActionDelegate
                    }
                    return messageDelegate
                }
            }
        }
    }

    onPeerChanged: {
        readTimer.start()
    }

    Timer {
        id: readTimer
        interval: 500
        onTriggered: {
            messagesModel.readAllMessages()

            if (peer.isValid()) {
                console.log("Model peer is valid!")
            }
        }
    }
}
