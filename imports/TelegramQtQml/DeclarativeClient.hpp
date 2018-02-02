#ifndef TELEGRAM_DECLARATIVE_CLIENT_HPP
#define TELEGRAM_DECLARATIVE_CLIENT_HPP

#include <QObject>

class CAppInformation;

namespace Telegram {

namespace Client {

class Client;
class DeclarativeSettings;
class AccountStorage;

class DeclarativeClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CAppInformation *applicationInformation READ appInformation WRITE setAppInformation)
    Q_PROPERTY(bool signedIn READ isSignedIn NOTIFY signedInChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeSettings *settings READ settings WRITE setSettings NOTIFY settingsChanged)
    Q_PROPERTY(Telegram::Client::AccountStorage *accountStorage READ accountStorage WRITE setAccountStorage NOTIFY accountStorageChanged)
    Q_PROPERTY(QObject *dataStorage MEMBER m_dataStorage)
public:
    explicit DeclarativeClient(QObject *parent = nullptr);

    CAppInformation *appInformation() const;

    bool isSignedIn() const;
    Client *backend() { return m_client; }

    DeclarativeSettings *settings() const { return m_settings; }
    AccountStorage *accountStorage() const;

public slots:
    void setAppInformation(CAppInformation *newAppInfo);
    void setSettings(DeclarativeSettings *settings);
    void setAccountStorage(AccountStorage *storage);

    void syncSettings();

signals:
    void signedInChanged(bool signedIn);
    void settingsChanged();
    void accountStorageChanged();

protected:
    Client *m_client;
    DeclarativeSettings *m_settings;
    AccountStorage *m_accountStorage;
    QObject *m_dataStorage;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_SETTINGS_HPP
