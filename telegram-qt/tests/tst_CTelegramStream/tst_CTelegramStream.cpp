/*
   Copyright (C) 2015 Alexandr Akulich <akulichalexander@gmail.com>

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
    QByteArray serializedValue;
    STestData(QVariant v, QByteArray e) : value(v), serializedValue(e) { }
};

class tst_CTelegramStream : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramStream(QObject *parent = 0);

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

        QCOMPARE(device.data(), data.at(i).serializedValue);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedValue);
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

        if ((data.at(i).serializedValue.length() > 10) && (device.data() != data.at(i).serializedValue)) {
            qDebug() << QString("Actual (%1 bytes):").arg(device.data().length()) << device.data().toHex();
            qDebug() << QString("Expected (%1 bytes):").arg(data.at(i).serializedValue.length()) << data.at(i).serializedValue.toHex();
        }

        QCOMPARE(device.data(), data.at(i).serializedValue);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedValue);
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

    QString stringToTest1 = QLatin1String("Some really pretty long string to be serialized. "
                                         "Start to speek something wise and sage. Abadfa dfa uzxcviuwekrhalflkjhzvzxciuvyoiuwehrkblabla-asdfasdf"
                                         "qwrq25!@!@(#*&!$@%@!()#*&@#($)&*)(!@*&#)(!*@&#()!@*&$%!*@&$&^!%$&*#@%$&*%^@#$&%@#$@#*$&^@#*(&^@#%*&^!F"
                                         "132465798+760++-*/*/651321///???asd0f98`0978jhkjhzxcv....end"); // Lenght: 313

    const int len = 313;
    QByteArray serialized1(1, char(0xfe));
    serialized1.append(char(len & 0xff));
    serialized1.append(char((len & 0xff00) >> 8));
    serialized1.append(char((len & 0xff0000) >> 16));
    serialized1.append(stringToTest1.toUtf8());

    int extraNulls = 4 - (len & 3);

    for (int i = 0; i < extraNulls; ++i)
        serialized1.append(char(0));

    data.append(STestData(stringToTest1, serialized1));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        QVERIFY2(!(device.data().length() % 4), "Results buffer is not padded (total length is not divisible by 4)");
        QVERIFY2((device.data().length() >= len + 4), "Results buffer size for long string should be at least stringLength + 4");
        QVERIFY2((device.data().length() <= len + 4 + 3), "Results buffer size for long string should never be more, than stringLength + 4 + 3");

        QCOMPARE(device.data(), data.at(i).serializedValue);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedValue);
        device.open(QBuffer::ReadOnly);

        CTelegramStream stream(&device);

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

        QCOMPARE(device.data(), data.at(i).serializedValue);
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.setData(data.at(i).serializedValue);
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

    const QByteArray encoded = QByteArray::fromHex("a1cf7230");

    {
        CTelegramStream stream(encoded);

        stream >> vector;
        QCOMPARE(quint32(vector.tlType), quint32(TLValue::GzipPacked));
    }
}

void tst_CTelegramStream::tlNumbersSerialization()
{
    QVector<TLNumber128> vector128;
    QVector<QByteArray> encoded128;

    TLNumber128 num128;
    QByteArray encoded;

    num128.parts[0] = 1;
    num128.parts[1] = 0;
    encoded = QByteArray::fromHex("01000000000000000000000000000000");
    vector128.append(num128);
    encoded128.append(encoded);
    num128.parts[0] = 0;
    num128.parts[1] = 1;
    encoded = QByteArray::fromHex("00000000000000000100000000000000");
    vector128.append(num128);
    encoded128.append(encoded);
    num128.parts[0] = 0x00001000;
    num128.parts[1] = 0xdeadbeef;
    encoded = QByteArray::fromHex("0010000000000000efbeadde00000000");
    vector128.append(num128);
    encoded128.append(encoded);

    for (int i = 0; i < vector128.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::WriteOnly);

        CTelegramStream stream(&device);

        stream << vector128.at(i);
        QCOMPARE(device.data(), encoded128.at(i));
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
    unsigned char dcOptions[208] = {
        0x15, 0xc4, 0xb5, 0x1c, 0x06, 0x00, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0d, 0x31, 0x37, 0x33,
        0x2e, 0x32, 0x34, 0x30, 0x2e, 0x35, 0x2e, 0x32,
        0x35, 0x33, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0e, 0x31, 0x34, 0x39,
        0x2e, 0x31, 0x35, 0x34, 0x2e, 0x31, 0x36, 0x37,
        0x2e, 0x34, 0x30, 0x00, 0xbb, 0x01, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0d, 0x31, 0x37, 0x34,
        0x2e, 0x31, 0x34, 0x30, 0x2e, 0x31, 0x34, 0x32,
        0x2e, 0x35, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0d, 0x31, 0x37, 0x33,
        0x2e, 0x32, 0x34, 0x30, 0x2e, 0x35, 0x2e, 0x32,
        0x35, 0x33, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0e, 0x31, 0x34, 0x39,
        0x2e, 0x31, 0x35, 0x34, 0x2e, 0x31, 0x36, 0x37,
        0x2e, 0x34, 0x30, 0x00, 0x58, 0x00, 0x00, 0x00,
        0x3c, 0xa4, 0xc2, 0x2e, 0x03, 0x00, 0x00, 0x00,
        0x09, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x68, 0x6f,
        0x73, 0x74, 0x00, 0x00, 0x0d, 0x31, 0x37, 0x34,
        0x2e, 0x31, 0x34, 0x30, 0x2e, 0x31, 0x34, 0x32,
        0x2e, 0x35, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
    };

    QByteArray dcOptionsData;
    dcOptionsData.append((char *) dcOptions, 208);

    QBuffer device;
    device.setData(dcOptionsData);
    device.open(QBuffer::ReadOnly);

    CTelegramStream stream(&device);

    TLVector<TLDcOption> optionsVector;

    stream >> optionsVector;

    QCOMPARE(optionsVector.size(), 6);
    QCOMPARE(optionsVector.at(0).ipAddress, QString("173.240.5.253"));
    QCOMPARE(optionsVector.at(1).ipAddress, QString("149.154.167.40"));
    QCOMPARE(optionsVector.at(3).ipAddress, QString("173.240.5.253"));

    QCOMPARE(optionsVector.at(0).port, quint32(25));

    QCOMPARE(optionsVector.at(5).id       , quint32(3));
    QCOMPARE(optionsVector.at(5).hostname , QString("localhost"));
    QCOMPARE(optionsVector.at(5).ipAddress, QString("174.140.142.5"));
    QCOMPARE(optionsVector.at(5).port     , quint32(80));
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

QTEST_MAIN(tst_CTelegramStream)

#include "tst_CTelegramStream.moc"
