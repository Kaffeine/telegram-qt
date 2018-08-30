#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "CClientTcpTransport.hpp"
#include "ClientSettings.hpp"
#include "AccountStorage.hpp"
#include "ClientConnection.hpp"
#include "Client.hpp"
#include "ClientRpcLayer.hpp"
#include "DataStorage.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/ConnectionOperation.hpp"

#include <QLoggingCategory>
#include <QTimer>

// Generated low-level layer includes
#include "ClientRpcAccountLayer.hpp"
#include "ClientRpcAuthLayer.hpp"
#include "ClientRpcBotsLayer.hpp"
#include "ClientRpcChannelsLayer.hpp"
#include "ClientRpcContactsLayer.hpp"
#include "ClientRpcHelpLayer.hpp"
#include "ClientRpcLangpackLayer.hpp"
#include "ClientRpcMessagesLayer.hpp"
#include "ClientRpcPaymentsLayer.hpp"
#include "ClientRpcPhoneLayer.hpp"
#include "ClientRpcPhotosLayer.hpp"
#include "ClientRpcStickersLayer.hpp"
#include "ClientRpcUpdatesLayer.hpp"
#include "ClientRpcUploadLayer.hpp"
#include "ClientRpcUsersLayer.hpp"
// End of generated low-level layer includes

