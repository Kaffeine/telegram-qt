#include "ClientMessagesOperation.hpp"
#include "ClientMessagesOperation_p.hpp"

namespace Telegram {

namespace Client {

MessagesOperationPrivate *MessagesOperationPrivate::get(MessagesOperation *parent)
{
    return static_cast<MessagesOperationPrivate*>(parent->d);
}

MessagesOperation::MessagesOperation(QObject *parent) :
    PendingOperation(parent)
{
    d = new MessagesOperationPrivate;
}

Peer MessagesOperation::peer() const
{
    Q_D(const MessagesOperation);
    return d->m_peer;
}

QVector<quint32> MessagesOperation::messages() const
{
    Q_D(const MessagesOperation);
    return d->m_messages;
}

} // Client

} // Telegram namespace
