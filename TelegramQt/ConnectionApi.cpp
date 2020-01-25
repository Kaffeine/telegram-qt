#include "ConnectionApi_p.hpp"

#include "AccountStorage.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientSettings.hpp"
#include "CClientTcpTransport.hpp"
#include "ConnectionError.hpp"
#include "DataStorage.hpp"
#include "Debug_p.hpp"

#include "Operations/ClientAuthOperation_p.hpp"
#include "Operations/ClientPingOperation.hpp"
#include "Operations/ConnectionOperation.hpp"
#include "RpcLayers/ClientRpcAuthLayer.hpp"

#include <QLoggingCategory>
#include <QTimer>

Q_LOGGING_CATEGORY(c_connectionApiLoggingCategory, "telegram.client.api.connection", QtInfoMsg)

namespace Telegram {

namespace Client {

static const QVector<uint> getIntervals()
{
    static QVector<uint> intervals;

    if (intervals.isEmpty()) {
        if (qEnvironmentVariableIsSet(ConnectionApi::reconnectionIntervalsEnvironmentVariableName())) {
            QByteArray values = qgetenv(ConnectionApi::reconnectionIntervalsEnvironmentVariableName());
            for (const QByteArray &val : values.split(',')) {
                bool ok;
                uint interval = val.toUInt(&ok);
                if (ok) {
                    intervals.append(interval);
                } else {
                    intervals.clear();
                    break;
                }
            }
        }
        if (intervals.isEmpty()) {
            intervals = { 0, 5000, 5000, 30000, 30000, 60000 };
        }
    }
    return intervals;
}

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
    case ConnectionApi::StatusDisconnected:
    case ConnectionApi::StatusDisconnecting:
    case ConnectionApi::StatusWaitForConnection:
    case ConnectionApi::StatusConnecting:
    case ConnectionApi::StatusWaitForAuthentication:
        return false;
    case ConnectionApi::StatusConnected:
    case ConnectionApi::StatusReady:
        return true;
    }
    Q_UNREACHABLE();
}

Connection *ConnectionApiPrivate::getDefaultConnection()
{
    if (m_mainConnection) {
        return m_mainConnection;
    }
    if (m_initialConnection) {
        return m_initialConnection;
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
        if (m_initialConnection == m_mainConnection) {
            m_initialConnection = nullptr;
        }

        onMainConnectionStatusChanged(m_mainConnection->status(), Connection::StatusReason::Local);
    }
}

void ConnectionApiPrivate::setInitialConnection(Connection *connection, SetConnectionOption option)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << connection;
    if (m_initialConnection) {
        if (option == DestroyOldConnection) {
            disconnect(m_initialConnection, nullptr, this, nullptr);
            m_initialConnection->deleteLater();
        }
    }
    m_initialConnection = connection;
}

void ConnectionApiPrivate::disconnectFromServer()
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO;
    setStatus(ConnectionApi::StatusDisconnected, ConnectionApi::StatusReasonLocal);
    setInitialConnection(nullptr);
    setMainConnection(nullptr);
    m_initialConnectOperation->deleteLater();
    m_initialConnectOperation = nullptr;

    qDeleteAll(m_connections);
    m_connections.clear();
    m_connectionOperations.clear();
}

PendingOperation *ConnectionApiPrivate::connectToDc(quint32 dcId)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << dcId;
    if (m_initialConnectOperation) {
        delete m_initialConnectOperation;
        m_initialConnectOperation = nullptr;
    }

    DcOption opt = m_backend->dataStorage()->serverConfiguration().getOption(
                ConnectionSpec(dcId, ConnectionSpec::RequestFlag::Ipv4Only)
                );
    if (!opt.isValid()) {
        return PendingOperation::failOperation(
                    QLatin1String("Unable to connect: the requested DC not found in configuration)"));
    }
    connectToServer({ opt });
    m_initialConnectOperation->setObjectName(QLatin1String("ConnectionApi::connectToServer(id)"));
    return m_initialConnectOperation;
}

