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

#include "Generator.hpp"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>

#include <zlib.h>

static const QString tlPrefix = QLatin1String("TL");
static const QString tlValueName = tlPrefix + QLatin1String("Value");
static const QString tlTypeMember = QLatin1String("tlType");
static const QString tlVectorType = QLatin1String("TLVector");
static const QString tlTrueType = QLatin1String("TLTrue");
static const QStringList podTypes = QStringList() << "bool" << "quint32" << "quint64" << "double" << tlValueName;
static const QStringList initTypesValues = QStringList() << "false" << "0" << "0" << "0" << "0";
static const QStringList plainTypes = QStringList() << "Bool" << "#" << "int" << "long" << "double" << "string" << "bytes"
                                                    << QStringLiteral("int128")
                                                    << QStringLiteral("int256")
                                                       ;
static const QStringList nativeTypes = QStringList() << "bool" << "quint32" << "quint32" << "quint64" << "double" << "QString" << "QByteArray"
                                                     << QStringLiteral("TLNumber128")
                                                     << QStringLiteral("TLNumber256")
                                                        ;

static const QString spacing = QString(4, QLatin1Char(' '));
static const QString doubleSpacing = spacing + spacing;

static const QString streamClassName = QLatin1String("CTelegramStream");
static const QString methodsClassName = QLatin1String("CTelegramConnection");

static const QStringList typesBlackList = QStringList()
        << QLatin1String("TLVector t")
        << QLatin1String("TLNull")
        << QLatin1String("TLMessagesMessage")
        << tlTrueType
           ;

QString ensureGoodName(const QString &name, const QVariantHash &context)
{
    static const QStringList badNames = QStringList()
            << QStringLiteral("static")
            << QStringLiteral("lat")
            << QStringLiteral("long")
            << QStringLiteral("public")
            << QStringLiteral("private")
            << QStringLiteral("inline")
               ;
    static const QStringList badNamesReplacers = QStringList()
            << QStringLiteral("isStatic")
            << QStringLiteral("latitude")
            << QStringLiteral("longitude")
            << QStringLiteral("isPublic")
            << QStringLiteral("isPrivate")
            << QStringLiteral("isInline")
               ;

    if (context.value("parentType").toString() == QLatin1String("channelAdminLogEventsFilter")) {
        if (name == QLatin1String("delete")) {
            return "deleted";
        }
    }

    int index = badNames.indexOf(name);
    if (index < 0) {
        return name;
    }

    return badNamesReplacers.at(index);
}

QString removeTypePrefix(QString name)
{
    if (name.startsWith(tlPrefix)) {
        return name.mid(2);
    }
    if (name.startsWith(QLatin1Char('Q')) && (name.size() > 1) && name.at(1).isUpper()) {
        return name.mid(1);
    }
    return name;
}

QDebug operator<<(QDebug d, const TLParam &param)
{
    d << param.type() << ":" << param.getAlias() << "; ";
    return d;
}

QDebug operator<<(QDebug d, const TLType &type)
{
    d << "TLType(" << type.name << ") {";
    foreach (const TLSubType &sub, type.subTypes) {
        d << sub.name << ":" << sub.members;
    }

    d << "}";

    return d;
}

inline int indexOfSeparator(const QString &str, int minIndex)
{
    const int dotIndex = str.indexOf(QChar('.'), minIndex);
    const int underscoreIndex = str.indexOf(QChar('_'), minIndex);

    if (dotIndex < 0) {
        return underscoreIndex;
    } else if (underscoreIndex < 0) {
        return dotIndex;
    }

    return dotIndex < underscoreIndex ? dotIndex : underscoreIndex;
}

QString Generator::removeSeparators(QString name)
{
    int separatorIndex = 0;
    while ((separatorIndex = indexOfSeparator(name, separatorIndex)) > 0) {
        if ((name.length() < separatorIndex + 1) || (!name.at(separatorIndex + 1).isLetter())) {
            break;
        }
        name[separatorIndex + 1] = name.at(separatorIndex + 1).toUpper();
        name.remove(separatorIndex, 1);
    }

    return name;
}

QString Generator::formatName(const QStringList &nameParts, FirstLetterCase firstCase)
{
    if (nameParts.isEmpty()) {
        return QString();
    }

    bool first = true;
    QString result;
    for (QString part : nameParts) {
        if (part.isEmpty()) {
            continue;
        }
        if (first) {
            first = false;
        } else {
            part[0] = part.at(0).toUpper();
        }
        result.append(part);
    }
    // TODO: Move removeSeparators out of the method
    result = removeSeparators(result);
    switch (firstCase) {
    case FirstLetterCase::Any:
        break;
    case FirstLetterCase::Upper:
        result[0] = result.at(0).toUpper();
        break;
    case FirstLetterCase::Lower:
        result[0] = result.at(0).toLower();
        break;
    }
    return result;
}

QString removePrefix(const QString &str)
{
    if (str.startsWith(tlPrefix)) {
        return str.mid(tlPrefix.size());
    } else {
        return str;
    }
}

QString joinLinesWithPrepend(const QStringList &lines, const QString &prep)
{
    if (lines.isEmpty()) {
        return QString();
    }
    QString result;
    int lineSize = [&]() {
        int size = 0;
        for (const QString &line : lines) {
            size += prep.size() + line.size() + 1;
        }
        return size;
    }();
    result.reserve(lineSize);
    for (const QString &line : lines) {
        result.append(prep + line + QLatin1Char('\n'));
    }
    return result;
}

QString Generator::formatMember(QString name, const QVariantHash &context)
{
    name = ensureGoodName(name, context);
    return removeSeparators(name);
}

QString Generator::formatMethodParam(const TLParam &param)
{
    if (podTypes.contains(param.type())) {
        return QString("%1 %2").arg(param.type()).arg(param.getAlias());
    } else {
        return  QString("const %1 &%2").arg(param.type()).arg(param.getAlias());
    }
}

QString Generator::formatMethodParams(const TLMethod &method)
{
    QString result;

    foreach (const TLParam &param, method.params) {
        if (param.dependOnFlag() && (param.type() == tlTrueType)) {
            continue;
        }

        if (!result.isEmpty()) {
            result += QLatin1String(", ");
        }

        result += formatMethodParam(param);
    }

    return result;
}

QString Generator::getTypeOrVectorType(const QString &str, bool *isVectorPtr)
{
    const bool isVector = str.startsWith(tlVectorType + QLatin1Char('<'));
    if (isVectorPtr) {
        *isVectorPtr = isVector;
    }
    if (!isVector) {
        return str;
    }
    const int firstIndex = str.indexOf(QLatin1Char('<')) + 1;
    const int lastIndex = str.indexOf(QLatin1Char('>'));
    const QString subType = str.mid(firstIndex, lastIndex - firstIndex);
    return subType;
}

