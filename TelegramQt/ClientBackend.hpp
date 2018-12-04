#ifndef TELEGRAM_CLIENT_BACKEND_HPP
#define TELEGRAM_CLIENT_BACKEND_HPP

#include <QObject>
#include <QVector>

#include "TelegramNamespace.hpp"
#include "DcConfiguration.hpp"

class CAppInformation;

namespace Telegram {

class PendingOperation;
struct DcOption;

namespace Client {

class Connection;
class Client;
class Settings;
class AccountStorage;
using AppInformation = ::CAppInformation;
class DataStorage;
class ConnectionApi;
class ContactsApi;
class MessagingApi;
class PendingRpcOperation;
class UpdatesInternalApi;

// Generated low-level layers forward declarations
class AccountRpcLayer;
class AuthRpcLayer;
class BotsRpcLayer;
class ChannelsRpcLayer;
class ContactsRpcLayer;
class HelpRpcLayer;
class LangpackRpcLayer;
class MessagesRpcLayer;
class PaymentsRpcLayer;
class PhoneRpcLayer;
class PhotosRpcLayer;
class StickersRpcLayer;
class UpdatesRpcLayer;
class UploadRpcLayer;
class UsersRpcLayer;
// End of generated low-level layers forward declarations

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
    Connection *ensureConnection(const ConnectionSpec &dcSpec);

    void setDcForLayer(const ConnectionSpec &dcSpec, BaseRpcLayerExtension *layer);

    DataStorage *dataStorage() { return m_dataStorage; }
    const DataStorage *dataStorage() const { return m_dataStorage; }

    MessagingApi *messagingApi() const { return m_messagingApi; }

    AccountStorage *accountStorage() { return m_accountStorage; }

    void processSeeOthers(PendingRpcOperation *operation);

    // Generated low-level layers
    AccountRpcLayer *accountLayer() { return m_accountLayer; }
    AuthRpcLayer *authLayer() { return m_authLayer; }
    BotsRpcLayer *botsLayer() { return m_botsLayer; }
    ChannelsRpcLayer *channelsLayer() { return m_channelsLayer; }
    ContactsRpcLayer *contactsLayer() { return m_contactsLayer; }
    HelpRpcLayer *helpLayer() { return m_helpLayer; }
    LangpackRpcLayer *langpackLayer() { return m_langpackLayer; }
    MessagesRpcLayer *messagesLayer() { return m_messagesLayer; }
    PaymentsRpcLayer *paymentsLayer() { return m_paymentsLayer; }
    PhoneRpcLayer *phoneLayer() { return m_phoneLayer; }
    PhotosRpcLayer *photosLayer() { return m_photosLayer; }
    StickersRpcLayer *stickersLayer() { return m_stickersLayer; }
    UpdatesRpcLayer *updatesLayer() { return m_updatesLayer; }
    UploadRpcLayer *uploadLayer() { return m_uploadLayer; }
    UsersRpcLayer *usersLayer() { return m_usersLayer; }
    // End of generated low-level layers

    AppInformation *m_appInformation = nullptr;
    Client *m_client = nullptr; // Parent
    Settings *m_settings = nullptr;
    AccountStorage *m_accountStorage = nullptr;
    DataStorage *m_dataStorage = nullptr;
    ConnectionApi *m_connectionApi = nullptr;
    ContactsApi *m_contactsApi = nullptr;
    MessagingApi *m_messagingApi = nullptr;

    // Generated low-level layer members
    AccountRpcLayer *m_accountLayer = nullptr;
    AuthRpcLayer *m_authLayer = nullptr;
    BotsRpcLayer *m_botsLayer = nullptr;
    ChannelsRpcLayer *m_channelsLayer = nullptr;
    ContactsRpcLayer *m_contactsLayer = nullptr;
    HelpRpcLayer *m_helpLayer = nullptr;
    LangpackRpcLayer *m_langpackLayer = nullptr;
    MessagesRpcLayer *m_messagesLayer = nullptr;
    PaymentsRpcLayer *m_paymentsLayer = nullptr;
    PhoneRpcLayer *m_phoneLayer = nullptr;
    PhotosRpcLayer *m_photosLayer = nullptr;
    StickersRpcLayer *m_stickersLayer = nullptr;
    UpdatesRpcLayer *m_updatesLayer = nullptr;
    UploadRpcLayer *m_uploadLayer = nullptr;
    UsersRpcLayer *m_usersLayer = nullptr;
    // End of generated low-level layer members

    UpdatesInternalApi *updatesApi() const { return m_updatesApi; }

    bool syncAccountToStorage();

protected:
    void onGetDcConfigurationFinished(PendingOperation *operation);

    void routeOperation(PendingRpcOperation *operation);

    PendingOperation *m_getConfigOperation = nullptr;
    UpdatesInternalApi *m_updatesApi = nullptr;
    QVector<PendingRpcOperation *> m_queuedRedirectedOperations;

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_BACKEND_HPP
