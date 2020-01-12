import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.1

import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

import ".."

ItemDelegate {
    id: dialogDelegate
    width: 200

    property string displayName
    property string pictureFileId
    property int chatType
    property int unreadMessageCount
    property var timestamp
    property var peer
    property var draft
    property bool isPinned
    readonly property bool isGroupChat: (chatType === Telegram.Namespace.ChatTypeGroup)
                                        || (chatType === Telegram.Namespace.ChatTypeMegaGroup)
    property var lastMessage

    property bool debugGeometry: false
    property int smallSpacing: spacing / 2

    contentItem: Item {
        id: content
        implicitHeight: Math.max(peerPicture.height, contentColumn.height)

        PeerPicture {
            id: peerPicture
            sizePx: Theme.iconSizeMedium
            anchors.verticalCenter: parent.verticalCenter
            visible: content.width > width * 4

            displayName: dialogDelegate.displayName
            peer: dialogDelegate.peer
            pictureFileId: dialogDelegate.pictureFileId
        }

        Item {
            id: contentColumn
            anchors.left: peerPicture.visible ? peerPicture.right : content.left
            anchors.leftMargin: peerPicture.visible ? dialogDelegate.spacing : 0
            anchors.right: content.right
            anchors.top: content.top
            anchors.bottom: content.bottom

            Item {
                anchors.top: parent.top
                width: parent.width
                height: displayNameLabel.implicitHeight
                RowLayout {
                    id: displayNameRow_
                    spacing: dialogDelegate.smallSpacing
                    height: displayNameLabel.implicitHeight
                    Rectangle {
                        id: chatTypeIcon
                        radius: 4
                        width: height
                        height: displayNameLabel.height
                        visible: false // func(dialogDelegate.chatType)
                        color: "blue"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    InlineHeader {
                        id: displayNameLabel
                        text: dialogDelegate.displayName
                        Layout.fillWidth: true
                    }

                    anchors.left: parent.left
                    anchors.right: deliveryIcon.visible ? deliveryIcon.left : lastMessageDateTime.left
                    anchors.rightMargin: dialogDelegate.spacing
                }

                Rectangle {
                    id: deliveryIcon
                    width: height
                    height: lastMessageDateTime.font.pixelSize
                    color: "green"
                    visible: !draft && (typeof(dialogDelegate.lastMessage) != "undefined" && dialogDelegate.lastMessage.flags & 1)
                    anchors.right: lastMessageDateTime.left
                    anchors.rightMargin: dialogDelegate.smallSpacing
                    anchors.verticalCenter: parent.verticalCenter
                }

                Label {
                    id: lastMessageDateTime
                    color: "gray"
                    horizontalAlignment: Qt.AlignRight
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 14

                    function formatRelativeCurrentDay(date)
                    {
                        var referenceDate = new Date
                        referenceDate.setHours(0,0,0,0)
                        if (dialogDelegate.timestamp >= referenceDate) {
                            // Today
                            return dialogDelegate.timestamp.toLocaleTimeString(Qt.locale(), Locale.ShortFormat);
                        }
                        referenceDate.setDate(referenceDate.getDate() - 1)
                        if (dialogDelegate.timestamp >= referenceDate) {
                            return qsTr("Yesterday")
                        }
                        referenceDate.setDate(referenceDate.getDate() - 6)
                        if (dialogDelegate.timestamp >= referenceDate) {
                            // Less than a week ago
                            return dialogDelegate.timestamp.toLocaleString(Qt.locale(), "ddd")
                        }
                        return dialogDelegate.timestamp.toLocaleDateString(Qt.locale(), Locale.ShortFormat)
                    }

                    text: typeof(dialogDelegate.timestamp) === "undefined" ? "<none>" : formatRelativeCurrentDay(dialogDelegate.timestamp)
                }
                Rectangle {
                    opacity: 0.1
                    color: "blue"
                    anchors.fill: parent
                    visible: dialogDelegate.debugGeometry
                }
            }

            Item {
                anchors.bottom: parent.bottom
                width: contentColumn.width
                height: messagePreviewLabel.implicitHeight

                Label {
                    id: messagePreviewLabel
                    elide: Text.ElideRight
                    text: prefixStyledText + contentText
                    anchors.left: parent.left
                    anchors.right: dialogIndicator.visible ? dialogIndicator.left : parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    maximumLineCount: 1

                    readonly property string prefixStyledText: prefixText ? "<font color=\"" + prefixColor + "\">" + prefixText + "</font>" : ""
                    readonly property color prefixColor: model.draft ? "red" : palette.link
                    readonly property string prefixText: {
                        if (model.draft) {
                            return "Draft: "
                        }
                        if (typeof(model.activeMessageActions) != "undefined") {
                            return ""
                        }
                        if (lastMessage) {
                            if (lastMessage.flags & 1) {
                                return "You: "
                            }
                            if (dialogDelegate.isGroupChat) {
                                return lastMessage.senderName + ": "
                            }
                        }
                        return ""
                    }

                    readonly property string contentText: {
                        if (model.draft)
                            return model.draft

                        var emphasedText
                        if (typeof(model.activeMessageActions) != "undefined" && model.activeMessageActions.count > 0) {
                            var firstAction = model.activeMessageActions.get(0)
                            if (firstAction.type === "typing") {
                                emphasedText = "..." + firstAction.contact + " is typing"
                            }
                            if (emphasedText) {
                                return "<font color=\"" + emphasedContentColor + "\">" + emphasedText + "</font>"
                            }
                            // Ignore unknown actions
                        }
                        if (typeof(lastMessage) === "undefined") {
                            return ""
                        }
                        var text = lastMessage.text
                        if (lastMessage.type === Telegram.Namespace.MessageTypeText) {
                            return text
                        }
                        if (lastMessage.type === Telegram.Namespace.MessageTypeWebPage) {
                            return text
                        }
                        if (lastMessage.type === Telegram.Namespace.MessageTypePhoto) {
                            emphasedText = "Photo"
                        } else if (lastMessage.type === Telegram.Namespace.MessageTypeVideo) {
                            emphasedText = "Video"
                        } else if (lastMessage.type === Telegram.Namespace.MessageTypeSticker) {
                            emphasedText = "Sticker"
                        } else if (lastMessage.type === Telegram.Namespace.MessageTypeAnimation) {
                            emphasedText = "GIF"
                        } else if (lastMessage.type === Telegram.Namespace.MessageTypeDocument) {
                            emphasedText = "File"
                        } else {
                            // Do *not* ignore unknown messages
                            emphasedText = "Unsupported content" + lastMessage.type
                        }
                        if (text.length !== 0) {
                            emphasedText += ", "
                        }

                        return "<font color=\"" + emphasedContentColor + "\">" + emphasedText + "</font>" + text
                    }
                    readonly property color emphasedContentColor: palette.link
                }

                Flow {
                    id: dialogIndicator
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter

                    UnreadMessageIndicator {
                        id: unreadIndicator
                        count: dialogDelegate.unreadMessageCount
                    }

                    Text {
                        id: pinnedIndicator
                        visible: dialogDelegate.isPinned && (unreadIndicator.count == 0)
                        text: "<pin>"
                        color: "gray"
                        font: lastMessageDateTime.font
                        height: font.pixelSize
                        textFormat: Text.PlainText
                    }
                }

                Rectangle {
                    opacity: 0.1
                    color: "red"
                    anchors.fill: parent
                    visible: dialogDelegate.debugGeometry
                }
            }
        }
    }
}