qint8 Generator::flagBitForMember(const QStringRef &type, QString *flagMember)
{
    int indexOfQuestion = type.indexOf(QLatin1Char('?'));
    if (indexOfQuestion < 0) {
        return -1;
    }

    int indexOfBitIndex = type.lastIndexOf(QLatin1Char('.'), indexOfQuestion) + 1;
    if (indexOfBitIndex <= 0) {
        return -2;
    }

    bool ok;
    QStringRef ref = type.mid(indexOfBitIndex, indexOfQuestion - indexOfBitIndex);
    qint8 result = ref.toUInt(&ok);

    if (!ok) {
        return -3;
    }

    if (flagMember) {
        *flagMember = type.left(indexOfBitIndex - 1).toString(); // (index - 1) is the dot, (index - 2) is the last symbol of the flag-member name
    }

    return result;
}

QString Generator::formatType(QString type)
{
    if (type.contains(QLatin1Char('?'))) {
        type = type.section(QLatin1Char('?'), 1);
    }

    if (plainTypes.contains(type)) {
        return nativeTypes.at(plainTypes.indexOf(type));
    } else if (type.startsWith(QLatin1String("Vector<"), Qt::CaseInsensitive)) {
        int firstIndex = type.indexOf(QLatin1Char('<')) + 1;
        int lastIndex = type.indexOf(QLatin1Char('>'));
        QString subType = type.mid(firstIndex, lastIndex - firstIndex);
        return QString("%1<%2>").arg(tlVectorType).arg(formatType(subType));
    } else {
        type[0] = type.at(0).toUpper();

        return tlPrefix + removeSeparators(type);
    }
}

QMap<QString, TLType> Generator::readTypesJson(const QJsonDocument &document)
{
    const QJsonArray constructors = document.object().value("constructors").toArray();

    QMap<QString, TLType> types;

    for (int i = 0; i < constructors.count(); ++i) {
        const QJsonObject obj = constructors.at(i).toObject();

        const QString predicateName = formatName(obj.value("predicate").toString(), FirstLetterCase::Upper);
        const quint32 predicateId = obj.value("id").toString().toInt();
        const QString typeName = formatType(obj.value("type").toString());

        TLType tlType = types.value(typeName);
        tlType.name = typeName;

        TLSubType tlSubType;
        tlSubType.name = predicateName;
        tlSubType.id = predicateId;

        const QJsonArray params = obj.value("params").toArray();

        foreach (const QJsonValue &paramValue, params) {
            const QJsonObject &paramObj = paramValue.toObject();
            const QString paramName = formatMember(paramObj.value("name").toString(), {{ "parentType", predicateName }} );

            const QString paramType = paramObj.value("type").toString();

            tlSubType.members.append(TLParam(paramName, formatType(paramType)));
        }

        tlType.subTypes.append(tlSubType);
        types.insert(typeName, tlType);
    }

    return types;
}

QMap<QString, TLMethod> Generator::readFunctionsJson(const QJsonDocument &document)
{
    const QJsonArray methods = document.object().value("methods").toArray();

    QMap<QString, TLMethod> result;

    for (int i = 0; i < methods.count(); ++i) {
        const QJsonObject obj = methods.at(i).toObject();

        const QString methodName = removeSeparators(obj.value("method").toString());
        const quint32 methodId = obj.value("id").toString().toInt();
        const QString typeName = formatType(obj.value("type").toString());

        TLMethod tlMethod;
        tlMethod.name = methodName;
        tlMethod.id = methodId;
        tlMethod.type = typeName;

        const QJsonArray params = obj.value("params").toArray();

        foreach (const QJsonValue &paramValue, params) {
            const QJsonObject &paramObj = paramValue.toObject();
            const QString paramName = formatMember(paramObj.value("name").toString(), {{ "parentType", methodName }} );

            const QString paramType = paramObj.value("type").toString();

            tlMethod.params.append(TLParam(paramName, formatType(paramType)));
        }

        result.insert(methodName, tlMethod);

//        quint32 id = obj.value("id").toString().toInt();
//        qDebug() << name << QString::number(id, 0x10);
    }

    return result;
}

QString TLParam::flagName() const
{
    QString flagName = getAlias();
    if (flagName.isEmpty()) {
        qCritical() << "Invalid flagName of a param";
        return QString();
    }
    flagName[0] = flagName.at(0).toUpper();
    return flagName;
}

void TLParam::setType(const QString &newType)
{
    m_type = newType;
    m_bareType = Generator::getTypeOrVectorType(newType, &m_isVector);
}

QString Generator::generateTLValuesDefinition(const TLType &type)
{
    QString code;

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("        %1 = 0x%2,\n").arg(subType.name).arg(subType.id, 8, 0x10, QLatin1Char('0')));
    }

    return code;
}

QString Generator::generateTLValuesDefinition(const TLMethod &method)
{
    return QString("        %1 = 0x%2,\n").arg(method.nameFirstCapital()).arg(method.id, 8, 0x10, QLatin1Char('0'));
}

QString Generator::generateTLTypeDefinition(const TLType &type, bool addSpecSources)
{
    QString code;

    code.append(QString("struct %1 {\n").arg(type.name));

//    QString anotherName = removePrefix(type.name);
//    anotherName[0] = anotherName.at(0).toUpper();
//    anotherName.prepend(QLatin1String("another"));
    bool constExpr = true;
    QString constructor = QString("%1() :\n").arg(type.name);
//    QString copyConstructor = spacing + QString("%1(const %1 &%2) :\n").arg(type.name).arg(anotherName);
//    QString copyOperator = spacing + QString("%1 &operator=(const %1 &%2) {\n").arg(type.name).arg(anotherName);
    static const QString specCommentPrefix = spacing + QStringLiteral("// ");
    QString specSource;
    QString isValidTypeCode;

    QStringList addedMembers;
    foreach (const TLSubType &subType, type.subTypes) {
        if (!subType.source.isEmpty()) {
            QStringList sourceLines;
            const QString source = subType.source;
            const int sectionsSplitterIndex = source.indexOf(QLatin1Char('='));
            const QStringRef basePart = source.leftRef(sectionsSplitterIndex);
            const int hashIndex = basePart.indexOf(QLatin1Char('#'));
            const int endOfPredicate = basePart.indexOf(QChar(' '), hashIndex);
            const QStringRef predicate = basePart.left(endOfPredicate);
            const QStringRef typePart = source.midRef(sectionsSplitterIndex);

            sourceLines.append(specCommentPrefix + predicate.toString());
            const int from = predicate.position() + predicate.size();
            for (const QStringRef memberSource : source.midRef(from, typePart.position() - from).split(QLatin1Char(' '), QString::SkipEmptyParts)) {
                sourceLines.append(specCommentPrefix + spacing + memberSource.toString());
            }
            sourceLines.append(specCommentPrefix + doubleSpacing + typePart.toString());

            specSource.append(sourceLines.join(QLatin1Char('\n')) + QLatin1Char('\n'));
        }
        isValidTypeCode.append(QStringLiteral("        case %1::%2:\n").arg(tlValueName, subType.name));
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.getAlias())) {
                continue;
            }

            addedMembers.append(member.getAlias());

//            copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
//            copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
            if (!podTypes.contains(member.type())) {
                constExpr = false;
                continue;
            }

            const QString initialValue = initTypesValues.at(podTypes.indexOf(member.type()));
            constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(member.getAlias()).arg(initialValue);
        }
    }

    constructor += QString("%1%2(%3::%4),\n").arg(doubleSpacing).arg(tlTypeMember).arg(tlValueName).arg(type.subTypes.first().name);
