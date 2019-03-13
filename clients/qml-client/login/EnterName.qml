import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQtTheme 1.0

AuthScreen {
    id: baseColumn
    objectName: "AuthEnterNameComponent"
    width: loginStack.width
    title: qsTr("Your name")
    description: qsTr("The phone number is not registered. Enter your name to continue.")
    signal submitName(string firstName, string lastName)

    onActivate: firstNameInput.forceActiveFocus()
    onSubmit: submitName(firstNameInput.text, lastNameInput.text)

    TextField {
        id: firstNameInput
        placeholderText: qsTr("First name")
        font.pixelSize: Theme.fontSizeMedium
        onAccepted: lastNameInput.focus = true
        Layout.fillWidth: true
    }
    TextField {
        id: lastNameInput
        placeholderText: qsTr("Last name")
        font.pixelSize: Theme.fontSizeMedium
        onAccepted: baseColumn.accept()
        Layout.fillWidth: true
    }
    Item {
        id: spacer
        Layout.fillHeight: true
    }
}
