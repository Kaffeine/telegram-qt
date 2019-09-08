import QtQuick 2.7
import QtQuick.Controls 2.2
import TelegramQtTheme 1.0

Item {
    id: delegate
    height: 32
    property alias text: label.text
    property string plainText: text
    property alias textFormat: label.textFormat
    property alias textColor: label.color
    property alias linkColor: label.linkColor
    signal linkActivated(string link)
    TextMetrics {
        id: metrics
        font: label.font
        text: delegate.plainText
    }

    Rectangle {
        id: background
        visible: label.visible
        anchors.centerIn: parent
        width: metrics.width + 20
        height: metrics.height + 10
        color: Theme.highlightBackgroundColor
        radius: 10
    }
    Text {
        id: label
        color: "white"
        anchors.centerIn: background
        onLinkActivated: delegate.linkActivated(link)
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        }
    }
}
