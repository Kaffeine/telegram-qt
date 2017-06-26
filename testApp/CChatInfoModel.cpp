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

#include "CChatInfoModel.hpp"
#include "CTelegramCore.hpp"

CChatInfoModel::CChatInfoModel(CTelegramCore *backend, QObject *parent) :
    QAbstractTableModel(parent),
    m_backend(backend)
{
    connect(m_backend, SIGNAL(peerAdded(Telegram::Peer)), this, SLOT(onPeerAdded(Telegram::Peer)));
    connect(m_backend, SIGNAL(chatChanged(quint32)), SLOT(onChatChanged(quint32)));
}

QVariant CChatInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (section) {
    case Id:
        return tr("Id");
    case Title:
        return tr("Title");
    case ParticipantsCount:
        return tr("Participants");
    case Broadcast:
        return tr("Broadcast");
    default:
        break;
    }

    return QVariant();
}

QVariant CChatInfoModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    int chatIndex = index.row();

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    if (chatIndex >= rowCount()) {
        return QVariant();
    }

    switch (section) {
    case Id:
        return m_chats.at(chatIndex).peer().id;
    case Title:
        return m_chats.at(chatIndex).title();
    case ParticipantsCount:
        return m_chats.at(chatIndex).participantsCount();
    case Broadcast:
        return m_chats.at(chatIndex).broadcast();
    default:
        break;
    }

    return QVariant();
}

void CChatInfoModel::onPeerAdded(const Telegram::Peer &peer)
{
    switch (peer.type) {
    case Telegram::Peer::Channel:
    case Telegram::Peer::Chat:
        break;
    default:
        return;
    }

    if (!peer.isValid() || haveChat(peer.id)) {
        return;
    }

    beginInsertRows(QModelIndex(), m_chats.count(), m_chats.count());
    m_peers.append(peer);
    m_chats.append(SGroupChat());
    m_backend->getChatInfo(&m_chats.last(), peer.id);
    endInsertRows();

    emit chatAdded(peer.id);
}

int CChatInfoModel::indexOfChat(quint32 id) const
{
    for (int i = 0; i < m_chats.count(); ++i) {
        if (m_chats.at(i).peer().id == id) {
            return i;
        }
    }

    return -1;
}

bool CChatInfoModel::haveChat(quint32 id) const
{
    return indexOfChat(id) >= 0;
}

const Telegram::ChatInfo *CChatInfoModel::chatById(quint32 id) const
{
    int index = indexOfChat(id);

    if (index < 0) {
        return 0;
    }

    return &m_chats.at(index);
}

Telegram::Peer CChatInfoModel::getPeer(quint32 chatId)
{
    int index = indexOfChat(chatId);

    if (index < 0) {
        return Telegram::Peer();
    }

    return m_peers.at(index);
}

void CChatInfoModel::onChatChanged(quint32 id)
{
    int i = indexOfChat(id);

    if (i < 0) {
        return;
    }

    m_backend->getChatInfo(&m_chats[i], id);
    m_chats[i].m_peer = m_chats[i].peer();
    emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
    emit chatChanged(id);
}
