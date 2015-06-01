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

CChatInfoModel::CChatInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{

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
        return m_chats.at(chatIndex).id;
    case Title:
        return m_chats.at(chatIndex).title;
    case ParticipantsCount:
        return m_chats.at(chatIndex).participantsCount;
    default:
        break;
    }

    return QVariant();
}

void CChatInfoModel::addChat(int id)
{
    beginInsertRows(QModelIndex(), m_chats.count(), m_chats.count());
    m_chats.append(TelegramNamespace::GroupChat(id));
    endInsertRows();
}

bool CChatInfoModel::haveChat(quint32 id)
{
    for (int i = 0; i < m_chats.count(); ++i) {
        if (m_chats.at(i).id == id) {
            return true;
        }
    }
    return false;
}

void CChatInfoModel::setChat(const TelegramNamespace::GroupChat &chat)
{
    for (int i = 0; i < m_chats.count(); ++i) {
        if (m_chats.at(i).id != chat.id) {
            continue;
        }

        m_chats[i] = chat;
        emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
        return;
    }
}
