/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "GeneratorNG.hpp"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

static const QString tlPrefix = QLatin1String("TL");
static const QString tlValueName = tlPrefix + QLatin1String("Value");
static const QString tlTypeMember = QLatin1String("tlType");
static const QString tlVectorType = QLatin1String("TLVector");
static const QStringList podTypes = QStringList() << "bool" << "quint32" << "quint64" << "double" << tlValueName;
static const QStringList initTypesValues = QStringList() << "false" << "0" << "0" << "0" << "0";
static const QStringList plainTypes = QStringList() << "Bool" << "int" << "long" << "double" << "string" << "bytes";
static const QStringList nativeTypes = QStringList() << "bool" << "quint32" << "quint64" << "double" << "QString" << "QByteArray";

static const QStringList badNames = QStringList() << "lat"<< "long" ;
static const QStringList badNamesReplacers = QStringList() << "latitude"<< "longitude";

static const QString spacing = QString(4, QLatin1Char(' '));
static const QString doubleSpacing = spacing + spacing;

static const QString streamClassName = QLatin1String("CTelegramStream");
static const QString methodsClassName = QLatin1String("CTelegramConnection");

static const QStringList typesBlackList = QStringList()
        << QLatin1String("TLVector t")
        << QLatin1String("TLNull")
        << QLatin1String("TLMessagesMessage")
           ;

QDebug operator<<(QDebug d, const TLParam &param)
{
    d << param.type << ":" << param.name << "; ";
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
    int dotIndex = str.indexOf(QChar('.'), minIndex);
    int underscoreIndex = str.indexOf(QChar('_'), minIndex);

    if (dotIndex < 0) {
        return underscoreIndex;
    } else if (underscoreIndex < 0) {
        return dotIndex;
    }

    return dotIndex < underscoreIndex ? dotIndex : underscoreIndex;
}

QString formatName(QString name)
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

QString formatName1stCapital(QString name)
{
    if (name.isEmpty()) {
        return QString();
    }

    name[0] = name.at(0).toUpper();
    return formatName(name);
}

QString removePrefix(const QString &str)
{
    if (str.startsWith(tlPrefix)) {
        return str.mid(tlPrefix.size());
    } else {
        return str;
    }
}

QString formatMember(QString name)
{
    if (badNames.contains(name)) {
        name = badNamesReplacers.at(badNames.indexOf(name));
    }

    return formatName(name);
}

QString formatMethodParam(const TLParam &param)
{
    if (podTypes.contains(param.type)) {
        return QString("%1 %2").arg(param.type).arg(param.name);
    } else {
        return  QString("const %1 &%2").arg(param.type).arg(param.name);
    }
}

QString formatMethodParams(const TLMethod &method)
{
    QString result;

    foreach (const TLParam &param, method.params) {
        if (!result.isEmpty()) {
            result += QLatin1String(", ");
        }

        result += formatMethodParam(param);
    }

    return result;
}

QString getTypeOrVectorType(const QString &str)
{
    if (!str.startsWith(tlVectorType + QLatin1Char('<'))) {
        return str;
    }

    int firstIndex = str.indexOf(QLatin1Char('<')) + 1;
    int lastIndex = str.indexOf(QLatin1Char('>'));
    const QString subType = str.mid(firstIndex, lastIndex - firstIndex);

    return subType;
}

QString formatType(QString type)
{
    if (plainTypes.contains(type)) {
        return nativeTypes.at(plainTypes.indexOf(type));
    } else if (type.startsWith(QLatin1String("Vector<"))) {
        int firstIndex = type.indexOf(QLatin1Char('<')) + 1;
        int lastIndex = type.indexOf(QLatin1Char('>'));
        QString subType = type.mid(firstIndex, lastIndex - firstIndex);
        return QString("%1<%2>").arg(tlVectorType).arg(formatType(subType));
    } else {
        type[0] = type.at(0).toUpper();

        return tlPrefix + formatName(type);
    }
}

static QMap<QString, TLType> readTypesJson(const QJsonDocument &document)
{
    const QJsonArray constructors = document.object().value("constructors").toArray();

    QMap<QString, TLType> types;

    for (int i = 0; i < constructors.count(); ++i) {
        const QJsonObject obj = constructors.at(i).toObject();

        const QString predicateName = formatName1stCapital(obj.value("predicate").toString());
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
            const QString paramName = formatMember(paramObj.value("name").toString());

            const QString paramType = paramObj.value("type").toString();

            tlSubType.members.append(TLParam(paramName, formatType(paramType)));
        }

        tlType.subTypes.append(tlSubType);
        types.insert(typeName, tlType);
    }

    return types;
}