namespace Telegram {

namespace Client {

Backend::Backend(Client *parent) :
    QObject(parent),
    m_client(parent)
{
    Backend *b = this;
    BaseRpcLayerExtension::SendMethod sendMethod = [b](const QByteArray &payload) mutable {
        PendingRpcOperation *operation = new PendingRpcOperation(payload, b);
        b->getDefaultConnection()->rpcLayer()->sendRpc(operation);
        return operation;
    };

    // Generated low-level layer initialization
    m_accountLayer = new AccountRpcLayer(this);
    m_accountLayer->setSendMethod(sendMethod);
    m_authLayer = new AuthRpcLayer(this);
    m_authLayer->setSendMethod(sendMethod);
    m_botsLayer = new BotsRpcLayer(this);
    m_botsLayer->setSendMethod(sendMethod);
    m_channelsLayer = new ChannelsRpcLayer(this);
    m_channelsLayer->setSendMethod(sendMethod);
    m_contactsLayer = new ContactsRpcLayer(this);
    m_contactsLayer->setSendMethod(sendMethod);
    m_helpLayer = new HelpRpcLayer(this);
    m_helpLayer->setSendMethod(sendMethod);
    m_langpackLayer = new LangpackRpcLayer(this);
    m_langpackLayer->setSendMethod(sendMethod);
    m_messagesLayer = new MessagesRpcLayer(this);
    m_messagesLayer->setSendMethod(sendMethod);
    m_paymentsLayer = new PaymentsRpcLayer(this);
    m_paymentsLayer->setSendMethod(sendMethod);
    m_phoneLayer = new PhoneRpcLayer(this);
    m_phoneLayer->setSendMethod(sendMethod);
    m_photosLayer = new PhotosRpcLayer(this);
    m_photosLayer->setSendMethod(sendMethod);
    m_stickersLayer = new StickersRpcLayer(this);
    m_stickersLayer->setSendMethod(sendMethod);
    m_updatesLayer = new UpdatesRpcLayer(this);
    m_updatesLayer->setSendMethod(sendMethod);
    m_uploadLayer = new UploadRpcLayer(this);
    m_uploadLayer->setSendMethod(sendMethod);
    m_usersLayer = new UsersRpcLayer(this);
    m_usersLayer->setSendMethod(sendMethod);
    // End of generated low-level layer initialization
}

PendingOperation *Backend::connectToServer()
{
    if (m_connectToServerOperation) {
        return m_connectToServerOperation;
    }

    if (m_mainConnection && m_mainConnection->status() != Connection::Status::Disconnected) {
        return PendingOperation::failOperation<PendingOperation>
                ({
                     { QStringLiteral("text"), QStringLiteral("Connection is already in progress") }
                 });
    }

    if (m_mainConnection) {
        // TODO!
    }

    if (!m_accountStorage) {
        return PendingOperation::failOperation<PendingOperation>
                ({
                     { QStringLiteral("text"), QStringLiteral("Account storage is missing") }
                 });
    }
    if (!m_dataStorage) {
        return PendingOperation::failOperation<PendingOperation>
                ({
                     { QStringLiteral("text"), QStringLiteral("Data storage is missing") }
                 });
    }

    Connection *connection = nullptr;
    if (m_accountStorage->hasMinimalDataSet()) {
        connection = createConnection(m_accountStorage->dcInfo());
        connection->setAuthKey(m_accountStorage->authKey());
    } else {
        connection = createConnection(m_settings->serverConfiguration().first());
    }
    m_connectToServerOperation = connection->connectToDc();
    return m_connectToServerOperation;
}

AuthOperation *Backend::signIn()
{
    if (!m_authOperation) {
        m_authOperation = new AuthOperation(this);
    }

    if (m_signedIn) {
        m_authOperation->setDelayedFinishedWithError({
                                                         { QStringLiteral("text"), QStringLiteral("Already signed in") }
                                                     });
        return m_authOperation;
    }
    if (!m_settings || !m_settings->isValid()) {
        qWarning() << "Invalid settings";
        m_authOperation->setDelayedFinishedWithError({
                                                         { QStringLiteral("text"), QStringLiteral("Invalid settings") }
                                                     });
        return m_authOperation;
    }

    // Transport?

/*  1 ) Establish TCP connection
    2a) if there is no key in AccountStorage, use DH layer to get it
    2b) use the key from AccountStorage
    -3) try to get self phone     (postponed)
    -4) if error, report an error (postponed)
    5a) if there is no phone number in AccountStorage, emit phoneRequired()
    6b) use phone from AccountStorage
     7) API Call authSendCode()
     8) If error 401 SESSION_PASSWORD_NEEDED:
     9)     API Call accountGetPassword() -> TLAccountPassword(salt)
    10)     API Call authCheckPassword( Utils::sha256(salt + password + salt) )
    11) API Call authSignIn()

     Request phone number

     Request auth code
     Request password

     Done!
  */

//    if (!m_private->m_appInfo || !m_private->m_appInfo->isValid()) {
//        qWarning() << "CTelegramCore::connectToServer(): App information is null or is not valid.";
//        return false;
//    }

//    m_private->m_dispatcher->setAppInformation(m_private->m_appInfo);
//    return m_private->m_dispatcher->connectToServer();
    // connectToServer(),
    // checkPhoneNumber()

    m_authOperation->setBackend(this);

    if (!m_accountStorage->phoneNumber().isEmpty()) {
        m_authOperation->setPhoneNumber(m_accountStorage->phoneNumber());
    }

    PendingOperation *connectionOperation = connectToServer();
    if (!connectionOperation->isFinished()) {
        m_authOperation->runAfter(connectionOperation);
        return m_authOperation;
    }
    m_authOperation->setRunMethod(&AuthOperation::requestAuthCode);
    m_authOperation->startLater();

    connect(m_authOperation, &PendingOperation::succeeded, [this]() {
        m_signedIn = true;
        emit m_client->signedInChanged(m_signedIn);
    });
    return m_authOperation;
}

Connection *Backend::createConnection(const DcOption &dcOption)
{
    Connection *connection = new Connection(this);
    connection->setDcOption(dcOption);
    connection->setServerRsaKey(m_settings->serverRsaKey());
    connection->rpcLayer()->setAppInformation(m_appInformation);

    TcpTransport *transport = new TcpTransport(connection);
    switch (m_settings->preferedSessionType()) {
    case Settings::SessionType::Default:
        break;
    case Settings::SessionType::Abridged:
        transport->setPreferedSessionType(TcpTransport::Abridged);
        break;
    case Settings::SessionType::Obfuscated:
        transport->setPreferedSessionType(TcpTransport::Obfuscated);
        break;
    }
    connection->setTransport(transport);
    return connection;
}

Connection *Backend::mainConnection()
{
    return m_mainConnection;
}

Connection *Backend::getDefaultConnection()
{
    if (mainConnection()) {
        return mainConnection();
    } else if (m_connectToServerOperation) {
        return m_connectToServerOperation->connection();
    }
    return nullptr;
}

void Backend::setMainConnection(Connection *connection)
{
    m_mainConnection = connection;
    auto updateStatusLambda = [this](Connection::Status status) {
        switch (status) {
        case Connection::Status::Authenticated:
        case Connection::Status::Signed:
            m_accountStorage->setAuthKey(m_mainConnection->authKey());
            m_accountStorage->setAuthId(m_mainConnection->authId());
            break;
        default:
            break;
        }
    };
    connect(m_mainConnection, &BaseConnection::statusChanged, updateStatusLambda);
    updateStatusLambda(m_mainConnection->status());
}

} // Client namespace

} // Telegram namespace
