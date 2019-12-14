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

#include "MessageService.hpp"

#include "ApiUtils.hpp"
#include "Debug_p.hpp"
#include "RandomGenerator.hpp"

#include <QDateTime>
#include <QLoggingCategory>

namespace Telegram {

namespace Server {

MessageService::MessageService(QObject *parent) :
    QObject(parent)
{
}

MessageData *MessageService::addMessage(quint32 fromId, Peer toPeer, const QString &text)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, text));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate64(getMessageUniqueTs());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

MessageData *MessageService::addMessageMedia(quint32 fromId, Peer toPeer, const MediaData &media)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, media));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate64(getMessageUniqueTs());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

const MessageData *MessageService::getMessage(quint64 globalId)
{
    if (!m_messages.contains(globalId)) {
        return nullptr;
    }
    return &m_messages[globalId];
}

quint64 MessageService::getMessageUniqueTs()
{
    quint64 ts = Telegram::Utils::formatTimeStamp(QDateTime::currentMSecsSinceEpoch());
    if (ts <= m_lastTimestamp) {
        ts = m_lastTimestamp + 1;
    }
    m_lastTimestamp = ts;
    return ts;
}

} // Server namespace

} // Telegram namespace