/*!
  Establish a connection to any of the given \a dcOptions

  Operation fails only in case of incorrect setup.
  Operation finished once DH connection established (ConnectionApi::StatusWaitForAuthentication).
*/
PendingOperation *ConnectionApiPrivate::connectToServer(const QVector<DcOption> &dcOptions)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << "(dcOptions)";

    if (dcOptions.isEmpty()) {
        return PendingOperation::failOperation(QLatin1String("Unable to connect to server: no address given"));
    }
    if (m_initialConnectOperation) {
        qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << "return existing connect operation"
                                                << m_initialConnectOperation;
        return m_initialConnectOperation;
    }
    m_initialConnectOperation = new PendingOperation(this);
    m_initialConnectOperation->setOperationName("ConnectionApi::connectToServer(options)");
    m_serverConfiguration = dcOptions;
    m_nextServerAddressIndex = 0;
    m_connectionAttemptNumber = 0;
    queueConnectToNextServer();
    return m_initialConnectOperation;
}

void ConnectionApiPrivate::connectToNextServer()
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << "queued:" << m_connectionQueued;
    if (!m_connectionQueued) {
        return;
    }

    if (m_nextServerAddressIndex >= m_serverConfiguration.count()) {
        onAllDcOptionsTried();
        return;
    }

    const DcOption dcOption = m_serverConfiguration.at(m_nextServerAddressIndex);
    ++m_nextServerAddressIndex;

    if (dcOption.flags & (DcOption::Ipv6|DcOption::MediaOnly)) {
        qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                                << "dequeued unsupported dc option, go for the next one...";
        return connectToNextServer();
    }

    Connection *newConnection = createConnection(dcOption);
    setInitialConnection(newConnection, DestroyOldConnection);

    AccountStorage *accountStorage = backend()->accountStorage();
    if (accountStorage && accountStorage->hasMinimalDataSet()) {
        qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                                << "Use session from account storage for the new initial connection"
                                                << newConnection;

        m_initialConnection->setAuthKey(accountStorage->authKey());
        m_initialConnection->rpcLayer()->setSessionData(
                    accountStorage->sessionId(),
                    accountStorage->contentRelatedMessagesNumber());
    }

    ConnectOperation *connectionOperation = new ConnectOperation(this);
    connectionOperation->setConnection(m_initialConnection);
    connectionOperation->deleteOnFinished();
    connect(connectionOperation, &PendingOperation::finished, this, [](PendingOperation *op) {
        if (op->isFailed()) {
            qCInfo(c_connectionApiLoggingCategory) << op << op->errorDetails();
        } else {
            qCDebug(c_connectionApiLoggingCategory) << op << "succeeded";
        }
    });
    connectionOperation->start();
    m_connectionQueued = false;
}

void ConnectionApiPrivate::queueConnectToNextServer()
{
    if (m_connectionQueued) {
        return;
    }

    m_connectionQueued = true;

    uint interval = 0;
    const QVector<uint> intervals = getIntervals();
    if (intervals.count() > m_connectionAttemptNumber) {
        interval = intervals.at(m_connectionAttemptNumber);
    } else {
        interval = intervals.last();
    }
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << "interval:" << interval;

    ++m_connectionAttemptNumber;

    if (interval == 0) {
        setStatus(ConnectionApi::StatusWaitForConnection, ConnectionApi::StatusReasonLocal);
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        QMetaObject::invokeMethod(this, [this]() { this->connectToNextServer(); }, Qt::QueuedConnection);
#else
        QMetaObject::invokeMethod(this, "connectToNextServer", Qt::QueuedConnection);
#endif
        return;
    }

    if (!m_queuedConnectionTimer) {
        m_queuedConnectionTimer = new QTimer(this);
        m_queuedConnectionTimer->setSingleShot(true);
        connect(m_queuedConnectionTimer, &QTimer::timeout,
                this, &ConnectionApiPrivate::connectToNextServer);
    }

    m_queuedConnectionTimer->start(static_cast<int>(interval));
    setStatus(ConnectionApi::StatusWaitForConnection, ConnectionApi::StatusReasonLocal);
}

