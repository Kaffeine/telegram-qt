#include "ConnectionApi_p.hpp"

#include "AccountStorage.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientSettings.hpp"
#include "CTelegramTransport.hpp"
#include "CClientTcpTransport.hpp"
#include "DataStorage.hpp"

#include "Operations/ClientAuthOperation_p.hpp"
#include "Operations/ClientPingOperation.hpp"
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

bool ConnectionApiPrivate::isSignedIn() const
{
    switch (m_status) {
    case ConnectionApi::StatusConnected:
    case ConnectionApi::StatusReady:
        return true;
    case ConnectionApi::StatusDisconnected:
    case ConnectionApi::StatusConnecting:
    case ConnectionApi::StatusWaitForAuthentication:
        return false;
    }
    Q_UNREACHABLE();
}

Connection *ConnectionApiPrivate::getDefaultConnection()
{
    if (mainConnection()) {
        return mainConnection();
    }

    if (m_initialConnectOperation) {
        return m_initialConnectOperation->connection();
    }
    return nullptr;
}

Connection *ConnectionApiPrivate::mainConnection()
{
    return m_mainConnection;
}

void ConnectionApiPrivate::setMainConnection(Connection *connection, SetConnectionOption option)
{
    if (m_mainConnection) {
        if (option == DestroyOldConnection) {
            disconnect(m_mainConnection, nullptr, this, nullptr);
            m_mainConnection->deleteLater();
        }
    }
    m_mainConnection = connection;
    if (m_mainConnection) {
        connect(m_mainConnection, &BaseConnection::statusChanged, this, &ConnectionApiPrivate::onMainConnectionStatusChanged);
        onMainConnectionStatusChanged(m_mainConnection->status(), Connection::StatusReason::Local);
    }
}

