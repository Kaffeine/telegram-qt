#ifndef TELEGRAMSERVERUSER_HPP
#define TELEGRAMSERVERUSER_HPP

#include <QObject>
#include <QVector>

#include "ServerNamespace.hpp"
#include "TLTypes.hpp"

namespace Telegram {

namespace Server {

class Session;
class LocalUser;

class MessageRecipient
{
public:
    virtual ~MessageRecipient() = default;
    virtual quint32 addMessage(const TLMessage &message, Session *excludeSession = nullptr) = 0;

    virtual Peer toPeer() const = 0;
    TLPeer toTLPeer() const;
};

class AbstractUser : public MessageRecipient
{
public:
    virtual quint32 id() const = 0;
    virtual QString phoneNumber() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual bool isOnline() const = 0;
    virtual quint32 dcId() const = 0;
    virtual QVector<quint32> contactList() const = 0;

    Peer toPeer() const override { return Peer::fromUserId(id()); }
    UserContact toContact() const;
};

class LocalUser : public AbstractUser
{
public:
    quint32 id() const { return m_id; }
    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString userName() const { return m_userName; }

    QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName);

    bool isOnline() const;

    quint32 dcId() const { return m_dcId; }
    void setDcId(quint32 id);

    Session *getSession(quint64 authId) const;
    QVector<Session*> sessions() const { return m_sessions; }
    QVector<Session*> activeSessions() const;
    bool hasActiveSession() const;
    void addSession(Session *session);

    bool hasPassword() const { return !m_passwordSalt.isEmpty() && !m_passwordHash.isEmpty(); }
    QByteArray passwordSalt() const { return m_passwordSalt; }
    QByteArray passwordHash() const { return m_passwordHash; }

    void setPlainPassword(const QString &password);
    void setPassword(const QByteArray &salt, const QByteArray &hash);

    QString passwordHint() const { return QString(); }

    quint32 addMessage(const TLMessage &message, Session *excludeSession = nullptr) override;
    const TLMessage *getMessage(quint32 messageId) const;

    TLVector<TLMessage> getHistory(const Telegram::Peer &peer, quint32 offsetId, quint32 offsetDate, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId, quint32 hash) const;

    quint32 pts() const { return m_pts; }
    quint32 addPts();

    void importContact(const UserContact &contact);
    QVector<quint32> contactList() const override { return m_contactList; }
    const QVector<UserDialog *> dialogs() const { return m_dialogs; }

    QVector<UserContact> importedContacts() const { return m_importedContacts; }

protected:
    UserDialog *ensureDialog(const Telegram::Peer &peer);

    quint32 m_id = 0;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_userName;
    QByteArray m_passwordSalt;
    QByteArray m_passwordHash;
    QVector<Session*> m_sessions;
    quint32 m_dcId = 0;

    quint32 m_pts = 0;
    QVector<TLMessage> m_messages;
    QVector<UserDialog *> m_dialogs;
    QVector<quint32> m_contactList; // Contains only registered users from the added contacts
    QVector<UserContact> m_importedContacts; // Contains phone + name of all added contacts (including not registered yet)
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAMSERVERUSER_HPP
