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

#include "RsaKey.hpp"

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/opensslv.h>

#include <QFileInfo>
#include <QLoggingCategory>

#include "RawStream.hpp"
#include "Utils.hpp"

#include "BigNumber_p.hpp"
#include "BigNumber.hpp"

static const QByteArray c_hardcodedRsaDataKey(
        "0c150023e2f70db7985ded064759cfecf0af328e69a41daf4d6f01b53813"
        "5a6f91f8f8b2a0ec9ba9720ce352efcf6c5680ffc424bd634864902de0b4"
        "bd6d49f4e580230e3ae97d95c8b19442b3c0a10d8f5633fecedd6926a7f6"
        "dab0ddb7d457f9ea81b8465fcd6fffeed114011df91c059caedaf97625f6"
        "c96ecc74725556934ef781d866b34f011fce4d835a090196e9a5f0e4449a"
        "f7eb697ddb9076494ca5f81104a305b6dd27665722c46b60e5df680fb16b"
        "210607ef217652e60236c255f6a28315f4083a96791d7214bf64c1df4fd0"
        "db1944fb26a2a57031b32eee64ad15a8ba68885cde74a5bfc920f6abf59b"
        "a5c75506373e7130f9042da922179251f");
static const QByteArray c_hardcodedRsaDataExp("010001");
static const quint64 c_hardcodedRsaDataFingersprint(0xc3b42b026ce86b21);

namespace Telegram {

void RsaKey::updateFingersprint()
{
    fingerprint = getFingerprint(*this);
}

bool RsaKey::isValid() const
{
    return !modulus.isEmpty() && !exponent.isEmpty() && (fingerprint == getFingerprint(*this));
}

bool RsaKey::isPrivate() const
{
    return isValid() && !secretExponent.isEmpty();
}

void RsaKey::loadFromFile(const QString &fileName)
{
    *this = fromFile(fileName);
}

quint64 RsaKey::getFingerprint(const RsaKey &key)
{
    if (key.modulus.isEmpty() || key.exponent.isEmpty()) {
        return 0;
    }
    RawStreamEx stream(RawStreamEx::WriteOnly);
    stream << key.modulus;
    stream << key.exponent;
    return Utils::getFingerprints(stream.getData(), Utils::Lower64Bits);
}

RsaKey RsaKey::fromFile(const QString &fileName)
{
    if (!QFileInfo::exists(fileName)) {
        qWarning() << "The RSA key file" << fileName << "does not exist";
        return RsaKey();
    }

    Telegram::RsaKey result;
    FILE *file = fopen(fileName.toLocal8Bit().constData(), "r");
    if (!file) {
        qWarning() << "Can not open RSA key file.";
        return result;
    }

    // Try PrivateKey
    RSA *key = PEM_read_RSAPrivateKey(file, nullptr, nullptr, nullptr);
    bool keyIsPrivate = key;

    if (!key) {
        fseek(file, 0, SEEK_SET);
        // Try SubjectPublicKeyInfo structure (BEGIN PUBLIC KEY)
        key = PEM_read_RSA_PUBKEY(file, nullptr, nullptr, nullptr);
    }

    if (!key) {
        fseek(file, 0, SEEK_SET);
        // Try PKCS#1 RSAPublicKey structure (BEGIN RSA PUBLIC KEY)
        key = PEM_read_RSAPublicKey(file, nullptr, nullptr, nullptr);
    }

    fclose(file);
    if (!key) {
        return result;
    }
    const BIGNUM *n, *e, *d;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    n=key->n;
    e=key->e;
    if (keyIsPrivate) {
        d=key->d;
    }
#else
    if (keyIsPrivate) {
        RSA_get0_key(key, &n, &e, &d);
    } else {
        RSA_get0_key(key, &n, &e, nullptr);
    }
#endif

    result.modulus = Utils::bignumToByteArray(n);
    result.exponent = Utils::bignumToByteArray(e);
    if (keyIsPrivate) {
        result.secretExponent = Utils::bignumToByteArray(d);
    }
    result.updateFingersprint();
    RSA_free(key);
    return result;
}

RsaKey RsaKey::defaultKey()
{
    RsaKey result;
    result.modulus = Utils::BigNumber::fromHex(c_hardcodedRsaDataKey).toByteArray();
    result.exponent = Utils::BigNumber::fromHex(c_hardcodedRsaDataExp).toByteArray();
    result.fingerprint = c_hardcodedRsaDataFingersprint;
    return result;
}

} // Telegram namespace