static QMap<QString, TLMethod> readFunctionsJson(const QJsonDocument &document)
{
    const QJsonArray methods = document.object().value("methods").toArray();

    QMap<QString, TLMethod> result;

    for (int i = 0; i < methods.count(); ++i) {
        const QJsonObject obj = methods.at(i).toObject();

        const QString methodName = formatName(obj.value("method").toString());
        const quint32 methodId = obj.value("id").toString().toInt();

        TLMethod tlMethod;
        tlMethod.name = methodName;
        tlMethod.id = methodId;

        const QJsonArray params = obj.value("params").toArray();

        foreach (const QJsonValue &paramValue, params) {
            const QJsonObject &paramObj = paramValue.toObject();
            const QString paramName = formatMember(paramObj.value("name").toString());

            const QString paramType = paramObj.value("type").toString();

            tlMethod.params.append(TLParam(paramName, formatType(paramType)));
        }

        result.insert(methodName, tlMethod);

//        quint32 id = obj.value("id").toString().toInt();
//        qDebug() << name << QString::number(id, 0x10);
    }

    return result;
}

QString GeneratorNG::generateTLValuesDefinition(const TLType &type)
{
    QString code;

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("        %1 = 0x%2,\n").arg(subType.name).arg(subType.id, 8, 0x10, QLatin1Char('0')));
    }

    return code;
}

QString GeneratorNG::generateTLValuesDefinition(const TLMethod &method)
{
    QString nameFirstCapital = method.name;
    if (!nameFirstCapital.isEmpty()) {
        nameFirstCapital[0] = nameFirstCapital.at(0).toUpper();
    }
    return QString("        %1 = 0x%2,\n").arg(nameFirstCapital).arg(method.id, 8, 0x10, QLatin1Char('0'));
}

QString GeneratorNG::generateTLTypeDefinition(const TLType &type)
{
    QString code;

    code.append(QString("struct %1 {\n").arg(type.name));

//    QString anotherName = removePrefix(type.name);
//    anotherName[0] = anotherName.at(0).toUpper();
//    anotherName.prepend(QLatin1String("another"));

    QString constructor = spacing + QString("%1() :\n").arg(type.name);
//    QString copyConstructor = spacing + QString("%1(const %1 &%2) :\n").arg(type.name).arg(anotherName);
//    QString copyOperator = spacing + QString("%1 &operator=(const %1 &%2) {\n").arg(type.name).arg(anotherName);
    QString membersCode;

    QStringList addedMembers;
    foreach (const TLSubType &subType, type.subTypes) {
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.name)) {
                continue;
            }

            addedMembers.append(member.name);

//            copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
//            copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(member.name).arg(anotherName);

            membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(member.type).arg(member.name));

            if (!podTypes.contains(member.type)) {
                continue;
            }

            const QString initialValue = initTypesValues.at(podTypes.indexOf(member.type));
            constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(member.name).arg(initialValue);
        }
    }

    constructor += QString("%1%2(%3::%4),\n").arg(doubleSpacing).arg(tlTypeMember).arg(tlValueName).arg(type.subTypes.first().name);
//    copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
//    copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
    membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(tlValueName).arg(tlTypeMember));

    constructor.chop(2);
    constructor.append(QLatin1String(" { }\n\n"));

//    copyConstructor.chop(2);
//    copyConstructor.append(QLatin1String(" { }\n\n"));

//    copyOperator.append(QString("\n%1%1return *this;\n%1}\n").arg(spacing));

    code.append(constructor);
//    code.append(copyConstructor);
//    code.append(copyOperator);

//    code.append(QLatin1Char('\n'));
    code.append(membersCode);

    code.append(QString("};\n\n"));

    return code;
}

QString GeneratorNG::generateStreamReadOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return spacing + QString("%1 &operator>>(%2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString GeneratorNG::generateStreamWriteOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return spacing + QString("%1 &operator<<(const %2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString GeneratorNG::generateStreamReadOperatorDefinition(const TLType &type)
{
    QString code;

    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();

    code.append(QString("%1 &%1::operator>>(%2 &%3)\n{\n").arg(streamClassName).arg(type.name).arg(argName));
    code.append(QString("%1%2 result;\n\n").arg(spacing).arg(type.name));
    code.append(QString("%1*this >> result.tlType;\n\n%1switch (result.tlType) {\n").arg(spacing));

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("%1case %2::%3:\n").arg(spacing).arg(tlValueName).arg(subType.name));

        foreach (const TLParam &member, subType.members) {
            code.append(QString("%1*this >> result.%2;\n").arg(doubleSpacing).arg(member.name));
        }

        code.append(QString("%1break;\n").arg(doubleSpacing));
    }

    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(QString("%1%2 = result;\n\n%1return *this;\n}\n\n").arg(spacing).arg(argName));

    return code;
}

