import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0

import TelegramQt 0.2 as Telegram
import TelegramQtTheme 1.0

import Client 1.0

ApplicationWindow {
    id: window_
    visible: true
    title: qsTr("TelegramQt Example")

//    visibility: Window.Maximized

//    width: recommendedDialogWidth
//    height: recommendedDialogHeight
    width: Screen.width * 1/4
    height: Screen.height * 2/4

    readonly property int recommendedDialogWidth: width < Screen.width * 2/4 ? width : Screen.width * 2/4
    readonly property int recommendedDialogHeight: height < Screen.height * 2/4 ? height : Screen.height * 2/4

    property string appname: Qt.application.name

    QtObject {
        id: options_
        property bool localServer: true && false
    }

    Telegram.FileAccountStorage {
        id: accountStorage_
        accountIdentifier: options_.localServer ? "default-local" : "default-official"
        fileName: StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.cache/telegram-qt/secrets/" + accountIdentifier
        onSynced: console.log("Account synced")
    }

    Telegram.InMemoryDataStorage {
        id: dataStorage_
    }

    Telegram.AppInformation {
        id: appInfo_
        appId: 14617
        appHash: "e17ac360fd072f83d5d08db45ce9a121" // Telepathy-Morse app hash
        appVersion: Qt.application.version
        deviceInfo: "pc"
        osInfo: "GNU/Linux"
        languageCode: "en"
    }

    Telegram.Settings {
        id: settings_
        pingInterval: 15000
        proxy.address: "127.0.0.1"
        proxy.port: 12343
    }

    Telegram.RsaKey {
        id: localServerKey_
        fileName: StandardPaths.writableLocation(StandardPaths.TempLocation) + "/TelegramTestServer.pem"
    }

    Telegram.Settings {
        id: localSettings_
        serverOptions: [
            Telegram.ServerOption {
                address: "127.0.0.1"
                port: 10443
            }
        ]
        serverKey: localServerKey_
    }

    Telegram.Client {
        id: telegramClient_
        applicationInformation: appInfo_
        settings: options_.localServer ? localSettings_ : settings_
        dataStorage: dataStorage_
        accountStorage: accountStorage_
    }

    ImageProviderWrapper {
        id: imageProvider_
        client: telegramClient_
    }

    Timer {
        id: startupOperation_
        interval: 30
        running: true
        onTriggered: {
            if (accountStorage_.fileExists() && accountStorage_.loadData()) {
                signInOperation_.checkIn()
            } else {
                signInOperation_.startAuthentication()
            }
        }
    }

    Telegram.AuthOperation {
        id: signInOperation_
        client: telegramClient_
        onCheckInFinished: {
            console.log("check in finished:" + signedIn)
            if (signedIn) {
                mainView_.sourceComponent = mainScreenComponent_
            } else {
                // TODO: Process network errors
                startAuthentication()
            }
        }

        onStatusChanged: {
            console.log("New status:" + status)
            if (status == Telegram.AuthOperation.SignedIn) {
                mainView_.sourceComponent = mainScreenComponent_
            }
        }

        onPhoneNumberRequired: {
            mainView_.sourceComponent = loginViewComponent_
        }
        onFinished: {
            console.log("Auth operation finished. Succeeded: " + succeeded)
        }
    }

    Component {
        id: loginViewComponent_
        Item {
            Login {
                anchors.centerIn: parent
                width: recommendedDialogWidth
                height: recommendedDialogHeight
            }
        }
    }

    Component {
        id: mainScreenComponent_
        MainScreen { }
    }

    Component {
        id: loadingViewComponent_
        Frame {
            BusyIndicator {
                anchors.centerIn: parent
            }
        }
    }

    Loader {
        id: mainView_
        anchors.fill: parent
        sourceComponent: loadingViewComponent_
    }

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: window_.close()
    }
}
