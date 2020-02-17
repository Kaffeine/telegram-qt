#include "Session.hpp"

#include "ApiUtils.hpp"
#include "RandomGenerator.hpp"

#include <QDateTime>
#include <QLoggingCategory>

namespace Telegram {

namespace Server {

constexpr quint32 c_sessionRotation = 1 * 60 * 60;
constexpr quint32 c_sessionOverlapping = 300;
constexpr quint32 c_maxServerSalts = 64;

Session::Session(quint64 sessionId) :
    m_sessionId(sessionId)
{
}

quint64 Session::getOldSalt() const
{
    if (m_oldSalt.validUntil < Utils::getCurrentTime()) {
        return 0;
    }
    return m_oldSalt.salt;
}

quint64 Session::getServerSalt() const
{
    Q_ASSERT_X(!m_salts.isEmpty(), "ServerSession", "server salt requested, but initial salt is not set");
    // https://core.telegram.org/api/optimisation#server-salt
    // "At present, a single salt’s lifespan is 1 hour"
    //
    // https://core.telegram.org/mtproto/description#server-salt
    // "<server salt is> a number periodically (say, every 24 hours) changed (separately for each session)"
    //
    // https://core.telegram.org/mtproto/service_messages#request-for-several-future-salts
    // "a server salt is attached to the authorization key rather than being session-specific"

    if (m_salts.at(1).validSince < Utils::getCurrentTime()) {
        m_oldSalt = m_salts.takeFirst();
        if (m_salts.count() < 2) {
            addSalt();
        }
    }
    return m_salts.constFirst().salt;
}

bool Session::checkSalt(quint64 salt) const
{
    return salt && ((getServerSalt() == salt) || (getOldSalt() == salt));
}

bool Session::generateInitialServerSalt()
{
    if (!m_salts.isEmpty()) {
        qCritical() << Q_FUNC_INFO << "a salt is already set";
        return false;
    }
    ServerSalt s = generateSalt(Utils::getCurrentTime());
    m_salts.append(s);
    addSalt();
    return true;
}

void Session::setInitialServerSalt(quint64 salt)
{
    if (!m_salts.isEmpty()) {
        qCritical() << Q_FUNC_INFO << "a salt is already set";
        return;
    }
    ServerSalt s;
    s.salt = salt;
    s.validSince = Utils::getCurrentTime();
    s.validUntil = s.validSince + c_sessionRotation;
    m_salts.append(s);
    addSalt();
}

QVector<ServerSalt> Session::getSalts(quint32 numberLimit) const
{
    const int limit = static_cast<int>(qMin<quint32>(numberLimit, c_maxServerSalts));
    m_salts.reserve(limit);
    while (m_salts.count() < limit) {
        addSalt();
    }
    return m_salts.mid(0, limit);
}

ServerSalt Session::generateSalt(quint32 validSince)
{
    ServerSalt s;
    s.validSince = validSince;
    s.validUntil = s.validSince + c_sessionRotation;
    RandomGenerator::instance()->generate(&s.salt);
    return s;
}

void Session::addSalt() const
{
    // This method is a part of private lazy salts generation mechanism.
    // Externally we're 'const'.
    m_salts.append(generateSalt(m_salts.constLast().validUntil - c_sessionOverlapping));
}

} // Server namespace

} // Telegram namespace
