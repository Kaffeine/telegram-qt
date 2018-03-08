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

#include "AesCtr.hpp"

#include <openssl/aes.h>
extern "C" {
#include <openssl/modes.h>
}

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_categoryCryptoAesCtr, "telegram.crypto.aes-ctr", QtWarningMsg)

namespace Telegram {

namespace Crypto {

AesCtrContext::AesCtrContext()
{
    m_ecount = QByteArray(EcountSize, char(0));
}

bool AesCtrContext::setKey(const QByteArray &key)
{
    if (key.size() != KeySize) {
        qCCritical(c_categoryCryptoAesCtr) << "AesCtrContext::setKey(): Invalid key size!";
        return false;
    }
    m_key = key;
    return true;
}

bool AesCtrContext::setIVec(const QByteArray &iv)
{
    if (iv.size() != IvecSize) {
        qCCritical(c_categoryCryptoAesCtr) << "AesCtrContext::setKey(): Invalid ivec size!";
        return false;
    }
    m_ivec = iv;
    return true;
}

QByteArray AesCtrContext::crypt(const QByteArray &in)
{
    QByteArray out;
    if (crypt(in, &out)) {
        return out;
    }
    return QByteArray();
}

bool AesCtrContext::crypt(const QByteArray &in, QByteArray *out)
{
    out->resize(in.size());
    union {
        char *ivecData;
        unsigned char *ivecSsl[16];
    };
    ivecData = m_ivec.data();
    union {
        char *ecountData;
        unsigned char *ecountSsl[16];
    };
    ecountData = m_ecount.data();

#ifdef TELEGRAM_DEBUG_CRYPTO
    qCDebug(c_categoryCryptoAesCtr).noquote() << QStringLiteral("Crypt 0x%1 (%2) bytes on ").arg(in.size(), 4, 16, QLatin1Char('0')).arg(in.size()) << m_description << "context" << this;
    qCDebug(c_categoryCryptoAesCtr) << "Key:" << m_key.toHex() << "Ivec:" << m_ivec.toHex() << "Ecount:" << m_ecount.toHex();
#endif // TELEGRAM_DEBUG_CRYPTO
    AES_KEY aes;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(m_key.constData()), 256, &aes);
    CRYPTO_ctr128_encrypt(reinterpret_cast<const uchar*>(in.constData()), reinterpret_cast<uchar*>(out->data()), in.size(), &aes, *ivecSsl, *ecountSsl, &m_num, (block128_f) AES_encrypt);
#ifdef TELEGRAM_DEBUG_CRYPTO
    qCDebug(c_categoryCryptoAesCtr) << "in:" << in.toHex();
    qCDebug(c_categoryCryptoAesCtr) << "out:" << out->toHex();
#endif
    return true;
}

} // Crypto

} // Telegram
