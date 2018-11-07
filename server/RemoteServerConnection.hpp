#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>

namespace Telegram {

namespace Server {

class ServerApi;
class RemoteUser;

class RemoteServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const;

    void setRemoteServer(ServerApi *remoteServer);

    RemoteUser *getUser(const QString &identifier);
    ServerApi *api();

protected:
    ServerApi *m_server = nullptr;
};

} // Server

} // Telegram

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
