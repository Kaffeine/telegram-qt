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
#include <openssl/rsa.h>
#include <openssl/opensslv.h>

#include <zlib.h>

#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
#include <QFileInfo>

#include "CRawStream.hpp"
#include "RandomGenerator.hpp"

struct SslBigNumberContext {
    SslBigNumberContext() :
        m_context(BN_CTX_new())
    {
    }
    ~SslBigNumberContext()
    {
        BN_CTX_free(m_context);
    }
    BN_CTX *context() { return m_context; }

private:
    BN_CTX *m_context;
};

struct SslBigNumber {
    SslBigNumber() :
        m_number(BN_new())
    {
    }

    SslBigNumber(SslBigNumber &&number) :
        m_number(number.m_number)
    {
        number.m_number = nullptr;
    }

    SslBigNumber(const SslBigNumber &number) :
        m_number(BN_new())
    {
        BN_copy(m_number, number.m_number);
    }

    ~SslBigNumber()
    {
        if (m_number) {
            BN_free(m_number);
        }
    }

    static SslBigNumber fromHex(const QByteArray &hex)
    {
        SslBigNumber result;
        if (BN_hex2bn(&result.m_number, hex.constData()) != 0) {
            return result;
        }
        return SslBigNumber();
    }

    static SslBigNumber fromByteArray(const QByteArray &bin)
    {
        SslBigNumber result;
        if (BN_bin2bn((uchar *) bin.constData(), bin.length(), result.m_number) != 0) {
            return result;
        }
        return SslBigNumber();
    }

    static QByteArray toByteArray(const BIGNUM *number)
    {
        QByteArray result;
        result.resize(BN_num_bytes(number));
        BN_bn2bin(number, (uchar *) result.data());
        return result;
    }

    QByteArray toByteArray() const
    {
        return toByteArray(m_number);
    }

    SslBigNumber mod_exp(const SslBigNumber &exponent, const SslBigNumber &modulus) const
    {
        SslBigNumberContext context;
        SslBigNumber result;
        BN_mod_exp(result.m_number, number(), exponent.number(), modulus.number(), context.context());
        return result;
    }

    const BIGNUM *number() const { return m_number; }
    BIGNUM *number() { return m_number; }

private:
    BIGNUM *m_number;
};

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

namespace Telegram {

int Utils::randomBytes(void *buffer, int count)
{
    return RandomGenerator::instance()->generate(buffer, count);
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

bool hexArrayToBN(const QByteArray &hex, BIGNUM **n)
{
    return BN_hex2bn(n, hex.constData()) != 0;
}

bool binArrayToBN(const QByteArray &bin, BIGNUM **n)
{
    return BN_bin2bn((uchar *) bin.constData(), bin.length(), *n) != 0;
}

quint64 Utils::getFingerprints(const QByteArray &data, bool lowerOrderBits)
{
    QByteArray shaSum = sha1(data);

    if (lowerOrderBits) {
        return *((quint64 *) shaSum.mid(12).constData());
    } else {
        return *((quint64 *) shaSum.constData());
    }
}

quint64 Utils::getRsaFingerprints(const Telegram::RsaKey &key)
{
    if (key.modulus.isEmpty() || key.exponent.isEmpty()) {
        return 0;
    }
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    CRawStreamEx stream(&buffer);
    stream << key.modulus;
    stream << key.exponent;
    return getFingerprints(buffer.data());
}

Telegram::RsaKey Utils::loadHardcodedKey()
{
    Telegram::RsaKey result;
    result.modulus = SslBigNumber::fromHex(s_hardcodedRsaDataKey).toByteArray();
    result.exponent = SslBigNumber::fromHex(s_hardcodedRsaDataExp).toByteArray();
    result.fingerprint = s_hardcodedRsaDataFingersprint;
    return result;
}

Telegram::RsaKey Utils::loadRsaKeyFromFile(const QString &fileName)
{
    Telegram::RsaKey result;
    FILE *file = fopen(fileName.toLocal8Bit().constData(), "r");
    if (!file) {
        qWarning() << "Can not open RSA key file.";
        return result;
    }

    // Try SubjectPublicKeyInfo structure (BEGIN PUBLIC KEY)
    RSA *key = PEM_read_RSA_PUBKEY(file, 0, 0, 0);

    if (!key) {
        // Try PKCS#1 RSAPublicKey structure (BEGIN RSA PUBLIC KEY)
        key = PEM_read_RSAPublicKey(file, 0, 0, 0);
    }

    fclose(file);
    if (!key) {
        qWarning() << "Can not read RSA key.";
        return result;
    }
    const BIGNUM *n, *e;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    n=key->n;
    e=key->e;
#else
    RSA_get0_key(key, &n, &e, nullptr);
#endif

    result.modulus = SslBigNumber::toByteArray(n);
    result.exponent = SslBigNumber::toByteArray(e);
    result.fingerprint = getRsaFingerprints(result);
    RSA_free(key);
    return result;
}

Telegram::RsaKey Utils::loadRsaPrivateKeyFromFile(const QString &fileName)
{
    Telegram::RsaKey result;
    if (!QFileInfo::exists(fileName)) {
        qWarning() << "The RSA key file" << fileName << "does not exist";
        return result;
    }
    FILE *file = fopen(fileName.toLocal8Bit().constData(), "r");
    if (!file) {
        qWarning() << "Can not open RSA key file.";
        return result;
    }
    RSA *key = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL);

    fclose(file);
    if (!key) {
        qWarning() << "Can not read RSA key.";
        return result;
    }
    const BIGNUM *n, *e, *d;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    n=key->n;
    e=key->e;
    d=key->d;
#else
    RSA_get0_key(key, &n, &e, &d);
#endif

    result.modulus = SslBigNumber::toByteArray(n);
    result.exponent = SslBigNumber::toByteArray(e);
    result.secretExponent = SslBigNumber::toByteArray(d);
    result.fingerprint = getRsaFingerprints(result);
    RSA_free(key);
    return result;
}

Telegram::RsaKey Utils::loadRsaKey()
{
    return loadHardcodedKey();
}

QByteArray Utils::binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp)
{
    const SslBigNumber dataNum = SslBigNumber::fromByteArray(data);
    const SslBigNumber pubModulus = SslBigNumber::fromByteArray(mod);
    const SslBigNumber pubExponent = SslBigNumber::fromByteArray(exp);
    const SslBigNumber resultNum = dataNum.mod_exp(pubExponent, pubModulus);
    return resultNum.toByteArray();
}

QByteArray Utils::aesDecrypt(const QByteArray &data, const SAesKey &key)
{
    if (data.length() % AES_BLOCK_SIZE) {
        qCritical() << Q_FUNC_INFO << "Data is not padded (the size %" << AES_BLOCK_SIZE << " is not zero)";
        return QByteArray();
    }
    QByteArray result = data;
    QByteArray initVector = key.iv;
    AES_KEY dec_key;
    AES_set_decrypt_key((const uchar *) key.key.constData(), key.key.length() * 8, &dec_key);
    AES_ige_encrypt((const uchar *) data.constData(), (uchar *) result.data(), data.length(), &dec_key, (uchar *) initVector.data(), AES_DECRYPT);
    return result;
}

QByteArray Utils::aesEncrypt(const QByteArray &data, const SAesKey &key)
{
    if (data.length() % AES_BLOCK_SIZE) {
        qCritical() << Q_FUNC_INFO << "Data is not padded (the size %" << AES_BLOCK_SIZE << " is not zero)";
        return QByteArray();
    }
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

} // Telegram
