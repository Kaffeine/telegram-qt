import QtQuick 2.9
import QtQuick.Controls 2.2

import TelegramQtTheme 1.0

Frame {
    id: root

    property alias showPicture: peerPicture.visible
    property var peerInfo

    Row {
        spacing: root.spacing

        PeerPicture {
            id: peerPicture
            sizePx: Theme.iconSizeMedium
            anchors.verticalCenter: parent.verticalCenter

            displayName: peerInfo.displayName
            peer: root.peerInfo.peer
        }

        InlineHeader {
            id: displayNameLabel
            text: peerInfo.displayName
        }
    }
}
