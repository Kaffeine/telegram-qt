import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQtTheme 1.0

AuthScreen {
    id: baseColumn
    objectName: "AuthEnterCodeComponent"
    width: loginStack.width
    title: qsTr("Your code")
    description: qsTr("We have sent an SMS with an activation code to your phone +" + signInOperation_.phoneNumber)
    signal submitAuthCode(string code)

    onActivate: authCodeField.forceActiveFocus()
    onSubmit: submitAuthCode(authCodeField.text)

    TextField {
        id: authCodeField
        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: qsTr("Enter the code")
        font.pixelSize: Theme.fontSizeMedium
        selectByMouse: true
        onAccepted: baseColumn.accept()
        Layout.fillWidth: true
    }
    Item {
        id: spacer
        Layout.fillHeight: true
    }
}