//    copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
//    copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);

    constructor.chop(2);
    constructor.append(QLatin1String(" { }\n\n"));

    isValidTypeCode.append(QStringLiteral(
                               "            return true;\n"
                               "        default:\n"
                               "            return false;\n"
                               "        };\n"
                               "    }\n"));

//    copyConstructor.chop(2);
//    copyConstructor.append(QLatin1String(" { }\n\n"));

//    copyOperator.append(QString("\n%1%1return *this;\n%1}\n").arg(spacing));

    const QString constExprSpace = QStringLiteral("constexpr ");
    if (constExpr) {
        code.append(spacing + constExprSpace + constructor);
    } else {
        code.append(spacing + constructor);
    }
    if (addSpecSources) {
        code.append(specSource);
    }
//    code.append(copyConstructor);
//    code.append(copyOperator);
    const QString isValidFirstLines = QStringLiteral("bool isValid() const {\n"
                                                     "        switch (tlType) {\n");
    if (constExpr) {
        code.append(spacing + QStringLiteral("Q_DECL_RELAXED_CONSTEXPR ") + isValidFirstLines);
    } else {
        code.append(spacing + isValidFirstLines);
    }
    code.append(isValidTypeCode);
    const QString memberFlags = joinLinesWithPrepend(generateTLTypeMemberFlags(type), doubleSpacing);
    if (!memberFlags.isEmpty()) {
        code.append(spacing + "enum Flags {\n");
        code.append(memberFlags);
        code.append(spacing + "};\n");
    }
    if (constExpr) {
        code.append(joinLinesWithPrepend(generateTLTypeMemberGetters(type), spacing + constExprSpace));
    } else {
        code.append(joinLinesWithPrepend(generateTLTypeMemberGetters(type), spacing));
    }
    const QString members = joinLinesWithPrepend(generateTLTypeMembers(type), spacing);
    code.append(members);
    code.append(QString("};\n\n"));

    return code;
}

QStringList Generator::generateTLTypeMemberFlags(const TLType &type)
{
    QStringList addedMembers;
    QMap<quint8,QString> memberFlags;

    foreach (const TLSubType &subType, type.subTypes) {
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.getAlias())) {
                continue;
            }
            addedMembers.append(member.getAlias());
            if (member.dependOnFlag()) {
                memberFlags.insertMulti(member.flagBit, member.flagName() + QStringLiteral(" = 1 << %1,").arg(member.flagBit));
            }
        }
    }
    QStringList result;
    for (quint8 flag : memberFlags.uniqueKeys()) {
        result.append(memberFlags.values(flag));
    }
    return result;
}

QStringList Generator::generateTLTypeMemberGetters(const TLType &type)
{
    QStringList memberGetters;
    QStringList addedMembers;
    foreach (const TLSubType &subType, type.subTypes) {
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.getAlias())) {
                continue;
            }
            addedMembers.append(member.getAlias());
            if (member.dependOnFlag() && (member.type() == tlTrueType)) {
                memberGetters.append(QStringLiteral("bool %1() const { return %2 & %3; }").arg(member.getAlias(), member.flagMember, member.flagName()));
            }
        }
    }
    return memberGetters;
}

QStringList Generator::generateTLTypeMembers(const TLType &type)
{
    QStringList membersCode;
    QStringList addedMembers;
    foreach (const TLSubType &subType, type.subTypes) {
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.getAlias())) {
                continue;
            }
            addedMembers.append(member.getAlias());
            if (member.dependOnFlag() && (member.type() == tlTrueType)) {
                continue; // No extra data behind the flag
            }
            if (member.accessByPointer()) {
                if (member.isVector()) {
                    membersCode.append(QStringLiteral("%1<%2*> %3;").arg(tlVectorType, member.bareType(), member.getAlias()));
                } else {
                    membersCode.append(QStringLiteral("%1 *%2;").arg(member.type(), member.getAlias()));
                }
            } else {
                membersCode.append(QStringLiteral("%1 %2;").arg(member.type(), member.getAlias()));
            }
        }
    }
    membersCode.append(QStringLiteral("%1 %2;").arg(tlValueName, tlTypeMember));
    return membersCode;
}

QString Generator::streamReadImplementationHead(const QString &argName, const QString &typeName)
{
    QString code;
    code.append(QString("%1 &%1::operator>>(%2 &%3)\n{\n").arg(streamClassName, typeName, argName));
    code.append(QString("%1%2 result;\n\n").arg(spacing, typeName));
    code.append(QString("%1*this >> result.tlType;\n\n%1switch (result.tlType) {\n").arg(spacing));
    return code;
}

QString Generator::streamReadImplementationEnd(const QString &argName)
{
    QString code;
    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(QString("%1%2 = result;\n\n%1return *this;\n}\n\n").arg(spacing, argName));
    return code;
}

QString Generator::streamReadPerTypeImplementation(const QString &argName, const TLSubType &subType)
{
    Q_UNUSED(argName)
    QString code;
    foreach (const TLParam &member, subType.members) {
        if (member.dependOnFlag()) {
            if (member.type() == tlTrueType) {
                continue;
            }
            code.append(doubleSpacing + QString("if (result.%1 & 1 << %2) {\n").arg(member.flagMember).arg(member.flagBit));
            code.append(doubleSpacing + spacing + QString("*this >> result.%1;\n").arg(member.getAlias()));
            code.append(doubleSpacing + QLatin1Literal("}\n"));
        } else {
            if (member.accessByPointer() && !member.isVector()) {
                code.append(doubleSpacing + QString("*this >> *result.%1;\n").arg(member.getAlias()));
            } else {
                code.append(doubleSpacing + QString("*this >> result.%1;\n").arg(member.getAlias()));
            }
        }
    }
    code.append(QString("%1break;\n").arg(doubleSpacing));
    return code;
}

QString Generator::streamWriteImplementationHead(const QString &argName, const QString &typeName)
{
    QString code;
    code.append(QString("%1 &%1::operator<<(const %2 &%3)\n{\n").arg(streamClassName, typeName, argName));
    code.append(QString("%1*this << %2.tlType;\n\n%1switch (%2.tlType) {\n").arg(spacing, argName));
    return code;
}

QString Generator::streamWriteFreeImplementationHead(const QString &argName, const QString &typeName)
{
    QString code;
    code.append(QString("%1 &operator<<(%1 &stream, const %2 &%3)\n{\n").arg(streamClassName, typeName, argName));
    code.append(QString("%1stream << %2.tlType;\n%1switch (%2.tlType) {\n").arg(spacing, argName));
    return code;
}

QString Generator::streamWriteImplementationEnd(const QString &argName)
{
    Q_UNUSED(argName)

    QString code;
    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(spacing + QString("return *this;\n}\n\n"));
    return code;
}

QString Generator::streamWriteFreeImplementationEnd(const QString &argName)
{
    Q_UNUSED(argName)
    QString code;
    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(spacing + QStringLiteral("return stream;\n}\n\n"));
    return code;
}

QString Generator::streamWritePerTypeImplementation(const QString &argName, const TLSubType &subType)
{
    return streamWritePerTypeImplementationBase(argName, subType, QStringLiteral("*this"));
}

