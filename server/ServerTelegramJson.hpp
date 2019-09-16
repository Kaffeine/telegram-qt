#ifndef TELEGRAM_QT_SERVER_JSON_HPP
#define TELEGRAM_QT_SERVER_JSON_HPP

#include "JsonUtils_p.hpp"

#include <QJsonValue>

namespace Telegram {

namespace Server {

class UserContact;

} // Server namespace

namespace Json {

QJsonValue toValue(const Server::UserContact &userContact);

template<>
Server::UserContact fromValue<>(const QJsonValue &jsonValue);

} // Json namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_JSON_HPP
