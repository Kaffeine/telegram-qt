/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "GeneratorNG.hpp"

#include <QDebug>
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

QString GeneratorNG::formatName(QString name)
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

QString GeneratorNG::formatName1stCapital(QString name)
{
    if (name.isEmpty()) {
        return QString();
    }

    name[0] = name.at(0).toUpper();
    return formatName(name);
}

inline QString GeneratorNG::removePrefix(const QString &str)
{
    if (str.startsWith(tlPrefix)) {
        return str.mid(tlPrefix.size());
    } else {
        return str;
    }
}

QString GeneratorNG::formatMember(QString name)
{
    if (badNames.contains(name)) {
        name = badNamesReplacers.at(badNames.indexOf(name));
    }

    return formatName(name);
}

QString GeneratorNG::getTypeOrVectorType(const QString &str)
{
    if (!str.startsWith(tlVectorType + QLatin1Char('<'))) {
        return str;
    }

    int firstIndex = str.indexOf(QLatin1Char('<')) + 1;
    int lastIndex = str.indexOf(QLatin1Char('>'));
    const QString subType = str.mid(firstIndex, lastIndex - firstIndex);

    return subType;
}

QString GeneratorNG::formatType(QString type)
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

QString GeneratorNG::generateStreamReadOperatorDeclaration(const TLType &type) const
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return spacing + QString("%1 &operator>>(%2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString GeneratorNG::generateStreamWriteOperatorDeclaration(const TLType &type) const
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return spacing + QString("%1 &operator<<(const %2 &%3);\n").arg(streamClassName).arg(type.name).arg(argName);
}

QString GeneratorNG::generateStreamReadOperatorDefinition(const TLType &type) const
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

QString GeneratorNG::generateStreamWriteOperatorDefinition(const TLType &type) const
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

QString GeneratorNG::generateDebugWriteOperatorDeclaration(const TLType &type) const
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return QString("QDebug operator<<(QDebug d, const %1 &%2);\n").arg(type.name).arg(argName);
}

QString GeneratorNG::generateDebugWriteOperatorDefinition(const TLType &type) const
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

QString GeneratorNG::formatMethodParam(const TLParam &param)
{
    if (podTypes.contains(param.type)) {
        return QString("%1 %2").arg(param.type).arg(param.name);
    } else {
        return  QString("const %1 &%2").arg(param.type).arg(param.name);
    }
}

QString GeneratorNG::formatMethodParams(const TLMethod &method)
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

QString GeneratorNG::generateConnectionMethodDeclaration(const TLMethod &method)
{
    return spacing + QString("quint64 %1(%2);\n").arg(method.name).arg(formatMethodParams(method));
}

QString GeneratorNG::generateConnectionMethodDefinition(const TLMethod &method)
{
    QString result;
    result += QString("quint64 %1::%2(%3)\n{\n").arg(methodsClassName).arg(method.name).arg(formatMethodParams(method));
    result += spacing + QLatin1String("QByteArray output;\n");
    result += spacing + QLatin1String("CTelegramStream outputStream(&output, /* write */ true);\n\n");

    result += spacing + QString("outputStream << %1::%2;\n").arg(tlValueName).arg(formatName1stCapital(method.name));

    foreach (const TLParam &param, method.params) {
        result += spacing + QString("outputStream << %1;\n").arg(param.name);

        if (!nativeTypes.contains(param.type)) {
            m_usedWriteOperators.append(param.type);

            const QString subType = getTypeOrVectorType(param.type);
            if (subType != param.type) {

                if (!nativeTypes.contains(subType)) {
                    m_usedWriteOperators.append(subType);
                }
            }
        }
    }

    result += QLatin1Char('\n');
    result += spacing + QLatin1String("return sendEncryptedPackage(output);\n}\n\n");

    return result;
}