QString Generator::streamWritePerTypeFreeImplementation(const QString &argName, const TLSubType &subType)
{
    return streamWritePerTypeImplementationBase(argName, subType, QStringLiteral("stream"));
}

QString Generator::streamWritePerTypeImplementationBase(const QString &argName, const TLSubType &subType, const QString &streamGetter)
{
    QString code;
    foreach (const TLParam &member, subType.members) {
        if (member.dependOnFlag()) {
            if (member.type() == tlTrueType) {
                continue;
            }
            code.append(doubleSpacing + QString("if (%1.%2 & 1 << %3) {\n").arg(argName).arg(member.flagMember).arg(member.flagBit));
            code.append(doubleSpacing + spacing + streamGetter + QString(" << %1.%2;\n").arg(argName).arg(member.getAlias()));
            code.append(doubleSpacing + QLatin1Literal("}\n"));
        } else {
            if (member.accessByPointer() && !member.isVector()) {
                code.append(doubleSpacing + streamGetter + QString(" << *%1.%2;\n").arg(argName).arg(member.getAlias()));
            } else {
                code.append(doubleSpacing + streamGetter + QString(" << %1.%2;\n").arg(argName).arg(member.getAlias()));
            }
        }
    }
    code.append(QString("%1break;\n").arg(doubleSpacing));
    return code;
}

QString Generator::generateStreamOperatorDefinition(const TLType &type, std::function<QString (const QString &, const QString &)> head,
                                                    std::function<QString (const QString &, const TLSubType &)> generateSubtypeCode,
                                                    std::function<QString (const QString &)> end)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    argName += QLatin1String("Value");
    QString code = head(argName, type.name);
    QHash<QString,int> implementationHash; // type name to implementation index map
    QStringList implementations;
    implementations.reserve(type.subTypes.count());
    foreach (const TLSubType &subType, type.subTypes) {
        const QString caseImplementation = generateSubtypeCode(argName, subType);
        const int implementationIndex = implementations.indexOf(caseImplementation);
        if (implementationIndex >= 0) {
            implementationHash.insert(subType.name, implementationIndex);
        } else {
            implementations.append(caseImplementation);
            implementationHash.insert(subType.name, implementations.count() - 1);
        }
    }
    for (int i = 0; i < implementations.count(); ++i) {
        foreach (const TLSubType &subType, type.subTypes) {
            if (implementationHash.value(subType.name) == i) {
                code.append(QString("%1case %2::%3:\n").arg(spacing, tlValueName, subType.name));
            }
        }
        code.append(implementations.at(i));
    }
    code.append(end(argName));
    return code;
}

QString Generator::generateStreamReadOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    argName += QLatin1String("Value");

    return spacing + QString("%1 &operator>>(%2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString Generator::generateStreamReadFreeOperatorDeclaration(const NameWithEntityType *type)
{
    QString argName = removePrefix(type->name);
    argName[0] = argName.at(0).toLower();
    argName += type->entityType();
    // CTelegramStream &operator>>(CTelegramStream &stream, TLAccountDaysTTL &accountDaysTTLValue);
    return QString("%1 &operator>>(%1 &stream, %2 &%3);\n").arg(streamClassName).arg(type->name).arg(argName);
}

QString Generator::generateStreamReadOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, streamReadImplementationHead, streamReadPerTypeImplementation, streamReadImplementationEnd);
}

QString Generator::generateStreamReadVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator>>(TLVector<%2> &v);")).arg(streamClassName, type);
}

QString Generator::generateStreamWriteOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    argName += QLatin1String("Value");
    return spacing + QString("%1 &operator<<(const %2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString Generator::generateStreamWriteFreeOperatorDeclaration(const NameWithEntityType *type)
{
    QString argName = removePrefix(type->name);
    argName[0] = argName.at(0).toLower();
    argName += type->entityType();
    // CTelegramStream &operator<<(CTelegramStream &stream, const TLFunctions::TLAuthSendCode &function)
    return QString("%1 &operator<<(%1 &stream, const %2 &%3);\n").arg(streamClassName).arg(type->name).arg(argName);
}

QString Generator::generateStreamWriteOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, streamWriteImplementationHead, streamWritePerTypeImplementation, streamWriteImplementationEnd);
}

QString Generator::generateStreamWriteFreeOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, streamWriteFreeImplementationHead, streamWritePerTypeFreeImplementation, streamWriteFreeImplementationEnd);
}

QString Generator::generateStreamWriteVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator<<(const TLVector<%2> &v);")).arg(streamClassName).arg(type);
}

QString Generator::generateDebugWriteOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    argName += QLatin1String("Value");
    return QString("QDebug operator<<(QDebug d, const %1 &%2);\n").arg(type.name).arg(argName);
}

QString Generator::debugOperatorImplementationHead(const QString &argName, const QString &typeName)
{
    Q_UNUSED(argName)
    QString code;
    code += QString("QDebug operator<<(QDebug d, const %1 &type)\n{\n").arg(typeName);
    code += spacing + QStringLiteral("d.noquote().nospace();\n");
    code += spacing + QString("d << \"%1(\" << type.tlType << \") {\";\n").arg(typeName);
    code += spacing + QStringLiteral("Spacer spacer;\n");
    code += spacing + QLatin1String("switch (type.tlType) {\n");
    return code;
}

QString Generator::debugOperatorImplementationEnd(const QString &argName)
{
    Q_UNUSED(argName)
    QString code;
    code += spacing + QLatin1String("default:\n");
    code += doubleSpacing + QLatin1String("break;\n");
    code += spacing + QLatin1String("}\n");
    code += spacing + QLatin1String("d << spacer.outerSpaces() << \"}\";\n\n");
    code += spacing + QLatin1String("return d;\n}\n\n");
    return code;
}

QString Generator::debugOperatorPerTypeImplementation(const QString &argName, const TLSubType &subType)
{
    Q_UNUSED(argName)
    QString code;
    foreach (const TLParam &member, subType.members) {
        QString typeDebugStatement = QStringLiteral("type.%1");
        if (member.type().contains(QLatin1String("QByteArray"))) {
            typeDebugStatement = QStringLiteral("type.%1.toHex()");
        }
        typeDebugStatement = typeDebugStatement.arg(member.getAlias());
        if (member.dependOnFlag()) {
            if (member.type() == tlTrueType) {
                continue;
            }
            code += doubleSpacing + QString("if (type.%1 & 1 << %2) {\n").arg(member.flagMember).arg(member.flagBit);
            code += doubleSpacing + spacing + QString("d << spacer.innerSpaces() << \"%1: \" << %2 <<\"\\n\";\n").arg(member.getAlias(), typeDebugStatement);
            code += doubleSpacing + QLatin1Literal("}\n");
        } else {
            code += doubleSpacing + QString("d << spacer.innerSpaces() << \"%1: \" << %2 <<\"\\n\";\n").arg(member.getAlias(), typeDebugStatement);
        }
    }
    code += doubleSpacing + QLatin1String("break;\n");
    return code;
}

