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
class User;
class RemoteClientConnection;
class RemoteUser;

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
    virtual bool identifierIsValid(const QString &identifier) = 0; // Argument is 'phoneNumber'

    virtual bool setupTLUser(TLUser *output, const RemoteUser *input, const User *forUser) const = 0;

    virtual User *getUser(const QString &identifier) const = 0;
    virtual User *getUser(quint32 userId) const = 0;
    virtual Session *createSession(quint64 authId, const QByteArray &authKey, const QString &address) = 0;
    virtual Session *getSessionByAuthId(quint64 authId) const = 0;
    virtual User *addUser(const QString &identifier) = 0;
};

} // Server

} // Telegram

#endif // TELEGRAM_SERVER_API_HPP
