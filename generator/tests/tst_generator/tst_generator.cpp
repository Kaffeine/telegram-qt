#include <QObject>
#include <QTest>
#include <QDebug>

#include "../Generator.hpp"

const QByteArray c_typesSection = QByteArrayLiteral("---types---");
const QByteArray c_functionsSection = QByteArrayLiteral("---functions---");

static QByteArray generateTextSpec(const QStringList &types, const QStringList &functions = {})
{
    QByteArray result;
    if (!types.isEmpty()) {
        const QString textData = QLatin1Char('\n') + types.join(QLatin1Char('\n')) + QLatin1Char('\n');
        result += c_typesSection;
        result += textData.toLocal8Bit();
    }
    if (!functions.isEmpty()) {
        const QString textData = QLatin1Char('\n') + functions.join(QLatin1Char('\n')) + QLatin1Char('\n');
        result += c_functionsSection;
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
    QStringLiteral("inputMediaUploadedPhoto#2f37e231 flags:# file:InputFile caption:string stickers:flags.0?Vector<InputDocument> ttl_seconds:flags.1?int = InputMedia;"),
    QStringLiteral("inputMediaPhotoExternal#922aec1 flags:# url:string caption:string ttl_seconds:flags.0?int = InputMedia;"),
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

const QStringList c_inputMediaFlags =
{
    QStringLiteral("TtlSeconds0 = 1 << 0,"),
    QStringLiteral("Stickers = 1 << 0,"),
    QStringLiteral("TtlSeconds1 = 1 << 1,"),
};

const QStringList c_sourcesRichText =
{
    QStringLiteral("textEmpty#dc3d824f = RichText;"),
    QStringLiteral("textPlain#744694e0 text:string = RichText;"),
    QStringLiteral("textBold#6724abc4 text:RichText = RichText;"),
    QStringLiteral("textItalic#d912a59c text:RichText = RichText;"),
    QStringLiteral("textUnderline#c12622c4 text:RichText = RichText;"),
    QStringLiteral("textStrike#9bf8bb95 text:RichText = RichText;"),
    QStringLiteral("textFixed#6c3f19b9 text:RichText = RichText;"),
    QStringLiteral("textUrl#3c2884c1 text:RichText url:string webpage_id:long = RichText;"),
    QStringLiteral("textEmail#de5a0dd6 text:RichText email:string = RichText;"),
    QStringLiteral("textConcat#7e6260d7 texts:Vector<RichText> = RichText;"),
};

const QStringList c_sourcesPageBlock =
{
    QStringLiteral("pageBlockUnsupported#13567e8a = PageBlock;"),
    QStringLiteral("pageBlockTitle#70abc3fd text:RichText = PageBlock;"),
    QStringLiteral("pageBlockSubtitle#8ffa9a1f text:RichText = PageBlock;"),
    QStringLiteral("pageBlockList#3a58c7f4 ordered:Bool items:Vector<RichText> = PageBlock;"),
    QStringLiteral("pageBlockEmbedPost#292c7be9 url:string webpage_id:long author_photo_id:long author:string date:int blocks:Vector<PageBlock> caption:RichText = PageBlock;"),
    QStringLiteral("pageBlockSlideshow#130c8963 items:Vector<PageBlock> caption:RichText = PageBlock;"),
    QStringLiteral("pageBlockPhoto#e9c69982 photo_id:long caption:RichText = PageBlock;"),
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
    void checkFormatName_data();
    void checkFormatName();
    void checkTypeWithMemberConflicts();
    void typeWithMemberFlagsConflict();
    void recursiveTypeMembers();
    void doubleRecursiveTypeMembers();
    void predicateForCrc_data();
    void predicateForCrc();
    void checkStreamReadOperator();
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

void tst_Generator::checkFormatName_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("output");
    QTest::addColumn<Generator::FormatOptions>("options");

    QTest::newRow("UpperCaseFirstLetter")
            << "inputVideo"
            << "InputVideo"
            << Generator::FormatOptions(Generator::FormatOption::UpperCaseFirstLetter);

    QTest::newRow("LowerCaseFirstLetter")
            << "InputVideo"
            << "inputVideo"
            << Generator::FormatOptions(Generator::FormatOption::LowerCaseFirstLetter);

    QTest::newRow("SkipFirstWord")
            << "AuthCheckPassword"
            << "CheckPassword"
            << Generator::FormatOptions(Generator::FormatOption::SkipFirstWord);

    QTest::newRow("RemoveSeparators")
            << "auth_checkPassword"
            << "authCheckPassword"
            << Generator::FormatOptions(Generator::FormatOption::RemoveSeparators);

    QTest::newRow("SkipTl")
            << "TLInputPeer"
            << "InputPeer"
            << Generator::FormatOptions(Generator::FormatOption::SkipTl);
}

void tst_Generator::checkFormatName()
{
    QFETCH(QString, input);
    QFETCH(QString, output);
    QFETCH(Generator::FormatOptions, options);
    QCOMPARE(Generator::formatName(input, options), output);
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
        QStringLiteral("TLInputVideo inputVideoId;"),
        QStringLiteral("TLInputAudio inputAudioId;"),
        QStringLiteral("TLVector<TLDocumentAttribute> attributes;"),
    };
    for (const QString &mustHaveMember : checkList) {
        if (!structMembers.contains(mustHaveMember)) {
            qDebug().noquote() << "Generated members:";
            for (const QString &member : structMembers) {
                qDebug().noquote() << "    " << member;
            }
            QString message = QStringLiteral("The member \"%1\" is missing in the generated struct of the type %2.").arg(mustHaveMember, generatedTypeName);
            QFAIL(message.toUtf8().constData());
        }
    }
}

void tst_Generator::typeWithMemberFlagsConflict()
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
    const QStringList flags = Generator::generateTLTypeMemberFlags(solvedType);
    QCOMPARE(flags, c_inputMediaFlags);
}

