import QtQuick 2.7
import QtQuick.Controls 2.2
import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

ItemDelegate {
    id: root_

    property var fromUserId
    property int messageFlags
    property var sentTimestamp

    Telegram.PeerInfo {
        id: peerInfo_
        client: telegramClient_
        userId: root_.fromUserId
    }

    contentItem: Item {
        id: content
        implicitHeight: details.height
        PeerPicture {
            id: pictureFrame
            sizePx: Theme.iconSizeMedium
            peer: peerInfo_.peer
            displayName: peerInfo_.displayName
            pictureFileId: peerInfo_.pictureFileId
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
                text: peerInfo_.displayName
                font.bold: true
                anchors.left: details.left
                anchors.leftMargin: root_.spacing
            }
            Label {
                id: messageLabel
                anchors.top: nameLabel.bottom
                anchors.left: details.left
                anchors.leftMargin: root_.spacing
                anchors.right: details.right
                text: root_.text
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: Theme.fontSizeTiny
            }
            Label {
                id: deliveryStatus
                anchors.bottom: details.bottom
                anchors.right: details.right
                readonly property string time: Qt.formatTime(root_.sentTimestamp)
                text: {
                    if (root_.messageFlags & Telegram.Namespace.MessageFlagOut) {
                        if (root_.messageFlags & Telegram.Namespace.MessageFlagRead) {
                            return "\u2713\u2713 " + time // "\u2714"?
                        }
                        return "\u2713 " + time
                    }
                    return time
                }
                font.pixelSize: Theme.fontSizeTiny
            }
        }
    }
}
