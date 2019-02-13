/*
   Copyright (C) 2014-2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include <QByteArray>

typedef struct bignum_st BIGNUM;

namespace Telegram {

namespace Utils {

struct SslBigNumber
{
    SslBigNumber();
    SslBigNumber(SslBigNumber &&other);
    SslBigNumber(const SslBigNumber &number);
    ~SslBigNumber();

    static SslBigNumber fromHex(const QByteArray &hex);
    static SslBigNumber fromByteArray(const QByteArray &bin);

    static QByteArray toByteArray(const BIGNUM *number);

    QByteArray toByteArray() const;

    SslBigNumber mod_exp(const SslBigNumber &exponent, const SslBigNumber &modulus) const;

    const BIGNUM *number() const { return m_number; }
    BIGNUM *number() { return m_number; }

private:
    BIGNUM *m_number = nullptr;
};

} // Utils namespace

} // Telegram namespace
