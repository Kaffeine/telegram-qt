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

#ifndef TELEGRAM_RPC_ERROR_HPP
#define TELEGRAM_RPC_ERROR_HPP

#include "telegramqt_global.h"
#include <QObject>

class CRawStreamEx;

namespace Telegram {

class RpcError
{
    Q_GADGET
public:
    enum Type {
        UnknownType,
        SeeOther = 303,
        BadRequest = 400,
        Unauthorized = 401,
        Forbidden = 403,
        NotFound = 404,
        Flood = 420,
        Internal = 500,
    };

    enum Reason {
        UnknownReason,
        FileMigrateX,
        PhoneMigrateX,
        NetworkMigrateX,
        UserMigrateX,
        FirstnameInvalid,
        LastnameInvalid,
        UsernameInvalid,
        UsernameOccupied,
        UsernameNotModified,
        PhoneNumberInvalid,
        PhoneCodeHashEmpty,
        PhoneCodeInvalid,
        PhoneCodeEmpty,
        PhoneCodeExpired,
        ApiIdInvalid,
        PasswordHashInvalid,
        PhoneNumberOccupied,
        PhoneNumberUnoccupied,
        FilePartXMissing,
        AuthKeyUnregistered,
        AuthKeyInvalid,
        UserDeactivated,
        SessionRevoked,
        SessionExpired,
        ActiveUserRequired,
        AuthKeyPermEmpty,
        SessionPasswordNeeded,
        FloodWaitX,
    };
    Q_ENUM(Reason)

    RpcError(Reason r = UnknownReason, quint32 arg = 0);

    Reason reason = UnknownReason;
    quint32 argument = 0;
    QByteArray message;
    Type type = UnknownType;

    bool readFromStream(CRawStreamEx &stream);

    static QString reasonToString(Reason reason, quint32 argument = 0);
    static bool reasonFromString(const QByteArray &str, Reason *reason, quint32 *argument);
};

CRawStreamEx &operator>>(CRawStreamEx &stream, RpcError &error);
CRawStreamEx &operator<<(CRawStreamEx &stream, const RpcError &error);

} // Telegram namespace

#endif // TELEGRAM_RPC_ERROR_HPP
