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

bool User::isOnline()
{
    return true;
}

Session User::getSession(quint64 authId) const
{
    for (const Session &s : m_sessions) {
        if (s.authId == authId) {
            return s;
        }
    }
    return Session();
}

void User::addSession(const Session &session)
{
    m_sessions.append(session);
}

void User::setPlainPassword(const QString &password)
{
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