QString Generator::generateDebugWriteOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, debugOperatorImplementationHead, debugOperatorPerTypeImplementation, debugOperatorImplementationEnd);
//    QDebug operator << (QDebug d, const TLUpdatesState &type) {
//        d << "TLUpdatesState(" << type.tlType << ")";
//        d << "{";
//        switch (type.tlType) {
//        case TLValue::UpdatesState:
//            d << "pts:" << type.pts;
//            d << "qts:" << type.qts;
//            d << "date:" << type.date;
//            d << "seq:" << type.seq;
//            d << "unreadCount:" << type.unreadCount;
//            break;
//        default:
//            break;
//        }
//        d << "}";

//        return d;
//    }
}

QString Generator::generateConnectionMethodDeclaration(const TLMethod &method)
{
    return spacing + QString("quint64 %1(%2);\n").arg(method.name).arg(formatMethodParams(method));
}

QString Generator::generateConnectionMethodDefinition(const TLMethod &method, QStringList &usedTypes)
{
    QString result;
    result += QString("quint64 %1::%2(%3)\n{\n").arg(methodsClassName).arg(method.name).arg(formatMethodParams(method));
    result += spacing + QLatin1String("QByteArray output;\n");
    result += spacing + streamClassName + QLatin1String(" outputStream(&output, /* write */ true);\n");

    result += spacing + QString("outputStream << %1::%2;\n").arg(tlValueName, formatName(method.name, FirstLetterCase::Upper));

    foreach (const TLParam &param, method.params) {
        if (param.dependOnFlag()) {
            if (param.type() == tlTrueType) {
                result += spacing + QString("// (%1 & 1 << %2) stands for %3 \"true\" value\n").arg(param.flagMember).arg(param.flagBit).arg(param.getAlias());
            } else {
                result += spacing + QString("if (%1 & 1 << %2) {\n").arg(param.flagMember).arg(param.flagBit);
                result += spacing + spacing + QString("outputStream << %1;\n").arg(param.getAlias());
                result += spacing + QLatin1String("}\n");
            }
        } else {
            result += spacing + QString("outputStream << %1;\n").arg(param.getAlias());
        }

        if (!nativeTypes.contains(param.bareType())) {
            usedTypes.append(param.type());
        }
    }

    result += spacing + QLatin1String("return sendEncryptedPackage(output);\n}\n\n");

    return result;
}

QString Generator::generateRpcProcessSwitchCase(const TLMethod &method)
{
    static const QString codeTemplate = QStringLiteral(
                "        case %1::%2:\n"
                "            process%2(&context);\n"
                "            break;\n"
                );
    return codeTemplate.arg(tlValueName, method.nameFirstCapital());
}

QString Generator::generateRpcProcessDeclaration(const TLMethod &method)
{
    return spacing + QString("void process%1(RpcProcessingContext *context);\n").arg(method.nameFirstCapital());
}

QString Generator::generateRpcProcessSampleDefinition(const TLMethod &method)
{
    QString result;
    result += QString("void %1::process%2(RpcProcessingContext *context)\n{\n").arg(methodsClassName, method.nameFirstCapital());
    result += spacing + QStringLiteral("qWarning() << Q_FUNC_INFO << \"Is not implemented yet\";\n");
    if (podTypes.contains(method.type)) {
        result += spacing + QStringLiteral("TLValue result; // %1\n").arg(method.type);
        result += spacing + QStringLiteral("context->inputStream() >> result;\n");
        result += spacing + QStringLiteral("context->setReadCode(result);\n");
    } else {
        result += spacing + QStringLiteral("%1 result;\n").arg(method.type);
        result += spacing + QStringLiteral("context->readRpcResult(&result);\n");
    }

    result += QStringLiteral("}\n\n");
    return result;
}

QString Generator::generateDebugRpcParse(const TLMethod &method)
{
    QString result;

    result += spacing + QString("case %1::%2: {\n").arg(tlValueName, formatName(method.name, FirstLetterCase::Upper));

    QString debugLine = QStringLiteral("qDebug() << request");

    foreach (const TLParam &param, method.params) {
        if (param.dependOnFlag()) {
            return QString();
        }
        if (param.type().startsWith(QLatin1String("TLType"))) {
            return QString();
        }
        result += spacing + spacing + QString("%1 %2;\n").arg(param.type()).arg(param.getAlias());
        result += spacing + spacing + QString("stream >> %1;\n").arg(param.getAlias());
        debugLine += QString(" << \"%1\" << %1").arg(param.getAlias());
    }

    result += spacing + spacing + debugLine + QLatin1String(";\n");
    result += spacing + QLatin1String("}\n");
    result += spacing + spacing + QLatin1String("break;\n\n");

    return result;
}

QStringList Generator::reorderLinesAsExist(QStringList newLines, QStringList existLines)
{
    QMutableListIterator<QString> existLineIt(existLines);
    while (existLineIt.hasNext()) {
        const QString value = existLineIt.next();
        const int index = newLines.indexOf(value);
        if (index >= 0) {
            newLines.removeAt(index);
        } else {
            existLineIt.remove();
        }
    }
    return existLines + newLines;
}

struct TypeTreeItem
{
    TypeTreeItem() { }
    TypeTreeItem(const QString &type) :
        typeName(type)
    {
    }

    QString typeName;
    QVector<TypeTreeItem*> dependencies;
    void ensureDependence(TypeTreeItem *item) {
        if (dependencies.contains(item)) {
            return;
        }
        dependencies.append(item);
    }
};

