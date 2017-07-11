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
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <stdio.h>

const static int hashMaxLength = 8;

inline int indexOfSeparator(const QString &str, int minIndex)
{
    int dotIndex = str.indexOf(QChar('.'), minIndex);
    int underscoreIndex = str.indexOf(QChar('_'), minIndex);

    if (dotIndex < 0) {
        return underscoreIndex;
    } else if (underscoreIndex < 0) {
        return dotIndex;
    }

    return dotIndex < underscoreIndex ? dotIndex : underscoreIndex;
}

bool replaceSection(const QString &fileName, const QString &startMarker, const QString &endMarker, const QString &newContent)
{
    QFile fileToProcess(fileName);

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

    if (previousContent == startMarker + newContent + endMarker) {
        printf("Nothing to do: new and previous contents are exactly same.\n");
        return true;
    }

    fileContent.remove(startPos, endPos - startPos);
    fileContent.insert(startPos, startMarker + newContent + endMarker);

    if (!fileToProcess.open(QIODevice::WriteOnly)) {
        printf("Can not write file: %s.\n", fileName.toLocal8Bit().constData());
        return false;
    }

    if (winNewLines) {
        fileContent.replace(QLatin1String("\n"), QLatin1String("\r\n"));
    }

    fileToProcess.write(fileContent.toLatin1());

    fileToProcess.close();

    return true;
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

QString generateCode(const QString &fileName, int indentation, bool closeEnum)
{
    QFile sourceFile(fileName);

    if (!sourceFile.open(QIODevice::ReadWrite)) {
        return QString();
    }

    QTextStream input(&sourceFile);

    QString result;
    QString indentationStr(indentation, QChar(' '));

    int currentLine = 0;
    while (!input.atEnd()) {
        QString line = input.readLine();
        ++currentLine;

        if (line.simplified().isEmpty() || (line.startsWith(QLatin1String("---")) && line.endsWith(QLatin1String("---")))) {
            continue;
        }

        int hashIndex = line.indexOf(QChar('#'));
        if ((hashIndex < 1) || (hashIndex + 1 > line.length())) {
            printf("Bad string: %s (%s:%d)\n", line.toLocal8Bit().constData(), fileName.toLocal8Bit().constData(), currentLine);
            return QString();
        }

        QString name = line.left(hashIndex);

        name[0] = name.at(0).toUpper();

        int separatorIndex = 0;
        while ((separatorIndex = indexOfSeparator(name, separatorIndex)) > 0) {
            if ((name.length() < separatorIndex + 1) || (!name.at(separatorIndex + 1).isLetter())) {
                printf("Bad name: %s (%s:%d)\n", name.toLocal8Bit().constData(), fileName.toLocal8Bit().constData(), currentLine);
                return QString();
            }
            name[separatorIndex + 1] = name.at(separatorIndex + 1).toUpper();
            name.remove(separatorIndex, 1);
        }

        QString value = line.mid(hashIndex + 1, hashMaxLength);
        int endOfValue = value.indexOf(QChar(' '));
        if (endOfValue > 0) {
            value.truncate(endOfValue);
        }

        result.append(indentationStr);

        if (!closeEnum || !input.atEnd()) {
            result.append(QString("%1 = 0x%2,\n").arg(name).arg(value));
        } else {
            result.append(QString("%1 = 0x%2\n").arg(name).arg(value));
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <source file or directory> <destination file> <marker>\nExample: %s specs ../TLValues.hpp TLValues\n", argv[0], argv[0]);
        return 0;
    }

    QCoreApplication app(argc, argv);

    static const QStringList arguments = app.arguments();
    static const int indentation = 8;
    QString indentationStr(indentation, QChar(' '));

    QString code;

    QDir argDir(arguments.at(1));

    if (argDir.exists()) {
        const QStringList filesList = argDir.entryList(QStringList() << "*.txt", QDir::Files|QDir::Readable, QDir::Name);

        for (int i = 0; i < filesList.count(); ++i) {
            bool closeEnum = i == filesList.count() - 1;
            code.append(indentationStr + QString("// From %1:\n").arg(filesList.at(i)));
            code.append(generateCode(argDir.absolutePath() + "/" + filesList.at(i), indentation, closeEnum));

            if (!closeEnum) {
                code.append(QChar('\n'));
            }
        }
    } else {
        code.append(generateCode(arguments.at(1), indentation, /* closeEnum */ true));
    }

    if (replacingHelper(arguments.at(2), indentation, arguments.at(3), code)) {
        printf("File successfully updated.\n");
    }

    return 0;
}
