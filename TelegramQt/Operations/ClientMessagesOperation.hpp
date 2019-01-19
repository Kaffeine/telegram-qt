#ifndef TELEGRAMQT_CLIENT_MESSAGES_OPERATION
#define TELEGRAMQT_CLIENT_MESSAGES_OPERATION

#include "../PendingOperation.hpp"
#include "../TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class MessagesOperationPrivate;
class MessagesOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit MessagesOperation(QObject *parent = nullptr);

    Peer peer() const;
    QVector<quint32> messages() const;

protected:
    Q_DECLARE_PRIVATE_D(d, MessagesOperation)

};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_MESSAGES_OPERATION
