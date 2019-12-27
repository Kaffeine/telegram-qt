import QtQuick 2.6
import QtQuick.Controls.Material 2.0

Item {
    id: root_
    height: sizePx
    width: sizePx

    property real sizePx: 42
    property string displayName
    property var peer

    Rectangle {
        id: placeholder_
        visible: root_.displayName
        readonly property var colors: [
            Material.Purple,
            Material.DeepPurple,
            Material.Blue,
            Material.LightBlue,
            Material.Cyan,
            Material.Teal,
            Material.LightGreen,
            Material.Lime,
            Material.Amber,
            Material.Orange,
            Material.DeepOrange,
            Material.Brown,
            Material.Grey,
            Material.BlueGrey,
        ]
        function getColor(username) {
            return colors[Qt.md5(username).charCodeAt(0) % colors.length]
        }

        color: {
            if (!peer) {
                return "white"
            }
            if (!peer.isValid()) {
                return "lightgray"
            }
            Material.color(getColor(root.peer.toString()))
        }
        anchors.fill: parent
        border.color: "black"
        border.width: 1

        Text {
            anchors.centerIn: parent
            font.pixelSize: parent.width * 0.8
            text: root_.displayName ? root_.displayName[0] : ""
            font.capitalization: Font.AllUppercase
        }
    }
}
