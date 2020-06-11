#ifndef TEST_CLIENT_UTILS_HPP
#define TEST_CLIENT_UTILS_HPP

#include "TestAuthProvider.hpp"
#include "TestUserData.hpp"
#include "TestUtils.hpp"

#include "test_server_data.hpp"

#include "AccountStorage.hpp"
#include "CAppInformation.hpp"
#include "Client.hpp"
#include "ClientSettings.hpp"
#include "ConnectionApi.hpp"
#include "DataStorage.hpp"

#include "Operations/ClientAuthOperation.hpp"

#include <QSignalSpy>

namespace Telegram {

namespace Test {

void setupAppInfo(Client::AppInformation *appInfo)
{
    appInfo->setAppId(14617);
    appInfo->setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo->setAppVersion(QLatin1String("0.1"));
    appInfo->setDeviceInfo(QLatin1String("pc"));
    appInfo->setOsInfo(QLatin1String("GNU/Linux"));
    appInfo->setLanguageCode(QLatin1String("en"));
}

void setupClientHelper(Telegram::Client::Client *client, const UserData &userData, const Telegram::RsaKey &serverPublicKey,
                       const Telegram::DcOption clientDcOption)
{
    Telegram::Client::AccountStorage *accountStorage = new Telegram::Client::AccountStorage(client);
    accountStorage->setPhoneNumber(userData.phoneNumber);
    accountStorage->setDcInfo(clientDcOption);
    Telegram::Client::Settings *clientSettings = new Telegram::Client::Settings(client);
    Telegram::Client::InMemoryDataStorage *dataStorage = new Telegram::Client::InMemoryDataStorage(client);
    client->setAppInformation(new Client::AppInformation(client));
    setupAppInfo(client->appInformation());
    client->setSettings(clientSettings);
    client->setAccountStorage(accountStorage);
    client->setDataStorage(dataStorage);
    QVERIFY(clientSettings->setServerConfiguration({clientDcOption}));
    QVERIFY(clientSettings->setServerRsaKey(serverPublicKey));
}

void setupClientHelper(Telegram::Client::Client *client, const UserData &userData, const Telegram::RsaKey &serverPublicKey,
                       const Telegram::DcOption clientDcOption, const Telegram::Client::Settings::SessionType sessionType)
{
    setupClientHelper(client, userData, serverPublicKey, clientDcOption);
    client->settings()->setPreferedSessionType(sessionType);
}

void signInHelper(Telegram::Client::Client *client, const UserData &userData, Telegram::Test::AuthProvider *authProvider,
                           Telegram::Client::AuthOperation **output = nullptr);

void signInHelper(Telegram::Client::Client *client, const UserData &userData, Telegram::Test::AuthProvider *authProvider,
                           Telegram::Client::AuthOperation **output)
{
    Telegram::Client::AuthOperation *signInOperation = client->connectionApi()->startAuthentication();
    if (output) {
        *output = signInOperation;
    }
    QSignalSpy serverAuthCodeSpy(authProvider, &Telegram::Test::AuthProvider::codeSent);
    QSignalSpy authCodeSpy(signInOperation, &Telegram::Client::AuthOperation::authCodeRequired);
    signInOperation->setPhoneNumber(userData.phoneNumber);
    TRY_VERIFY(!authCodeSpy.isEmpty());
    QCOMPARE(authCodeSpy.count(), 1);
    QCOMPARE(serverAuthCodeSpy.count(), 1);
    QList<QVariant> authCodeSentArguments = serverAuthCodeSpy.takeFirst();
    QCOMPARE(authCodeSentArguments.count(), 2);
    const QString authCode = authCodeSentArguments.at(1).toString();

    signInOperation->submitAuthCode(authCode);

    if (!userData.password.isEmpty()) {
        QSignalSpy authPasswordSpy(signInOperation, &Telegram::Client::AuthOperation::passwordRequired);
        QSignalSpy passwordCheckFailedSpy(signInOperation, &Telegram::Client::AuthOperation::passwordCheckFailed);
        TRY_VERIFY2(!authPasswordSpy.isEmpty(), "The user has a password-protection, "
                                                "but there are no passwordRequired signals on the client side");
        QCOMPARE(authPasswordSpy.count(), 1);
        QVERIFY(passwordCheckFailedSpy.isEmpty());

        signInOperation->submitPassword(userData.password + QStringLiteral("invalid"));
        TRY_VERIFY2(!passwordCheckFailedSpy.isEmpty(), "The submitted password is not valid, "
                                                       "but there are not signals on the client side");
        QVERIFY(!signInOperation->isFinished());
        QCOMPARE(passwordCheckFailedSpy.count(), 1);

        signInOperation->submitPassword(userData.password);
    }
}

class Client : public Telegram::Client::Client
{
public:
    explicit Client(QObject *parent = nullptr)
        : Telegram::Client::Client(parent)
    {
        setSettings(new Telegram::Client::Settings(this));
        setAccountStorage(new Telegram::Client::AccountStorage(this));
        setDataStorage(new Telegram::Client::InMemoryDataStorage(this));
        setAppInformation(new Telegram::Client::AppInformation(this));
        setupAppInfo(appInformation());
    }
};

} // Test namespace

} // Telegram namespace

#endif // TEST_CLIENT_UTILS_HPP
