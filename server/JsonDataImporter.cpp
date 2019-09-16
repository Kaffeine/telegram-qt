#include "JsonDataImporter.hpp"

#include "AuthService.hpp"
#include "JsonUtils_p.hpp"
#include "ServerTelegramJson.hpp"
#include "ServerImportApi.hpp"
#include "Session.hpp"
#include "TelegramServer.hpp"
#include "TelegramServerUser.hpp"
#include "Utils.hpp"

#include <QDir>
#include <QFile>
#include <QJsonDocument>

namespace Telegram {

namespace Server {

void JsonDataImporter::setBaseDirectory(const QString &directory)
{
    if (directory.isEmpty()) {
        m_baseDirectory.clear();
        return;
    }
    m_baseDirectory = directory;
    if (!m_baseDirectory.endsWith(QLatin1Char('/'))) {
        m_baseDirectory.append(QLatin1Char('/'));
    }
}

bool JsonDataImporter::prepare()
{
    if (m_baseDirectory.isEmpty()) {
        return false;
    }
    if (!QDir().mkpath(m_baseDirectory)) {
        return false;
    }

    return true;
}

void JsonDataImporter::exportForServer(Server *server)
{
    ServerImportApi importApi(server);

    QJsonObject root;
    root[QLatin1String("version")] = 1;
    root[QLatin1String("authKeys")] = Json::toJsonArray(importApi.getAuthorizations());
    const QList<Session *> sessions = importApi.getSessions();

    {
        QJsonArray sessionArray;
        for (const Session *session : sessions) {
            QJsonObject sessionObject;
            sessionObject[QLatin1String("id")]             = Json::toValue(session->id());
            sessionObject[QLatin1String("layer")]          = Json::toValue(session->layer());
            sessionObject[QLatin1String("getServerSalt")]  = Json::toValue(session->getServerSalt());
            sessionObject[QLatin1String("ip")]             = Json::toValue(session->ip);
            sessionObject[QLatin1String("timestamp")]      = Json::toValue(session->timestamp);
            sessionObject[QLatin1String("appId")]          = Json::toValue(session->appId);
            sessionObject[QLatin1String("appVersion")]     = Json::toValue(session->appVersion);
            sessionObject[QLatin1String("osInfo")]         = Json::toValue(session->osInfo);
            sessionObject[QLatin1String("deviceInfo")]     = Json::toValue(session->deviceInfo);
            sessionObject[QLatin1String("sequenceNumber")] = Json::toValue(session->lastSequenceNumber);
            sessionObject[QLatin1String("messageNumber")]  = Json::toValue(session->lastMessageNumber);
            sessionObject[QLatin1String("systemLanguage")] = Json::toValue(session->systemLanguage);
            sessionObject[QLatin1String("languagePack")]   = Json::toValue(session->languagePack);
            sessionObject[QLatin1String("languageCode")]   = Json::toValue(session->languageCode);
            sessionArray.append(sessionObject);
        }
        if (!sessionArray.isEmpty()) {
            root[QLatin1String("sessions")] = sessionArray;
        }
    }

    {
        QJsonArray usersArray;
        const QList<quint32> localUserIds = importApi.getLocalUsers();
        for (quint32 userId : localUserIds) {
            const LocalUser *user = server->getUser(userId);
            QJsonObject userObject;
            userObject[QLatin1String("id")] = Json::toValue(user->id());
            userObject[QLatin1String("phoneNumber")] = user->phoneNumber();
            userObject[QLatin1String("firstName")] = user->firstName();
            userObject[QLatin1String("lastName")] = user->lastName();
            if (!user->userName().isEmpty()) {
                userObject[QLatin1String("userName")] = user->userName();
            }

            quint32 onlineTimestamp = user->onlineTimestamp();
            if (onlineTimestamp) {
                userObject["onlineTimestamp"] = Json::toValue(onlineTimestamp);
            }

            QJsonArray sessionsArray;
            for (const Session *session : user->sessions()) {
                sessionsArray.append(Json::toValue(session->id()));
            }
            if (!sessionsArray.isEmpty()) {
                userObject[QLatin1String("sessions")] = sessionsArray;
            }

            QJsonArray authorizationsArray = Json::toJsonArray(user->authorizations());
            if (!authorizationsArray.isEmpty()) {
                userObject[QLatin1String("authorizations")] = authorizationsArray;
            }

            QJsonArray importedContactsArray = Json::toJsonArray(user->importedContacts(), &Json::toValue);
            if (!importedContactsArray.isEmpty()) {
                userObject[QLatin1String("importedContacts")] = importedContactsArray;
            }

            usersArray.append(userObject);
        }
        if (!usersArray.isEmpty()) {
            root[QLatin1String("users")] = usersArray;
        }
    }

    QFile data(m_baseDirectory + QStringLiteral("server%1.json").arg(server->dcId()));
    data.open(QIODevice::WriteOnly);
    data.write(QJsonDocument(root).toJson());
}

void JsonDataImporter::importForServer(Server *server)
{
    QFile data(m_baseDirectory + QStringLiteral("server%1.json").arg(server->dcId()));
    data.open(QIODevice::ReadOnly);
    const QJsonObject root = QJsonDocument::fromJson(data.readAll()).object();

    ServerImportApi importApi(server);
    {
        const QJsonArray authKeysArray = root.value(QLatin1String("authKeys")).toArray();
        for (const QJsonValue &authKeyValue : authKeysArray) {
            const QByteArray authKey = Json::fromValue<QByteArray>(authKeyValue);
            const quint64 keyId = Telegram::Utils::getFingerprints(authKey, Telegram::Utils::Lower64Bits);
            importApi.addAuthKey(keyId, authKey);
        }
    }

    {
        const QJsonArray sessionArray = root.value(QLatin1String("sessions")).toArray();
        for (const QJsonValue &sessionArrayValue : sessionArray) {
            const QJsonObject sessionObject = sessionArrayValue.toObject();

            quint64 sessionId = Json::fromValue<quint64>(sessionObject[QLatin1String("id")]);

            Session *session = importApi.addSession(sessionId);
            session->setLayer(Json::fromValue<quint32>(sessionObject[QLatin1String("layer")]));
            session->setInitialServerSalt(Json::fromValue<quint64>(sessionObject[QLatin1String("getServerSalt")]));

            Json::fromValue(&session->ip, sessionObject[QLatin1String("ip")]);
            Json::fromValue(&session->timestamp, sessionObject[QLatin1String("timestamp")]);
            Json::fromValue(&session->appId, sessionObject[QLatin1String("appId")]);
            Json::fromValue(&session->appVersion, sessionObject[QLatin1String("appVersion")]);
            Json::fromValue(&session->osInfo, sessionObject[QLatin1String("osInfo")]);
            Json::fromValue(&session->deviceInfo, sessionObject[QLatin1String("deviceInfo")]);
            Json::fromValue(&session->lastSequenceNumber, sessionObject[QLatin1String("lastSequenceNumber")]);
            Json::fromValue(&session->lastMessageNumber, sessionObject[QLatin1String("lastMessageNumber")]);
            Json::fromValue(&session->systemLanguage, sessionObject[QLatin1String("systemLanguage")]);
            Json::fromValue(&session->languagePack, sessionObject[QLatin1String("languagePack")]);
            Json::fromValue(&session->languageCode, sessionObject[QLatin1String("languageCode")]);
        }
    }

    {
        const QJsonArray usersArray = root.value(QLatin1String("users")).toArray();
        for (const QJsonValue &userValue : usersArray) {
            const QJsonObject userObject = userValue.toObject();

            const quint32 userId = Json::fromValue<quint32>(userObject[QLatin1String("id")]);
            const QString phoneNumber = Json::fromValue<QString>(userObject[QLatin1String("phoneNumber")]);

            LocalUser *user = new LocalUser(userId, phoneNumber);
            user->setDcId(server->dcId());
            user->setFirstName(userObject[QLatin1String("firstName")].toString());
            user->setLastName(userObject[QLatin1String("lastName")].toString());
            user->setUserName(userObject[QLatin1String("userName")].toString());
            user->setOnlineTimestamp(Json::fromValue<quint32>(userObject[QLatin1String("onlineTimestamp")]));
            server->insertUser(user);

            const QJsonArray sessionArray = userObject[QLatin1String("sessions")].toArray();
            const QVector<quint64> sessions = Json::fromValue< QVector<quint64> >(sessionArray);
            for (const quint64 &sessionId : sessions) {
                Session *session = server->getSessionById(sessionId);
                if (!session) {
                    continue;
                }
                server->bindUserSession(user, session);
            }
            const QJsonArray authorizationsArray = userObject[QLatin1String("authorizations")].toArray();
            const QVector<quint64> authKeys = Json::fromValue< QVector<quint64> >(authorizationsArray);

            for (const quint64 &authKeyId : authKeys) {
                if (server->authService()->getAuthKeyById(authKeyId).isEmpty()) {
                    continue;
                }
                server->authService()->addUserAuthorization(user, authKeyId);
            }

            const QJsonArray importedContactsArray = userObject[QLatin1String("importedContacts")].toArray();
            const QVector<UserContact> importedContacts = Json::fromValue< QVector<UserContact> >(importedContactsArray);

            for (const UserContact &importedContact : importedContacts) {
                server->importUserContact(user, importedContact);
            }
        }
    }
}

} // Server namespace

} // Telegram namespace
