import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQtTheme 1.0

AuthScreen {
    id: baseColumn
    objectName: "AuthEnterPasswordComponent"
    width: loginStack.width
    title: qsTr("Password")
    description: qsTr("You have enabled Two-Step Verification, so your account is protected with an additional password.")
    signal submitPassword(string password)

    onActivate: passwordField.forceActiveFocus()
    onSubmit: submitPassword(passwordField.text)

    TextField {
        id: passwordField
        echoMode: TextInput.Password
        inputMethodHints: Qt.ImhHiddenText | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
        placeholderText: qsTr("Enter the password")
        font.pixelSize: Theme.fontSizeMedium
        onAccepted: baseColumn.accept()
    }
    Text {
        readonly property string forgotUrl: "forgotPassword"
        textFormat: Text.RichText
        text: "<a href=\"" + forgotUrl + "\">Forgot password?</a>"
        onLinkActivated: {
            if (link == forgotUrl) {
                signInOperation.recovery()
            }
        }
        font.pixelSize: Theme.fontSizeSmall
    }
    Item {
        id: spacer
        Layout.fillHeight: true
    }
}
