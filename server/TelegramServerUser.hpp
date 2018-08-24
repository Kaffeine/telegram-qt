#ifndef TELEGRAMSERVERUSER_HPP
#define TELEGRAMSERVERUSER_HPP

#include <QObject>
#include <QVector>

#include "../TelegramQt/CAppInformation.hpp"

namespace Telegram {

namespace Server {

class User;

class Session
{
public:
    Session()
    {
    }

    Session(const Session &otherSession) :
        authId(otherSession.authId),
        appInfo(nullptr),
        timestamp(otherSession.timestamp)
    {
        if (otherSession.appInfo) {
            appInfo = new CAppInformation(otherSession.appInfo);
        }
    }

    User *userOrWantedUser() const { return m_user ? m_user : m_wanterUser; }
    User *user() const { return m_user; }
    void setUser(User *user) { m_user = user; }

    User *wanterUser() const { return m_wanterUser; }
    void setWantedUser(User *user) { m_wanterUser = user; }

    quint64 authId = 0;
    quint64 sessionId = 0;
    QByteArray authKey;
    CAppInformation *appInfo = nullptr;
    QString ip;
    quint64 timestamp = 0;

protected:
    User *m_wanterUser = nullptr;
    User *m_user = nullptr;
};

class RemoteUser
{
public:
    virtual quint32 id() const = 0;
    virtual QString phoneNumber() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual bool isOnline() const = 0;
    virtual quint32 dcId() const = 0;
};

class User : public QObject, public RemoteUser
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

    quint32 id() const { return m_id; }
    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName);

    bool isOnline() const;

    quint32 dcId() const { return m_dcId; }
    void setDcId(quint32 id);

    Session *getSession(quint64 authId) const;
    QVector<Session*> sessions() const { return m_sessions; }
    void addSession(Session *session);

    bool hasPassword() const { return !m_passwordSalt.isEmpty() && !m_passwordHash.isEmpty(); }
    QByteArray passwordSalt() const { return m_passwordSalt; }
    QByteArray passwordHash() const { return m_passwordHash; }

    void setPlainPassword(const QString &password);
    void setPassword(const QByteArray &salt, const QByteArray &hash);

    QString passwordHint() const { return QString(); }

signals:
    void sessionAdded(Session *newSession);
    void sessionDestroyed(Session *destroyedSession);

protected:
    quint32 m_id = 0;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_userName;
    QByteArray m_passwordSalt;
    QByteArray m_passwordHash;
    QVector<Session*> m_sessions;
    quint32 m_dcId = 0;
};

} // Server

} // Telegram

Q_DECLARE_TYPEINFO(Telegram::Server::Session, Q_MOVABLE_TYPE);

#endif // TELEGRAMSERVERUSER_HPP
