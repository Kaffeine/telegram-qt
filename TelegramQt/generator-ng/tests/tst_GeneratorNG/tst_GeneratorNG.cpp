#include <QObject>
#include <QTest>
#include <QDebug>

#include "GeneratorNG.hpp"

class tst_GeneratorNG : public QObject
{
    Q_OBJECT
public:
    explicit tst_GeneratorNG(QObject *parent = nullptr);
private slots:
    void checkRemoveWord_data();
    void checkRemoveWord();
};

tst_GeneratorNG::tst_GeneratorNG(QObject *parent) :
    QObject(parent)
{
}

void tst_GeneratorNG::checkRemoveWord_data()
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

void tst_GeneratorNG::checkRemoveWord()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    QFETCH(QString, word);
    QCOMPARE(GeneratorNG::removeWord(input, word), output);
}

QTEST_APPLESS_MAIN(tst_GeneratorNG)

#include "tst_GeneratorNG.moc"
