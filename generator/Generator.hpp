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
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <QtGlobal>

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QVariantHash>
#include <QVector>
#include <functional>

QT_FORWARD_DECLARE_CLASS(QJsonDocument)

struct Name {
    QString name;
    virtual ~Name() { }
};

struct NameWithEntityType : public Name
{
    virtual QString entityType() const = 0;
};

struct TLParam {
    TLParam() { }
    TLParam(const QString &newName, const QString &newType, qint8 newFlagBit = -1) :
        flagBit(newFlagBit), m_name(newName) { setType(newType); }

    qint8 flagBit = -1;
    QString flagMember;
    QString flagName() const;

    QString type() const { return m_type; }
    QString bareType() const { return m_bareType; }
    void setType(const QString &newType);

    bool isVector() const { return m_isVector; }

    bool accessByPointer() const { return m_accessByPointer; }
    void setAccessByPointer(bool accessByPointer) { m_accessByPointer = accessByPointer; }

    QString getAlias() const { return !m_alias.isEmpty() ? m_alias : m_name; }
    void setAlias(const QString &newAlias) { m_alias = newAlias; }

    QString getName() const { return m_name; }
    void setName(const QString &newName) { m_name = newName; }
    bool dependOnFlag() const { return flagBit >= 0; }

protected:
    QString m_type;
    QString m_bareType;
    QString m_alias;
    QString m_name;
    bool m_isVector = false;
    bool m_accessByPointer = false;
};

struct TLSubType : public Name {
    quint32 id;
    QList<TLParam> members;
    QString source; // The source from the spec
};

struct TLType : public NameWithEntityType {
    QString entityType() const override { return QStringLiteral("Value"); }
    QList<TLSubType> subTypes;

    bool isSelfReferenced() const { return m_selfReferenced; }
    void setSelfReferenced(const bool referenced) { m_selfReferenced = referenced; }

protected:
    bool m_selfReferenced = false;
};

struct TLMethod : public NameWithEntityType {
    QString entityType() const override { return QStringLiteral("Function"); }
    QString nameFirstCapital() const {
        if (name.isEmpty()) {
            return QString();
        }
        QString capital = name;
        capital[0] = capital.at(0).toUpper();
        return capital;
    }
    quint32 id;
    QString type;
    QString source; // The source from the spec
    QList< TLParam > params;
};

class Generator
{
public:
    struct LineParseResult {
        bool isValid() const { return predicateId && !predicateName.isEmpty() && !typeName.isEmpty(); }
        QString predicateName;
        QString typeName;
        QList<TLParam> params;
        quint32 predicateId = 0;
    };

    enum class FirstLetterCase {
        Any, // Keep same
        Upper,
        Lower,
    };

    Generator();
    bool loadFromJson(const QByteArray &data);
    bool loadFromText(const QByteArray &data);
    bool resolveTypes();
    void setExistsRpcProcessDefinitions(const QString &code);
    void generate();

    static QString getTypeOrVectorType(const QString &str, bool *isVectorPtr = nullptr);
    static qint8 flagBitForMember(const QStringRef &type, QString *flagMember);

    static QMap<QString, TLType> readTypesJson(const QJsonDocument &document);
    static QMap<QString, TLMethod> readFunctionsJson(const QJsonDocument &document);

    static QString removeSeparators(QString name);
    static QString formatName(const QString &name, FirstLetterCase firstCase = FirstLetterCase::Any) { return formatName(QStringList({name}), firstCase); }
    static QString formatName(const QStringList &nameParts, FirstLetterCase firstCase = FirstLetterCase::Any);
    static QString formatType(QString type);
    static QString formatMember(QString name, const QVariantHash &context = {});
    static QString formatMethodParam(const TLParam &param);
    static QString formatMethodParams(const TLMethod &method);
    static QByteArray getPredicateForCrc32(const QByteArray &sourceLine);
    static quint32 getCrc32(const QByteArray &bytes);
    static LineParseResult parseLine(const QString &line);

    QMap<QString, TLType> types() const { return m_types; }
    QList<TLType> solvedTypes() const { return m_solvedTypes; }
    QMap<QString, TLMethod> functions() const { return m_functions; }
    QVector<QStringList> groups() const { return m_groups; }

    void setAddSpecSources(bool addSources);

    static QString removeWord(QString input, QString word);
    static QString generateTLValuesDefinition(const TLType &type);
    static QString generateTLValuesDefinition(const TLMethod &method);
    static QString generateTLTypeDefinition(const TLType &type, bool addSpecSources = false);
    static QStringList generateTLTypeMemberFlags(const TLType &type);
    static QStringList generateTLTypeMemberGetters(const TLType &type);
    static QStringList generateTLTypeMembers(const TLType &type);