QMap<QString, TLType> GeneratorNG::readTypes(const QJsonDocument &document)
{
    const QJsonArray constructors = document.object().value("constructors").toArray();

    QMap<QString, TLType> types;

    for (int i = 0; i < constructors.count(); ++i) {
        const QJsonObject obj = constructors.at(i).toObject();

        const QString predicateName = formatName1stCapital(obj.value("predicate").toString());
        const QString typeName = formatType(obj.value("type").toString());

        if (!nativeTypes.contains(typeName)) {
            TLType tlType = types.value(typeName);
            tlType.name = typeName;

            TLSubType tlSubType;
            tlSubType.name = predicateName;

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

//        quint32 id = obj.value("id").toString().toInt();
//        qDebug() << name << QString::number(id, 0x10);
    }

    return types;
}

QMap<QString, TLMethod> GeneratorNG::readMethods(const QJsonDocument &document)
{
    const QJsonArray methods = document.object().value("methods").toArray();

    QMap<QString, TLMethod> result;

    for (int i = 0; i < methods.count(); ++i) {
        const QJsonObject obj = methods.at(i).toObject();

        const QString methodName = formatName(obj.value("method").toString());

        TLMethod tlMethod;
        tlMethod.name = methodName;

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

bool GeneratorNG::loadData(const QByteArray &data)
{
    const QJsonDocument document = QJsonDocument::fromJson(data);

    m_types = readTypes(document);
    m_solvedTypes = solveTypes(m_types);

    m_methods = readMethods(document);

    return !(m_types.isEmpty() || m_solvedTypes.isEmpty() | m_methods.isEmpty());
}

void GeneratorNG::generate()
{
    codeOfTLTypes.clear();
    codeStreamReadDeclarations.clear();
    codeStreamWriteDeclarations.clear();
    codeStreamReadDefinitions.clear();
    codeStreamWriteDefinitions.clear();
    codeConnectionDeclarations.clear();
    codeConnectionDefinitions.clear();

    static const QStringList whiteList = QStringList()
            << QLatin1String("auth")
            << QLatin1String("account")
            << QLatin1String("messages")
            << QLatin1String("contacts")
            << QLatin1String("updates")
            << QLatin1String("upload")
            << QLatin1String("users");

    foreach (const TLMethod &method, m_methods) {
        bool addImplementation = false;
        foreach (const QString &white, whiteList) {
            if (method.name.startsWith(white)) {
                addImplementation = true;
                break;
            }
        }
        if (addImplementation) {
            codeConnectionDeclarations.append(generateConnectionMethodDeclaration(method));
            codeConnectionDefinitions.append(generateConnectionMethodDefinition(method));
        } else {
            // It's still necessary to generate definition to figure out used stream write operators
            generateConnectionMethodDefinition(method);
        }
    }

    m_usedWriteOperators.removeDuplicates();

    foreach (const QString &str, m_usedWriteOperators) {
        if (str.startsWith(tlVectorType)) {
            qDebug() << str;
        }
    }

    foreach (const QString &str, m_usedWriteOperators) {
        if (!str.startsWith(tlVectorType)) {
            qDebug() << str;
        }
    }

    foreach (const TLType &type, m_solvedTypes) {
        if ((type.subTypes.count() == 1) && (type.subTypes.first().members.isEmpty())) {
            qDebug() << "Empty type" << type.name;
            continue;
        }

        codeOfTLTypes.append(generateTLTypeDefinition(type));

        codeStreamReadDeclarations.append(generateStreamReadOperatorDeclaration(type));
        codeStreamReadDefinitions.append(generateStreamReadOperatorDefinition(type));

        if (m_usedWriteOperators.contains(type.name)) {
            codeStreamWriteDeclarations.append(generateStreamWriteOperatorDeclaration(type));
            codeStreamWriteDefinitions.append(generateStreamWriteOperatorDefinition(type));
        }

        codeDebugWriteDeclarations.append(generateDebugWriteOperatorDeclaration(type));
        codeDebugWriteDefinitions .append(generateDebugWriteOperatorDefinition(type));
    }
}
