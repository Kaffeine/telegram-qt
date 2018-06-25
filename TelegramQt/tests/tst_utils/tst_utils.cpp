/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include <QObject>

#include "Utils.hpp"
#include "TelegramNamespace.hpp"
#include "RandomGenerator.hpp"

#include <QTest>
#include <QDebug>

#include "keys_data.hpp"

using namespace Telegram;

class tst_utils : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testAesEncryption();
    void testRsaLoad();
    void testRsaFingersprint();
    void testRsaEncryption();
    void testRsaKey();
    void testRsaKeyIsValid();
    void testDeterministicRandom();
};

void tst_utils::initTestCase()
{
    Telegram::initialize();
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_utils::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

void tst_utils::testAesEncryption()
{
    const QByteArray key(32, char(1));
    const QByteArray iv(32, char(2));
    const SAesKey aesKey(key, iv);
    const QByteArray sourceData = QByteArrayLiteral("TestData12345678");
    const QByteArray encodedData = Utils::aesEncrypt(sourceData, aesKey);
    QVERIFY(!encodedData.isEmpty());
    const QByteArray decodedData = Utils::aesDecrypt(encodedData, aesKey);
    QCOMPARE(sourceData, decodedData);
}

void tst_utils::testRsaLoad()
{
    const RsaKey privateKey = Utils::loadRsaPrivateKeyFromFile(TestKeyData::privateKeyFileName());
    QCOMPARE(privateKey.modulus, TestKeyData::keyModulus);
    QCOMPARE(privateKey.exponent, TestKeyData::keyExponent);
    QCOMPARE(privateKey.secretExponent, TestKeyData::keySecretExponent);
    QCOMPARE(privateKey.fingerprint, TestKeyData::keyFingerprint);
    const RsaKey publicKey = Utils::loadRsaKeyFromFile(TestKeyData::publicKeyFileName());
    QCOMPARE(publicKey.modulus, TestKeyData::keyModulus);
    QCOMPARE(publicKey.exponent, TestKeyData::keyExponent);
    QCOMPARE(publicKey.fingerprint, TestKeyData::keyFingerprint);
}

void tst_utils::testRsaFingersprint()
{
    const Telegram::RsaKey builtInKey = Utils::loadHardcodedKey();
    const quint64 fingerprint = Utils::getRsaFingerprints(builtInKey);
    QCOMPARE(fingerprint, builtInKey.fingerprint);
}

void tst_utils::testRsaEncryption()
{
    const RsaKey publicKey = Utils::loadRsaKeyFromFile(TestKeyData::publicKeyFileName());
    QVERIFY(publicKey.isValid());
    const QByteArray sourceData = QByteArrayLiteral("TestData12345678datatextasdfasdfzxcvzxcp1asdfa"
                                                    "sdf2391238721oi3jlkjlzxmc1231236789678056346xm"
                                                    "ncvkjafk;jh141234123zxcvzxcvasdfasdf1123789073");
    const QByteArray encodedData = Utils::rsa(sourceData, publicKey);
    QVERIFY(!encodedData.isEmpty());
    const QByteArray referenceEncodedData = QByteArray::fromHex(
                "05001ed872bfb0062f43b68b9c5eb1f48607e4ae4ad7e4724818e324c50fc10b"
                "5d2449f8fe3389e23cb63295b5b48c1ff939c718526f7e21a7e96780c1f41011"
                "16aba4b0db9a2108341246fc85815c2e6524832d5c632fbd83c763719bf3a5b9"
                "1b32924a0f84a3a1dff0cc8844f7879eb801d95dbe18cfc6c1bbcc3695b6fef7"
                "e21415976e87011e2d0d312a3719eee06cc8d9bddb327abae54fa8d6e069f556"
                "a4af0c149c952f5668105615c9f0356682772085a963b4cc90b2f5fa32dc5976"
                "5e041191cfc12c3cf1162c1bbf21af146837a4325d9761a7fbc28d61264a213a"
                "5075c2fe65d3f96e3fb7f4913b128856201f8f97fb6953c07441a62826a5dbce");
    QCOMPARE(encodedData, referenceEncodedData);
    const RsaKey privateKey = Utils::loadRsaPrivateKeyFromFile(TestKeyData::privateKeyFileName());
    QVERIFY(privateKey.isValid());
    const QByteArray decodedData = Utils::binaryNumberModExp(encodedData, privateKey.modulus, privateKey.secretExponent);
    QCOMPARE(sourceData, decodedData);
}

void tst_utils::testRsaKey()
{
    Telegram::RsaKey key;
    key.modulus = QByteArrayLiteral("keykeykey");
    key.exponent = QByteArrayLiteral("exp");
    key.fingerprint = 123456ull;

    Telegram::RsaKey key2;
    QVERIFY(key2.modulus.isEmpty());
    key2 = key;
    QCOMPARE(key.modulus, key2.modulus);
    QCOMPARE(key.exponent, key2.exponent);
    QCOMPARE(key.fingerprint, key2.fingerprint);
}

void tst_utils::testRsaKeyIsValid()
{
    Telegram::RsaKey key;
    QVERIFY2(!key.isValid(), "An emtpy should not be valid");
    key.modulus = QByteArrayLiteral("mod");
    QVERIFY2(!key.isValid(), "A key without an exponent and a fingerprint is not valid");
    key.exponent = QByteArrayLiteral("exp");
    QVERIFY2(!key.isValid(), "A key without a fingerprint is not valid");
    key.fingerprint = 123456ull;
    QVERIFY(!key.isValid());
    QVERIFY2(!key.isValid(), "The key fingerprint does not match the modulus and exponend, so the key should not be valid");
    key.updateFingersprint();
    QVERIFY2(key.isValid(), "The key should be valid");
    key.modulus.clear();
    QVERIFY2(!key.isValid(), "A key without a modulus is not valid");
}

void tst_utils::testDeterministicRandom()
{
    DeterministicGenerator deterministic;
    RandomGeneratorSetter generatorKeeper(&deterministic);

    quint32 r1 = 0;
    quint64 r2 = 0;
    Utils::randomBytes(&r1);
    Utils::randomBytes(&r2);
    QCOMPARE(r1, 0xb7cd2516u);
    QCOMPARE(r2, 0x7927fd99f6d9255dull);
    QByteArray bigChunk(0x80, 0);
    Utils::randomBytes(&bigChunk);
    QCOMPARE(bigChunk.toHex(), QByteArrayLiteral(
                 "f44095b6e320767f606f095eb7edab5581e9e3441adbb0d628832f7dc4574a77"
                 "a382973ce22911b7e4df2a9d2c693826bbd125bcf8a4d4a2f2a2a789398dd504"
                 "953abec4424f3cc56f35d17e47d8bc3a7a525f73b3d900dfca930e72955695b6"
                 "60b692035c79002440e77dfa5e893a2b51e2820e7c43ac11da6331a96b636bb3")
             );
}

QTEST_APPLESS_MAIN(tst_utils)

#include "tst_utils.moc"
