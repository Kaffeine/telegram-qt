#include "DeclarativeClient.hpp"

#include "../../TelegramQt/Client.hpp"
#include "DeclarativeSettings.hpp"

namespace Telegram {

namespace Client {

DeclarativeClient::DeclarativeClient(QObject *parent) :
    QObject(parent),
    m_client(new Client(this))
{
    connect(m_client, &Client::signedInChanged, this, &DeclarativeClient::signedInChanged);
}

CAppInformation *DeclarativeClient::appInformation() const
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

void DeclarativeClient::setAppInformation(CAppInformation *newAppInfo)
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

void DeclarativeClient::syncSettings()
{
    m_settings->syncSettings();
}

} // Client

} // Telegram
