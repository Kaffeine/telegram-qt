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
    switch (peer.type()) {
    case Telegram::Peer::Chat:
        result.tlType = TLValue::PeerChat;
        result.chatId = peer.id();
        break;
    case Telegram::Peer::Channel:
        result.tlType = TLValue::PeerChannel;
        result.channelId = peer.id();
        break;
    case Telegram::Peer::User:
        result.tlType = TLValue::PeerUser;
        result.userId = peer.id();
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

Namespace::MessageType getPublicMessageType(const TLMessageMedia &media)
{
    const TLValue type = media.tlType;
    switch (type) {
    case TLValue::MessageMediaEmpty:
        return Namespace::MessageTypeText;
    case TLValue::MessageMediaPhoto:
        return Namespace::MessageTypePhoto;
    case TLValue::MessageMediaGeo:
        return Namespace::MessageTypeGeo;
    case TLValue::MessageMediaContact:
        return Namespace::MessageTypeContact;
    case TLValue::MessageMediaDocument:
        for (const TLDocumentAttribute &attribute : media.document.attributes) {
            switch (attribute.tlType) {
            case TLValue::DocumentAttributeSticker:
                return Namespace::MessageTypeSticker;
            case TLValue::DocumentAttributeAnimated:
                return Namespace::MessageTypeAnimation;
            case TLValue::DocumentAttributeAudio:
                return Namespace::MessageTypeAudio;
            case TLValue::DocumentAttributeVideo:
                return Namespace::MessageTypeVideo;
            default:
                break;
            }
        }
        return Namespace::MessageTypeDocument;
    case TLValue::MessageMediaWebPage:
        return Namespace::MessageTypeWebPage;
        // TODO:
    case TLValue::MessageMediaVenue:
    case TLValue::MessageMediaGame:
    case TLValue::MessageMediaInvoice:
    case TLValue::MessageMediaGeoLive:
    case TLValue::MessageMediaUnsupported:
    default:
        return Namespace::MessageTypeUnsupported;
    }
}

TLValue::Value toTLValue(Namespace::MessageType type)
{
    switch (type) {
    case Namespace::MessageTypeText:
        return TLValue::MessageMediaEmpty;
    case Namespace::MessageTypePhoto:
        return TLValue::MessageMediaPhoto;
    case Namespace::MessageTypeGeo:
        return TLValue::MessageMediaGeo;
    case Namespace::MessageTypeContact:
        return TLValue::MessageMediaContact;
    case Namespace::MessageTypeDocument:
        return TLValue::MessageMediaDocument;
    case Namespace::MessageTypeWebPage:
        return TLValue::MessageMediaWebPage;
    default:
        return TLValue::MessageMediaUnsupported;
    }
}

Telegram::MessageAction toPublic(const TLSendMessageAction &action)
{
    Telegram::MessageAction publicAction;
    switch (action.tlType) {
    case TLValue::SendMessageCancelAction:
        publicAction.type = Telegram::MessageAction::Type::None;
        break;
    case TLValue::SendMessageTypingAction:
        publicAction.type = Telegram::MessageAction::Type::Typing;
        break;
    case TLValue::SendMessageRecordVideoAction:
        publicAction.type = Telegram::MessageAction::Type::RecordVideo;
        break;
    case TLValue::SendMessageRecordAudioAction:
        publicAction.type = Telegram::MessageAction::Type::RecordAudio;
        break;
    case TLValue::SendMessageUploadVideoAction:
        publicAction.type = Telegram::MessageAction::Type::UploadVideo;
        publicAction.progress = action.progress;
        break;
    case TLValue::SendMessageUploadAudioAction:
        publicAction.type = Telegram::MessageAction::Type::UploadAudio;
        publicAction.progress = action.progress;
        break;
    case TLValue::SendMessageUploadPhotoAction:
        publicAction.type = Telegram::MessageAction::Type::UploadPhoto;
        publicAction.progress = action.progress;
        break;
    case TLValue::SendMessageUploadDocumentAction:
        publicAction.type = Telegram::MessageAction::Type::UploadDocument;
        publicAction.progress = action.progress;
        break;
    case TLValue::SendMessageUploadRoundAction:
        publicAction.type = Telegram::MessageAction::Type::UploadRoundVideo;
        publicAction.progress = action.progress;
        break;
    case TLValue::SendMessageGeoLocationAction:
        publicAction.type = Telegram::MessageAction::Type::GeoLocation;
        break;
    case TLValue::SendMessageChooseContactAction:
        publicAction.type = Telegram::MessageAction::Type::ChooseContact;
        break;
    default:
        break;
    }
    return publicAction;
}

TLSendMessageAction toTL(const Telegram::MessageAction &action)
{
    TLSendMessageAction tlAction;

    switch (action.type) {
    case Telegram::MessageAction::Type::None:
        tlAction.tlType = TLValue::SendMessageCancelAction;
        break;
    case Telegram::MessageAction::Type::Typing:
        tlAction.tlType = TLValue::SendMessageTypingAction;
        break;
    case Telegram::MessageAction::Type::RecordVideo:
        tlAction.tlType = TLValue::SendMessageRecordVideoAction;
        break;
    case Telegram::MessageAction::Type::RecordAudio:
        tlAction.tlType = TLValue::SendMessageRecordAudioAction;
        break;
    case Telegram::MessageAction::Type::UploadVideo:
        tlAction.tlType = TLValue::SendMessageUploadVideoAction;
        tlAction.progress = action.progress;
        break;
    case Telegram::MessageAction::Type::UploadAudio:
        tlAction.tlType = TLValue::SendMessageUploadAudioAction;
        tlAction.progress = action.progress;
        break;
    case Telegram::MessageAction::Type::UploadPhoto:
        tlAction.tlType = TLValue::SendMessageUploadPhotoAction;
        tlAction.progress = action.progress;
        break;
    case Telegram::MessageAction::Type::UploadDocument:
        tlAction.tlType = TLValue::SendMessageUploadDocumentAction;
        tlAction.progress = action.progress;
        break;
    case Telegram::MessageAction::Type::UploadRoundVideo:
        tlAction.tlType = TLValue::SendMessageUploadRoundAction;
        tlAction.progress = action.progress;
        break;
    case Telegram::MessageAction::Type::GeoLocation:
        tlAction.tlType = TLValue::SendMessageGeoLocationAction;
        break;
    case Telegram::MessageAction::Type::ChooseContact:
        tlAction.tlType = TLValue::SendMessageChooseContactAction;
        break;
    }

    return tlAction;
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
