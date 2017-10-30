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

#include "CTestDispatcher.hpp"

#include <QBuffer>
#include <QTest>
#include <QDebug>

class tst_CTelegramDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramDispatcher(QObject *parent = 0);

private slots:
    void testUpdateDcOptions();

};

tst_CTelegramDispatcher::tst_CTelegramDispatcher(QObject *parent) :
    QObject(parent)
{
}

static TLDcOption constructDcOption(quint32 id, QString ipAddress, quint32 port)
{
    TLDcOption result;
    result.id = id;
    result.ipAddress = ipAddress;
    result.port = port;
    return result;
}

void tst_CTelegramDispatcher::testUpdateDcOptions()
{
    const TLUpdate dcUpdate = []() {
        TLUpdate dcUpdate;
        dcUpdate.tlType = TLValue::UpdateDcOptions;
        dcUpdate.dcOptions = QVector<TLDcOption>({constructDcOption(1, QLatin1String("149.154.175.50"), 443)});
        return dcUpdate;
    }();

    const QVector<TLDcOption> options = {
        constructDcOption(1, QLatin1String("149.154.167.50"), 443),
        constructDcOption(2, QLatin1String("149.154.167.51"), 443),
        constructDcOption(3, QLatin1String("149.154.175.10"), 443),
        constructDcOption(4, QLatin1String("149.154.167.91"), 443),
        constructDcOption(5, QLatin1String("149.154.171.10"), 443),
    };

    const QVector<TLDcOption> newOptions = [&options, &dcUpdate]() {
        QVector<TLDcOption> result = options;
        result.replace(0, dcUpdate.dcOptions.first());
        return result;
    }();

    CTestDispatcher dispatcher;
    dispatcher.testSetDcConfiguration(options);

    const QVector<TLDcOption> currentOptions1 = dispatcher.testGetDcConfiguration();
    QVERIFY(options.count() == currentOptions1.count());
    for (int i = 0; i < currentOptions1.count(); ++i) {
        const TLDcOption &updated = currentOptions1.at(i);
        const TLDcOption &correct = options.at(i);

        QCOMPARE(updated.id, correct.id);
        QCOMPARE(updated.ipAddress, correct.ipAddress);
        QCOMPARE(updated.port, correct.port);
    }

    dispatcher.testProcessUpdate(dcUpdate);

    const QVector<TLDcOption> currentOptions2 = dispatcher.testGetDcConfiguration();
    QVERIFY(newOptions.count() == currentOptions2.count());
    for (int i = 0; i < currentOptions2.count(); ++i) {
        const TLDcOption &updated = currentOptions2.at(i);
        const TLDcOption &correct = newOptions.at(i);

        QCOMPARE(updated.id, correct.id);
        QCOMPARE(updated.ipAddress, correct.ipAddress);
        QCOMPARE(updated.port, correct.port);
    }
}

QTEST_MAIN(tst_CTelegramDispatcher)

#include "tst_CTelegramDispatcher.moc"
