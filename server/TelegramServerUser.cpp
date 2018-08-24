#include "TelegramServerUser.hpp"

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

void User::addSession(Session *session)
{
    m_sessions.append(session);
    session->setUser(this);
    emit sessionAdded(m_sessions.last());
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

} // Server

} // Telegram