QList<TLType> Generator::solveTypes(QMap<QString, TLType> types, QMap<QString, TLType> *unresolved)
{
    QStringList solvedTypesNames = nativeTypes;
    solvedTypesNames.append(tlValueName);

    { // Bake types
        for (const QString &typeName : types.keys()) {
            TLType &type = types[typeName];
            QHash<QString,QString> members;
            // Bake member types
            for (const TLSubType &subType : type.subTypes) {
                for (const TLParam &member : subType.members) {
                    if (members.contains(member.getName())) {
                        if (members.value(member.getName()) == member.type()) {
                            continue;
                        }
                    }
                    members.insertMulti(member.getName(), member.type());
                    if (member.bareType() == type.name) {
                        type.setSelfReferenced(true);
                    }
                }
            }

            // Bake conflicted member aliases
            for (TLSubType &subType : type.subTypes) {
                for (TLParam &member : subType.members) {
                    if (members.values(member.getName()).count() > 1) {
                        QString typeWithoutTL = removeTypePrefix(member.bareType());
                        typeWithoutTL = removeWord(typeWithoutTL, member.getName());
                        if (member.getName().compare(typeWithoutTL, Qt::CaseInsensitive) != 0) {
                            if (member.isVector()) {
                                member.setAlias(formatName({typeWithoutTL, member.getName(), QStringLiteral("Vector")}, FirstLetterCase::Lower));
                            } else {
                                member.setAlias(formatName({typeWithoutTL, member.getName()}, FirstLetterCase::Lower));
                            }
                        }
                    }
                }
            }
        }

        // Bake access by pointer
        for (const QString &typeName : types.keys()) {
            TLType &type = types[typeName];

            for (TLSubType &subType : type.subTypes) {
                for (TLParam &member : subType.members) {
                    if (types.value(member.bareType()).isSelfReferenced()) {
                        member.setAccessByPointer(true);
                    }
                }
            }
        }
    }

    QVector<TypeTreeItem> typeTree;
    { // Setup the tree
        typeTree.reserve(types.count() + solvedTypesNames.count());
        QHash<QString,TypeTreeItem*> typeItemHash;
        typeItemHash.reserve(typeTree.count());
        for (const QString &typeName : types.keys() + solvedTypesNames) {
            typeTree.append(typeName);
            typeItemHash.insert(typeName, &typeTree.last());
        }

        for (const QString &typeName : types.keys()) {
            const TLType &type = types.value(typeName);
            TypeTreeItem *typeItem = typeItemHash.value(typeName);

            foreach (const TLSubType &subType, type.subTypes) {
                foreach (const TLParam &member, subType.members) {
                    TypeTreeItem *dep = typeItemHash.value(member.bareType());
                    if (!dep) {
                        qWarning() << "Type with name" << member.bareType() << "not found!";
                    }
                    typeItem->ensureDependence(dep);
                }
            }
        }
    }

    QList<TLType> solvedTypes;
    { // Solve!
        QVector<TypeTreeItem*> notSolvedTypes;
        notSolvedTypes.reserve(typeTree.count());
        solvedTypes.reserve(typeTree.count());

        for (TypeTreeItem &item : typeTree) {
            if (!solvedTypesNames.contains(item.typeName)) {
                notSolvedTypes.append(&item);
            }
        }

        while (!notSolvedTypes.isEmpty()) {
            bool hasSolved = false;
            auto currentItemIt = notSolvedTypes.begin();
            while (currentItemIt != notSolvedTypes.end()) {
                TypeTreeItem *item = *currentItemIt;
                bool solved = true;
                for (TypeTreeItem *dependence : item->dependencies) {
                    if (item == dependence) {
                        continue;
                    }
                    if (!notSolvedTypes.contains(dependence)) {
                        // Already solved
                        continue;
                    }
                    solved = false;
                    break;
                }
                if (solved) {
                    const TLType &type = types.value(item->typeName);
                    solvedTypes.append(type);
                    hasSolved = true;
                    currentItemIt = notSolvedTypes.erase(currentItemIt);
                } else {
                    ++currentItemIt;
                }
            }
            if (!hasSolved) {
                // Unable to solve any one type
                break;
            }
        }

        QVector<TypeTreeItem*> notSolvedEnds = notSolvedTypes;
        {
            auto currentItemIt = notSolvedEnds.begin();
            while (currentItemIt != notSolvedEnds.end()) {
                TypeTreeItem *item = *currentItemIt;
                bool hasNotSolvedDeps = false;
                for (TypeTreeItem *dependence : item->dependencies) {
                    if (notSolvedTypes.contains(dependence)) {
                        hasNotSolvedDeps = true;
                        break;
                    }
                }
                if (hasNotSolvedDeps) {
                    // This item depends on an another one, so it is not a end point
                    currentItemIt = notSolvedEnds.erase(currentItemIt);
                } else {
                    ++currentItemIt;
                }
            }
        }

        for (const TypeTreeItem *item : notSolvedEnds) {
            if (unresolved) {
                const TLType &type = types.value(item->typeName);
                unresolved->insert(type.name, type);
            }

            qDebug() << "Not solved ends:" << item->typeName;
            for (TypeTreeItem *child : item->dependencies) {
                qDebug() << "    Sub member:" << child->typeName;
            }
        }
    }

    return solvedTypes;
}

void Generator::getUsedAndVectorTypes(QStringList &usedTypes, QStringList &vectors) const
{
    QStringList newUsedTypes = usedTypes;

    while (!newUsedTypes.isEmpty()) {
        QStringList veryNewTypes;
        foreach (const QString &type, newUsedTypes) {
            if (!m_types.contains(type)) {
                QString bareType = getTypeOrVectorType(type);
                if (nativeTypes.contains(bareType)) {
                    continue;
                }
                if (bareType != type) { // Vector
                    if (!vectors.contains(bareType)) {
                        vectors.append(bareType);
                    }
                }
                if (usedTypes.contains(bareType) || veryNewTypes.contains(bareType)) {
                    continue;
                }
                veryNewTypes.append(bareType);
                continue;
            }

            const TLType t = m_types.value(type);

            foreach (const TLSubType &sub, t.subTypes) {
                foreach (const TLParam &member, sub.members) {
                    QString memberType = getTypeOrVectorType(member.type());

                    if (nativeTypes.contains(memberType)) {
                        continue;
                    }

                    if (memberType != member.type()) { // Vector
                        if (!vectors.contains(memberType)) {
                            vectors.append(memberType);
                        }
                    }
                    if (usedTypes.contains(memberType)) {
                        continue;
                    }

                    veryNewTypes.append(memberType);
                }
            }
        }

        usedTypes.append(veryNewTypes);
        newUsedTypes = veryNewTypes;
    }
}

Generator::Generator() :
    m_addSpecSources(false)
{
}

bool Generator::loadFromJson(const QByteArray &data)
{
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        return false;
    }
    m_types = readTypesJson(document);
    m_functions = readFunctionsJson(document);
    m_groups.append(m_types.keys());
    m_groups.append(m_functions.keys());
    return true;
}

enum EntryType {
    EntryTypedef,
    EntryFunction
};

bool Generator::loadFromText(const QByteArray &data)
{
    QTextStream input(data);
    EntryType entryType = EntryTypedef;
    m_groups.append(QStringList());

    int currentLine = 0;
    while (!input.atEnd()) {
        QString line = input.readLine();
        ++currentLine;

        if (line == QLatin1String("---functions---")) {
            entryType = EntryFunction;
            if (!m_groups.last().isEmpty()) {
                m_groups.append(QStringList());
            }
            continue;
        }

        if (line == QLatin1String("---types---")) {
            entryType = EntryTypedef;
            if (!m_groups.last().isEmpty()) {
                m_groups.append(QStringList());
            }
            continue;
        }

        line = line.section(QLatin1String("//"), 0, 0);
        if (line.simplified().isEmpty() || (line.startsWith(QLatin1String("---")) && line.endsWith(QLatin1String("---")))) {
            continue;
        }

        LineParseResult parseResult = parseLine(line);
        if (!parseResult.isValid()) {
            printf("Bad string: %s (line %d)\n", line.toLocal8Bit().constData(), currentLine);
        }

        const QString typeName = formatType(parseResult.typeName);
        if (entryType == EntryTypedef) {
            const QString predicateName = formatName(parseResult.predicateName, FirstLetterCase::Upper);
            if (!m_types.contains(typeName)) {
                m_groups.last().append(typeName);
            }
            TLType tlType = m_types.value(typeName);
            tlType.name = typeName;

            TLSubType tlSubType;
            tlSubType.name = predicateName;
            tlSubType.id = parseResult.predicateId;
            tlSubType.members.append(parseResult.params);
            tlSubType.source = line;

            tlType.subTypes.append(tlSubType);
            m_types.insert(typeName, tlType);
        } else if (entryType == EntryFunction) {
            const QString functionName = removeSeparators(parseResult.predicateName);
            if (!m_functions.contains(functionName)) {
                m_groups.last().append(functionName);
            }
            TLMethod tlMethod;
            tlMethod.name = functionName;
            tlMethod.id = parseResult.predicateId;
            tlMethod.type = typeName;
            tlMethod.params.append(parseResult.params);
            tlMethod.source = line;

            m_functions.insert(functionName, tlMethod);
        }
    }

    return true;
}

