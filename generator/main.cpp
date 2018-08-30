/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCommandLineParser>

#include <QJsonDocument>

#include "Generator.hpp"

enum StatusCode {
    NoError,
    InvalidAction,
    InvalidArgument,
    SchemaReadError,
    UnableToResolveTypes,
    NetworkError,
    ServerError,
    FileAccessError
};

enum SchemaFormat {
    JsonFormat,
    TextFormat,
};

static bool s_dryRun = false;
static bool s_dump = true;
static bool s_addSpecSources = false;

static const QByteArray c_textLayerMarker = QByteArrayLiteral("// LAYER ");

static QString s_inputDir;
static QString s_outputDir;
static QString s_author;

QString calcVarName(const QString &var)
{
    QStringList words = Generator::getWords(var);
    QString name;
    for (QString &namePart : words) {
        namePart = namePart.toUpper();
    }
    name = QStringLiteral("__VAR_") + Generator::joinLinesWithPrepend(words, QString(), QStringLiteral("_")) + QStringLiteral("_");
    return name;
}

QString readFile(const QString &fileName)
{
    QFile f(s_inputDir + fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << Q_FUNC_INFO << "Unable to open the file" << fileName;
        return QString();
    }
    return QString::fromUtf8(f.readAll());
}

bool writeFile(const QString &fileName, const QString &source)
{
    QFile f(s_inputDir + fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        qWarning() << Q_FUNC_INFO << "Unable to open the file" << fileName;
        return false;
    }
    f.write(source.toUtf8());
    return true;
}

QString readTemplateFile(const QString &templateName)
{
    return readFile(QStringLiteral("../generator/templates/") + templateName);
}

static const QString c_authorVar = calcVarName("AuthorName"); // __VAR_AUTHOR_NAME__
static const QString c_groupNameVar = calcVarName("GroupName"); // __VAR_GROUP_NAME__
static const QString c_groupNameSmallVar = calcVarName("GroupNameSmall"); // __VAR_GROUP_NAME_SMALL__
static const QString c_groupNameCapitalVar = calcVarName("GroupNameCapital"); // __VAR_GROUP_NAME_CAPITAL__

QString getLicenseText(const QString &author)
{
    static QString text;
    if (text.isEmpty()) {
        text = readTemplateFile(QStringLiteral("LICENSE.template"));


        text.replace(c_authorVar, author);
        if (!text.endsWith(QStringLiteral("\n\n"))) {
            text.append(QLatin1Char('\n'));
        }
    }
    return text;
}

/* Replacing helper */
QString getSectionContent(const QString &fileName, const QString &startMarker, const QString &endMarker, bool *winEol = nullptr)
{
    QFile fileToProcess(s_inputDir + fileName);

    if (!fileToProcess.open(QIODevice::ReadOnly))
        return QString();

    QString fileContent = fileToProcess.readAll();
    fileToProcess.close();

    bool winNewLines = fileContent.indexOf(QLatin1String("\r\n")) > 0;

    if (winNewLines) {
        fileContent.replace(QLatin1String("\r\n"), QLatin1String("\n"));
    }

    if (winEol) {
        *winEol = winNewLines;
    }

    int startPos = fileContent.indexOf(startMarker);
    int endPos   = fileContent.indexOf(endMarker);
    if (startPos >= 0) {
        if (endPos < 0) {
            printf("There is only start marker in the file %s. Error.\n", fileName.toLocal8Bit().constData());
            return QString();
        }

        endPos += endMarker.length();
    } else {
        return QString();
    }

    const QString previousContent = fileContent.mid(startPos, endPos - startPos);

    return previousContent;
}

QString getGeneratedContent(const QString &fileName, int spacing, const QString &marker, bool *winEol = nullptr)
{
    const QString space(spacing, QChar(' '));
    return getSectionContent(fileName,
                             QString("%1// Generated %2\n").arg(space).arg(marker),
                             QString("%1// End of generated %2\n").arg(space).arg(marker), winEol);
}

