/*
   Copyright (C) 2014-2020 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_PEER_HPP
#define TELEGRAM_PEER_HPP

#include "telegramqt_global.h"

#include <QObject>

namespace Telegram {

class TELEGRAMQT_EXPORT Peer
{
    Q_GADGET
    Q_PROPERTY(Telegram::Peer::Type type MEMBER m_type)
    Q_PROPERTY(quint32 id MEMBER m_id)
public:
    enum Type {
        User,
        Chat,
        Channel,
    };
    Q_ENUM(Type)

    constexpr Peer() = default;
    constexpr Peer(quint32 id, Type t);

    constexpr Type type() const { return m_type; }
    constexpr quint32 id() const { return m_id; }

    Q_INVOKABLE constexpr bool isValid() const { return m_id; }

    constexpr bool operator==(const Peer &p) const
    {
        return (p.m_id == m_id) && (p.m_type == m_type);
    }

    constexpr bool operator!=(const Peer &p) const
    {
        return (p.m_id != m_id) || (p.m_type != m_type);
    }

    constexpr static Peer fromUserId(quint32 id)
    {
        return Peer(id, User);
    }

    constexpr static Peer fromChatId(quint32 id)
    {
        return Peer(id, Chat);
    }

    constexpr static Peer fromChannelId(quint32 id)
    {
        return Peer(id, Channel);
    }

    Q_REQUIRED_RESULT QString toString() const;
    Q_REQUIRED_RESULT static Peer fromString(const QString &string);

private:
    Type m_type = User;
    quint32 m_id = 0;
};

inline constexpr Peer::Peer(quint32 id, Type t)
    : m_type(t), m_id(id)
{
}

inline uint qHash(const Peer &key, uint seed)
{
    const quint64 k = static_cast<quint64>(key.id()) | (static_cast<quint64>(key.type()) << 32);
    return ::qHash(k, seed);
}

} // Telegram namespace

#endif // TELEGRAM_PEER_HPP
