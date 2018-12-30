import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQtTheme 1.0

AuthScreen {
    id: baseColumn
    objectName: "AuthEnterPhoneComponent"
    width: loginStack.width
    title: qsTr("Your phone")
    description: qsTr("Please confirm your country code and enter your phone number")
    signal submitPhoneNumber(string phoneNumber)

    onActivate: countryBox.forceActiveFocus()
    onSubmit: submitPhoneNumber(countryBox.currentCode + phoneNumberField.text)

    ComboBox {
        id: countryBox
        model: phoneCodeModel
        textRole: "country"
        Layout.preferredWidth: countryBox.implicitWidth * 2

        MouseArea {
            hoverEnabled: false
            acceptedButtons: Qt.NoButton
            anchors.fill: parent
            onWheel: {
                if (wheel.angleDelta.y < 0) {
                    parent.incrementCurrentIndex()
                } else {
                    parent.decrementCurrentIndex()
                }
            }
        }
        readonly property string currentCode: phoneCodeModel.get(countryBox.currentIndex).code
        readonly property var length: phoneCodeModel.get(countryBox.currentIndex).length
    }
    Item {
        id: row
        Layout.preferredWidth: countryBox.width
        height: phoneNumberField.implicitHeight
        Text {
            id: phoneCode
            text: "+" + countryBox.currentCode
            font: phoneNumberField.font
            anchors.top: phoneNumberField.top
            anchors.topMargin: phoneNumberField.topPadding
            anchors.left: parent.left
        }
        TextField {
            id: phoneNumberField
            inputMethodHints: Qt.ImhDigitsOnly
            selectByMouse: true
            validator: RegExpValidator { regExp: /\d*/ }
            maximumLength: countryBox.length
            focus: true
            font.pixelSize: Theme.fontSizeSmall
            anchors.left: phoneCode.right
            anchors.right: parent.right
            onAccepted: baseColumn.accept()
        }
    }
    Item {
        id: spacer
        Layout.fillHeight: true
    }
}

