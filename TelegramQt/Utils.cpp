/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "Utils.hpp"

#define ZLIB_CONST
#include <zlib.h>

#include <QCryptographicHash>
#include <QDebug>
#include <QFileInfo>

#include "RandomGenerator.hpp"

#include "BigNumber.hpp"

namespace Telegram {

// Slightly modified version of Euclidean algorithm. Once we are looking for prime numbers,
// we can drop parity of asked numbers.
quint64 Utils::greatestCommonOddDivisor(quint64 a, quint64 b)
{
    while (a != 0 && b != 0) {
        while (!(b & 1)) {
            b >>= 1;
        }
        while (!(a & 1)) {
            a >>= 1;
        }
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return b == 0 ? a : b;
}

// Yet another copy of some unknown pq-solver algorithm.
// Links (join lines):
// https://github.com/DrKLO/Telegram/blob/433f59c5b9ed17543d8e206c83f0bc7c7edb43a6
// /TMessagesProj/jni/jni.c#L86
// https://github.com/ex3ndr/telegram-mt/blob/91b1186e567b0484d6f371b8e5c61c425daf867e
// /src/main/java/org/telegram/mtproto/secure/pq/PQLopatin.java#L35
// https://github.com/vysheng/tg/blob/1dad2e89933085ea1e3d9fb1becb1907ce5de55f
// /mtproto-client.c#L296
quint64 Utils::findDivider(quint64 number)
{
    int it = 0;
    quint64 g = 0;
    for (int i = 0; i < 3 || it < 10000; i++) {
        const quint64 q = ((rand() & 15) + 17) % number;
        quint64 x = (quint64) rand() % (number - 1) + 1;
        quint64 y = x;
        const quint32 lim = 1 << (i + 18);
        for (quint32 j = 1; j < lim; j++) {
            ++it;
            quint64 a = x;
            quint64 b = x;
            quint64 c = q;
            while (b) {
                if (b & 1) {
                    c += a;
                    if (c >= number) {
                        c -= number;
                    }
                }
                a += a;
                if (a >= number) {
                    a -= number;
                }
                b >>= 1;
            }
            x = c;
            const quint64 z = x < y ? number + x - y : x - y;
            g = greatestCommonOddDivisor(z, number);
            if (g != 1) {
                return g;
            }
            if (!(j & (j - 1))) {
                y = x;
            }
        }

        if (g > 1 && g < number) {
            return g;
        }
    }

    return 1;
}

QByteArray Utils::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QByteArray Utils::sha256(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha256);
}

quint64 Utils::getFingerprints(const QByteArray &data, const BitsOrder64 order)
{
    QByteArray shaSum = sha1(data);

    if (order == BitsOrder64::Lower64Bits) {
        return *((quint64 *) shaSum.mid(12).constData());
    } else {
        return *((quint64 *) shaSum.constData());
    }
}

QByteArray Utils::binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp)
{
    const BigNumber dataNum = BigNumber::fromByteArray(data);
    const BigNumber pubModulus = BigNumber::fromByteArray(mod);
    const BigNumber pubExponent = BigNumber::fromByteArray(exp);
    const BigNumber resultNum = dataNum.mod_exp(pubExponent, pubModulus);
    return resultNum.toByteArray();
}

QByteArray Utils::packGZip(const QByteArray &data)
{
    z_stream stream;
    stream.zalloc = nullptr;
    stream.zfree = nullptr;
    stream.opaque = nullptr;
    stream.avail_in = static_cast<uInt>(data.size());
    stream.next_in = reinterpret_cast<z_const Bytef*>(data.constData());

    constexpr int compressionLevel = 6; // It seems that Telegram uses this compression level
    int deflateResult = deflateInit2(&stream,
                                     compressionLevel,
                                     Z_DEFLATED,
                                     MAX_WBITS + 16, // (8 to 15) + 16 for gzip
                                     MAX_MEM_LEVEL,
                                     Z_DEFAULT_STRATEGY);
    if (deflateResult != Z_OK) {
        return QByteArray(); // deflate init failed
    }

    char buffer[c_gzipBufferSize];
    QByteArray result;

    do {
        stream.avail_out = c_gzipBufferSize;
        stream.next_out = reinterpret_cast<Bytef*>(buffer);
        deflate(&stream, Z_FINISH); // Z_FINISH
        result.append(buffer, static_cast<int>(c_gzipBufferSize - stream.avail_out));
    } while (stream.avail_out == 0);

    deflateEnd(&stream);

    return result;
}

QByteArray Utils::unpackGZip(const QByteArray &data)
{
    if (data.size() <= 4) {
        qDebug() << Q_FUNC_INFO << "Input data is too small to be gzip package";
        return QByteArray();
    }

    z_stream stream;
    stream.zalloc = nullptr;
    stream.zfree = nullptr;
    stream.opaque = nullptr;
    stream.avail_in = static_cast<uInt>(data.size());
    stream.next_in = reinterpret_cast<z_const Bytef*>(data.constData());

    int inflateResult = inflateInit2(&stream, MAX_WBITS + 32); // gzip decoding
    if (inflateResult != Z_OK) {
        return QByteArray(); // inflate init failed
    }

    char buffer[c_gzipBufferSize];
    QByteArray result;

    do {
        stream.avail_out = c_gzipBufferSize;
        stream.next_out = reinterpret_cast<Bytef*>(buffer);
        inflateResult = inflate(&stream, Z_NO_FLUSH);
        switch (inflateResult) {
        case Z_NEED_DICT:
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
        case Z_STREAM_ERROR:
            inflateEnd(&stream);
            return QByteArray();
        default:
            break;
        }
        result.append(buffer, static_cast<int>(c_gzipBufferSize - stream.avail_out));
    } while (stream.avail_out == 0);

    inflateEnd(&stream);

    return result;
}

} // Telegram
