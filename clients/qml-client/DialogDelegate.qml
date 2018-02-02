import QtQuick 2.7
import QtQuick.Controls 2.2
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

ItemDelegate {
    id: dialogDelegate
    height: 64
    width: 200
    property int margin: (pictureFrame.width - picture.width) / 2
    Item {
        id: pictureFrame
        height: parent.height
        width: height
        Rectangle {
            id: picture
            color: "black"
            width: 48
            height: 48
            anchors.centerIn: parent
        }
    }
    Item {
        id: details
        anchors.left: pictureFrame.right
        anchors.right: parent.right
        anchors.rightMargin: dialogDelegate.margin
        height: parent.height

        Label {
            id: nameLabel
            text: model.firstName + " " + model.lastName
            font.pixelSize: Theme.fontSizeSmall
        }
        Label {
            id: messageLabel
            anchors.bottom: parent.bottom
            text: sender + ": " + messageText
            elide: Text.ElideRight
            font.pixelSize: Theme.fontSizeTiny
            readonly property string sender: model.draft ? "Draft" : model.messageFlags & Telegram.Namespace.MessageFlagOut ? "You" : model.firstName
            readonly property string messageText: model.draft ? model.draft : model.lastMessage
        }
        Label {
            id: deliveryStatus
            anchors.right: parent.right
            text: {
                if (model.messageFlags & Telegram.Namespace.MessageFlagOut) {
                    if (model.messageFlags & Telegram.Namespace.MessageFlagRead) {
                        return "\u2713\u2713" // "\u2714"?
                    }
                    return "\u2713"
                }
                return ""
            }
            font.pixelSize: Theme.fontSizeSmall
        }
        Label {
            id: pinnedIndicator
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: "\u235f" // '\uD83D\uDCCC'?
            font.pixelSize: Theme.fontSizeSmall
            visible: model.pinnedOrder >= 0 & !unreadCountLabel.visible
        }
        Item {
            id: unreadCountIndicator
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: metrics.width + 10
            height: metrics.height
            visible: model.unreadMessageNumber
            TextMetrics {
                id: metrics
                font: unreadCountLabel.font
                text: unreadCountLabel.text
            }

            Rectangle {
                id: unreadBackground
                visible: unreadCountLabel.visible
                anchors.fill: unreadCountIndicator
                color: "gray"
                radius: 10
            }
            Label {
                id: unreadCountLabel
                text: model.unreadMessageNumber
                color: "white"
                anchors.centerIn: unreadBackground
            }
        }
    }
}
