#ifndef TELEGRAM_CLIENT_BACKEND_HPP
#define TELEGRAM_CLIENT_BACKEND_HPP

#include <QObject>
#include <QVector>

#include "TelegramNamespace.hpp"
#include "DcConfiguration.hpp"

namespace Telegram {

class PendingOperation;
struct DcOption;

namespace Client {

class AccountApi;
class AccountStorage;
class AppInformation;
class Client;
class Connection;
class ConnectionApi;
class ContactsApi;
class DataStorage;
class FilesApi;
class MessagingApi;
class PendingRpcOperation;
class Settings;
class UpdatesInternalApi;

class AccountRpcLayer;
class AuthRpcLayer;
class ChannelsRpcLayer;
class ContactsRpcLayer;
class HelpRpcLayer;
class MessagesRpcLayer;
class PhotosRpcLayer;
class UpdatesRpcLayer;
class UsersRpcLayer;

class BaseRpcLayerExtension;

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(Client *parent);

    bool isSignedIn() const;

    Settings *settings() const { return m_settings; }

    PendingOperation *getDcConfig();

    PendingOperation *sync();

    Connection *getDefaultConnection();

    DataStorage *dataStorage() { return m_dataStorage; }
    const DataStorage *dataStorage() const { return m_dataStorage; }

    ConnectionApi *connectionApi() const { return m_connectionApi; }
    FilesApi *filesApi() const { return m_filesApi; }
    MessagingApi *messagingApi() const { return m_messagingApi; }
    ContactsApi *contactsApi() const { return m_contactsApi; }

    AccountStorage *accountStorage() { return m_accountStorage; }

    AccountRpcLayer *accountLayer() { return m_accountLayer; }
    AuthRpcLayer *authLayer() { return m_authLayer; }
    ChannelsRpcLayer *channelsLayer() { return m_channelsLayer; }
    ContactsRpcLayer *contactsLayer() { return m_contactsLayer; }
    HelpRpcLayer *helpLayer() { return m_helpLayer; }
    MessagesRpcLayer *messagesLayer() { return m_messagesLayer; }
    PhotosRpcLayer *photosLayer() { return m_photosLayer; }
    UpdatesRpcLayer *updatesLayer() { return m_updatesLayer; }
    UsersRpcLayer *usersLayer() { return m_usersLayer; }

    AppInformation *m_appInformation = nullptr;
    Client *m_client = nullptr; // Parent
    Settings *m_settings = nullptr;
    AccountStorage *m_accountStorage = nullptr;
    DataStorage *m_dataStorage = nullptr;
    AccountApi *m_accountApi = nullptr;
    ConnectionApi *m_connectionApi = nullptr;
    ContactsApi *m_contactsApi = nullptr;
    MessagingApi *m_messagingApi = nullptr;
    FilesApi *m_filesApi = nullptr;

    AccountRpcLayer *m_accountLayer = nullptr;
    AuthRpcLayer *m_authLayer = nullptr;
    ChannelsRpcLayer *m_channelsLayer = nullptr;
    ContactsRpcLayer *m_contactsLayer = nullptr;
    HelpRpcLayer *m_helpLayer = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;
    PhotosRpcLayer *m_photosLayer = nullptr;
    UpdatesRpcLayer *m_updatesLayer = nullptr;
    UsersRpcLayer *m_usersLayer = nullptr;

    UpdatesInternalApi *updatesApi() const { return m_updatesApi; }

    bool syncAccountToStorage();

protected:
    void onGetDcConfigurationFinished(PendingOperation *operation);

    PendingOperation *m_getConfigOperation = nullptr;
    UpdatesInternalApi *m_updatesApi = nullptr;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_BACKEND_HPP
