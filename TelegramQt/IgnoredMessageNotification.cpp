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

#include "IgnoredMessageNotification.hpp"

#include "CRawStream.hpp"
#include "TLTypes.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace MTProto {

// https://core.telegram.org/mtproto/service_messages_about_messages#notice-of-ignored-error-message

IgnoredMessageNotification::IgnoredMessageNotification(const TLBadMsgNotification &tlNotification)
{
    fromTlNotification(&tlNotification);
}

QString IgnoredMessageNotification::codeToString(quint32 code)
{
    switch (code) {
    case MessageIdTooLow:
        return QLatin1String("Id too low");
    case MessageIdTooHigh:
        return QLatin1String("Id too high");
    case IncorrectTwoLowerOrderMessageIdBits:
        return QLatin1String("Incorrect two lower order id bits");
    case ContainerIdAlreadyReceived:
        return QLatin1String("Container id is the same as id of a previously received message");
    case MessageIdTooOld:
        return QLatin1String("Message too old, and it cannot be verified whether the server has"
                             " received a message with this id or not");
    case SequenceNumberTooLow:
        return QLatin1String("Sequence number too low");
    case SequenceNumberTooHigh:
        return QLatin1String("Sequence number too high");
    case EvenSequenceNumberExpected:
        return QLatin1String("An even sequence number expected");
    case OddSequenceNumberExpected:
        return QLatin1String("Odd sequence number expected");
    case IncorrectServerSalt:
        return QLatin1String("Incorrect server salt");
    case InvalidContainer:
        return QLatin1String("Invalid container");
    default:
        return QStringLiteral("Unknown error code %1").arg(code);
    }
}

QString IgnoredMessageNotification::toString() const
{
    return QStringLiteral("Bad message 0x%1/0x%2 (%3)").arg(messageId, sizeof(messageId) * 2, 0x10, QLatin1Char('0'))
            .arg(seqNo, sizeof(seqNo) * 2, 0x10, QLatin1Char('0'))
            .arg(codeToString(errorCode));
}

bool IgnoredMessageNotification::toTlNotification(TLBadMsgNotification *output) const
{
    if (errorCode == UnknownError) {
        qCritical() << __func__ << "Invalid error code";
        return false;
    }

    if (errorCode == IncorrectServerSalt) {
        output->tlType = TLValue::BadServerSalt;
        output->newServerSalt = newServerSalt;
    } else {
        output->tlType = TLValue::BadMsgNotification;
    }
    output->badMsgId = messageId;
    output->badMsgSeqno = seqNo;
    output->errorCode = errorCode;
    return true;
}

bool IgnoredMessageNotification::fromTlNotification(const TLBadMsgNotification *input)
{
    if (!input->isValid()) {
        qCritical() << __func__ << "Invalid input";
        return false;
    }
    messageId = input->badMsgId;
    seqNo = input->badMsgSeqno;
    errorCode = input->errorCode;
    newServerSalt = input->newServerSalt;
    if (input->tlType == TLValue::BadServerSalt) {
        if (errorCode != IncorrectServerSalt) {
            qCritical() << __func__ << "Invalid input error code";
            return false;
        }
        if (!input->newServerSalt) {
            qCritical() << __func__ << "Invalid input (no server salt)";
            return false;
        }
    }
    return true;
}

} // MTProto

} // Telegram
