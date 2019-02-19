/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of BrainIM library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#ifndef BRAIN_IM_MESSAGES_MODEL_HPP
#define BRAIN_IM_MESSAGES_MODEL_HPP

#include <QAbstractTableModel>
#include <QDateTime>

#include "TelegramNamespace.hpp"

#include "DeclarativeClientOperator.hpp"

//#include "Event.hpp"
//#include "Types.hpp"

namespace Telegram {

namespace Client {

class DeclarativeClient;
class MessagesOperation;

class Event
{
    Q_GADGET
    Q_PROPERTY(Type type MEMBER type)
public:
    enum class Type {
        Invalid       = 0,
        Message       = 1 << 0,
        Call          = 1 << 1,
        FileTransfer  = 1 << 2,
        NewDay        = 1 << 3,
        ServiceAction = 1 << 4,
    };
    Q_ENUM(Type)
    Q_DECLARE_FLAGS(Types, Type)

    Type type = Type::Invalid;
};

struct CallEvent : public Event
{
    Q_GADGET
    Q_PROPERTY(quint32 duration MEMBER duration)
    Q_PROPERTY(QStringList participants MEMBER participants)
public:
    CallEvent();

    const Peer peer() const { return m_peer; }
    void setPeer(const Peer &peer) { m_peer = peer; }

    QStringList participants;

    quint32 id = 0;
    quint32 timestamp = 0;
    quint32 duration = 0;

    Peer m_peer;
};

struct MessageEvent : public Event
{
    Q_GADGET
    Q_PROPERTY(QString text MEMBER text)
    Q_PROPERTY(quint32 sender MEMBER fromId)
public:
    enum class Status {
        Unknown,
        Sent,
        Received,
        Read,
        Deleted
    };
    Q_ENUM(Status)

    enum class Flag {
        None      = 0x0,
        Read      = 0x1, // Message was read
        Out       = 0x2, // Message is outgoing
        Forwarded = 0x4,
        IsReply   = 0x8,
    };
    Q_ENUM(Flag)

    Q_DECLARE_FLAGS(Flags, Flag)

    enum class Type {
        Invalid     = 0x00,
        Text        = 0x01,
        Photo       = 0x02,
        Audio       = 0x04,
        Video       = 0x08,
        Contact     = 0x10,
        Document    = 0x20,
        Geo         = 0x40,
        WebPage     = 0x80,
        All         = 0xff
    };
    Q_ENUM(Type)
    Q_DECLARE_FLAGS(TypeFlags, Type)

    MessageEvent();

    quint32 fromId = 0; // Sender handle

    const Peer forwardFromPeer() const { return m_forwardPeer; }
    void setForwardFromPeer(const Peer &peer) { m_forwardPeer = peer; }

    quint32 replyToMessageId = 0;
    quint32 forwardContactId = 0; // If forward peer is a group chat, then the contact is the actual sender.
    QString text;
    quint32 id = 0;
    quint32 sentTimestamp = 0;
    quint32 receivedTimestamp = 0;
    quint32 fwdTimestamp = 0;
    Status status = Status::Unknown;
    Type messageType = Type::Invalid;
    Flags flags;

    Peer m_forwardPeer;
};

class ServiceAction : public Event
{
    Q_GADGET
    Q_PROPERTY(QDateTime date MEMBER date)
public:
    enum class ActionType {
        Invalid,
        AddParticipant,
        DeleteParticipant,
    };
    Q_ENUM(ActionType)

    ServiceAction()
    {
        type = Event::Type::ServiceAction;
    }

    QDateTime date;
    ActionType actionType = ActionType::Invalid;
    QString actor;
    QStringList users;
};

class NewDayAction : public Event
{
    Q_GADGET
    Q_PROPERTY(QDate date MEMBER date)
public:
    explicit NewDayAction(const QDate &d = QDate()) :
        date(d)
    {
        type = Event::Type::NewDay;
    }

    QDate date;
};

class MessagesModel : public QAbstractTableModel, public DeclarativeClientMixin
{
    Q_OBJECT
    //Q_PROPERTY(Classes enabledClass NOTIFY classChanged)
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeClient *client READ qmlClient WRITE setQmlClient NOTIFY clientChanged)
public:
    enum class Column {
        Peer,
        Contact,
        Direction,
        SentTimestamp,
        ReceivedTimestamp,
        MessageId,
        MessageText,
        Type, // Text, Photo, Audio
        Class, // Message, Call, NewDay
        Status,
        ForwardFrom,
        ForwardTimestamp,
        PeerText,
        ForwardFromText,
        Count,
        Invalid = Count,
    };

    enum class Role {
        EventType, // Message, Call, NewDay
        MessageType, // Text, Photo, Audio
        Timestamp, // For local events, such as NewDay
        SentTimestamp,
        ReceivedTimestamp,
        Identifier, // Message ID
        Peer,
        Contact,
        Message,
        NewDay,
        ActionType, // Service action type, such as Partici
        Actor,
        Duration, // Call duration
        Users,
        PreviousEntry,
        NextEntry,
        Count, // Roles count
        Invalid = Count,
    };
    Q_ENUM(Role)

    explicit MessagesModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    //QString peerToText(const Telegram::Peer &peer) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant getData(int index, Role role) const;
    QVariant getSiblingEntryData(int index) const;

    Telegram::Peer peer() const { return m_peer; }

public slots:
    void setQmlClient(DeclarativeClient *qmlClient);

    void addMessages(const QVector<MessageEvent> &messages);
    //void onFileRequestComplete(const QString &uniqueId);
    //int setMessageMediaData(quint64 messageId, const QVariant &data);
    //void setMessageRead(Telegram::Peer peer, quint32 messageId, bool out);
    //void setMessageInboxRead(Telegram::Peer peer, quint32 messageId);
    //void setMessageOutboxRead(Telegram::Peer peer, quint32 messageId);
    //void setResolvedMessageId(quint64 randomId, quint32 resolvedId);
    void clear();
    void setPeer(const Telegram::Peer peer);

    void onPeerChanged();

    void fetchPrevious();
    void fetchNext();

Q_SIGNALS:
    void clientChanged();

    void classChanged();
    void peerChanged(Telegram::Peer peer);

protected:
    void insertMessages(const QVector<quint32> &messageIds);

    void processMessages(const QVector<quint32> &messageIds);
    void onMessageReceived(const Telegram::Peer peer, quint32 messageId);

    static Role intToRole(int value);
    static Column intToColumn(int value);
    static Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole);
    QString roleToName(Role role) const;

    QVector<Event*> m_events;
    Telegram::Peer m_peer;
};

inline int MessagesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(Column::Count);
}

} // Client namespace

} // Telegram namespace

//Q_DECLARE_METATYPE(BrainIM::MessageEvent)
//Q_DECLARE_METATYPE(BrainIM::MessageEntity)
//Q_DECLARE_METATYPE(BrainIM::MessagesModel::Entity)

#endif // BRAIN_IM_MESSAGES_MODEL_HPP
