#ifndef TELEGRAM_LOCAL_SERVER_API_HPP
#define TELEGRAM_LOCAL_SERVER_API_HPP

#include "ServerApi.hpp"

#include "DcConfiguration.hpp"
#include "MTProto/TLValues.hpp"

struct TLInputPeer;
struct TLInputUser;
struct TLUpdate;

namespace Telegram {

class PendingOperation;
class RpcError;

namespace Server {

class AuthService;
class AuthorizedUser;
class LocalUser;
class RemoteClientConnection;
class AbstractUser;
class MessageData;
struct UserContact;

class LocalServerApi : public AbstractServerApi
{
public:
    virtual AuthService *authService() const = 0;

    virtual DcConfiguration serverConfiguration() const = 0;
    virtual LocalUser *addUser(const QString &identifier) = 0;
    virtual LocalUser *getUser(const QString &identifier) const = 0;
    virtual LocalUser *getUser(quint32 userId) const = 0;
    virtual Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const = 0;

    using AbstractServerApi::getRecipient;
    virtual MessageRecipient *getRecipient(const TLInputPeer &peer, const LocalUser *applicant) const = 0;

    using AbstractServerApi::getAbstractUser;
    virtual AbstractUser *getAbstractUser(quint32 userId, quint64 accessHash, const LocalUser *applicant) const = 0;
    virtual AbstractUser *getAbstractUser(const TLInputUser &inputUser, const LocalUser *applicant) const = 0;
    virtual Peer getPeerByUserName(const QString &userName) const = 0;

    virtual bool bindClientConnectionSession(RemoteClientConnection *connection, quint64 sessionId) = 0;
    virtual Session *getSessionById(quint64 authId) const = 0;
    virtual void bindUserSession(AuthorizedUser *user, Session *session) = 0;
    virtual bool usernameIsValid(const QString &username) const = 0;
    virtual bool setUserName(LocalUser *user, const QString &newUsername, RpcError *error = nullptr) = 0;
    virtual bool setUserOnline(LocalUser *user, bool online, Session *fromSession = nullptr) = 0;

    virtual PendingOperation *searchContacts(const QString &query, quint32 limit, QVector<Peer> *output) = 0;
    virtual PendingOperation *exportAuthorization(quint32 dcId, quint32 userId, QByteArray *outputAuthBytes) = 0;
    virtual QByteArray generateExportedAuthorization(quint32 userId) = 0;
    virtual AuthorizedUser *getAuthorizedUser(quint32 userId, const QByteArray &authBytes) = 0;

    virtual void reportMessageRead(const MessageData *messageData) = 0;

    virtual QVector<quint32> getPeerWatchers(const Peer &peer) const = 0;
    virtual QVector<UpdateNotification> processMessage(MessageData *messageData) = 0;
    virtual QVector<UpdateNotification> processMessageEdit(MessageData *messageData) = 0;
    virtual QVector<UpdateNotification> createUpdates(UpdateNotification::Type updateType,
                                                      LocalUser *applicant,
                                                      Session *excludeSession) const = 0;

    virtual AbstractUser *importUserContact(LocalUser *user, const UserContact &contact) = 0;
    virtual bool bakeUpdate(TLUpdate *update, const UpdateNotification &notification, QSet<Peer> *interestingPeers) const = 0;
    virtual void queueUpdates(const QVector<UpdateNotification> &updates) = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_LOCAL_SERVER_API_HPP
