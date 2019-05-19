/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "keys_data.hpp"
#include "TestAuthProvider.hpp"
#include "TestClientUtils.hpp"
#include "TestServerUtils.hpp"
#include "TestUserData.hpp"
#include "TestUtils.hpp"

#define TEST_PRIVATE_API

#ifdef TEST_PRIVATE_API
#include "DataStorage_p.hpp"
#endif

using namespace Telegram;

class tst_AccountApi : public QObject
{
    Q_OBJECT
public:
    explicit tst_AccountApi(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
};

tst_AccountApi::tst_AccountApi(QObject *parent) :
    QObject(parent)
{
}

void tst_AccountApi::initTestCase()
{
    qRegisterMetaType<UserData>();
    QVERIFY(TestKeyData::initKeyFiles());
}

void tst_AccountApi::cleanupTestCase()
{
    QVERIFY(TestKeyData::cleanupKeyFiles());
}

QTEST_GUILESS_MAIN(tst_AccountApi)

#include "tst_AccountApi.moc"
