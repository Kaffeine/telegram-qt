#include "TelegramServer.hpp"

#include <QLoggingCategory>
#include <QTcpServer>
#include <QTcpSocket>

#include "TelegramServerUser.hpp"
#include "TelegramServerClient.hpp"
#include "RemoteServerConnection.hpp"
#include "Session.hpp"

#include "CServerTcpTransport.hpp"

// Generated RPC Operation Factory includes
#include "AccountOperationFactory.hpp"
#include "AuthOperationFactory.hpp"
#include "BotsOperationFactory.hpp"
#include "ChannelsOperationFactory.hpp"
#include "ContactsOperationFactory.hpp"
#include "HelpOperationFactory.hpp"
#include "LangpackOperationFactory.hpp"
#include "MessagesOperationFactory.hpp"
#include "PaymentsOperationFactory.hpp"
#include "PhoneOperationFactory.hpp"
#include "PhotosOperationFactory.hpp"
#include "StickersOperationFactory.hpp"
#include "UpdatesOperationFactory.hpp"
#include "UploadOperationFactory.hpp"
#include "UsersOperationFactory.hpp"
// End of generated RPC Operation Factory includes

Q_LOGGING_CATEGORY(loggingCategoryServer, "telegram.server.main", QtDebugMsg)
Q_LOGGING_CATEGORY(loggingCategoryServerApi, "telegram.server.api", QtDebugMsg)

