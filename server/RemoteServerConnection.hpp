#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>
#include <QVector>

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

class Server;
class ServerApi;
class RemoteUser;

class RemoteServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const;

    void setRemoteServer(Server *remoteServer);

    RemoteUser *getUser(const QString &identifier);
    ServerApi *api();

protected:
    Server *m_server = nullptr;
};

} // Server

} // Telegram

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
