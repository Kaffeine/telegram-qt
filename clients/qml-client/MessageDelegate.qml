import QtQuick 2.7
import QtQuick.Controls 2.2
import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

ItemDelegate {
    id: messageDelegate

    Telegram.UserInfo {
        id: userInfo
        client: telegramClient
        userId: model.message.sender
    }

    property var senderInfo: userInfo //userInfoProvider.getUserInfo(model.message.sender)

    contentItem: Item {
        id: content
        implicitHeight: details.height
        PeerPicture {
            id: pictureFrame
            width: 48
            height: 48
            displayName: senderInfo.displayName
        }
        Item {
            id: details
            height: {
                var contentHeight = nameLabel.height + messageLabel.implicitHeight
                if (contentHeight > pictureFrame.height) {
                    return contentHeight
                }
                return pictureFrame.height
            }
            anchors.left: pictureFrame.right
            anchors.right: content.right

            Label {
                id: nameLabel
                text: senderInfo.displayName
                font.bold: true
                anchors.left: details.left
                anchors.leftMargin: messageDelegate.spacing
            }
            Label {
                id: messageLabel
                anchors.top: nameLabel.bottom
                anchors.left: details.left
                anchors.leftMargin: messageDelegate.spacing
                anchors.right: details.right
                text: model.message.text
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: Theme.fontSizeTiny
            }
            Label {
                id: deliveryStatus
                anchors.bottom: details.bottom
                anchors.right: details.right
                readonly property string time: model.time
                text: {
                    if (model.messageFlags & Telegram.Namespace.MessageFlagOut) {
                        if (model.messageFlags & Telegram.Namespace.MessageFlagRead) {
                            return "\u2713\u2713 " + time // "\u2714"?
                        }
                        return "\u2713 " + time
                    }
                    return time
                }
                font.pixelSize: Theme.fontSizeTiny - 4
            }
        }
    }
}
