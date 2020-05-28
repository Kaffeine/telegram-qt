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

MessageData *MessageService::addMessage(quint32 fromId, Peer toPeer, const MessageContent &content)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, content));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate(Telegram::Utils::getCurrentTime());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

MessageData *MessageService::addServiceMessage(quint32 fromId, Peer toPeer, const ServiceMessageAction &action)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, action));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate(Telegram::Utils::getCurrentTime());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

MessageData *MessageService::replaceMessageContent(quint64 globalId, const MessageContent &content)
{
    MessageData *message = &m_messages[globalId];
    message->setContent(content);
    message->setEditDate(Telegram::Utils::getCurrentTime());
    return message;
}

const MessageData *MessageService::getMessage(quint64 globalId)
{
    if (!m_messages.contains(globalId)) {
        return nullptr;
    }
    return &m_messages[globalId];
}

bool MessageService::addMessageReference(quint64 globalId, const Peer &peer, quint32 messageId)
{
    if (!m_messages.contains(globalId)) {
        return false;
    }
    m_messages[globalId].addReference(peer, messageId);
    return true;
}

} // Server namespace

} // Telegram namespace
