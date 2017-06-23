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

#ifndef CCHATINFOMODEL_HPP
#define CCHATINFOMODEL_HPP

#include <QAbstractTableModel>
#include <QPixmap>
#include <QSet>

#include "TelegramNamespace.hpp"

class CTelegramCore;
class CFileManager;

struct SGroupChat : Telegram::ChatInfo {
    SGroupChat() :
        Telegram::ChatInfo()
    {
    }

    Telegram::Peer m_peer;
    QPixmap m_picture;
    QString m_pictureToken;
};

class CChatInfoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Id,
        Title,
        Picture,
        ParticipantsCount,
        Broadcast,
        ColumnsCount
    };

    explicit CChatInfoModel(CTelegramCore *backend, QObject *parent = 0);

    void setFileManager(CFileManager *manager);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int indexOfChat(const Telegram::Peer peer) const;
    int indexOfChat(quint32 id) const;
    bool haveChat(quint32 id) const;
    const Telegram::ChatInfo *chatById(quint32 id) const;

    Telegram::Peer getPeer(quint32 chatId);

signals:
    void chatAdded(quint32 id);
    void chatChanged(quint32 id);

protected slots:
    void onPeerAdded(const Telegram::Peer &peer);
    void onChatChanged(quint32 id);
    void onFileRequestComplete(const QString &uniqueId);

private:
    QString getPictureCacheToken(const Telegram::Peer &peer) const;
    QString getPictureCacheToken(const QString &key) const;
    CTelegramCore *m_backend;
    CFileManager *m_fileManager;
    QSet<QString> m_requests;

    QList<SGroupChat> m_chats;
    QVector<Telegram::Peer> m_peers;

};

inline int CChatInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CChatInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_chats.count();
}

#endif // CCHATINFOMODEL_HPP
