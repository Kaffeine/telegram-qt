#ifndef TELEGRAM_DECLARATIVE_CLIENT_HPP
#define TELEGRAM_DECLARATIVE_CLIENT_HPP

#include <QObject>

#include "telegramqt_qml_global.h"

namespace Telegram {

namespace Client {

class AccountApi;
class AppInformation;
class Client;
class DeclarativeSettings;
class AccountStorage;
class DataStorage;
class ConnectionApi;
class MessagingApi;

class TELEGRAMQT_QML_EXPORT DeclarativeClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Client::AppInformation *applicationInformation READ appInformation WRITE setAppInformation)
    Q_PROPERTY(bool signedIn READ isSignedIn NOTIFY signedInChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeSettings *settings READ settings WRITE setSettings NOTIFY settingsChanged)
    Q_PROPERTY(Telegram::Client::AccountStorage *accountStorage READ accountStorage WRITE setAccountStorage NOTIFY accountStorageChanged)
    Q_PROPERTY(Telegram::Client::DataStorage *dataStorage READ dataStorage WRITE setDataStorage NOTIFY dataStorageChanged)

    Q_PROPERTY(Telegram::Client::AccountApi *accountApi READ accountApi CONSTANT)
    Q_PROPERTY(Telegram::Client::ConnectionApi *connectionApi READ connectionApi CONSTANT)
    Q_PROPERTY(Telegram::Client::MessagingApi *messagingApi READ messagingApi CONSTANT)
public:
    explicit DeclarativeClient(QObject *parent = nullptr);

    AppInformation *appInformation() const;

    bool isSignedIn() const;
    Client *client() { return m_client; }

    DeclarativeSettings *settings() const { return m_settings; }
    AccountStorage *accountStorage() const;
    DataStorage *dataStorage() const;
    AccountApi *accountApi() const;
    ConnectionApi *connectionApi() const;
    MessagingApi *messagingApi() const;

public slots:
    void setAppInformation(AppInformation *newAppInfo);
    void setSettings(DeclarativeSettings *settings);
    void setAccountStorage(AccountStorage *storage);
    void setDataStorage(DataStorage *storage);

    bool syncSettings();

signals:
    void signedInChanged(bool signedIn);
    void settingsChanged();
    void accountStorageChanged();
    void dataStorageChanged();

protected:
    Client *m_client = nullptr;
    DeclarativeSettings *m_settings = nullptr;
    AccountStorage *m_accountStorage = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_SETTINGS_HPP