bool Generator::resolveTypes()
{
    QMap<QString, TLType> unresolved;
    m_solvedTypes = solveTypes(m_types, &unresolved);

    if (!unresolved.isEmpty()) {
        qDebug() << "Unresolved:" << unresolved.count() << unresolved;
    }
    return unresolved.isEmpty() && !m_solvedTypes.isEmpty();
}

void Generator::setExistsRpcProcessDefinitions(const QString &code)
{
    existsCodeRpcProcessDefinitions = code;
}

void Generator::generate()
{
    codeOfTLValues.clear();
    codeOfTLTypes.clear();
    codeStreamReadDeclarations.clear();
    codeStreamReadDefinitions.clear();
    codeStreamReadTemplateInstancing.clear();
    codeStreamWriteDeclarations.clear();
    codeStreamWriteDefinitions.clear();
    codeStreamWriteTemplateInstancing.clear();
    codeConnectionDeclarations.clear();
    codeConnectionDefinitions.clear();
    codeRpcProcessDeclarations.clear();
    codeRpcProcessDefinitions.clear();
    codeRpcProcessSwitchCases.clear();
    codeRpcProcessSwitchUpdatesCases.clear();
    codeDebugWriteDeclarations.clear();
    codeDebugWriteDefinitions.clear();
    codeDebugRpcParse.clear();

    QStringList typesUsedForWrite;
    QStringList vectorUsedForWrite;
    QStringList vectorUsedForExtraWrite;

    static const QStringList whiteList = QStringList()
            << QLatin1String("auth")
            << QLatin1String("account")
            << QLatin1String("help")
            << QLatin1String("messages")
            << QLatin1String("contacts")
            << QLatin1String("channels")
            << QLatin1String("updates")
            << QLatin1String("upload")
            << QLatin1String("users");

    QStringList usedTypes;
    foreach (const TLMethod &method, m_functions) {
        bool addImplementation = false;
        foreach (const QString &white, whiteList) {
            if (method.name.startsWith(white)) {
                addImplementation = true;
                break;
            }
        }
        if (addImplementation) {
            codeConnectionDeclarations.append(generateConnectionMethodDeclaration(method));
            codeConnectionDefinitions.append(generateConnectionMethodDefinition(method, typesUsedForWrite));

            if (method.type == QLatin1String("TLUpdates")) {
                codeRpcProcessSwitchUpdatesCases.append(QStringLiteral("        case %1::%2:\n").arg(tlValueName, method.nameFirstCapital()));
            } else {
                codeRpcProcessDeclarations.append(generateRpcProcessDeclaration(method));

                static const auto addDefinition = [&](const TLMethod &method) {
                    const QString signature = QString("void %1::process%2(RpcProcessingContext *context)\n").arg(methodsClassName, method.nameFirstCapital());
                    int index = existsCodeRpcProcessDefinitions.indexOf(signature);
                    if (index >= 0) {
                        int indexOfEnd = existsCodeRpcProcessDefinitions.indexOf(QLatin1String("\n}\n"), index);

                        if (indexOfEnd > 0) {
                            return existsCodeRpcProcessDefinitions.mid(index, indexOfEnd - index) + QLatin1String("\n}\n\n");
                        } else {
                            qWarning() << "Invalid input";
                        }
                    }
                    return generateRpcProcessSampleDefinition(method);
                };

                codeRpcProcessDefinitions.append(addDefinition(method));
                codeRpcProcessSwitchCases.append(generateRpcProcessSwitchCase(method));
            }
            if (!usedTypes.contains(method.type)) {
                usedTypes.append(method.type);
            }
        } else {
            // It's still necessary to generate definition to figure out used stream write operators
            generateConnectionMethodDefinition(method, typesUsedForWrite);
        }
    }

    typesUsedForWrite.removeDuplicates();

    for (int i = 0; i < typesUsedForWrite.count(); ++i) {
        const QString t = getTypeOrVectorType(typesUsedForWrite.at(i));

        if (typesUsedForWrite.at(i) != t) {
            vectorUsedForWrite.append(t);
            typesUsedForWrite[i] = t;
        }
    }

    foreach (const TLType &type, m_solvedTypes) {
        if (nativeTypes.contains(type.name)) {
            continue;
        }

        if (typesBlackList.contains(type.name)) {
            continue;
        }

        if (usedTypes.contains(type.name)) {
            continue;
        }
        usedTypes += type.name;
    }

    QStringList vectorUsedForRead;
    getUsedAndVectorTypes(usedTypes, vectorUsedForRead);
    getUsedAndVectorTypes(typesUsedForWrite, vectorUsedForWrite);

    QStringList newWriteInstances;
    foreach (const QString &str, vectorUsedForWrite) {
        newWriteInstances.append(generateStreamWriteVectorTemplate(str));
    }
    QStringList existWriteInstances = existsStreamWriteTemplateInstancing.split(QLatin1Char('\n'), QString::SkipEmptyParts);
    codeStreamWriteTemplateInstancing = reorderLinesAsExist(newWriteInstances, existWriteInstances).join(QLatin1Char('\n'));
    if (!codeStreamWriteTemplateInstancing.isEmpty()) {
        codeStreamWriteTemplateInstancing.append(QLatin1Char('\n'));
    }

    foreach (const QString &vector, vectorUsedForWrite) {
        if (!vectorUsedForRead.contains(vector)) {
            vectorUsedForRead.append(vector);
        }
    }

    QStringList newReadInstances;
    foreach (const QString &str, vectorUsedForRead) {
        newReadInstances.append(generateStreamReadVectorTemplate(str));
    }
    QStringList existReadInstances = existsStreamReadTemplateInstancing.split(QLatin1Char('\n'), QString::SkipEmptyParts);
    codeStreamReadTemplateInstancing = reorderLinesAsExist(newReadInstances, existReadInstances).join(QLatin1Char('\n'));
    if (!codeStreamReadTemplateInstancing.isEmpty()) {
        codeStreamReadTemplateInstancing.append(QLatin1Char('\n'));
    }

    foreach (const QStringList &group, m_groups) {
        if (group.isEmpty()) {
            continue;
        }
        if (m_types.contains(group.first())) {
            codeOfTLValues.append(QLatin1String("        // Types\n"));
            foreach (const QString &typeName, group) {
                if (!m_types.contains(typeName)) {
                    qCritical() << "Name of group item not found in types map";
                    return;
                }
                const TLType &type = m_types.value(typeName);
                codeOfTLValues.append(generateTLValuesDefinition(type));
            }
        } else if (m_functions.contains(group.first())) {
            codeOfTLValues.append(QLatin1String("        // Methods\n"));
            foreach (const QString &typeName, group) {
                if (!m_functions.contains(typeName)) {
                    qCritical() << "Name of group item not found in types map";
                    return;
                }
                const TLMethod &method = m_functions.value(typeName);
                codeOfTLValues.append(generateTLValuesDefinition(method));
            }
        } else {
            qCritical() << "Name of group item is neither a type or a method";
            return;
        }
    }

    foreach (const TLMethod &method, m_functions) {
        codeDebugRpcParse.append(generateDebugRpcParse(method));
    }

    foreach (const TLType &type, m_solvedTypes) {
        if (nativeTypes.contains(type.name)) {
            continue;
        }

        if (typesBlackList.contains(type.name)) {
            continue;
        }

        codeOfTLTypes.append(generateTLTypeDefinition(type, m_addSpecSources));

        codeStreamReadDeclarations.append(generateStreamReadOperatorDeclaration(type));
        codeStreamReadDefinitions.append(generateStreamReadOperatorDefinition(type));

        if (typesUsedForWrite.contains(type.name)) {
            codeStreamWriteDeclarations.append(generateStreamWriteOperatorDeclaration(type));
            codeStreamWriteDefinitions.append(generateStreamWriteOperatorDefinition(type));
        } else {
            codeStreamExtraWriteDeclarations.append(generateStreamWriteFreeOperatorDeclaration(&type));
            codeStreamExtraWriteDefinitions .append(generateStreamWriteFreeOperatorDefinition(type));
        }

        codeDebugWriteDeclarations.append(generateDebugWriteOperatorDeclaration(type));
        codeDebugWriteDefinitions .append(generateDebugWriteOperatorDefinition(type));
    }

}

