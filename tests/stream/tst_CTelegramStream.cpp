#include <QObject>

#include "CTelegramStream.hpp"

#include <QBuffer>
#include <QTest>
#include <QDebug>

struct STestData {
    QVariant value;
    QByteArray expected;
    STestData(QVariant v, QByteArray e) : value(v), expected(e) { }
};

class tst_CTelegramStream : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramStream(QObject *parent = 0);

private slots:
    void writeStringTestLimit();
    void writeShortString();
    void writeLongString();
    void writeInt();

};

tst_CTelegramStream::tst_CTelegramStream(QObject *parent) :
    QObject(parent)
{
}

void tst_CTelegramStream::writeShortString()
{
    QList<STestData> data;

    const char testExpectedChars1[8] = { char(4), 't', 'e', 's', 't', 0, 0, 0 };
    const char testExpectedChars2[8] = { char(5), 't', 'e', 's', 't', '5', 0, 0 };
    const char testExpectedChars3[8] = { char(6), 't', 'e', 's', 't', '6', '6', 0 };
    const char testExpectedChars4[8] = { char(7), '7', 's', 'e', 'v', 'e', 'n', '7' };

    data.append(STestData(QLatin1String("test"), QByteArray(testExpectedChars1, sizeof(testExpectedChars1))));
    data.append(STestData(QLatin1String("test5"), QByteArray(testExpectedChars2, sizeof(testExpectedChars2))));
    data.append(STestData(QLatin1String("test66"), QByteArray(testExpectedChars3, sizeof(testExpectedChars3))));
    data.append(STestData(QLatin1String("7seven7"), QByteArray(testExpectedChars4, sizeof(testExpectedChars4))));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::ReadWrite);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        QCOMPARE(device.data(), data.at(i).expected);
    }
}

void tst_CTelegramStream::writeStringTestLimit()
{
    QList<STestData> data;

    QString stringToTest;
    QByteArray expected;

    for (int i = 0; i < 5; ++i) {
        stringToTest = QString(i, QChar('a'));
        expected = QByteArray(i, char('a'));
        expected.prepend(char(i));
        if (expected.length() % 4)
            expected.append(QByteArray(4 - expected.length() % 4, char(0)));

        data.append(STestData(stringToTest, expected));
    }

    stringToTest = QString(253, QChar::fromLatin1(char(0x70)));
    expected = QByteArray(253, char(0x70));
    expected.prepend(char(253));
    expected.append(char(0));
    expected.append(char(0));

    data.append(STestData(stringToTest, expected));

    stringToTest = QString(254, QChar::fromLatin1(char(0x71)));
    expected = QByteArray(254, char(0x71));

    expected.prepend(char(0)); // LengthBig
    expected.prepend(char(0)); // LengthMiddle
    expected.prepend(char(254)); // LengthLittle

    expected.prepend(char(254)); // Long-string marker

    expected.append(char(0)); // Padding1
    expected.append(char(0)); // Padding2

    data.append(STestData(stringToTest, expected));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::ReadWrite);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        if ((data.at(i).expected.length() > 10) && (device.data() != data.at(i).expected)) {
            qDebug() << QString("Actual (%1 bytes):").arg(device.data().length()) << device.data().toHex();
            qDebug() << QString("Expected (%1 bytes):").arg(data.at(i).expected.length()) << data.at(i).expected.toHex();
        }

        QCOMPARE(device.data(), data.at(i).expected);
    }
}

void tst_CTelegramStream::writeLongString()
{
    QList<STestData> data;

    QString stringToTest1 = QLatin1String("Some really pretty long string to be serialized. "
                                         "Start to speek something wise and sage. Abadfa dfa uzxcviuwekrhalflkjhzvzxciuvyoiuwehrkblabla-asdfasdf"
                                         "qwrq25!@!@(#*&!$@%@!()#*&@#($)&*)(!@*&#)(!*@&#()!@*&$%!*@&$&^!%$&*#@%$&*%^@#$&%@#$@#*$&^@#*(&^@#%*&^!F"
                                         "132465798+760++-*/*/651321///???asd0f98`0978jhkjhzxcv....end"); // Lenght: 313

    const int len = 313;
    QByteArray expected1(1, char(0xfe));
    expected1.append(char(len & 0xff));
    expected1.append(char((len & 0xff00) >> 8));
    expected1.append(char((len & 0xff0000) >> 16));
    expected1.append(stringToTest1.toUtf8());

    int extraNulls = 4 - (len & 3);

    for (int i = 0; i < extraNulls; ++i)
        expected1.append(char(0));

    data.append(STestData(stringToTest1, expected1));

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::ReadWrite);

        CTelegramStream stream(&device);

        stream << data.at(i).value.toString();

        QVERIFY2(!(device.data().length() % 4), "Results buffer is not padded (total length is not divisible by 4)");
        QVERIFY2((device.data().length() >= len + 4), "Results buffer size for long string should be at least stringLength + 4");
        QVERIFY2((device.data().length() <= len + 4 + 3), "Results buffer size for long string should never be more, than stringLength + 4 + 3");

        QCOMPARE(device.data(), data.at(i).expected);
    }
}

void tst_CTelegramStream::writeInt()
{
    QList<STestData> data;

    {
        QByteArray testExpected;
        quint32 values[5] = { 0x01, 0xff, 0x00, 0xaabbcc, 0xdeadbeef };
        const char expected1[4] = { char(values[0]), 0, 0, 0 };
        const char expected2[4] = { char(values[1]), 0, 0, 0 };
        const char expected3[4] = { char(values[2]), 0, 0, 0 };
        const char expected4[4] = { char(0xcc), char(0xbb), char(0xaa), char(0x00) };
        const char expected5[4] = { char(0xef), char(0xbe), char(0xad), char(0xde) };

        testExpected.append(expected1, 4);
        testExpected.append(expected2, 4);
        testExpected.append(expected3, 4);
        testExpected.append(expected4, 4);
        testExpected.append(expected5, 5);

        for (int i = 0; i < 5; ++i)
            data.append(STestData(values[i], testExpected.mid(i * 4, 4)));
    }

    for (int i = 0; i < data.count(); ++i) {
        QBuffer device;
        device.open(QBuffer::ReadWrite);

        CTelegramStream stream(&device);

        stream << data.at(i).value.value<quint32>();

        QCOMPARE(device.data(), data.at(i).expected);
    }
}

QTEST_MAIN(tst_CTelegramStream)

#include "tst_CTelegramStream.moc"
