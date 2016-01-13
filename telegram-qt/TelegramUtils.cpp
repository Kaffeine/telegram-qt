#include "TelegramUtils.hpp"

namespace TelegramUtils
{

QString maskPhoneNumber(const QString &identifier)
{
    if (identifier.isEmpty()) {
        return QString();
    }

    // We don't want to mask "numbers" like unknown777000, so lets check if phoneNumber is consist of digits only.
    bool ok1, ok2;
    identifier.mid(0, identifier.size() / 2).toInt(&ok1);

    if (ok1) {
        identifier.mid(identifier.size() / 2).toInt(&ok2);
    }

    if (ok1 && ok2) {
        // Expected something like: 55xxxxxxxx (hidden).
        return identifier.mid(0, identifier.size() / 4) + QString(identifier.size() - identifier.size() / 4, QLatin1Char('x')); // + QLatin1String(" (hidden)");
    } else {
        return identifier;
    }
}

QStringList maskPhoneNumberList(const QStringList &list)
{
    if (list.count() == 1) {
        return QStringList() << maskPhoneNumber(list.first());
    }

    QStringList result;

    const int listDigits = QString::number(list.count()).size();

    foreach (const QString &number, list) {
        if (number.length() >= 5 + listDigits) {
            QString masked = QString(QLatin1String("%1xx%2%3"))
                    .arg(number.mid(0, 2))
                    .arg(list.indexOf(number), listDigits, 10, QLatin1Char('0'))
                    .arg(QString(number.length() - 4 - listDigits, QLatin1Char('x')));
            result.append(masked);
        } else { // fallback
            result.append(maskPhoneNumber(number) + QLatin1String(" (fallback)"));
        }
    }

    return result;
}

QString mimeTypeByStorageFileType(TLValue type)
{
    switch (type) {
    case TLValue::StorageFileJpeg:
        return QLatin1String("image/jpeg");
    case TLValue::StorageFileGif:
        return QLatin1String("image/gif");
    case TLValue::StorageFilePng:
        return QLatin1String("image/png");
    case TLValue::StorageFilePdf:
        return QLatin1String("application/pdf");
    case TLValue::StorageFileMp3:
        return QLatin1String("audio/mpeg");
    case TLValue::StorageFileMov:
        return QLatin1String("video/quicktime");
    case TLValue::StorageFileMp4:
        return QLatin1String("audio/mp4");
    case TLValue::StorageFileWebp:
        return QLatin1String("image/webp");
    default:
        return QString();
    }
}

TelegramNamespace::MessageType telegramMessageTypeToPublicMessageType(TLValue type)
{
    switch (type) {
    case TLValue::MessageMediaEmpty:
        return TelegramNamespace::MessageTypeText;
    case TLValue::MessageMediaPhoto:
        return TelegramNamespace::MessageTypePhoto;
    case TLValue::MessageMediaVideo:
        return TelegramNamespace::MessageTypeVideo;
    case TLValue::MessageMediaGeo:
        return TelegramNamespace::MessageTypeGeo;
    case TLValue::MessageMediaContact:
        return TelegramNamespace::MessageTypeContact;
    case TLValue::MessageMediaAudio:
        return TelegramNamespace::MessageTypeAudio;
    case TLValue::MessageMediaDocument:
        return TelegramNamespace::MessageTypeDocument;
    default:
        return TelegramNamespace::MessageTypeUnsupported;
    }
}

TelegramNamespace::MessageAction telegramMessageActionToPublicAction(TLValue action)
{
    switch (action) {
    case TLValue::SendMessageCancelAction:         return TelegramNamespace::MessageActionNone;
    case TLValue::SendMessageTypingAction:         return TelegramNamespace::MessageActionTyping;
    case TLValue::SendMessageRecordVideoAction:    return TelegramNamespace::MessageActionRecordVideo;
    case TLValue::SendMessageRecordAudioAction:    return TelegramNamespace::MessageActionRecordAudio;
    case TLValue::SendMessageUploadVideoAction:    return TelegramNamespace::MessageActionUploadVideo;
    case TLValue::SendMessageUploadAudioAction:    return TelegramNamespace::MessageActionUploadAudio;
    case TLValue::SendMessageUploadPhotoAction:    return TelegramNamespace::MessageActionUploadPhoto;
    case TLValue::SendMessageUploadDocumentAction: return TelegramNamespace::MessageActionUploadDocument;
    case TLValue::SendMessageGeoLocationAction:    return TelegramNamespace::MessageActionGeoLocation;
    case TLValue::SendMessageChooseContactAction:  return TelegramNamespace::MessageActionChooseContact;
    default:
        return TelegramNamespace::MessageActionNone;
    }
}

TLValue::Value publicMessageActionToTelegramAction(TelegramNamespace::MessageAction action)
{
    switch (action) {
    case TelegramNamespace::MessageActionNone:           return TLValue::SendMessageCancelAction;
    case TelegramNamespace::MessageActionTyping:         return TLValue::SendMessageTypingAction;
    case TelegramNamespace::MessageActionRecordVideo:    return TLValue::SendMessageRecordVideoAction;
    case TelegramNamespace::MessageActionRecordAudio:    return TLValue::SendMessageRecordAudioAction;
    case TelegramNamespace::MessageActionUploadVideo:    return TLValue::SendMessageUploadVideoAction;
    case TelegramNamespace::MessageActionUploadAudio:    return TLValue::SendMessageUploadAudioAction;
    case TelegramNamespace::MessageActionUploadPhoto:    return TLValue::SendMessageUploadPhotoAction;
    case TelegramNamespace::MessageActionUploadDocument: return TLValue::SendMessageUploadDocumentAction;
    case TelegramNamespace::MessageActionGeoLocation:    return TLValue::SendMessageGeoLocationAction;
    case TelegramNamespace::MessageActionChooseContact:  return TLValue::SendMessageChooseContactAction;
    }

    return TLValue::BoolFalse;
}

}