QByteArray Generator::getPredicateForCrc32(const QByteArray &sourceLine)
{
    static const QRegularExpression expr("([a-zA-Z\\.0-9_]+)(#[0-9a-f]+)?([^=]*)=\\s*([a-zA-Z\\.<>0-9_]+);");
    const QRegularExpressionMatch match = expr.match(QString::fromLatin1(sourceLine));
    if (!match.isValid()) {
        return QByteArray();
    }
    static const QRegularExpression flags(QStringLiteral(" [a-zA-Z0-9_]+\\:flags\\.[0-9]+\\?true"));
    QString str = match.captured(1) + match.captured(3) + QStringLiteral("= ") + match.captured(4);
    str.replace(flags, QString());
    QByteArray arr = str.toLatin1();
    for (char &c : arr) {
        switch (c) {
        case '<':
        case '>':
        case '(':
        case ')':
        case '{':
        case '}':
            c = ' ';
        default:
            break;
        }
    }
    arr.replace(QByteArrayLiteral(":bytes "), QByteArrayLiteral(":string "));
    arr.replace(QByteArrayLiteral("?bytes "), QByteArrayLiteral("?string "));
    return arr.simplified();
}

quint32 Generator::getCrc32(const QByteArray &bytes)
{
    return crc32(0l, reinterpret_cast<const unsigned char*>(bytes.constData()), bytes.size());
}

Generator::LineParseResult Generator::parseLine(const QString &line)
{
    const int sectionsSplitterIndex = line.indexOf(QLatin1Char('='));
    const QStringRef basePart = line.leftRef(sectionsSplitterIndex).trimmed();
    const QStringRef typePart = line.midRef(sectionsSplitterIndex + 2, line.size() - 3 - sectionsSplitterIndex);
    const int hashIndex = basePart.indexOf(QLatin1Char('#'));
    if ((hashIndex == 0) || (hashIndex + 1 > basePart.length())) {
        return LineParseResult();
    }

    quint32 predicateId = 0;
    QStringRef predicateBaseName;
    const QByteArray barePredicate = getPredicateForCrc32(line.toLatin1());
    const quint32 calculatedPredicateId = getCrc32(barePredicate);

    if (hashIndex > 0) {
        QStringRef predicateValue = basePart.mid(hashIndex + 1);
        const int endOfValue = predicateValue.indexOf(QChar(' '));
        predicateBaseName = basePart.left(hashIndex);
        if (endOfValue > 0) {
            predicateValue = predicateValue.left(endOfValue);
        }
        bool ok;
        predicateId = predicateValue.toUInt(&ok, 16);
        if (!ok) {
            qWarning() << "parseLine: Could't read predicate id from line" << line;
            return LineParseResult();
        }

        if (predicateId != calculatedPredicateId) {
            qWarning() << "parseLine: the read predicate is different from the calculated" << QString("%1 vs %2")
                          .arg(predicateId, /* fieldwidth */ 8, /* base */ 16, QLatin1Char('0'))
                          .arg(calculatedPredicateId, /* fieldwidth */ 8, /* base */ 16, QLatin1Char('0'))
                       << "for line" << line;
        }
    } else {
        predicateId = calculatedPredicateId;
        const int endOfName = basePart.indexOf(QLatin1Char(' '));
        predicateBaseName = basePart.left(endOfName);
    }

    bool skipParams = false;
    if (basePart.contains('{') && basePart.contains('}')) {
        const int templateBegin = basePart.indexOf(QLatin1Char('{'));
        const int templateEnd = basePart.indexOf(QLatin1Char('}'));
        QStringRef templ = basePart.mid(templateBegin + 1, templateEnd - templateBegin - 1);
        printf("Read template %s, type %s.\n", templ.toLatin1().constData(), predicateBaseName.toLatin1().constData());
        skipParams = true;
    }

    QList<TLParam> tlParams;
    if (!skipParams) {
        QVector<QStringRef> params = basePart.split(QLatin1Char(' '), QString::SkipEmptyParts);
        params.removeFirst(); // The first part is predicate name + id.

        foreach (const QStringRef &paramValue, params) {
            QVector<QStringRef> nameAndType = paramValue.split(QLatin1Char(':'));
            const QString paramName = formatMember(nameAndType.first().toString(), {{ "parentType", predicateBaseName.toString() }} );
            const QString paramType = formatType(nameAndType.last().toString());
            QString flagMember;
            qint8 flagsBit = flagBitForMember(nameAndType.last(), &flagMember);

            tlParams << TLParam(paramName, paramType, flagsBit);
            tlParams.last().flagMember = flagMember;
        }
    }
    LineParseResult result;
    result.predicateName = predicateBaseName.toString();
    result.predicateId = predicateId;
    result.typeName = typePart.trimmed().toString();
    result.params = tlParams;

    return result;
}

void Generator::setAddSpecSources(bool addSources)
{
    m_addSpecSources = addSources;
}

QString Generator::removeWord(QString input, QString word)
{
    if (input.isEmpty()) {
        return QString();
    }
    if (word.isEmpty()) {
        return input;
    }
    const bool firstIsLower = input.at(0).isLower();
    input[0] = input.at(0).toUpper();
    word[0] = word.at(0).toUpper();
    const QRegularExpression regexp(QStringLiteral("[A-Z][^A-Z]*"));
    QRegularExpressionMatchIterator match = regexp.globalMatch(input);
    QStringList words;
    while(match.hasNext()) {
        words.append(match.next().captured());
    }
    words.removeAll(word);
    if (words.isEmpty()) {
        return QString();
    }
    QString out = words.join(QString());
    if (firstIsLower) {
        out[0] = out.at(0).toLower();
    }
    return out;
}
