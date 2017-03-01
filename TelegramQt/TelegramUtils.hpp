#ifndef CTELEGRAMUTILS_HPP
#define CTELEGRAMUTILS_HPP

#include "TelegramNamespace.hpp"
#include "TLValues.hpp"

#include <QStringList>

namespace TelegramUtils
{
    QString maskPhoneNumber(const QString &identifier);
    QStringList maskPhoneNumberList(const QStringList &list);

    QString mimeTypeByStorageFileType(TLValue type);
    TelegramNamespace::MessageType telegramMessageTypeToPublicMessageType(TLValue type);
    TLValue::Value publicMessageTypeToTelegramMessageType(TelegramNamespace::MessageType type);
    TelegramNamespace::MessageAction telegramMessageActionToPublicAction(TLValue action);
    TLValue::Value publicMessageActionToTelegramAction(TelegramNamespace::MessageAction action);

    enum TelegramMessageFlags {
        TelegramMessageFlagNone    = 0,
        TelegramMessageFlagUnread  = 1 << 0,
        TelegramMessageFlagOut     = 1 << 1,
        TelegramMessageFlagForward = 1 << 2,
        TelegramMessageFlagReply   = 1 << 3,
    };
}

#endif // CTELEGRAMUTILS_HPP
