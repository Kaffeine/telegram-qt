#include "RemoteServerConnection.hpp"

#include "LocalServerApi.hpp"
#include "TelegramServerUser.hpp"

namespace Telegram {

namespace Server {

AbstractServerConnection::AbstractServerConnection(QObject *parent)
    : QObject(parent)
{
}

RemoteServerConnection::RemoteServerConnection(QObject *parent)
    : AbstractServerConnection(parent)
{
}

void RemoteServerConnection::setRemoteServer(LocalServerApi *remoteServer)
{
    m_server = remoteServer;
}

AbstractUser *RemoteServerConnection::getUser(const quint32 userId) const
{
    return m_server->getUser(userId);
}

AbstractUser *RemoteServerConnection::getUser(const QString &identifier) const
{
    return m_server->getUser(identifier);
}

AbstractServerApi *RemoteServerConnection::api()
{
    return m_server;
}

QByteArray RemoteServerConnection::getForeingUserAuthorization(quint32 userId)
{
    return m_server->generateExportedAuthorization(userId);
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
