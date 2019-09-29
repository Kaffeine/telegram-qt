#ifndef TELEGRAM_SERVER_API_HPP
#define TELEGRAM_SERVER_API_HPP

#include <QObject>

#include "DcConfiguration.hpp"
#include "MTProto/TLValues.hpp"
#include "TelegramNamespace.hpp"

struct TLInputPeer;
struct TLInputUser;

namespace Telegram {

class PendingOperation;
class RpcError;

namespace Server {

class AuthService;
class AuthorizedUser;
class IMediaService;
class Session;
class LocalUser;
class RemoteClientConnection;
class AbstractUser;
class MessageData;
class MessageRecipient;
class MessageService;
struct UserContact;

struct PhoneStatus
{
    bool online = false;
    quint32 dcId = 0;
    bool exists() const { return dcId; }
};

struct UpdateNotification
{
    Q_GADGET
public:
    enum class Type {
        Invalid,
        NewMessage,
        MessageAction,
        ReadInbox,
        ReadOutbox,
        UpdateName,
        UpdateUserStatus,
    };
    Q_ENUM(Type)

    Peer dialogPeer;
    MessageAction messageAction;
    quint32 userId = 0; // The Update recipient
    quint32 fromId = 0;
    quint32 messageId = 0;
    quint32 pts = 0;
    quint32 date = 0;
    Session *excludeSession = nullptr;
    Type type = Type::Invalid;
};

class AbstractServerApi
{
public:
    virtual ~AbstractServerApi() = default;

    virtual DcConfiguration serverConfiguration() const = 0;
    virtual quint32 dcId() const = 0;
    virtual PhoneStatus getPhoneStatus(const QString &identifier) const = 0;
    virtual bool identifierIsValid(const QString &identifier) const = 0; // Argument is 'phoneNumber'
    virtual QString normalizeIdentifier(const QString &identifier) const = 0;

    virtual AuthService *authService() const = 0;
    virtual IMediaService *mediaService() const = 0;
    virtual MessageService *messageService() const = 0;

    virtual Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const = 0;
    virtual MessageRecipient *getRecipient(const TLInputPeer &peer, const LocalUser *applicant) const = 0;
    virtual MessageRecipient *getRecipient(const Peer &peer) const = 0;

    virtual AbstractUser *getAbstractUser(quint32 userId) const = 0;
    virtual AbstractUser *getAbstractUser(const QString &identifier) const = 0;
    virtual AbstractUser *getAbstractUser(const TLInputUser &inputUser, const LocalUser *applicant) const = 0;
    virtual AbstractUser *getAbstractUser(quint32 userId, quint64 accessHash, const LocalUser *applicant) const = 0;
    virtual Peer getPeerByUserName(const QString &userName) const = 0;

    virtual void queueUpdates(const QVector<UpdateNotification> &updates) = 0;
    virtual void queueServerUpdates(const QVector<UpdateNotification> &updates) = 0;
};

class LocalServerApi : public AbstractServerApi
{
public:
    virtual LocalUser *addUser(const QString &identifier) = 0;
    virtual LocalUser *getUser(const QString &identifier) const = 0;
    virtual LocalUser *getUser(quint32 userId) const = 0;

    virtual bool bindClientConnectionSession(RemoteClientConnection *connection, quint64 sessionId) = 0;
    virtual Session *getSessionById(quint64 authId) const = 0;
    virtual void bindUserSession(AuthorizedUser *user, Session *session) = 0;
    virtual bool usernameIsValid(const QString &username) const = 0;
    virtual bool setUserName(LocalUser *user, const QString &newUsername, RpcError *error = nullptr) = 0;
    virtual bool setUserOnline(LocalUser *user, bool online, Session *fromSession = nullptr) = 0;

    virtual PendingOperation *exportAuthorization(quint32 dcId, quint32 userId, QByteArray *outputAuthBytes) = 0;
    virtual QByteArray generateExportedAuthorization(quint32 userId) = 0;
    virtual AuthorizedUser *getAuthorizedUser(quint32 userId, const QByteArray &authBytes) = 0;

    virtual void reportMessageRead(const MessageData *messageData) = 0;

    virtual QVector<quint32> getPeerWatchers(const Peer &peer) const = 0;
    virtual QVector<UpdateNotification> processMessage(MessageData *messageData) = 0;
    virtual QVector<UpdateNotification> createUpdates(UpdateNotification::Type updateType,
                                                      LocalUser *applicant,
                                                      Session *excludeSession) const = 0;

    virtual AbstractUser *importUserContact(LocalUser *user, const UserContact &contact) = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