QString getPartiallyGeneratedContent(const QString &fileName, int spacing, const QString &marker, bool *winEol = nullptr)
{
    const QString space(spacing, QChar(' '));
    return getSectionContent(fileName,
                             QString("%1// Partially generated %2\n").arg(space).arg(marker),
                             QString("%1// End of partially generated %2\n").arg(space).arg(marker), winEol);
}

QString preprocessFile(const QString &fileName)
{
    if (s_dryRun || (s_inputDir == s_outputDir)) {
        return s_inputDir + fileName;
    }
    static QStringList processedFiles;
    if (!processedFiles.contains(fileName)) {
        processedFiles.append(fileName);
        const QString in = s_inputDir + fileName;
        const QString out = s_outputDir + fileName;
        if (QFileInfo::exists(out)) {
            if (!QFile::remove(out)) {
                qWarning() << Q_FUNC_INFO << "Unable to overwrite file" << out;
            }
        }
        if (!QFile::copy(in, out)) {
            qWarning() << Q_FUNC_INFO << "Unable to copy file" << fileName << "from" << s_inputDir << "to" << s_outputDir;
            return QString();
        }
    }
    return s_outputDir + fileName;
}

/* End of replacing helper */

void debugType(const TLType &type)
{
    qDebug() << type.name;
    foreach (const TLSubType &subType, type.subTypes) {
        qDebug() << "    " << subType.name;
        foreach (const TLParam &member, subType.members) {
            qDebug() << "        " << member.type() << member.getAlias();
        }
    }
}

StatusCode fetchJson(const QString &specFileName)
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkRequest req(QUrl(QLatin1String("https://core.telegram.org/schema/json")));
    QNetworkReply *reply = mgr.get(req);

    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        delete reply;
        return NetworkError;
    }

    QByteArray data = reply->readAll();
    delete reply;

    if (data.isEmpty()) {
        return ServerError;
    }

    QFile specsOutFile(specFileName);
    if (!specsOutFile.open(QIODevice::WriteOnly)) {
        return FileAccessError;
    }

    QJsonDocument document = QJsonDocument::fromJson(data);
    specsOutFile.write(document.toJson());
    specsOutFile.close();

    printf("Spec file successfully downloaded (and formatted).\n");
    return NoError;
}

StatusCode fetchText(const QString &url, QString *output)
{
    QEventLoop eventLoop;
    QNetworkAccessManager nam;
    QObject::connect(&nam, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkRequest req(QUrl::fromUserInput(url));
    QNetworkReply *reply = nam.get(req);

    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->error() << reply->errorString();
        delete reply;
        return NetworkError;
    }
    const QByteArray data = reply->readAll();
    delete reply;

    if (data.isEmpty()) {
        qWarning() << "The result is empty";
        return ServerError;
    }

    int layerIndex = data.indexOf(c_textLayerMarker);
    if (layerIndex < 0) {
        qWarning() << "No layer marker";
        return SchemaReadError;
    }
    bool ok;
    QByteArray mid = data.mid(layerIndex + c_textLayerMarker.length());
    mid = mid.trimmed();
    int layer = mid.toInt(&ok);
    if (!ok) {
        qWarning() << "No layer version in data" << mid;
        return SchemaReadError;
    }

    if (output->isEmpty()) {
        *output = QStringLiteral("scheme-%1.tl").arg(layer);
    }
    QFile specsOutFile(*output);
    if (!specsOutFile.open(QIODevice::WriteOnly)) {
        return FileAccessError;
    }
    specsOutFile.write(data);
    specsOutFile.close();

    printf("The spec file is successfully downloaded and saved as %s\n", output->toUtf8().constData());
    return NoError;
}

