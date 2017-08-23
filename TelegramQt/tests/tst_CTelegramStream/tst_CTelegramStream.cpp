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

#include "CTelegramStream.hpp"

#include <QBuffer>
#include <QTest>
#include <QDebug>

struct STestData {
    QVariant value;
    QByteArray serializedData;
    STestData(QVariant v, QByteArray e) : value(v), serializedData(e) { }
};

class tst_CTelegramStream : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramStream(QObject *parent = nullptr);

private slots:
    void stringsLimitSerialization();
    void shortStringSerialization();
    void longStringSerialization();
    void intSerialization();
    void vectorOfIntsSerialization();
    void vectorDeserializationError();
    void tlNumbersSerialization();
    void tlDcOptionDeserialization();
    void readError();

};

tst_CTelegramStream::tst_CTelegramStream(QObject *parent) :
    QObject(parent)
{
}

void tst_CTelegramStream::shortStringSerialization()
{
    QList<STestData> data;

    const char serializedChars1[8] = { char(4), 't', 'e', 's', 't', 0, 0, 0 };
    const char serializedChars2[8] = { char(5), 't', 'e', 's', 't', '5', 0, 0 };
    const char serializedChars3[8] = { char(6), 't', 'e', 's', 't', '6', '6', 0 };
    const char serializedChars4[8] = { char(7), '7', 's', 'e', 'v', 'e', 'n', '7' };

    data.append(STestData(QLatin1String("test"), QByteArray(serializedChars1, sizeof(serializedChars1))));
    data.append(STestData(QLatin1String("test5"), QByteArray(serializedChars2, sizeof(serializedChars2))));
    data.append(STestData(QLatin1String("test66"), QByteArray(serializedChars3, sizeof(serializedChars3))));
    data.append(STestData(QLatin1String("7seven7"), QByteArray(serializedChars4, sizeof(serializedChars4))));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        QCOMPARE(device.data(), data.at(i).serializedData);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedData);
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

        QString result;

        stream >> result;

        QCOMPARE(result, data.at(i).value.toString());
    }
}

void tst_CTelegramStream::stringsLimitSerialization()
{
    QList<STestData> data;

    QString stringToTest;
    QByteArray serializedString;

    for (int i = 0; i < 5; ++i) {
        stringToTest = QString(i, QChar('a'));
        serializedString = QByteArray(i, char('a'));
        serializedString.prepend(char(i));
        if (serializedString.length() % 4)
            serializedString.append(QByteArray(4 - serializedString.length() % 4, char(0)));

        data.append(STestData(stringToTest, serializedString));
    }

    stringToTest = QString(253, QChar::fromLatin1(char(0x70)));
    serializedString = QByteArray(253, char(0x70));
    serializedString.prepend(char(253));
    serializedString.append(char(0));
    serializedString.append(char(0));

    data.append(STestData(stringToTest, serializedString));

    stringToTest = QString(254, QChar::fromLatin1(char(0x71)));
    serializedString = QByteArray(254, char(0x71));

    serializedString.prepend(char(0)); // LengthBig
    serializedString.prepend(char(0)); // LengthMiddle
    serializedString.prepend(char(254)); // LengthLittle

    serializedString.prepend(char(254)); // Long-string marker

    serializedString.append(char(0)); // Padding1
    serializedString.append(char(0)); // Padding2

    data.append(STestData(stringToTest, serializedString));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        if ((data.at(i).serializedData.length() > 10) && (device.data() != data.at(i).serializedData)) {
            qDebug() << QString("Actual (%1 bytes):").arg(device.data().length()) << device.data().toHex();
            qDebug() << QString("Expected (%1 bytes):").arg(data.at(i).serializedData.length()) << data.at(i).serializedData.toHex();
        }

        QCOMPARE(device.data(), data.at(i).serializedData);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedData);
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

        QString result;

        stream >> result;

        if (result != data.at(i).value.toString()) {
            qDebug() << QString("Error at %1").arg(i);
        }

        QCOMPARE(result, data.at(i).value.toString());
    }
}