AuthOperation *ConnectionApiPrivate::startAuthentication()
{
    QVariantHash errorDetails = getBackendSetupErrorDetails();
    if (!errorDetails.isEmpty()) {
        return PendingOperation::failOperation<AuthOperation>(errorDetails, this);
    }

    if (m_authOperation) {
        if (m_authOperation->isFinished()) {
            delete m_authOperation;
        } else {
            return PendingOperation::failOperation<AuthOperation>
                    (QLatin1String("Auth operation is already in progress"), this);
        }
    }

    m_authOperation = new AuthOperation(this);
    m_authOperation->setObjectName(QLatin1String("Auth/StartAuthentication"));
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    priv->setBackend(backend());
    priv->setRunMethod(&AuthOperationPrivate::requestAuthCode);
    connect(m_authOperation, &AuthOperation::finished,
            this, &ConnectionApiPrivate::onNewAuthenticationFinished);
    connect(m_authOperation, &AuthOperation::authCodeRequired,
            this, &ConnectionApiPrivate::onAuthCodeRequired);
    PendingOperation *connectionOperation = connectToServer(backend()->settings()->serverConfiguration());
    connectionOperation->setObjectName(QLatin1String("ConnectionApi::connectToServer(dcs from settings)"));
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
                (QLatin1String("Auth operation is already in progress"), this);
    }
    AccountStorage *accountStorage = backend()->accountStorage();
    if (!accountStorage || !accountStorage->hasMinimalDataSet()) {
        return PendingOperation::failOperation<AuthOperation>
                (QLatin1String("No minimal account data set"), this);
    }
    m_authOperation = new AuthOperation(this);
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    m_authOperation->setObjectName(QLatin1String("Auth/CheckIn"));
    priv->setBackend(backend());
    priv->setRunMethod(&AuthOperationPrivate::checkAuthorization);
    connect(m_authOperation, &AuthOperation::finished,
            this, &ConnectionApiPrivate::onCheckInFinished);
    if (m_mainConnection) {
        m_authOperation->startLater();
    } else {
        PendingOperation *connOp = connectToServer({accountStorage->dcInfo()});
        m_authOperation->runAfter(connOp);
    }
    return m_authOperation;
}

QVariantHash ConnectionApiPrivate::getBackendSetupErrorDetails() const
{
    if (!backend()->accountStorage()) {
        return {{PendingOperation::c_text(), QLatin1String("Account storage is missing")}};
    }
    if (!backend()->dataStorage()) {
        return {{PendingOperation::c_text(), QLatin1String("Data storage is missing")}};
    }
    Settings *settings = backend()->settings();
    if (!settings) {
        return {{PendingOperation::c_text(), QLatin1String("Settings object is missing")}};
    }
    if (!settings->serverRsaKey().isValid()) {
        return {{PendingOperation::c_text(), QLatin1String("Invalid server RSA key")}};
    }
    if (!settings->isValid()) {
        return {{PendingOperation::c_text(), QLatin1String("Invalid settings")}};
    }
    return {};
}