StatusCode format(const QString &specFileName)
{
    QFile specsFile(specFileName);
    if (!specsFile.open(QIODevice::ReadOnly)) {
        return FileAccessError;
    }

    QByteArray data = specsFile.readAll();

    specsFile.close();

    if (!specsFile.open(QIODevice::WriteOnly)) {
        return FileAccessError;
    }

    QJsonDocument document = QJsonDocument::fromJson(data);
    specsFile.write(document.toJson());
    specsFile.close();

    printf("Spec file successfully formatted.\n");
    return NoError;
}


/*! \class OutputFile
    \inmodule Generator
    \brief An object to buffer changes to a file

    The purpose of the object is to apply all changes to an in-memory buffer
    and write it to the file on the object destruction.

    The write does not happen if the previous content matches the new one, so
    this class also prevents file from unneeded timestamp changes.

    The loaded content is always in Unix EOL format, but writeback operation
    keeps the origin file EOLs.
    */
class OutputFile : public QObject
{
    Q_OBJECT
public:
    enum class EolFormat {
        Unix,
        Windows,
    };

    explicit OutputFile(const QString &fileName);
    explicit OutputFile(const char *fileName);
    ~OutputFile();

    bool hasContent() const { return !m_content.isEmpty(); }
    QString content() const { return m_content; }
    QString &contentRef() { return m_content; }

    void setContent(const QString &content)
    {
        m_content = content;
    }

    bool replaceParts(const char *marker, const QString &newContent, int spacing = 0);
    bool replace(const char *marker, const QString &newContent, int spacing = 0) { return replace(QString::fromUtf8(marker), newContent, spacing); }
    bool replace(const QString &marker, const QString &newContent, int spacing = 0);
    bool replace(const QString &startMarker, const QString &endMarker, QString newContent);

protected:
    QString m_fileName;
    QString m_content;
    EolFormat m_FileEolFormat = EolFormat::Unix;
};