PendingOperation *ConnectionApiPrivate::connectToServer(const QVector<DcOption> &dcOptions)
{
    if (dcOptions.isEmpty()) {
        return PendingOperation::failOperation(QStringLiteral("Unable to connect to server: no address given"));
    }
    if (m_initialConnectOperation) {
        if (dcOptions.contains(m_initialConnectOperation->connection()->dcOption())) {
            switch (m_initialConnectOperation->connection()->status()) {
            case BaseConnection::Status::Connecting:
            case BaseConnection::Status::Connected:
            case BaseConnection::Status::HasDhKey:
            case BaseConnection::Status::Signed:
                return m_initialConnectOperation;
            default:
                m_initialConnectOperation->connection()->transport()->disconnectFromHost();
                break;
            }
        }
        m_initialConnectOperation->deleteLater();
        m_initialConnectOperation = nullptr;
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
    connect(connection, &BaseConnection::statusChanged,
            this, &ConnectionApiPrivate::onInitialConnectionStatusChanged);

    m_initialConnectOperation = connection->connectToDc();
    connect(m_initialConnectOperation, &PendingOperation::finished, this, &ConnectionApiPrivate::onInitialConnectOperationFinished);
    return m_initialConnectOperation;
}

AuthOperation *ConnectionApiPrivate::startAuthentication()
{
    QVariantHash errorDetails = getBackendSetupErrorDetails();
    if (!errorDetails.isEmpty()) {
        return PendingOperation::failOperation<AuthOperation>(errorDetails, this);
    }

    if (isSignedIn()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Already signed in"), this);
    }
    if (m_authOperation && !m_authOperation->isFinished()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Auth operation is already in progress"), this);
    }

    m_authOperation = new AuthOperation(this);
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    priv->setBackend(backend());
    priv->setRunMethod(&AuthOperation::requestAuthCode);
    connect(m_authOperation, &AuthOperation::finished, this, &ConnectionApiPrivate::onNewAuthenticationFinished);
    connect(m_authOperation, &AuthOperation::authCodeRequired, this, &ConnectionApiPrivate::onAuthCodeRequired);
    PendingOperation *connectionOperation = connectToServer(backend()->settings()->serverConfiguration());
    m_authOperation->runAfter(connectionOperation);
    return m_authOperation;
}

AuthOperation *ConnectionApiPrivate::checkIn()
{
    QVariantHash errorDetails = getBackendSetupErrorDetails();
    if (!errorDetails.isEmpty()) {
        return PendingOperation::failOperation<AuthOperation>(errorDetails, this);
    }

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
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    priv->setBackend(backend());
    priv->setRunMethod(&AuthOperation::checkAuthorization);
    connect(m_authOperation, &AuthOperation::finished, this, &ConnectionApiPrivate::onNewAuthenticationFinished);
    PendingOperation *connectionOperation = connectToServer({accountStorage->dcInfo()});
    m_authOperation->runAfter(connectionOperation);
    m_initialConnectOperation->connection()->setAuthKey(accountStorage->authKey());
    m_initialConnectOperation->connection()->rpcLayer()->setSessionData(
                accountStorage->sessionId(),
                accountStorage->contentRelatedMessagesNumber());
    return m_authOperation;
}

QVariantHash ConnectionApiPrivate::getBackendSetupErrorDetails() const
{
    if (!backend()->accountStorage()) {
        return {{PendingOperation::c_text(), QStringLiteral("Account storage is missing")}};
    }
    if (!backend()->dataStorage()) {
        return {{PendingOperation::c_text(), QStringLiteral("Data storage is missing")}};
    }
    Settings *settings = backend()->settings();
    if (!settings) {
        return {{PendingOperation::c_text(), QStringLiteral("Settings object is missing")}};
    }
    if (!settings->isValid()) {
        return {{PendingOperation::c_text(), QStringLiteral("Invalid settings")}};
    }
    return {};
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
    case Settings::SessionType::None:
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

Connection *ConnectionApiPrivate::ensureConnection(const ConnectionSpec &connectionSpec)
{
    qCDebug(c_connectionApiLoggingCategory) << Q_FUNC_INFO << connectionSpec.dcId << connectionSpec.flags;
    ConnectionSpec spec = connectionSpec;
    spec.flags |= ConnectionSpec::RequestFlag::Ipv4Only; // Enable only ipv4 for now
    if (!m_connections.contains(connectionSpec)) {
        const DcOption opt = backend()->dataStorage()->serverConfiguration().getOption(spec);
        if (!opt.isValid()) {
            qCWarning(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Unable to find suitable DC";
            return nullptr;
        }
        m_connections.insert(connectionSpec, createConnection(opt));
    }
    return m_connections.value(connectionSpec);
}

void ConnectionApiPrivate::onInitialConnectOperationFinished(PendingOperation *operation)
{
    disconnect(m_initialConnectOperation->connection(), &BaseConnection::statusChanged,
               this, &ConnectionApiPrivate::onInitialConnectionStatusChanged);

    if (operation->isSucceeded()) {
        backend()->getDcConfig();
        return;
    }
    m_initialConnectOperation = nullptr;
    operation->deleteLater();
    setStatus(ConnectionApi::StatusDisconnected);
}

void ConnectionApiPrivate::onInitialConnectionStatusChanged(BaseConnection::Status status,
                                                             BaseConnection::StatusReason reason)
{
    qCDebug(c_connectionApiLoggingCategory) << Q_FUNC_INFO << status << reason;
    switch (status) {
    case BaseConnection::Status::Disconnected:
    case BaseConnection::Status::Disconnecting:
        setStatus(ConnectionApi::StatusDisconnected);
        break;
    case BaseConnection::Status::Connecting:
        setStatus(ConnectionApi::StatusConnecting);
        break;
    case BaseConnection::Status::Connected:
        // Nothing to do; wait for DH
        break;
    case BaseConnection::Status::HasDhKey:
        break;
    case BaseConnection::Status::Signed:
    case BaseConnection::Status::Failed:
        break;
    }
}

void ConnectionApiPrivate::onNewAuthenticationFinished(PendingOperation *operation)
{
    if (operation != m_authOperation) {
        qCCritical(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Unexpected auth operation";
        return;
    }
    if (!operation->isSucceeded()) {
        setStatus(ConnectionApi::StatusWaitForAuthentication);
        qCDebug(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "TODO?";
        return;
    }
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    Connection *conn = priv->m_authenticatedConnection;
    if (conn->status() != Connection::Status::Signed) {
        qCCritical(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Unexpected connection status" << conn->status();
        return;
    }
    setMainConnection(conn);
}

void ConnectionApiPrivate::onAuthCodeRequired()
{
    setStatus(ConnectionApi::StatusWaitForAuthentication, ConnectionApi::StatusReasonRemote);
}

void ConnectionApiPrivate::onMainConnectionStatusChanged(BaseConnection::Status status, BaseConnection::StatusReason reason)
{
    if (!m_mainConnection) {
        return;
    }

    const bool keepAliveIsWanted = (status == Connection::Status::Signed) || (status == Connection::Status::HasDhKey);
    if (keepAliveIsWanted) {
        if (!m_pingOperation) {
            m_pingOperation = new PingOperation(this);
            m_pingOperation->setSettings(backend()->m_settings);
            m_pingOperation->setRpcLayer(m_mainConnection->rpcLayer());
            connect(m_pingOperation, &PingOperation::pingFailed, this, &ConnectionApiPrivate::onPingFailed);
        }
        m_pingOperation->ensureActive();
    } else {
        if (m_pingOperation) {
            m_pingOperation->ensureInactive();
        }
    }

    switch (status) {
    case Connection::Status::Signed:
    {
        backend()->syncAccountToStorage();
        setStatus(ConnectionApi::StatusConnected);
        PendingOperation *syncOperation = backend()->sync();
        connect(syncOperation, &PendingOperation::finished, this, &ConnectionApiPrivate::onSyncFinished);
        syncOperation->startLater();
    }
        break;
    default:
        break;
    }
}

void ConnectionApiPrivate::onSyncFinished(PendingOperation *operation)
{
    if (operation->isSucceeded()) {
        setStatus(ConnectionApi::StatusReady, ConnectionApi::StatusReasonLocal);
    } else {
        qCCritical(c_connectionApiLoggingCategory) << Q_FUNC_INFO << "Unexpected sync operation status" << operation->errorDetails();
    }
}

void ConnectionApiPrivate::onPingFailed()
{
    qCWarning(c_connectionApiLoggingCategory) << Q_FUNC_INFO;
}

void ConnectionApiPrivate::setStatus(ConnectionApi::Status status, ConnectionApi::StatusReason reason)
{
    Q_Q(ConnectionApi);
    if (m_status == status) {
        return;
    }
    m_status = status;
    emit q->statusChanged(status, reason);
}

ConnectionApi::ConnectionApi(QObject *parent) :
    ClientApi(parent)
{
    d = new ConnectionApiPrivate(this);
}

bool ConnectionApi::isSignedIn() const
{
    Q_D(const ConnectionApi);
    return d->isSignedIn();
}

ConnectionApi::Status ConnectionApi::status() const
{
    Q_D(const ConnectionApi);
    return d->status();
}

Telegram::Client::AuthOperation *ConnectionApi::startAuthentication()
{
    Q_D(ConnectionApi);
    return d->startAuthentication();
}

AuthOperation *ConnectionApi::checkIn()
{
    Q_D(ConnectionApi);
    return d->checkIn();
}

} // Client namespace

} // Telegram namespace
