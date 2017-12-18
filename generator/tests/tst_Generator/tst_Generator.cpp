#include <QObject>
#include <QTest>
#include <QDebug>

#include "Generator.hpp"

const QString c_typesSection = QStringLiteral("---types---");
const QString c_functionsSection = QStringLiteral("---functions---");

static QByteArray generateTextSpec(const QStringList &types, const QStringList &functions = {})
{
    QByteArray result;
    if (!types.isEmpty()) {
        const QString textData = c_typesSection + QLatin1Char('\n') + types.join(QLatin1Char('\n')) + QLatin1Char('\n');
        result += textData.toLocal8Bit();
    }
    if (!functions.isEmpty()) {
        const QString textData = c_functionsSection + QLatin1Char('\n') + functions.join(QLatin1Char('\n')) + QLatin1Char('\n');
        result += textData.toLocal8Bit();
    }
    return result;
}

class tst_Generator : public QObject
{
    Q_OBJECT
public:
    explicit tst_Generator(QObject *parent = nullptr);

    TLType getSolvedType(const Generator &generator, const QString &typeName) const;

private slots:
    void checkRemoveWord_data();
    void checkRemoveWord();
};

tst_Generator::tst_Generator(QObject *parent) :
    QObject(parent)
{
}

TLType tst_Generator::getSolvedType(const Generator &generator, const QString &typeName) const
{
    const QString tName = Generator::formatType(typeName);
    for (const TLType solved : generator.solvedTypes()) {
        if (solved.name == tName) {
            return solved;
        }
    }
    return TLType();
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
