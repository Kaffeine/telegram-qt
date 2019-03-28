#include "ServerUtils.hpp"

#include "ApiUtils.hpp"
#include "ServerApi.hpp"
#include "ServerMessageData.hpp"
#include "ServerNamespace.hpp"
#include "TelegramServerUser.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

namespace Utils {

void getInterestingPeers(QSet<Peer> *peers, const TLVector<TLMessage> &messages)
{
    for (const TLMessage &message : messages) {
        if (message.fromId) {
            Telegram::Peer messagePeer = Peer::fromUserId(message.fromId);
            peers->insert(messagePeer);
        }
    }
}

bool setupTLUser(TLUser *output, const AbstractUser *input, const LocalUser *applicant)
{
    output->id = input->id();
    output->tlType = TLValue::User;
    output->firstName = input->firstName();
    output->lastName = input->lastName();
    output->username = input->userName();
    // TODO: Check if the user has access to the requested user phone
    output->phone = input->phoneNumber();

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

bool setupTLUpdatesState(TLUpdatesState *output, const LocalUser *forUser)
{
    output->pts = forUser->getPostBox()->pts();
    output->date = Telegram::Utils::getCurrentTime();
    output->seq = 1; // FIXME
    output->qts = 0;
    output->unreadCount = 0;
    return true;
}

bool setupTLPeers(TLVector<TLUser> *users, TLVector<TLChat> *chats,
                  const QSet<Peer> &peers, const ServerApi *api, const LocalUser *forUser)
{
    users->clear();
    chats->clear();
    for (const Peer &peer : peers) {
        if (!peer.isValid()) {
            continue;
        }
        if (peer.type == Peer::User) {
            users->append(TLUser());
            AbstractUser *user = api->getAbstractUser(peer.id);
            if (!user) {
                qWarning() << Q_FUNC_INFO << "User not found:" << peer.id;
                continue;
            }
            setupTLUser(&users->last(), user, forUser);
        } else {
            // TODO
            return false;
        }
    }
    return true;
}

bool setupTLMessage(TLMessage *output, const MessageData *messageData, quint32 messageId,
                    const LocalUser *forUser)
{
    output->tlType = TLValue::Message;
    output->id = messageId;

    quint32 flags = 0;
    //if (!receiverInbox->isBroadcast()) {
        output->fromId = messageData->fromId();
        flags |= TLMessage::FromId;
    //}
    output->message = messageData->text();
    output->date = messageData->date();
    output->toId = Telegram::Utils::toTLPeer(messageData->toPeer());

    if (messageData->media().isValid()) {
        setupTLMessageMedia(&output->media, &messageData->media());
        flags |= TLMessage::Media;
    }

    const bool messageToSelf = messageData->toPeer() == forUser->toPeer();
    if (messageData->fromId() == forUser->userId()) {
        if (!messageToSelf) {
            flags |= TLMessage::Out;
        }
    }
    output->flags = flags;

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
    }

    if (!mediaData->caption.isEmpty()) {
        output->caption = mediaData->caption;
        output->flags |= TLMessageMedia::Caption;
    }

    return true;
}

} // Utils namespace

} // Server namespace

} // Telegram namespace
