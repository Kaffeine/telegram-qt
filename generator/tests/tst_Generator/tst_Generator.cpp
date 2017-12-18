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

const QStringList c_sourcesInputMediaDeps =
{
    QStringLiteral("inputPhotoEmpty = InputPhoto;"),
    QStringLiteral("inputFileEmpty = InputFile;"),
    QStringLiteral("inputVideoEmpty = InputVideo;"),
    QStringLiteral("inputAudioEmpty = InputAudio;"),
    QStringLiteral("inputDocumentEmpty = InputDocument;"),
    QStringLiteral("documentAttributeEmpty = DocumentAttribute;"),
};

const QStringList c_sourcesInputMedia =
{
    QStringLiteral("inputMediaEmpty#9664f57f = InputMedia;"),
    QStringLiteral("inputMediaUploadedPhoto#f7aff1c0 file:InputFile caption:string = InputMedia;"),
    QStringLiteral("inputMediaPhoto#e9bfb4f3 id:InputPhoto caption:string = InputMedia;"),
    QStringLiteral("inputMediaContact#a6e45987 phone_number:string first_name:string last_name:string = InputMedia;"),
    QStringLiteral("inputMediaUploadedVideo#82713fdf file:InputFile duration:int w:int h:int mime_type:string caption:string = InputMedia;"),
    QStringLiteral("inputMediaUploadedThumbVideo#7780ddf9 file:InputFile thumb:InputFile duration:int w:int h:int mime_type:string caption:string = InputMedia;"),
    QStringLiteral("inputMediaVideo#936a4ebd id:InputVideo caption:string = InputMedia;"),
    QStringLiteral("inputMediaUploadedAudio#4e498cab file:InputFile duration:int mime_type:string = InputMedia;"),
    QStringLiteral("inputMediaAudio#89938781 id:InputAudio = InputMedia;"),
    QStringLiteral("inputMediaUploadedDocument#1d89306d file:InputFile mime_type:string attributes:Vector<DocumentAttribute> caption:string = InputMedia;"),
    QStringLiteral("inputMediaUploadedThumbDocument#ad613491 file:InputFile thumb:InputFile mime_type:string attributes:Vector<DocumentAttribute> caption:string = InputMedia;"),
    QStringLiteral("inputMediaDocument#1a77f29c id:InputDocument caption:string = InputMedia;"),
};

class tst_Generator : public QObject
{
    Q_OBJECT
public:
    explicit tst_Generator(QObject *parent = nullptr);

    TLType getSolvedType(const Generator &generator, const QString &typeName) const;

private slots:
    void checkRemoveWord_data();
    void checkRemoveWord();
    void checkTypeWithMemberConflicts();
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

void tst_Generator::checkTypeWithMemberConflicts()
{
    const QStringList sources = c_sourcesInputMediaDeps + c_sourcesInputMedia;
    const QString generatedTypeName = Generator::parseLine(c_sourcesInputMedia.first()).typeName;
    const QByteArray textData = generateTextSpec(sources);
    Generator generator;
    QVERIFY(generator.loadFromText(textData));
    QVERIFY(generator.resolveTypes());
    QVERIFY(!generator.solvedTypes().isEmpty());
    const TLType solvedType = getSolvedType(generator, generatedTypeName);
    QVERIFY(!solvedType.name.isEmpty());
    const QStringList structMembers = Generator::generateTLTypeMembers(solvedType);
    static const QStringList checkList = {
        QStringLiteral("TLInputFile thumb;"),
        QStringLiteral("TLInputVideo idInputVideo;"),
        QStringLiteral("TLInputAudio idInputAudio;"),
        QStringLiteral("TLVector<TLDocumentAttribute> attributes;"),
    };
    for (const QString &mustHaveMember : checkList) {
        if (!structMembers.contains(mustHaveMember)) {
            // qDebug().noquote() << structMembers.join(QLatin1Char('\n'));
            QString message = QStringLiteral("The member \"%1\" is missing in the generated struct of the type %2.").arg(mustHaveMember, generatedTypeName);
            QFAIL(message.toUtf8().constData());
        }
    }
}

QTEST_APPLESS_MAIN(tst_Generator)

#include "tst_Generator.moc"
