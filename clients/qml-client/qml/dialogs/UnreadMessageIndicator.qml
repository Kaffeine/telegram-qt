import QtQuick 2.7
import QtQuick.Controls 2.2

Label {
    id: control
    visible: count

    leftPadding: 2
    rightPadding: 2
    topPadding: 0
    bottomPadding: 0
    //implicitWidth: metrics.width + leftPadding + rightPadding
    //implicitHeight: metrics.height + topPadding + bottomPadding

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    text: control.count
    color: "white"

    property int count
    property bool active

    TextMetrics {
        id: metrics
        font: control.font
        text: control.text
    }

    background: Rectangle {
        id: background
        radius: 4
        color: active ? "steelblue" : "gray"
    }
}
