#include "TelegramServerUser.hpp"

#include "ApiUtils.hpp"
#include "ServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "Session.hpp"
#include "Utils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

TLPeer MessageRecipient::toTLPeer() const
{
    const Peer p = toPeer();
    if (Q_UNLIKELY(!p.isValid())) {
        qCritical() << Q_FUNC_INFO << "Invalid peer" << this;
        return TLPeer();
    }
    TLPeer result;
    switch (p.type) {
    case Peer::User:
        result.tlType = TLValue::PeerUser;
        result.userId = p.id;
        break;
    case Peer::Chat:
        result.tlType = TLValue::PeerChat;
        result.chatId = p.id;
        break;
    case Peer::Channel:
        result.tlType = TLValue::PeerChannel;
        result.channelId = p.id;
        break;
    }
    return result;
}

User::User(QObject *parent) :
    QObject(parent)
{
}

void User::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
    m_id = qHash(m_phoneNumber);
}

void User::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

void User::setLastName(const QString &lastName)
{
    m_lastName = lastName;
}

bool User::isOnline() const
{
    return true;
}

void User::setDcId(quint32 id)
{
    m_dcId = id;
}

Session *User::getSession(quint64 authId) const
{
    for (Session *s : m_sessions) {
        if (s->authId == authId) {
            return s;
        }
    }
    return nullptr;
}

QVector<Session *> User::activeSessions() const
{
    QVector<Session *> result;
    for (Session *s : m_sessions) {
        if (s->isActive()) {
            result.append(s);
        }
    }
    return result;
}

bool User::hasActiveSession() const
{
    for (Session *s : m_sessions) {
        if (s->isActive()) {
            return true;
        }
    }
    return false;
}

void User::addSession(Session *session)
{
    m_sessions.append(session);
    session->setUser(this);
    emit sessionAdded(session);
}

void User::setPlainPassword(const QString &password)
{
    if (password.isEmpty()) {
        m_passwordSalt.clear();
        m_passwordHash.clear();
        return;
    }
    QByteArray pwdSalt(8, Qt::Uninitialized);
    Utils::randomBytes(&pwdSalt);
    const QByteArray pwdData = pwdSalt + password.toUtf8() + pwdSalt;
    const QByteArray pwdHash = Utils::sha256(pwdData);
    setPassword(pwdSalt, pwdHash);
}

void User::setPassword(const QByteArray &salt, const QByteArray &hash)
{
    qDebug() << Q_FUNC_INFO << "salt:" << salt.toHex();
    qDebug() << Q_FUNC_INFO << "hash:" << hash.toHex();

    m_passwordSalt = salt;
    m_passwordHash = hash;
}

quint32 User::addMessage(const TLMessage &message, Session *excludeSession)
{
    m_messages.append(message);
    m_messages.last().id = addPts();
    return m_messages.last().id;
}

quint32 User::addPts()
{
    return ++m_pts;
}

void User::importContact(const UserContact &contact)
{
    // Check for contact registration status and the contact id setup performed out of this function
    m_importedContacts.append(contact);

    if (contact.id) {
        m_contactList.append(contact.id);
    }
}

} // Server

} // Telegram
