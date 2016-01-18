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

#ifndef TELEGRAMNAMESPACE_HPP
#define TELEGRAMNAMESPACE_HPP

#include "telegramqt_export.h"

#include <QObject>
#include <QFlags>
#include <QMetaType>

class CTelegramDispatcher;

class TELEGRAMQT_EXPORT TelegramNamespace : public QObject
{
    Q_OBJECT
    Q_ENUMS(ContactStatus)
public:
    enum ContactStatus {
        ContactStatusUnknown,
        ContactStatusOffline,
        ContactStatusOnline
    };

    enum MessageDeliveryStatus {
        MessageDeliveryStatusUnknown,
        MessageDeliveryStatusSent,
        MessageDeliveryStatusRead,
        MessageDeliveryStatusDeleted
    };

    enum MessageFlag {
        MessageFlagNone      = 0x0,
        MessageFlagRead      = 0x1, // Message was read
        MessageFlagOut       = 0x2, // Message is outgoing
        MessageFlagForwarded = 0x4
    };
    Q_DECLARE_FLAGS(MessageFlags, MessageFlag)

    enum MessageType {
        MessageTypeUnsupported = 0x00,
        MessageTypeText        = 0x01,
        MessageTypePhoto       = 0x02,
        MessageTypeAudio       = 0x04,
        MessageTypeVideo       = 0x08,
        MessageTypeContact     = 0x10,
        MessageTypeDocument    = 0x20,
        MessageTypeGeo         = 0x40
    };
    Q_DECLARE_FLAGS(MessageTypeFlags, MessageType)

    enum AuthSignError {
        AuthSignErrorUnknown,
        AuthSignErrorAppIdIsInvalid,
        AuthSignErrorPhoneNumberIsInvalid,
        AuthSignErrorPhoneNumberIsOccupied,
        AuthSignErrorPhoneNumberIsUnoccupied,
        AuthSignErrorPhoneCodeIsInvalid,
        AuthSignErrorPhoneCodeIsExpired,
        AuthSignErrorFirstNameIsInvalid,
        AuthSignErrorLastNameIsInvalid
    };

    enum AccountUserNameStatus {
        AccountUserNameStatusUnknown,
        AccountUserNameStatusIsInvalid,
        AccountUserNameStatusIsOccupied,
        AccountUserNameStatusIsNotModified,
        AccountUserNameStatusCanBeUsed,
        AccountUserNameStatusCanNotBeUsed,
        AccountUserNameStatusAccepted
    };

    enum ConnectionState {
        ConnectionStateDisconnected,
        ConnectionStateConnecting,
        ConnectionStateConnected,
        ConnectionStateAuthRequired,
        ConnectionStateAuthenticated,
        ConnectionStateReady // Initializated
    };

    enum ContactLastOnline {
        ContactLastOnlineUnknown,
        ContactLastOnlineRecently,
        ContactLastOnlineLastWeek,
        ContactLastOnlineLastMonth,
        ContactLastOnlineMask = 0xf
    };

    enum MessageAction {
        MessageActionNone, // Cancel
        MessageActionTyping,
        MessageActionRecordVideo,
        MessageActionRecordAudio,
        MessageActionUploadVideo,
        MessageActionUploadAudio,
        MessageActionUploadPhoto,
        MessageActionUploadDocument,
        MessageActionGeoLocation,
        MessageActionChooseContact
    };

    static void registerTypes();

    struct DcOption
    {
        inline DcOption() : port(0) { }
        inline DcOption(const QString &a, quint32 p) : address(a), port(p) { }
        QString address;
        quint32 port;
    };

    struct Message
    {
        Message() :
            id(0),
            timestamp(0),
            fwdTimestamp(0),
            type(MessageTypeUnsupported),
            flags(0)
        {

        }

        QString peer;
        QString contact;
        QString text;
        QString fwdContact;
        quint32 id;
        quint32 timestamp;
        quint32 fwdTimestamp;
        MessageType type;
        MessageFlags flags;
    };

    class MessageMediaInfo
    {
    public:
        MessageMediaInfo();

        MessageType type() const;

        // Photo, Video
        QString caption() const;

        // GeoPoint
        double latitude() const;
        double longitude() const;
        void setGeoPoint(double latitude, double longitude);

    protected:
        friend class CTelegramDispatcher;
        class Private;

        Private *d;
    };

    struct GroupChat
    {
        GroupChat(quint32 id = 0) :
            id(id),
            participantsCount(0),
            date(0),
            left(false)
        {
        }

        quint32 id;
        QString title;
        quint32 participantsCount;
        quint32 date;
        bool left;
    };

};

Q_DECLARE_METATYPE(TelegramNamespace::DcOption)
Q_DECLARE_METATYPE(TelegramNamespace::Message)
Q_DECLARE_METATYPE(TelegramNamespace::GroupChat)

Q_DECLARE_TYPEINFO(TelegramNamespace::DcOption, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(TelegramNamespace::Message, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(TelegramNamespace::GroupChat, Q_MOVABLE_TYPE);

Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageTypeFlags)

#endif // TELEGRAMNAMESPACE_HPP
