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

#ifndef GENERATORNG_HPP
#define GENERATORNG_HPP

#include <QtGlobal>

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>

#include <QJsonDocument>

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
    quint32 id;
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
    quint32 id;
    QList< TLParam > params;

    TLMethod &operator=(const TLMethod &anotherMethod) {
        name = anotherMethod.name;
        params = anotherMethod.params;

        return *this;
    }
};

class GeneratorNG
{
public:
    bool loadData(const QByteArray &data);
    void generate();

    static QString generateTLValuesDefinition(const TLType &type);
    static QString generateTLValuesDefinition(const TLMethod &method);
    static QString generateTLTypeDefinition(const TLType &type);
    static QString generateStreamReadOperatorDeclaration(const TLType &type);
    static QString generateStreamReadOperatorDefinition(const TLType &type);
    static QString generateStreamWriteOperatorDeclaration(const TLType &type);
    static QString generateStreamWriteOperatorDefinition(const TLType &type);

    static QString generateDebugWriteOperatorDeclaration(const TLType &type);
    static QString generateDebugWriteOperatorDefinition(const TLType &type);

    static QString generateConnectionMethodDeclaration(const TLMethod &method);
    QString generateConnectionMethodDefinition(const TLMethod &method);

    static QMap<QString, TLType> readTypes(const QJsonDocument &document);
    static QMap<QString, TLMethod> readMethods(const QJsonDocument &document);
    static QList<TLType> solveTypes(QMap<QString, TLType> types);

    QString codeOfTLValues;
    QString codeOfTLTypes;
    QString codeStreamReadDeclarations;
    QString codeStreamReadDefinitions;
    QString codeStreamWriteDeclarations;
    QString codeStreamWriteDefinitions;
    QString codeConnectionDeclarations;
    QString codeConnectionDefinitions;
    QString codeDebugWriteDeclarations;
    QString codeDebugWriteDefinitions;

private:
    static QString formatType(QString type);
    static QString formatName(QString name);
    static QString formatName1stCapital(QString name);

    static QString removePrefix(const QString &str);

    static QString formatMember(QString name);

    static QString getTypeOrVectorType(const QString &str);

    static QString formatMethodParam(const TLParam &param);
    static QString formatMethodParams(const TLMethod &method);

    QMap<QString, TLType> m_types;
    QList<TLType> m_solvedTypes;
    QMap<QString, TLMethod> m_methods;

    QStringList m_usedWriteOperators;
};

#endif // GENERATORNG_HPP
