#ifndef TELEGRAMSERVERUSER_HPP
#define TELEGRAMSERVERUSER_HPP

#include <QObject>
#include <QVector>
#include <QHash>

#include "ServerNamespace.hpp"
#include "TLTypes.hpp"

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

    quint32 addMessage(MessageData *message);
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
        return { m_peer.id };
    }

    void setUserId(quint32 userId)
    {
        m_peer = Peer::fromUserId(userId);
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
    virtual QVector<PostBox *> postBoxes() = 0;

    virtual Peer toPeer() const = 0;
    TLPeer toTLPeer() const;
};

class AbstractUser : public MessageRecipient
{
public:
    virtual quint32 id() const = 0;
    virtual QString phoneNumber() const = 0;
    virtual QString userName() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual bool isOnline() const = 0;
    virtual quint32 dcId() const = 0;
    virtual QVector<ImageDescriptor> getImages() const = 0;
    virtual ImageDescriptor getCurrentImage() const = 0;
    virtual QVector<quint32> contactList() const = 0;

    Peer toPeer() const override { return Peer::fromUserId(id()); }
    UserContact toContact() const;
};

class LocalUser : public AbstractUser
{
public:
    explicit LocalUser(quint32 userId, const QString &phoneNumber);
    LocalUser() = default;

    quint32 userId() const { return m_id; }
    quint32 id() const override { return m_id; }
    QString phoneNumber() const override { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString userName() const override { return m_userName; }
    void setUserName(const QString &userName);

    QString firstName() const override { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const override { return m_lastName; }
    void setLastName(const QString &lastName);

    bool isOnline() const override;

    quint32 dcId() const override { return m_dcId; }
    void setDcId(quint32 id);

    Session *getSession(quint64 sessionId) const;
    QVector<Session*> sessions() const { return m_sessions; }
    QVector<Session*> activeSessions() const;
    bool hasActiveSession() const;
    void addSession(Session *session);

    QVector<ImageDescriptor> getImages() const override { return m_photos; }
    ImageDescriptor getCurrentImage() const override;
    void updateImage(const ImageDescriptor &image);

    bool hasPassword() const { return !m_passwordSalt.isEmpty() && !m_passwordHash.isEmpty(); }
    QByteArray passwordSalt() const { return m_passwordSalt; }
    QByteArray passwordHash() const { return m_passwordHash; }

    void setPlainPassword(const QString &password);
    void setPassword(const QByteArray &salt, const QByteArray &hash);

    QString passwordHint() const { return QString(); }

    UserPostBox *getPostBox() { return &m_box; }
    const UserPostBox *getPostBox() const { return &m_box; }

    QVector<PostBox *> postBoxes() override { return { &m_box }; }

    void importContact(const UserContact &contact);
    QVector<quint32> contactList() const override { return m_contactList; }
    const QVector<UserDialog *> dialogs() const { return m_dialogs; }

    QVector<UserContact> importedContacts() const { return m_importedContacts; }

    void bumpDialogUnreadCount(const Telegram::Peer &peer);
    void addNewMessage(const Telegram::Peer &peer, quint32 messageId, quint64 messageDate);
    UserDialog *getDialog(const Telegram::Peer &peer);
    void syncDialogsOrder();

protected:
    UserDialog *ensureDialog(const Telegram::Peer &peer);
    void setUserId(quint32 userId);

    UserPostBox m_box;

    quint32 m_id = 0;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_userName;
    QByteArray m_passwordSalt;
    QByteArray m_passwordHash;
    QVector<Session*> m_sessions;
    QVector<ImageDescriptor> m_photos;

    quint32 m_dcId = 0;

    QVector<UserDialog *> m_dialogs;
    QVector<quint32> m_contactList; // Contains only registered users from the added contacts
    QVector<UserContact> m_importedContacts; // Contains phone + name of all added contacts (including not registered yet)
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVERUSER_HPP
