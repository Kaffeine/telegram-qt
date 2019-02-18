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

#include <QLoggingCategory>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>

#include <QTextStream>

#include <zlib.h>

//Q_LOGGING_CATEGORY(c_loggingGenerator, "telegram.generator", QtDebugMsg)
Q_LOGGING_CATEGORY(c_loggingTextParser, "telegram.generator.textParser", QtWarningMsg)
Q_LOGGING_CATEGORY(c_loggingTlValues, "telegram.generator.values", QtDebugMsg)

static const QString tlPrefix = QLatin1String("TL");
static const QString tlValueName = tlPrefix + QLatin1String("Value");
static const QString tlTypeMember = QLatin1String("tlType");
static const QString tlVectorType = QLatin1String("TLVector");
static const QString functionsType = QLatin1String("TLFunctions");
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
static const QLatin1String c_internalExportMacro = QLatin1String("TELEGRAMQT_INTERNAL_EXPORT");

static const QStringList methodBlackList = {
    QStringLiteral("contest"),
};

static const QString c_phonePrivacyFilter = QStringLiteral("Telegram::Utils::maskPhoneNumber(%1)");
static const QString c_numberPrivacyFilter = QStringLiteral("Telegram::Utils::maskNumber(%1)");
static const QHash<QString,QString> c_privacyFilter = {
    { QLatin1String("phone"), c_phonePrivacyFilter },
    { QLatin1String("phoneNumber"), c_phonePrivacyFilter },
    { QLatin1String("accessHash"), c_numberPrivacyFilter },
};

QString Generator::spacing = QString(4, QLatin1Char(' '));
QString Generator::doubleSpacing = Generator::spacing + Generator::spacing;

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

QString processOperationType(const QString &typeName)
{
    if (typeName == QLatin1String("bool")) {
        return tlPrefix + QLatin1String("Bool");
    }
    return typeName;
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

QString Generator::formatName(const QStringList &nameParts, const FormatOptions options)
{
    if (nameParts.isEmpty()) {
        return QString();
    }

    bool first = true;
    bool skipVeryFirst = options & FormatOption::SkipFirstWord;
    QString result;
    for (QString part : nameParts) {
        if (part.isEmpty()) {
            continue;
        }
        if (skipVeryFirst) {
            skipVeryFirst = false;
            continue;
        }
        if (first) {
            first = false;
        } else {
            part[0] = part.at(0).toUpper();
        }
        result.append(part);
    }
    if (result.isEmpty()) {
        return result;
    }
    // TODO: Move removeSeparators out of the method
    if (true || options & FormatOption::RemoveSeparators) {
        result = removeSeparators(result);
    }
    if (options & FormatOption::UpperCaseFirstLetter) {
        result[0] = result.at(0).toUpper();
    } else if (options & FormatOption::LowerCaseFirstLetter) {
        result[0] = result.at(0).toLower();
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

QString Generator::joinLinesWithPrepend(const QStringList &lines, const QString &prep, const QString &sep)
{
    if (lines.isEmpty()) {
        return QString();
    }
    QString result;
    int size = (prep.size() + sep.size()) * lines.count();
    for (const QString &line : lines) {
        size += line.size();
    }
    result.reserve(size);
    for (const QString &line : lines) {
        result.append(prep + line + sep);
    }
    return result;
}

QString Generator::formatName(const QString &name, const FormatOptions options)
{
    if (name.isEmpty()) {
        return QString();
    }
    if (name.startsWith(tlPrefix) && (options & FormatOption::SkipTl)) {
        return formatName(getWords(name.mid(tlPrefix.length())), options);
    }
    return formatName(getWords(name), options);
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

        const QString predicateName = formatName(obj.value("predicate").toString(), FormatOption::UpperCaseFirstLetter);
        const quint32 predicateId = obj.value("id").toString().toInt();
        const QString typeName = formatType(obj.value("type").toString());

        TLType tlType = types.value(typeName);
        tlType.name = typeName;

        TLSubType tlSubType;
        tlSubType.name = predicateName;
        tlSubType.predicateId = predicateId;

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
        tlMethod.predicateId = methodId;
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

QString Predicate::predicateName() const
{
    if (name.startsWith(tlPrefix)) {
        return Generator::formatName(name.mid(tlPrefix.length()), Generator::FormatOption::LowerCaseFirstLetter);
    }
    QString formatted = Generator::formatName(name, Generator::FormatOption::LowerCaseFirstLetter|Generator::FormatOption::SkipFirstWord);
    if (!formatted.isEmpty()) {
        return formatted;
    }
    return name;
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

QString Generator::generateTLValuesDefinition(const Predicate *predicate)
{
    return QString("%1 = 0x%2,\n").arg(predicate->nameFirstCapital()).arg(predicate->predicateId, 8, 0x10, QLatin1Char('0'));
}

QString Generator::generateTLTypeDefinition(const TLType &type, bool addSpecSources)
{
    QString code;
    if (type.isSelfReferenced()) {
        code.append(QStringLiteral("struct %1;\n").arg(type.name));
        code.append(QStringLiteral("using %1Ptr = TLPtr<%1>;\n\n").arg(type.name));
    }
    code.append(QString("struct %1 %2 {\n").arg(c_internalExportMacro, type.name));

    bool constExpr = true;
    static const QString specCommentPrefix = spacing + QStringLiteral("// ");
    QString specSource;
    QStringList thisTypeCases;

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
        thisTypeCases.append(QStringLiteral("case %1::%2:").arg(tlValueName, subType.name));
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.getAlias())) {
                continue;
            }

            addedMembers.append(member.getAlias());
            if (!podTypes.contains(member.type())) {
                constExpr = false;
                continue;
            }

            const QString initialValue = initTypesValues.at(podTypes.indexOf(member.type()));
        }
    }


    const QString constructor = QStringLiteral("%1() = default;\n\n").arg(type.name);
    const QString constExprSpace = QStringLiteral("constexpr ");
    if (constExpr) {
        code.append(spacing + constExprSpace + constructor);
    } else {
        code.append(spacing + constructor);
    }
    if (addSpecSources) {
        code.append(specSource);
    }

    const QString maybeCpp14ConstExpr = constExpr ? QStringLiteral("Q_DECL_RELAXED_CONSTEXPR ") : QString();
    const QString isValid = QStringLiteral("bool isValid() const { return hasType(tlType); }\n");
    code.append(spacing + maybeCpp14ConstExpr + isValid);
    code.append(spacing + QStringLiteral("Q_DECL_RELAXED_CONSTEXPR static bool hasType(const quint32 value) {\n"));
    code.append(doubleSpacing + QStringLiteral("switch (value) {\n"));
    code.append(joinLinesWithPrepend(thisTypeCases, doubleSpacing, QStringLiteral("\n")));
    code.append(QStringLiteral(
                               "            return true;\n"
                               "        default:\n"
                               "            return false;\n"
                               "        };\n"
                               "    }\n"));

    const QString memberFlags = joinLinesWithPrepend(generateTLTypeMemberFlags(type), doubleSpacing, QStringLiteral("\n"));
    if (!memberFlags.isEmpty()) {
        code.append(spacing + "enum Flags {\n");
        code.append(memberFlags);
        code.append(spacing + "};\n");
    }
    if (constExpr) {
        code.append(joinLinesWithPrepend(generateTLTypeMemberGetters(type), spacing + constExprSpace, QStringLiteral("\n")));
    } else {
        code.append(joinLinesWithPrepend(generateTLTypeMemberGetters(type), spacing, QStringLiteral("\n")));
    }
    const QString members = joinLinesWithPrepend(generateTLTypeMembers(type), spacing, QStringLiteral("\n"));
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
                    membersCode.append(QStringLiteral("%1Ptr %2;").arg(member.type(), member.getAlias()));
                }
            } else {
                if (podTypes.contains(member.type())) {
                    const QString initialValue = initTypesValues.at(podTypes.indexOf(member.type()));
                    membersCode.append(QStringLiteral("%1 %2 = %3;").arg(member.type(), member.getAlias(), initialValue));
                } else {
                    membersCode.append(QStringLiteral("%1 %2;").arg(member.type(), member.getAlias()));
                }
            }
        }
    }
    membersCode.append(QStringLiteral("%1 %2 = %1::%3;").arg(tlValueName, tlTypeMember, type.subTypes.first().name));
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

