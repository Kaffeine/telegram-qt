#include "ServerUtils.hpp"

#include "ApiUtils.hpp"
#include "GroupChat.hpp"
#include "ServerApi.hpp"
#include "ServerMessageData.hpp"
#include "ServerNamespace.hpp"
#include "TelegramServerUser.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

namespace Utils {

void getInterestingPeers(QSet<Peer> *peers, const TLChatFull &chatFull)
{
    if (chatFull.tlType == TLValue::ChatFull) {
        peers->insert(Peer::fromChatId(chatFull.id));
    } else if (chatFull.tlType == TLValue::ChannelFull) {
        peers->insert(Peer::fromChannelId(chatFull.id));
    }

    for (const TLChatParticipant &participant : chatFull.participants.participants) {
        peers->insert(Peer::fromUserId(participant.userId));
    }
}

void getInterestingPeers(QSet<Peer> *peers, const TLVector<TLMessage> &messages)
{
    for (const TLMessage &message : messages) {
        if (message.fromId) {
            Telegram::Peer messagePeer = Peer::fromUserId(message.fromId);
            peers->insert(messagePeer);
        }
        if (message.media.userId) {
            Telegram::Peer messagePeer = Peer::fromUserId(message.media.userId);
            peers->insert(messagePeer);
        }
    }
}

bool setupTLUser(TLUser *output, const AbstractUser *input, const AbstractUser *applicant)
{
    output->id = input->id();
    output->tlType = TLValue::User;
    output->firstName = input->firstName();
    output->lastName = input->lastName();
    output->username = input->userName();
    // TODO: Check if the user has access to the requested user phone
    output->phone = input->phoneNumber();
    setupTLUserStatus(&output->status, input, applicant);

    ImageDescriptor image = input->getCurrentImage();

    if (image.isValid()) {
        output->photo.tlType = TLValue::UserProfilePhoto;
        output->photo.photoId = image.id;
        setupTLFileLocation(&output->photo.photoSmall, image.sizes.first().fileDescriptor);
        setupTLFileLocation(&output->photo.photoBig, image.sizes.last().fileDescriptor);
    } else {
        output->photo.tlType = TLValue::UserProfilePhotoEmpty;
    }

    quint32 flags = 0;
    if (!output->firstName.isEmpty()) {
        flags |= TLUser::FirstName;
    }
    if (!output->lastName.isEmpty()) {
        flags |= TLUser::LastName;
    }
    if (!output->username.isEmpty()) {
        flags |= TLUser::Username;
    }
    if (!output->phone.isEmpty()) {
        flags |= TLUser::Phone;
    }
    if (output->photo.tlType != TLValue::UserProfilePhotoEmpty) {
        flags |= TLUser::Photo;
    }
    if (output->status.tlType != TLValue::UserStatusEmpty) {
        flags |= TLUser::Status;
    }
    if (output->id == applicant->id()) {
        flags |= TLUser::Self;
    }
    if (applicant->contactList().contains(output->id)) {
        flags |= TLUser::Contact;
        if (input->contactList().contains(applicant->id())) {
            flags |= TLUser::MutualContact;
        }
    }
    output->flags = flags;

    return true;
}

bool setupTLUserStatus(TLUserStatus *output, const AbstractUser *input, const AbstractUser *forUser)
{
    Q_UNUSED(forUser)
    const quint32 onlineDate = input->onlineTimestamp();
    const quint32 currentDate = Telegram::Utils::getCurrentTime();

    if (currentDate > onlineDate) {
        output->tlType = TLValue::UserStatusOffline;
        output->wasOnline = onlineDate;
    } else {
        output->tlType = TLValue::UserStatusOnline;
        output->expires = onlineDate;
    }

    return true;
}

bool setupTLChat(TLChat *output, const GroupChat *input, const AbstractUser *forUser)
{
    output->tlType = TLValue::Chat;
    output->id = input->id();
    output->title = input->title();
    output->date = input->date();
    output->version = 1;
    output->participantsCount = input->members().count();

    quint32 flags = 0;
    if (input->creatorId() == forUser->id()) {
        output->flags |= TLChat::Creator;
    }
    output->flags = flags;

    return true;
}

bool setupTLChatFull(TLChatFull *output, const GroupChat *input, const AbstractUser *forUser)
{
    output->id = input->id();
    Utils::setupTLChatParticipants(&output->participants, input, forUser);

    return true;
}

bool setupTLChatParticipants(TLChatParticipants *output, const GroupChat *input, const AbstractUser *forUser)
{
    const QVector<ChatMember> members = input->members();

    output->tlType = TLValue::ChatParticipants;
    output->chatId = input->id();
    output->version = 1;
    output->participants.reserve(members.count());
    for (const ChatMember &member : members) {
        output->participants.append(TLChatParticipant());
        TLChatParticipant &participant = output->participants.last();
        participant.userId = member.userId;
        switch (member.role) {
        case ChatMember::Role::Creator:
            participant.tlType = TLValue::ChatParticipantCreator;
            break;
        case ChatMember::Role::Admin:
            participant.tlType = TLValue::ChatParticipantAdmin;
            participant.inviterId = member.inviterId;
            participant.date = member.date;
            break;
        case ChatMember::Role::User:
            participant.tlType = TLValue::ChatParticipant;
            participant.inviterId = member.inviterId;
            participant.date = member.date;
            break;
        case ChatMember::Role::Invalid:
            break;
        }
    }

    return true;
}

bool setupTLContactsLink(TLContactsLink *output, const AbstractUser *input, const AbstractUser *forUser)
{
    setupTLUser(&output->user, input, forUser);
    if (forUser->contactList().contains(input->id())) {
        output->myLink.tlType = TLValue::ContactLinkContact;
    } else {
        output->myLink.tlType = TLValue::ContactLinkNone;
    }

    if (input->contactList().contains(forUser->id())) {
        output->foreignLink.tlType = TLValue::ContactLinkContact;
    } else {
        output->foreignLink.tlType = TLValue::ContactLinkNone;
    }

    return true;
}

bool setupTLUpdatesState(TLUpdatesState *output, const AbstractUser *forUser)
{
    const UserPostBox *box = forUser->getPostBox();
    output->pts = box->pts();
    output->date = Telegram::Utils::getCurrentTime();
    output->seq = 1; // FIXME
    output->qts = 0;
    output->unreadCount = box->unreadCount();
    return true;
}

bool setupTLPeers(TLVector<TLUser> *users, TLVector<TLChat> *chats,
                  const QSet<Peer> &peers, const AbstractServerApi *api, const AbstractUser *forUser)
{
    users->clear();
    chats->clear();
    for (const Peer &peer : peers) {
        if (!peer.isValid()) {
            continue;
        }
        switch (peer.type()) {
        case Peer::User:
        {
            users->append(TLUser());
            AbstractUser *user = api->getAbstractUser(peer.id());
            if (!user) {
                qWarning() << Q_FUNC_INFO << "User not found:" << peer.id();
                continue;
            }
            setupTLUser(&users->last(), user, forUser);
        }
            break;
        case Peer::Chat:
        {
            chats->append(TLChat());
            GroupChat *chat = api->getGroupChat(peer.id());
            if (!chat) {
                qWarning() << Q_FUNC_INFO << "Chat not found:" << peer.id();
                continue;
            }
            setupTLChat(&chats->last(), chat, forUser);
        }
            break;
        case Peer::Channel:
            return false;
        }
    }
    return true;
}

static void setupUserMessage(TLMessage *output, const MessageData *messageData, const AbstractUser *forUser)
{
    output->tlType = TLValue::Message;

    quint32 flags = 0;
    //if (!receiverInbox->isBroadcast()) {
        output->fromId = messageData->fromId();
        flags |= TLMessage::FromId;
    //}
    output->message = messageData->content().text();
    output->editDate = messageData->editDate();
    if (output->editDate) {
        flags |= TLMessage::EditDate;
    }

    if (messageData->content().media().isValid()) {
        setupTLMessageMedia(&output->media, &messageData->content().media());
        flags |= TLMessage::Media;
    }

    const bool messageToSelf = messageData->toPeer() == forUser->toPeer();
    if (messageData->fromId() == forUser->id()) {
        if (!messageToSelf) {
            flags |= TLMessage::Out;
        }
    }
    output->flags = flags;
}

static void setupServiceMessage(TLMessage *output, const MessageData *messageData, const AbstractUser *forUser)
{
    output->tlType = TLValue::MessageService;

    quint32 flags = 0;
    //if (!receiverInbox->isBroadcast()) {
        output->fromId = messageData->fromId();
        flags |= TLMessage::FromId;
    //}
    switch (messageData->action().type) {
    case ServiceMessageAction::Type::Empty:
        break;
    case ServiceMessageAction::Type::ChatCreate:
        output->action.tlType = TLValue::MessageActionChatCreate;
        output->action.title = messageData->action().title;
        output->action.users = messageData->action().users;
        break;
    }

    output->flags = flags;
}

bool setupTLMessage(TLMessage *output, const MessageData *messageData, quint32 messageId,
                    const AbstractUser *forUser)
{
    output->id = messageId;
    output->date = messageData->date();
    output->toId = Telegram::Utils::toTLPeer(messageData->toPeer());

    if (messageData->isServiceMessage()) {
        setupServiceMessage(output, messageData, forUser);
    } else {
        setupUserMessage(output, messageData, forUser);
    }

    return true;
}

bool setupTLPhoto(TLPhoto *output, const ImageDescriptor &image)
{
    output->id = image.id;
    if (!image.isValid()) {
        output->tlType = TLValue::PhotoEmpty;
        return false;
    }

    output->date = image.date;
    output->flags = 0;
    output->tlType = TLValue::Photo;
    output->sizes.resize(image.sizes.count());

    for (int i = 0; i < image.sizes.count(); ++i) {
        const ImageSizeDescriptor &size = image.sizes.at(i);

        output->sizes[i].tlType = TLValue::PhotoSize;
        output->sizes[i].w = size.w;
        output->sizes[i].h = size.h;
        output->sizes[i].type = size.sizeType;
        output->sizes[i].bytes = size.bytes;
        output->sizes[i].size = size.size;

        switch (size.sizeType) {
        case ImageSizeDescriptor::Small:
            output->sizes[i].type = QLatin1String("s");
            break;
        case ImageSizeDescriptor::Medium:
            output->sizes[i].type = QLatin1String("m");
            break;
        case ImageSizeDescriptor::Large:
            output->sizes[i].type = QLatin1String("x");
            break;
        case ImageSizeDescriptor::Max:
            output->sizes[i].type = QLatin1String("y");
            break;
        default:
            qCritical() << Q_FUNC_INFO << "Unexpected size type" << size.sizeType;
            break;
        }

        setupTLFileLocation(&output->sizes[i].location, size.fileDescriptor);
    }

    return true;
}

bool setupTLFileLocation(TLFileLocation *output, const FileDescriptor &file)
{
    if (!file.isValid()) {
        output->tlType = TLValue::FileLocationUnavailable;
        return false;
    }

    output->dcId = file.dcId;
    output->volumeId = file.volumeId;
    output->localId = file.localId;
    output->secret = file.secret;
    output->tlType = TLValue::FileLocation;
    return true;
}

bool setupTLMessageMedia(TLMessageMedia *output, const MediaData *mediaData)
{
    switch (mediaData->type) {
    case MediaData::Invalid:
        return false;
    case MediaData::Contact:
        output->tlType = TLValue::MessageMediaContact;
        output->phoneNumber = mediaData->contact.phone;
        output->firstName = mediaData->contact.firstName;
        output->lastName = mediaData->contact.lastName;
        output->userId = mediaData->contact.id;
        break;
    case MediaData::Document:
        output->tlType = TLValue::MessageMediaDocument;
        output->flags = 0;
        output->flags |= TLMessageMedia::Document;
        output->document.tlType = TLValue::Document;
        output->document.date = mediaData->file.date;
        output->document.size = mediaData->file.size;
        output->document.mimeType = mediaData->mimeType;
        output->document.dcId = mediaData->file.dcId;
        output->document.accessHash = mediaData->file.accessHash;
        output->document.id = mediaData->file.id;

        for (const DocumentAttribute &attribute : mediaData->attributes) {
            TLDocumentAttribute tlAttribute;
            switch (attribute.type) {
            case DocumentAttribute::FileName:
                tlAttribute.tlType = TLValue::DocumentAttributeFilename;
                tlAttribute.fileName = attribute.value.toString();
                output->document.attributes.append(tlAttribute);
                break;
            default:
                break;
            }
        }

        break;
    case MediaData::Photo:
        output->tlType = TLValue::MessageMediaPhoto;
        output->flags = 0;
        output->flags |= TLMessageMedia::Photo;
        Utils::setupTLPhoto(&output->photo, mediaData->image);
        break;
    }

#if TELEGRAMQT_LAYER < 73
    if (!mediaData->caption.isEmpty()) {
        output->caption = mediaData->caption;
        output->flags |= TLMessageMedia::Caption;
    }
#endif

    return true;
}

} // Utils namespace

} // Server namespace

} // Telegram namespace
