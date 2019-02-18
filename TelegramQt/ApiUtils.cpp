#include "ApiUtils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Utils {

Telegram::Peer toPublicPeer(const TLInputPeer &inputPeer, quint32 selfId)
{
    switch (inputPeer.tlType) {
    case TLValue::InputPeerSelf:
        return Telegram::Peer::fromUserId(selfId);
    case TLValue::InputPeerUser:
        return Telegram::Peer::fromUserId(inputPeer.userId);
    case TLValue::InputPeerChat:
        return Telegram::Peer::fromChatId(inputPeer.chatId);
    case TLValue::InputPeerChannel:
        return Telegram::Peer::fromChannelId(inputPeer.channelId);
    case TLValue::InputPeerEmpty:
    default:
        return Telegram::Peer();
    }
}

Telegram::Peer toPublicPeer(const TLPeer &peer)
{
    switch (peer.tlType) {
    case TLValue::PeerChat:
        return Telegram::Peer::fromChatId(peer.chatId);
    case TLValue::PeerChannel:
        return Telegram::Peer::fromChannelId(peer.channelId);
    case TLValue::PeerUser:
        return Telegram::Peer::fromUserId(peer.userId);
    default:
        return Telegram::Peer();
    }
}

Telegram::Peer toPublicPeer(const TLUser &user)
{
    if (!user.isValid() || !user.id) {
        return Telegram::Peer();
    }
    return Telegram::Peer(user.id, Telegram::Peer::User);
}

Telegram::Peer toPublicPeer(const TLChat *chat)
{
    switch(chat->tlType) {
    case TLValue::Chat:
    case TLValue::ChatForbidden:
        return Telegram::Peer::fromChatId(chat->id);
    case TLValue::Channel:
    case TLValue::ChannelForbidden:
        return Telegram::Peer::fromChannelId(chat->id);
    default:
        return Telegram::Peer();
    }
}

TLPeer toTLPeer(const Telegram::Peer &peer)
{
    TLPeer result;
    switch (peer.type) {
    case Telegram::Peer::Chat:
        result.tlType = TLValue::PeerChat;
        result.chatId = peer.id;
        break;
    case Telegram::Peer::Channel:
        result.tlType = TLValue::PeerChannel;
        result.channelId = peer.id;
        break;
    case Telegram::Peer::User:
        result.tlType = TLValue::PeerUser;
        result.userId = peer.id;
        break;
    }
    return result;
}

Peer getMessageDialogPeer(const TLMessage &message, quint32 applicantUserId)
{
    if (message.toId.tlType == TLValue::PeerUser) {
        if (message.toId.userId == applicantUserId) {
            if (message.fromId) {
                return Peer::fromUserId(message.fromId);
            }
        }
    }
    return toPublicPeer(message.toId);
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

TelegramNamespace::MessageType getPublicMessageType(const TLMessageMedia &media)
{
    const TLValue type = media.tlType;
    switch (type) {
    case TLValue::MessageMediaEmpty:
        return TelegramNamespace::MessageTypeText;
    case TLValue::MessageMediaPhoto:
        return TelegramNamespace::MessageTypePhoto;
    case TLValue::MessageMediaGeo:
        return TelegramNamespace::MessageTypeGeo;
    case TLValue::MessageMediaContact:
        return TelegramNamespace::MessageTypeContact;
    case TLValue::MessageMediaDocument:
        for (const TLDocumentAttribute &attribute : media.document.attributes) {
            switch (attribute.tlType) {
            case TLValue::DocumentAttributeSticker:
                return TelegramNamespace::MessageTypeSticker;
            case TLValue::DocumentAttributeAnimated:
                return TelegramNamespace::MessageTypeAnimation;
            default:
                break;
            }
        }
        return TelegramNamespace::MessageTypeDocument;
    case TLValue::MessageMediaWebPage:
        return TelegramNamespace::MessageTypeWebPage;
        // TODO:
    case TLValue::MessageMediaVenue:
    case TLValue::MessageMediaGame:
    case TLValue::MessageMediaInvoice:
    case TLValue::MessageMediaGeoLive:
    case TLValue::MessageMediaUnsupported:
    default:
        return TelegramNamespace::MessageTypeUnsupported;
    }
}

TLValue::Value toTLValue(TelegramNamespace::MessageType type)
{
    switch (type) {
    case TelegramNamespace::MessageTypeText:
        return TLValue::MessageMediaEmpty;
    case TelegramNamespace::MessageTypePhoto:
        return TLValue::MessageMediaPhoto;
    case TelegramNamespace::MessageTypeGeo:
        return TLValue::MessageMediaGeo;
    case TelegramNamespace::MessageTypeContact:
        return TLValue::MessageMediaContact;
    case TelegramNamespace::MessageTypeDocument:
        return TLValue::MessageMediaDocument;
    case TelegramNamespace::MessageTypeWebPage:
        return TLValue::MessageMediaWebPage;
    default:
        return TLValue::MessageMediaUnsupported;
    }
}

TelegramNamespace::MessageAction toPublicMessageAction(TLValue action)
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

TLValue::Value toTLValue(TelegramNamespace::MessageAction action)
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

quint64 formatTimeStamp(qint64 timeInMs)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;
    const quint64 secs = static_cast<quint64>(timeInMs) / 1000ul;
    const quint64 msecs = maxMsecValue / 1000 * (timeInMs % 1000);
    return (secs << 32) + msecs;
}

quint64 timeStampToMSecsSinceEpoch(quint64 ts)
{
    static const quint64 maxMsecValue = (quint64(1) << 32) - 1;
    const quint64 secs = ts >> 32;
    quint64 msecs = ts & maxMsecValue;
    msecs = msecs * 10000 / maxMsecValue;
    if (msecs % 10 >= 5) {
        msecs += 5;
    }
    msecs /= 10;
    return secs * 1000 + msecs;
}

} // Utils namespace

} // Telegram namespace
