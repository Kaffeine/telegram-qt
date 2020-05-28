#ifndef TELEGRAM_QT_SERVER_AUTHORIZATION_PROVIDER_HPP
#define TELEGRAM_QT_SERVER_AUTHORIZATION_PROVIDER_HPP

#include <QByteArray>
#include <QString>

namespace Telegram {

namespace Server {

class Session;

namespace Authorization {

enum class CodeStatus {
    PhoneInvalid,
    HashEmpty,
    HashInvalid,
    CodeEmpty,
    CodeExpired,
    CodeInvalid,
    CodeValid,
};

struct Code
{
    enum class Type {
        Default,
        App,
        Sms,
        Call,
        FlashCall,
#ifdef MTPROTO_FORK
        NotNeeded,
        Denied,
#endif
    };

    QByteArray hash;
    QString code;
    Type type = Type::Default;

    bool isValid() const
    {
        return !hash.isEmpty() && !code.isEmpty();
    }
};

struct SentCodeInfo
{
    QByteArray hash;
    Code::Type type = Code::Type::Default;
    quint32 length = 0;
    QString pattern; // For flash call
};

class Provider
{
public:
    virtual ~Provider() = 0;
    virtual SentCodeInfo sendCode(Session *session, const QString &identifier) = 0;
    virtual CodeStatus getCodeStatus(const QString &identifier, const QByteArray &hash, const QString &code) = 0;
};

inline Provider::~Provider() { }

} // Authorization

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_AUTHORIZATION_PROVIDER_HPP
