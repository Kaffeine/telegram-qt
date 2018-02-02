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

#include "RpcError.hpp"

#include "CRawStream.hpp"
#include "TLValues.hpp"

#include <QHash>
#include <QMetaEnum>
#include <QRegularExpression>
#include <QLoggingCategory>

namespace Telegram {

//QMetaEnum rpcErrorReasonEnum()
//{
//    QMetaEnum reasonEnum = QMetaEnum::fromType<RpcError::Reason>();
//    return reasonEnum;
//}

bool RpcError::readFromStream(CRawStreamEx &stream)
{
    quint32 v;
    quint32 code;
    stream >> v;
    if (v != TLValue::RpcError) {
        return false;
    }
    stream >> code;
    stream >> message;
    type = static_cast<RpcError::Type>(code);
    reasonFromString(message, &reason, &argument);
    return !stream.error();
}

QString RpcError::reasonToString(RpcError::Reason reason, quint32 argument)
{
    static const QMetaEnum reasonEnum = QMetaEnum::fromType<Reason>();
    static QHash<quint32, QString> reasons;
    if (reasons.contains(reason)) {
        return reasons.value(reason);
    }
    const char *key = reasonEnum.valueToKey(reason);
    if (!key) {
        qWarning() << Q_FUNC_INFO << "Unable to make a text for the given reason" << reason;
        return QString();
    }
    const QString reasonKey = QString::fromLatin1(key);
    static const QRegularExpression regExpr(QStringLiteral("(?=[A-Z][^A-Z]*)"));
    QStringList reasonWords = reasonKey.split(regExpr);
    if (reasonWords.count() < 2) {
        return reasonWords.first().toUpper();
    }
    reasonWords.removeFirst(); // The first element is always empty for this regexp.
    bool hasArg = false;
    for (QString &word : reasonWords) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 8, 0))
        if (word == QLatin1Char('X')) {
#else
        if ((word.length() == 1) && (word.at(0) == QLatin1Char('X'))) {
#endif
            hasArg = true;
            word = QString::number(argument);
            break;
        }
    }
    const QString result = reasonWords.join(QLatin1Char('_')).toUpper();
    if (!hasArg) {
        reasons.insert(reason, result);
    }
    return result;
}

bool RpcError::reasonFromString(const QByteArray &str, RpcError::Reason *reason, quint32 *argument)
{
    static const QMetaEnum reasonEnum = QMetaEnum::fromType<Reason>();
    auto reasonWords = str.split('_');
    for (QByteArray &word : reasonWords) {
        bool ok;
        const quint32 arg = word.toUInt(&ok);
        if (ok) {
            *argument = arg;
            word = QByteArrayLiteral("X");
            continue;
        }
        word = word.toLower();
        word[0] = QChar::fromLatin1(word.at(0)).toUpper().toLatin1();
    }
    const QByteArray reasonKey = reasonWords.join(QByteArray());
    bool ok;
    int value = reasonEnum.keyToValue(reasonKey.constData(), &ok);
    if (!ok) {
        return false;
    }
    *reason = static_cast<RpcError::Reason>(value);
    return true;
}

CRawStreamEx &operator>>(CRawStreamEx &stream, RpcError &error)
{
    error.readFromStream(stream);
    return stream;
}

CRawStreamEx &operator<<(CRawStreamEx &stream, const RpcError &error)
{
    stream << TLValue::RpcError;
    quint32 code = error.type;
    stream << code;
    stream << error.message;
    return stream;
}

RpcError::RpcError(RpcError::Reason r, quint32 arg) :
    reason(r),
    argument(arg)
{
    if (r == UnknownReason) {
        return;
    }
    switch (r) {
    case PhoneNumberInvalid:
    case PhoneCodeHashEmpty:
    case PhoneCodeInvalid:
    case PhoneCodeEmpty:
    case PhoneCodeExpired:
    case PhoneNumberUnoccupied:
        type = BadRequest;
        break;
//    case FileMigrateX:
    case PhoneMigrateX:
//    case NetworkMigrateX:
//    case UserMigrateX:
        type = SeeOther;
        break;
//    case FirstnameInvalid:
//    case LastnameInvalid:
//    case UsernameInvalid:
//    case UsernameOccupied:
//    case UsernameNotModified:

//    case ApiIdInvalid:
//    case PasswordHashInvalid:
//    case PhoneNumberOccupied:
//    case FilePartXMissing:
//    case AuthKeyUnregistered:
//    case AuthKeyInvalid:
//    case UserDeactivated:
//    case SessionRevoked:
//    case SessionExpired:
//    case ActiveUserRequired:
//    case AuthKeyPermEmpty:
    case SessionPasswordNeeded:
        type = Unauthorized;
        break;
    case FloodWaitX:
        type = Flood;
    default:
        break;
    }
    message = reasonToString(r, argument).toLatin1();
}

} // Telegram
