import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

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

    // readonly property color prefixColor: model.draft ? Material.color(Material.Red) : Material.color(Material.Blue)

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
        color: control.active ? "steelblue" : "gray"
    }
}
