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

void MessageData::setGlobalId(quint64 id)
{
    m_globalId = id;
}

quint32 MessageData::date() const
{
    quint64 secs = m_date >> 32;
    return static_cast<quint32>(secs);
}

void MessageData::setContent(const MessageContent &newContent)
{
    m_content = newContent;
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

} // Server namespace

} // Telegram namespace
