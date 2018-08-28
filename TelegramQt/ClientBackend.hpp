#ifndef TELEGRAM_CLIENT_BACKEND_HPP
#define TELEGRAM_CLIENT_BACKEND_HPP

#include <QObject>
#include <QVector>


class CAppInformation;
struct TLDcOption;

namespace Telegram {

class PendingOperation;

namespace Client {

class Connection;
class Client;
class Settings;
class AccountStorage;
class DataStorage;
class RpcLayer;
class AuthOperation;

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(Client *parent);

    RpcLayer *rpcLayer();

    PendingOperation *connectToServer();
    AuthOperation *signIn();

    Connection *createConnection();
    Connection *createConnection(const TLDcOption &dcInfo);
    Connection *mainConnection();

    void setMainConnection(Connection *connection);

    CAppInformation *m_appInformation = nullptr;
    Client *m_client; // Parent
    Settings *m_settings;
    AccountStorage *m_accountStorage;
    DataStorage *m_dataStorage;
    Connection *m_mainConnection = nullptr;

    AuthOperation *m_authOperation = nullptr;

    bool m_signedIn = false;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_BACKEND_HPP