QString GeneratorNG::generateStreamReadVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator>>(TLVector<%2> &v);\n")).arg(streamClassName).arg(type);
}

QString GeneratorNG::generateStreamWriteOperatorDefinition(const TLType &type)
{
    QString code;

    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();

    code.append(QString("%1 &%1::operator<<(const %2 &%3)\n{\n").arg(streamClassName).arg(type.name).arg(argName));
    code.append(QString("%1*this << %2.tlType;\n\n%1switch (%2.tlType) {\n").arg(spacing).arg(argName));

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("%1case %2::%3:\n").arg(spacing).arg(tlValueName).arg(subType.name));

        foreach (const TLParam &member, subType.members) {
            code.append(doubleSpacing + QString("*this << %1.%2;\n").arg(argName).arg(member.name));
        }

        code.append(QString("%1break;\n").arg(doubleSpacing));
    }

    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(spacing + QString("return *this;\n}\n\n"));

    return code;
}

QString GeneratorNG::generateStreamWriteVectorTemplate(const QString &type)
{
    return QString(QLatin1String("template %1 &%1::operator<<(const TLVector<%2> &v);\n")).arg(streamClassName).arg(type);
}

QString GeneratorNG::generateDebugWriteOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return QString("QDebug operator<<(QDebug d, const %1 &%2);\n").arg(type.name).arg(argName);
}

QString GeneratorNG::generateDebugWriteOperatorDefinition(const TLType &type)
{
    QString code;

    code += QString("QDebug operator<<(QDebug d, const %1 &type)\n{\n").arg(type.name);
    code += spacing + QString("d << \"%1(\" << type.tlType.toString() << \") {\";\n").arg(type.name);
    code += spacing + QLatin1String("switch (type.tlType) {\n");

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("%1case %2::%3:\n").arg(spacing).arg(tlValueName).arg(subType.name));

        foreach (const TLParam &member, subType.members) {
            code += doubleSpacing + QString("d << \"%1:\" << type.%1;\n").arg(member.name);
        }

        code += doubleSpacing + QLatin1String("break;\n");
    }

    code += spacing + QLatin1String("default:\n");
    code += doubleSpacing + QLatin1String("break;\n");
    code += spacing + QLatin1String("}\n");
    code += spacing + QLatin1String("d << \"}\";\n\n");
    code += spacing + QLatin1String("return d;\n}\n\n");

    return code;

//    QDebug operator << (QDebug d, const TLUpdatesState &type) {
//        d << "TLUpdatesState(" << type.tlType.toString() << ")";
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

QString GeneratorNG::generateConnectionMethodDeclaration(const TLMethod &method)
{
    return spacing + QString("quint64 %1(%2);\n").arg(method.name).arg(formatMethodParams(method));
}

QString GeneratorNG::generateConnectionMethodDefinition(const TLMethod &method, QStringList &usedTypes)
{
    QString result;
    result += QString("quint64 %1::%2(%3)\n{\n").arg(methodsClassName).arg(method.name).arg(formatMethodParams(method));
    result += spacing + QLatin1String("QByteArray output;\n");
    result += spacing + streamClassName + QLatin1String(" outputStream(&output, /* write */ true);\n\n");

    result += spacing + QString("outputStream << %1::%2;\n").arg(tlValueName).arg(formatName1stCapital(method.name));

    foreach (const TLParam &param, method.params) {
        result += spacing + QString("outputStream << %1;\n").arg(param.name);

        if (!nativeTypes.contains(getTypeOrVectorType(param.type))) {
            usedTypes.append(param.type);
        }
    }

    result += QLatin1Char('\n');
    result += spacing + QLatin1String("return sendEncryptedPackage(output);\n}\n\n");

    return result;
}

QList<TLType> GeneratorNG::solveTypes(QMap<QString, TLType> types)
{
    QList<TLType> solvedTypes;
    QStringList solvedTypesNames = nativeTypes;
    solvedTypesNames.append(tlValueName);

    int previousSolvedTypesCount = -1;

    // In order to successful compilation, type must rely only on defined types.
    while (solvedTypes.count() != previousSolvedTypesCount) { // Check for infinity loop
        previousSolvedTypesCount = solvedTypes.count();
        foreach(const QString &typeName, types.keys()) {
            const TLType &type = types.value(typeName);

            bool solved = true;

            if (nativeTypes.contains(type.name)) {
                types.remove(typeName);
                continue;
            }

            foreach (const TLSubType &subType, type.subTypes) {
                foreach (const TLParam &member, subType.members) {
                    QString memberType = getTypeOrVectorType(member.type);

                    if (!solvedTypesNames.contains(memberType)) {
                        solved = false;
                        break;
                    }
                }

                if (!solved) {
                    break;
                }
            }

            if (solved) {
                solvedTypes.append(type);
                types.remove(typeName);
                solvedTypesNames.append(typeName);

                qDebug() << "Solved:" << typeName;
            }
        }
    }

    qDebug() << "Unresolved:" << types.count();

    return solvedTypes;
}

