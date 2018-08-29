#include "TelegramServerClient.hpp"

#include "TLTypes.hpp"
#include "CTelegramTransport.hpp"
#include "SendPackageHelper.hpp"
#include "TelegramUtils.hpp"
#include "ServerDhLayer.hpp"
#include "ServerRpcLayer.hpp"

#include <QDateTime>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(loggingCategoryRemoteClientConnection, "telegram.server.remoteclient.connection", QtDebugMsg)

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
    m_rpcLayer = new RpcLayer(this);
    m_rpcLayer->setSendPackageHelper(m_sendHelper);
}

RpcLayer *RemoteClientConnection::rpcLayer()
{
    return reinterpret_cast<RpcLayer*>(m_rpcLayer);
}

void RemoteClientConnection::setRpcFactories(const QVector<RpcOperationFactory *> &rpcFactories)
{
    rpcLayer()->setRpcFactories(rpcFactories);
}

void RemoteClientConnection::setServerApi(ServerApi *api)
{
    rpcLayer()->setServerApi(api);
}

void RemoteClientConnection::setSession(Session *session)
{
    rpcLayer()->setSession(session);
}

} // Server

} // Telegram