/* Return operation instead of Connection to be able to return errors if connection uncreatable */
ConnectOperation *ConnectionApiPrivate::connectToExtraDc(const ConnectionSpec &connectionSpec)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                            << connectionSpec.dcId << connectionSpec.flags;
    ConnectionSpec spec = connectionSpec;
    spec.flags |= ConnectionSpec::RequestFlag::Ipv4Only; // Enable only ipv4 for now
    ConnectOperation *operation = m_connectionOperations.value(connectionSpec);
    if (operation) {
        qCDebug(c_connectionApiLoggingCategory) << __func__ << "Preexist operation:" << operation;
        // verify that the operation is suitable for reuse
        if (operation->isFinished()) {
            // if (operation->)
        } else {
            // OK, operation is not finished yet
        }
    } else {
        qCDebug(c_connectionApiLoggingCategory) << __func__ << "New operation";
    }

    if (!m_connectionOperations.contains(connectionSpec)) {
        const DcOption opt = backend()->dataStorage()->serverConfiguration().getOption(spec);
        if (!opt.isValid()) {
            const QString text = QLatin1String("Unable to find suitable DC option");
            return PendingOperation::failOperation<ConnectOperation>(text, this);
        }

        Connection *conn = ensureConnection(connectionSpec);
        if (connectionSpec.dcId == mainConnection()->dcOption().id) {
            // Same DC, auth export is not needed
            conn->setAuthKey(mainConnection()->authKey());
            conn->rpcLayer()->startNewSession();
        } else {
            if (!m_exportedAuthorizations.contains(connectionSpec.dcId)) {
                AuthRpcLayer::PendingAuthExportedAuthorization *rpcOperation = nullptr;
                rpcOperation = backend()->authLayer()->exportAuthorization(connectionSpec.dcId);
                rpcOperation->setObjectName(rpcOperation->objectName()
                                            + QStringLiteral("/dc%1").arg(connectionSpec.dcId));
                rpcOperation->connectToFinished(this, &ConnectionApiPrivate::onRpcExportAuthorizationResult,
                                                connectionSpec.dcId,
                                                rpcOperation);
            }

            // if has exported authentication
            //     use it
            // else
            //     export authentication
            //     save authentication
            //
            // connectToDc
            // conn - start new DH
            // conn - start new Rpc session
            // conn - import authentication
            // emit finished()
            // const QString text = QLatin1String("NOT IMPLEMENTED");
            // return PendingOperation::failOperation<ConnectOperation>(text, this);
        }
        ConnectOperation *operation = new ConnectOperation(this);
        operation->setConnection(conn);
        m_connectionOperations.insert(connectionSpec, operation);
        operation->start();
    }
    return m_connectionOperations.value(connectionSpec);
}

/*!
  The method constructs new Connection ready to connect to the passed server address.
*/
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
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                  << "Session type is not set. Use fallback.";
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

    connect(connection, &BaseConnection::statusChanged,
            this, [this, connection] (BaseConnection::Status status, BaseConnection::StatusReason reason) {
        this->onConnectionStatusChanged(connection, status, reason);
    });
    connect(connection, &BaseConnection::errorOccured,
            this, &ConnectionApiPrivate::onConnectionError);

    return connection;
}

/*!
  \fn Connection *ConnectionApiPrivate::ensureConnection(const ConnectionSpec &connectionSpec)

  The method returns new or existing Connection to the passed server address.

  The returned Connection is prepaired to work with \a connectionSpec and can have any status.
*/
Connection *ConnectionApiPrivate::ensureConnection(const ConnectionSpec &connectionSpec)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                            << connectionSpec.dcId << connectionSpec.flags;
    ConnectionSpec spec = connectionSpec;
    spec.flags |= ConnectionSpec::RequestFlag::Ipv4Only; // Enable only ipv4 for now
    if (!m_connections.contains(connectionSpec)) {
        const DcOption opt = backend()->dataStorage()->serverConfiguration().getOption(spec);
        if (!opt.isValid()) {
            qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                      << "Unable to find suitable DC";
            return nullptr;
        }
        m_connections.insert(connectionSpec, createConnection(opt));
    }
    return m_connections.value(connectionSpec);
}

void ConnectionApiPrivate::ensureConnected(Connection *connection)
{
    // mainConnection()->rpcLayer()->
}

PendingOperation *ConnectionApiPrivate::getAuthentication(quint32 dcId)
{
    AuthRpcLayer::PendingAuthExportedAuthorization *rpcOperation = nullptr;
    rpcOperation = backend()->authLayer()->exportAuthorization(dcId);

    return rpcOperation;
}

