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

#include "Storage.hpp"

namespace Telegram {

namespace Server {

Storage::Storage(QObject *parent) :
    QObject(parent)
{
}

MessageData *Storage::addMessage(quint32 fromId, Peer toPeer, const QString &text)
{
    ++m_lastGlobalId;
    m_messages.insert(m_lastGlobalId, MessageData(fromId, toPeer, text));
    MessageData *message = &m_messages[m_lastGlobalId];
    message->setDate(Telegram::Utils::getCurrentTime());
    message->setGlobalId(m_lastGlobalId);
    return message;
}

const MessageData *Storage::getMessage(quint64 globalId)
{
    if (!m_messages.contains(globalId)) {
        return nullptr;
    }
    return &m_messages[globalId];
}

} // Server namespace

} // Telegram namespace
