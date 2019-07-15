#include "ServerImportApi.hpp"

#include "AuthService.hpp"
#include "TelegramServer.hpp"

namespace Telegram {

namespace Server {

ServerImportApi::ServerImportApi(Server *server)
    : m_server(server)
{

}

QList<QByteArray> ServerImportApi::getAuthorizations() const
{
    return m_server->authService()->m_authorizations.values();
}

QList<Session *> ServerImportApi::getSessions() const
{
    return m_server->m_sessions.values();
}

QList<quint32> ServerImportApi::getLocalUsers() const
{
    return m_server->m_users.keys();
}

void ServerImportApi::addAuthKey(quint64 authId, const QByteArray &authKey)
{
    m_server->authService()->registerAuthKey(authId, authKey);
}

Session *ServerImportApi::addSession(quint64 sessionId)
{
    return m_server->addSession(sessionId);
}

} // Server namespace

} // Telegram namespace