PendingOperation *ConnectionApiPrivate::ensureDcHasAuthentication(quint32 dcId)
{
    AuthRpcLayer::PendingAuthExportedAuthorization *rpcOperation = nullptr;
    rpcOperation = backend()->authLayer()->exportAuthorization(dcId);
    rpcOperation->setObjectName(rpcOperation->objectName()
                                + QStringLiteral("/dc%1").arg(dcId));
    rpcOperation->connectToFinished(this, &ConnectionApiPrivate::onRpcExportAuthorizationResult,
                                    dcId,
                                    rpcOperation);
    return rpcOperation;
}

void ConnectionApiPrivate::onReconnectOperationFinished(PendingOperation *operation)
{
    qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                              << "result errors:" << operation->errorDetails();
    if (operation->isSucceeded()) {
        checkIn();
    }
}

void ConnectionApiPrivate::onInitialConnectionStatusChanged(BaseConnection::Status status,
                                                             BaseConnection::StatusReason reason)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                            << m_initialConnection << status << reason;
    switch (status) {
    case BaseConnection::Status::Disconnected:
        queueConnectToNextServer();
        break;
    case BaseConnection::Status::Disconnecting:
        // Nothing to do; wait for Disconnected
        break;
    case BaseConnection::Status::Connecting:
        setStatus(ConnectionApi::StatusConnecting, ConnectionApi::StatusReasonLocal);
        break;
    case BaseConnection::Status::Connected:
        // Nothing to do; wait for DH
        break;
    case BaseConnection::Status::HasDhKey:
        m_connectionAttemptNumber = 0;
    {
        PendingOperation *op = backend()->getDcConfig();
        op->invokeOnFinished(this, &ConnectionApiPrivate::onGotDcConfig, op);
    }
        break;
    case BaseConnection::Status::Signed:
        break;
    case BaseConnection::Status::Failed:
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                  << "failed" << m_initialConnection;
        break;
    }
}

void ConnectionApiPrivate::onGotDcConfig(PendingOperation *operation)
{
    if (!operation->isSucceeded()) {
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO << operation->errorDetails();
    }
    if (m_initialConnection && m_initialConnection->status() == Connection::Status::HasDhKey) {
        setStatus(ConnectionApi::StatusWaitForAuthentication, ConnectionApi::StatusReasonLocal);
        m_initialConnectOperation->setFinished();
    }
}

void ConnectionApiPrivate::onCheckInFinished(PendingOperation *operation)
{
    if (operation != m_authOperation) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                   << "Unexpected auth operation";
        return;
    }

    if (operation->isSucceeded()) {
        AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
        Connection *conn = priv->m_authenticatedConnection;
        if (conn->status() != Connection::Status::Signed) {
            qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                       << "Unexpected connection status"
                                                       << conn->status();
            return;
        }
        if (m_initialConnectOperation) {
            m_initialConnectOperation->deleteLater();
            m_initialConnectOperation = nullptr;
        }
        setMainConnection(conn);
    } else {
        disconnectFromServer();
    }
}

void ConnectionApiPrivate::onNewAuthenticationFinished(PendingOperation *operation)
{
    if (operation != m_authOperation) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO << "Unexpected auth operation";
        return;
    }
    if (!operation->isSucceeded()) {
        setStatus(ConnectionApi::StatusWaitForAuthentication, ConnectionApi::StatusReasonError);
        qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << "TODO?";
        return;
    }
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    Connection *conn = priv->m_authenticatedConnection;
    if (conn->status() != Connection::Status::Signed) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                   << "Unexpected connection status" << conn->status();
        return;
    }
    if (m_initialConnectOperation) {
        m_initialConnectOperation->deleteLater();
        m_initialConnectOperation = nullptr;
    }
    setMainConnection(conn);
}

void ConnectionApiPrivate::onAuthCodeRequired()
{
    setStatus(ConnectionApi::StatusWaitForAuthentication, ConnectionApi::StatusReasonLocal);
}

