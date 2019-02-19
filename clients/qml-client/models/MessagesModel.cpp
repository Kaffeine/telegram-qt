/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "MessagesModel.hpp"

#include <QDateTime>
#include <QDebug>
#include <QTimer>

#include "../../imports/TelegramQtQml/DeclarativeClient.hpp"

#include "Client.hpp"
#include "DataStorage.hpp"
#include "DialogList.hpp"
#include "PendingOperation.hpp"
#include "MessagingApi.hpp"
#include "Debug.hpp"

#include "Operations/ClientMessagesOperation.hpp"

namespace Telegram {

namespace Client {

static const int UserRoleOffset = Qt::UserRole + 1;

//QString messageDeliveryStatusStr(MessagesModel::SMessage::Status status)
//{
//    switch (status) {
//    case MessagesModel::SMessage::StatusUnknown:
//        return QLatin1String("Unknown");
//    case MessagesModel::SMessage::StatusSent:
//        return QLatin1String("Sent");
//    case MessagesModel::SMessage::StatusReceived:
//        return QLatin1String("Received");
//    case MessagesModel::SMessage::StatusRead:
//        return QLatin1String("Read");
//    case MessagesModel::SMessage::StatusDeleted:
//        return QLatin1String("Deleted");
//    default:
//        return QString();
//    }
//}

//MessagesModel::SMessage::SMessage(const Telegram::Message &m) :
//    Telegram::Message(m),
//    id64(0),
//    status(StatusUnknown)
//{
//    if (flags & TelegramNamespace::MessageFlagRead) {
//        status = StatusRead;
//    } else if (flags & TelegramNamespace::MessageFlagOut) {
//        status = StatusSent;
//    } else {
//        status = StatusReceived;
//    }
//}

/*!
    \class MessagesModel
    \brief provides a data model for all kind of events
    \inmodule Models
*/

MessagesModel::MessagesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
//    connect(m_backend, SIGNAL(sentMessageIdReceived(quint64,quint32)),
//            SLOT(setResolvedMessageId(quint64,quint32)));

//    connect(m_backend, SIGNAL(messageReadInbox(Telegram::Peer,quint32)),
//            SLOT(setMessageInboxRead(Telegram::Peer,quint32)));
//    connect(m_backend, SIGNAL(messageReadOutbox(Telegram::Peer,quint32)),
    //            SLOT(setMessageOutboxRead(Telegram::Peer,quint32)));
    connect(this, &MessagesModel::peerChanged,
            this, &MessagesModel::onPeerChanged);
}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_events.count();
}

//void MessagesModel::setFileManager(CFileManager *manager)
//{
//    m_fileManager = manager;
//    connect(m_fileManager, &CFileManager::requestComplete, this, &MessagesModel::onFileRequestComplete);
//}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
    static const QHash<int, QByteArray> extraRoles {
        { UserRoleOffset + static_cast<int>(Role::Identifier), "identifier" },
        { UserRoleOffset + static_cast<int>(Role::Contact), "sender" },
        { UserRoleOffset + static_cast<int>(Role::MessageType), "messageType" },
        { UserRoleOffset + static_cast<int>(Role::EventType), "eventType" },
        { UserRoleOffset + static_cast<int>(Role::Timestamp), "timestamp" },
        { UserRoleOffset + static_cast<int>(Role::SentTimestamp), "sentTimestamp" },
        { UserRoleOffset + static_cast<int>(Role::ReceivedTimestamp), "receivedTimestamp" },
        { UserRoleOffset + static_cast<int>(Role::Message), "message" },
        { UserRoleOffset + static_cast<int>(Role::NewDay), "newDay" },
        { UserRoleOffset + static_cast<int>(Role::ActionType), "actionType" },
        { UserRoleOffset + static_cast<int>(Role::Actor), "actor" },
        { UserRoleOffset + static_cast<int>(Role::Users), "users" },
        { UserRoleOffset + static_cast<int>(Role::PreviousEntry), "previousMessage" },
        { UserRoleOffset + static_cast<int>(Role::NextEntry), "nextMessage" },
    };

    return extraRoles;
}

//QString MessagesModel::peerToText(const Telegram::Peer &peer) const
//{
//    if (peer.type == Telegram::Peer::User) {
//        Telegram::UserInfo info;
//        m_backend->getUserInfo(&info, peer.id);
//        if (!info.id()) {
//            qDebug() << Q_FUNC_INFO << "Unknown contact..";
//            return QStringLiteral("user%1").arg(peer.id);
//        }
//        return CContactModel::formatName(info);
//    }
//    Telegram::ChatInfo info;
//    m_backend->getChatInfo(&info, peer.id);
//    if (!info.title().isEmpty()) {
//        return info.title();
//    }
//    return QStringLiteral("chat%1").arg(peer.id);
//    return QString();
//}

