import QtQuick 2.7
import QtQuick.Controls 2.2

Control {
    id: control
    visible: count

    leftPadding: 4
    rightPadding: 4
    implicitWidth: metrics.width + leftPadding + rightPadding
    implicitHeight: metrics.height + topPadding + bottomPadding

    property int count

    TextMetrics {
        id: metrics
        font: unreadCountLabel.font
        text: unreadCountLabel.text
    }
    contentItem: Label {
        id: unreadCountLabel
        text: control.count
        color: "white"
    }
    background: Rectangle {
        id: background
        visible: unreadCountLabel.visible
        color: "gray"
        radius: control.leftPadding
    }
}
