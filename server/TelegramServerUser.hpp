#ifndef TELEGRAMSERVERUSER_HPP
#define TELEGRAMSERVERUSER_HPP

#include <QObject>
#include <QVector>
#include <QHash>

#include "ServerNamespace.hpp"
#include "MTProto/TLTypes.hpp"

namespace Telegram {

namespace Server {

class Session;
class LocalUser;
class MessageData;

class AbstractUser;

class PostBox
{
public:
    virtual ~PostBox() = default;

    Peer peer() const { return m_peer; }

    quint32 bumpPts() { return ++m_pts; }
    quint32 pts() const { return m_pts; }
    quint32 lastMessageId() const { return m_lastMessageId; }
    virtual QVector<quint32> users() const = 0;

    quint32 addMessage(quint64 globalId);
    quint64 getMessageGlobalId(quint32 messageId) const;

    QHash<quint32,quint64> getAllMessageKeys() const;

protected:
    Peer m_peer;
    quint32 m_pts = 0;
    quint32 m_lastMessageId = 0;
    QHash<quint32,quint64> m_messages; // messageId to MessageData object id
};

class UserPostBox : public PostBox
{
public:
    UserPostBox() = default;

    QVector<quint32> users() const override
    {
        return { m_peer.id() };
    }

    void setUserId(UserId userId)
    {
        m_peer = userId;
    }

    quint32 unreadCount() const
    {
        return m_unreadCount;
    }

    void setUnreadCount(quint32 count);

protected:
    quint32 m_unreadCount = 0;
};

class MessageRecipient
{
public:
    virtual ~MessageRecipient() = default;

    virtual Peer toPeer() const = 0;
    TLPeer toTLPeer() const;
};

class AbstractUser : public MessageRecipient
{
public:
    virtual UserId userId() const = 0;
    virtual quint32 id() const = 0;
    virtual QString phoneNumber() const = 0;
    virtual QString userName() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual quint32 onlineTimestamp() const = 0;
    virtual bool isOnline() const = 0;
    virtual quint32 dcId() const = 0;
    virtual UserPostBox *getPostBox() = 0;
    virtual const UserPostBox *getPostBox() const = 0;
    virtual QVector<ImageDescriptor> getImages() const = 0;
    virtual ImageDescriptor getCurrentImage() const = 0;
    virtual QVector<UserId> contactList() const = 0;

    Peer toPeer() const override { return Peer::fromUserId(id()); }
    UserContact toContact() const;
};

class AuthorizedUser : public AbstractUser
{
public:
    UserId userId() const override { return m_id; }
    quint32 id() const override { return m_id.id; }

    quint32 dcId() const override { return m_dcId; }
    void setDcId(quint32 id);

    Session *getSession(quint64 sessionId) const;

    QVector<quint64> authorizations() const { return m_authKeyIds; }
    void addAuthKey(quint64 authId);

    QVector<Session*> sessions() const { return m_sessions; }
    QVector<Session*> activeSessions() const;
    bool hasActiveSession() const;
    void addSession(Session *session);

protected:
    QVector<quint64> m_authKeyIds;
    QVector<Session*> m_sessions; // Sessions are owned by the Server class

    UserId m_id = 0;
    quint32 m_dcId = 0;
};

class LocalUser : public AuthorizedUser
{
public:
    explicit LocalUser(UserId userId, const QString &phoneNumber);
    LocalUser() = default;
    ~LocalUser() override;

    QString phoneNumber() const override { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString userName() const override { return m_userName; }
    void setUserName(const QString &userName);

    QString firstName() const override { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const override { return m_lastName; }
    void setLastName(const QString &lastName);

    QString about() const { return m_about; }
    void setAbout(const QString &about);

    quint32 onlineTimestamp() const override { return m_onlineTimestamp; }
    void setOnlineTimestamp(quint32 onlineTimestampSec);

    bool isOnline() const override;

    QVector<ImageDescriptor> getImages() const override { return m_photos; }
    ImageDescriptor getCurrentImage() const override;
    void updateImage(const ImageDescriptor &image);

    bool hasPassword() const { return !m_passwordSalt.isEmpty() && !m_passwordHash.isEmpty(); }
    QByteArray passwordSalt() const { return m_passwordSalt; }
    QByteArray passwordHash() const { return m_passwordHash; }

    void setPlainPassword(const QString &password);
    void setPassword(const QByteArray &salt, const QByteArray &hash);

    QString passwordHint() const { return QString(); }

    UserPostBox *getPostBox() override { return &m_box; }
    const UserPostBox *getPostBox() const override { return &m_box; }

    void importContact(const UserContact &contact);
    QVector<UserId> contactList() const override { return m_contactList; }
    const QVector<UserDialog *> dialogs() const { return m_dialogs; }

    QVector<UserContact> importedContacts() const { return m_importedContacts; }

    void bumpDialogUnreadCount(const Telegram::Peer &peer);
    void addNewMessage(const Telegram::Peer &peer, quint32 messageId, quint64 messageDate);
    UserDialog *getDialog(const Telegram::Peer &peer);
    const UserDialog *getDialog(const Telegram::Peer &peer) const;
    void syncDialogsOrder();

protected:
    UserDialog *ensureDialog(const Telegram::Peer &peer);
    void setUserId(UserId userId);

    UserPostBox m_box;

    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_userName;
    QString m_about;
    QByteArray m_passwordSalt;
    QByteArray m_passwordHash;
    QVector<ImageDescriptor> m_photos;

    QVector<UserDialog *> m_dialogs;
    QVector<UserId> m_contactList; // Contains only registered users from the added contacts
    QVector<UserContact> m_importedContacts; // Contains phone + name of all added contacts (including not registered yet)

    quint32 m_onlineTimestamp = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVERUSER_HPP
