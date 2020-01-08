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

    QString nameFirstCapital() const {
        if (name.isEmpty()) {
            return QString();
        }
        QString capital = name;
        capital[0] = capital.at(0).toUpper();
        return capital;
    }

    virtual ~Name() { }
};

struct TypedEntity : public Name
{
    virtual QString getEntityTLType() const = 0;
    virtual QString entityType() const = 0; // Returns string "Function" or "Value"

    QString variableName() const;
};

struct Predicate : public TypedEntity
{
    enum PredicateType {
        Invalid,
        Function,
        Type,
    };

    bool generateOnlyPredicateId = false; // Generate only TLValue

    quint32 predicateId = 0;
    PredicateType predicateType = Invalid;
    QString predicateName() const;
    QString source; // The source from the spec
};

struct TLParam {
    TLParam() { }
    TLParam(const QString &newName, const QString &newType, qint8 newFlagBit = -1) :
        flagBit(newFlagBit), m_name(newName) { setType(newType); }

    qint8 flagBit = -1;
    QString flagMember;
    QString flagName() const;
    void setFlagName(const QString &flagName);

    QString getType() const { return type(); }

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
    QString m_flagName;
    bool m_isVector = false;
    bool m_accessByPointer = false;
};

struct TLSubType : public Predicate {
    QString entityType() const override { return QStringLiteral("Value"); }
    QString getEntityTLType() const override { return name; }
    QMap<quint8, QString> getBoolFlags() const;
    QList<TLParam> members;
};

struct TLType : public TypedEntity {
    QString entityType() const override { return QStringLiteral("Value"); }
    QString getEntityTLType() const override { return name; }

    QMap<quint8, QString> getBoolFlags() const;

    QList<TLSubType> subTypes;

    bool isSelfReferenced() const { return m_selfReferenced; }
    void setSelfReferenced(const bool referenced) { m_selfReferenced = referenced; }

protected:
    bool m_selfReferenced = false;
};

struct TLMethod : public Predicate {
    QString entityType() const override { return QStringLiteral("Function"); }
    QString getEntityTLType() const override { return functionTypeName(); }
    QString functionTypeName() const;
    QString nameFromSecondWord() const;
    QString type;
    QList< TLParam > params;
};

class Generator
{
    Q_GADGET
public:
    struct LineParseResult {
        bool isValid() const { return predicateId && !predicateName.isEmpty() && !typeName.isEmpty(); }
        QString predicateName;
        QString typeName;
        QList<TLParam> params;
        quint32 predicateId = 0;
    };

    enum class FormatOption {
        None = 0,
        UpperCaseFirstLetter = 1 << 1,
        LowerCaseFirstLetter = 1 << 2,
        SkipFirstWord = 1 << 3,
        RemoveSeparators = 1 << 4,
        SkipTl = 1 << 5,
    };
    Q_ENUM(FormatOption)
    Q_DECLARE_FLAGS(FormatOptions, FormatOption)

    Generator();

    static QString spacing;
    static QString doubleSpacing;

    bool loadFromJson(const QByteArray &data);
    bool loadFromText(const QByteArray &data);
    bool resolveTypes();
    void generate();
    QStringList generateTLValues() const;

    void dumpReadData() const;
    void dumpSolvedTypes() const;

    QStringList functionGroups() const { return m_functionGroups; }

    struct MethodsCode {
        QStringList usings;
        QStringList declarations;
        QStringList definitions;
    };
    MethodsCode generateClientFunctions(const QString &prefix) const;

    static QString getTypeOrVectorType(const QString &str, bool *isVectorPtr = nullptr);
    static qint8 flagBitForMember(const QStringRef &type, QString *flagMember);

    static QMap<QString, TLType> readTypesJson(const QJsonDocument &document);
    static QMap<QString, TLMethod> readFunctionsJson(const QJsonDocument &document);

    static QString removeSeparators(QString name);
    static QString joinLinesWithPrepend(const QStringList &lines, const QString &prep = QString(), const QString &sep = QString());
    static QString formatName(const QString &name, const FormatOptions options = FormatOption::None);
    static QString formatName(const QStringList &nameParts, const FormatOptions options = FormatOption::None);
    static QString formatType(QString type);
    static QString formatMember(QString name, const QVariantHash &context = {});
    static QString formatMethodParam(const TLParam &param);
    static QString formatMethodParams(const TLMethod &method);
    static QByteArray getBarePredicate(const QByteArray &sourceLine);
    static quint32 getCrc32(const QByteArray &bytes);
    static LineParseResult parseLine(const QString &line);

    QMap<QString, TLType> types() const { return m_types; }
    QList<TLType> solvedTypes() const { return m_solvedTypes; }
    QMap<QString, TLMethod> functions() const { return m_functions; }
    QVector<QStringList> groups() const { return m_groups; }

    void setAddSpecSources(bool addSources);

    static QStringList getWords(const QString &input);
    static QString removeWord(QString input, QString word);
    static QString generateTLValuesDefinition(const Predicate *predicate);
    static QString generateTLTypeDefinition(const TLType &type, bool addSpecSources = false);
    static QStringList generateTLTypeMemberFlags(const TLType &type);
    static QStringList generateTLTypeMemberGetters(const TLType &type);
    static QStringList generateTLTypeMembers(const TLType &type);

