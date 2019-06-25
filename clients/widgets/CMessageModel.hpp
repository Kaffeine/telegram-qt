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

#ifndef CMESSAGEMODEL_HPP
#define CMESSAGEMODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Client;

} // Client namespace

} // Telegram namespace

class CContactModel;
class CFileManager;

class CMessageModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Peer,
        Contact,
        Direction,
        Timestamp,
        MessageId,
        Message,
        Status,
        ForwardFrom,
        ForwardTimestamp,
        ColumnsCount,
        PeerText,
        ForwardFromText
    };

    struct SMessage : public Telegram::Message
    {
        enum Status {
            StatusUnknown,
            StatusSent,
            StatusReceived,
            StatusRead,
            StatusDeleted
        };

        SMessage() :
            Telegram::Message(),
            id64(0),
            status(StatusUnknown)
        {
        }

        SMessage(const Telegram::Message &m);

        quint64 id64;
        Status status;
        QVariant mediaData;
    };

    explicit CMessageModel(Telegram::Client::Client *backend, QObject *parent = nullptr);
    void setFileManager(CFileManager *manager);
    void setContactsModel(CContactModel *model);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QString peerToText(const Telegram::Peer &peer) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant rowData(quint32 messageIndex, int column) const;
    const SMessage *messageAt(quint32 messageIndex) const;

    int messageIndex(quint64 messageId) const; // Messages id should be quint32, but it require "outgoing random to incremental message id resolving" (Not implemented yet).

public slots:
    void addMessage(const SMessage &message);
#if 0
    void onFileRequestComplete(const QString &uniqueId);
    int setMessageMediaData(quint64 messageId, const QVariant &data);
#endif
    void setMessageRead(Telegram::Peer peer, quint32 messageId, bool out);
    void setMessageInboxRead(Telegram::Peer peer, quint32 messageId);
    void setMessageOutboxRead(Telegram::Peer peer, quint32 messageId);
    void setResolvedMessageId(quint64 randomId, quint32 resolvedId);
    void clear();

private:
    Telegram::Client::Client *m_backend = nullptr;
    CFileManager *m_fileManager = nullptr;
    CContactModel *m_contactsModel = nullptr;
    QList<SMessage> m_messages;
    QHash<QString,quint64> m_fileRequests; // uniqueId to messageId

};

inline int CMessageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CMessageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_messages.count();
}

#endif // CMESSAGEMODEL_HPP
