#ifndef TELEGRAM_SERVER_UTILS_HPP
#define TELEGRAM_SERVER_UTILS_HPP

#include <QSet>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

class AbstractUser;
class LocalUser;
class MessageData;
class ServerApi;

namespace Utils {

void getInterestingPeers(QSet<Peer> *peers, const TLVector<TLMessage> &messages);

bool setupTLUser(TLUser *output, const AbstractUser *input, const LocalUser *forUser);
bool setupTLUpdatesState(TLUpdatesState *output, const LocalUser *forUser);
bool setupTLPeers(TLVector<TLUser> *users, TLVector<TLChat> *chats,
                  const QSet<Peer> &peers, const ServerApi *api, const LocalUser *forUser);
bool setupTLMessage(TLMessage *output, const MessageData *messageData, quint32 messageId,
                    const LocalUser *forUser);

template <typename T>
bool setupTLPeers(T *output,
                  const QSet<Peer> &peers, const ServerApi *api, const LocalUser *forUser)
{
    return setupTLPeers(&output->users, &output->chats,
                        peers, api, forUser);
}

} // Utils namespace

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