    static QString streamReadImplementationHead(const TypedEntity *type);
    static QString streamReadImplementationEnd(const QString &argName);
    static QString streamReadPerTypeImplementation(const TypedEntity *type, const TLSubType &subType);
    static QString streamReadFunctionFreeImplementationHead(const TypedEntity *type);
    static QString streamReadFunctionFreeImplementationEnd();
    static QString streamReadFunctionFreePerArgumentImplementation(const TypedEntity *type, const TLParam &param);

    static QString streamWriteImplementationHead(const TypedEntity *type);
    static QString streamWriteFreeImplementationHead(const TypedEntity *type);
    static QString streamWriteImplementationEnd(const QString &argName);
    static QString streamWriteFreeImplementationEnd(const QString &argName);
    static QString streamWritePerTypeImplementation(const TypedEntity *type, const TLSubType &subType);
    static QString streamWritePerTypeFreeImplementation(const TypedEntity *type, const TLSubType &subType);
    static QString streamWritePerTypeImplementationBase(const TypedEntity *type, const TLSubType &subType, const QString &streamGetter);

    static QString generateStreamOperatorDefinition(const TLType *type,
                                                    std::function<QString(const TypedEntity *type)> head,
                                                    std::function<QString(const TypedEntity *type, const TLSubType &subType)> generateSubtypeCode,
                                                    std::function<QString(const QString &argName)> end
                                                    );

    static QString generateStreamOperatorDefinition(const TLMethod *type,
                                                    std::function<QString(const TypedEntity *type)> head,
                                                    std::function<QString(const TypedEntity *type, const TLParam &param)> generateSubtypeCode,
                                                    std::function<QString()> end
                                                    );
    static QString streamReadOperatorDeclaration(const TypedEntity *type);
    static QString streamReadFreeOperatorDeclaration(const TypedEntity *type);
    static QString streamReadFreeOperatorDefinition(const TLMethod *method);
    static QString streamReadOperatorDefinition(const TLType *type);
    static QString streamReadVectorTemplate(const QString &type);
    static QString streamWriteOperatorDeclaration(const TLType *type);
    static QString streamWriteFreeOperatorDeclaration(const TypedEntity *type);
    static QString streamWriteOperatorDefinition(const TLType *type);
    static QString streamWriteFreeOperatorDefinition(const TLType *type);
    static QString streamWriteVectorTemplate(const QString &type);
    static QString streamWriteFreeVectorTemplate(const QString &type);

    QStringList generateRpcReplyTemplates(const QString &groupName) const;

    static QString generateDebugWriteOperatorDeclaration(const TLType *type);
    static QString debugOperatorImplementationHead(const TypedEntity *type);
    static QString debugOperatorImplementationEnd(const QString &argName);
    static QString debugOperatorPerTypeImplementation(const TypedEntity *type, const TLSubType &subType);
    static QString generateDebugWriteOperatorDefinition(const TLType *type);

    static QString generateConnectionMethodDeclaration(const TLMethod &method);
    static QString generateConnectionMethodDefinition(const TLMethod &method, QStringList &usedTypes);
    static QString generateRpcProcessDeclaration(const TLMethod &method);
    static QString generateRpcProcessSampleDefinition(const TLMethod &method);
    static QString generateRpcProcessSwitchCase(const TLMethod &method);

    QString generateFunctionStructs() const;
    static QString generateFunctionStruct(const TLMethod &method);
    MethodsCode generateFunctionStreamOperators() const;
    QStringList generateTypeFlagsToString() const;

    QStringList serverRpcFactoryIncludes() const;
    QStringList serverRpcFactoryInitialization() const;
    MethodsCode generateServerRpcProcessMethods(const QString &groupName) const;
    QStringList generateServerRpcMembers(const QString &groupName) const;
    QStringList generateServerMethodForRpcFunction(const QString &groupName) const;

    MethodsCode generateServerRpcRunMethods(const QString &groupName, const QString &previousSourceCode) const;

    static QString generateDebugRpcParse(const TLMethod &method);

    static QStringList reorderLinesAsExist(QStringList newLines, QStringList existLines);

    static QList<TLType> solveTypes(QMap<QString, TLType> types, QMap<QString, TLType> *unresolved = nullptr);

    void getUsedAndVectorTypes(QStringList &usedTypes, QStringList &vectors) const;

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
    QString codeDebugWriteDeclarations;
    QString codeDebugWriteDefinitions;
    QString codeDebugRpcParse;

private:
    QVector<Predicate*> m_extraPredicates;
    QMap<QString, TLType> m_types;
    QList<TLType> m_solvedTypes;
    QMap<QString, TLMethod> m_functions;
    QVector<QStringList> m_groups;
    bool m_addSpecSources;
    QStringList m_functionGroups;
};

Q_DECLARE_METATYPE(Generator::FormatOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(Generator::FormatOptions)

#endif // GENERATORNG_HPP
