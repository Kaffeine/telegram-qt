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
struct TLBadMsgNotification;

namespace Telegram {

namespace MTProto {

struct TELEGRAMQT_INTERNAL_EXPORT IgnoredMessageNotification
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
    constexpr IgnoredMessageNotification() = default;
    explicit IgnoredMessageNotification(const TLBadMsgNotification &tlNotification);

    quint64 messageId = 0;
    quint64 newServerSalt = 0;
    quint32 seqNo = 0;
    quint32 errorCode = 0;

    static QString codeToString(quint32 code);
    QString toString() const;

    bool toTlNotification(TLBadMsgNotification *output) const;
    bool fromTlNotification(const TLBadMsgNotification *input);
};

} // MTProto namespace

} // Telegram namespace

#endif //  TELEGRAM_QT_IGNORED_MESSAGE_NOTIFICATION_HPP
