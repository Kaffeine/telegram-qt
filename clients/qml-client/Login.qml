import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

import "login"

Frame {
    id: loginScreen
    width: 800
    height: 600

    ListModel {
        id: phoneCodeModel
        ListElement {
            code: "44"
            country: "United Kingdom"
            length: 10
        }
        ListElement {
            code: "7"
            country: "Russian Federation"
            length: 10
        }
        ListElement {
            code: "34"
            country: "Spain"
            length: 9 // 6 or 7, followed by 8 digits
        }
        ListElement {
            code: ""
            country: "Custom"
            length: 12
        }
    }

    Connections {
        target: signInOperation
        onAuthCodeRequired: loginStack.replace("login/EnterCode.qml")
        onPasswordRequired: loginStack.replace("login/EnterPassword.qml")
        onFinished: console.log("Sign in finished:" + succeeded)
    }

    StackView {
        id: loginStack
        anchors.fill: parent
        anchors.margins: Theme.paddingMedium
        initialItem: "login/EnterPhone.qml"
        property int current: 0
        onCurrentItemChanged: {
            if (currentItem) {
                currentItem.activate()
            }
        }
        function next() { currentItem.accept() }

        Connections {
            target: loginStack.currentItem
            ignoreUnknownSignals: true
            onSubmitAuthCode: signInOperation.submitAuthCode(code)
            onSubmitPassword: signInOperation.submitPassword(password)
            onSubmitPhoneNumber: {
                signInOperation.phoneNumber = phoneNumber
                signInOperation.start()
            }
        }
        opacity: signInOperation.busy ? 0 : 1
        Behavior on opacity { NumberAnimation { } }
    }

    Button {
        id: next
        text: "Next"
        anchors.bottom: loginScreen.contentItem.bottom
        anchors.bottomMargin: 80
        anchors.horizontalCenter: loginScreen.contentItem.horizontalCenter
        onClicked: loginStack.next()
    }

    BusyIndicator {
        running: signInOperation.busy
        anchors.centerIn: parent
    }
}
