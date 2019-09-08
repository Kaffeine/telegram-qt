/*
   Copyright (C) 2019 Alexander Akulich <akulichalexander@gmail.com>

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

#include "DeclarativeMessageSender.hpp"

#include "Client.hpp"
#include "MessagingApi.hpp"

Telegram::Client::DeclarativeMessageSender::DeclarativeMessageSender(QObject *parent) :
    DeclarativeClientOperator(parent)
{
}

void Telegram::Client::DeclarativeMessageSender::setPeer(const Telegram::Peer peer)
{
    if (m_peer == peer) {
        return;
    }
    m_peer = peer;
    emit peerChanged(peer);
}

void Telegram::Client::DeclarativeMessageSender::setText(const QString &text)
{
    if (m_text == text) {
        return;
    }
    m_text = text;
    emit textChanged(text);
}

void Telegram::Client::DeclarativeMessageSender::sendMessage()
{
    client()->messagingApi()->sendMessage(m_peer, m_text);
    clearDraft();
}

void Telegram::Client::DeclarativeMessageSender::clearDraft()
{
    setText(QString());
}
