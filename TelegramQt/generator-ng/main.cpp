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

#include "GeneratorNG.hpp"

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

static QString s_inputDir;
static QString s_outputDir;

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

bool replaceSection(const QString &fileName, const QString &startMarker, const QString &endMarker, const QString &newContent)
{
    QFile fileToProcess(s_inputDir + fileName);

    if (!fileToProcess.open(QIODevice::ReadOnly))
        return false;

    QString fileContent = fileToProcess.readAll();
    fileToProcess.close();

    bool winNewLines = fileContent.indexOf(QLatin1String("\r\n")) > 0;

    if (winNewLines) {
        fileContent.replace(QLatin1String("\r\n"), QLatin1String("\n"));
    }

    int startPos = fileContent.indexOf(startMarker);
    int endPos   = fileContent.indexOf(endMarker);

    if (startPos >= 0) {
        if (endPos < 0) {
            printf("There is only start marker in the file %s. Error.\n", fileName.toLocal8Bit().constData());
            return false;
        }

        endPos += endMarker.length();
    } else {
        return false;
    }

    const QString previousContent = fileContent.mid(startPos, endPos - startPos);

    const bool changed = previousContent != startMarker + newContent + endMarker;

    if (s_dump) {
        const char *strChanged = "changed";
        const char *strNotChanged = "not changed";

        printf("File: \"%s\", Startmarker: \"%s\", Code (%s):\n%s\n", fileName.toLocal8Bit().constData(), startMarker.trimmed().toLocal8Bit().constData(),
               changed ? strChanged : strNotChanged,
               newContent.toLocal8Bit().constData());
    }

    if (!changed) {
        printf("Nothing to do: new and previous contents are exactly same.\n");
        return true;
    }

    fileContent.remove(startPos, endPos - startPos);
    fileContent.insert(startPos, startMarker + newContent + endMarker);

    if (!s_dryRun) {
        fileToProcess.setFileName(s_outputDir + fileName);
        if (!fileToProcess.open(QIODevice::WriteOnly))
            return false;

        if (winNewLines) {
            fileContent.replace(QLatin1String("\n"), QLatin1String("\r\n"));
        }

        fileToProcess.write(fileContent.toLatin1());

        fileToProcess.close();
        printf("Replacing is done.\n");
    } else {
        printf("Replacing is done (dry run).\n");
    }

    return true;
}

bool partialReplacingHelper(const QString &fileName, int spacing, const QString &marker, const QString &newContent)
{
    const QString space(spacing, QChar(' '));

    if (!replaceSection(fileName,
                        QString("%1// Partially generated %2\n").arg(space).arg(marker),
                        QString("%1// End of partially generated %2\n").arg(space).arg(marker), newContent)) {
        printf("Can not update file %s with marker %s.\n", fileName.toLatin1().constData(), marker.toLatin1().constData());
        return false;
    } else {
        return true;
    }
}

bool replacingHelper(const QString &fileName, int spacing, const QString &marker, const QString &newContent)
{
    const QString space(spacing, QChar(' '));

    if (!replaceSection(fileName,
                        QString("%1// Generated %2\n").arg(space).arg(marker),
                        QString("%1// End of generated %2\n").arg(space).arg(marker), newContent)) {
        printf("Can not update file %s with marker %s.\n", fileName.toLatin1().constData(), marker.toLatin1().constData());
        return false;
    } else {
        return true;
    }
}

/* End of replacing helper */

void debugType(const TLType &type)
{
    qDebug() << type.name;
    foreach (const TLSubType &subType, type.subTypes) {
        qDebug() << "    " << subType.name;
        foreach (const TLParam &member, subType.members) {
            qDebug() << "        " << member.type << member.name;
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

    GeneratorNG generator;
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

    generator.existsStreamReadTemplateInstancing = getGeneratedContent(QStringLiteral("CTelegramStream.cpp"), 0, QLatin1String("vector read templates instancing"));
    generator.existsStreamWriteTemplateInstancing = getGeneratedContent(QStringLiteral("CTelegramStream.cpp"), 0, QLatin1String("vector write templates instancing"));
    generator.setExistsRpcProcessDefinitions(getPartiallyGeneratedContent(QStringLiteral("CTelegramConnection.cpp"),
                                                                          0,
                                                                          QStringLiteral("Telegram API RPC process implementation")));
    generator.generate();

    replacingHelper(QLatin1String("TLValues.hpp"), 8, QLatin1String("TLValues"), generator.codeOfTLValues);
    replacingHelper(QLatin1String("TLTypes.hpp"), 0, QLatin1String("TLTypes"), generator.codeOfTLTypes);
    replacingHelper(QLatin1String("CTelegramStream.hpp"), 4, QLatin1String("read operators"), generator.codeStreamReadDeclarations);
    replacingHelper(QLatin1String("CTelegramStream.cpp"), 0, QLatin1String("read operators implementation"), generator.codeStreamReadDefinitions);
    replacingHelper(QLatin1String("CTelegramStream.cpp"), 0, QLatin1String("vector read templates instancing"), generator.codeStreamReadTemplateInstancing);
    replacingHelper(QLatin1String("CTelegramStream.hpp"), 4, QLatin1String("write operators"), generator.codeStreamWriteDeclarations);
    replacingHelper(QLatin1String("CTelegramStream.cpp"), 0, QLatin1String("write operators implementation"), generator.codeStreamWriteDefinitions);
    replacingHelper(QLatin1String("CTelegramStream.cpp"), 0, QLatin1String("vector write templates instancing"), generator.codeStreamWriteTemplateInstancing);
    replacingHelper(QLatin1String("CTelegramConnection.hpp"), 4, QLatin1String("Telegram API methods declaration"), generator.codeConnectionDeclarations);
    replacingHelper(QLatin1String("CTelegramConnection.cpp"), 0, QLatin1String("Telegram API methods implementation"), generator.codeConnectionDefinitions);

    replacingHelper(QLatin1String("CTelegramConnection.hpp"), 4, QLatin1String("Telegram API RPC process declarations"), generator.codeRpcProcessDeclarations);
    partialReplacingHelper(QLatin1String("CTelegramConnection.cpp"), 0, QLatin1String("Telegram API RPC process implementation"), generator.codeRpcProcessDefinitions);
    replacingHelper(QLatin1String("CTelegramConnection.cpp"), 8, QLatin1String("RPC processing switch cases"), generator.codeRpcProcessSwitchCases);
    replacingHelper(QLatin1String("CTelegramConnection.cpp"), 8, QLatin1String("RPC processing switch updates cases"), generator.codeRpcProcessSwitchUpdatesCases);

    replacingHelper(QLatin1String("TLTypesDebug.hpp"), 0, QLatin1String("TLTypes debug operators"), generator.codeDebugWriteDeclarations);
    replacingHelper(QLatin1String("TLTypesDebug.cpp"), 0, QLatin1String("TLTypes debug operators"), generator.codeDebugWriteDefinitions);

    replacingHelper(QLatin1String("TLRpcDebug.cpp"), 4, QLatin1String("RPC debug cases"), generator.codeDebugRpcParse);

    printf("Spec file successfully used for generation.\n");
    return NoError;
}

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

    QCommandLineOption addSpecSourcesOption(QStringLiteral("add-spec-sources"));
    parser.addOption(addSpecSourcesOption);

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

    if (parser.positionalArguments().count() != 1) {
        parser.showHelp(InvalidArgument);
    }

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

    const QString specFileName = parser.positionalArguments().first();

    StatusCode code = InvalidArgument;

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
