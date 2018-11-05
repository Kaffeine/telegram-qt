#include "ConnectionApi_p.hpp"

#include "AccountStorage.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientSettings.hpp"
#include "CTelegramTransport.hpp"
#include "CClientTcpTransport.hpp"
#include "DataStorage.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/ConnectionOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_connectionApiLoggingCategory, "telegram.client.api.connection", QtWarningMsg)

namespace Telegram {

namespace Client {

ConnectionApiPrivate::ConnectionApiPrivate(ConnectionApi *parent) :
    ClientApiPrivate(parent)
{
}

ConnectionApiPrivate *ConnectionApiPrivate::get(ConnectionApi *parent)
{
    return reinterpret_cast<ConnectionApiPrivate*>(parent->d);
}

Connection *ConnectionApiPrivate::getDefaultConnection()
{
    if (mainConnection()) {
        return mainConnection();
    }

    if (m_connectToServerOperation) {
        return m_connectToServerOperation->connection();
    }
    return nullptr;
}

Connection *ConnectionApiPrivate::mainConnection()
{
    return m_mainConnection;
}

void ConnectionApiPrivate::setMainConnection(Connection *connection)
{
    m_mainConnection = connection;
    connect(m_mainConnection, &BaseConnection::statusChanged, this, &ConnectionApiPrivate::onMainConnectionStatusChanged);
    onMainConnectionStatusChanged();
}

PendingOperation *ConnectionApiPrivate::connectToServer(const QVector<DcOption> &dcOptions)
{
    if (m_connectToServerOperation) {
        if (dcOptions.contains(m_connectToServerOperation->connection()->dcOption())) {
            switch (m_connectToServerOperation->connection()->status()) {
            case BaseConnection::Status::Connecting:
            case BaseConnection::Status::Connected:
            case BaseConnection::Status::HasDhKey:
            case BaseConnection::Status::Signed:
                return m_connectToServerOperation;
            default:
                m_connectToServerOperation->connection()->transport()->disconnectFromHost();
                break;
            }
        }
        m_connectToServerOperation->deleteLater();
        m_connectToServerOperation = nullptr;
    }

    if (mainConnection()) {
        if (mainConnection()->status() != Connection::Status::Disconnected) {
            return PendingOperation::failOperation<PendingOperation>
                    (QStringLiteral("Connection is already in progress"), this);
        } else {
            // TODO!
        }
    }

    if (!backend()->accountStorage()) {
        return PendingOperation::failOperation<PendingOperation>
                (QStringLiteral("Account storage is missing"), this);
    }
    if (!backend()->dataStorage()) {
        return PendingOperation::failOperation<PendingOperation>
                (QStringLiteral("Data storage is missing"), this);
    }

    Connection *connection = createConnection(dcOptions.first());
    m_connectToServerOperation = connection->connectToDc();
    connect(m_connectToServerOperation, &PendingOperation::finished, this, &ConnectionApiPrivate::onConnectOperationFinished);
    return m_connectToServerOperation;
}

AuthOperation *ConnectionApiPrivate::signIn()
{
    if (backend()->isSignedIn()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Already signed in"), this);
    }
    Settings *settings = backend()->m_settings;
    if (!settings || !settings->isValid()) {
        qCWarning(c_connectionApiLoggingCategory) << "Invalid settings";
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Invalid settings"), this);
    }
    if (m_authOperation && !m_authOperation->isFinished()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Auth operation is already in progress"), this);
    }

    m_authOperation = new AuthOperation(this);
    m_authOperation->setBackend(backend());
    PendingOperation *connectionOperation = connectToServer(settings->serverConfiguration());
    m_authOperation->runAfter(connectionOperation);
    m_authOperation->setRunMethod(&AuthOperation::requestAuthCode);
    return m_authOperation;
}

AuthOperation *ConnectionApiPrivate::checkIn()
{
    if (m_authOperation && !m_authOperation->isFinished()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Auth operation is already in progress"), this);
    }
    AccountStorage *accountStorage = backend()->accountStorage();
    if (!accountStorage || !accountStorage->hasMinimalDataSet()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("No minimal account data set"), this);
    }
    m_authOperation = new AuthOperation(this);
    m_authOperation->setBackend(backend());
    PendingOperation *connectionOperation = connectToServer({accountStorage->dcInfo()});
    m_authOperation->runAfter(connectionOperation);
    m_authOperation->setRunMethod(&AuthOperation::checkAuthorization);
    m_connectToServerOperation->connection()->setAuthKey(accountStorage->authKey());
    m_connectToServerOperation->connection()->rpcLayer()->setSessionData(
                accountStorage->sessionId(),
                accountStorage->contentRelatedMessagesNumber());
    return m_authOperation;
}

Connection *ConnectionApiPrivate::createConnection(const DcOption &dcOption)
{
    Connection *connection = new Connection(this);
    connection->setDcOption(dcOption);
    connection->rpcLayer()->setAppInformation(backend()->m_appInformation);
    connection->rpcLayer()->installUpdatesHandler(backend()->updatesApi());
    connection->setDeltaTime(backend()->accountStorage()->deltaTime());

    Settings *settings = backend()->m_settings;
    connection->setServerRsaKey(settings->serverRsaKey());
    TcpTransport *transport = new TcpTransport(connection);
    transport->setProxy(settings->proxy());

    switch (settings->preferedSessionType()) {
    case Settings::SessionType::Default:
        qCWarning(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Session type is not set. Use fallback.";
        transport->setPreferedSessionType(TcpTransport::Obfuscated);
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

Connection *ConnectionApiPrivate::ensureConnection(const ConnectionSpec &dcSpec)
{
    qCDebug(c_connectionApiLoggingCategory) << Q_FUNC_INFO << dcSpec.dcId << dcSpec.flags;
    ConnectionSpec spec = dcSpec;
    spec.flags |= ConnectionSpec::RequestFlag::Ipv4Only; // Enable only ipv4 for now
    if (!m_connections.contains(dcSpec)) {
        const DcOption opt = backend()->dataStorage()->serverConfiguration().getOption(spec);
        if (!opt.isValid()) {
            qCWarning(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Unable to find suitable DC";
            return nullptr;
        }
        m_connections.insert(dcSpec, createConnection(opt));
    }
    return m_connections.value(dcSpec);
}

void ConnectionApiPrivate::onConnectOperationFinished(PendingOperation *operation)
{
    if (operation->isSucceeded()) {
        backend()->getDcConfig();
        return;
    }
    m_connectToServerOperation = nullptr;
    operation->deleteLater();
}

void ConnectionApiPrivate::onMainConnectionStatusChanged()
{
    if (!m_mainConnection) {
        return;
    }
    backend()->setSignedIn(m_mainConnection->status() == Connection::Status::Signed);
    if (backend()->isSignedIn()) {
        backend()->syncAccountToStorage();
    }
}

ConnectionApi::ConnectionApi(QObject *parent) :
    ClientApi(parent)
{
    d = new ConnectionApiPrivate(this);
}

Telegram::Client::AuthOperation *ConnectionApi::signUp()
{
     return signIn();
}

Telegram::Client::AuthOperation *ConnectionApi::signIn()
{
    Q_D(ConnectionApi);
    return d->signIn();
}

AuthOperation *ConnectionApi::checkIn()
{
    Q_D(ConnectionApi);
    return d->checkIn();
}

} // Client namespace

} // Telegram namespace
