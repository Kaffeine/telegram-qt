#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>

namespace Telegram {

namespace Server {

class AbstractServerApi;
class AbstractUser;
class LocalServerApi;

class RemoteServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const;

    void setRemoteServer(LocalServerApi *remoteServer);

    AbstractUser *getUser(const quint32 userId);
    AbstractUser *getUser(const QString &identifier);
    AbstractServerApi *api();

    QByteArray getForeingUserAuthorization(quint32 userId);

protected:
    LocalServerApi *m_server = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