void ConnectionApiPrivate::onConnectionStatusChanged(Connection *connection, BaseConnection::Status status,
                                                     BaseConnection::StatusReason reason)
{
    if (connection == m_initialConnection) {
        onInitialConnectionStatusChanged(status, reason);
    } else if (connection == m_mainConnection) {
        onMainConnectionStatusChanged(status, reason);
    } else {
        if (connection->status() == Connection::Status::HasDhKey) {
            if (connection->authId() == mainConnection()->authId()) {
                connection->setStatus(Connection::Status::Signed, Connection::StatusReason::Local);
            } else if (m_exportedAuthorizations.contains(connection->dcOption().id)) {
                importAuthentication(connection);
            }
        }
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                  << connection
                                                  << status << reason << "is not processed";
    }

    for (const ConnectionSpec &spec : m_connectionOperations.keys()) {
        ConnectOperation *operation = m_connectionOperations.value(spec);

        if (operation && operation->connection() == connection) {
            if (status == BaseConnection::Status::Disconnected) {
                qCDebug(c_connectionApiLoggingCategory) << __func__
                                                        << "cleanup operation" << operation;
                // operation->deleteLater();
                delete operation;
                connection->deleteLater();

                m_connectionOperations.remove(spec);
                m_connections.remove(spec);
                break;
            }
        }
    }
}

void ConnectionApiPrivate::onMainConnectionStatusChanged(BaseConnection::Status status,
                                                         BaseConnection::StatusReason reason)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO
                                            << m_mainConnection << status << reason;

    const bool keepAliveIsWanted =
            (status == Connection::Status::Signed) ||
            (status == Connection::Status::HasDhKey);
    if (keepAliveIsWanted) {
        if (!m_pingOperation) {
            m_pingOperation = new PingOperation(this);
            m_pingOperation->setSettings(backend()->m_settings);
            m_pingOperation->setRpcLayer(m_mainConnection->rpcLayer());
            connect(m_pingOperation, &PingOperation::pingFailed,
                    this, &ConnectionApiPrivate::onPingFailed);
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
        setStatus(ConnectionApi::StatusConnected, ConnectionApi::StatusReasonLocal);
        PendingOperation *syncOperation = backend()->sync();
        connect(syncOperation, &PendingOperation::finished,
                this, &ConnectionApiPrivate::onSyncFinished);
        syncOperation->startLater();
    }
        break;
    case Connection::Status::Disconnected:
    {
        switch (m_status) {
        case ConnectionApi::StatusDisconnecting:
            setStatus(ConnectionApi::StatusDisconnected, ConnectionApi::StatusReasonLocal);
            break;
        case ConnectionApi::StatusConnected:
        case ConnectionApi::StatusReady:
            onMainConnectionLost();
            break;
        default:
            break;
        }
    }
        break;
    default:
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                  << status << reason << "not processed";
        break;
    }
}

void ConnectionApiPrivate::onMainConnectionLost()
{
    setStatus(ConnectionApi::StatusConnecting, ConnectionApi::StatusReasonError);
    AccountStorage *storage = backend()->accountStorage();
    storage->setAuthKey(m_mainConnection->authKey());
    storage->setAuthId(m_mainConnection->authId());
    storage->setDcInfo(m_mainConnection->dcOption());
    storage->setSessionData(m_mainConnection->rpcLayer()->sessionId(),
                            m_mainConnection->rpcLayer()->contentRelatedMessagesNumber());

    Connection *previousMainConnection = m_mainConnection;
    setMainConnection(nullptr);
    previousMainConnection->deleteLater();
    checkIn();
}

