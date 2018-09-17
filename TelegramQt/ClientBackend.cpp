#include "ClientBackend.hpp"
#include "CClientTcpTransport.hpp"
#include "ClientSettings.hpp"
#include "AccountStorage.hpp"
#include "ClientConnection.hpp"
#include "Client.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcHelpLayer.hpp"
#include "DataStorage.hpp"
#include "RpcError.hpp"
#include "Debug_p.hpp"

#include "Operations/ClientAuthOperation.hpp"
#include "Operations/ClientHelpOperation.hpp"
#include "Operations/ConnectionOperation.hpp"
#include "PendingRpcOperation.hpp"

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
    BaseRpcLayerExtension::RpcProcessingMethod rpcProcessMethod = [b](PendingRpcOperation *operation) mutable {
        b->getDefaultConnection()->rpcLayer()->sendRpc(operation);
    };

    // Generated low-level layer initialization
    m_accountLayer = new AccountRpcLayer(this);
    m_accountLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_authLayer = new AuthRpcLayer(this);
    m_authLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_botsLayer = new BotsRpcLayer(this);
    m_botsLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_channelsLayer = new ChannelsRpcLayer(this);
    m_channelsLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_contactsLayer = new ContactsRpcLayer(this);
    m_contactsLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_helpLayer = new HelpRpcLayer(this);
    m_helpLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_langpackLayer = new LangpackRpcLayer(this);
    m_langpackLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_messagesLayer = new MessagesRpcLayer(this);
    m_messagesLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_paymentsLayer = new PaymentsRpcLayer(this);
    m_paymentsLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_phoneLayer = new PhoneRpcLayer(this);
    m_phoneLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_photosLayer = new PhotosRpcLayer(this);
    m_photosLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_stickersLayer = new StickersRpcLayer(this);
    m_stickersLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_updatesLayer = new UpdatesRpcLayer(this);
    m_updatesLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_uploadLayer = new UploadRpcLayer(this);
    m_uploadLayer->setRpcProcessingMethod(rpcProcessMethod);
    m_usersLayer = new UsersRpcLayer(this);
    m_usersLayer->setRpcProcessingMethod(rpcProcessMethod);
    // End of generated low-level layer initialization
}

