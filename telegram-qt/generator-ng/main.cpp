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

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QList>
#include <QMap>

/* Replacing helper */
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

    printf("Replacing is done.\n");

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

/* End of replacing helper */

static const QString tlPrefix = QLatin1String("TL");
static const QString tlValueName = tlPrefix + QLatin1String("Value");
static const QString tlTypeMember = QLatin1String("tlType");
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

inline QString removePrefix(const QString &str)
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

QString getTypeOrVectorType(const QString &str)
{
    if (!str.startsWith(QLatin1String("TLVector<"))) {
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
        return QString("TLVector<%1>").arg(formatType(subType));
    } else {
        type[0] = type.at(0).toUpper();

        return tlPrefix + formatName(type);
    }
}

struct TLParam {
    TLParam() { }
    TLParam(const QString &newName, const QString &newType) :
        name(newName), type(newType) { }

    QString name;
    QString type;

    TLParam &operator=(const TLParam &anotherMember) {
        name = anotherMember.name;
        type = anotherMember.type;

        return *this;
    }
};

struct TLSubType {
    QString name;
    QList<TLParam> members;

    TLSubType &operator=(const TLSubType &anotherType) {
        name = anotherType.name;
        members = anotherType.members;

        return *this;
    }

    bool haveMember(const QString &name) {
        foreach (const TLParam &member, members) {
            if (member.name == name) {
                return true;
            }
        }

        return false;
    }
};

struct TLType {
    QString name;
    QList<TLSubType> subTypes;

    TLType &operator=(const TLType &anotherType) {
        name = anotherType.name;
        subTypes = anotherType.subTypes;

        return *this;
    }
};

struct TLMethod {
    QString name;
    QList< TLParam > params;

    TLMethod &operator=(const TLMethod &anotherMethod) {
        name = anotherMethod.name;
        params = anotherMethod.params;

        return *this;
    }
};

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

QString generateTLType(const TLType &type)
{
    QString code;

    code.append(QString("struct %1 {\n").arg(type.name));

    QString anotherName = removePrefix(type.name);
    anotherName[0] = anotherName.at(0).toUpper();
    anotherName.prepend(QLatin1String("another"));

    QString constructor = spacing + QString("%1() :\n").arg(type.name);
    QString copyConstructor = spacing + QString("%1(const %1 &%2) :\n").arg(type.name).arg(anotherName);
    QString copyOperator = spacing + QString("%1 &operator=(const %1 &%2) {\n").arg(type.name).arg(anotherName);
    QString membersCode;

    QStringList addedMembers;
    foreach (const TLSubType &subType, type.subTypes) {
        foreach (const TLParam &member, subType.members) {
            if (addedMembers.contains(member.name)) {
                continue;
            }

            addedMembers.append(member.name);

            copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
            copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(member.name).arg(anotherName);

            membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(member.type).arg(member.name));

            if (!podTypes.contains(member.type)) {
                continue;
            }

            const QString initialValue = initTypesValues.at(podTypes.indexOf(member.type));
            constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(member.name).arg(initialValue);
        }
    }

    constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(tlTypeMember).arg(type.subTypes.first().name);
    copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
    copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
    membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(tlValueName).arg(tlTypeMember));

    constructor.chop(2);
    constructor.append(QLatin1String(" { }\n\n"));

    copyConstructor.chop(2);
    copyConstructor.append(QLatin1String(" { }\n\n"));

    copyOperator.append(QString("\n%1%1return *this;\n%1}\n").arg(spacing));

    code.append(constructor);
    code.append(copyConstructor);
    code.append(copyOperator);

    code.append(QLatin1Char('\n'));
    code.append(membersCode);

    code.append(QString("};\n\n"));

    return code;
}

QString generateStreamOperatorDeclaration(const TLType &type)
{
    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();
    return QString("%1%2 &operator>>(%3 &%4);\n").arg(spacing).arg(streamClassName).arg(type.name).arg(argName);
}

