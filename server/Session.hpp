#ifndef TELEGRAM_QT_SERVER_USER_SESSION_HPP
#define TELEGRAM_QT_SERVER_USER_SESSION_HPP

#include <QVector>

#include "ServerNamespace.hpp"

namespace Telegram {

namespace Server {

class RemoteClientConnection;

class Session
{
public:
    explicit Session(quint64 sessionId);

    bool isActive() const { return m_connection; }
    RemoteClientConnection *getConnection() const { return m_connection; }
    void setConnection(RemoteClientConnection *connection) { m_connection = connection; }

    quint64 id() const { return m_sessionId; }

    quint32 userId() const { return m_userId; }
    void setUserId(quint32 userId) { m_userId = userId; }

    quint32 wantedUserId() const { return m_wanterUserId; }
    void setWantedUserId(quint32 userId) { m_wanterUserId = userId; }

    quint32 userOrWantedUserId() const { return m_userId ? m_userId : m_wanterUserId; }

    quint32 layer() const { return m_layer; }
    void setLayer(quint32 layer) { m_layer = layer; }

    quint64 getOldSalt() const;
    quint64 getServerSalt() const;
    bool checkSalt(quint64 salt) const;
    bool generateInitialServerSalt();
    void setInitialServerSalt(quint64 salt);
    QVector<ServerSalt> getSalts(quint32 numberLimit) const;

    static ServerSalt generateSalt(quint32 validSince);

    quint32 appId = 0;
    quint32 lastSequenceNumber = 0;
    quint64 lastMessageNumber = 0;
    QString deviceInfo;
    QString osInfo;
    QString appVersion;
    QString systemLanguage;
    QString languagePack;
    QString languageCode;
    QString ip;
    quint32 timestamp = 0;

protected:
    void addSalt() const;

    quint64 m_sessionId = 0;
    RemoteClientConnection *m_connection = nullptr;
    quint32 m_wanterUserId = 0;
    quint32 m_userId = 0;
    mutable QVector<ServerSalt> m_salts;
    mutable ServerSalt m_oldSalt;
    quint32 m_layer = 0;
};

} // Server namespace

} // Telegram namespace

Q_DECLARE_TYPEINFO(Telegram::Server::Session, Q_MOVABLE_TYPE);

#endif // TELEGRAM_QT_SERVER_USER_SESSION_HPP
