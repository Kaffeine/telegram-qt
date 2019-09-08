import QtQuick 2.0
import QtQuick.Layouts 1.3
import TelegramQtTheme 1.0

ColumnLayout {
    id: authScreen
    function accept() {
        console.log("Accepted: " + objectName)
        submit()
    }
    signal submit() // A signal to submit the item data
    signal activate() // A signal to activate the item context

    property string title
    property string description

    spacing: Theme.paddingMedium

    Text {
        id: pageHeader
        text: authScreen.title
        font.pixelSize: Theme.fontSizeLarge
        font.bold: true
        Layout.alignment: Qt.AlignRight
    }

    Rectangle {
        Layout.fillWidth: true
        height: 3
        color: Theme.highlightBackgroundColor
    }
    Text {
        id: descriptionText
        text: authScreen.description
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        font.pixelSize: Theme.fontSizeSmall
        Layout.maximumWidth: authScreen.width
        visible: text
    }
}
