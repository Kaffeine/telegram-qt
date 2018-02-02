#include "RemoteServerConnection.hpp"
#include "TelegramServer.hpp"
#include "TelegramServerUser.hpp"

namespace Telegram {

namespace Server {

RemoteServerConnection::RemoteServerConnection(QObject *parent)
    : QObject(parent)
{
}

void RemoteServerConnection::setRemoteServer(Server *remoteServer)
{
    m_server = remoteServer;
}

RemoteUser *RemoteServerConnection::getUser(const QString &identifier)
{
    return m_server->getLocalUser(identifier);
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

} // Server

} // Telegram
