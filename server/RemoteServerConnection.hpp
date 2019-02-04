#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>

namespace Telegram {

namespace Server {

class ServerApi;
class AbstractUser;

class RemoteServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const;

    void setRemoteServer(ServerApi *remoteServer);

    AbstractUser *getUser(const QString &identifier);
    ServerApi *api();

protected:
    ServerApi *m_server = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