void ConnectionApiPrivate::onMainConnectionRestored()
{
    switch (m_mainConnection->status()) {
    case Connection::Status::HasDhKey:
        break;
    default:
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO
                                                  << "Unexpected connection status"
                                                  << m_mainConnection->status();
        return;
    }

    m_authOperation = new AuthOperation(this);
    m_authOperation->setObjectName(QLatin1String("Auth/CheckIn(Restore)"));
    AuthOperationPrivate *priv = AuthOperationPrivate::get(m_authOperation);
    priv->setBackend(backend());
    priv->setRunMethod(&AuthOperationPrivate::checkAuthorization);
    connect(m_authOperation, &AuthOperation::finished,
            this, &ConnectionApiPrivate::onCheckInFinished);
    m_authOperation->startLater();
}

void ConnectionApiPrivate::onSyncFinished(PendingOperation *operation)
{
    if (operation->isSucceeded()) {
        setStatus(ConnectionApi::StatusReady, ConnectionApi::StatusReasonLocal);
    } else {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                   << "Unexpected sync operation status"
                                                   << operation->errorDetails();
    }
}

void ConnectionApiPrivate::onPingFailed()
{
    qCWarning(c_connectionApiLoggingCategory) << CALL_INFO;
}

void ConnectionApiPrivate::onConnectionError(const QByteArray &errorBytes)
{
    const ConnectionError error(errorBytes);
    qCWarning(c_connectionApiLoggingCategory) << CALL_INFO << error.description() << sender();

    if (error.code() == ConnectionError::InvalidAuthKey) {
        if (sender() == m_initialConnection) {
            m_backend->accountStorage()->invalidateAuthKey(m_initialConnection->authId());
            if (m_initialConnectOperation && !m_initialConnectOperation->isFinished()) {
                m_initialConnectOperation->setFinishedWithError({{PendingOperation::c_text(), error.description()}});
                // Note: operation and initialConnection destroyed on finished
            }
        }
    }
}

void ConnectionApiPrivate::onAllDcOptionsTried()
{
    m_nextServerAddressIndex = 0;
    connectToNextServer();
}

void ConnectionApiPrivate::onRpcExportAuthorizationResult(quint32 dcId, BasePendingRpcResult *rpcOperation)
{
    if (rpcOperation->isFailed()) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                   << "TODO: Implement 'op failed' case" << rpcOperation->errorDetails();
        return;
    }

    AuthRpcLayer::PendingAuthExportedAuthorization *operation = nullptr;
    operation = static_cast<AuthRpcLayer::PendingAuthExportedAuthorization*>(rpcOperation);

    TLAuthExportedAuthorization result;
    operation->getResult(&result);

    if (result.id != dataStorage()->selfUserId()) {
        qCWarning(c_connectionApiLoggingCategory) << CALL_INFO << "Exported id:" << result.id
                                                  << "own:" << dataStorage()->selfUserId();
    }
    if (result.bytes.isEmpty()) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO << "Unexpected empty auth data";
        return;
    }

    m_exportedAuthorizations.insert(dcId, result.bytes);

    for (const ConnectionSpec &spec : m_connectionOperations.keys()) {
        if (spec.dcId != dcId) {
            continue;
        }
        ConnectOperation *op = m_connectionOperations.value(spec);
        if (op->connection()->status() == Connection::Status::HasDhKey) {
            importAuthentication(op->connection());
        }
    }
}

void ConnectionApiPrivate::onRpcImportAuthorizationResult(Connection *connection, BasePendingRpcResult *rpcOperation)
{
    if (rpcOperation->isFailed()) {
        qCCritical(c_connectionApiLoggingCategory) << CALL_INFO
                                                   << "TODO: Implement 'op failed' case" << rpcOperation->errorDetails();
        return;
    }

    AuthRpcLayer::PendingAuthAuthorization *operation = nullptr;
    operation = static_cast<AuthRpcLayer::PendingAuthAuthorization*>(rpcOperation);

    TLAuthAuthorization result;
    operation->getResult(&result);
    connection->setStatus(Connection::Status::Signed, Connection::StatusReason::Remote);
}

