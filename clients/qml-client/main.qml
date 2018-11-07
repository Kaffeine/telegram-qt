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

    property string appname: Qt.application.name

    QtObject {
        id: options
        property bool localServer: true && false
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
        accountIdentifier: options.localServer ? "default-local" : "default-official"
        fileName: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.cache/telegram-qt/secrets/" + accountIdentifier
        onSynced: console.log("Account synced")
    }

    Telegram.InMemoryDataStorage {
        id: dataStorage
    }

    Telegram.AppInformation {
        id: appInfo
        appId: 14617
        appHash: "e17ac360fd072f83d5d08db45ce9a121" // Telepathy-Morse app hash
        appVersion: "0.2"
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
        proxy.address: "127.0.0.1"
        proxy.port: 12343
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
                port: 11441
            }
        ]
        serverKey: localServerKey
    }

    Telegram.Client {
        id: telegramClient
        applicationInformation: appInfo
        settings: options.localServer ? localSettings : settings
        dataStorage: dataStorage
        accountStorage: accountStorage
    }

    Timer {
        id: startupOperation
        interval: 30
        running: true
        onTriggered: {
            if (accountStorage.fileExists() && accountStorage.loadData()) {
                console.log("CheckIn")
                signInOperation.checkIn()
            } else {
                console.log("SignIn")
                signInOperation.signIn()
            }
        }
    }

    Telegram.AuthOperation {
        id: signInOperation
        client: telegramClient
        onCheckInFinished: {
            console.log("check in finished:" + signedIn)
            if (signedIn) {
                window.currentView = mainScreen
            } else {
                // TODO: Process network errors
                signIn()
            }
        }

        onStatusChanged: {
            console.log("New status:" + status)
            if (status == Telegram.AuthOperation.SignedIn) {
                window.currentView = mainScreen
            }
        }

        onPhoneNumberRequired: {
            window.currentView = loginScreen
        }
        onFinished: {
            console.log("Auth operation finished. Succeeded: " + succeeded)
        }
    }

    property Item currentView: busyScreen

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

    Loader {
        id: busyScreen
        active: visible
        visible: window.currentView === busyScreen
        anchors.fill: parent
        sourceComponent: Frame {
            BusyIndicator {
                anchors.centerIn: parent
            }
        }
    }

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: window.close()
    }

//    Pane {
//        anchors.fill: parent
//        ListView {
//            anchors.fill: parent
//            model: accountHelper.accounts
//            delegate: ItemDelegate {
//                width: parent.width
//                height: 64
//                text: modelData
//            }
//        }
//    }
}
