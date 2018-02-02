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

#include "RpcError.hpp"

#include <QTest>
#include <QDebug>

using namespace Telegram;

class tst_RpcError : public QObject
{
    Q_OBJECT
private slots:
    void errorReasonToString_data();
    void errorReasonToString();
    void errorStringToReason_data();
    void errorStringToReason();
};

void tst_RpcError::errorReasonToString_data()
{
    QTest::addColumn<QString>("reasonStr");
    QTest::addColumn<RpcError::Reason>("reason");
    QTest::addColumn<quint32>("argument");

    QTest::newRow("Phone migrate 2")
            << QStringLiteral("PHONE_MIGRATE_2")
            << RpcError::PhoneMigrateX
            << 2u;
    QTest::newRow("User migrate 5")
            << QStringLiteral("USER_MIGRATE_5")
            << RpcError::UserMigrateX
            << 5u;
    QTest::newRow("First name")
            << QStringLiteral("FIRSTNAME_INVALID")
            << RpcError::FirstnameInvalid
            << 0u;
    QTest::newRow("Invalid phone number")
            << QStringLiteral("PHONE_NUMBER_INVALID")
            << RpcError::PhoneNumberInvalid
            << 0u;
    QTest::newRow("Auth code hash is empty")
            << QStringLiteral("PHONE_CODE_HASH_EMPTY")
            << RpcError::PhoneCodeHashEmpty
            << 0u;
    QTest::newRow("Auth code is empty")
            << QStringLiteral("PHONE_CODE_EMPTY")
            << RpcError::PhoneCodeEmpty
            << 0u;
    QTest::newRow("Expired auth code")
            << QStringLiteral("PHONE_CODE_EXPIRED")
            << RpcError::PhoneCodeExpired
            << 0u;
    QTest::newRow("Invalid phone number")
            << QStringLiteral("API_ID_INVALID")
            << RpcError::ApiIdInvalid
            << 0u;
    QTest::newRow("File part number 234 is missing")
            << QStringLiteral("FILE_PART_234_MISSING")
            << RpcError::FilePartXMissing
            << 234u;
    QTest::newRow("Unregistered auth key")
            << QStringLiteral("AUTH_KEY_UNREGISTERED")
            << RpcError::AuthKeyUnregistered
            << 0u;
    QTest::newRow("Flood, wait for 5 minutes")
            << QStringLiteral("FLOOD_WAIT_300")
            << RpcError::FloodWaitX
            << 300u;
}

void tst_RpcError::errorReasonToString()
{
    QFETCH(QString, reasonStr);
    QFETCH(RpcError::Reason, reason);
    QFETCH(quint32, argument);
    QCOMPARE(RpcError::reasonToString(reason, argument), reasonStr);
}

void tst_RpcError::errorStringToReason_data()
{
    return errorReasonToString_data();
}

void tst_RpcError::errorStringToReason()
{
    QFETCH(QString, reasonStr);
    QFETCH(RpcError::Reason, reason);
    QFETCH(quint32, argument);
    RpcError::Reason r;
    quint32 arg = 0;
    QVERIFY(RpcError::reasonFromString(reasonStr.toLatin1(), &r, &arg));
    QCOMPARE(r, reason);
    QCOMPARE(arg, argument);
}

QTEST_APPLESS_MAIN(tst_RpcError)

#include "tst_RpcError.moc"
