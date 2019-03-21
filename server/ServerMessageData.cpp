#include "ServerMessageData.hpp"

namespace Telegram {

namespace Server {

MessageData::MessageData(quint32 from, Peer to, const QString &text) :
    m_text(text),
    m_to(to),
    m_fromId(from)
{
}

void MessageData::setGlobalId(quint64 id)
{
    m_globalId = id;
}

// Needed for save/load and for autotests
void MessageData::setDate(quint32 date)
{
    m_date = date;
}

bool MessageData::isMessageToSelf() const
{
    return (m_to.type == Peer::User) && (m_to.id == m_fromId);
}

void MessageData::addReference(const Peer &peer, quint32 messageId)
{
    m_references.insert(peer, messageId);
}

Peer MessageData::getDialogPeer(quint32 applicantUserId) const
{
    if (m_to.type == Peer::User) {
        if (m_to.id == applicantUserId) {
            return Peer::fromUserId(m_fromId);
        }
    }
    return m_to;
}

} // Server namespace

} // Telegram namespace
