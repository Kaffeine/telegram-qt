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
#include <QHash>

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

struct TLType {
    QString name;
    QList<TLTypeMember> members;
    QStringList types;

    TLType &operator=(const TLType &anotherType) {
        name = anotherType.name;
        members = anotherType.members;
        types = anotherType.types;

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

void debugType(const TLType &type)
{
    qDebug() << type.name;
    qDebug() << type.types;
    foreach (const TLTypeMember &member, type.members) {
        qDebug() << "    " << member.type << member.name;
    }
}

QString generateTLType(const TLType &type)
{
    QString code;

    static const QString spacing = QString(4, QLatin1Char(' '));

    code.append(QString("struct %1 {\n").arg(type.name));

    QString anotherName = type.name;
    if (anotherName.startsWith(tlPrefix)) {
        anotherName = anotherName.mid(tlPrefix.size());
    }

    anotherName.prepend(QLatin1String("another"));

    QString constructor = spacing + QString("%1() :\n").arg(type.name);
    QString copyConstructor = spacing + QString("%1(const %1 &%2) :\n").arg(type.name).arg(anotherName);
    QString copyOperator = spacing + QString("%1 &operator=(const %1 &%2) {\n").arg(type.name).arg(anotherName);
    QString membersCode;

    for (int i = 0; i < type.members.count(); ++i) {
        static const QString doubleSpacing = spacing + spacing;

        const TLTypeMember &member = type.members.at(i);

        copyConstructor += QString("%1%2(%3.%2),\n").arg(doubleSpacing).arg(member.name).arg(anotherName);
        copyOperator += QString("%1%2 = %3.%2;\n").arg(doubleSpacing).arg(member.name).arg(anotherName);

        membersCode.append(QString("%1%2 %3;\n").arg(spacing).arg(member.type).arg(member.name));

        if (!typesToInit.contains(member.type)) {
            continue;
        }

        QString initialValue;
        if (member.name == tlTypeMember) {
            initialValue = type.types.first(); // ?
        } else {
            initialValue = initTypesValues.at(typesToInit.indexOf(member.type));
        }
        constructor += QString("%1%2(%3),\n").arg(doubleSpacing).arg(member.name).arg(initialValue);
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

int main(int argc, char *argv[])
{
    QFile specsFile("json");
    specsFile.open(QIODevice::ReadOnly);

    const QByteArray data = specsFile.readAll();

    specsFile.close();

    const QJsonDocument json = QJsonDocument::fromJson(data);

    const QJsonArray constructors = json.object().value("constructors").toArray();


    QHash<QString, TLType> types;

    for (int i = 0; i < constructors.count(); ++i) {
        const QJsonObject obj = constructors.at(i).toObject();

        QString name = obj.value("predicate").toString();

        name[0] = name.at(0).toUpper();

        int separatorIndex = 0;
        while ((separatorIndex = indexOfSeparator(name, separatorIndex)) > 0) {
            if ((name.length() < separatorIndex + 1) || (!name.at(separatorIndex + 1).isLetter())) {
                return -1;
            }
            name[separatorIndex + 1] = name.at(separatorIndex + 1).toUpper();
            name.remove(separatorIndex, 1);
        }

        quint32 id = obj.value("id").toString().toInt();

        const QString typeName = formatType(obj.value("type").toString());

        if (!actualTypes.contains(typeName)) {
            TLType tlType = types.value(typeName);
            tlType.name = typeName;
            tlType.types.append(name);

            const QJsonArray params = obj.value("params").toArray();

            foreach (const QJsonValue &paramValue, params) {
                const QJsonObject &paramObj = paramValue.toObject();
                const QString paramName = formatMember(paramObj.value("name").toString());

                if (tlType.haveMember(paramName)) {
                    continue;
                }

                const QString paramType = paramObj.value("type").toString();

                if (!tlType.members.isEmpty() && (tlType.members.last().name == tlTypeMember)) {
                    tlType.members.insert(tlType.members.count() - 1, TLTypeMember(paramName, formatType(paramType)));
                } else {
                    tlType.members.append(TLTypeMember(paramName, formatType(paramType)));
                }
            }

            if (tlType.types.count() == 2) {
                tlType.members.append(TLTypeMember(tlTypeMember, tlValueName));
            }

            types.insert(typeName, tlType);
        }

        qDebug() << name << QString::number(id, 0x10);
    }

    QString code;

    QList<TLType> solvedTypes;
    QStringList solvedTypesNames = actualTypes;
    solvedTypesNames.append(tlValueName);

    int previousSolvedTypesCount = -1;

    while (solvedTypes.count() != previousSolvedTypesCount) { // Check for infinity loop
        previousSolvedTypesCount = solvedTypes.count();
        foreach(const QString &typeName, types.keys()) {
            const TLType &type = types.value(typeName);

            bool solved = true;

            foreach (const TLTypeMember &member, type.members) {
                QString memberType = getTypeOrVectorType(member.type);

                if (!solvedTypesNames.contains(memberType)) {
                    solved = false;
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

    foreach (const TLType &type, solvedTypes) {
        if (type.members.isEmpty()) {
            qDebug() << "Empty type" << type.name;
            continue;
        }

        code.append(generateTLType(type));
    }

    replacingHelper(QLatin1String("../TLTypes.hpp"), 0, QLatin1String("TLTypes"), code);

    return 0;
}
