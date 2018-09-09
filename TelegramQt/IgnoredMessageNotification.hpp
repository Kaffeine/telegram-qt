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

#ifndef TELEGRAM_QT_IGNORED_MESSAGE_NOTIFICATION_HPP
#define TELEGRAM_QT_IGNORED_MESSAGE_NOTIFICATION_HPP

#include "telegramqt_global.h"
#include <QObject>

class CRawStream;

namespace Telegram {

namespace MTProto {

class TELEGRAMQT_EXPORT IgnoredMessageNotification
{
    Q_GADGET
public:
    enum ErrorCode {
        UnknownError,
        MessageIdTooLow = 16,
        MessageIdTooHigh = 17,
        IncorrectTwoLowerOrderMessageIdBits = 18,
        ContainerIdAlreadyReceived = 19,
        MessageIdTooOld = 20,
        SequenceNumberTooLow = 32,
        SequenceNumberTooHigh = 33,
        EvenSequenceNumberExpected = 34,
        OddSequenceNumberExpected = 35,
        IncorrectServerSalt = 48,
        InvalidContainer = 64,
    };
    Q_ENUM(ErrorCode)
    quint64 messageId;
    quint32 seqNo;
    quint32 errorCode;

    static QString codeToString(quint32 code);
    QString toString() const;
};

CRawStream &operator>>(CRawStream &stream, IgnoredMessageNotification &error);
CRawStream &operator<<(CRawStream &stream, const IgnoredMessageNotification &error);

} // MTProto

} // Telegram

#endif //  TELEGRAM_QT_IGNORED_MESSAGE_NOTIFICATION_HPP
