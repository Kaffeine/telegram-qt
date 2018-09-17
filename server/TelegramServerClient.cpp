#include "TelegramServerClient.hpp"

#include "TLTypes.hpp"
#include "CTelegramTransport.hpp"
#include "SendPackageHelper.hpp"
#include "TelegramUtils.hpp"
#include "ServerApi.hpp"
#include "ServerDhLayer.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"

#include <QDateTime>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(loggingCategoryRemoteClientConnection, "telegram.server.remoteclient.connection", QtWarningMsg)

namespace Telegram {

namespace Server {

class SendPackageHelper : public BaseSendPackageHelper
{
public:
    explicit SendPackageHelper(BaseConnection *connection) :
        BaseSendPackageHelper()
    {
        m_connection = connection;
    }

    quint64 newMessageId(SendMode mode) override
    {
        quint64 ts = TelegramUtils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
        if (mode == SendMode::ServerReply) {
            ts &= ~quint64(3);
            ts |= 1;
        } else if (mode == SendMode::ServerInitiative) {
            ts |= 3;
        } else {
            qCWarning(loggingCategoryRemoteClientConnection) << Q_FUNC_INFO << "Invalid mode";
        }
        return m_connection->transport()->getNewMessageId(ts);
    }

    void sendPackage(const QByteArray &package) override
    {
        return m_connection->transport()->sendPackage(package);
    }
};

RemoteClientConnection::RemoteClientConnection(QObject *parent) :
    BaseConnection(parent)
{
    m_sendHelper = new SendPackageHelper(this);
    m_dhLayer = new DhLayer(this);
    m_dhLayer->setSendPackageHelper(m_sendHelper);
    connect(m_dhLayer, &BaseDhLayer::stateChanged, this, &RemoteClientConnection::onClientDhStateChanged);
    m_rpcLayer = new RpcLayer(this);
    m_rpcLayer->setSendPackageHelper(m_sendHelper);
}

RpcLayer *RemoteClientConnection::rpcLayer() const
{
    return reinterpret_cast<RpcLayer*>(m_rpcLayer);
}

void RemoteClientConnection::setRpcFactories(const QVector<RpcOperationFactory *> &rpcFactories)
{
    rpcLayer()->setRpcFactories(rpcFactories);
}

ServerApi *RemoteClientConnection::api() const
{
    return rpcLayer()->api();
}

void RemoteClientConnection::setServerApi(ServerApi *api)
{
    rpcLayer()->setServerApi(api);
}

Session *RemoteClientConnection::session() const
{
    return rpcLayer()->session();
}

void RemoteClientConnection::setSession(Session *session)
{
    session->setConnection(this);
    rpcLayer()->setSession(session);
}

void RemoteClientConnection::onClientDhStateChanged()
{
    if (m_dhLayer->state() == BaseDhLayer::State::HasKey) {
        Session *session = api()->createSession(m_sendHelper->authId(), m_sendHelper->authKey(), m_transport->remoteAddress());
        setSession(session);
    }
}

void RemoteClientConnection::sendKeyError()
{
    static const QByteArray errorPackage = QByteArray::fromHex(QByteArrayLiteral("6cfeffff"));
    m_transport->sendPackage(errorPackage);
}

bool RemoteClientConnection::processAuthKey(quint64 authKeyId)
{
    if (authKeyId == m_sendHelper->authId()) {
        return true;
    }
    if (!m_sendHelper->authId()) {
        Session *session = api()->getSessionByAuthId(authKeyId);
        if (session) {
            setSession(session);
            m_sendHelper->setAuthKey(session->authKey);
            m_sendHelper->setServerSalt(api()->serverSalt());
            return true;
        }
    }

    disconnect(m_transport, &CTelegramTransport::packageReceived, this, &RemoteClientConnection::onTransportPackageReceived);
    connect(m_transport, &CTelegramTransport::packageReceived, this, &RemoteClientConnection::sendKeyError);
    setStatus(Status::Failed, StatusReason::Local);
    sendKeyError();
    return false;
}

} // Server

} // Telegram