    static QString streamReadImplementationHead(const QString &argName, const QString &typeName);
    static QString streamReadImplementationEnd(const QString &argName);
    static QString streamReadPerTypeImplementation(const QString &argName, const TLSubType &subType);

    static QString streamWriteImplementationHead(const QString &argName, const QString &typeName);
    static QString streamWriteFreeImplementationHead(const QString &argName, const QString &typeName);
    static QString streamWriteImplementationEnd(const QString &argName);
    static QString streamWriteFreeImplementationEnd(const QString &argName);
    static QString streamWritePerTypeImplementation(const QString &argName, const TLSubType &subType);
    static QString streamWritePerTypeFreeImplementation(const QString &argName, const TLSubType &subType);
    static QString streamWritePerTypeImplementationBase(const QString &argName, const TLSubType &subType, const QString &streamGetter);

    static QString generateStreamOperatorDefinition(const TLType &type,
                                                    std::function<QString(const QString &argName, const QString &typeName)> head,
                                                    std::function<QString(const QString &argName, const TLSubType &subType)> generateSubtypeCode,
                                                    std::function<QString(const QString &argName)> end
                                                    );
    static QString generateStreamReadOperatorDeclaration(const TLType &type);
    static QString generateStreamReadFreeOperatorDeclaration(const NameWithEntityType *type);
    static QString generateStreamReadOperatorDefinition(const TLType &type);
    static QString generateStreamReadVectorTemplate(const QString &type);
    static QString generateStreamWriteOperatorDeclaration(const TLType &type);
    static QString generateStreamWriteFreeOperatorDeclaration(const NameWithEntityType *type);
    static QString generateStreamWriteOperatorDefinition(const TLType &type);
    static QString generateStreamWriteFreeOperatorDefinition(const TLType &type);
    static QString generateStreamWriteVectorTemplate(const QString &type);
    static QString generateStreamWriteFreeVectorTemplate(const QString &type);

    static QString generateDebugWriteOperatorDeclaration(const TLType &type);
    static QString debugOperatorImplementationHead(const QString &argName, const QString &typeName);
    static QString debugOperatorImplementationEnd(const QString &argName);
    static QString debugOperatorPerTypeImplementation(const QString &argName, const TLSubType &subType);
    static QString generateDebugWriteOperatorDefinition(const TLType &type);

    static QString generateConnectionMethodDeclaration(const TLMethod &method);
    static QString generateConnectionMethodDefinition(const TLMethod &method, QStringList &usedTypes);
    static QString generateRpcProcessDeclaration(const TLMethod &method);
    static QString generateRpcProcessSampleDefinition(const TLMethod &method);
    static QString generateRpcProcessSwitchCase(const TLMethod &method);

    static QString generateDebugRpcParse(const TLMethod &method);

    static QStringList reorderLinesAsExist(QStringList newLines, QStringList existLines);

    static QList<TLType> solveTypes(QMap<QString, TLType> types, QMap<QString, TLType> *unresolved = nullptr);

    void getUsedAndVectorTypes(QStringList &usedTypes, QStringList &vectors) const;

    QString codeOfTLValues;
    QString codeOfTLTypes;
    QString codeStreamReadDeclarations;
    QString codeStreamReadDefinitions;
    QString codeStreamReadTemplateInstancing;
    QString codeStreamWriteDeclarations;
    QString codeStreamWriteDefinitions;
    QString codeStreamWriteTemplateInstancing;
    QString codeStreamExtraReadDeclarations;
    QString codeStreamExtraWriteDeclarations;
    QString codeStreamExtraWriteDefinitions;
    QString codeConnectionDeclarations;
    QString codeConnectionDefinitions;
    QString codeRpcProcessDeclarations;
    QString codeRpcProcessDefinitions;
    QString codeRpcProcessSwitchCases;
    QString codeRpcProcessSwitchUpdatesCases;
    QString existsStreamReadTemplateInstancing;
    QString existsStreamWriteTemplateInstancing;
    QString existsCodeRpcProcessDefinitions;
    QString codeDebugWriteDeclarations;
    QString codeDebugWriteDefinitions;
    QString codeDebugRpcParse;

private:
    QMap<QString, TLType> m_types;
    QList<TLType> m_solvedTypes;
    QMap<QString, TLMethod> m_functions;
    QVector<QStringList> m_groups;
    bool m_addSpecSources;
};

#endif // GENERATORNG_HPP
