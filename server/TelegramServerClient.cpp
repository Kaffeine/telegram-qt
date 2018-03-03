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
        BaseSendPackageHelper(),
        m_connection(connection)
    {
    }

    quint64 newMessageId(bool isReply) override
    {
        quint64 ts = TelegramUtils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
        if (isReply) {
            ts &= ~quint64(3);
            ts |= 1;
        } else {
            ts |= 3;
        }
        return m_connection->transport()->getNewMessageId(ts);
    }

    void sendPackage(const QByteArray &package) override
    {
        return m_connection->transport()->sendPackage(package);
    }

protected:
    BaseConnection *m_connection;
};

RemoteClientConnection::RemoteClientConnection(QObject *parent) :
    BaseConnection(parent)
{
    m_senderHelper = new SendPackageHelper(this);
    m_dhLayer = new DhLayer(this);
    m_dhLayer->setSendPackageHelper(m_senderHelper);
    m_rpcLayer = new RpcLayer(this);
    m_rpcLayer->setSendPackageHelper(m_senderHelper);
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

void RemoteClientConnection::setUser(User *user)
{
    rpcLayer()->setUser(user);
}

} // Server

} // Telegram