QString generateStreamOperatorDefinition(const TLType &type)
{
    QString code;

    QString argName = removePrefix(type.name);
    argName[0] = argName.at(0).toLower();

    code.append(QString("%1 &%1::operator>>(%2 &%3)\n{\n").arg(streamClassName).arg(type.name).arg(argName));
    code.append(QString("%1%2 result;\n\n").arg(spacing).arg(type.name));
    code.append(QString("%1*this >> result.tlType;\n\n%1switch (result.tlType) {\n").arg(spacing));

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("%1case %2:\n").arg(spacing).arg(subType.name));

        foreach (const TLParam &member, subType.members) {
            code.append(QString("%1*this >> result.%2;\n").arg(doubleSpacing).arg(member.name));
        }

        code.append(QString("%1break;\n").arg(doubleSpacing));
    }

    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));
    code.append(QString("%1%2 = result;\n\n%1return *this;\n}\n\n").arg(spacing).arg(argName));

    return code;
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

QString generateConnectionMethodDeclaration(const TLMethod &method)
{
    return QString("%1void %2(%3);\n").arg(spacing).arg(method.name).arg(formatMethodParams(method));
}

QString generateConnectionMethodDefinition(const TLMethod &method)
{
    QString result;
    result += QString("void %1::%2(%3)\n{\n").arg(methodsClassName).arg(method.name).arg(formatMethodParams(method));
    result += spacing + QLatin1String("QByteArray output;\n");
    result += spacing + QLatin1String("CTelegramStream outputStream(&output, /* write */ true);\n\n");

    result += spacing + QString("outputStream << %1;\n").arg(formatName1stCapital(method.name));

    foreach (const TLParam &param, method.params) {
        result += spacing + QString("outputStream << %1;\n").arg(param.name);
    }

    result += QLatin1Char('\n');
    result += spacing + QLatin1String("sendEncryptedPackage(output);\n}\n\n");

    return result;
}

QMap<QString, TLType> readTypes(const QJsonDocument &document)
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

QMap<QString, TLMethod> readMethods(const QJsonDocument &document)
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

QList<TLType> solveTypes(QMap<QString, TLType> types)
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

int main(int argc, char *argv[])
{
    QFile specsFile("json");
    specsFile.open(QIODevice::ReadOnly);

    const QByteArray data = specsFile.readAll();

    if (data.isEmpty()) {
        return 1;
    }

    specsFile.close();

    const QJsonDocument document = QJsonDocument::fromJson(data);

    const QMap<QString, TLType> types = readTypes(document);
    const QList<TLType> solvedTypes = solveTypes(types);

    const QMap<QString, TLMethod> methods = readMethods(document);

    QString codeOfTLTypes;
    QString codeStreamDeclarations;
    QString codeStreamDefinition;
    QString codeConnectionDeclaration;
    QString codeConnectionDefinition;

    foreach (const TLType &type, solvedTypes) {
        if ((type.subTypes.count() == 1) && (type.subTypes.first().members.isEmpty())) {
            qDebug() << "Empty type" << type.name;
            continue;
        }

        codeOfTLTypes.append(generateTLType(type));
        codeStreamDeclarations.append(generateStreamOperatorDeclaration(type));
        codeStreamDefinition.append(generateStreamOperatorDefinition(type));
    }

    foreach (const TLMethod &method, methods) {
        if (!method.name.startsWith(QLatin1String("messages"))) {
            continue;
        }

        codeConnectionDeclaration.append(generateConnectionMethodDeclaration(method));
        codeConnectionDefinition.append(generateConnectionMethodDefinition(method));
    }

    replacingHelper(QLatin1String("../TLTypes.hpp"), 0, QLatin1String("TLTypes"), codeOfTLTypes);
    replacingHelper(QLatin1String("../CTelegramStream.hpp"), 4, QLatin1String("operators"), codeStreamDeclarations);
    replacingHelper(QLatin1String("../CTelegramStream.cpp"), 0, QLatin1String("operators implementation"), codeStreamDefinition);
    replacingHelper(QLatin1String("../CTelegramConnection.hpp"), 4, QLatin1String("Telegram API methods declaration"), codeConnectionDeclaration);
    replacingHelper(QLatin1String("../CTelegramConnection.cpp"), 0, QLatin1String("Telegram API methods implementation"), codeConnectionDefinition);

    return 0;
}
