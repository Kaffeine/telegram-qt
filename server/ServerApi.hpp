#ifndef TELEGRAM_SERVER_API_HPP
#define TELEGRAM_SERVER_API_HPP

#include <QObject>

#include "TelegramNamespace.hpp"
#include "GroupChat.hpp"

namespace Telegram {

namespace Server {

class IMediaService;
class Session;
class AbstractUser;
class GroupChat;
class MessageRecipient;
class MessageService;

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
        CreateChat,
        ChatParticipants,
        NewMessage,
        EditMessage,
        MessageAction,
        ReadInbox,
        ReadOutbox,
        UpdateName,
        UpdateUserStatus,
    };
    Q_ENUM(Type)

    Peer dialogPeer;
    MessageAction messageAction;
    UserId userId = 0; // The Update recipient
    UserId fromId = 0;
    quint32 messageId = 0;
    quint64 messageDataId = 0;
    quint32 dcId = 0;
    quint32 pts = 0;
    quint32 date = 0;
    Session *excludeSession = nullptr;
    bool joinWithNext = false;
    Type type = Type::Invalid;
};

class AbstractServerApi
{
public:
    virtual ~AbstractServerApi() = default;

    virtual quint32 dcId() const = 0;
    virtual PhoneStatus getPhoneStatus(const QString &identifier) const = 0;
    virtual bool identifierIsValid(const QString &identifier) const = 0; // Argument is 'phoneNumber'
    virtual QString normalizeIdentifier(const QString &identifier) const = 0;

    virtual IMediaService *mediaService() const = 0;
    virtual MessageService *messageService() const = 0;

    virtual AbstractUser *getAbstractUser(UserId userId) const = 0;
    virtual AbstractUser *getAbstractUser(const QString &identifier) const = 0;
    virtual GroupChat *getGroupChat(ChatId chatId) const = 0;

    virtual void queueServerUpdates(const QVector<UpdateNotification> &updates) = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
