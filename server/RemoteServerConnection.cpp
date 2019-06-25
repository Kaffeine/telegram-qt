#include "RemoteServerConnection.hpp"

#include "ServerApi.hpp"
#include "TelegramServerUser.hpp"

namespace Telegram {

namespace Server {

RemoteServerConnection::RemoteServerConnection(QObject *parent)
    : QObject(parent)
{
}

void RemoteServerConnection::setRemoteServer(ServerApi *remoteServer)
{
    m_server = remoteServer;
}

AbstractUser *RemoteServerConnection::getUser(const QString &identifier)
{
    return m_server->getAbstractUser(identifier);
}

ServerApi *RemoteServerConnection::api()
{
    return m_server;
}

quint32 RemoteServerConnection::dcId() const
{
    if (!m_server) {
        return 0;
    }
    return m_server->dcId();
}

} // Server namespace

} // Telegram namespace
