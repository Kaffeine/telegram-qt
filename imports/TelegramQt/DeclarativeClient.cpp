#include "DeclarativeClient.hpp"

#include "../../TelegramQt/Client.hpp"
#include "DeclarativeSettings.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_qmlLoggingCategory, "telegram.client.qml", QtWarningMsg)

namespace Telegram {

namespace Client {

DeclarativeClient::DeclarativeClient(QObject *parent) :
    QObject(parent),
    m_client(new Client(this))
{
    connect(m_client, &Client::signedInChanged, this, &DeclarativeClient::signedInChanged);
}

AppInformation *DeclarativeClient::appInformation() const
{
    return m_client->appInformation();
}

bool DeclarativeClient::isSignedIn() const
{
    return m_client->isSignedIn();
}

AccountStorage *DeclarativeClient::accountStorage() const
{
    return m_client->accountStorage();
}

DataStorage *DeclarativeClient::dataStorage() const
{
    return m_client->dataStorage();
}

AccountApi *DeclarativeClient::accountApi() const
{
    return m_client->accountApi();
}

ConnectionApi *DeclarativeClient::connectionApi() const
{
    return m_client->connectionApi();
}

MessagingApi *DeclarativeClient::messagingApi() const
{
    return m_client->messagingApi();
}

void DeclarativeClient::setAppInformation(AppInformation *newAppInfo)
{
    m_client->setAppInformation(newAppInfo);
}

void DeclarativeClient::setSettings(DeclarativeSettings *settings)
{
    if (m_settings == settings) {
        return;
    }

    m_settings = settings;
    m_client->setSettings(settings);
    emit settingsChanged();
}

void DeclarativeClient::setAccountStorage(AccountStorage *storage)
{
    m_client->setAccountStorage(storage);
    emit accountStorageChanged();
}

void DeclarativeClient::setDataStorage(DataStorage *storage)
{
    m_client->setDataStorage(storage);
    emit dataStorageChanged();
}

bool DeclarativeClient::syncSettings()
{
    if (!m_settings) {
        qCCritical(c_qmlLoggingCategory).nospace() << this << ": Unable to sync settings (Settings instance is not set).";
        return false;
    }
    m_settings->syncSettings();
    return true;
}

} // Client

} // Telegram
