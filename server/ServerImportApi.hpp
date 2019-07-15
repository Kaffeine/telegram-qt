#ifndef TELEGRAM_QT_SERVER_SERVER_IMPORT_API_HPP
#define TELEGRAM_QT_SERVER_SERVER_IMPORT_API_HPP

#include <QtGlobal>

class MessageData;

namespace Telegram {

namespace Server {

class LocalUser;
class Server;
class Session;

class ServerImportApi
{
public:
    explicit ServerImportApi(Server *server);

    QList<QByteArray> getAuthorizations() const;
    QList<Session *> getSessions() const;
    QList<quint32> getLocalUsers() const;

    void addAuthKey(quint64 authId, const QByteArray &authKey);
    Session *addSession(quint64 sessionId);

protected:
    Server *m_server = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_SERVER_IMPORT_API_HPP
