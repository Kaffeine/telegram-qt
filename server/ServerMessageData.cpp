#include "ServerMessageData.hpp"

#include "ApiUtils.hpp"

namespace Telegram {

namespace Server {

MessageData::MessageData(quint32 from, Peer to, const QString &text) :
    m_text(text),
    m_to(to),
    m_fromId(from)
{
    m_date = Telegram::Utils::getCurrentTime();
}

void MessageData::setGlobalId(quint64 id)
{
    m_globalId = id;
}

void MessageData::addReference(const Peer &peer, quint32 messageId)
{
    m_references.insert(peer, messageId);
}

} // Server namespace

} // Telegram namespace
