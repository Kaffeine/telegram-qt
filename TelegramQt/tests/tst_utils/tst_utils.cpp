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
#include "RsaKey.hpp"
#include "Crypto/Aes.hpp"

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
    void testRsaLoadPublicPkcs1Key();
    void testRsaLoadPublicPkcs8Key();
    void testRsaLoadPrivateKey();
    void testRsaFingersprint();
    void testRsaEncryption();
    void testRsaKey();
    void testBuiltInKey();
    void testRsaKeyIsValid();
    void testDeterministicRandom();
    void testGzipPack();
    void testGzipUnpack();
    void testGzipOnDifferentDataSizes_data();
    void testGzipOnDifferentDataSizes();
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
    const Crypto::AesKey aesKey(key, iv);
    const QByteArray sourceData = QByteArrayLiteral("TestData12345678");
    const QByteArray encodedData = Crypto::aesEncrypt(sourceData, aesKey);
    QVERIFY(!encodedData.isEmpty());
    const QByteArray decodedData = Crypto::aesDecrypt(encodedData, aesKey);
    QCOMPARE(sourceData, decodedData);
}

void tst_utils::testRsaLoadPublicPkcs1Key()
{
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyPkcs1FileName());
    QCOMPARE(publicKey.modulus, TestKeyData::keyModulus);
    QCOMPARE(publicKey.exponent, TestKeyData::keyExponent);
    QCOMPARE(publicKey.fingerprint, TestKeyData::keyFingerprint);
}

void tst_utils::testRsaLoadPublicPkcs8Key()
{
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyPkcs1FileName());
    QCOMPARE(publicKey.modulus, TestKeyData::keyModulus);
    QCOMPARE(publicKey.exponent, TestKeyData::keyExponent);
    QCOMPARE(publicKey.fingerprint, TestKeyData::keyFingerprint);
}

void tst_utils::testRsaLoadPrivateKey()
{
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QCOMPARE(privateKey.modulus, TestKeyData::keyModulus);
    QCOMPARE(privateKey.exponent, TestKeyData::keyExponent);
    QCOMPARE(privateKey.secretExponent, TestKeyData::keySecretExponent);
    QCOMPARE(privateKey.fingerprint, TestKeyData::keyFingerprint);
}

void tst_utils::testRsaFingersprint()
{
    const Telegram::RsaKey builtInKey = RsaKey::defaultKey();
    const quint64 fingerprint = RsaKey::getFingerprint(builtInKey);
    QCOMPARE(fingerprint, builtInKey.fingerprint);
}

