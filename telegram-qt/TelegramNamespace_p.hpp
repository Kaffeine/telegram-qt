#ifndef TELEGRAMNAMESPACE_P_HPP
#define TELEGRAMNAMESPACE_P_HPP

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class TelegramNamespace::MessageMediaInfo::Private : public TLMessageMedia { };
class TelegramNamespace::PasswordInfo::Private : public TLAccountPassword { };
class TelegramNamespace::UserInfo::Private : public TLUser { };

TelegramNamespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

#endif // TELEGRAMNAMESPACE_P_HPP

