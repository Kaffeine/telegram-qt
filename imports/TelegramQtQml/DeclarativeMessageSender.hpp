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

#ifndef TELEGRAM_DECLARATIVE_MESSAGE_SENDER_HPP
#define TELEGRAM_DECLARATIVE_MESSAGE_SENDER_HPP

#include "DeclarativeClientOperator.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class TELEGRAMQT_QML_EXPORT DeclarativeMessageSender : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit DeclarativeMessageSender(QObject *parent = nullptr);

    Peer peer() const { return m_peer; }

    QString text() const { return m_text; }

public Q_SLOTS:
    void setPeer(const Telegram::Peer peer);
    void setText(const QString &text);

    void sendMessage();
    void clearDraft();

Q_SIGNALS:
    void peerChanged(Telegram::Peer peer);
    void textChanged(const QString &text);

protected:
    Telegram::Peer m_peer;
    QString m_text;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_DECLARATIVE_MESSAGE_SENDER_HPP