void GeneratorNG::getUsedAndVectorTypes(QStringList &usedTypes, QStringList &vectors) const
{
    QStringList newUsedTypes = usedTypes;

    while (!newUsedTypes.isEmpty()) {
        QStringList veryNewTypes;
        foreach (const QString &type, newUsedTypes) {
            const TLType t = m_types.value(type);

            foreach (const TLSubType &sub, t.subTypes) {
                foreach (const TLParam &member, sub.members) {
                    QString memberType = getTypeOrVectorType(member.type);

                    if (nativeTypes.contains(memberType)) {
                        continue;
                    }

                    if (memberType != member.type) { // Vector
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

bool GeneratorNG::loadDataFromJson(const QByteArray &data)
{
    const QJsonDocument document = QJsonDocument::fromJson(data);
    m_types = readTypesJson(document);
    m_functions = readFunctionsJson(document);

    return !m_types.isEmpty() && !m_functions.isEmpty();
}

void GeneratorNG::generate()
{
    m_solvedTypes = solveTypes(m_types);

    codeOfTLValues.clear();
    codeOfTLTypes.clear();
    codeStreamReadDeclarations.clear();
    codeStreamReadDefinitions.clear();
    codeStreamWriteDeclarations.clear();
    codeStreamWriteDefinitions.clear();
    codeStreamWriteTemplateInstancing.clear();
    codeConnectionDeclarations.clear();
    codeConnectionDefinitions.clear();
    codeDebugWriteDeclarations.clear();
    codeDebugWriteDefinitions.clear();

    QStringList typesUsedForWrite;
    QStringList vectorUsedForWrite;

    static const QStringList whiteList = QStringList()
            << QLatin1String("auth")
            << QLatin1String("account")
            << QLatin1String("messages")
            << QLatin1String("contacts")
            << QLatin1String("updates")
            << QLatin1String("upload")
            << QLatin1String("users");

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

    QStringList usedTypes;
    foreach (const TLType &type, m_solvedTypes) {
        if (nativeTypes.contains(type.name)) {
            continue;
        }

        if (typesBlackList.contains(type.name)) {
            continue;
        }

        usedTypes += type.name;
    }

    QStringList vectorUsedForRead;
    getUsedAndVectorTypes(usedTypes, vectorUsedForRead);
    foreach (const QString &str, vectorUsedForRead) {
        codeStreamReadTemplateInstancing.append(generateStreamReadVectorTemplate(str));
    }

    getUsedAndVectorTypes(typesUsedForWrite, vectorUsedForWrite);
    foreach (const QString &str, vectorUsedForWrite) {
        codeStreamWriteTemplateInstancing.append(generateStreamWriteVectorTemplate(str));
    }

    codeOfTLValues.append(QLatin1String("        // Types\n"));
    foreach (const TLType &type, m_types) {
        codeOfTLValues.append(generateTLValuesDefinition(type));
    }

    codeOfTLValues.append(QLatin1String("        // Methods\n"));
    foreach (const TLMethod &method, m_functions) {
        codeOfTLValues.append(generateTLValuesDefinition(method));
    }

    foreach (const TLType &type, m_solvedTypes) {
        if (nativeTypes.contains(type.name)) {
            continue;
        }

        if (typesBlackList.contains(type.name)) {
            continue;
        }

        codeOfTLTypes.append(generateTLTypeDefinition(type));

        codeStreamReadDeclarations.append(generateStreamReadOperatorDeclaration(type));
        codeStreamReadDefinitions.append(generateStreamReadOperatorDefinition(type));

        if (typesUsedForWrite.contains(type.name)) {
            codeStreamWriteDeclarations.append(generateStreamWriteOperatorDeclaration(type));
            codeStreamWriteDefinitions.append(generateStreamWriteOperatorDefinition(type));
        }

        codeDebugWriteDeclarations.append(generateDebugWriteOperatorDeclaration(type));
        codeDebugWriteDefinitions .append(generateDebugWriteOperatorDefinition(type));
    }

}
