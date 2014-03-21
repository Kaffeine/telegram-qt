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

QTEST_MAIN(tst_CTelegramCore)

#include "tst_CTelegramCore.moc"
