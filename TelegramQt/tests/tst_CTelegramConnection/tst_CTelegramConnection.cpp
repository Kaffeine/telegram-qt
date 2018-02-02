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

#include <QObject>

#include "CTestConnection.hpp"
#include "CTelegramTransport.hpp"
#include "TelegramUtils.hpp"

#include <QTest>
#include <QDebug>

#include <QDateTime>

class tst_CTelegramConnection : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramConnection(QObject *parent = nullptr);

private slots:
    void testTimestampAlwaysGrow();
    void testNewMessageId();
    void testClientTimestampNeverOdd();
    void testTimestampConversion();
    void testAesKeyGeneration();

};

tst_CTelegramConnection::tst_CTelegramConnection(QObject *parent) :
    QObject(parent)
{
}

void tst_CTelegramConnection::testTimestampAlwaysGrow()
{
    const quint64 time = 1395335796550;

    quint64 previousTimeStamp = CTelegramConnection::formatClientTimeStamp(time - 1);
    for (int i = 0; i < 2000; ++i) {
        const quint64 newTimeStamp = CTelegramConnection::formatClientTimeStamp(time + i);
        if (newTimeStamp < previousTimeStamp) {
            // Print erroneous method results and arguments.
            qDebug() << "previous:" << previousTimeStamp << time + i - 1;
            qDebug() << "new:" << newTimeStamp << time + i;
            qDebug() << "iteration:" << i;
            // Make same call to erroneous CTelegramCore::formatClientTimeStamp() to simplify debugging via break point.
            const quint64 timeStamp = CTelegramConnection::formatClientTimeStamp(time + i);
            Q_UNUSED(timeStamp)
        }
        QVERIFY2(newTimeStamp > previousTimeStamp, "New timestamp should be more or equal than previous");
        previousTimeStamp = newTimeStamp;
    }
}

void tst_CTelegramConnection::testNewMessageId()
{
    CTestConnection connection;

    quint64 previousTimeStamp = 0;
    for (int i = 0; i < 2000; ++i) {
        const quint64 newTimeStamp = connection.testNewMessageId();
        if (newTimeStamp < previousTimeStamp) {
            // Print erroneous method results and arguments.
            qDebug() << "previous:" << previousTimeStamp;
            qDebug() << "new:" << newTimeStamp;
            qDebug() << "iteration:" << i;
        }
        QVERIFY2(newTimeStamp > previousTimeStamp, "New timestamp should be more or equal than previous");
        previousTimeStamp = newTimeStamp;
    }
}

void tst_CTelegramConnection::testClientTimestampNeverOdd()
{
    quint64 time = 1395335796550;

    for (int i = 0; i < 2000; ++i) {
        if (CTelegramConnection::formatClientTimeStamp(time + i) & 3) {
            QVERIFY(!(CTelegramConnection::formatClientTimeStamp(time + i) & 3));
            break;
        }
    }
}

void tst_CTelegramConnection::testTimestampConversion()
{
    quint64 time = 1395335796550;
    quint64 ts = TelegramUtils::formatTimeStamp(time);
    QCOMPARE(TelegramUtils::timeStampToMSecsSinceEpoch(ts), time);

    ts = 0x532ea31d36cecc00;
    time = 1395565341214;

    QCOMPARE(TelegramUtils::timeStampToMSecsSinceEpoch(ts), time);
}

