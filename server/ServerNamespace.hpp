#ifndef TELEGRAM_SERVER_NAMESPACE_HPP
#define TELEGRAM_SERVER_NAMESPACE_HPP

#include "TelegramNamespace.hpp"

#include <QString>

namespace Telegram {

namespace Server {

struct InputPeer : public Telegram::Peer
{
    InputPeer() = default;
    InputPeer(const Telegram::Peer &peer);

    qint64 accessHash = 0;
};

struct ServerSalt
{
    quint64 salt = 0;
    quint32 validSince = 0;
    quint32 validUntil = 0;
};

} // Server

} // Telegram

#endif // TELEGRAM_SERVER_NAMESPACE_HPP
