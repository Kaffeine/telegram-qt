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

#include "CTelegramTransport.hpp"
#include "CTelegramConnection.hpp"

#include <QTest>
#include <QDebug>

#include <QDateTime>

class NullTransport : public CTelegramTransport
{
    Q_OBJECT
public:
    explicit NullTransport(QObject *parent = nullptr) : CTelegramTransport(parent) { }

public:
    void connectToHost(const QString &ipAddress, quint32 port) override
    {
        Q_UNUSED(ipAddress)
        Q_UNUSED(port)
    }
    void disconnectFromHost() override {}

protected:
    void sendPackageImplementation(const QByteArray &package) override
    {
        Q_UNUSED(package)
    }
};

class tst_CTelegramTransport : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramTransport(QObject *parent = nullptr);

private slots:
    void testNewMessageId();
    void testNewMessageIdExtra();

};

tst_CTelegramTransport::tst_CTelegramTransport(QObject *parent) :
    QObject(parent)
{
}

void tst_CTelegramTransport::testNewMessageId()
{
    NullTransport transport;
    const quint64 time = 1395335796550;
    for (quint64 t = 0; t < 12; ++t) {
        const quint64 telegramTimeStamp = CTelegramConnection::formatTimeStamp(time) + t;
        const quint64 ending = telegramTimeStamp & 3;
        quint64 previousTS = telegramTimeStamp - 1;
        for (quint64 i = 0; i < 2000; ++i) {
            const quint64 newTimeStamp = transport.getNewMessageId(telegramTimeStamp);
            const quint64 newEnding = newTimeStamp & 3;
            if (ending != newEnding) {
                qDebug() << ending << "vs" << newEnding << "for TS" << telegramTimeStamp << "after TS" << previousTS;
            }
            QCOMPARE(ending, newEnding);

            if (newTimeStamp <= previousTS) {
                // Print erroneous method results and arguments.
                qDebug() << "previous:" << telegramTimeStamp;
                qDebug() << "new:" << newTimeStamp;
                qDebug() << "iteration:" << i;
            }
            QVERIFY2(newTimeStamp > previousTS, "The new timestamp should be more or equal than previous");
            previousTS = newTimeStamp;
        }
    }
}

void tst_CTelegramTransport::testNewMessageIdExtra()
{
    const QVector<quint64> times = {
        0x1234567891ull, // Server response1 to a client message
        0x1234567891ull, // Server response2 to a client message
        0x1234567893ull, // Server own message
        0x1234567891ull, // Server response3 to a client message
                                   };
    NullTransport transport;

    const QVector<quint64> expectedTimeStamp = {
        0x1234567891ull, // Server response1 to a client message
        0x1234567895ull, // Server response2 to a client message
        0x1234567897ull, // Server own message
        0x1234567899ull, // Server response3 to a client message
                                   };

    quint64 previousTS = times.first() - 1;
    for (int i = 0; i < times.count(); ++i) {
        const quint64 newTimeStamp = transport.getNewMessageId(times.at(i));
        if (newTimeStamp <= previousTS) {
            qWarning() << QString::number(times.at(i), 2) << "newTS:" << QString::number(newTimeStamp, 2) << "expected:" << QString::number(expectedTimeStamp.at(i), 2);
        }
        QVERIFY2(newTimeStamp > previousTS, "The new timestamp should be more or equal than previous");
        if (newTimeStamp != expectedTimeStamp.at(i)) {
            qWarning() << QString::number(expectedTimeStamp.at(i), 0x10);
        }
        QCOMPARE(newTimeStamp, expectedTimeStamp.at(i));
        previousTS = newTimeStamp;
    }
}

QTEST_MAIN(tst_CTelegramTransport)

#include "tst_CTelegramTransport.moc"
