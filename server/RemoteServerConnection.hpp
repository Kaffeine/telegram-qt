#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>

namespace Telegram {

class PendingVariant;

namespace Server {

class AbstractServerApi;
class AbstractUser;
class LocalServerApi;

class AbstractServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit AbstractServerConnection(QObject *parent = nullptr);

    virtual QStringList supportedSchemes() const { return {}; }

    virtual quint32 dcId() const = 0;

    virtual AbstractUser *getUser(const quint32 userId) const = 0;
    virtual AbstractUser *getUser(const QString &identifier) const = 0;
    virtual AbstractServerApi *api() = 0;

    virtual QByteArray getForeingUserAuthorization(quint32 userId) = 0;

    virtual PendingVariant *searchContacts(const QString &query, quint32 limit) = 0;
};

class RemoteServerConnection : public AbstractServerConnection
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const override;

    void setRemoteServer(LocalServerApi *remoteServer);

    AbstractUser *getUser(const quint32 userId) const override;
    AbstractUser *getUser(const QString &identifier) const override;
    AbstractServerApi *api();

    QByteArray getForeingUserAuthorization(quint32 userId);

    PendingVariant *searchContacts(const QString &query, quint32 limit) override;

protected:
    LocalServerApi *m_server = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