QString Generator::streamReadFunctionFreeImplementationHead(const TypedEntity *type)
{
    QString code;
    code.append(QString("%1 &operator>>(%1 &stream, %2::%3 &%4)\n{\n"
                        "    // stream >> function.tlType;\n").arg(streamClassName,
                                                                   functionsType,
                                                                   type->getEntityTLType(),
                                                                   type->variableName()));
    // CTelegramStream &operator>>(CTelegramStream &stream, TLFunctions::TLAuthCheckPassword &function)
    // {
    //     // stream >> function.tlType;
    return code;
}

QString Generator::streamReadFunctionFreeImplementationEnd()
{
    return QStringLiteral("    return stream;\n"
                          "}\n\n");
}

QString Generator::streamReadFunctionFreePerArgumentImplementation(const QString &argName, const TLParam &param)
{
    QString result;
    if (param.dependOnFlag()) {
        if (param.type() == tlTrueType) {
            result += spacing + QString("// (%1.%2 & 1 << %3) stands for %4 \"true\" value\n").arg(argName, param.flagMember).arg(param.flagBit).arg(param.getAlias());
        } else {
            result += spacing + QString("if (%1.%2 & 1 << %3) {\n").arg(argName, param.flagMember).arg(param.flagBit);
            result += spacing + spacing + QString("stream >> %1.%2;\n").arg(argName, param.getAlias());
            result += spacing + QLatin1String("}\n");
        }
    } else {
        result += spacing + QString("stream >> %1.%2;\n").arg(argName, param.getAlias());
    }
    return result;
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
    const QString argName = type.variableName();
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

QString Generator::generateStreamOperatorDefinition(const TLMethod *type, std::function<QString (const TypedEntity *type)> head,
                                                    std::function<QString (const QString &, const TLParam &)> generateSubtypeCode,
                                                    std::function<QString ()> end)
{
    QString result = head(type);
    QString paramsCode;
    foreach (const TLParam &param, type->params) {
        paramsCode += generateSubtypeCode(type->variableName(), param);
    }
    if (paramsCode.isEmpty()) {
        paramsCode = spacing + QStringLiteral("Q_UNUSED(%1)\n").arg(type->variableName());
    }
    result += paramsCode;

    result.append(end());
    return result;
}

QString Generator::streamReadOperatorDeclaration(const TypedEntity *type)
{
    QString result;
    QTextStream stream(&result);
    stream << spacing << streamClassName << " &operator>>("
           << type->getEntityTLType() << " &" << type->variableName() << ");" << endl;
    return result;
}

QString Generator::streamReadFreeOperatorDeclaration(const TypedEntity *type)
{
    // CTelegramStream &operator>>(CTelegramStream &stream, TLAccountDaysTTL &accountDaysTTLValue);
    QString result;
    QTextStream stream(&result);
    stream << streamClassName << " &operator>>(" << streamClassName << " &stream, "
           << type->getEntityTLType() << " &" << type->variableName() << ");" << endl;
    return result;
}

QString Generator::streamReadFreeOperatorDefinition(const TLMethod *method)
{
    return generateStreamOperatorDefinition(method,
                                            streamReadFunctionFreeImplementationHead,
                                            streamReadFunctionFreePerArgumentImplementation,
                                            streamReadFunctionFreeImplementationEnd);
}

QString Generator::streamReadOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type,
                                            streamReadImplementationHead,
                                            streamReadPerTypeImplementation,
                                            streamReadImplementationEnd);
}