OutputFile::OutputFile(const QString &fileName) :
    m_fileName(fileName)
{
    QFile fileToProcess(s_inputDir + m_fileName);
    if (!fileToProcess.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray fileContent = fileToProcess.readAll();
    if (fileContent.indexOf(QByteArrayLiteral("\r\n")) >= 0) {
        m_FileEolFormat = EolFormat::Windows;
    } else {
        m_FileEolFormat = EolFormat::Unix;
    }
    if (m_FileEolFormat == EolFormat::Windows) {
        fileContent.replace(QByteArrayLiteral("\r\n"), QByteArrayLiteral("\n"));
    }
    setContent(fileContent);
}

OutputFile::OutputFile(const char *fileName) :
    OutputFile(QString::fromLatin1(fileName))
{
}

OutputFile::~OutputFile()
{
    QFile fileToProcess(s_inputDir + m_fileName);
    QByteArray previousContent;
    if (fileToProcess.open(QIODevice::ReadOnly)) {
        previousContent = fileToProcess.readAll();
    }
    QByteArray fileContent = m_content.toUtf8();
    if (m_FileEolFormat == EolFormat::Windows) {
        fileContent.replace(QByteArrayLiteral("\n"), QByteArrayLiteral("\r\n"));
    }
    if (previousContent == fileContent) {
        printf("No changes in file %s\n", m_fileName.toUtf8().constData());
        return;
    }
    fileToProcess.close();
    fileToProcess.setFileName(s_outputDir + m_fileName);
    if (s_dryRun) {
        printf("Replacing is done (dry run).\n");
        return;
    }
    if (!fileToProcess.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        // emit error()
        return;
    }
    fileToProcess.write(fileContent);
    printf("Replacing is done.\n");
}

bool OutputFile::replaceParts(const char *marker, const QString &newContent, int spacing)
{
    const QString space(spacing, QChar(' '));
    if (!replace(QStringLiteral("%1// Partially generated %2\n").arg(space).arg(marker),
                 QStringLiteral("%1// End of partially generated %2\n").arg(space).arg(marker), newContent)) {
        printf("Can not update file %s with marker %s.\n", m_fileName.toLatin1().constData(), marker);
        return false;
    }
    return true;
}

bool OutputFile::replace(const QString &marker, const QString &newContent, int spacing)
{
    const QString space(spacing, QChar(' '));
    if (!replace(QString("%1// Generated %2\n").arg(space, marker),
                 QString("%1// End of generated %2\n").arg(space, marker), newContent)) {
        printf("Can not update file %s with marker %s.\n", m_fileName.toLatin1().constData(), marker.toUtf8().constData());
        return false;
    }
    return true;
}

bool OutputFile::replace(const QString &startMarker, const QString &endMarker, QString newContent)
{
    int startPos = m_content.indexOf(startMarker);
    int endPos   = m_content.indexOf(endMarker);

    if (startPos >= 0) {
        if (endPos < 0) {
            printf("There is only start marker in the file %s. Error.\n", m_fileName.toLocal8Bit().constData());
            return false;
        }
        endPos += endMarker.length();
    } else {
        printf("There is no start marker in the file %s. Error.\n", m_fileName.toLocal8Bit().constData());
        return false;
    }

    while (newContent.length() > 2) {
        const QChar &lastChar = newContent.at(newContent.length() - 1);
        const QChar &prevChar = newContent.at(newContent.length() - 2);
        if (lastChar == QLatin1Char('\n') && (prevChar == lastChar)) {
            newContent.chop(1);
        } else {
            break;
        }
    }

    const QString previousContent = m_content.mid(startPos, endPos - startPos);
    const bool changed = previousContent != startMarker + newContent + endMarker;

    if (s_dump) {
        const char *strChanged = "changed";
        const char *strNotChanged = "not changed";

        printf("File: \"%s\", Startmarker: \"%s\", Code (%s):\n%s\n", m_fileName.toLocal8Bit().constData(), startMarker.trimmed().toLocal8Bit().constData(),
               changed ? strChanged : strNotChanged,
               newContent.toLocal8Bit().constData());
    }
    if (!changed) {
        printf("Nothing to do: new and previous contents are exactly same.\n");
        return true;
    }
    m_content.remove(startPos, endPos - startPos);
    m_content.insert(startPos, startMarker + newContent + endMarker);
    return true;
}

struct FunctionGroup
{
    QString name1stCapital;
    QString nameSmall;
    QString nameCapital;
};

void preprocessContent(QString *content, const FunctionGroup &group)
{
    content->replace(c_groupNameVar, group.name1stCapital);
    content->replace(c_groupNameSmallVar, group.nameSmall);
    content->replace(c_groupNameCapitalVar, group.nameCapital);
}

StatusCode generate(SchemaFormat format, const QString &specFileName)
{
    QFile specsFile(specFileName);
    if (!specsFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open spec file" << specFileName << "in" << QDir().absolutePath();
        return InvalidArgument;
    }

    const QByteArray data = specsFile.readAll();

    if (data.isEmpty()) {
        qWarning() << "Unable to read spec file" << specFileName;
        return InvalidArgument;
    }

    specsFile.close();

    Generator generator;
    generator.setAddSpecSources(s_addSpecSources);

    bool success = true;

    switch (format) {
    case JsonFormat:
        success = generator.loadFromJson(data);
        break;
    case TextFormat:
        success = generator.loadFromText(data);
        break;
    }

    if (s_dump) {
        generator.dumpReadData();
    }

    if (generator.types().isEmpty()) {
        qWarning() << "There are no types in the schema";
        return SchemaReadError;
    }

    if (generator.functions().isEmpty()) {
        qWarning() << "There are no functions in the schema";
        return SchemaReadError;
    }

    if (!success) {
        qWarning() << "Unable to parse schema";
        return SchemaReadError;
    }

    if (!generator.resolveTypes()) {
        qWarning() << "Unable to resolve types";
        return UnableToResolveTypes;
    }

    if (s_dump) {
        generator.dumpSolvedTypes();
    }

    generator.existsStreamReadTemplateInstancing = getGeneratedContent(QStringLiteral("CTelegramStream.cpp"), 0, QLatin1String("vector read templates instancing"));
    generator.existsStreamWriteTemplateInstancing = getGeneratedContent(QStringLiteral("CTelegramStream.cpp"), 0, QLatin1String("vector write templates instancing"));
    generator.generate();

    {
        OutputFile fileValues("TLValues.hpp");
        fileValues.replace("TLValues", generator.codeOfTLValues, 8);
    }
    {
        OutputFile fileValues("TLTypes.hpp");
        fileValues.replace("TLTypes", generator.codeOfTLTypes);
    }

    {
        OutputFile fileTelegramStreamHeader("CTelegramStream.hpp");
        OutputFile fileTelegramStreamSource("CTelegramStream.cpp");
        OutputFile fileTelegramStreamExtraOperatorsHeader("CTelegramStreamExtraOperators.hpp");
        OutputFile fileTelegramStreamExtraOperatorsSource("CTelegramStreamExtraOperators.cpp");
        fileTelegramStreamHeader.replace("read operators", generator.codeStreamReadDeclarations, 4);
        fileTelegramStreamSource.replace("read operators implementation", generator.codeStreamReadDefinitions);
        fileTelegramStreamSource.replace("vector read templates instancing", generator.codeStreamReadTemplateInstancing);
        fileTelegramStreamHeader.replace("write operators", generator.codeStreamWriteDeclarations, 4);
        fileTelegramStreamSource.replace("write operators implementation", generator.codeStreamWriteDefinitions);
        fileTelegramStreamSource.replace("vector write templates instancing", generator.codeStreamWriteTemplateInstancing);
        fileTelegramStreamExtraOperatorsHeader.replace("write operators", generator.codeStreamExtraWriteDeclarations);
        fileTelegramStreamExtraOperatorsSource.replace("write operators implementation", generator.codeStreamExtraWriteDefinitions);
    }

    {

        OutputFile fileTypesDebugHeader("TLTypesDebug.hpp");
        OutputFile fileTypesDebugSource("TLTypesDebug.cpp");
        OutputFile fileRpcDebugSource("TLRpcDebug.cpp");
        fileTypesDebugHeader.replace("TLTypes debug operators", generator.codeDebugWriteDeclarations);
        fileTypesDebugSource.replace("TLTypes debug operators", generator.codeDebugWriteDefinitions);
        fileRpcDebugSource.replace("RPC debug cases", generator.codeDebugRpcParse, 4);
    }

    QVector<FunctionGroup> functionGroups;
    for (const QString &group : generator.functionGroups()) {
        FunctionGroup g;
        g.name1stCapital = Generator::formatName(group, Generator::FormatOption::UpperCaseFirstLetter);
        g.nameSmall = group.toLower();
        g.nameCapital = group.toUpper();
        functionGroups.append(g);
    }

    const QString licenseText = getLicenseText(s_author);
    // ClientRpcLayer
    {
        const QString clientRpcLayerTemplateCpp = readTemplateFile("ClientRpcLayerTemplate.cpp");
        const QString clientRpcLayerTemplateHpp = readTemplateFile("ClientRpcLayerTemplate.hpp");
        QStringList lowLevelForwardDeclarations;
        QStringList lowLevelRpcGetters;
        QStringList lowLevelRpcMembers;
        QStringList lowLevelInitCode;
        QStringList lowLevelIncludes;
        for (const FunctionGroup &group : functionGroups) {
            const QString fileBaseName = QLatin1String("ClientRpc") + group.name1stCapital + ("Layer");
            OutputFile sourceFile(QStringLiteral("RpcLayers/") + fileBaseName + (".cpp"));
            OutputFile headerFile(QStringLiteral("RpcLayers/") + fileBaseName + (".hpp"));
            if (!sourceFile.hasContent()) {
                QString defaultContent = clientRpcLayerTemplateCpp;
                defaultContent.prepend(licenseText);
                preprocessContent(&defaultContent, group);
                sourceFile.setContent(defaultContent);
            }
            if (!headerFile.hasContent()) {
                QString defaultContent = clientRpcLayerTemplateHpp;
                defaultContent.prepend(licenseText);
                preprocessContent(&defaultContent, group);
                headerFile.setContent(defaultContent);
            }
            const Generator::MethodsCode functions = generator.generateClientFunctions(group.nameSmall);
            const QString declCode = Generator::joinLinesWithPrepend(functions.declarations, Generator::spacing, QStringLiteral("\n"));
            headerFile.replace("Telegram API declarations", declCode, 4);
            const QString defCode = Generator::joinLinesWithPrepend(functions.definitions, QString(), QStringLiteral("\n"));
            sourceFile.replace("Telegram API definitions", defCode);
            const QString templatesCode = Generator::joinLinesWithPrepend(generator.generateRpcReplyTemplates(group.nameSmall), QString(), QStringLiteral("\n"));
            sourceFile.replace("Telegram API reply template specializations", templatesCode);

            lowLevelForwardDeclarations.append(QStringLiteral("class %1RpcLayer;").arg(group.name1stCapital));
            lowLevelIncludes.append(QStringLiteral("#include \"%1\"").arg(fileBaseName + (".hpp")));
            lowLevelRpcGetters.append(QStringLiteral("%1RpcLayer *%2Layer() { return m_%2Layer; }").arg(group.name1stCapital, group.nameSmall));
            lowLevelRpcMembers.append(QStringLiteral("%1RpcLayer *m_%2Layer = nullptr;").arg(group.name1stCapital, group.nameSmall));
            lowLevelInitCode.append(QStringLiteral("m_%1Layer = new %2RpcLayer(this);").arg(group.nameSmall, group.name1stCapital));
            lowLevelInitCode.append(QStringLiteral("m_%1Layer->setSendMethod(sendMethod);").arg(group.nameSmall));
        }

        {
            const QString lowLevelForwardDeclarationsCode = Generator::joinLinesWithPrepend(lowLevelForwardDeclarations, QString(), QStringLiteral("\n"));
            const QString lowLevelRpcGettersCode = Generator::joinLinesWithPrepend(lowLevelRpcGetters, Generator::spacing, QStringLiteral("\n"));
            const QString lowLevelRpcMembersCode = Generator::joinLinesWithPrepend(lowLevelRpcMembers, Generator::spacing, QStringLiteral("\n"));
            const QString lowLevelInitCodeCode = Generator::joinLinesWithPrepend(lowLevelInitCode, Generator::spacing, QStringLiteral("\n"));
            const QString lowLevelIncludesCode = Generator::joinLinesWithPrepend(lowLevelIncludes, QString(), QStringLiteral("\n"));

            OutputFile headerFile("ClientBackend.hpp");
            OutputFile sourceFile("ClientBackend.cpp");
            headerFile.replace("low-level layers forward declarations", lowLevelForwardDeclarationsCode);
            headerFile.replace("low-level layers", lowLevelRpcGettersCode, 4);
            headerFile.replace("low-level layer members", lowLevelRpcMembersCode, 4);
            sourceFile.replace("low-level layer initialization", lowLevelInitCodeCode, 4);
            sourceFile.replace("low-level layer includes", lowLevelIncludesCode);
        }
    }

    {
        OutputFile fileTypes("TLFunctions.hpp");
        fileTypes.replace("TLFunctions", generator.generateFunctionStructs());
    }

    {
        OutputFile headerFile("../server/FunctionStreamOperators.hpp");
        OutputFile sourceFile("../server/FunctionStreamOperators.cpp");
        const Generator::MethodsCode functions = generator.generateFunctionStreamOperators();
        const QString declCode = Generator::joinLinesWithPrepend(functions.declarations);
        headerFile.replace("write operators", declCode);
        const QString defCode = Generator::joinLinesWithPrepend(functions.definitions);
        sourceFile.replace("write operators", defCode);
    }

    // Server
    {
        const QString serverOperationFactoryTemplateCpp = readTemplateFile("ServerOperationFactory.cpp");
        const QString serverOperationFactoryTemplateHpp = readTemplateFile("ServerOperationFactory.hpp");
        for (const FunctionGroup &group : functionGroups) {
            const QString fileBaseName = QStringLiteral("../server/RpcOperations/") + group.name1stCapital + QStringLiteral("OperationFactory");
            OutputFile sourceFile(fileBaseName + (".cpp"));
            OutputFile headerFile(fileBaseName + (".hpp"));
            if (!sourceFile.hasContent()) {
                QString defaultContent = serverOperationFactoryTemplateCpp;
                defaultContent.prepend(licenseText);
                preprocessContent(&defaultContent, group);
                sourceFile.setContent(defaultContent);
            }
            if (!headerFile.hasContent()) {
                QString defaultContent = serverOperationFactoryTemplateHpp;
                defaultContent.prepend(licenseText);
                preprocessContent(&defaultContent, group);
                headerFile.setContent(defaultContent);
            }

            {
                const Generator::MethodsCode functions = generator.generateServerRpcProcessMethods(group.nameSmall);
                const QString declCode = Generator::joinLinesWithPrepend(functions.declarations, Generator::spacing, QStringLiteral("\n"));
                headerFile.replace("process methods", declCode, 4);
                const QString defCode = Generator::joinLinesWithPrepend(functions.definitions);
                sourceFile.replace("process methods", defCode);
            }
            {
                const Generator::MethodsCode functions = generator.generateServerRpcRunMethods(group.nameSmall, sourceFile.content());
                const QString declCode = Generator::joinLinesWithPrepend(functions.declarations, Generator::spacing, QStringLiteral("\n"));
                headerFile.replace("run methods", declCode, 4);
                const QString defCode = Generator::joinLinesWithPrepend(functions.definitions);
                sourceFile.replace("run methods", defCode);
            }
            const QString rpcMembers = Generator::joinLinesWithPrepend(generator.generateServerRpcMembers(group.nameSmall), Generator::spacing, QStringLiteral("\n"));
            headerFile.replace("RPC members", rpcMembers, 4);

            const QString methodForRpcFunctionCases = Generator::joinLinesWithPrepend(generator.generateServerMethodForRpcFunction(group.nameSmall));
            sourceFile.replace("methodForRpcFunction cases", methodForRpcFunctionCases, 4);
        }

        {
            const int initIndentation = 8;
            OutputFile sourceFile("../server/TelegramServer.cpp");
            QString includes = Generator::joinLinesWithPrepend(generator.serverRpcFactoryIncludes(),
                                                               QString(), QStringLiteral("\n"));
            QString initialization = Generator::joinLinesWithPrepend(generator.serverRpcFactoryInitialization(),
                                                                     QString(initIndentation, QLatin1Char(' ')), QStringLiteral("\n"));
            sourceFile.replace("RPC Operation Factory includes", includes);
            sourceFile.replace("RPC Operation Factory initialization", initialization, initIndentation);
        }
    }

    printf("Spec file successfully used for generation.\n");
    return NoError;
}

/* Example of usage:
     generator --generate-from-text %{sourceDir}/generator/scheme-45.tl -I %{sourceDir}/TelegramQt
     generator --fetch-text https://raw.githubusercontent.com/telegramdesktop/tdesktop/bccd80187489a5a1e94d1adb7de7c72275a62f1a/Telegram/Resources/scheme.tl
     // 72, commit bccd80187489a5a1e94d1adb7de7c72275a62f1a
     generator --generate-from-text scheme-72.tl -I %{sourceDir}/TelegramQt

 */

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption inputDirOption(QStringList({QStringLiteral("I"), QStringLiteral("input-dir")}));
    inputDirOption.setValueName(QStringLiteral("inputDir"));
    parser.addOption(inputDirOption);

    QCommandLineOption outputDirOption(QStringList({QStringLiteral("O"), QStringLiteral("output-dir")}));
    outputDirOption.setValueName(QStringLiteral("outputDir"));
    parser.addOption(outputDirOption);

    QCommandLineOption dryRunOption(QStringLiteral("dry-run"));
    parser.addOption(dryRunOption);

    QCommandLineOption dumpOption(QStringLiteral("dump"));
    parser.addOption(dumpOption);

    QCommandLineOption authorOption(QStringLiteral("author"));
    authorOption.setValueName(QStringLiteral("author"));
    parser.addOption(authorOption);

    QCommandLineOption addSpecSourcesOption(QStringLiteral("add-spec-sources"));
    parser.addOption(addSpecSourcesOption);

    QCommandLineOption fetchTextOption(QStringLiteral("fetch-text"));
    fetchTextOption.setValueName(QStringLiteral("url"));
    parser.addOption(fetchTextOption);

    QCommandLineOption fetchJsonOption(QStringLiteral("fetch-json"));
    parser.addOption(fetchJsonOption);

    QCommandLineOption formatJsonOption(QStringLiteral("format-json"));
    parser.addOption(formatJsonOption);

    QCommandLineOption generateFromJsonOption(QStringLiteral("generate-from-json"));
    parser.addOption(generateFromJsonOption);

    QCommandLineOption generateFromTextOption(QStringLiteral("generate-from-text"));
    parser.addOption(generateFromTextOption);

    parser.addPositionalArgument(QStringLiteral("spec"), QStringLiteral("The specification file (text or json)"));

    parser.process(app);

    if (!parser.isSet(fetchTextOption) && (parser.positionalArguments().count() != 1)) {
        parser.showHelp(InvalidArgument);
    }

    s_author = parser.value(authorOption);
    s_dryRun = parser.isSet(dryRunOption);
    s_dump = parser.isSet(dumpOption);
    s_addSpecSources = parser.isSet(addSpecSourcesOption);
    s_inputDir = parser.value(inputDirOption);
    if (s_inputDir.isEmpty()) {
        s_inputDir = QStringLiteral("./");
    } else if (!s_inputDir.endsWith(QLatin1Char('/'))) {
        s_inputDir.append(QLatin1Char('/'));
    }
    s_outputDir = parser.value(outputDirOption);
    if (s_outputDir.isEmpty()) {
        s_outputDir = s_inputDir;
    } else if (!s_outputDir.endsWith(QLatin1Char('/'))) {
        s_outputDir.append(QLatin1Char('/'));
    }

    QString specFileName;
    if (!parser.positionalArguments().isEmpty()) {
        specFileName = parser.positionalArguments().first();
    }

    StatusCode code = InvalidArgument;

    if (parser.isSet(fetchTextOption)) {
        QString url = parser.value(fetchTextOption);
        code = fetchText(url, &specFileName);
        if (code != NoError) {
            return code;
        }
    }

    if (parser.isSet(fetchJsonOption)) {
        code = fetchJson(specFileName);
        if (code != NoError) {
            return code;
        }
    }

    if (parser.isSet(formatJsonOption)) {
        code = format(specFileName);
        if (code != NoError) {
            return code;
        }
    }

    if (!QDir(s_outputDir).exists()) {
        if (!QDir().mkpath(s_outputDir)) {
            qWarning() << "Unable to create output directory" << QDir(s_outputDir).absolutePath();
            return FileAccessError;
        }
    }

    if (parser.isSet(generateFromJsonOption)) {
        code = generate(JsonFormat, specFileName);
        if (code != NoError) {
            return code;
        }
    }

    if (parser.isSet(generateFromTextOption)) {
        code = generate(TextFormat, specFileName);
        if (code != NoError) {
            return code;
        }
    }

    return code;
}

#include "main.moc"
