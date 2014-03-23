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

#include "CTelegramCore.hpp"
#include "CTcpTransport.hpp"

#include <QTest>
#include <QDebug>

#include <QDateTime>

class tst_CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit tst_CTelegramCore(QObject *parent = 0);

private slots:
    void testTimestampAlwaysGrow();
    void testClientTimestampNeverOdd();
    void testTimestampConversion();
    void testPQAuthRequest();

};

tst_CTelegramCore::tst_CTelegramCore(QObject *parent) :
    QObject(parent)
{
}

void tst_CTelegramCore::testTimestampAlwaysGrow()
{
    quint64 time = 1395335796550;

    quint64 retTime = 0;
    for (int i = 0; i < 2000; ++i) {
        if (retTime >= CTelegramCore::formatClientTimeStamp(time + i)) {
            QCOMPARE(retTime, CTelegramCore::formatClientTimeStamp(time + i));
            break;
        }

        retTime = CTelegramCore::formatClientTimeStamp(time + i);
    }
}

void tst_CTelegramCore::testClientTimestampNeverOdd()
{
    quint64 time = 1395335796550;

    for (int i = 0; i < 2000; ++i) {
        if (CTelegramCore::formatClientTimeStamp(time + i) & 3) {
            QVERIFY(!(CTelegramCore::formatClientTimeStamp(time + i) & 3));
            break;
        }
    }
}

void tst_CTelegramCore::testTimestampConversion()
{
    quint64 time = 1395335796550;
    quint64 ts = CTelegramCore::formatTimeStamp(time);
    QCOMPARE(CTelegramCore::timeStampToMSecsSinceEpoch(ts), time);

    ts = 0x532ea31d36cecc00;
    time = 1395565341214;

    QCOMPARE(CTelegramCore::timeStampToMSecsSinceEpoch(ts), time);
}

void tst_CTelegramCore::testPQAuthRequest()
{
    CTelegramTransport *transport = new CTcpTransport();
    CTelegramCore core;
    core.setTransport(transport);
    core.requestPqAuthorization();

    QByteArray encoded = transport->lastPackage();

    QVERIFY2(encoded.at(0) == char(0xef), "Abridged version marker");
    QCOMPARE(encoded.at(1), char(0x0a)); // Package length information should be equal to 0x0a (real size / 4)
    QCOMPARE(encoded.length(), 0x0a * 4 + 2); // Package size should be equal to 0x0a * 4 + 2 (2 is size of marker+size_info)
    QVERIFY2(encoded.mid(2, 8) == QByteArray(8, char(0)), "In this method auth id should be equal zero");

    // TODO: check timestamp
//    qDebug() << "Timestamp:" << encoded.mid(10, 8).toHex();

    QByteArray messageBodyLength(4, char(0));
    messageBodyLength[0] = 0x14;

    QCOMPARE(encoded.mid(18, 4), messageBodyLength); // Expected payload length is 20 bytes

    QByteArray reqPqRaw;
    reqPqRaw.resize(4);
    reqPqRaw[0] = 0x78;
    reqPqRaw[1] = 0x97;
    reqPqRaw[2] = 0x46;
    reqPqRaw[3] = 0x60;

    QCOMPARE(encoded.mid(22, 4), reqPqRaw); // Expected payload length is 20 bytes
}

QTEST_MAIN(tst_CTelegramCore)

#include "tst_CTelegramCore.moc"
