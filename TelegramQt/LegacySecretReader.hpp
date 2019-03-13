#ifndef TELEGRAM_LEGACY_SECRET_READER
#define TELEGRAM_LEGACY_SECRET_READER

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

// Internal class
class LegacySecretReader
{
public:
    QString accountIdentifier;
    QString phoneNumber;
    QByteArray authKey;
    quint64 authId = 0;
    qint32 deltaTime = 0;
    DcOption dcInfo;

    bool isValid;

    bool loadFromData(const QByteArray &data);

private:
    bool setSecretInfo(const QByteArray &secret);

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_LEGACY_SECRET_READER