QString Generator::streamReadVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator>>(TLVector<%2> &v);")).arg(streamClassName, type);
}

QString Generator::streamWriteOperatorDeclaration(const TLType &type)
{
    QString result;
    QTextStream stream(&result);
    stream << spacing << streamClassName << " &operator<<(const " << type.name << " &" << type.variableName() << ");" << endl;
    return result;
}

QString Generator::streamWriteFreeOperatorDeclaration(const TypedEntity *type)
{
    // CTelegramStream &operator<<(CTelegramStream &stream, const TLFunctions::TLAuthSendCode &function)
    QString result;
    QTextStream stream(&result);
    stream << c_internalExportMacro << " "
           << streamClassName << " &operator<<(" << streamClassName << " &stream, const "
           << type->getEntityTLType() << " &" << type->variableName() << ");" << endl;
    return result;
}

QString Generator::streamWriteOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, streamWriteImplementationHead, streamWritePerTypeImplementation, streamWriteImplementationEnd);
}

QString Generator::streamWriteFreeOperatorDefinition(const TLType &type)
{
    return generateStreamOperatorDefinition(type, streamWriteFreeImplementationHead, streamWritePerTypeFreeImplementation, streamWriteFreeImplementationEnd);
}

QString Generator::streamWriteVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator<<(const TLVector<%2> &v);")).arg(streamClassName).arg(type);
}

QStringList Generator::generateRpcReplyTemplates(const QString &groupName) const
{
    QString targetPrefix = groupName;
    if (targetPrefix.endsWith(QLatin1Char('s'))) {
        targetPrefix.chop(1);
    }
    QStringList result;
    for (const QString &type : m_types.keys()) {
        QString name = removePrefix(type);
        name[0] = name.at(0).toLower();
        if (!name.startsWith(targetPrefix)) {
            continue;
        }
        result.append(QStringLiteral("template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, %1 *output);").arg(type));
    }

    // template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLAccountPassword *output);
    return result;
}

