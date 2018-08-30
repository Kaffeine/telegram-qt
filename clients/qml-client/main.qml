import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0
import TelegramQt 1.0 as Telegram
import TelegramQtTheme 1.0

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("TelegramQt Example")

//    visibility: Window.Maximized

//    width: recommendedDialogWidth
//    height: recommendedDialogHeight
    width: Screen.width * 1/4
    height: Screen.height * 2/4

    readonly property int recommendedDialogWidth: width < Screen.width * 2/4 ? width : Screen.width * 2/4
    readonly property int recommendedDialogHeight: height < Screen.height * 2/4 ? height : Screen.height * 2/4

//    header: Label {
//        text: view.currentItem.title
//        horizontalAlignment: Text.AlignHCenter
//    }


    QtObject {
        id: options
//        property bool localServer: true
        property bool localServer: false
    }

    ListModel {
        id: accountModel
        ListElement {
            account: "123456"
            encrypted: true
            lastOnline: "Yesterday"
            avatar: "red"
        }
    }

    Telegram.FileAccountStorage {
        id: accountStorage
////        property string authKey
////        property string accountIdentifier
////        property int authId
////        property int deltaTime
//        property string directory: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.cache/telepathy-morse/secrets"
//        // accountIdentifier: phoneNumberField.text
//        // format: AccountSecretHelper.FormatBinary
    }

    Telegram.AccountSecretHelper {
        id: accountHelper
//        directory: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.cache/telepathy-morse/secrets"
        directory: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.cache/morse/secrets"
        onAccountsChanged: {
            console.log("Accounts:" + accounts)
            if (accounts.length > 0) {
                account = accounts[0]
            }
            accountStorage.fileName = directory + "/" + account
            accountStorage.loadData()
        }
    }
    Telegram.InMemoryDataStorage {
        id: dataStorage
    }

    Telegram.AppInformation {
        id: appInfo
        appId: 14617
        appHash: "e17ac360fd072f83d5d08db45ce9a121" // Telepathy-Morse app hash
        appVersion: "0.1"
        deviceInfo: "pc"
        osInfo: "GNU/Linux"
        languageCode: "en"
    }
    Telegram.RsaKey {
        id: officialServerKey
        loadDefault: true
    }
    Telegram.Settings {
        id: settings
        pingInterval: 15000
        // proxy.address: "192.168.0.103"
        // proxy.port: 9050
        serverOptions: [
            Telegram.ServerOption {
                address: "149.154.175.50"
                port: 443
            },
            Telegram.ServerOption {
                address: "149.154.167.51"
                port: 443
            }
        ]
        serverKey: officialServerKey
    }

    Telegram.RsaKey {
        id: localServerKey
        fileName: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/TelegramServer/public_key.pem"
    }
    Telegram.Settings {
        id: localSettings
        serverOptions: [
            Telegram.ServerOption {
                address: "127.0.0.1"
                port: 11443
            }
        ]
        serverKey: localServerKey
    }

    Telegram.Client {
        id: telegramClient
        applicationInformation: appInfo
        settings: options.localServer ? localSettings : settings
        readonly property bool hasAccount: accountHelper.accounts
        dataStorage: dataStorage
        accountStorage: accountStorage

        onSignedInChanged: {
            if (signedIn) {
                window.currentView = mainScreen
            }
        }
    }

    Timer {
        id: startupOperation
        interval: 50
        running: true
        onTriggered: {
//            window.currentView = mainScreen; return
            if (accountHelper.account) {
                restoreSessionOperation.phoneNumber = accountHelper.account
                restoreSessionOperation.start()
            } else {
                window.currentView = loginScreen
            }
            signInOperation.start()
        }
    }

    Telegram.AuthOperation {
        id: signInOperation
        target: telegramClient
        onPhoneNumberRequired: {
            window.currentView = loginScreen
        }
        onFinished: {
            console.log("Sign in finished:" + succeed)
        }
    }

    property Item currentView

    Loader {
        id: loginScreen
        anchors.centerIn: parent
        width: recommendedDialogWidth
        height: recommendedDialogHeight
        visible: window.currentView === loginScreen
        active: visible
        sourceComponent: Login {
        }
    }

    QtObject {
        id: messageSendStubProxy
        signal messageSent(string message, var peer)
        onMessageSent: {
            var typeText = (peer.type == 0 ? "User" : "Chat")
            console.log("Message to " + typeText + " " + peer.id)
        }
        signal draftChanged(string message, var peer)
    }

    Loader {
        id: mainScreen
        active: visible
        visible: window.currentView === mainScreen
        anchors.fill: parent
        sourceComponent: MainScreen {
        }
    }

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: window.close()
    }
}
