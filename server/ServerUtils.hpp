#ifndef TELEGRAM_SERVER_UTILS_HPP
#define TELEGRAM_SERVER_UTILS_HPP

#include <QSet>

#include "MTProto/TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

class AbstractUser;
class GroupChat;
class MediaData;
class MessageData;
class AbstractServerApi;

class FileDescriptor;
class ImageDescriptor;

namespace Utils {

void getInterestingPeers(QSet<Peer> *peers, const TLChatFull &chatFull);
void getInterestingPeers(QSet<Peer> *peers, const QVector<TLMessage> &messages);

bool setupTLUser(TLUser *output, const AbstractUser *input, const AbstractUser *forUser);
bool setupTLUserStatus(TLUserStatus *output, const AbstractUser *input, const AbstractUser *forUser);
bool setupTLChat(TLChat *output, const GroupChat *input, const AbstractUser *forUser);
bool setupTLChatFull(TLChatFull *output, const GroupChat *input, const AbstractUser *forUser);
bool setupTLChatParticipants(TLChatParticipants *output, const GroupChat *input, const AbstractUser *forUser);
bool setupTLContactsLink(TLContactsLink *output, const AbstractUser *input, const AbstractUser *forUser);
bool setupTLUpdatesState(TLUpdatesState *output, const AbstractUser *forUser);
bool setupTLPeers(QVector<TLUser> *users, QVector<TLChat> *chats,
                  const QSet<Peer> &peers, const AbstractServerApi *api, const AbstractUser *forUser);
bool setupTLMessage(TLMessage *output, const MessageData *messageData, quint32 messageId,
                    const AbstractUser *forUser);

bool setupTLMessageMedia(TLMessageMedia *output, const MediaData *mediaData);

template <typename T>
bool setupTLPeers(T *output,
                  const QSet<Peer> &peers, const AbstractServerApi *api, const AbstractUser *forUser)
{
    return setupTLPeers(&output->users, &output->chats,
                        peers, api, forUser);
}

bool setupTLPhoto(TLPhoto *output, const ImageDescriptor &image);
bool setupTLFileLocation(TLFileLocation *output, const FileDescriptor &file);

} // Utils namespace

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
