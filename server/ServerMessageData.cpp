#include "ServerMessageData.hpp"

namespace Telegram {

namespace Server {

DocumentAttribute DocumentAttribute::fromFileName(const QString &fileName)
{
    DocumentAttribute attribute;
    attribute.type = FileName;
    attribute.value = fileName;
    return attribute;
}

bool DocumentAttribute::operator==(const DocumentAttribute &another) const
{
    return (type == another.type) && (value == another.value);
}

bool DocumentAttribute::operator!=(const DocumentAttribute &another) const
{
    return !(*this == another);
}

MessageData::MessageData(quint32 from, Peer to, const MessageContent &content)
    : m_content(content)
    , m_to(to)
    , m_fromId(from)
{
}

MessageData::MessageData(quint32 from, Peer to, const ServiceMessageAction &action)
    : m_action(action)
    , m_to(to)
    , m_fromId(from)
{
}

void MessageData::setGlobalId(quint64 id)
{
    m_globalId = id;
}

quint32 MessageData::date() const
{
    return m_date;
}

quint32 MessageData::editDate() const
{
    return m_editDate;
}

void MessageData::setContent(const MessageContent &newContent)
{
    m_content = newContent;
}

void MessageData::setDate(quint32 date)
{
    m_date = date;
}

void MessageData::setEditDate(quint32 date)
{
    m_editDate = date;
}

bool MessageData::isMessageToSelf() const
{
    return (m_to.type() == Peer::User) && (m_to.id() == m_fromId);
}

bool MessageData::isServiceMessage() const
{
    return m_action.type != ServiceMessageAction::Type::Empty;
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

MessageContent::MessageContent(const QString &text)
    : m_text(text)
{
}

MessageContent::MessageContent(const MediaData &media)
    : m_media(media)
{
}

bool MessageContent::operator==(const MessageContent &anotherContent) const
{
    return m_text == anotherContent.m_text && m_media == anotherContent.m_media;
}

bool MediaData::operator==(const MediaData &anotherMediaData) const
{
    if (type != anotherMediaData.type) {
        return false;
    }
    switch (type) {
    case Invalid:
        return true;
    case Contact:
        return contact == anotherMediaData.contact;
    case Document:
        if (caption != anotherMediaData.caption) {
            return false;
        }
        if (file != anotherMediaData.file) {
            return false;
        }
        if (attributes != anotherMediaData.attributes) {
            return false;
        }
        if (mimeType != anotherMediaData.mimeType) {
            return false;
        }
        return true;
    case Photo:
        if (caption != anotherMediaData.caption) {
            return false;
        }
        if (image != anotherMediaData.image) {
            return false;
        }
        return true;
    }

    Q_UNREACHABLE();
    return false;
}

PeerList ServiceMessageAction::getPeers() const
{
    return { };
}

} // Server namespace

} // Telegram namespace
