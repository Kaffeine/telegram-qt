/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_AES_CTR_HPP
#define TELEGRAM_AES_CTR_HPP

#include "telegramqt_global.h"

#include <QByteArray>

namespace Telegram {

namespace Crypto {

class TELEGRAMQT_INTERNAL_EXPORT AesCtrContext
{
public:
    explicit AesCtrContext();
    static constexpr int KeySize = 32;
    static constexpr int IvecSize = 16;
    static constexpr int EcountSize = 16;

    QByteArray key() const { return m_key; }
    bool setKey(const QByteArray &key);

    QByteArray ivec() const { return m_ivec; }
    bool setIVec(const QByteArray &iv);

    bool hasKey() const { return !m_key.isEmpty(); }

    QByteArray ecount() const { return m_ecount; }
    quint32 num() const { return m_num; }

    QByteArray crypt(const QByteArray &in);
    bool crypt(const QByteArray &in, QByteArray *out);

    // The context description is needed only for debug
    void setDescription(const QByteArray &desc) { m_description = desc; }
protected:
    QByteArray m_key;
    QByteArray m_ivec;
    QByteArray m_ecount;
    quint32 m_num = 0;
    QByteArray m_description;
};

} // Crypto

} // Telegram

#endif // TELEGRAM_AES_CTR_HPP
