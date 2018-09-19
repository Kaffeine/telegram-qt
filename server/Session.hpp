#ifndef TELEGRAM_QT_SERVER_USER_SESSION_HPP
#define TELEGRAM_QT_SERVER_USER_SESSION_HPP

#include <QVector>

namespace Telegram {

namespace Server {

class RemoteClientConnection;
class User;

class Session
{
public:
    bool isActive() const { return m_connection; }
    RemoteClientConnection *getConnection() const { return m_connection; }
    void setConnection(RemoteClientConnection *connection) { m_connection = connection; }

    User *userOrWantedUser() const { return m_user ? m_user : m_wanterUser; }
    User *user() const { return m_user; }
    void setUser(User *user) { m_user = user; }

    User *wanterUser() const { return m_wanterUser; }
    void setWantedUser(User *user) { m_wanterUser = user; }

    quint32 layer() const { return m_layer; }
    void setLayer(quint32 layer) { m_layer = layer; }

    quint32 appId = 0;
    quint32 lastSequenceNumber = 0;
    quint64 lastMessageNumber = 0;
    quint64 authId = 0;
    quint64 sessionId = 0;
    QByteArray authKey;
    QString deviceInfo;
    QString osInfo;
    QString appVersion;
    QString systemLanguage;
    QString languagePack;
    QString languageCode;
    QString ip;
    quint64 timestamp = 0;

protected:
    RemoteClientConnection *m_connection = nullptr;
    User *m_wanterUser = nullptr;
    User *m_user = nullptr;
    quint32 m_layer = 0;
};

} // Server

} // Telegram

Q_DECLARE_TYPEINFO(Telegram::Server::Session, Q_MOVABLE_TYPE);

#endif // TELEGRAM_QT_SERVER_USER_SESSION_HPP
