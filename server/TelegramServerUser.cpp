#include "TelegramServerUser.hpp"

#include "Session.hpp"
#include "Utils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

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
