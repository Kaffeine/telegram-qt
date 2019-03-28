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

    static DocumentAttribute fromFileName(const QString &fileName)
    {
        DocumentAttribute attribute;
        attribute.type = FileName;
        attribute.value = fileName;
        return attribute;
    }

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

    QString caption;
    ImageDescriptor image;

    // Document
    FileDescriptor file;
    QVector<DocumentAttribute> attributes;
    QString mimeType;

    UserContact contact;

    Type type = Invalid;
};

class MessageData
{
public:
    MessageData() = default;
    MessageData(quint32 from, Peer to, const QString &text);
    MessageData(quint32 from, Peer to, const MediaData &media);

    quint64 globalId() const { return m_globalId; }
    void setGlobalId(quint64 id);

    const MediaData &media() const { return m_media; }
    QString text() const { return m_text; }
    Peer toPeer() const { return m_to; }
    quint32 fromId() const { return m_fromId; }
    quint32 date() const;

    // Wanted for autotests
    void setDate32(quint32 date);

    quint64 date64() const { return m_date; }
    // Needed for save/load and for autotests
    void setDate64(quint64 date);

    bool isMessageToSelf() const;

    void addReference(const Peer &peer, quint32 messageId);
    quint32 getReference(const Peer &peer) const { return m_references.value(peer); }

    Peer getDialogPeer(quint32 applicantUserId) const;

protected:
    MessageData(quint32 from, Peer to);

    QHash<Peer, quint32> m_references;
    MediaData m_media;
    QString m_text;
    Peer m_to;
    quint64 m_globalId = 0;
    quint32 m_fromId = 0;
    quint64 m_date = 0;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_MESSAGE_DATA_HPP
