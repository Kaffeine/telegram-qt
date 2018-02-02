#ifndef TELEGRAMSERVER_HPP
#define TELEGRAMSERVER_HPP

#include <QObject>
#include "../TelegramQt/TLTypes.hpp"
#include "../TelegramQt/TelegramNamespace.hpp"

#include "ServerApi.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QTimer)

#include <QHash>
#include <QSet>
#include <QVector>

namespace Telegram {

namespace Server {

struct AuthCode
{
    QString hash;
    QString code;
};

class User;
class RemoteClientConnection;
class RpcOperationFactory;

class Server : public QObject, public ServerApi
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void setDcOption(const DcOption &option);

    void setServerPrivateRsaKey(const Telegram::RsaKey &key);

    bool start();
    void loadData();

    QSet<RemoteClientConnection*> getConnections() { return m_activeConnections; }

    quint32 getDcIdForUserIdentifier(const QString &phoneNumber);

    // ServerAPI:
    quint32 dcId() const override { return m_dcOption.id; }
    PhoneStatus getPhoneStatus(const QString &identifier) override;
    PasswordInfo getPassword(const QString &identifier) override;
    bool checkPassword(const QString &identifier, const QString &hash) override;
    QString sendAppCode(const QString &identifier) override;
    AuthCodeStatus getAuthCodeStatus(const QString &identifier, const QString &hash, const QString &code) override;
    bool identifierIsValid(const QString &identifier) override;

    User *getUser(const QString &identifier);
    User *getUser(quint64 authId);
    User *addUser(const QString &identifier);

    void insertUser(User *user);

signals:

public slots:

protected slots:
    void onNewConnection();

protected:
    void onClientConnectionStatusChanged();

protected:
    QHash<QString, AuthCode> m_sentCodeMap;

private:
    QTcpServer *m_serverSocket;
    DcOption m_dcOption;
    Telegram::RsaKey m_key;

    QHash<QString, quint32> m_phoneToUserId;
    QHash<quint64, quint32> m_authIdToUserId;
    QHash<quint32, User*> m_users; // userId to User
    QSet<RemoteClientConnection*> m_activeConnections;
    QVector<RpcOperationFactory*> m_rpcOperationFactories;
};

} // Server

} // Telegram

#endif // TELEGRAMSERVER_HPP