void tst_Generator::recursiveTypeMembers()
{
    const QStringList sources = c_sourcesRichText;
    const QString generatedTypeName = Generator::parseLine(c_sourcesRichText.first()).typeName;
    const QByteArray textData = generateTextSpec(sources);
    Generator generator;
    QVERIFY(generator.loadFromText(textData));
    QMap<QString, TLType> types = generator.types();
    QCOMPARE(types.size(), 1);
    QVERIFY(generator.resolveTypes());
    QVERIFY(!generator.solvedTypes().isEmpty());
    const TLType solvedType = getSolvedType(generator, generatedTypeName);

    QVERIFY(!solvedType.name.isEmpty());
    const QStringList structMembers = Generator::generateTLTypeMembers(solvedType);
    static const QStringList checkList = {
        QStringLiteral("QString email;"),
        QStringLiteral("QString stringText;"),
        QStringLiteral("TLRichTextPtr richText;"),
        QStringLiteral("TLVector<TLRichText*> texts;"),
    };
    for (const QString &mustHaveMember : checkList) {
        if (!structMembers.contains(mustHaveMember)) {
            qDebug().noquote() << "Generated members:";
            for (const QString &member : structMembers) {
                qDebug().noquote() << "    " << member;
            }
            QString message = QStringLiteral("The member \"%1\" is missing in the generated struct of the type %2.").arg(mustHaveMember, generatedTypeName);
            QFAIL(message.toUtf8().constData());
        }
    }
}

void tst_Generator::doubleRecursiveTypeMembers()
{
    const QStringList sources = c_sourcesRichText + c_sourcesPageBlock;
    const QString generatedTypeName = Generator::parseLine(c_sourcesPageBlock.first()).typeName;
    const QByteArray textData = generateTextSpec(sources);
    Generator generator;
    QVERIFY(generator.loadFromText(textData));
    QMap<QString, TLType> types = generator.types();
    QVERIFY(!types.isEmpty());
    QVERIFY(generator.resolveTypes());
    QVERIFY(!generator.solvedTypes().isEmpty());
    const TLType solvedType = getSolvedType(generator, generatedTypeName);
    QVERIFY(!solvedType.name.isEmpty());
    const QStringList structMembers = Generator::generateTLTypeMembers(solvedType);
    static const QStringList checkList = {
        QStringLiteral("TLRichTextPtr text;"),
        QStringLiteral("TLVector<TLRichText*> richTextItemsVector;"),
        QStringLiteral("TLVector<TLPageBlock*> blocks;"),
        QStringLiteral("TLVector<TLPageBlock*> pageBlockItemsVector;"),
        QStringLiteral("TLRichTextPtr caption;"),
    };
    for (const QString &mustHaveMember : checkList) {
        if (!structMembers.contains(mustHaveMember)) {
            qDebug().noquote() << "Generated members:";
            for (const QString &member : structMembers) {
                qDebug().noquote() << "    " << member;
            }
            QString message = QStringLiteral("The member \"%1\" is missing in the generated struct of the type %2.").arg(mustHaveMember, generatedTypeName);
            QFAIL(message.toUtf8().constData());
        }
    }
}

