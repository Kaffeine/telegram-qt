#ifndef TELEGRAM_QT_JSON_P_HPP
#define TELEGRAM_QT_JSON_P_HPP

/* This file contains Telegram types to/from JSON converters */

#include "JsonUtils_p.hpp"

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Json {

inline QJsonValue toValue(const Peer &peer)
{
    return toValue(peer.toString());
}

inline Peer fromValue(const QJsonValue &value)
{
    return Telegram::Peer::fromString(value.toString());
}

} // Json namespace

} // Telegram namespace

#endif // TELEGRAM_QT_JSON_P_HPP
