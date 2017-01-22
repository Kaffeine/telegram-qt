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
#ifndef GENERATORNG_HPP
#define GENERATORNG_HPP

#include <QtGlobal>

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QVector>

struct TLParam {
    TLParam() { }
    TLParam(const QString &newName, const QString &newType, qint8 newFlagBit = -1) :
        name(newName), type(newType), flagBit(newFlagBit) { }

    QString name;
    QString type;
    qint8 flagBit;
    QString flagMember;

    bool dependOnFlag() const { return flagBit >= 0; }
};

struct TLSubType {
    QString name;
    quint32 id;
    QList<TLParam> members;

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
};

struct TLMethod {
    QString name;
    quint32 id;
    QList< TLParam > params;
};

class GeneratorNG
{
public:
    bool loadFromJson(const QByteArray &data);
    bool loadFromText(const QByteArray &data);
    bool resolveTypes();
    void generate();

    static QString generateTLValuesDefinition(const TLType &type);
    static QString generateTLValuesDefinition(const TLMethod &method);
    static QString generateTLTypeDefinition(const TLType &type);
    static QString generateStreamReadOperatorDeclaration(const TLType &type);
    static QString generateStreamReadOperatorDefinition(const TLType &type);
    static QString generateStreamReadVectorTemplate(const QString &type);
    static QString generateStreamWriteOperatorDeclaration(const TLType &type);
    static QString generateStreamWriteOperatorDefinition(const TLType &type);
    static QString generateStreamWriteVectorTemplate(const QString &type);

    static QString generateDebugWriteOperatorDeclaration(const TLType &type);
    static QString generateDebugWriteOperatorDefinition(const TLType &type);

    static QString generateConnectionMethodDeclaration(const TLMethod &method);
    static QString generateConnectionMethodDefinition(const TLMethod &method, QStringList &usedTypes);

    static QString generateDebugRpcParse(const TLMethod &method);

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
    QString codeConnectionDeclarations;
    QString codeConnectionDefinitions;
    QString codeDebugWriteDeclarations;
    QString codeDebugWriteDefinitions;
    QString codeDebugRpcParse;

private:
    QMap<QString, TLType> m_types;
    QList<TLType> m_solvedTypes;
    QMap<QString, TLMethod> m_functions;
    QVector<QStringList> m_groups;
};

#endif // GENERATORNG_HPP