QVariant MessagesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

//    switch (section) {
//    case Peer:
//        return tr("Peer");
//    case Contact:
//        return tr("Phone");
//    case Direction:
//        return tr("Direction");
//    case Timestamp:
//        return tr("Timestamp");
//        break;
//    case MessageId:
//        return tr("Message Id");
//    case Message:
//        return tr("Message text");
//    case Status:
//        return tr("Status");
//    case ForwardFrom:
//        return tr("Forward from");
//    case ForwardTimestamp:
//        return tr("Forward timestamp");
//    default:
//        break;
//    }

    return QVariant();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    const Role r = indexToRole(index, role);
    return getData(index.row(), r);
}

QVariant MessagesModel::getData(int index, Role role) const
{
    if (index < 0 || index >= m_events.count()) {
        return QVariant();
    }

    union {
        const Event *event;
        const MessageEvent *message;
        const ServiceAction *serviceAction;
        const NewDayAction *newDay;
        const CallEvent *call;
//        const FileTransfer *fileTransfer;
    };
    event = m_events.at(index);

    if (role == Role::EventType) {
        return QVariant::fromValue(static_cast<int>(event->type));
    }

    switch (event->type) {
    case Event::Type::NewDay:
        switch (role) {
        case Role::Timestamp:
            return newDay->date;
        default:
            return QVariant();
        }
    case Event::Type::ServiceAction:
        switch (role) {
        case Role::ActionType:
            return QVariant::fromValue(static_cast<int>(serviceAction->actionType));
        case Role::Timestamp:
            return serviceAction->date;
        case Role::Actor:
            return serviceAction->actor;
        case Role::Users:
            return serviceAction->users;
        default:
            return QVariant();
        }
    case Event::Type::Message:
        switch (role) {
        case Role::MessageType:
            return QVariant::fromValue(static_cast<int>(message->messageType));
        case Role::SentTimestamp:
            return QVariant::fromValue(QDateTime::fromSecsSinceEpoch(message->sentTimestamp));
        case Role::ReceivedTimestamp:
            return QVariant::fromValue(QDateTime::fromSecsSinceEpoch(message->receivedTimestamp));
        case Role::Identifier:
            return QVariant::fromValue(message->id);
        case Role::Contact:
            return QVariant::fromValue(message->fromId);
        case Role::Message:
            return QVariant::fromValue(*message);
        case Role::PreviousEntry:
            return getSiblingEntryData(index - 1);
        case Role::NextEntry:
            return getSiblingEntryData(index + 1);
        default:
            return QVariant();
        }
    case Event::Type::Call:
        switch (role) {
        case Role::Timestamp:
            return QVariant::fromValue(QDateTime::fromSecsSinceEpoch(call->timestamp));
        case Role::Peer:
            return QVariant::fromValue(call->peer());
        case Role::Duration:
            return QVariant::fromValue(QTime().addSecs(call->duration));
        default:
            return QVariant();
        }
    default:
        return QVariant();
    }

    Q_UNREACHABLE();
    return QVariant();
}

QVariant MessagesModel::getSiblingEntryData(int index) const
{
    if (index < 0 || index >= m_events.count()) {
        return QVariant();
    }

    union {
        const Event *event;
        const MessageEvent *message;
        const ServiceAction *serviceAction;
        const NewDayAction *newDay;
        //const Call *call;
        //const FileTransfer *fileTransfer;
    };
    event = m_events.at(index);

    if (event->type != Event::Type::Message) {
        return QVariant();
    }

    return QVariantMap({
                           { roleToName(Role::MessageType),
                             QVariant::fromValue(static_cast<int>(message->messageType)) },
                           { roleToName(Role::Contact),
                             QVariant::fromValue(message->fromId) },
                       });
}

void MessagesModel::setQmlClient(DeclarativeClient *qmlClient)
{
    m_qmlClient = qmlClient;
    emit clientChanged();

    connect(client()->messagingApi(), &MessagingApi::messageReceived,
            this, &MessagesModel::onMessageReceived);
}

//const MessagesModel::SMessage *MessagesModel::messageAt(quint32 messageIndex) const
//{
//    if (int(messageIndex) >= m_messages.count()) {
//        return 0;
//    }

//    return &m_messages[messageIndex];
//}

//int MessagesModel::messageIndex(quint64 messageId) const
//{
//    for (int i = 0; i < m_messages.count(); ++i) {
//        if (m_messages.at(i).id == messageId) {
//            return i;
//        }
//        if (m_messages.at(i).id64 == messageId) {
//            return i;
//        }
//    }