QString Generator::generateDebugWriteOperatorDeclaration(const TLType &type)
{
    return c_internalExportMacro + QStringLiteral(" QDebug operator<<(QDebug d, const %1 &%2);\n")
            .arg(type.name, type.variableName());
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
    if (subType.members.isEmpty()) {
        code += doubleSpacing + "d << \" }\";\n";
        code += doubleSpacing + "return d;\n";
        return code;
    } else {
        code += doubleSpacing + "d << \"\\n\";\n";
    }
    bool hasFlags = !subType.getBoolFlags().isEmpty();

    for (const TLParam &member : subType.members) {
        QString typeDebugStatement = QStringLiteral("type.%1");
        if (member.type().contains(QLatin1String("QByteArray"))) {
            typeDebugStatement = QStringLiteral("type.%1.toHex()");
        }
        typeDebugStatement = typeDebugStatement.arg(member.getAlias());
        typeDebugStatement = c_privacyFilter.value(member.getAlias(), QStringLiteral("%1")).arg(typeDebugStatement);

        if (member.dependOnFlag()) {
            if (member.type() == tlTrueType) {
                continue;
            }
            code += doubleSpacing + QString("if (type.%1 & 1 << %2) {\n").arg(member.flagMember).arg(member.flagBit);
            code += doubleSpacing + spacing + QString("d << spacer.innerSpaces() << \"%1: \" << %2 <<\"\\n\";\n").arg(member.getAlias(), typeDebugStatement);
            code += doubleSpacing + QLatin1Literal("}\n");
        } else if (member.accessByPointer() && !member.isVector()) {
            code += doubleSpacing + QString("d << spacer.innerSpaces() << \"%1: \" << *%2 <<\"\\n\";\n").arg(member.getAlias(), typeDebugStatement);
        } else if (hasFlags && (member.getAlias() == QLatin1String("flags"))) {
            code += doubleSpacing + QString("d << spacer.innerSpaces() << \"%1: \" << %2"
                                            " << \" (\" << flagsToString(type)"
                                            " <<\")\\n\";\n").arg(member.getAlias(), typeDebugStatement);
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

    result += spacing + QString("outputStream << %1::%2;\n").arg(tlValueName, formatName(method.name, FormatOption::UpperCaseFirstLetter));

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

QString Generator::generateFunctionStructs() const
{
    QStringList result;
    for (const TLMethod &type : m_functions) {
        result.append(generateFunctionStruct(type));
    }
    return result.join(QStringLiteral("\n"));
}

QString Generator::generateFunctionStruct(const TLMethod &method)
{
    QString code;
    code.append(QStringLiteral("struct %1\n"
                               "{\n"
                               "    static constexpr %2 predicate = %2::%3;\n").arg(method.functionTypeName(), tlValueName, method.nameFirstCapital()));
    // struct TLAuthSendCode
    // {
    //     static constexpr TLValue predicate = TLValue::AuthSendCode;
    QStringList arguments;
    for (const TLParam &param : method.params) {
        if (param.dependOnFlag() && (param.type() == tlTrueType)) {
            continue;
        }

        if (podTypes.contains(param.type())) {
            const QString initialValue = initTypesValues.at(podTypes.indexOf(param.type()));
            arguments.append(QStringLiteral("%1 %2 = %3;").arg(param.type(), param.getAlias(), initialValue));
        } else if (param.isVector()) {
            arguments.append(QStringLiteral("%1<%2> %3;").arg(tlVectorType, param.bareType(), param.getAlias()));
        } else {
            arguments.append(QStringLiteral("%1 %2;").arg(param.type(), param.getAlias()));
        }
    }
    code.append(joinLinesWithPrepend(arguments, spacing, QStringLiteral("\n")));
    code.append(QStringLiteral("};\n"));
    return code;
}

Generator::MethodsCode Generator::generateFunctionStreamOperators() const
{
    MethodsCode result;
    for (const TLMethod &method : m_functions) {
        result.declarations.append(streamReadFreeOperatorDeclaration(&method));
        result.definitions.append(streamReadFreeOperatorDefinition(&method));
    }
    return result;
}

QStringList Generator::generateTypeFlagsToString() const
{
    // declaration:
    // template <typename Type>
    // QString flagsToString(const Type &instance);

    // definition:
    // template<>
    // QString flagsToString(const TLConfig &instance)
    // {
    //     const quint32 flags = instance.flags;
    //     QStringList result;

    //     if (flags & TLConfig::TmpSessions) {
    //         result << QLatin1String("TmpSessions");
    //     }
    //     if (flags & TLConfig::PhonecallsEnabled) {
    //         result << QLatin1String("PhonecallsEnabled");
    //     }
    //     if (flags & TLConfig::LangPackVersion) {
    //         result << QLatin1String("LangPackVersion");
    //     }
    //     if (flags & TLConfig::SuggestedLangCode) {
    //         result << QLatin1String("SuggestedLangCode");
    //     }
    //     return result.join(QLatin1Char('|'));
    // }

    QStringList result;

    for (const TLType &type : m_solvedTypes) {
        if (nativeTypes.contains(type.name)) {
            continue;
        }

        if (typesBlackList.contains(type.name)) {
            continue;
        }

        const QMap<quint8,QString> memberFlags = type.getBoolFlags();
        if (memberFlags.isEmpty()) {
            continue;
        }

        QString code;
        QTextStream stream(&code, QIODevice::WriteOnly);
        stream << "template<>" << endl;
        stream << "QString flagsToString(const " << type.name << " &instance)" << endl;
        stream << "{" << endl;
        stream << "    const quint32 flags = instance.flags;" << endl;
        stream << "    QStringList result;" << endl;

        for (quint8 flag : memberFlags.uniqueKeys()) {
            // if (flags & TLConfig::TmpSessions) {
            //     result << QLatin1String("TmpSessions");
            // }
            stream << "    if (flags & " << type.name << "::" << memberFlags.value(flag) << ") {" << endl;
            stream << "        result << QLatin1String(\"" << memberFlags.value(flag) << "\");" << endl;
            stream << "    }" << endl;
        }

        stream << "    if (result.isEmpty()) {" << endl;
        stream << "        return QLatin1String(\"<no bool flags>\");" << endl;
        stream << "    }" << endl;
        stream << "    return result.join(QLatin1Char('|'));" << endl;
        stream << "}" << endl;
        result.append(code);
    }
    return result;
}

QStringList Generator::serverRpcFactoryIncludes() const
{
    QStringList result;
    for (const QString &group : functionGroups()) {
        const QString firstCapital = formatName(group, Generator::FormatOption::UpperCaseFirstLetter);
        result << QStringLiteral("#include \"%1OperationFactory.hpp\"").arg(firstCapital);
    }
    return result;
}

QStringList Generator::serverRpcFactoryInitialization() const
{
    QStringList result;
    for (const QString &group : functionGroups()) {
        const QString firstCapital = formatName(group, Generator::FormatOption::UpperCaseFirstLetter);
        result << QStringLiteral("new %1OperationFactory(),").arg(firstCapital);
    }
    return result;
}

Generator::MethodsCode Generator::generateServerRpcProcessMethods(const QString &groupName) const
{
    const QString prefixFirstUpper = formatName(groupName, FormatOption::UpperCaseFirstLetter);
    const QString className = prefixFirstUpper + QStringLiteral("RpcOperation");
    MethodsCode result;
    for (const TLMethod &method : m_functions) {
        if (!method.name.startsWith(groupName)) {
            continue;
        }
        const QString predicateName = method.predicateName();

        // bool processCheckPhone(RpcProcessingContext &context);
        result.declarations.append(QString("bool process%1(RpcProcessingContext &context);").arg(method.nameFromSecondWord()));

        // bool AuthRpcOperation::processCheckPhone(RpcProcessingContext &context)
        // {
        //     setRunMethod(&AuthRpcOperation::runCheckPhone);
        //     context.inputStream() >> m_checkPhone;
        //     return true;
        // }

        const QString declaration = QStringLiteral(
                    "bool %1::process%2(RpcProcessingContext &context)\n"
                    "{\n"
                    "    setRunMethod(&%1::run%2);\n"
                    "    context.inputStream() >> m_%3;\n"
                    "    return !context.inputStream().error();\n"
                    "}\n\n"
                    ).arg(className, method.nameFromSecondWord(), predicateName);
        result.definitions.append(declaration);
    }
    return result;
}

QStringList Generator::generateServerRpcMembers(const QString &groupName) const
{
    QStringList result;
    for (const TLMethod &method : m_functions) {
        if (!method.name.startsWith(groupName)) {
            continue;
        }
        result.append(QStringLiteral("%1::%2 m_%3;").arg(functionsType, method.functionTypeName(), method.predicateName()));
    }
    // TLFunctions::TLAuthCheckPhone m_checkPhone;
    // TLFunctions::TLAuthSendCode m_sendCode;
    return result;
}

QStringList Generator::generateServerMethodForRpcFunction(const QString &groupName) const
{
    const QString prefixFirstUpper = formatName(groupName, FormatOption::UpperCaseFirstLetter);
    QStringList result;
    for (const TLMethod &method : m_functions) {
        if (!method.name.startsWith(groupName)) {
            continue;
        }
        result.append(QStringLiteral("    case %1::%2%3:\n"
                                     "        return &%2RpcOperation::process%3;\n").arg(tlValueName, prefixFirstUpper, method.nameFromSecondWord()));
    }
    // case TLValue::AuthCheckPhone:
    //     return &AuthRpcOperation::processCheckPhone;
    return result;
}

Generator::MethodsCode Generator::generateServerRpcRunMethods(const QString &groupName, const QString &previousSourceCode) const
{
    const QString prefixFirstUpper = formatName(groupName, FormatOption::UpperCaseFirstLetter);
    const QString className = prefixFirstUpper + QStringLiteral("RpcOperation");
    MethodsCode result;
    for (const TLMethod &method : m_functions) {
        if (!method.name.startsWith(groupName)) {
            continue;
        }

        // void runCheckPhone();
        result.declarations.append(QString("void run%1();").arg(method.nameFromSecondWord()));

        static const auto addDefinition = [&className](const TLMethod &method, const QString &previousCode) {
            const QString signature = QString("void %1::run%2()\n").arg(className, method.nameFromSecondWord());
            int index = previousCode.indexOf(signature);
            if (index >= 0) {
                int indexOfEnd = previousCode.indexOf(QLatin1String("\n}\n"), index);

                if (indexOfEnd > 0) {
                    QString code = previousCode.mid(index, indexOfEnd - index) + QLatin1String("\n}\n\n");
                    bool keepCustomNotImplemented = true;
                    bool notImplemented = code.contains("NotImplemented") || code.contains("not implemented");
                    if (!notImplemented || keepCustomNotImplemented) {
                        return code;
                    }
                } else {
                    qWarning() << "Invalid input";
                }
            }
            // void AuthRpcOperation::runCheckPhone()
            // {
            //     // TLFunctions::TLAuthCheckPhone &arguments = m_checkPhone;
            //     if (processNotImplementedMethod(TLValue::AuthCheckPhone)) {
            //         return;
            //     }
            //     TLAuthAuthorization result;
            //     sendRpcReply(result);
            // }
            QString definition;
            QTextStream stream(&definition);
            stream << "void " << className << "::run" << method.nameFromSecondWord() << "()" << endl;
            stream << "{" << endl;
            if (!method.params.isEmpty()) {
                stream << "    // TLFunctions::TL" << method.nameFirstCapital() << " &arguments = m_" << method.predicateName() << ";" << endl;
            }
            stream << "    if (processNotImplementedMethod(TLValue::" << method.nameFirstCapital() << ")) {" << endl;
            stream << "        return;" << endl;
            stream << "    }" << endl;
            stream << "    " << method.type << " result;" << endl;
            stream << "    sendRpcReply(result);" << endl;
            stream << "}" << endl;
            stream << endl;

            return definition;
        };
        result.definitions.append(addDefinition(method, previousSourceCode));
    }
    return result;
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
    // case TLValue::AuthSignIn:
    //     d << request << "(";
    // {
    //     Telegram::Debug::Spacer spacer;
    //     QString phoneNumber;
    //     stream >> phoneNumber;
    //     QString phoneCodeHash;
    //     stream >> phoneCodeHash;
    //     QString phoneCode;
    //     stream >> phoneCode;
    //     d << endl;
    //     d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << endl;
    //     d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << endl;
    //     d << spacer.innerSpaces() << "phoneCode: " << phoneCode << endl;
    // }
    //     d << ")";
    //     break;

    QString result;
    QTextStream stream(&result, QIODevice::WriteOnly);
    stream << spacing << QStringLiteral("case %1::%2:").arg(tlValueName, method.nameFirstCapital()) << endl;
    // stream << spacing << QStringLiteral("case %1::%2:").arg(tlValueName, formatName(method.name, FormatOption::UpperCaseFirstLetter)) << endl;
    stream << spacing << "    d << \"" << method.nameFirstCapital() << "(\";" << endl;

    if (!method.params.isEmpty()) {
        stream << spacing << "{" << endl;
        stream << spacing << "    d << endl;" << endl;
        stream << spacing << QStringLiteral("    Telegram::Debug::Spacer spacer;") << endl;

        for (const TLParam &param : method.params) {
            if (param.dependOnFlag()) {
                continue;
            }
            stream << spacing << QStringLiteral("    %1 %2;").arg(param.type(), param.getAlias()) << endl;
            stream << spacing << QStringLiteral("    stream >> %1;").arg(param.getAlias()) << endl;
            stream << spacing << "    d << spacer.innerSpaces()"
                   << " << \"" << param.getAlias() << ": \" << " << param.getAlias()
                   << " << endl;" << endl;
        }
        stream << spacing << "}" << endl;
    }

    stream << spacing << QStringLiteral("    d << \")\";") << endl;
    stream << spacing << QStringLiteral("    break;") << endl;

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
                                member.setAlias(formatName({typeWithoutTL, member.getName(), QStringLiteral("Vector")}, FormatOption::LowerCaseFirstLetter));
                            } else {
                                member.setAlias(formatName({typeWithoutTL, member.getName()}, FormatOption::LowerCaseFirstLetter));
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
        bool parsedManually = false;

        qCDebug(c_loggingTextParser) << "Read line" << currentLine << ":" << line;

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

        if (line.startsWith(QLatin1String("//")) && line.contains(QLatin1String("// parsed manually"))) {
            parsedManually = true;
            line = line.mid(2);
        }

        line = line.section(QLatin1String("//"), 0, 0);
        if (line.simplified().isEmpty() || (line.startsWith(QLatin1String("---")) && line.endsWith(QLatin1String("---")))) {
            continue;
        }

        if (parsedManually && !line.contains(QLatin1Char('#'))) {
            // Skip lines without predicate
            continue;
        }
        LineParseResult parseResult = parseLine(line);
        if (!parseResult.isValid() && !parsedManually) {
            qCWarning(c_loggingTextParser).noquote() << QStringLiteral("Bad string: %s (line %d)").arg(line).arg(currentLine);
        }

        const QString typeName = formatType(parseResult.typeName);
        if (entryType == EntryTypedef) {
            const QString predicateName = formatName(parseResult.predicateName, FormatOption::UpperCaseFirstLetter);
            TLType tlType = m_types.value(typeName);
            tlType.name = typeName;

            TLSubType tlSubType;
            tlSubType.name = predicateName;
            tlSubType.predicateId = parseResult.predicateId;
            tlSubType.members.append(parseResult.params);
            tlSubType.source = line;

            tlType.subTypes.append(tlSubType);

            if (parsedManually) {
                m_extraPredicates.append(new TLSubType(tlSubType));
                continue;
            }

            if (!m_types.contains(typeName)) {
                m_groups.last().append(typeName);
            }
            m_types.insert(typeName, tlType);
        } else if (entryType == EntryFunction) {
            TLMethod tlMethod;
            tlMethod.predicateId = parseResult.predicateId;
            tlMethod.source = line;
            tlMethod.type = typeName;

            if (!parseResult.predicateName.contains(QLatin1Char('.'))) {
                parsedManually = true;
            }

            const QString groupName = parseResult.predicateName.section(QLatin1Char('.'), 0, 0);

            if (methodBlackList.contains(groupName)) {
                parsedManually = true;
            }
            const QString functionName = removeSeparators(parseResult.predicateName);
            tlMethod.name = functionName;
            tlMethod.params.append(parseResult.params);

            if (parsedManually) {
                m_extraPredicates.append(new TLMethod(tlMethod));
                continue;
            }
            if (!m_functions.contains(functionName)) {
                m_groups.last().append(functionName);
            }
            m_functions.insert(functionName, tlMethod);

            if (groupName.indexOf(QRegularExpression("[A-Z]")) < 0) {
                if (!m_functionGroups.contains(groupName)) {
                    m_functionGroups.append(groupName);
                }
            }
        }
    }
    std::sort(m_functionGroups.begin(), m_functionGroups.end(), [](const QString &s1, const QString &s2) {
        return s1 < s2;
    });
    qDebug() << "Sort:" << m_functionGroups;

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

void Generator::generate()
{
    codeOfTLTypes.clear();
    codeStreamReadDeclarations.clear();
    codeStreamReadDefinitions.clear();
    codeStreamReadTemplateInstancing.clear();
    codeStreamWriteDeclarations.clear();
    codeStreamWriteDefinitions.clear();
    codeStreamWriteTemplateInstancing.clear();
    codeRpcProcessDeclarations.clear();
    codeRpcProcessDefinitions.clear();
    codeRpcProcessSwitchCases.clear();
    codeRpcProcessSwitchUpdatesCases.clear();
    codeDebugWriteDeclarations.clear();
    codeDebugWriteDefinitions.clear();
    codeDebugRpcParse.clear();

    QStringList typesUsedForWrite;
    QStringList vectorUsedForWrite;

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
            if (method.type == QLatin1String("TLUpdates")) {
                codeRpcProcessSwitchUpdatesCases.append(QStringLiteral("        case %1::%2:\n").arg(tlValueName, method.nameFirstCapital()));
            }
            if (!usedTypes.contains(method.type)) {
                usedTypes.append(method.type);
            }
        }
        // It's still necessary to generate definition to figure out used stream write operators
        generateConnectionMethodDefinition(method, typesUsedForWrite);
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
        newWriteInstances.append(streamWriteVectorTemplate(str));
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
        newReadInstances.append(streamReadVectorTemplate(str));
    }
    QStringList existReadInstances = existsStreamReadTemplateInstancing.split(QLatin1Char('\n'), QString::SkipEmptyParts);
    codeStreamReadTemplateInstancing = reorderLinesAsExist(newReadInstances, existReadInstances).join(QLatin1Char('\n'));
    if (!codeStreamReadTemplateInstancing.isEmpty()) {
        codeStreamReadTemplateInstancing.append(QLatin1Char('\n'));
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

        codeStreamReadDeclarations.append(streamReadOperatorDeclaration(&type));
        codeStreamReadDefinitions.append(streamReadOperatorDefinition(type));

        if (typesUsedForWrite.contains(type.name)) {
            codeStreamWriteDeclarations.append(streamWriteOperatorDeclaration(type));
            codeStreamWriteDefinitions.append(streamWriteOperatorDefinition(type));
        } else {
            codeStreamExtraWriteDeclarations.append(streamWriteFreeOperatorDeclaration(&type));
            codeStreamExtraWriteDefinitions .append(streamWriteFreeOperatorDefinition(type));
        }

        codeDebugWriteDeclarations.append(generateDebugWriteOperatorDeclaration(type));
        codeDebugWriteDefinitions .append(generateDebugWriteOperatorDefinition(type));
    }
    codeOfTLValues = joinLinesWithPrepend(generateTLValues(), doubleSpacing);
}

QStringList Generator::generateTLValues()
{
    qCDebug(c_loggingTlValues()) << Q_FUNC_INFO;
    QStringList result;
    foreach (const QStringList &group, m_groups) {
        if (group.isEmpty()) {
            continue;
        }
        const QString groupMember = group.first();
        if (m_types.contains(groupMember)) {
            result.append(QLatin1String("// Types\n"));
            foreach (const QString &typeName, group) {
                if (!m_types.contains(typeName)) {
                    qCCritical(c_loggingTlValues()) << "Name of group item" << typeName << "not found in the types map";
                    return QStringList();
                }
                const TLType &type = m_types.value(typeName);
                foreach (const TLSubType &subType, type.subTypes) {
                    result.append(generateTLValuesDefinition(&subType));
                }
            }
        } else if (m_functions.contains(groupMember)) {
            result.append(QLatin1String("// Functions\n"));
            foreach (const QString &typeName, group) {
                if (!m_functions.contains(typeName)) {
                    qCCritical(c_loggingTlValues()) << "Name of group item" << typeName << "not found in the functions map";
                    return QStringList();
                }
                const TLMethod &method = m_functions.value(typeName);
                result.append(generateTLValuesDefinition(&method));
            }
        } else {
            qCCritical(c_loggingTlValues()) << "Name of group item" << groupMember << "is neither a type or a function";
            return QStringList();
        }
    }

    if (!m_extraPredicates.isEmpty()) {
        result.append(QLatin1String("// Extra predicates\n"));
    }
    for (const Predicate *predicate : m_extraPredicates) {
        const QString value = generateTLValuesDefinition(predicate);
        qCDebug(c_loggingTlValues()) << "Add extra predicate:" << value;
        result.append(value);
    }
    return result;
}

void Generator::dumpReadData() const
{
    qDebug() << "\n" << Q_FUNC_INFO;
    qDebug() << "Groups:";
    for (const QStringList &group : m_groups) {
        qDebug() << "    " << group;
    }
    qDebug() << "Types:" << m_types.keys();
    for (const TLType &type : m_types) {
        qDebug() << "    name:" << type.name;
        qDebug() << "    SubTypes:";
        for (const TLSubType &sub : type.subTypes) {
            qDebug() << "        name:" << sub.name << "predicate:" << sub.predicateName();
            qDebug() << "        source:" << sub.source;

        }
    }
}

void Generator::dumpSolvedTypes() const
{
    qDebug() << "\n" << Q_FUNC_INFO;
    qDebug() << "Types:";
    for (const TLType &type : m_solvedTypes) {
        qDebug() << "    name:" << type.name;
        qDebug() << "    SubTypes:";
        for (const TLSubType &sub : type.subTypes) {
            qDebug() << "        name:" << sub.name << "predicate:" << sub.predicateName();
            qDebug() << "        source:" << sub.source;

        }
    }
}

Generator::MethodsCode Generator::generateClientFunctions(const QString &prefix) const
{
    MethodsCode result;
    const QString operationBaseName = QStringLiteral("PendingRpcResult");
    for (const TLMethod &method : m_functions) {
        if (!method.name.startsWith(prefix)) {
            continue;
        }
        const QString prefixFirstUpper = formatName(prefix, FormatOption::UpperCaseFirstLetter);
        const QString className = prefixFirstUpper + QStringLiteral("RpcLayer");
        const QString predicateName = formatName(method.name, FormatOption::LowerCaseFirstLetter|FormatOption::SkipFirstWord);
        // PendingRpcOperation *checkPassword(const QByteArray &passwordHash);

        bool resultIsVector;
        QString resultName = Generator::formatName(getTypeOrVectorType(method.type, &resultIsVector),
                                                   FormatOption::UpperCaseFirstLetter|FormatOption::SkipTl);

        const QString operationName = resultIsVector ?
                    QLatin1String("Pending") + resultName + QLatin1String("Vector")
                  : QLatin1String("Pending") + resultName;
        QString operationType = processOperationType(method.type);
        result.usings.append(QStringLiteral("using %1 = %2<%3 *>;")
                             .arg(operationName, operationBaseName, operationType));
        // using PendingAuthSentCode = PendingRpcResult<TLAuthSentCode *>;
        result.declarations.append(QStringLiteral("%1 *%2(%3);")
                                   .arg(operationName, predicateName, formatMethodParams(method)));
        // PendingAuthSentCode *sendCode(quint32 flags, const QString &phoneNumber, ...);
        QString definitionCode = QStringLiteral("%2::%1 *%2::%3(%4)\n{\n")
                .arg(operationName, className, predicateName, formatMethodParams(method));

        QStringList debugArguments = { QStringLiteral("Q_FUNC_INFO") };
        for (const TLParam &param : method.params) {
            if (param.dependOnFlag() && (param.type() == tlTrueType)) {
                continue;
            }
            if (param.type() == QLatin1String("QByteArray")) {
                debugArguments.append(param.getAlias() + QStringLiteral(".toHex()"));
            } else {
                debugArguments.append(param.getAlias());
            }
        }

        // qCDebug(c_clientRpcAuthCategory) << Q_FUNC_INFO << phoneNumber << smsType << apiId << apiHash << langCode;
        definitionCode += spacing + QStringLiteral("qCDebug(c_clientRpc%1Category)%2;\n").arg(prefixFirstUpper, joinLinesWithPrepend(debugArguments, QStringLiteral(" << ")));
        definitionCode += spacing + streamClassName + QLatin1String(" outputStream(CTelegramStream::WriteOnly);\n");
        definitionCode += spacing + QString("outputStream << %1::%2;\n").arg(tlValueName, formatName(method.name, FormatOption::UpperCaseFirstLetter));

        foreach (const TLParam &param, method.params) {
            if (param.dependOnFlag()) {
                if (param.type() == tlTrueType) {
                    definitionCode += spacing + QString("// (%1 & 1 << %2) stands for %3 \"true\" value\n").arg(param.flagMember).arg(param.flagBit).arg(param.getAlias());
                } else {
                    definitionCode += spacing + QString("if (%1 & 1 << %2) {\n").arg(param.flagMember).arg(param.flagBit);
                    definitionCode += spacing + spacing + QString("outputStream << %1;\n").arg(param.getAlias());
                    definitionCode += spacing + QLatin1String("}\n");
                }
            } else {
                definitionCode += spacing + QString("outputStream << %1;\n").arg(param.getAlias());
            }
        }
        definitionCode += spacing + QStringLiteral("%1 *op = new %1(this, outputStream.getData());\n")
                .arg(operationName);
        definitionCode += spacing + QLatin1String("processRpcCall(op);\n");
        definitionCode += spacing + QLatin1String("return op;\n}\n");
        result.definitions.append(definitionCode);

        // PendingAuthSentCode *op = new PendingAuthSentCode(this, outputStream.getData());
        // processRpcCall(op);
        // return op;
    }
    result.usings.removeDuplicates();
    return result;
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

QStringList Generator::getWords(const QString &input)
{
    if (input.isEmpty()) {
        return QStringList();
    }
    QStringList words;
    int indexOfPreviousUpper = 0;
    for (int i = 1; i < input.length(); ++i) {
        if (input.at(i).isUpper()) {
            words.append(input.mid(indexOfPreviousUpper, i - indexOfPreviousUpper));
            indexOfPreviousUpper = i;
        }
        if (i == (input.length() - 1)) {
            words.append(input.mid(indexOfPreviousUpper));
        }
    }
    return words;
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

QString TLMethod::functionTypeName() const
{
    return tlPrefix + nameFirstCapital();
}

QString TLMethod::nameFromSecondWord() const
{
    QStringList words = Generator::getWords(name);
    words.removeFirst();
    return words.join(QString());
}

QString TypedEntity::variableName() const
{
    QString varName = removePrefix(name);
    varName[0] = varName.at(0).toLower();
    varName += entityType();
    return varName;
}

QMap<quint8, QString> TLType::getBoolFlags() const
{
    QMap<quint8, QString> result;
    for (const TLSubType &subType : subTypes) {
        QMap<quint8, QString> subTypeFlags = subType.getBoolFlags();
        for (quint8 flagBit : subTypeFlags.keys()) {
            if (result.contains(flagBit) && (result.value(flagBit) != subTypeFlags.value(flagBit))) {
                qWarning() << Q_FUNC_INFO << "TODO: Process multiflags";
                continue;
            }
            result.insert(flagBit, subTypeFlags.value(flagBit));
        }
    }
    return result;
}

QMap<quint8, QString> TLSubType::getBoolFlags() const
{
    QMap<quint8, QString> flags;
    for (const TLParam &member : members) {
        if (member.type() != tlTrueType) {
            continue;
        }
        if (!member.dependOnFlag()) {
            continue;
        }
        flags.insertMulti(member.flagBit, member.flagName());
    }
    return flags;
}
