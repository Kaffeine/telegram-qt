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

#include <QObject>
#include <QTest>

#include "Crypto/AesCtr.hpp"

class tst_crypto : public QObject
{
    Q_OBJECT
private slots:
    void aesCtrContext();
};

void tst_crypto::aesCtrContext()
{
    const QByteArray key = QByteArray::fromHex(QByteArrayLiteral("452114b9fbd4a919a27a256821dd1e72"
                                                                 "13c562f26f94883c4c7449b74fc8fb96"));
    const QByteArray iv1 = QByteArray::fromHex(QByteArrayLiteral("d4c0727f2043d69fcc94eb639cc9486a"));
    const QByteArray ec1 = QByteArray::fromHex(QByteArrayLiteral("00000000000000000000000000000000"));
    const QByteArray dec1 = QByteArray::fromHex(QByteArrayLiteral("c6c021e092aff8f9452114b9fbd4a919"
                                                                  "a27a256821dd1e7213c562f26f94883c"
                                                                  "4c7449b74fc8fb96d4c0727f2043d69f"
                                                                  "cc94eb639cc9486aefefefef39175b65"));
    const QByteArray enc1 = QByteArray::fromHex(QByteArrayLiteral("03d6cd84351bfb08df7faa6e2c5b727b"
                                                                  "6db368b1880ce7d6e1ccec708fbe098a"
                                                                  "cee6e68f6c0358efcaf9e08dfe593f16"
                                                                  "dd484f07170c583a61b2c3998de93b24"));
    const QByteArray iv2 = QByteArray::fromHex(QByteArrayLiteral("d4c0727f2043d69fcc94eb639cc9486e"));
    const QByteArray ec2 = QByteArray::fromHex(QByteArrayLiteral("11dca4648bc510508e5d2c76b4fe6041"));

    Telegram::Crypto::AesCtrContext sendContext;
    sendContext.setKey(key);
    sendContext.setIVec(iv1);
    Telegram::Crypto::AesCtrContext receiveContext = sendContext;
    // Test setup
    QCOMPARE(sendContext.ivec().toHex(), iv1.toHex());
    QCOMPARE(sendContext.ecount().toHex(), ec1.toHex());

    // Test copy constructor
    QCOMPARE(receiveContext.ivec().toHex(), iv1.toHex());
    QCOMPARE(receiveContext.ecount().toHex(), ec1.toHex());

    // Test encryption and the state after encryption
    const QByteArray encrypted1 = sendContext.crypt(dec1);
    QCOMPARE(encrypted1.toHex(), enc1.toHex());
    QCOMPARE(sendContext.ivec().toHex(), iv2.toHex());
    QCOMPARE(sendContext.ecount().toHex(), ec2.toHex());

    // Test decryption and the state after decryption
    const QByteArray decrypted1 = receiveContext.crypt(encrypted1);
    QCOMPARE(decrypted1.toHex(), dec1.toHex());
    QCOMPARE(receiveContext.ivec().toHex(), iv2.toHex());
    QCOMPARE(receiveContext.ecount().toHex(), ec2.toHex());

    // Test that the new state (including iv and ec) is used correctly
    const QByteArray dec2 = QByteArray::fromHex(QByteArrayLiteral("3936a545059585f4cf1bc7b6d62fc9ba"
                                                                  "0e520c5aded80d0f6159d468b99336cd"));
    const QByteArray enc2 = QByteArray::fromHex(QByteArrayLiteral("c9f2ce37f3c3116cc43821018460a599"
                                                                  "c0ed8af0f358ca971c0876503b5d7933"));
    const QByteArray iv3 = QByteArray::fromHex(QByteArrayLiteral("d4c0727f2043d69fcc94eb639cc94870"));
    const QByteArray ec3 = QByteArray::fromHex(QByteArrayLiteral("cebf86aa2d80c7987d51a23882ce4ffe"));

    const QByteArray encrypted2 = sendContext.crypt(dec2);
    QCOMPARE(encrypted2.toHex(), enc2.toHex());
    QCOMPARE(sendContext.ivec().toHex(), iv3.toHex());
    QCOMPARE(sendContext.ecount().toHex(), ec3.toHex());
    const QByteArray decrypted2 = receiveContext.crypt(encrypted2);
    QCOMPARE(decrypted2.toHex(), dec2.toHex());
    QCOMPARE(receiveContext.ivec().toHex(), iv3.toHex());
    QCOMPARE(receiveContext.ecount().toHex(), ec3.toHex());

    // Test some small data crypted step-by-step
    const QByteArray words = QByteArrayLiteral("word1");
    const QByteArray encrypted3 = sendContext.crypt(words);
    const QByteArray decrypted31 = receiveContext.crypt(encrypted3.left(3));
    const QByteArray decrypted32 = receiveContext.crypt(encrypted3.mid(3));
    QCOMPARE(words.toHex(), (decrypted31 + decrypted32).toHex());
}

QTEST_APPLESS_MAIN(tst_crypto)

#include "tst_crypto.moc"