//    return -1;
//}

void MessagesModel::addMessages(const QVector<MessageEvent> &messages)
{
//    Telegram::MessageMediaInfo mediaInfo;
//    Telegram::RemoteFile fileInfo;
//    SMessage processedMessage = message;
//    bool needFileData = false;
//    if (message.type != TelegramNamespace::MessageTypeText) {
//        m_backend->getMessageMediaInfo(&mediaInfo, message.id, message.peer());
//        mediaInfo.getRemoteFileInfo(&fileInfo);
//        switch (message.type) {
//        case TelegramNamespace::MessageTypePhoto:
//        case TelegramNamespace::MessageTypeVideo:
//            needFileData = true;
//            break;
//        case TelegramNamespace::MessageTypeDocument: {
//            if (mediaInfo.mimeType().startsWith(QLatin1String("image/"))) {
//                needFileData = true;
//            }
//        }
//            break;
//        case TelegramNamespace::MessageTypeGeo:
//            processedMessage.text = QString("%1%2, %3%4").arg(mediaInfo.latitude()).arg(QChar(0x00b0)).arg(mediaInfo.longitude()).arg(QChar(0x00b0));
//            break;
//        default:
//            break;
//        }
//    }

//    if (needFileData) {
//        const QByteArray data = m_fileManager->getData(fileInfo.getUniqueId());
//        const QPixmap picture = QPixmap::fromImage(QImage::fromData(data));
//        if (!picture.isNull()) {
//            processedMessage.mediaData = picture;
//            needFileData = false;
//        }
//    }

//    for (int i = 0; i < m_messages.count(); ++i) {
//        if ((m_messages.at(i).id64 && (m_messages.at(i).id64 == message.id64))
//                || (!m_messages.at(i).id64 && (m_messages.at(i).id == message.id))) {
//            m_messages.replace(i, processedMessage);
//            emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
//            return;
//        }
//    }
    int newRow = m_events.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
//    m_messages.append(processedMessage);
//    if (!m_messages.last().timestamp) {
//        m_messages.last().timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
//    }
    endInsertRows();

//    if (needFileData) {
//        const quint64 id = message.id ? message.id : message.id64;
//        const QString uniqueId = m_fileManager->requestFile(fileInfo);
//        m_fileRequests.insert(uniqueId, id);
//    }
}

//void MessagesModel::onFileRequestComplete(const QString &uniqueId)
//{
//    if (!m_fileRequests.contains(uniqueId)) {
//        return;
//    }
//    qDebug() << Q_FUNC_INFO << uniqueId;
//    const QByteArray data = m_fileManager->getData(uniqueId);
//    const QPixmap picture = QPixmap::fromImage(QImage::fromData(data));
//    const quint64 messageId = m_fileRequests.take(uniqueId);
//    setMessageMediaData(messageId, picture);
//}

//int MessagesModel::setMessageMediaData(quint64 messageId, const QVariant &data)
//{
//    int i = messageIndex(messageId);
//    if (i < 0) {
//        return i;
//    }

//    m_messages[i].mediaData = data;
//    emit dataChanged(index(i, Message), index(i, Message), QVector<int>() << Qt::DecorationRole);
//    return i;
//}

//void MessagesModel::setMessageRead(Telegram::Peer peer, quint32 messageId, bool out)
//{
//    int from = -1;
//    for (int i = 0; i < m_messages.count(); ++i) {
//        SMessage &message = m_messages[i];

//        const bool hasFlagOut = message.flags & TelegramNamespace::MessageFlagOut;
//        const bool hasRightDirection = hasFlagOut == out;
//        const bool idIsFitInRange = message.id <= messageId;
//        const bool isNotAlreadyRead = message.status != MessagesModel::SMessage::StatusRead;
//        const bool haveTargetPeer = message.peer() == peer;

//        if (hasRightDirection && idIsFitInRange && isNotAlreadyRead && haveTargetPeer) {
//            if (from < 0) {
//                from = i;
//            }

//            message.status = MessagesModel::SMessage::StatusRead;
//        } else {
//            if (from >= 0) {
//                QModelIndex firstIndex = index(from, Status);
//                QModelIndex lastIndex = index(i - 1, Status);
//                emit dataChanged(firstIndex, lastIndex);
//                from = -1;
//            }
//        }
//    }

//    if (from >= 0) {
//        QModelIndex firstIndex = index(from, Status);
//        QModelIndex lastIndex = index(m_messages.count() - 1, Status);
//        emit dataChanged(firstIndex, lastIndex);
//    }
//}

//void MessagesModel::setMessageInboxRead(Telegram::Peer peer, quint32 messageId)
//{
//    setMessageRead(peer, messageId, /* out */ false);
//}

