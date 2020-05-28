#ifndef TELEGRAMSERVER_HPP
#define TELEGRAMSERVER_HPP

#include <QObject>

#include "MTProto/TLTypes.hpp"
#include "RsaKey.hpp"
#include "LocalServerApi.hpp"
#include "TelegramNamespace.hpp"

#include <QHash>
#include <QHostAddress>
#include <QSet>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QTimer)

namespace Telegram {

namespace Server {

namespace Authorization {

class Provider;

} // Authorization namespace

class LocalUser;
class MediaService;
class Session;
class RemoteClientConnection;
class RemoteServerConnection;
class AbstractUser;
class PostBox;
class RpcOperationFactory;

class Server : public QObject, public LocalServerApi
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    void setListenAddress(const QHostAddress &address);
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
    void setMessageService(MessageService *messageService);

    DcConfiguration serverConfiguration() const override { return m_dcConfiguration; }
    quint32 dcId() const override { return m_dcOption.id; }

    PhoneStatus getPhoneStatus(const QString &identifier) const override;
    bool identifierIsValid(const QString &identifier) const override;
    QString normalizeIdentifier(const QString &identifier) const override;

    AuthService *authService() const override { return m_authService; }
    IMediaService *mediaService() const override { return m_mediaServiceIface; }
    MessageService *messageService() const override { return m_messageService; }

    AbstractUser *getAbstractUser(quint32 userId) const override;
    AbstractUser *getAbstractUser(const QString &identifier) const override;
    AbstractUser *getAbstractUser(const TLInputUser &inputUser, const LocalUser *applicant) const override;
    AbstractUser *getAbstractUser(quint32 userId, quint64 accessHash, const LocalUser *applicant) const override;
    AbstractUser *getRemoteUser(quint32 userId) const;
    AbstractUser *getRemoteUser(const QString &identifier) const;

    QVector<PostBox *> getPostBoxes(const Peer &targetPeer, AbstractUser *applicant = nullptr) const override;

    RemoteServerConnection *getRemoteServer(quint32 dcId) const;

    Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const override;
    MessageRecipient *getRecipient(const TLInputPeer &peer, const LocalUser *applicant) const override;
    MessageRecipient *getRecipient(const Peer &peer) const override;

    QVector<quint32> getPeerWatchers(const Peer &peer) const override;

    LocalUser *getUser(const QString &identifier) const override;
    LocalUser *getUser(quint32 userId) const override;
    Peer getPeerByUserName(const QString &userName) const override;
    LocalUser *addUser(const QString &identifier) override;

    bool bindClientConnectionSession(RemoteClientConnection *connection, quint64 sessionId) override;

    Session *getSessionById(quint64 sessionId) const override;
    void bindUserSession(AuthorizedUser *user, Session *session) override;
    bool usernameIsValid(const QString &username) const override;
    bool setUserName(LocalUser *user, const QString &newUsername, RpcError *error = nullptr) override;
    bool setUserOnline(LocalUser *user, bool online, Session *fromSession = nullptr) override;

    PendingOperation *exportAuthorization(quint32 dcId, quint32 userId, QByteArray *outputAuthBytes) override;
    QByteArray generateExportedAuthorization(quint32 userId) override;
    AuthorizedUser *getAuthorizedUser(quint32 userId, const QByteArray &authBytes) override;

    PendingOperation *searchContacts(const QString &query, quint32 limit, QVector<Peer> *output);

    void reportMessageRead(const MessageData *messageData) override;

    QVector<UpdateNotification> processMessage(MessageData *messageData) override;
    QVector<UpdateNotification> processMessageEdit(MessageData *messageData) override;
    QVector<UpdateNotification> createUpdates(UpdateNotification::Type updateType,
                                              LocalUser *applicant,
                                              Session *excludeSession) const override;

    AbstractUser *importUserContact(LocalUser *user, const UserContact &contact) override;

    bool bakeUpdate(TLUpdate *update, const UpdateNotification &notification, QSet<Peer> *interestingPeers) const override;
    void queueUpdates(const QVector<UpdateNotification> &notifications) override;
    void queueServerUpdates(const QVector<UpdateNotification> &notificationsForServer) override;
    QVector<UpdateNotification> processServerUpdates(const QVector<UpdateNotification> &notificationsForServer);

    void insertUser(LocalUser *user);
    bool isLocalBox(const PostBox *box) const;

signals:

public slots:

protected slots:
    void onNewConnection();

protected:
    Session *addSession(quint64 sessionId);

    void onClientConnectionStatusChanged();
    void onUserSessionStatusChanged(LocalUser *user, Session *session);

    void reportLocalMessageRead(LocalUser *user, const UpdateNotification &notification);
    void setSessionConnection(Session *session, RemoteClientConnection *connection);

protected:
    AuthService *m_authService = nullptr;
    IMediaService *m_mediaServiceIface = nullptr;
    MediaService *m_mediaService = nullptr;
    MessageService *m_messageService = nullptr;

private:
    QTcpServer *m_serverSocket;
    QHostAddress m_listenAddress;
    DcOption m_dcOption;
    Telegram::RsaKey m_key;

    QSet<RemoteClientConnection*> m_activeConnections;
    QSet<RemoteServerConnection*> m_remoteServers;
    QVector<RpcOperationFactory*> m_rpcOperationFactories;
    DcConfiguration m_dcConfiguration;

    // Session data
    QHash<quint32, QByteArray> m_exportedAuthorizations; // userId to auth bytes
    QHash<quint32, AuthorizedUser *> m_authorizedUsers; // userId to AuthorizedUser

    // Data
    QHash<quint32, LocalUser*> m_users; // userId to User
    QHash<quint64, Session*> m_sessions; // Session id to Session

    // Maps for faster lookup
    QHash<QString, quint32> m_phoneToUserId;
    QHash<QString, quint32> m_usernameToUserId;

    friend class ServerImportApi;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVER_HPP
