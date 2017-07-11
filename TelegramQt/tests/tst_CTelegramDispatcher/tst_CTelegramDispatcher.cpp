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

inline TLDcOption constructDcOption(quint32 id, QString hostname, QString ipAddress, quint32 port)
{
    TLDcOption result;
    result.id = id;
    result.hostname = hostname;
    result.ipAddress = ipAddress;
    result.port = port;
    return result;
}

void tst_CTelegramDispatcher::testUpdateDcOptions()
{
    TLDcOption newOption;
    newOption.id = 1;
    newOption.ipAddress = QLatin1String("149.154.175.50");
    newOption.port = 443;

    QVector<TLDcOption> options;
    options << constructDcOption(1, QLatin1String(""), QLatin1String("149.154.167.50"), 443);
    options << constructDcOption(2, QLatin1String(""), QLatin1String("149.154.167.51"), 443);
    options << constructDcOption(3, QLatin1String(""), QLatin1String("149.154.175.10"), 443);
    options << constructDcOption(4, QLatin1String(""), QLatin1String("149.154.167.91"), 443);
    options << constructDcOption(5, QLatin1String(""), QLatin1String("149.154.171.10"), 443);

    TLUpdate dcUpdate;
    dcUpdate.tlType = TLValue::UpdateDcOptions;
    dcUpdate.dcOptions = QVector<TLDcOption>() << newOption;

    CTestDispatcher dispatcher;
    dispatcher.testSetDcConfiguration(options);
    dispatcher.testProcessUpdate(dcUpdate);

    QVector<TLDcOption> newOptions = dispatcher.testGetDcConfiguration();

    options.replace(0, newOption);

    QVERIFY(options.count() == newOptions.count());

    for (int i = 0; i < newOptions.count(); ++i) {
        const TLDcOption &updated = newOptions.at(i);
        const TLDcOption &correct = options.at(i);

        QCOMPARE(updated.id, correct.id);
        QCOMPARE(updated.hostname, correct.hostname);
        QCOMPARE(updated.ipAddress, correct.ipAddress);
        QCOMPARE(updated.port, correct.port);
    }
}

QTEST_MAIN(tst_CTelegramDispatcher)

#include "tst_CTelegramDispatcher.moc"