//void MessagesModel::setMessageOutboxRead(Telegram::Peer peer, quint32 messageId)
//{
//    setMessageRead(peer, messageId, /* out */ true);
//}

//void MessagesModel::setResolvedMessageId(quint64 randomId, quint32 resolvedId)
//{
//    for (int i = 0; i < m_messages.count(); ++i) {
//        SMessage &message = m_messages[i];
//        if (message.id64 == randomId) {
//            message.id = resolvedId;
//            message.status = MessagesModel::SMessage::StatusSent;

//            QModelIndex firstIndex = index(i, MessageId);
//            QModelIndex lastIndex = index(i, Status);
//            emit dataChanged(firstIndex, lastIndex);
//            break;
//        }
//    }
//}

void MessagesModel::clear()
{
    if (m_events.isEmpty()) {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, m_events.count() - 1);
    m_events.clear();
    endRemoveRows();
}

void MessagesModel::setPeer(const Telegram::Peer peer)
{
    if (m_peer == peer) {
        return;
    }
    m_peer = peer;
    emit peerChanged(peer);
}

void MessagesModel::onPeerChanged()
{
    beginResetModel();
    qDeleteAll(m_events);
    m_events.clear();
    endResetModel();
    if (m_peer.isValid()) {
        fetchPrevious();
        return;
    }
}

void MessagesModel::fetchPrevious()
{
    if (!m_peer.isValid()) {
        return;
    }
    qWarning() << Q_FUNC_INFO << "for peer" << m_peer.toString();
    MessagesOperation *op = client()->messagingApi()->getHistory(m_peer, MessageFetchOptions::useLimit(10));
    connect(op, &MessagesOperation::finished, this, [this, op] () {
        processMessages(op->messages());
    });
}

void MessagesModel::fetchNext()
{
}

void MessagesModel::insertMessages(const QVector<quint32> &messageIds)
{
    QVector<quint32> messagesToInsertNow = messageIds;

    QVector<Event*> newEvents;
    for (const quint32 messageId : messagesToInsertNow) {
        Message m;
        if (!m_qmlClient->client()->dataStorage()->getMessage(&m, m_peer, messageId)) {
            continue;
        }

        MessageEvent *event = new MessageEvent();
        event->fromId = m.fromId;
        event->text = m.text;
        event->receivedTimestamp = m.timestamp;
        event->sentTimestamp = event->receivedTimestamp;
        newEvents.prepend(event);
    }

    beginInsertRows(QModelIndex(), m_events.count(), m_events.count() + newEvents.count() - 1);
    m_events.append(newEvents);
    endInsertRows();
}

void MessagesModel::processMessages(const QVector<quint32> &messageIds)
{
    beginResetModel();
    qDeleteAll(m_events);
    m_events.clear();
    insertMessages(messageIds);
    endResetModel();
}

void MessagesModel::onMessageReceived(const Peer peer, quint32 messageId)
{
    qDebug() << Q_FUNC_INFO << "peer:" << peer << "messageId:" << messageId;
    if (peer != m_peer) {
        return;
    }
    insertMessages({messageId});
}

MessagesModel::Role MessagesModel::intToRole(int value)
{
    if (value < 0 || value > static_cast<int>(Role::Count)) {
        return Role::Invalid;
    }
    return static_cast<Role>(value);
}

MessagesModel::Column MessagesModel::intToColumn(int value)
{
    if (value < 0 || value > static_cast<int>(Column::Count)) {
        return Column::Invalid;
    }
    return static_cast<Column>(value);
}

MessagesModel::Role MessagesModel::indexToRole(const QModelIndex &index, int role)
{
    if (role >= UserRoleOffset) {
        return intToRole(role - UserRoleOffset);
    }

    const Column section = intToColumn(index.column());

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (section) {
        case Column::MessageId:
            return Role::Identifier;
        case Column::MessageText:
            return Role::Message;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return Role::Invalid;
}

QString MessagesModel::roleToName(MessagesModel::Role role) const
{
    static QHash<int, QString> names;
    if (Q_UNLIKELY(names.isEmpty())) {
        constexpr int count = static_cast<int>(Role::Count);
        names.reserve(count);
        for (int i = 0; i < count; ++i) {
            names[i] = QString::fromLatin1(roleNames()[UserRoleOffset + i]);
        }
    }
    return names.value(static_cast<int>(role));
}

MessageEvent::MessageEvent() :
    Event()
{
    type = Event::Type::Message;
}

CallEvent::CallEvent() :
    Event()
{
    type = Event::Type::Call;
}

} // Client namespace

} // Telegram namespace