void ConnectionApiPrivate::setStatus(ConnectionApi::Status status, ConnectionApi::StatusReason reason)
{
    qCDebug(c_connectionApiLoggingCategory) << CALL_INFO << status << reason;
    Q_Q(ConnectionApi);
    if (m_status == status) {
        return;
    }
    m_status = status;
    emit q->statusChanged(status, reason);
}

void ConnectionApiPrivate::importAuthentication(Connection *connection)
{
    AuthRpcLayer *authLayer = backend()->authLayer();
    BaseRpcLayerExtension::RpcProcessingMethod method = authLayer->rpcProcessingMethod();
    authLayer->setRpcProcessingMethod(nullptr);
    const QByteArray bytes = m_exportedAuthorizations.value(connection->dcOption().id);
    const quint32 userId = dataStorage()->selfUserId();
    AuthRpcLayer::PendingAuthAuthorization *rpcOperation = authLayer->importAuthorization(userId, bytes);
    rpcOperation->setObjectName(rpcOperation->objectName()
                                + QStringLiteral("/dc%1").arg(connection->dcOption().id));

    authLayer->setRpcProcessingMethod(method);

    connection->rpcLayer()->sendRpc(rpcOperation);

    rpcOperation->connectToFinished(this, &ConnectionApiPrivate::onRpcImportAuthorizationResult,
                                    connection,
                                    rpcOperation);
}

// Valid value is a comma-separated list of intervals in msecs. E.g.: "0,5000,30000,60000"
const char *ConnectionApi::reconnectionIntervalsEnvironmentVariableName()
{
    return "TELEGRAM_RECONNECTION_INTERVALS";
}

/*!
    \class Telegram::Client::ConnectionApi
    \brief Provides an API to work with online status and authentication.

    \inmodule TelegramQt
    \ingroup Client
*/

/*!
    \enum Telegram::Client::ConnectionApi::Status

    This enumeration describes the current state of connection.

    \value StatusDisconnected
        There is no active or pending connection.
    \value StatusDisconnecting
        Disconnection is requested, but not proceeded yet.
    \value StatusWaitForConnection
        A connection is requested, but we have to wait for some time before connect.
    \value StatusConnecting
        Connection is in progress.
    \value StatusWaitForAuthentication
        An encrypted connection is established, but the user is not authenticated yet.
    \value StatusConnected
        Connection established, but synchronization is not completed yet.
    \value StatusReady
        The user is authenticated and the initial synchronization finished.
 */
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

int ConnectionApi::remainingTimeToConnect() const
{
    Q_D(const ConnectionApi);
    if ((d->status() != StatusWaitForConnection) || !d->m_connectionQueued) {
        return -1;
    }
    if (!d->m_queuedConnectionTimer) {
        return 0;
    }
    return d->m_queuedConnectionTimer->remainingTime();
}

void ConnectionApi::disconnectFromServer()
{
    Q_D(ConnectionApi);
    return d->disconnectFromServer();
}

bool ConnectionApi::connectRightNow()
{
    Q_D(ConnectionApi);

    if (remainingTimeToConnect() <= 0) {
        return false;
    }

    d->m_queuedConnectionTimer->start(0);
    return true;
}

AuthOperation *ConnectionApi::startAuthentication()
{
    Q_D(ConnectionApi);
    return d->startAuthentication();
}

/*!
  High level API for establishing the main connection needed for the most of RPC calls.

  The operation succeed on connection established and server confirmed the session data.
  The typical reasons to fail are:
  \list 1
      \li There is an already active connection
      \li The account storage has no session information
      \li Incorrect setup (e.g. AccountStorage is not set)
      \li Server declined the session data
      \li The session is explicitly revoked from another session
  \endlist

  \note The operation doesn't fail in case of network errors (it keeps trying to connect).

  \sa PendingOperation::errorDetails()
*/
AuthOperation *ConnectionApi::checkIn()
{
    Q_D(ConnectionApi);
    return d->checkIn();
}

} // Client namespace

} // Telegram namespace
