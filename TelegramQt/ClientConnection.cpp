#include "ClientConnection.hpp"

#include "ApiUtils.hpp"
#include "ClientDhLayer.hpp"
#include "ClientRpcLayer.hpp"
#include "CTelegramTransport.hpp"
#include "SendPackageHelper.hpp"
#include "Utils.hpp"
#include "Debug_p.hpp"

#include "PendingRpcOperation.hpp"
#include "Operations/ConnectionOperation.hpp"

#include <QDateTime>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientConnectionCategory, "telegram.client.connection", QtWarningMsg)

namespace Telegram {

namespace Client {

class SendPackageHelper : public BaseMTProtoSendHelper
{
public:
    explicit SendPackageHelper(BaseConnection *connection) :
        BaseMTProtoSendHelper()
    {
        m_connection = connection;
    }

    quint64 newMessageId(SendMode mode) override
    {
        quint64 ts = Telegram::Utils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch() + deltaTime() * 1000);
        if (mode == SendMode::Client) {
            ts &= ~quint64(3);
        } else {
            qCWarning(c_clientConnectionCategory) << Q_FUNC_INFO << "Invalid mode";
        }
        return m_connection->transport()->getNewMessageId(ts);
    }

    void sendPacket(const QByteArray &package) override
    {
        return m_connection->transport()->sendPacket(package);
    }
};

/*
    \class Telegram::Client::Connection
    \brief Client-specific connection with DH and RPC layers.
    \inmodule TelegramQt
    \ingroup Client
*/
Connection::Connection(QObject *parent) :
    BaseConnection(parent)
{
    m_sendHelper = new SendPackageHelper(this);
    m_dhLayer = new DhLayer(this);
    m_dhLayer->setSendPackageHelper(m_sendHelper);
    connect(m_dhLayer, &BaseDhLayer::stateChanged, this, &Connection::onClientDhStateChanged);
    m_rpcLayer = new RpcLayer(this);
    m_rpcLayer->setSendHelper(m_sendHelper);
}

void Connection::setDcOption(const DcOption &dcOption)
{
    m_dcOption = dcOption;
    setObjectName(QStringLiteral("Client(dc%1, flags %2)")
                  .arg(dcOption.id)
                  .arg(dcOption.flags)
                  );
    m_dhLayer->setObjectName(objectName());
    m_rpcLayer->setObjectName(objectName());
}

qint32 Connection::deltaTime() const
{
    return m_sendHelper->deltaTime();
}

void Connection::setDeltaTime(const qint32 newDt)
{
    m_sendHelper->setDeltaTime(newDt);
}

Connection *Connection::fromOperation(PendingRpcOperation *operation)
{
    return reinterpret_cast<Telegram::Client::Connection*>(operation->getConnection());
}

RpcLayer *Connection::rpcLayer()
{
    return reinterpret_cast<RpcLayer*>(m_rpcLayer);
}

/*!
  \fn void Connection::connectToDc()

  This method establish Transport (TCP/UDP/HTTP) level connection.

  \sa BaseTransport::connectToHost()
*/
void Connection::connectToDc()
{
    qCDebug(c_clientConnectionCategory) << CALL_INFO << m_dcOption.id << m_dcOption.address << m_dcOption.port;

    if (transport()->state() != QAbstractSocket::UnconnectedState) {
        transport()->disconnectFromHost(); // Ensure that there is no connection
    }

    setStatus(Status::Connecting, StatusReason::Local);
    transport()->connectToHost(m_dcOption.address, m_dcOption.port);
}

void Connection::onClientDhStateChanged()
{
    qCDebug(c_clientConnectionCategory) << CALL_INFO
                                        << m_dcOption.id << m_dcOption.address << "DH status:" << m_dhLayer->state();
    if (m_dhLayer->state() == BaseDhLayer::State::HasKey) {
        if (!m_rpcLayer->sessionId()) {
            rpcLayer()->startNewSession();
        }
        rpcLayer()->setServerSalt(m_dhLayer->serverSalt());
        if (!m_queuedOperations.isEmpty()) {
            for (PendingRpcOperation *operation : m_queuedOperations) {
                quint64 messageId = rpcLayer()->sendRpc(operation);
                qCDebug(c_clientConnectionCategory) << "Dequeue operation"
                                                    << TLValue::firstFromArray(operation->requestData())
                                                    << "with new id" << messageId;
            }
            m_queuedOperations.clear();
        }
    }
}

bool Connection::processAuthKey(quint64 authKeyId)
{
    return authKeyId == m_sendHelper->authId();
}

} // Client namespace

} // Telegram namespace
