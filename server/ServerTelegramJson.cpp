#include "ServerTelegramJson.hpp"

#include "ServerNamespace.hpp"

#include <QJsonDocument>
#include <QJsonObject>

namespace Telegram {

namespace Json {

QJsonValue toValue(const Server::UserContact &userContact)
{
    QJsonObject messageObject;
    messageObject[QLatin1String("id")] = toValue(userContact.id);
    messageObject[QLatin1String("phone")] = toValue(userContact.phone);
    messageObject[QLatin1String("firstName")] = toValue(userContact.firstName);
    if (!userContact.lastName.isEmpty()) {
        messageObject[QLatin1String("lastName")] = toValue(userContact.lastName);
    }

    return messageObject;
}

template<>
Server::UserContact fromValue<>(const QJsonValue &jsonValue)
{
    const QJsonObject object = jsonValue.toObject();
    Server::UserContact userContact;
    userContact.id = fromValue<quint32>(object[QLatin1String("id")]);;
    userContact.phone = fromValue<QString>(object[QLatin1String("phone")]);
    userContact.firstName = fromValue<QString>(object[QLatin1String("firstName")]);
    userContact.lastName = fromValue<QString>(object[QLatin1String("lastName")]);
    return userContact;
}

} // Json namespace

} // Telegram namespace
