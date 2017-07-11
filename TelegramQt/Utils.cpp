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

#include <openssl/aes.h>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>

#include <zlib.h>

#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>

static const QByteArray s_hardcodedRsaDataKey("0c150023e2f70db7985ded064759cfecf0af328e69a41daf4d6f01b53813"
                                              "5a6f91f8f8b2a0ec9ba9720ce352efcf6c5680ffc424bd634864902de0b4"
                                              "bd6d49f4e580230e3ae97d95c8b19442b3c0a10d8f5633fecedd6926a7f6"
                                              "dab0ddb7d457f9ea81b8465fcd6fffeed114011df91c059caedaf97625f6"
                                              "c96ecc74725556934ef781d866b34f011fce4d835a090196e9a5f0e4449a"
                                              "f7eb697ddb9076494ca5f81104a305b6dd27665722c46b60e5df680fb16b"
                                              "210607ef217652e60236c255f6a28315f4083a96791d7214bf64c1df4fd0"
                                              "db1944fb26a2a57031b32eee64ad15a8ba68885cde74a5bfc920f6abf59b"
                                              "a5c75506373e7130f9042da922179251f");
static const QByteArray s_hardcodedRsaDataExp("010001");
static const quint64 s_hardcodedRsaDataFingersprint(0xc3b42b026ce86b21);

int Utils::randomBytes(char *buffer, int count)
{
    return RAND_bytes((unsigned char *) buffer, count);
}

// Slightly modified version of Euclidean algorithm. Once we are looking for prime numbers, we can drop parity of asked numbers.
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
// Links:
// https://github.com/DrKLO/Telegram/blob/433f59c5b9ed17543d8e206c83f0bc7c7edb43a6/TMessagesProj/jni/jni.c#L86
// https://github.com/ex3ndr/telegram-mt/blob/91b1186e567b0484d6f371b8e5c61c425daf867e/src/main/java/org/telegram/mtproto/secure/pq/PQLopatin.java#L35
// https://github.com/vysheng/tg/blob/1dad2e89933085ea1e3d9fb1becb1907ce5de55f/mtproto-client.c#L296
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

QByteArray bnToBinArray(const BIGNUM *n)
{
    QByteArray result;
    result.resize(BN_num_bytes(n));
    BN_bn2bin(n, (uchar *) result.data());
    return result;
}

QByteArray bnToHexArray(const BIGNUM *n)
{
    char *hex = BN_bn2hex(n);
    QByteArray result(hex);
    OPENSSL_free(hex);

    return result;
}

bool hexArrayToBN(const QByteArray &hex, BIGNUM **n)
{
    return BN_hex2bn(n, hex.constData()) != 0;
}

bool binArrayToBN(const QByteArray &bin, BIGNUM **n)
{
    return BN_bin2bn((uchar *) bin.constData(), bin.length(), *n) != 0;
}

quint64 Utils::getFingersprint(const QByteArray &data, bool lowerOrderBits)
{
    QByteArray shaSum = sha1(data);

    if (lowerOrderBits) {
        return *((quint64 *) shaSum.mid(12).constData());
    } else {
        return *((quint64 *) shaSum.constData());
    }
}

SRsaKey Utils::loadHardcodedKey()
{
    SRsaKey result;

    BIGNUM *tmpBN = BN_new();

    hexArrayToBN(s_hardcodedRsaDataKey, &tmpBN);

    result.key = bnToBinArray(tmpBN);

    hexArrayToBN(s_hardcodedRsaDataExp, &tmpBN);

    result.exp = bnToBinArray(tmpBN);

    result.fingersprint = s_hardcodedRsaDataFingersprint;

    BN_free(tmpBN);

    return result;
}

SRsaKey Utils::loadRsaKey()
{
    return loadHardcodedKey();
//    return loadRsaKeyFromFile("telegram_server_key.pub");
}

QByteArray Utils::binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp)
{
    QByteArray result;
    result.fill(char(0), 256);

    BN_CTX *bn_context = BN_CTX_new();

    BIGNUM *pubModulus = BN_new();
    BIGNUM *pubExponent = BN_new();
    BIGNUM *resultNum = BN_new();
    BIGNUM *dataNum = BN_new();

    binArrayToBN(mod, &pubModulus);
    binArrayToBN(exp, &pubExponent);

    BN_bin2bn((uchar *) data.constData(), data.length(), dataNum);

    BN_mod_exp(resultNum, dataNum, pubExponent, pubModulus, bn_context);

    BN_bn2bin(resultNum, (uchar *) result.data());

    BN_free(dataNum);
    BN_free(resultNum);
    BN_free(pubExponent);
    BN_free(pubModulus);

    BN_CTX_free(bn_context);

    return result;
}

QByteArray Utils::aesDecrypt(const QByteArray &data, const SAesKey &key)
{
    QByteArray result = data;

    QByteArray initVector = key.iv;

    AES_KEY dec_key;
    AES_set_decrypt_key((const uchar *) key.key.constData(), key.key.length() * 8, &dec_key);

    AES_ige_encrypt((const uchar *) data.constData(), (uchar *) result.data(), data.length(), &dec_key, (uchar *) initVector.data(), AES_DECRYPT);
    return result;
}

QByteArray Utils::aesEncrypt(const QByteArray &data, const SAesKey &key)
{
    QByteArray result = data;

    QByteArray initVector = key.iv;

    AES_KEY enc_key;
    AES_set_encrypt_key((const uchar *) key.key.constData(), key.key.length() * 8, &enc_key);

    AES_ige_encrypt((const uchar *) data.constData(), (uchar *) result.data(), data.length(), &enc_key, (uchar *) initVector.data(), AES_ENCRYPT);
    return result;
}

QByteArray Utils::unpackGZip(const QByteArray &data)
{
    if (data.size() <= 4) {
        qDebug() << Q_FUNC_INFO << "Input data is too small to be gzip package";
        return QByteArray();
    }

    QByteArray result;

    int inflateResult;
    z_stream stream;
    static const int CHUNK_SIZE = 1024;
    char out[CHUNK_SIZE];

    /* allocate inflate state */
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = data.size();
    stream.next_in = (Bytef*)(data.data());

    inflateResult = inflateInit2(&stream, 15 + 32); // gzip decoding

    if (inflateResult != Z_OK) {
        return QByteArray();
    }

    do {
        stream.avail_out = CHUNK_SIZE;
        stream.next_out = (Bytef*)(out);

        inflateResult = inflate(&stream, Z_NO_FLUSH);

        switch (inflateResult) {
        case Z_NEED_DICT:
            inflateResult = Z_DATA_ERROR;     // and fall through
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
        case Z_STREAM_ERROR:
            inflateEnd(&stream);
            return QByteArray();
        default:
            break;
        }

        result.append(out, CHUNK_SIZE - stream.avail_out);
    } while (stream.avail_out == 0);

    inflateEnd(&stream);

    return result;
}
