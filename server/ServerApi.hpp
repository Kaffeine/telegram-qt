#ifndef TELEGRAM_SERVER_API_HPP
#define TELEGRAM_SERVER_API_HPP

#include <QObject>
#include "../TelegramQt/TLTypes.hpp"
#include "../TelegramQt/TelegramNamespace.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QTimer)

#include <QHash>
#include <QMap>
#include <QSet>

namespace Telegram {

namespace Server {

class User;
class RemoteClientConnection;

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
    enum class AuthCodeStatus {
        PhoneInvalid,
        HashEmpty,
        HashInvalid,
        CodeEmpty,
        CodeExpired,
        CodeInvalid,
        CodeValid,
    };

    virtual quint32 dcId() const = 0;
    virtual PhoneStatus getPhoneStatus(const QString &identifier) = 0;
    virtual PasswordInfo getPassword(const QString &identifier) = 0;
    virtual bool checkPassword(const QString &identifier, const QString &hash) = 0;
    virtual QString sendAppCode(const QString &identifier) = 0;
    virtual AuthCodeStatus getAuthCodeStatus(const QString &identifier, const QString &hash, const QString &code) = 0;
    virtual bool identifierIsValid(const QString &identifier) = 0; // Argument is 'phoneNumber'

    virtual User *getUser(const QString &identifier) = 0;
    virtual User *getUser(quint64 authId) = 0;
    virtual User *addUser(const QString &identifier) = 0;
};

} // Server

} // Telegram

#endif // TELEGRAM_SERVER_API_HPP
