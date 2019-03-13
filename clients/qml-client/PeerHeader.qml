import QtQuick 2.9
import QtQuick.Controls 2.2

Frame {
    id: root

    property alias showPicture: peerPicture.visible
    property var peer
    property var peerInfo

    Row {
        spacing: root.spacing

        PeerPicture {
            id: peerPicture
            height: 42
            width: height
            anchors.verticalCenter: parent.verticalCenter

            displayName: peerInfo.displayName
            peer: root.peer
        }

        InlineHeader {
            id: displayNameLabel
            text: peerInfo.displayName
        }
    }
}
