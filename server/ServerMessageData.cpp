#include "ServerMessageData.hpp"

namespace Telegram {

namespace Server {

MessageData::MessageData(quint32 from, Peer to) :
    m_to(to),
    m_fromId(from)
{
}

MessageData::MessageData(quint32 from, Peer to, const QString &text) :
    MessageData(from, to)
{
    m_text = text;
}

MessageData::MessageData(quint32 from, Peer to, const MediaData &media) :
    MessageData(from, to)
{
    m_media = media;
}

void MessageData::setGlobalId(quint64 id)
{
    m_globalId = id;
}

quint32 MessageData::date() const
{
    quint64 secs = m_date >> 32;
    return static_cast<quint32>(secs);
}

void MessageData::setDate32(quint32 date)
{
    m_date = date;
    m_date = m_date << 32;
}

void MessageData::setDate64(quint64 date)
{
    m_date = date;
}

bool MessageData::isMessageToSelf() const
{
    return (m_to.type() == Peer::User) && (m_to.id() == m_fromId);
}

void MessageData::addReference(const Peer &peer, quint32 messageId)
{
    m_references.insert(peer, messageId);
}

Peer MessageData::getDialogPeer(quint32 applicantUserId) const
{
    if (m_to.type() == Peer::User) {
        if (m_to.id() == applicantUserId) {
            return Peer::fromUserId(m_fromId);
        }
    }
    return m_to;
}

} // Server namespace

} // Telegram namespace
