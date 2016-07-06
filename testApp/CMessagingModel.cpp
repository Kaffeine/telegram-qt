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

#include "CMessagingModel.hpp"
#include "CContactModel.hpp"

#include "CTelegramCore.hpp"

#include <QDateTime>

QString messageDeliveryStatusStr(TelegramNamespace::MessageDeliveryStatus status)
{
    switch (status) {
    case TelegramNamespace::MessageDeliveryStatusUnknown:
        return QLatin1String("Unknown");
    case TelegramNamespace::MessageDeliveryStatusSent:
        return QLatin1String("Sent");
    case TelegramNamespace::MessageDeliveryStatusRead:
        return QLatin1String("Read");
    case TelegramNamespace::MessageDeliveryStatusDeleted:
        return QLatin1String("Deleted");
    default:
        return QString();
    }
}

CMessagingModel::CMessagingModel(CTelegramCore *backend, QObject *parent) :
    QAbstractTableModel(parent),
    m_backend(backend)
{
}

QVariant CMessagingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (section) {
    case Peer:
        return tr("Peer");
    case Contact:
        return tr("Phone");
    case Direction:
        return tr("Direction");
    case Timestamp:
        return tr("Timestamp");
        break;
    case MessageId:
        return tr("Message Id");
    case Message:
        return tr("Message text");
    case Status:
        return tr("Status");
    case ForwardFromContact:
        return tr("Forward from");
    case ForwardTimestamp:
        return tr("Forward timestamp");
    default:
        break;
    }

    return QVariant();
}

QVariant CMessagingModel::data(const QModelIndex &index, int role) const
{
    int section = index.column();
    int messageIndex = index.row();

    if (messageIndex >= rowCount()) {
        return QVariant();
    }

    if ((role == Qt::DecorationRole) && (section == Message)) {
        if (m_messages.at(messageIndex).mediaData.isValid()) {
            return m_messages.at(messageIndex).mediaData;
        }

        return QVariant();
    }

    if ((role != Qt::DisplayRole) && (role != Qt::EditRole)) {
        return QVariant();
    }

    return rowData(messageIndex, section);
}

QVariant CMessagingModel::rowData(quint32 messageIndex, int column) const
{
    if (int(messageIndex) >= m_messages.count()) {
        return QVariant();
    }

    switch (column) {
    case Peer:
        return QVariant::fromValue(m_messages.at(messageIndex).peer());
    case Contact:
        return m_messages.at(messageIndex).userId;
    case Direction:
        return (m_messages.at(messageIndex).flags & TelegramNamespace::MessageFlagOut) ? tr("out") : tr("in");
    case Timestamp:
        return QDateTime::fromMSecsSinceEpoch(quint64(m_messages.at(messageIndex).timestamp) * 1000);
    case MessageId:
        return m_messages.at(messageIndex).id ? m_messages.at(messageIndex).id : m_messages.at(messageIndex).id64;
    case Message:
        return m_messages.at(messageIndex).text;
    case Status:
        if (m_messages.at(messageIndex).flags & TelegramNamespace::MessageFlagOut) {
            return messageDeliveryStatusStr(m_messages.at(messageIndex).status);
        } else {
            return tr("Incoming");
        }
    case ForwardFromContact:
        return m_messages.at(messageIndex).forwardContactId;
    case ForwardTimestamp:
        if (m_messages.at(messageIndex).fwdTimestamp) {
            return QDateTime::fromMSecsSinceEpoch(quint64(m_messages.at(messageIndex).fwdTimestamp) * 1000);
        }
        break;
    default:
        break;
    }

    return QVariant();
}

const CMessagingModel::SMessage *CMessagingModel::messageAt(quint32 messageIndex) const
{
    if (int(messageIndex) >= m_messages.count()) {
        return 0;
    }

    return &m_messages[messageIndex];
}

int CMessagingModel::messageIndex(quint64 messageId) const
{
    for (int i = 0; i < m_messages.count(); ++i) {
        if (m_messages.at(i).id == messageId) {
            return i;
        }
        if (m_messages.at(i).id64 == messageId) {
            return i;
        }
    }

    return -1;
}

void CMessagingModel::addMessage(const SMessage &message)
{
    for (int i = 0; i < m_messages.count(); ++i) {
        if ((m_messages.at(i).id64 && (m_messages.at(i).id64 == message.id64))
                || (!m_messages.at(i).id64 && (m_messages.at(i).id == message.id))) {
            m_messages.replace(i, message);

            emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
            return;
        }
    }
    beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
    m_messages.append(message);
    if (!m_messages.last().timestamp) {
        m_messages.last().timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
    }
    endInsertRows();
}

int CMessagingModel::setMessageMediaData(quint64 messageId, const QVariant &data)
{
    int i = messageIndex(messageId);
    if (i < 0) {
        return i;
    }

    m_messages[i].mediaData = data;
#if QT_VERSION < 0x050000
    emit dataChanged(index(i, Message), index(i, Message));
#else
    emit dataChanged(index(i, Message), index(i, Message), QVector<int>() << Qt::DecorationRole);
#endif
    return i;
}

void CMessagingModel::setMessageDeliveryStatus(const QString &phone, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status)
{
    Q_UNUSED(phone);
    for (int i = 0; i < m_messages.count(); ++i) {
        if (m_messages.at(i).id64 == messageId) {
            m_messages[i].status = status;

            QModelIndex messageIndex = index(i, Status);
            emit dataChanged(messageIndex, messageIndex);
            break;
        }
    }
}