void tst_utils::testRsaEncryption()
{
    const RsaKey publicKey = RsaKey::fromFile(TestKeyData::publicKeyFileName());
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
    const RsaKey privateKey = RsaKey::fromFile(TestKeyData::privateKeyFileName());
    QVERIFY(privateKey.isValid());
    QVERIFY(privateKey.isPrivate());
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

void tst_utils::testBuiltInKey()
{
    const Telegram::RsaKey key = Telegram::RsaKey::defaultKey();
    QVERIFY(key.isValid());
    QCOMPARE(key.fingerprint, Telegram::RsaKey::getFingerprint(key));
}

void tst_utils::testRsaKeyIsValid()
{
    Telegram::RsaKey key;
    QVERIFY2(!key.isValid(), "An empty key should not be considered as valid");
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
    RandomGenerator::instance()->generate(&r1);
    RandomGenerator::instance()->generate(&r2);
    QCOMPARE(r1, 0xb7cd2516u);
    QCOMPARE(r2, 0x7927fd99f6d9255dull);
    QByteArray bigChunk(0x80, '\0');
    RandomGenerator::instance()->generate(&bigChunk);
    QCOMPARE(bigChunk.toHex(), QByteArrayLiteral(
                 "f44095b6e320767f606f095eb7edab5581e9e3441adbb0d628832f7dc4574a77"
                 "a382973ce22911b7e4df2a9d2c693826bbd125bcf8a4d4a2f2a2a789398dd504"
                 "953abec4424f3cc56f35d17e47d8bc3a7a525f73b3d900dfca930e72955695b6"
                 "60b692035c79002440e77dfa5e893a2b51e2820e7c43ac11da6331a96b636bb3")
             );
}

const QByteArray c_gzipPackedData = QByteArray::fromHex(
            QByteArrayLiteral(
                "1f8b08000000000000034be16c99c300"
                "04cbf736472b9f6a8e369f5eb98709c8"
                "173db2554610489f3976831524cf08c4"
                "7c8626967a86a6267a86e6a67aa6060c"
                "bb1921f20204e419a1f2ea4606068656"
                "06494616566946c6295669602e10a012"
                "89307d207b9950cc3533d7333544b117"
                "9f3c23541e6aaf9979b2958149aa05c8"
                "5e2342f63203313fb27f0c0d0c90edc5"
                "27cf0895c7e25f6342f6b2a0fbc712d5"
                "bff8e419a1f258fc6b82cf5e26a83e84"
                "7fccccf40c8de0fe6126cddc2464f7b0"
                "6284431a489f293ef70840f5f15a1a02"
                "83d542cf14ec1a0606e4704297373587"
                "c89f008a2f6863644801d207ae303274"
                "083330189432303c98cc02a6ef003572"
                "01e5125e41d206483dc36220eb950a83"
                "1cd4dc062b4e30ade0c7c030219e11ac"
                "4f401d685f46494941b195be7e895e6e"
                "aa3e248f80b403008b1f9e4c44030000"
                ));

const QByteArray c_gzipUnpackedData = QByteArray::fromHex(
            QByteArrayLiteral(
                "6409849c00000000a7bd835b23ca835b"
                "379779bc0200000015c4b51c11000000"
                "ccc6d80500000000010000000e313439"
                "2e3135342e3137352e353000bb010000"
                "ccc6d80510000000010000000e313439"
                "2e3135342e3137352e353000bb010000"
                "ccc6d805010000000100000027323030"
                "313a306232383a663233643a66303031"
                "3a303030303a303030303a303030303a"
                "30303061bb010000ccc6d80500000000"
                "020000000e3134392e3135342e313637"
                "2e353100bb010000ccc6d80510000000"
                "020000000e3134392e3135342e313637"
                "2e353100bb010000ccc6d80501000000"
                "0200000027323030313a303637633a30"
                "3465383a663030323a303030303a3030"
                "30303a303030303a30303061bb010000"
                "ccc6d80500000000030000000f313439"
                "2e3135342e3137352e313030bb010000"
                "ccc6d80510000000030000000f313439"
                "2e3135342e3137352e313030bb010000"
                "ccc6d805010000000300000027323030"
                "313a306232383a663233643a66303033"
                "3a303030303a303030303a303030303a"
                "30303061bb010000ccc6d80500000000"
                "040000000e3134392e3135342e313637"
                "2e393100bb010000ccc6d80510000000"
                "040000000e3134392e3135342e313637"
                "2e393100bb010000ccc6d80501000000"
                "0400000027323030313a303637633a30"
                "3465383a663030343a303030303a3030"
                "30303a303030303a30303061bb010000"
                "ccc6d80502000000040000000f313439"
                "2e3135342e3136362e313230bb010000"
                "ccc6d805030000000400000027323030"
                "313a303637633a303465383a66303034"
                "3a303030303a303030303a303030303a"
                "30303062bb010000ccc6d80501000000"
                "0500000027323030313a306232383a66"
                "3233663a663030353a303030303a3030"
                "30303a303030303a30303061bb010000"
                "ccc6d80510000000050000000d39312e"
                "3130382e35362e3132300000bb010000"
                "ccc6d80500000000050000000d39312e"
                "3130382e35362e3135370000bb010000"
                "c8000000a086010064000000c0d40100"
                "8813000030750000e093040030750000"
                "dc0500000a00000060ea000002000000"
                "c800000000a3020000ea24001e000000"
                "05000000803a090005000000204e0000"
                "905f010030750000102700000d687474"
                "70733a2f2f742e6d652f000015c4b51c"
                "00000000"
                ));

void tst_utils::testGzipPack()
{
    QByteArray result = Utils::packGZip(c_gzipUnpackedData);
    QCOMPARE(result.toHex(), c_gzipPackedData.toHex());
}

void tst_utils::testGzipUnpack()
{
    QByteArray result = Utils::unpackGZip(c_gzipPackedData);
    QCOMPARE(result.toHex(), c_gzipUnpackedData.toHex());
}

void tst_utils::testGzipOnDifferentDataSizes_data()
{
    QTest::addColumn<uint>("dataSize");
    QTest::newRow("Empty") << 0u;
    QTest::newRow("Small") << Utils::c_gzipBufferSize / 2;
    QTest::newRow("Exact buffer size") << Utils::c_gzipBufferSize;
    QTest::newRow("Twice as big") << Utils::c_gzipBufferSize * 2;
    QTest::newRow("Really big") << Utils::c_gzipBufferSize * 10;
    QTest::newRow("Big (not aligned 1)") << Utils::c_gzipBufferSize * 2 + 1;
    QTest::newRow("Big (not aligned 2)") << Utils::c_gzipBufferSize * 2 + 2;
    QTest::newRow("Big (not aligned 3)") << Utils::c_gzipBufferSize * 2 + 3;
}

void tst_utils::testGzipOnDifferentDataSizes()
{
    QFETCH(uint, dataSize);
    const int dataSizeInt = static_cast<int>(dataSize);

    DeterministicGenerator deterministic;
    RandomGeneratorSetter generatorKeeper(&deterministic);
    QByteArray data = RandomGenerator::instance()->generate(dataSizeInt);

    QByteArray packed = Utils::packGZip(data);
    QVERIFY(!packed.isEmpty());
    QByteArray unpacked = Utils::unpackGZip(packed);
    QCOMPARE(unpacked.size(), dataSizeInt);
}

QTEST_APPLESS_MAIN(tst_utils)

#include "tst_utils.moc"