void tst_CTelegramStream::longStringSerialization()
{
    QList<STestData> data;

    static const QString stringToTest1 = QStringLiteral("This is a long string, which is going to be serialized. "
                                                        "Starting to speek something wise and sage... Abadfa"
                                                        "dfa uzxcviuwekrhalflkjhzvzxciuvyoiuwehrkblabla-asdfasdf"
                                                        "qwrq25!@!@(#*&!$@%@!()#*&@#($)&*)(!@*&#)(!*@&#()!@*&$%!"
                                                        "*@&$&^!%$&*#@%$&*%^@#$&%@#$@#*$&^@#*(&^@#%*&^!F132465798"
                                                        "+760++-*/*/651321///???asd0f98`0978jhkjhzxcv....end");

    static const QString stringToTest2 = QStringLiteral("It seems that we need to test some much longer string"
                                                        "with four hundred characters at least. AS:DLMZXCoiu123787"
                                                        "Ljlkj123l4mzxcv989871234-09-0asd;lv,;,l;xzcvllas "
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "  1234asplk;lkxzv==+_)!@#(*&234234zsdclkmasd2143164537xgcxn"
                                                        "here we are!"
                                                        );

    auto serialize = [](const QByteArray &str) {
        const int len = str.length();
        QByteArray serialized(1, char(0xfe));
        serialized.append(char(len & 0xff));
        serialized.append(char((len & 0xff00) >> 8));
        serialized.append(char((len & 0xff0000) >> 16));
        serialized.append(str);

        while (serialized.length() % 4) {
            serialized.append(char(0));
        }
        return serialized;
    };

    data.append(STestData(stringToTest1, serialize(stringToTest1.toUtf8())));
    data.append(STestData(stringToTest2, serialize(stringToTest2.toUtf8())));

    /* Serialization */
    for (int i = 0; i < data.count(); ++i) {
        QByteArray dataArray;
        CTelegramStream stream(&dataArray, true);
        const QString originString = data.at(i).value.toString();
        stream << originString;
        QVERIFY2(!(dataArray.length() % 4), "Results data is not padded (total length is not divisible by 4)");
        QVERIFY2((dataArray.length() >= originString.length() + 4), "Results data size for long string should be at least stringLength + one byte for 0xfe + three bytes for size");
        QVERIFY2((dataArray.length() <= originString.length() + 4 + 3), "Results data size for long string should never be more, than stringLength + 4 + 3,"
                                                                        "because we should never pad for more, than 3 bytes");
        QCOMPARE(dataArray, data.at(i).serializedData);
    }

    /* Deserialization */
    for (int i = 0; i < data.count(); ++i) {
        CTelegramStream stream(data.at(i).serializedData);
        QString result;
        stream >> result;
        QCOMPARE(result, data.at(i).value.toString());
    }
}

void tst_CTelegramStream::intSerialization()
{
    QList<STestData> data;

    {
        QByteArray testSerialized;
        quint32 values[5] = { 0x01, 0xff, 0x00, 0xaabbcc, 0xdeadbeef };
        const char serialized1[4] = { char(values[0]), 0, 0, 0 };
        const char serialized2[4] = { char(values[1]), 0, 0, 0 };
        const char serialized3[4] = { char(values[2]), 0, 0, 0 };
        const char serialized4[4] = { char(0xcc), char(0xbb), char(0xaa), char(0x00) };
        const char serialized5[4] = { char(0xef), char(0xbe), char(0xad), char(0xde) };

        testSerialized.append(serialized1, 4);
        testSerialized.append(serialized2, 4);
        testSerialized.append(serialized3, 4);
        testSerialized.append(serialized4, 4);
        testSerialized.append(serialized5, 5);

        for (int i = 0; i < 5; ++i)
            data.append(STestData(values[i], testSerialized.mid(i * 4, 4)));
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << data.at(i).value.value<quint32>();

        QCOMPARE(device.data(), data.at(i).serializedData);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedData);
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

        quint32 result;

        stream >> result;

        QCOMPARE(result, data.at(i).value.value<quint32>());
    }
}

void tst_CTelegramStream::vectorOfIntsSerialization()
{
    TLVector<quint64> vector;
    vector.append(0x12345678);
    QByteArray encoded = QByteArray::fromHex("15c4b51c010000007856341200000000");

    if (TLValue::Vector != 0x1cb5c415) {
        QFAIL("The test data is not updated to the current API yet");
    }

    {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << vector;
        QCOMPARE(device.data(), encoded);
    }

    {
        QBuffer device;
        device.setData(encoded);
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

        TLVector<quint64> value;

        stream >> value;

        QCOMPARE(value, vector);
    }
}

void tst_CTelegramStream::vectorDeserializationError()
{
    TLVector<quint32> vector;

    const QByteArray encoded = QByteArray::fromHex("12345678");

    {
        CTelegramStream stream(encoded);

        stream >> vector;
        QVERIFY(!vector.isValid());
    }
}

