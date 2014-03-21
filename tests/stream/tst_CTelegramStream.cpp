/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

QTEST_MAIN(tst_CTelegramStream)

#include "tst_CTelegramStream.moc"
