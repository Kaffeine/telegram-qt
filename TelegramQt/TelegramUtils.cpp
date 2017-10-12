#include "TelegramUtils.hpp"

namespace TelegramUtils
{

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
    case TLValue::MessageMediaWebPage:
        return TelegramNamespace::MessageTypeWebPage;
    default:
        return TelegramNamespace::MessageTypeUnsupported;
    }
}

TLValue::Value publicMessageTypeToTelegramMessageType(TelegramNamespace::MessageType type)
{
    switch (type) {
    case TelegramNamespace::MessageTypeText:
        return TLValue::MessageMediaEmpty;
    case TelegramNamespace::MessageTypePhoto:
        return TLValue::MessageMediaPhoto;
    case TelegramNamespace::MessageTypeVideo:
        return TLValue::MessageMediaVideo;
    case TelegramNamespace::MessageTypeGeo:
        return TLValue::MessageMediaGeo;
    case TelegramNamespace::MessageTypeContact:
        return TLValue::MessageMediaContact;
    case TelegramNamespace::MessageTypeAudio:
        return TLValue::MessageMediaAudio;
    case TelegramNamespace::MessageTypeDocument:
        return TLValue::MessageMediaDocument;
    case TelegramNamespace::MessageTypeWebPage:
        return TLValue::MessageMediaWebPage;
    default:
        return TLValue::MessageMediaUnsupported;
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