namespace Telegram {

namespace Server {

Server::Server(QObject *parent) :
    QObject(parent)
{
    m_rpcOperationFactories = {
        // Generated RPC Operation Factory initialization
        new AccountOperationFactory(),
        new AuthOperationFactory(),
        new BotsOperationFactory(),
        new ChannelsOperationFactory(),
        new ContactsOperationFactory(),
        new HelpOperationFactory(),
        new LangpackOperationFactory(),
        new MessagesOperationFactory(),
        new PaymentsOperationFactory(),
        new PhoneOperationFactory(),
        new PhotosOperationFactory(),
        new StickersOperationFactory(),
        new UpdatesOperationFactory(),
        new UploadOperationFactory(),
        new UsersOperationFactory(),
        // End of generated RPC Operation Factory initialization
    };
    m_serverSocket = new QTcpServer(this);
    connect(m_serverSocket, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

void Server::setDcOption(const DcOption &option)
{
    m_dcOption = option;
}

void Server::setServerPrivateRsaKey(const Telegram::RsaKey &key)
{
    m_key = key;
}

bool Server::start()
{
    if (!m_serverSocket->listen(QHostAddress(m_dcOption.address), m_dcOption.port)) {
        qWarning() << "Unable to listen port" << m_dcOption.port;
        return false;
    }
    qDebug() << "Start a server" << m_dcOption.id << "on" << m_dcOption.address << ":" << m_dcOption.port << "Key:" << m_key.fingerprint;
    return true;
}

void Server::loadData()
{
    const int number = 10;
    for (int i = 0; i < number; ++i) {
        User *newUser = new User(this);
        newUser->setPhoneNumber(QStringLiteral("%1").arg(i, 6, 10, QLatin1Char('0')));
        insertUser(newUser);
    }
}

void Server::setServerConfiguration(const DcConfiguration &config)
{
    m_dcConfiguration = config;
}

void Server::addServerConnection(RemoteServerConnection *remoteServer)
{
    m_remoteServers.insert(remoteServer);
}

quint32 Server::getDcIdForUserIdentifier(const QString &phoneNumber)
{
    if (m_phoneToUserId.contains(phoneNumber)) {
        return m_dcOption.id;
    }
    return 0;
}

void Server::setAuthorizationProvider(Authorization::Provider *provider)
{
    m_authProvider = provider;
}

void Server::onNewConnection()
{
    QTcpSocket *newConnection = m_serverSocket->nextPendingConnection();
    if (newConnection == nullptr) {
        qCDebug(loggingCategoryServer) << "expected pending connection does not exist";
        return;
    }
    qCDebug(loggingCategoryServer) << "A new incoming connection from" << newConnection->peerAddress().toString();
    TcpTransport *transport = new TcpTransport(newConnection, this);
    newConnection->setParent(transport);
    RemoteClientConnection *client = new RemoteClientConnection(this);
    connect(client, &BaseConnection::statusChanged, this, &Server::onClientConnectionStatusChanged);
    client->setServerRsaKey(m_key);
    client->setTransport(transport);
    client->setServerApi(this);
    client->setRpcFactories(m_rpcOperationFactories);

    m_activeConnections.insert(client);
}

void Server::onClientConnectionStatusChanged()
{
    RemoteClientConnection *client = qobject_cast<RemoteClientConnection*>(sender());
    if (client->status() == RemoteClientConnection::Status::Authenticated) {
        if (!client->session()) {

            qDebug() << Q_FUNC_INFO << "A new auth key";
        }
    } else if (client->status() == RemoteClientConnection::Status::Disconnected) {
        // TODO: Initiate session cleanup after session expiration time out
    }
}

User *Server::getLocalUser(const QString &identifier) const
{
    quint32 id = m_phoneToUserId.value(identifier);
    if (!id) {
        return nullptr;
    }
    return m_users.value(id);
}

RemoteUser *Server::getRemoteUser(const QString &identifier) const
{
    for (RemoteServerConnection *remoteServer : m_remoteServers) {
        RemoteUser *u = remoteServer->getUser(identifier);
        if (u) {
            return u;
        }
    }
    return nullptr;
}

User *Server::getUser(const QString &identifier)
{
    return getLocalUser(identifier);
}

User *Server::addUser(const QString &identifier)
{
    qDebug() << Q_FUNC_INFO << identifier;
    User *user = new User(this);
    user->setPhoneNumber(identifier);
    user->setDcId(dcId());
    insertUser(user);
    return user;
}

Session *Server::createSession(quint64 authId, const QByteArray &authKey, const QString &address)
{
    Session *session = new Session();
    session->authId = authId;
    session->authKey = authKey;
    session->ip = address;
    m_authIdToSession.insert(authId, session);
    return session;
}

Session *Server::getSessionByAuthId(quint64 authKeyId) const
{
    return m_authIdToSession.value(authKeyId);
}

void Server::insertUser(User *user)
{
    qDebug() << Q_FUNC_INFO << user << user->phoneNumber() << user->id();
    m_users.insert(user->id(), user);
    m_phoneToUserId.insert(user->phoneNumber(), user->id());
    for (Session *session : user->sessions()) {
        m_authIdToSession.insert(session->authId, session);
    }
}

PhoneStatus Server::getPhoneStatus(const QString &identifier) const
{
    PhoneStatus result;
    RemoteUser *user = getLocalOrRemoteUser(identifier);
    if (user) {
        result.online = user->isOnline();
        result.dcId = user->dcId();
    }
    return result;
}

PasswordInfo Server::getPassword(const QString &identifier)
{
    PasswordInfo result;
    User *user = getUser(identifier);
    if (user && user->hasPassword()) {
        result.currentSalt = user->passwordSalt();
        result.hint = user->passwordHint();
    }
    return result;
}

bool Server::checkPassword(const QString &identifier, const QByteArray &hash)
{
    User *user = getUser(identifier);
    if (user && user->hasPassword()) {
        return user->passwordHash() == hash;
    }
    return false;

}

bool Server::identifierIsValid(const QString &identifier)
{
    const bool result = identifier.length() > 4;
    qCDebug(loggingCategoryServerApi) << "identifierIsValid(" << identifier << "):" << result;
    return result;
}

RemoteUser *Server::getLocalOrRemoteUser(const QString &identifier) const
{
    RemoteUser *user = getLocalUser(identifier);
    if (!user) {
        user = getRemoteUser(identifier);
    }
    return user;
}

} // Server

} // Telegram
