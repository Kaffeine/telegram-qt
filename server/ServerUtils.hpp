#ifndef TELEGRAM_SERVER_UTILS_HPP
#define TELEGRAM_SERVER_UTILS_HPP

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

class AbstractUser;
class LocalUser;
class ServerApi;

namespace Utils {

bool setupTLUser(TLUser *output, const AbstractUser *input, const LocalUser *forUser);
bool setupTLUpdatesState(TLUpdatesState *output, const LocalUser *forUser);

} // Utils namespace

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_API_HPP
