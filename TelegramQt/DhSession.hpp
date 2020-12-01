// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (C) 2020 Alexandr Akulich <akulichalexander@gmail.com>
 *
 * This file is a part of TelegramQt project.
 */

#include "telegramqt_global.h"

#include "MTProto/TLNumbers.hpp"
#include "Crypto/Aes.hpp"

namespace Telegram {

class TELEGRAMQT_INTERNAL_EXPORT BaseDhSession
{
public:
    TLNumber128 clientNonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
    quint64 pq = 0;
    quint32 p = 0;
    quint32 q = 0;

    quint32 g = 0;
    QByteArray dhPrime;
    QByteArray gA;

    Crypto::AesKey tmpAesKey;
};

} // Telegram namespace
