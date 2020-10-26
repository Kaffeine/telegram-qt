/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#ifndef TELEGRAM_SERVER_MESSAGE_DATA_HPP
#define TELEGRAM_SERVER_MESSAGE_DATA_HPP

#include "TelegramNamespace.hpp"
#include "ServerNamespace.hpp"

#include <QHash>
#include <QVariant>

namespace Telegram {

namespace Server {

struct DocumentAttribute
{
    enum Type {
        Invalid,
        FileName,
    };

    static DocumentAttribute fromFileName(const QString &fileName);
    bool operator==(const DocumentAttribute &another) const;
    bool operator!=(const DocumentAttribute &another) const;

    Type type = Invalid;
    QVariant value;
};

class MediaData
{
public:
    enum Type {
        Invalid,
        Contact,
        Document,
        Photo,
    };

    bool isValid() const { return type != Invalid; }

    bool operator==(const MediaData &anotherMediaData) const;

    QString caption;
    ImageDescriptor image;

    // Document
    FileDescriptor file;
    QVector<DocumentAttribute> attributes;
    QString mimeType;

    UserContact contact;

    Type type = Invalid;
};

class MessageContent
{
public:
    MessageContent() = default;
    MessageContent(const QString &text);
    MessageContent(const MediaData &media);

    const MediaData &media() const { return m_media; }
    QString text() const { return m_text; }

    bool operator==(const MessageContent &anotherContent) const;

protected:
    MediaData m_media;
    QString m_text;
};

class ServiceMessageAction
{
public:
    enum class Type {
        Empty,
        ChatCreate,
    };

    Type type = Type::Empty;
    QString title;
    QVector<quint32> users;

    PeerList getPeers() const;
};

class MessageData
{
public:
    MessageData() = default;
    MessageData(quint32 from, Peer to, const MessageContent &content);
    MessageData(quint32 from, Peer to, const ServiceMessageAction &action);

    quint64 globalId() const { return m_globalId; }
    void setGlobalId(quint64 id);

    Peer toPeer() const { return m_to; }
    quint32 fromId() const { return m_fromId; }

    quint32 date() const;
    void setDate(quint32 date);

    quint32 editDate() const;
    void setEditDate(quint32 date);

    const ServiceMessageAction &action() const { return m_action; }
    const MessageContent &content() const { return m_content; }
    void setContent(const MessageContent &newContent);

    bool isMessageToSelf() const;
    bool isServiceMessage() const;

    void addReference(const Peer &peer, quint32 messageId);
    quint32 getReference(const Peer &peer) const { return m_references.value(peer); }

    Peer getDialogPeer(quint32 applicantUserId) const;

protected:
    MessageContent m_content;
    ServiceMessageAction m_action;
    QHash<Peer, quint32> m_references;
    Peer m_to;
    quint64 m_globalId = 0;
    quint32 m_date = 0;
    quint32 m_fromId = 0;
    quint32 m_editDate = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_MESSAGE_DATA_HPP
