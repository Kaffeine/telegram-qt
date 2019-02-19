#ifndef TELEGRAM_SERVER_API_HPP
#define TELEGRAM_SERVER_API_HPP

#include <QObject>
#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

#include "DcConfiguration.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QTimer)

#include <QHash>
#include <QMap>
#include <QSet>

namespace Telegram {

namespace Server {

namespace Authorization {

class Provider;

} // Authorization namespace

class Session;
class LocalUser;
class RemoteClientConnection;
class AbstractUser;

struct PhoneStatus
{
    bool online = false;
    quint32 dcId = 0;
    bool exists() const { return dcId; }
};

struct PasswordInfo
{
    bool hasPassword() const { return !currentSalt.isEmpty(); }
    QByteArray newSalt;
    QString emailUnconfirmedPattern;
    QByteArray currentSalt;
    QString hint;
    bool hasRecovery = false;
};

class ServerApi
{
public:
    virtual ~ServerApi() = default;

    virtual DcConfiguration serverConfiguration() const = 0;
    virtual quint32 dcId() const = 0;
    virtual PhoneStatus getPhoneStatus(const QString &identifier) const = 0;
    virtual PasswordInfo getPassword(const QString &identifier) = 0;
    virtual bool checkPassword(const QString &identifier, const QByteArray &hash) = 0;
    virtual Authorization::Provider *getAuthorizationProvider() = 0;
    virtual bool identifierIsValid(const QString &identifier) const = 0; // Argument is 'phoneNumber'
    virtual QString normalizeIdentifier(const QString &identifier) const = 0;

    virtual Telegram::Peer getPeer(const TLInputPeer &peer, const LocalUser *applicant) const = 0;

    virtual AbstractUser *getAbstractUser(quint32 userId) const = 0;
    virtual AbstractUser *getAbstractUser(const QString &identifier) const = 0;
    virtual LocalUser *getUser(const QString &identifier) const = 0;
    virtual LocalUser *getUser(quint32 userId) const = 0;
    virtual AbstractUser *getUser(const TLInputUser &inputUser, LocalUser *self) const = 0;
    virtual AbstractUser *tryAccessUser(quint32 userId, quint64 accessHash, LocalUser *applicant) const = 0;
    virtual Session *createSession(quint64 authId, const QByteArray &authKey, const QString &address) = 0;
    virtual Session *getSessionByAuthId(quint64 authId) const = 0;
    virtual void bindUserSession(LocalUser *user, Session *session) = 0;
    virtual LocalUser *addUser(const QString &identifier) = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
