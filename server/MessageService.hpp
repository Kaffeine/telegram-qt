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

#ifndef TELEGRAM_QT_SERVER_MESSAGE_SERVICE_HPP
#define TELEGRAM_QT_SERVER_MESSAGE_SERVICE_HPP

#include "ServerNamespace.hpp"
#include "ServerMessageData.hpp"

#include <QHash>
#include <QObject>
#include <QSet>

namespace Telegram {

namespace Server {

class MessageService : public QObject
{
    Q_OBJECT
public:
    explicit MessageService(QObject *parent = nullptr);
    MessageData *addMessage(quint32 fromId, Peer toPeer, const QString &text);
    MessageData *addMessageMedia(quint32 fromId, Peer toPeer, const MediaData &media);
    const MessageData *getMessage(quint64 globalId);

protected:
    quint64 getMessageUniqueTs();

    QHash<quint64, MessageData> m_messages;
    quint64 m_lastGlobalId = 0;
    quint64 m_lastTimestamp = 0;
};

} // Server namespaceMediaService

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_MESSAGE_SERVICE_HPP
