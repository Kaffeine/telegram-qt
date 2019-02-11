#ifndef TELEGRAM_SERVER_UTILS_HPP
#define TELEGRAM_SERVER_UTILS_HPP

#include <QSet>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

class AbstractUser;
class LocalUser;
class ServerApi;

namespace Utils {

void getInterestingPeers(QSet<Peer> *peers, const TLVector<TLMessage> &messages);

bool setupTLUser(TLUser *output, const AbstractUser *input, const LocalUser *forUser);
bool setupTLUpdatesState(TLUpdatesState *output, const LocalUser *forUser);
bool setupTLPeers(const QSet<Peer> &peers, TLVector<TLUser> *users, TLVector<TLChat> *chats,
                  const ServerApi *api,
                  const LocalUser *forUser);

} // Utils namespace

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
