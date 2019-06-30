#ifndef TELEGRAMSERVER_HPP
#define TELEGRAMSERVER_HPP

#include <QObject>

#include "RsaKey.hpp"
#include "MTProto/TLTypes.hpp"
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

class Server : public QObject, public LocalServerApi
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

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
    void setStorage(Storage *storage);

    void registerAuthKey(quint64 authId, const QByteArray &authKey);

    // ServerAPI:
    Authorization::Provider *getAuthorizationProvider() override { return m_authProvider; }

    DcConfiguration serverConfiguration() const override { return m_dcConfiguration; }
    quint32 dcId() const override { return m_dcOption.id; }

    PhoneStatus getPhoneStatus(const QString &identifier) const override;
    PasswordInfo getPassword(const QString &identifier) override;
    bool checkPassword(const QString &identifier, const QByteArray &hash) override;
    bool identifierIsValid(const QString &identifier) const override;
    QString normalizeIdentifier(const QString &identifier) const override;

    Storage *storage() const override { return m_storage; }

    AbstractUser *getAbstractUser(quint32 userId) const override;
    AbstractUser *getAbstractUser(const QString &identifier) const override;
    AbstractUser *getAbstractUser(const TLInputUser &inputUser, const LocalUser *applicant) const override;
    AbstractUser *getAbstractUser(quint32 userId, quint64 accessHash, const LocalUser *applicant) const override;
    AbstractUser *getRemoteUser(quint32 userId) const;
    AbstractUser *getRemoteUser(const QString &identifier) const;

    Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const override;
    MessageRecipient *getRecipient(const TLInputPeer &peer, const LocalUser *applicant) const override;
    MessageRecipient *getRecipient(const Peer &peer) const override;

    QVector<quint32> getPeerWatchers(const Peer &peer) const override;

    LocalUser *getUser(const QString &identifier) const override;
    LocalUser *getUser(quint32 userId) const override;
    Peer getPeerByUserName(const QString &userName) const override;
    LocalUser *addUser(const QString &identifier) override;

    bool bindClientSession(RemoteClientConnection *client, quint64 sessionId) override;
    Session *getSessionById(quint64 sessionId) const override;
    void bindUserSession(LocalUser *user, Session *session) override;
    bool setUserName(LocalUser *user, const QString &newUsername) override;
    QByteArray getAuthKeyById(quint64 authId) const override;
    quint32 getUserIdByAuthId(quint64 authId) const override;
    void addUserAuthorization(LocalUser *user, quint64 authKeyId);

    QVector<UpdateNotification> processMessage(MessageData *messageData) override;
    QVector<UpdateNotification> createUpdates(UpdateNotification::Type updateType,
                                              LocalUser *applicant,
                                              Session *excludeSession) const override;

    void queueUpdates(const QVector<UpdateNotification> &notifications) override;

    void insertUser(LocalUser *user);

signals:

public slots:

protected slots:
    void onNewConnection();

protected:
    Session *addSession(quint64 sessionId);

    void onClientConnectionStatusChanged();

protected:
    Authorization::Provider *m_authProvider = nullptr;
    Storage *m_storage = nullptr;

private:
    QTcpServer *m_serverSocket;
    DcOption m_dcOption;
    Telegram::RsaKey m_key;

    QSet<RemoteClientConnection*> m_activeConnections;
    QSet<RemoteServerConnection*> m_remoteServers;
    QVector<RpcOperationFactory*> m_rpcOperationFactories;
    DcConfiguration m_dcConfiguration;

    // Data
    QHash<quint64, QByteArray> m_authorizations; // Auth id to auth key
    QHash<quint32, LocalUser*> m_users; // userId to User
    QHash<quint64, Session*> m_sessions; // Session id to Session

    // Maps for faster lookup
    QHash<QString, quint32> m_phoneToUserId;
    QHash<QString, quint32> m_usernameToUserId;
    QHash<quint64, quint32> m_authToUserId;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVER_HPP
