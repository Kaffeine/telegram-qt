/*
   Copyright (C) 2015-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "TelegramNamespace_p.hpp"

#include <QTest>
#include <QDebug>

using namespace Telegram;

class RemoteFileTest : public RemoteFile
{
public:
    RemoteFileTest();
    RemoteFileTest(const RemoteFile &file);
    using RemoteFile::Private;
    using RemoteFile::d;

    RemoteFileTest &operator=(const RemoteFile &file)
    {
        *d = *Private::get(&file);
        return *this;
    }
};

RemoteFileTest::RemoteFileTest() :
    RemoteFile()
{
}

RemoteFileTest::RemoteFileTest(const RemoteFile &file) :
    RemoteFile(file)
{
}

class tst_TelegramRemoteFile : public QObject
{
    Q_OBJECT
public:
    explicit tst_TelegramRemoteFile(QObject *parent = nullptr);

private slots:
    void serialization_fileLocation();
    void serialization_inputFileLocation();

};

tst_TelegramRemoteFile::tst_TelegramRemoteFile(QObject *parent) :
    QObject(parent)
{
}

void tst_TelegramRemoteFile::serialization_fileLocation()
{
    TLFileLocation testLocation;
    testLocation.tlType = TLValue::FileLocation;
    testLocation.volumeId = 0x123456ul;
    testLocation.localId = 0x43211234u;
    testLocation.secret = 0x12345678ul;
    testLocation.dcId = 0x1u;

    RemoteFileTest remoteFile;
    remoteFile.d->setFileLocation(&testLocation);
    remoteFile.d->m_size = 0x23456789ul;

    const QString fileId = remoteFile.getUniqueId();
    RemoteFileTest deserializedRemoteFile = RemoteFile::fromUniqueId(fileId);

    const TLFileLocation deserializedLocation = deserializedRemoteFile.d->getFileLocation();
    QCOMPARE(deserializedLocation.tlType  , testLocation.tlType);
    QCOMPARE(deserializedLocation.dcId    , testLocation.dcId);
    QCOMPARE(deserializedLocation.volumeId, testLocation.volumeId);
    QCOMPARE(deserializedLocation.localId , testLocation.localId);
    QCOMPARE(deserializedLocation.secret  , testLocation.secret);
}

void tst_TelegramRemoteFile::serialization_inputFileLocation()
{
    TLInputFileLocation testLocation;
    testLocation.tlType = TLValue::InputVideoFileLocation;
    testLocation.id = 0xaabbccddeeff1234ull;
    testLocation.accessHash = 0x12345678abcdef99ul;

    RemoteFileTest remoteFile;
    remoteFile.d->setInputFileLocation(&testLocation);
    remoteFile.d->m_dcId = 0x7;
    remoteFile.d->m_size = 0x34567899ul;

    const QString fileId = remoteFile.getUniqueId();
    RemoteFileTest deserializedRemoteFile = RemoteFile::fromUniqueId(fileId);

    QCOMPARE(deserializedRemoteFile.d->m_dcId, remoteFile.d->m_dcId);
    QCOMPARE(deserializedRemoteFile.d->m_size, remoteFile.d->m_size);

    const TLInputFileLocation deserializedLocation = deserializedRemoteFile.d->getInputFileLocation();
    QCOMPARE(deserializedLocation.tlType    , testLocation.tlType);
    QCOMPARE(deserializedLocation.id        , testLocation.id);
    QCOMPARE(deserializedLocation.accessHash, testLocation.accessHash);
}

QTEST_APPLESS_MAIN(tst_TelegramRemoteFile)

#include "tst_TelegramRemoteFile.moc"