PendingOperation *Backend::connectToServer(const QVector<DcOption> &dcOptions)
{
    if (m_connectToServerOperation) {
        if (dcOptions.contains(m_connectToServerOperation->connection()->dcOption())) {
            switch (m_connectToServerOperation->connection()->status()) {
            case BaseConnection::Status::Connecting:
            case BaseConnection::Status::Connected:
            case BaseConnection::Status::Authenticated:
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
    connection = createConnection(dcOptions.first());
    m_connectToServerOperation = connection->connectToDc();
    connect(m_connectToServerOperation, &PendingOperation::finished, this, &Backend::onConnectOperationFinished);
    return m_connectToServerOperation;
}

AuthOperation *Backend::signIn()
{
    if (m_signedIn) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Already signed in"), this);
    }
    if (!m_settings || !m_settings->isValid()) {
        qWarning() << "Invalid settings";
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Invalid settings"), this);
    }
    if (m_authOperation && !m_authOperation->isFinished()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Auth operation is already in progress"), this);
    }

    m_authOperation = new AuthOperation(this);
    PendingOperation *connectionOperation = connectToServer(m_settings->serverConfiguration());
    m_authOperation->runAfter(connectionOperation);
    m_authOperation->setRunMethod(&AuthOperation::requestAuthCode);
    return m_authOperation;
}

AuthOperation *Backend::checkIn()
{
    if (m_authOperation && !m_authOperation->isFinished()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("Auth operation is already in progress"), this);
    }
    if (!m_accountStorage->hasMinimalDataSet()) {
        return PendingOperation::failOperation<AuthOperation>
                (QStringLiteral("No minimal account data set"), this);
    }
    m_authOperation = new AuthOperation(this);
    PendingOperation *connectionOperation = connectToServer({m_accountStorage->dcInfo()});
    m_authOperation->runAfter(connectionOperation);
    m_authOperation->setRunMethod(&AuthOperation::checkAuthorization);
    m_connectToServerOperation->connection()->setAuthKey(m_accountStorage->authKey());
    return m_authOperation;
}

PendingOperation *Backend::getDcConfig()
{
    if (m_getConfigOperation) {
        if (!m_getConfigOperation->isFailed()) {
            return m_getConfigOperation;
        }
        // Delete the failed operation
        m_getConfigOperation->deleteLater();
        m_getConfigOperation = nullptr;
    }

    HelpOperation *op = new HelpOperation(this);
    op->setBackend(this);
    op->setRunMethod(&HelpOperation::requestDcConfig);
    op->startLater();
    m_getConfigOperation = op;
    connect(op, &PendingOperation::finished, this, &Backend::onGetDcConfigurationFinished);
    return m_getConfigOperation;
}

Connection *Backend::createConnection(const DcOption &dcOption)
{
    Connection *connection = new Connection(this);
    connection->setDcOption(dcOption);
    connection->setServerRsaKey(m_settings->serverRsaKey());
    connection->rpcLayer()->setAppInformation(m_appInformation);
    connection->setDeltaTime(m_accountStorage->deltaTime());

    TcpTransport *transport = new TcpTransport(connection);
    transport->setProxy(m_settings->proxy());

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

Connection *Backend::ensureConnection(const ConnectionSpec &dcSpec)
{
    qWarning() << Q_FUNC_INFO << dcSpec.dcId << dcSpec.flags;
    ConnectionSpec spec = dcSpec;
    spec.flags |= ConnectionSpec::RequestFlag::Ipv4Only; // Enable only ipv4 for now
    if (!m_connections.contains(dcSpec)) {
        const DcOption opt = dataStorage()->serverConfiguration().getOption(spec);
        if (!opt.isValid()) {
            qWarning() << Q_FUNC_INFO << "Unable to find suitable DC";
            return nullptr;
        }
        m_connections.insert(dcSpec, createConnection(opt));
    }
    return m_connections.value(dcSpec);
}

void Backend::setDcForLayer(const ConnectionSpec &dcSpec, BaseRpcLayerExtension *layer)
{
    Backend *b = this;
    BaseRpcLayerExtension::RpcProcessingMethod sendMethod = [b, dcSpec](PendingRpcOperation *operation) mutable {
        b->ensureConnection(dcSpec)->rpcLayer()->sendRpc(operation);
    };
    layer->setRpcProcessingMethod(sendMethod);
}

void Backend::setMainConnection(Connection *connection)
{
    m_mainConnection = connection;
    connect(m_mainConnection, &BaseConnection::statusChanged, this, &Backend::onMainConnectionStatusChanged);
    onMainConnectionStatusChanged();
}

void Backend::onConnectOperationFinished(PendingOperation *operation)
{
    if (!operation->isSucceeded()) {
        m_connectToServerOperation = nullptr;
        operation->deleteLater();
        return;
    }
    getDcConfig();
}

void Backend::onGetDcConfigurationFinished(PendingOperation *operation)
{
    if (!operation->isSucceeded()) {
        qWarning() << Q_FUNC_INFO << "Unable to get dc configuration" << operation->errorDetails();
        return;
    }
    for (PendingRpcOperation *operation : m_queuedRedirectedOperations) {
        routeOperation(operation);
    }
    m_queuedRedirectedOperations.clear();
}

void Backend::processSeeOthers(PendingRpcOperation *operation)
{
    qWarning() << Q_FUNC_INFO << "operation"
               << TLValue::firstFromArray(operation->requestData());
    if (!getDcConfig()->isFinished()) {
        qWarning() << Q_FUNC_INFO << "Queued";
        m_queuedRedirectedOperations.append(operation);
        return;
    }
    routeOperation(operation);
}

void Backend::routeOperation(PendingRpcOperation *operation)
{
    qWarning() << Q_FUNC_INFO << "operation"
               << TLValue::firstFromArray(operation->requestData());
    const quint32 dcId = operation->rpcError()->argument;
    operation->clearResult();
    ConnectionSpec spec(dcId);

    TLValue requestType = TLValue::firstFromArray(operation->requestData());
    switch (requestType) {
    case TLValue::UploadGetFile:
        spec.flags |= ConnectionSpec::RequestFlag::MediaOnly;
        break;
    default:
        break;
    }
    Connection *connection = ensureConnection(spec);
    if (!connection) {
        qWarning() << Q_FUNC_INFO << "Unable to get connection for operation"
                   << TLValue::firstFromArray(operation->requestData()) << "dc spec" << spec.dcId << spec.flags;
        operation->deleteLater();
        return;
    }
    connection->processSeeOthers(operation);
}

void Backend::onMainConnectionStatusChanged()
{
    if (!m_mainConnection) {
        return;
    }
    setSignedIn(m_mainConnection->status() == Connection::Status::Signed);
    if (isSignedIn()) {
        syncAccountToStorage();
    }
}

bool Backend::syncAccountToStorage()
{
    if (!m_mainConnection) {
        return false;
    }
    switch (m_mainConnection->status()) {
    case Connection::Status::Authenticated:
    case Connection::Status::Signed:
        break;
    default:
        return false;
    }
    if (!m_mainConnection->dcOption().isValid()) {
        connect(getDcConfig(), &PendingOperation::finished, this, &Backend::syncAccountToStorage);
        return false;
    }
    m_accountStorage->setAuthKey(m_mainConnection->authKey());
    m_accountStorage->setAuthId(m_mainConnection->authId());
    m_accountStorage->setDcInfo(m_mainConnection->dcOption());
    m_accountStorage->setDeltaTime(m_mainConnection->deltaTime());
    m_accountStorage->sync();
    return true;
}

void Backend::setSignedIn(bool signedIn)
{
    if (m_signedIn == signedIn) {
        return;
    }
    m_signedIn = signedIn;
    emit m_client->signedInChanged(signedIn);
}

} // Client namespace

} // Telegram namespace
