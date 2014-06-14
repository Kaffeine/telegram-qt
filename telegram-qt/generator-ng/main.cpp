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
static const QStringList typesToInit = QStringList() << "bool" << "quint32" << "quint64" << "double" << tlValueName;
static const QStringList initTypesValues = QStringList() << "false" << "0" << "0" << "0" << "0";
static const QStringList plainTypes = QStringList() << "Bool" << "int" << "long" << "double" << "string" << "bytes";
static const QStringList actualTypes = QStringList() << "bool" << "quint32" << "quint64" << "double" << "QString" << "QByteArray";

static const QStringList badNames = QStringList() << "lat"<< "long" ;
static const QStringList badNamesReplacers = QStringList() << "latitude"<< "longitude";

static const QString spacing = QString(4, QLatin1Char(' '));
static const QString doubleSpacing = spacing + spacing;

static const QString streamClassName = QLatin1String("CTelegramStream");

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
    if (!str.startsWith(QLatin1String("QVector<"))) {
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
        return actualTypes.at(plainTypes.indexOf(type));
    } else if (type.startsWith(QLatin1String("Vector<"))) {

        int firstIndex = type.indexOf(QLatin1Char('<')) + 1;
        int lastIndex = type.indexOf(QLatin1Char('>'));
        QString subType = type.mid(firstIndex, lastIndex - firstIndex);
        return QString("QVector<%1>").arg(formatType(subType));
    } else {
        type[0] = type.at(0).toUpper();

        return tlPrefix + formatName(type);
    }
}

struct TLTypeMember {
    TLTypeMember() { }
    TLTypeMember(const QString &newName, const QString &newType) :
        name(newName), type(newType) { }

    QString name;
    QString type;

    TLTypeMember &operator=(const TLTypeMember &anotherMember) {
        name = anotherMember.name;
        type = anotherMember.type;

        return *this;
    }
};

struct TLSubType {
    QString name;
    QList<TLTypeMember> members;

    TLSubType &operator=(const TLSubType &anotherType) {
        name = anotherType.name;
        members = anotherType.members;

        return *this;
    }

    bool haveMember(const QString &name) {
        foreach (const TLTypeMember &member, members) {
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

void debugType(const TLType &type)
{
    qDebug() << type.name;
    foreach (const TLSubType &subType, type.subTypes) {
        qDebug() << "    " << subType.name;
        foreach (const TLTypeMember &member, subType.members) {
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
        foreach (const TLTypeMember &member, subType.members) {
            if (addedMembers.contains(member.name)) {
                continue;
            }

            addedMembers.append(member.name);

            copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
            copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(member.name).arg(anotherName);

            membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(member.type).arg(member.name));

            if (!typesToInit.contains(member.type)) {
                continue;
            }

            const QString initialValue = initTypesValues.at(typesToInit.indexOf(member.type));
            constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(member.name).arg(initialValue);
        }
    }

    if (type.subTypes.count() > 1) {
        constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(tlTypeMember).arg(type.subTypes.first().name);
        copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
        copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(tlTypeMember).arg(anotherName);
        membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(tlValueName).arg(tlTypeMember));
    }

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
    code.append(QString("%1%2 type;\n").arg(spacing).arg(tlValueName));
    code.append(QString("%1*this >> type;\n\n%1switch (type) {\n").arg(spacing));

    foreach (const TLSubType &subType, type.subTypes) {
        code.append(QString("%1case %2:\n").arg(spacing).arg(subType.name));

        foreach (const TLTypeMember &member, subType.members) {
            code.append(QString("%1*this >> result.%2;\n").arg(doubleSpacing).arg(member.name));
        }

        code.append(QString("%1break;\n").arg(doubleSpacing));
    }

    code.append(QString("%1default:\n%1%1break;\n%1}\n\n").arg(spacing));

    if (type.subTypes.count() > 1) {
        code.append(QString("%1result.%2 = type;\n").arg(spacing).arg(tlTypeMember));
    }

    code.append(QString("%1%2 = result;\n\n%1return *this;\n}\n\n").arg(spacing).arg(argName));

    return code;
}

int main(int argc, char *argv[])
{
    QFile specsFile("json");
    specsFile.open(QIODevice::ReadOnly);

    const QByteArray data = specsFile.readAll();

    specsFile.close();

    const QJsonDocument json = QJsonDocument::fromJson(data);

    const QJsonArray constructors = json.object().value("constructors").toArray();

    QMap<QString, TLType> types;

    for (int i = 0; i < constructors.count(); ++i) {
        const QJsonObject obj = constructors.at(i).toObject();

        QString predicateName = obj.value("predicate").toString();

        predicateName[0] = predicateName.at(0).toUpper();

        int separatorIndex = 0;
        while ((separatorIndex = indexOfSeparator(predicateName, separatorIndex)) > 0) {
            if ((predicateName.length() < separatorIndex + 1) || (!predicateName.at(separatorIndex + 1).isLetter())) {
                return -1;
            }
            predicateName[separatorIndex + 1] = predicateName.at(separatorIndex + 1).toUpper();
            predicateName.remove(separatorIndex, 1);
        }

        quint32 id = obj.value("id").toString().toInt();

        const QString typeName = formatType(obj.value("type").toString());

        if (!actualTypes.contains(typeName)) {
            TLType tlType = types.value(typeName);
            tlType.name = typeName;

            TLSubType tlSubType;
            tlSubType.name = predicateName;

            const QJsonArray params = obj.value("params").toArray();

            foreach (const QJsonValue &paramValue, params) {
                const QJsonObject &paramObj = paramValue.toObject();
                const QString paramName = formatMember(paramObj.value("name").toString());

                const QString paramType = paramObj.value("type").toString();

                tlSubType.members.append(TLTypeMember(paramName, formatType(paramType)));
            }

            tlType.subTypes.append(tlSubType);
            types.insert(typeName, tlType);
        }

//        qDebug() << name << QString::number(id, 0x10);
    }

    QList<TLType> solvedTypes;
    QStringList solvedTypesNames = actualTypes;
    solvedTypesNames.append(tlValueName);

    int previousSolvedTypesCount = -1;

    // In order to successful compilation, type must rely only on defined types.
    while (solvedTypes.count() != previousSolvedTypesCount) { // Check for infinity loop
        previousSolvedTypesCount = solvedTypes.count();
        foreach(const QString &typeName, types.keys()) {
            const TLType &type = types.value(typeName);

            bool solved = true;

            foreach (const TLSubType &subType, type.subTypes) {
                foreach (const TLTypeMember &member, subType.members) {
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

    QString codeOfTLTypes;
    QString codeStreamDeclarations;
    QString codeStreamDefinition;

    foreach (const TLType &type, solvedTypes) {
        if ((type.subTypes.count() == 1) && (type.subTypes.first().members.isEmpty())) {
            qDebug() << "Empty type" << type.name;
            continue;
        }

        codeOfTLTypes.append(generateTLType(type));
        codeStreamDeclarations.append(generateStreamOperatorDeclaration(type));
        codeStreamDefinition.append(generateStreamOperatorDefinition(type));
    }

    replacingHelper(QLatin1String("../TLTypes.hpp"), 0, QLatin1String("TLTypes"), codeOfTLTypes);
    replacingHelper(QLatin1String("../CTelegramStream.hpp"), 0, QLatin1String("operators"), codeStreamDeclarations);
    replacingHelper(QLatin1String("../CTelegramStream.cpp"), 0, QLatin1String("operators implementation"), codeStreamDefinition);

    return 0;
}
