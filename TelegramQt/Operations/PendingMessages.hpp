#ifndef TELEGRAMQT_CLIENT_PENDING_MESSAGES_HPP
#define TELEGRAMQT_CLIENT_PENDING_MESSAGES_HPP

#include "../PendingOperation.hpp"
#include "../TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class PendingMessagesPrivate;
class TELEGRAMQT_EXPORT PendingMessages : public PendingOperation
{
    Q_OBJECT
public:
    explicit PendingMessages(QObject *parent = nullptr);

    Peer peer() const;
    QVector<quint32> messages() const;

protected:
    Q_DECLARE_PRIVATE_D(d, PendingMessages)

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_PENDING_MESSAGES_HPP