void tst_CTelegramStream::tlNumbersSerialization()
{
    QVector<TLNumber128> vector128;
    QVector<QByteArray> encoded128;

    TLNumber128 num128;
    QByteArray encoded;

    {
        num128.parts[0] = 1;
        num128.parts[1] = 0;
        encoded = QByteArray::fromHex("01000000000000000000000000000000");
        vector128.append(num128);
        encoded128.append(encoded);
    }
    {
        num128.parts[0] = 0;
        num128.parts[1] = 1;
        encoded = QByteArray::fromHex("00000000000000000100000000000000");
        vector128.append(num128);
        encoded128.append(encoded);
    }
    {
        num128.parts[0] = 0x00001000;
        num128.parts[1] = 0xdeadbeef;
        encoded = QByteArray::fromHex("0010000000000000efbeadde00000000");
        vector128.append(num128);
        encoded128.append(encoded);
    }
    {
        num128.parts[0] = 0x123456789abcdef0ull;
        num128.parts[1] = 0xdeadbeeff0011234ull;
        encoded = QByteArray::fromHex("f0debc9a78563412341201f0efbeadde");
        vector128.append(num128);
        encoded128.append(encoded);
    }

    for (int i = 0; i < vector128.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << vector128.at(i);
        QCOMPARE(device.data().toHex(), encoded128.at(i).toHex());
    }

    for (int i = 0; i < vector128.count(); ++i) {
        QBuffer device;
        device.setData(encoded128.at(i));
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

        TLNumber128 value;

        stream >> value;

        QCOMPARE(value, vector128.at(i));
    }
}

void tst_CTelegramStream::tlDcOptionDeserialization()
{
    QByteArray dcOptionsData;
    CTelegramStream inputStream(&dcOptionsData, /* write */ true);
    TLVector<TLDcOption> optionsVector;

    TLDcOption opt1;
    opt1.flags = 0;
    opt1.id = 2;
    opt1.ipAddress = QStringLiteral("1.2.3.4");
    opt1.port = 80;
    TLDcOption opt2;
    opt2.flags = 0;
    opt2.id = 3;
    opt2.ipAddress = QStringLiteral("2.3.4.5");
    opt2.port = 180;
    TLDcOption opt3;
    opt3.flags = 0;
    opt3.id = 4;
    opt3.ipAddress = QStringLiteral("3.4.5.6");
    opt3.port = 443;
    optionsVector << opt1 << opt2 << opt3;
    inputStream << optionsVector;

    CTelegramStream stream(dcOptionsData);
    TLVector<TLDcOption> readOptionsVector;
    stream >> readOptionsVector;

    QCOMPARE(readOptionsVector.size(), 3);
    QCOMPARE(readOptionsVector.at(0).ipAddress, opt1.ipAddress);
    QCOMPARE(readOptionsVector.at(1).ipAddress, opt2.ipAddress);
    QCOMPARE(readOptionsVector.at(2).ipAddress, opt3.ipAddress);

    QCOMPARE(readOptionsVector.at(0).flags, opt1.flags);
    QCOMPARE(readOptionsVector.at(0).port, opt1.port);
    QCOMPARE(readOptionsVector.at(1).id, opt2.id);
    QCOMPARE(readOptionsVector.at(2).id, opt3.id);

    QVERIFY(readOptionsVector.isValid());
}

void tst_CTelegramStream::readError()
{
    {
        static const char input[8] = { char(6), 't', 'e', 's', 't', '1', 'a', 0 };
        static const QByteArray data(input, sizeof(input));

        CTelegramStream stream(data);

        QVERIFY2(!stream.error(), "Unexpected error (there was been no read operation, so nothing can cause an error).");

        QString result;
        stream >> result;

        QCOMPARE(result, QLatin1String("test1a"));
        QVERIFY2(!stream.error(), "Stream is at the end of input, but without read it should be not an error yet.");

        // nothing to read
        stream >> result;
        QVERIFY2(stream.error(), "Read after the end should be an error.");
    }

    {
        static const char input[5] = { char(0xcc), char(0xbb), char(0xaa), char(0x00), char(0x20) };
        static const QByteArray data(input, sizeof(input));

        CTelegramStream stream(data);

        QVERIFY(!stream.error());

        quint32 result;
        stream >> result;

        QCOMPARE(result, quint32(0xaabbcc));
        QVERIFY2(!stream.error(), "Stream is at the end of input, but without read it should be not a error yet.");

        stream >> result;
        QVERIFY2(stream.error(), "Partial read, error should be set.");
    }

}

QTEST_APPLESS_MAIN(tst_CTelegramStream)

#include "tst_CTelegramStream.moc"