void tst_CTelegramConnection::testAesKeyGeneration()
{
    unsigned char auth[192] = {
        0x26, 0x40, 0xa5, 0xb0, 0x79, 0x4a, 0x7b, 0xed,
        0x84, 0x0e, 0x0b, 0xf8, 0x48, 0x0c, 0x17, 0x4b,
        0x1e, 0xde, 0xf5, 0x29, 0x21, 0x45, 0xf2, 0xbe,
        0x19, 0xa2, 0x63, 0xeb, 0x8e, 0xfb, 0x67, 0x19,
        0x06, 0x78, 0x6f, 0x72, 0xc2, 0x1d, 0x82, 0x16,
        0x3b, 0x7b, 0xad, 0xbb, 0x0f, 0x5b, 0xa7, 0xf3,
        0x53, 0xfa, 0xcb, 0xc2, 0x9e, 0xc0, 0xb1, 0xdd,
        0x9f, 0x61, 0x8c, 0x9c, 0x77, 0x57, 0x5b, 0x7f,
        0xd4, 0x47, 0x05, 0x2a, 0x98, 0xcd, 0xe5, 0xea,
        0x4a, 0xb0, 0x12, 0x00, 0x23, 0x1e, 0xf1, 0x17,
        0x6a, 0x80, 0xee, 0x2e, 0x9c, 0xd5, 0x7d, 0xfd,
        0x29, 0x5e, 0x11, 0xe5, 0xde, 0xe4, 0x6b, 0xd4,
        0x8e, 0x94, 0x71, 0xe4, 0x48, 0xa8, 0xa3, 0x54,
        0x9f, 0xdf, 0x55, 0xb7, 0x44, 0xd2, 0xa9, 0xe4,
        0xc2, 0xbb, 0x09, 0x3b, 0xa5, 0x61, 0x58, 0xaa,
        0xa4, 0x57, 0x44, 0x67, 0x25, 0xd5, 0x80, 0xd2,
        0x34, 0x83, 0xfd, 0x65, 0x93, 0x8a, 0x3a, 0xad,
        0xe4, 0x66, 0x5b, 0x46, 0x08, 0xf3, 0xd1, 0x50,
        0x9c, 0x9d, 0xd7, 0x4f, 0x81, 0x99, 0xd1, 0xaf,
        0x1f, 0x0d, 0x79, 0xb7, 0xd0, 0xe2, 0x79, 0xb5,
        0x8a, 0xef, 0x6d, 0xc6, 0x5a, 0xc7, 0xce, 0x77,
        0x0d, 0x5e, 0xa7, 0xd1, 0x8b, 0x2f, 0x1a, 0x97,
        0xe3, 0x46, 0x34, 0x76, 0x9d, 0xe5, 0xb6, 0xe8,
        0x8e, 0xbd, 0x27, 0x17, 0x98, 0x43, 0xb7, 0x8c
    };

    unsigned char messageKey[16] = {
        0x15, 0x02, 0xfd, 0xa4, 0x01, 0xf5, 0xf2, 0x2d,
        0x69, 0x07, 0x20, 0xac, 0xea, 0x77, 0x53, 0xe9
    };

    unsigned char expectedKey[32] = {
        0x61, 0x72, 0x1b, 0x31, 0x06, 0x68, 0xdc, 0x80,
        0x23, 0x2b, 0x35, 0xbb, 0xfa, 0x50, 0x4a, 0x8a,
        0x69, 0x7f, 0xc8, 0x2b, 0x09, 0x68, 0x0f, 0x33,
        0x1d, 0xd4, 0x23, 0x9a, 0x94, 0x39, 0xf1, 0x66
    };

    unsigned char expectedIv[32] = {
        0x51, 0x54, 0xfb, 0x77, 0xac, 0x38, 0x95, 0x37,
        0x35, 0xf5, 0x6d, 0x45, 0x49, 0xb1, 0x34, 0x83,
        0x23, 0x8b, 0x42, 0x4d, 0x4e, 0x5f, 0x97, 0x00,
        0x17, 0x97, 0x42, 0xb7, 0xb3, 0x44, 0x6e, 0x7b
    };

    QByteArray authArray;
    authArray.append((char *) auth, 192);

    QByteArray messageKeyArray;
    messageKeyArray.append((char *) messageKey, 16);

    QByteArray aesKeyArray;
    aesKeyArray.append((char *) expectedKey, 32);

    QByteArray aesIvArray;
    aesIvArray.append((char *) expectedIv, 32);

    CTestConnection core;

    core.setAuthKey(authArray);

    SAesKey result = core.testGenerateClientToServerAesKey(messageKeyArray);

    QCOMPARE(result.key, aesKeyArray);
    QCOMPARE(result.iv , aesIvArray);
}

QTEST_MAIN(tst_CTelegramConnection)

#include "tst_CTelegramConnection.moc"
