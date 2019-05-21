#include "PendingMessages.hpp"
#include "PendingMessages_p.hpp"

namespace Telegram {

namespace Client {

PendingMessagesPrivate *PendingMessagesPrivate::get(PendingMessages *parent)
{
    return static_cast<PendingMessagesPrivate*>(parent->d);
}

/*!
    \class Telegram::Client::PendingMessages
    \brief Provides IDs of the requested messages.
    \inmodule TelegramQt
    \ingroup Client
 */
PendingMessages::PendingMessages(QObject *parent) :
    PendingOperation(new PendingMessagesPrivate(this), parent)
{
}

Peer PendingMessages::peer() const
{
    Q_D(const PendingMessages);
    return d->m_peer;
}

QVector<quint32> PendingMessages::messages() const
{
    Q_D(const PendingMessages);
    return d->m_messages;
}

} // Client namespace

} // Telegram namespace
