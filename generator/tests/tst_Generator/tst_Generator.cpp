#include <QObject>
#include <QTest>
#include <QDebug>

#include "Generator.hpp"

class tst_Generator : public QObject
{
    Q_OBJECT
public:
    explicit tst_Generator(QObject *parent = nullptr);
private slots:
    void checkRemoveWord_data();
    void checkRemoveWord();
};

tst_Generator::tst_Generator(QObject *parent) :
    QObject(parent)
{
}

void tst_Generator::checkRemoveWord_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("output");
    QTest::addColumn<QString>("word");

    QTest::newRow("No word in the input")
            << "idInputVideo"
            << "idInputVideo"
            << "audio";
    QTest::newRow("Word in the end (different case)")
            << "idInputVideo"
            << "idInput"
            << "video";
    QTest::newRow("Word in the end (same case)")
            << "idInputVideo"
            << "idInput"
            << "Video";
    QTest::newRow("Word in the middle (different case)")
            << "idInputVideo"
            << "idVideo"
            << "input";
    QTest::newRow("Word in the middle (same case)")
            << "idInputVideo"
            << "idVideo"
            << "Input";
    QTest::newRow("Word in the beginning (different case)")
            << "idInputVideo"
            << "inputVideo"
            << "Id";
    QTest::newRow("Word in the beginning (same case)")
            << "idInputVideo"
            << "inputVideo"
            << "id";
}

void tst_Generator::checkRemoveWord()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    QFETCH(QString, word);
    QCOMPARE(Generator::removeWord(input, word), output);
}

QTEST_APPLESS_MAIN(tst_Generator)

#include "tst_Generator.moc"
