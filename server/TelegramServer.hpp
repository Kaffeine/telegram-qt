#ifndef TELEGRAMSERVER_HPP
#define TELEGRAMSERVER_HPP

#include <QObject>

#include "RsaKey.hpp"
#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

#include "ServerApi.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QTimer)

#include <QHash>
#include <QSet>
#include <QVector>

namespace Telegram {

namespace Server {

class LocalUser;
class Session;
class RemoteClientConnection;
class RemoteServerConnection;
class AbstractUser;
class RpcOperationFactory;

class Server : public QObject, public ServerApi
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void setDcOption(const DcOption &option);

    void setServerPrivateRsaKey(const Telegram::RsaKey &key);

    bool start();
    void stop();
    void loadData();

    void setServerConfiguration(const DcConfiguration &config);
    void addServerConnection(RemoteServerConnection *remoteServer);

    QSet<RemoteClientConnection*> getConnections() { return m_activeConnections; }

    quint32 getDcIdForUserIdentifier(const QString &phoneNumber);

    void setAuthorizationProvider(Authorization::Provider *provider);

    // ServerAPI:
    Authorization::Provider *getAuthorizationProvider() override { return m_authProvider; }

    DcConfiguration serverConfiguration() const override { return m_dcConfiguration; }
    quint32 dcId() const override { return m_dcOption.id; }

    PhoneStatus getPhoneStatus(const QString &identifier) const override;
    PasswordInfo getPassword(const QString &identifier) override;
    bool checkPassword(const QString &identifier, const QByteArray &hash) override;
    bool identifierIsValid(const QString &identifier) const override;
    QString normalizeIdentifier(const QString &identifier) const override;

    AbstractUser *getAbstractUser(quint32 userId) const override;
    AbstractUser *getAbstractUser(const QString &identifier) const override;
    AbstractUser *getRemoteUser(quint32 userId) const;
    AbstractUser *getRemoteUser(const QString &identifier) const;

    Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const override;

    LocalUser *getUser(const QString &identifier) const override;
    LocalUser *getUser(quint32 userId) const override;
    AbstractUser *getUser(const TLInputUser &inputUser, LocalUser *self) const override;
    AbstractUser *tryAccessUser(quint32 userId, quint64 accessHash, LocalUser *applicant) const override;
    LocalUser *addUser(const QString &identifier) override;

    Session *createSession(quint64 authId, const QByteArray &authKey, const QString &address) override;
    Session *getSessionByAuthId(quint64 authKeyId) const override;
    void bindUserSession(LocalUser *user, Session *session) override;

    void insertUser(LocalUser *user);

signals:

public slots:

protected slots:
    void onNewConnection();

protected:
    void onClientConnectionStatusChanged();

protected:
    Authorization::Provider *m_authProvider = nullptr;

private:
    QTcpServer *m_serverSocket;
    DcOption m_dcOption;
    Telegram::RsaKey m_key;

    QHash<QString, quint32> m_phoneToUserId;
    QHash<quint64, Session*> m_authIdToSession;
    QHash<quint32, LocalUser*> m_users; // userId to User
    QSet<RemoteClientConnection*> m_activeConnections;
    QSet<RemoteServerConnection*> m_remoteServers;
    QVector<RpcOperationFactory*> m_rpcOperationFactories;
    DcConfiguration m_dcConfiguration;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVER_HPP