void tst_Generator::predicateForCrc_data()
{
    QTest::addColumn<QByteArray>("input");
    QTest::addColumn<QByteArray>("output");

    QTest::addRow("Trivial") << QByteArrayLiteral("help.getConfig#c4f9186b = Config;")
                             << QByteArrayLiteral("help.getConfig = Config");

    QTest::addRow("Trivial") << QByteArrayLiteral("req_pq#60469778 nonce:int128 = ResPQ;")
                             << QByteArrayLiteral("req_pq nonce:int128 = ResPQ");

    QTest::addRow("With true flags") << QByteArrayLiteral("channels.createChannel#f4893d7f flags:#"
                                                          " broadcast:flags.0?true megagroup:flags.1?true"
                                                          " title:string about:string = Updates;")
                                     << QByteArrayLiteral("channels.createChannel flags:#"
                                                          " title:string about:string = Updates");

    QTest::addRow("With flags") << QByteArrayLiteral("updates.getDifference#25939651 flags:#"
                                                     " pts:int pts_total_limit:flags.0?int date:int"
                                                     " qts:int = updates.Difference;")
                                << QByteArrayLiteral("updates.getDifference flags:#"
                                                     " pts:int pts_total_limit:flags.0?int date:int"
                                                     " qts:int = updates.Difference");

    QTest::addRow("With vector") << QByteArrayLiteral("messages.getAllChats#eba80ff0"
                                                      " except_ids:Vector<int> = messages.Chats;")
                                 << QByteArrayLiteral("messages.getAllChats"
                                                      " except_ids:Vector int = messages.Chats");

    QTest::addRow("Vector") << QByteArrayLiteral("vector#1cb5c415 {t:Type} # [ t ] = Vector t;")
                            << QByteArrayLiteral("vector t:Type # [ t ] = Vector t");
}

void tst_Generator::predicateForCrc()
{
    QFETCH(QByteArray, input);
    QFETCH(QByteArray, output);
    QCOMPARE(Generator::getBarePredicate(input), output);
}

void tst_Generator::checkStreamReadOperator()
{
    QByteArray sources =
            "\n"
            "postAddress#1e8caaeb"
            " street_line1:string"
            " street_line2:string"
            " city:string state:string"
            " country_iso2:string"
            " post_code:string = PostAddress;"
            "\n"
            "paymentRequestedInfo#909c3f94 flags:#"
            " name:flags.0?string"
            " phone:flags.1?string"
            " email:flags.2?string"
            " shipping_address:flags.3?PostAddress"
            " = PaymentRequestedInfo;";

    QByteArray declarationsCode =
            "    Stream &operator>>(TLPostAddress &postAddressValue);\n"
            "    Stream &operator>>(TLPaymentRequestedInfo &paymentRequestedInfoValue);\n";

    QByteArray definitionsCode =
            "Stream &Stream::operator>>(TLPostAddress &postAddressValue)\n"
            "{\n"
            "    TLPostAddress result;\n"
            "\n"
            "    *this >> result.tlType;\n"
            "\n"
            "    switch (result.tlType) {\n"
            "    case TLValue::PostAddress:\n"
            "        *this >> result.streetLine1;\n"
            "        *this >> result.streetLine2;\n"
            "        *this >> result.city;\n"
            "        *this >> result.state;\n"
            "        *this >> result.countryIso2;\n"
            "        *this >> result.postCode;\n"
            "        break;\n"
            "    default:\n"
            "        break;\n"
            "    }\n"
            "\n"
            "    postAddressValue = result;\n"
            "\n"
            "    return *this;\n"
            "}\n"
            "\n"
            "Stream &Stream::operator>>(TLPaymentRequestedInfo &paymentRequestedInfoValue)\n"
            "{\n"
            "    TLPaymentRequestedInfo result;\n"
            "\n"
            "    *this >> result.tlType;\n"
            "\n"
            "    switch (result.tlType) {\n"
            "    case TLValue::PaymentRequestedInfo:\n"
            "        *this >> result.flags;\n"
            "        if (result.flags & TLPaymentRequestedInfo::Name) {\n"
            "            *this >> result.name;\n"
            "        }\n"
            "        if (result.flags & TLPaymentRequestedInfo::Phone) {\n"
            "            *this >> result.phone;\n"
            "        }\n"
            "        if (result.flags & TLPaymentRequestedInfo::Email) {\n"
            "            *this >> result.email;\n"
            "        }\n"
            "        if (result.flags & TLPaymentRequestedInfo::ShippingAddress) {\n"
            "            *this >> result.shippingAddress;\n"
            "        }\n"
            "        break;\n"
            "    default:\n"
            "        break;\n"
            "    }\n"
            "\n"
            "    paymentRequestedInfoValue = result;\n"
            "\n"
            "    return *this;\n"
            "}\n"
            "\n";

    const QByteArray textData = c_typesSection + sources;

    Generator generator;
    QVERIFY(generator.loadFromText(textData));
    QMap<QString, TLType> types = generator.types();
    QVERIFY(!types.isEmpty());
    QVERIFY(generator.resolveTypes());
    QVERIFY(!generator.solvedTypes().isEmpty());
    generator.generate();

    QCOMPARE(generator.codeStreamReadDeclarations.toLatin1(), declarationsCode);
    qWarning().noquote() << generator.codeStreamReadDefinitions;
    QCOMPARE(generator.codeStreamReadDefinitions.toLatin1(), definitionsCode);
}

QTEST_APPLESS_MAIN(tst_Generator)

#include "tst_generator.moc"
