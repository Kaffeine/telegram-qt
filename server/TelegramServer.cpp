#include "TelegramServer.hpp"

#include "ApiUtils.hpp"
#include "AuthService.hpp"
#include "Debug_p.hpp"
#include "MediaService.hpp"
#include "MessageService.hpp"
#include "PendingVariant.hpp"
#include "RandomGenerator.hpp"
#include "RemoteClientConnection.hpp"
#include "RemoteServerConnection.hpp"
#include "ServerDhLayer.hpp"
#include "ServerMessageData.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerTcpTransport.hpp"
#include "ServerUtils.hpp"
#include "Session.hpp"
#include "TelegramServerUser.hpp"
#include "GroupChat.hpp"

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

#include "telegramqt_macros.h"

#include <QLoggingCategory>
#include <QTcpServer>
#include <QTcpSocket>

Q_LOGGING_CATEGORY(loggingCategoryServer, "telegram.server.main", QtInfoMsg)
Q_LOGGING_CATEGORY(loggingCategoryServerApi, "telegram.server.api", QtWarningMsg)
Q_LOGGING_CATEGORY(lcServerUpdates, "telegram.server.updates", QtInfoMsg)
Q_LOGGING_CATEGORY(lcServerCrossUpdates, "telegram.server.cross.updates", QtInfoMsg)

namespace Telegram {

static constexpr int ExportedAuthorizationKeySize = 128;

namespace Server {

Server::Server(QObject *parent) :
    QObject(parent)
{
    m_authService = new AuthService(this);
    m_mediaService = new MediaService(this);
    m_mediaServiceIface = m_mediaService;

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

Server::~Server()
{
    qDeleteAll(m_authorizedUsers);
    qDeleteAll(m_sessions);
    qDeleteAll(m_users);
    qDeleteAll(m_rpcOperationFactories);
}

void Server::setListenAddress(const QHostAddress &address)
{
    m_listenAddress = address;
}

void Server::setDcOption(const DcOption &option)
{
    m_dcOption = option;
    setObjectName(QStringLiteral("Server(dc%1)").arg(dcId()));

    m_mediaService->setDcId(option.id);
}

void Server::setServerPrivateRsaKey(const Telegram::RsaKey &key)
{
    m_key = key;
}

bool Server::start()
{
    if (!m_dcOption.id) {
        qCCritical(loggingCategoryServer).noquote().nospace() << "Unable to start server: Invalid (null) DC id.";
        return false;
    }

    QHostAddress address = m_listenAddress;
    if (address.isNull()) {
        address = QHostAddress(m_dcOption.address);
    }

    if (!m_serverSocket->listen(address, m_dcOption.port)) {
        qCCritical(loggingCategoryServer).noquote().nospace() << "Unable to listen port " << m_dcOption.port
                                                              << " ("  << m_serverSocket->serverError() << ")";
        return false;
    }
    qCInfo(loggingCategoryServer).nospace().noquote() << "Start server (DC " << m_dcOption.id << ") "
                                                      << m_dcOption.address << ":" << m_dcOption.port
                                                      << " (listening " << m_serverSocket->serverAddress().toString()
                                                      << ":" << m_serverSocket->serverPort() << ")"
                                                      << TELEGRAMQT_HEX_SHOWBASE
                                                      << "; Key:" << m_key.fingerprint;
    return true;
}

void Server::stop()
{
    qCInfo(loggingCategoryServer).nospace().noquote() << "Stop server (DC " << m_dcOption.id << ") "
                                                      << "on " << m_dcOption.address << ":" << m_dcOption.port;
    if (m_serverSocket) {
        m_serverSocket->close();
    }

    // Connections removed from the set on disconnected.
    // Copy connections to a variable to iterate over a constant container instead of
    // (virtually) simultanously mutated member variable.
    QSet<RemoteClientConnection*> activeConnections = m_activeConnections;
    for (RemoteClientConnection *client : activeConnections) {
        client->transport()->disconnectFromHost();
    }
}

void Server::loadData()
{
    const int number = 10;
    for (int i = 0; i < number; ++i) {
        LocalUser *newUser = new LocalUser();
        newUser->setPhoneNumber(QStringLiteral("%1").arg(i, 6, 10, QLatin1Char('0')));
        insertUser(newUser);
    }
}

void Server::setServerConfiguration(const DcConfiguration &config)
{
    m_dcConfiguration = config;
}

void Server::addServerConnection(AbstractServerConnection *remoteServer)
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
    m_authService->setAuthorizationProvider(provider);
}

void Server::setMessageService(MessageService *storage)
{
    m_messageService = storage;
}

void Server::onNewConnection()
{
    QTcpSocket *socket = m_serverSocket->nextPendingConnection();
    if (!socket) {
        qCDebug(loggingCategoryServer) << "expected pending connection does not exist";
        return;
    }
    TcpTransport *transport = new TcpTransport(socket, this);
    socket->setParent(transport);
    RemoteClientConnection *client = new RemoteClientConnection(this);
    const QString address = transport->remoteAddress();
    qCInfo(loggingCategoryServer) << CALL_INFO << client;
    client->setObjectName(QStringLiteral("cli %1 on dc%2").arg(address).arg(dcId()));
    connect(client, &BaseConnection::statusChanged, this, &Server::onClientConnectionStatusChanged);
    client->setServerRsaKey(m_key);
    client->setTransport(transport);
    client->setServerApi(this);
    client->setRpcFactories(m_rpcOperationFactories);

    m_activeConnections.insert(client);
}

Session *Server::addSession(quint64 sessionId)
{
    Session *session = new Session(sessionId);
    m_sessions.insert(sessionId, session);
    return session;
}

void Server::onClientConnectionStatusChanged()
{
    RemoteClientConnection *client = qobject_cast<RemoteClientConnection*>(sender());
    if (client->status() == RemoteClientConnection::Status::HasDhKey) {
        if (!client->session()) {
            m_authService->registerAuthKey(client->authId(), client->authKey());
            qCDebug(loggingCategoryServer) << Q_FUNC_INFO << "Connected a client with a new auth key"
                                              << "from" << client->transport()->remoteAddress();
        }
    } else if (client->status() == RemoteClientConnection::Status::Disconnected) {
        if (client->session()) {
            qCInfo(loggingCategoryServer) << this << __func__ << "Disconnected a client with session id"
                                          << TELEGRAMQT_HEX_SHOWBASE << client->session()->id()
                                          << "from" << client->transport()->remoteAddress();
            setSessionConnection(client->session(), nullptr);
            // Update session 'last seen' timestamp on disconnect
            client->session()->timestamp = Telegram::Utils::getCurrentTime();
        } else {
            qCInfo(loggingCategoryServer) << this << __func__ << "Disconnected a client without a session"
                                          << "from" << client->transport()->remoteAddress();
        }
        // TODO: Initiate session cleanup after session expiration time out
        m_activeConnections.remove(client);
        client->deleteLater();
    }
}

void Server::onUserSessionStatusChanged(LocalUser *user, Session *session)
{
    if (session->isActive()) {
        // The user become online
        // Wait for account.updateStatus API call
    } else if (!user->hasActiveSession()) {
        // The user has no connected devices.
        // Definitely offline.
        if (user->isOnline()) {
            setUserOnline(user, false);
        }
    }
}

void Server::reportLocalMessageRead(LocalUser *user, const UpdateNotification &notification)
{
    UserDialog *senderDialog = user->getDialog(notification.dialogPeer);

    if (senderDialog->readOutboxMaxId >= notification.messageId) {
        return;
    }

    // Outbox is actually updated, so bump PTS and generate an update
    senderDialog->readOutboxMaxId = notification.messageId;
    user->getPostBox()->bumpPts();

    if (user->hasActiveSession()) {
        UpdateNotification userNotification = notification;
        userNotification.pts = user->getPostBox()->pts();
        queueUpdates({userNotification});
    }
}

void Server::setSessionConnection(Session *session, RemoteClientConnection *connection)
{
    session->setConnection(connection);

    if (session->userId()) {
        LocalUser *localUser = getUser(session->userId());
        if (localUser) {
            // It is OK to have no local user
            // because we have sessions for imported authorizations as well.
            onUserSessionStatusChanged(localUser, session);
        }
    }
}

Peer Server::getPeer(const TLInputPeer &peer, const LocalUser *applicant) const
{
    switch (peer.tlType) {
    case TLValue::InputPeerEmpty:
        return Peer();
    case TLValue::InputPeerSelf:
        return Peer::fromUserId(applicant->id());
    case TLValue::InputPeerChat:
        return Peer::fromChatId(peer.chatId);
    case TLValue::InputPeerUser:
        return Peer::fromUserId(peer.userId);
    case TLValue::InputPeerChannel:
        return Peer::fromChannelId(peer.channelId);
    default:
        qCWarning(loggingCategoryServerApi) << this << __func__ << "Invalid input peer type" << peer.tlType;
        return Peer();
    };
}

MessageRecipient *Server::getRecipient(const TLInputPeer &peer, const LocalUser *applicant) const
{
    switch (peer.tlType) {
    case TLValue::InputPeerEmpty:
        return nullptr;
    case TLValue::InputPeerSelf:
        return getAbstractUser(applicant->id());
    case TLValue::InputPeerUser:
        return getAbstractUser(peer.userId);
    case TLValue::InputPeerChat: {
        GroupChat *chat = getGroupChat(peer.chatId);
        if (!chat->memberIds().contains(applicant->userId())) {
            // The applicant is not a member of the requested chat
            return nullptr;
        }
        return chat;
    }
    case TLValue::InputPeerChannel:
        //recipient = api()->getChannel(peer.channelId, peer.accessHash);
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

MessageRecipient *Server::getRecipient(const Peer &peer) const
{
    if (!peer.isValid()) {
        return nullptr;
    }
    switch (peer.type()) {
    case Peer::User:
        return getAbstractUser(peer.id());
    case Peer::Chat:
        return getGroupChat(peer.id());
    default:
        return nullptr;
    }
}

// Returns the list of Users who interesting in the peer info updates
QVector<quint32> Server::getPeerWatchers(const Peer &peer) const
{
    QVector<quint32> watchers;
    if (peer.type() == Peer::User) {
        const LocalUser *localUser = getUser(peer.id());
        if (localUser) {
            const QVector<UserDialog *> dialogs = localUser->dialogs();
            for (const UserDialog *dialog : dialogs) {
                if (!dialog->peer.isValid()) {
                    // Sanity check was failed.
                    continue;
                }
                if (dialog->peer.type() == Peer::User) {
                    watchers.append(dialog->peer.id());
                }
            }
        }
        const AbstractUser *user = localUser ? localUser : getAbstractUser(peer.id());
        const QVector<quint32> contactList = user->contactList();
        for (const quint32 contactId : contactList) {
            if (watchers.contains(contactId)) {
                continue;
            }
            watchers.append(contactId);
        }

        // Any user is interesting in themself
        if (!watchers.contains(peer.id())) {
            watchers << peer.id();
        }
    }

    return watchers;
}

LocalUser *Server::getUser(const QString &identifier) const
{
    const quint32 id = m_phoneToUserId.value(identifier);
    if (!id) {
        return nullptr;
    }
    return m_users.value(id);
}

LocalUser *Server::getUser(quint32 userId) const
{
    return m_users.value(userId);
}

Peer Server::getPeerByUserName(const QString &userName) const
{
    quint32 userId = m_usernameToUserId.value(userName);
    if (userId) {
        return Peer::fromUserId(userId);
    }
    return Peer();
}

AbstractUser *Server::getAbstractUser(const TLInputUser &inputUser, const LocalUser *applicant) const
{
    switch (inputUser.tlType) {
    case TLValue::InputUserSelf:
        return getUser(applicant->userId());
    case TLValue::InputUser:
        return getAbstractUser(inputUser.userId, inputUser.accessHash, applicant);
    case TLValue::InputUserEmpty:
        return nullptr;
    default:
        return nullptr;
    }
}

AbstractUser *Server::getAbstractUser(quint32 userId, quint64 accessHash, const LocalUser *applicant) const
{
    AbstractUser *u = getAbstractUser(userId);
    // TODO: Check access hash
    return u;
}

LocalUser *Server::addUser(const QString &identifier)
{
    qCDebug(loggingCategoryServerApi) << Q_FUNC_INFO << identifier;
    AbstractUser *existsUser = getAbstractUser(identifier);
    if (existsUser) {
        qCDebug(loggingCategoryServerApi) << CALL_INFO << "Unable to add user"
                                          << identifier << "(the identifier is already taken)"
                                          << "by user id" << existsUser->id();
        return nullptr;
    }

    LocalUser *user = new LocalUser();
    user->setPhoneNumber(identifier);
    user->setDcId(dcId());
    insertUser(user);
    return user;
}

bool Server::bindClientConnectionSession(RemoteClientConnection *connection, quint64 sessionId)
{
    Session *session = getSessionById(sessionId);
    const quint32 userId = m_authService->getUserIdByAuthId(connection->authId());
    LocalUser *localUser = userId ? getUser(userId) : nullptr;

    if (!session) {
        session = addSession(sessionId);
        session->ip = connection->transport()->remoteAddress();

        if (connection->dhLayer()->state() == DhLayer::State::HasKey) {
            session->setInitialServerSalt(connection->dhLayer()->serverSalt());
        } else {
            session->generateInitialServerSalt();
        }

        if (localUser) {
            localUser->addSession(session);
        }
    }

    connection->setSession(session);
    setSessionConnection(session, connection);

    return true;
}

Session *Server::getSessionById(quint64 sessionId) const
{
    return m_sessions.value(sessionId);
}

void Server::bindUserSession(AuthorizedUser *user, Session *session)
{
    user->addSession(session);
    if (session->isActive()) {
        m_authService->addUserAuthorization(user, session->getConnection()->authId());
    }
}

bool Server::usernameIsValid(const QString &username) const
{
    static constexpr int MinimumUsernameLength = 5;
    static constexpr int MaximumUsernameLength = 32;
    // Length: 5-32 characters.
    if ((username.length() < MinimumUsernameLength) || (username.length() > MaximumUsernameLength)) {
        return false;
    }
    // Accepted characters: A-z (case-insensitive), 0-9 and underscores.
    // Only single underscore
    return true;
}

bool Server::setUserName(LocalUser *user, const QString &newUsername, RpcError *error)
{
    if (user->userName() == newUsername) {
        if (error) {
            error->setReason(RpcError::UsernameNotModified);
        }
        return true;
    }
    const Peer p = getPeerByUserName(newUsername);
    if (p.isValid()) {
        if (error) {
            error->setReason(RpcError::UsernameOccupied);
        }
        return false;
    }
    const QString previousName = user->userName();
    if (!newUsername.isEmpty()) {
        m_usernameToUserId.insert(newUsername, user->id());
    }
    user->setUserName(newUsername);
    m_usernameToUserId.remove(previousName);
    if (error) {
        error->unset();
    }
    return true;
}

// Returns true is the status changed.
bool Server::setUserOnline(LocalUser *user, bool online, Session *fromSession)
{
    quint32 date = Telegram::Utils::getCurrentTime();
    const bool wasOnline = user->onlineTimestamp() > date;
    if (online) {
        date += m_dcConfiguration.onlineCloudTimeoutMs / 1000;
    }
    user->setOnlineTimestamp(date);
    if (online == wasOnline) {
        return false;
    }

    const QVector<UpdateNotification> notifications = createUpdates(UpdateNotification::Type::UpdateUserStatus,
                                             user, fromSession);
    routeUpdates(notifications);

    return true;
}

GroupChat *Server::createChat(LocalUser *user, const QString &title, const QVector<quint32> &members)
{
    const quint32 date = Telegram::Utils::getCurrentTime();
    const quint32 chatId = generateChatId();
    LocalGroupChat *groupChat = new LocalGroupChat(chatId, dcId());
    groupChat->setCreator(user->id());
    groupChat->setTitle(title);
    groupChat->inviteMembers(members, user->id(), date);
    groupChat->setDate(date);

    insertGroup(groupChat);

    return groupChat;
}

PendingOperation *Server::exportAuthorization(quint32 dcId, quint32 userId, QByteArray *outputAuthBytes)
{
    if (dcId == m_dcOption.id) {
        return PendingOperation::failOperation(QLatin1String("Invalid request: this DC is the target one"));
    }

    AbstractServerConnection *targetDc = getRemoteServer(dcId);
    if (!targetDc) {
        return PendingOperation::failOperation(QLatin1String("Target DC is not available"));
    }

    *outputAuthBytes = targetDc->getForeingUserAuthorization(userId);
    if (outputAuthBytes->isEmpty()) {
        return PendingOperation::failOperation(QLatin1String("Target DC can not authorize the user"));
    }

    PendingOperation *operation = new PendingOperation(this);
    operation->setObjectName(QStringLiteral("ExportAuthOperation(user%1 from %2 to %3)")
                             .arg(userId).arg(m_dcOption.id).arg(dcId));
    operation->finishLater();
    return operation;
}

QByteArray Server::generateExportedAuthorization(quint32 userId)
{
    QByteArray bytes = RandomGenerator::instance()->generate(ExportedAuthorizationKeySize);
    m_exportedAuthorizations.insert(userId, bytes);
    return bytes;
}

AuthorizedUser *Server::getAuthorizedUser(quint32 userId, const QByteArray &authBytes)
{
    if (!userId || authBytes.isEmpty()) {
        return nullptr;
    }
    if (!m_exportedAuthorizations.values(userId).contains(authBytes)) {
        return nullptr;
    }
    if (!m_authorizedUsers.contains(userId)) {
        AbstractUser *originUser = getRemoteUser(userId);
        // Use LocalUser for now
        AuthorizedUser *newUser = new LocalUser(userId, originUser->phoneNumber());
        newUser->setDcId(originUser->dcId());

        m_authorizedUsers.insert(userId, newUser);
    }
    return m_authorizedUsers.value(userId);
}

PendingOperation *Server::searchContacts(const QString &query, quint32 limit, QVector<Peer> *output)
{
    PendingOperation *operation = new PendingOperation(this);
    operation->setObjectName(QStringLiteral("searchContacts(query: %1, limit: %2)")
                             .arg(query).arg(limit));

    const QString scheme = query.section(QLatin1Char(':'), 0, 0);

    for (AbstractServerConnection *server : m_remoteServers) {
        if (server->supportedSchemes().contains(scheme)) {
            PendingVariant *foreingRequest = server->searchContacts(query, limit);
            connect(foreingRequest, &PendingVariant::finished, this, [operation, foreingRequest, output]() {
                if (!foreingRequest->isSucceeded()) {
                    qWarning() << "Search op failed" << foreingRequest->errorDetails();

                    operation->finishLater();
                    return;
                }

                const QVariant result = foreingRequest->result();
                if (!result.isNull()) {
                    PeerList peers = result.value<PeerList>();
                    output->append(peers);
                }
                operation->finishLater();
            });

            return operation;
        }
    }

    const Peer peer = getPeerByUserName(query);
    if (peer.isValid()) {
        output->append(peer);
    }

    operation->finishLater();

    return operation;
}

void Server::reportMessageRead(const MessageData *messageData)
{
    const Peer senderPostBoxPeer = messageData->fromId()
            ? Peer::fromUserId(messageData->fromId())
            : messageData->toPeer();
    const quint32 senderMessageId = messageData->getReference(senderPostBoxPeer);

    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    UpdateNotification notification;
    notification.userId = messageData->fromId();
    notification.type = UpdateNotification::Type::ReadOutbox;
    notification.date = requestDate;
    notification.messageId = senderMessageId;
    notification.dialogPeer = messageData->toPeer();

    // The sender is Remote User
    AbstractUser *remoteUser = getAbstractUser(messageData->fromId());
    if (remoteUser->dcId() != dcId()) {
        AbstractServerConnection *remoteServerConnection = getRemoteServer(remoteUser->dcId());
        AbstractServerApi *remoteApi = remoteServerConnection->api();
        remoteApi->queueServerUpdates({notification});
        return;
    }

    // The sender is Local User
    LocalUser *messageSender = getUser(notification.userId);
    reportLocalMessageRead(messageSender, notification);
}

// Return updates for the chat creator
QVector<UpdateNotification> Server::announceNewChat(const Peer &peer, Session *excludeSession)
{
    if (peer.type() != Peer::Chat) {
        return { };
    }

    const GroupChat *groupChat = getGroupChat(peer.id());

    ServiceMessageAction serviceAction;
    serviceAction.type = ServiceMessageAction::Type::ChatCreate;
    serviceAction.title = groupChat->title();
    serviceAction.users = groupChat->memberIds();

    MessageData *messageData = messageService()->addServiceMessage(groupChat->creatorId(), peer, serviceAction);
    messageData->setDate(groupChat->date());

    UpdateNotification notification;
    notification.type = UpdateNotification::Type::CreateChat;
    notification.date = groupChat->date();
    notification.dcId = groupChat->dcId();
    notification.messageDataId = messageData->globalId();
    notification.excludeSession = excludeSession;
    notification.dialogPeer = peer;

    QVector<UpdateNotification> notificationsForCreator;
    QVector<quint32> notifiedDCs;
    for (const ChatMember &member : groupChat->members()) {
        AbstractUser *user = getAbstractUser(member.userId);
        notification.userId = member.userId;

        if (user->dcId() == dcId()) {
            // Local update
            QVector<UpdateNotification> notifications = processServerUpdates({notification});
            queueUpdates(notifications);
            if (member.role == ChatMember::Role::Creator) {
                notificationsForCreator = notifications;
            }
        } else {
            if (notifiedDCs.contains(user->dcId())) {
                continue;
            }

            notifiedDCs.append(user->dcId());

            // Remote update
            AbstractServerConnection *remote = getRemoteServer(user->dcId());
            if (!remote) {
                continue;
            }

            remote->api()->queueServerUpdates({notification});
        }
    }

    return notificationsForCreator;
}

/*
    Process the message data, deliver the message to all recipients, add
    the new message to dialogs and generate UpdateNotification list.

    The sender notification (if any) will be the first one in the result list.
 */
QVector<UpdateNotification> Server::processMessage(MessageData *messageData, Session *excludeSession)
{
    const Peer targetPeer = messageData->toPeer();
    AbstractUser *fromUser = getAbstractUser(messageData->fromId());
    QVector<PostBox *> boxes = getPostBoxes(targetPeer, fromUser);
    QVector<UpdateNotification> notifications;
    QVector<quint32> notifiedDCs;

    // Result and broadcasted Updates date seems to be always older than the message date,
    // so prepare the request date right on the start.
    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    for (PostBox *box : boxes) {
        UpdateNotification notification;
        notification.type = UpdateNotification::Type::NewMessage;
        notification.date = requestDate;
        notification.messageDataId = messageData->globalId();

        if (isLocalBox(box)) {
            const quint32 newMessageId = box->addMessage(notification.messageDataId);
            messageService()->addMessageReference(notification.messageDataId, box->peer(), newMessageId);
            notification.messageId = newMessageId;
            notification.pts = box->pts();
        }

        for (const quint32 userId : box->users()) {
            // Box users:
            // single user in User boxes
            // a lot of users in Channel boxes
            notification.userId = userId;
            if (targetPeer.type() == Peer::User) {
                if (userId == fromUser->id()) {
                    notification.dialogPeer = targetPeer;
                } else {
                    notification.dialogPeer = fromUser->toPeer();
                }
            } else {
                notification.dialogPeer = targetPeer;
            }

            LocalUser *user = getUser(userId);
            if (user) {
                user->addNewMessage(notification.dialogPeer, notification.messageId, notification.messageDataId);

                if (user == fromUser) {
                    UserDialog *dialog = user->getDialog(notification.dialogPeer);
                    dialog->readInboxMaxId = notification.messageId;
                } else {
                    user->bumpDialogUnreadCount(notification.dialogPeer);
                }

                if (user->userId() == messageData->fromId()) {
                    // Notifications for the sender
                    notification.excludeSession = excludeSession;
                    notifications = { notification };
                    queueUpdates({notification});
                    notification.excludeSession = nullptr;
                } else {
                    queueUpdates({notification});
                }
            } else {
                // User is not a local user
                AbstractUser *remoteUser = getRemoteUser(userId);
                if (!remoteUser) {
                    qCWarning(loggingCategoryServerApi) << CALL_INFO
                                                        << "Invalid userId"
                                                        << userId;
                    continue;
                }
                if (notifiedDCs.contains(remoteUser->dcId())) {
                    continue;
                }
                notifiedDCs.append(remoteUser->dcId());
                notification.userId = 0;

                AbstractServerConnection *remoteServerConnection = getRemoteServer(remoteUser->dcId());
                AbstractServerApi *remoteApi = remoteServerConnection->api();
                // if (!remoteApi->messageService()->hasMessage()) {
                //     remoteApi->messageService()->importMessage(messageData)
                // }
                remoteApi->queueServerUpdates({notification});
            }
        }
    }

    return notifications;
}

QVector<UpdateNotification> Server::processMessageEdit(MessageData *messageData)
{
    const Peer targetPeer = messageData->toPeer();
    AbstractUser *fromUser = getUser(messageData->fromId());
    QVector<PostBox *> boxes = getPostBoxes(targetPeer, fromUser);
    if ((targetPeer.type() == Peer::User) && !messageData->isMessageToSelf()) {
        boxes.append(fromUser->getPostBox());
    }
    // Boxes:
    // message to contact
    //    Users (self and recipient (if not self))
    //
    // message to group chat
    //    Users (each member)
    //
    // message to megagroup or broadcast
    //    Channel (the channel)

    QVector<UpdateNotification> notifications;
    QVector<quint32> notifiedDCs;

    // Result and broadcasted Updates date seems to be always older than the message date,
    // so prepare the request date right on the start.
    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    for (PostBox *box : boxes) {
        box->bumpPts();
        const quint32 messageId = messageData->getReference(box->peer());
        UpdateNotification notification;
        notification.type = UpdateNotification::Type::EditMessage;
        notification.date = requestDate;
        notification.messageId = messageId;
        notification.pts = box->pts();
        for (const quint32 userId : box->users()) {
            notification.userId = userId;
            if (targetPeer.type() == Peer::User) {
                if (userId == fromUser->id()) {
                    notification.dialogPeer = targetPeer;
                } else {
                    notification.dialogPeer = fromUser->toPeer();
                }
            } else {
                notification.dialogPeer = targetPeer;
            }
            LocalUser *user = getUser(userId);
            if (!user) {
                // User is not a local user
                AbstractUser *remoteUser = getRemoteUser(userId);
                if (!remoteUser) {
                    qCWarning(loggingCategoryServerApi) << CALL_INFO
                                                        << "Invalid userId"
                                                        << userId;
                    continue;
                }
                if (notifiedDCs.contains(remoteUser->dcId())) {
                    continue;
                }
                notifiedDCs.append(remoteUser->dcId());
                notification.userId = 0;

                AbstractServerConnection *remoteServerConnection = getRemoteServer(remoteUser->dcId());
                AbstractServerApi *remoteApi = remoteServerConnection->api();
                // if (!remoteApi->messageService()->hasMessage()) {
                //     remoteApi->messageService()->importMessage(messageData)
                // }
                remoteApi->queueServerUpdates({notification});
                continue;
            }

            if ((userId == fromUser->id()) && !notifications.isEmpty()) {
                // Keep the sender Notification on the first place
                notifications.append(notifications.constFirst());
                notifications.first() = notification;
                continue;
            }

            notifications.append(notification);
        }
    }

    return notifications;
}

void Server::processUserMessageAction(const Peer &targetPeer,
                                      LocalUser *applicant,
                                      Telegram::MessageAction messageAction,
                                      Session *excludeSession)
{
    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    const QVector<PostBox *> boxes = getPostBoxes(targetPeer, applicant);

    for (PostBox *box : boxes) {
        UpdateNotification notification;
        notification.type = UpdateNotification::Type::MessageAction;
        notification.date = requestDate;
        notification.fromId = applicant->id();
        notification.messageAction = messageAction;

        for (const quint32 userId : box->users()) {
            // The Update recipient
            notification.userId = userId;
            if (targetPeer.type() == Peer::User) {
                if (userId == applicant->id()) {
                    notification.dialogPeer = targetPeer;
                } else {
                    notification.dialogPeer = applicant->toPeer();
                }
            } else {
                notification.dialogPeer = targetPeer;
            }

            if (userId == applicant->id()) {
                notification.excludeSession = excludeSession;
            }

            AbstractUser *user = getAbstractUser(userId);
            if (user->dcId() == dcId()) {
                queueServerUpdates({notification});
            } else {
                AbstractServerConnection *remoteServerConnection = getRemoteServer(user->dcId());
                AbstractServerApi *remoteApi = remoteServerConnection->api();
                remoteApi->queueServerUpdates({notification});
            }
        }
    }
}

QVector<UpdateNotification> Server::createUpdates(UpdateNotification::Type updateType,
                                                  LocalUser *applicant,
                                                  Session *excludeSession) const
{
    QVector<UpdateNotification> notifications;
    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    const QVector<quint32> watchers = getPeerWatchers(applicant->toPeer());

    UpdateNotification notification;

    switch (updateType) {
    case UpdateNotification::Type::UpdateName:
        notification.type = updateType;
        notification.date = requestDate;
        notification.fromId = applicant->id();
        break;
    case UpdateNotification::Type::UpdateUserStatus:
        notification.type = updateType;
        notification.date = requestDate;
        notification.fromId = applicant->id();
        break;
    default:
        return { };
    }

    for (const quint32 userId : watchers) {
        notification.userId = userId;
        notifications.append(notification);
    }

    UpdateNotification *selfNotification = nullptr;
    for (UpdateNotification &notification : notifications) {
        if (notification.userId == applicant->id()) {
            selfNotification = &notification;
            break;
        }
    }
    if (selfNotification) {
        selfNotification->excludeSession = excludeSession;
    }

    return notifications;
}

AbstractUser *Server::importUserContact(LocalUser *user, const UserContact &contact)
{
    UserContact userContact = contact;
    AbstractUser *registeredUser = getAbstractUser(contact.phone);
    if (registeredUser) {
        userContact.id = registeredUser->id();
    }
    user->importContact(userContact);

    return registeredUser;
}

bool Server::bakeUpdate(TLUpdate *update, const UpdateNotification &notification, QSet<Peer> *interestingPeers) const
{
    LocalUser *recipient = getUser(notification.userId);
    AbstractUser *interestingUser = nullptr;
    if (!recipient) {
        qCWarning(lcServerUpdates) << CALL_INFO << "Invalid user!" << notification.userId;
        return false;
    }

    switch (notification.type) {
    case UpdateNotification::Type::ChatParticipants:
    {
        // This implementation is weak to race conditions.
        // The right way is to get all update data from the notification
        quint32 chatId = notification.dialogPeer.id();
        GroupChat *groupChat = getGroupChat(chatId);
        if (!groupChat) {
            return false;
        }

        update->tlType = TLValue::UpdateChatParticipants;
        Utils::setupTLChatParticipants(&update->participants, groupChat, nullptr);
    }
        break;
    case UpdateNotification::Type::NewMessage:
    case UpdateNotification::Type::EditMessage:
    {
        const quint64 globalMessageId = recipient->getPostBox()->getMessageGlobalId(notification.messageId);
        const MessageData *messageData = messageService()->getMessage(globalMessageId);

        if (!messageData) {
            qCWarning(lcServerUpdates) << CALL_INFO << "no message";
            return false;
        }

        if (notification.type == UpdateNotification::Type::NewMessage) {
            if (messageData->toPeer().type() == Peer::Channel) {
                update->tlType = TLValue::UpdateNewChannelMessage;
            } else {
                update->tlType = TLValue::UpdateNewMessage;
            }
        } else if (notification.type == UpdateNotification::Type::EditMessage) {
            if (messageData->toPeer().type() == Peer::Channel) {
                update->tlType = TLValue::UpdateEditChannelMessage;
            } else {
                update->tlType = TLValue::UpdateEditMessage;
            }
        } else {
            qCWarning(lcServerUpdates) << CALL_INFO << "unexpected notification type";
            return false;
        }

        Utils::setupTLMessage(&update->message, messageData, notification.messageId, recipient);
        update->pts = notification.pts;
        update->ptsCount = 1;

        interestingPeers->insert(messageData->toPeer());
        if (update->message.fromId) {
            interestingPeers->insert(Peer::fromUserId(update->message.fromId));
        }

        if (messageData->isServiceMessage()) {
            for (const Peer &peer : messageData->action().getPeers()) {
                interestingPeers->insert(peer);
            }
        }
    }
        break;
    case UpdateNotification::Type::MessageAction:
    {
        switch (notification.dialogPeer.type()) {
        case Peer::User:
            update->tlType = TLValue::UpdateUserTyping;
            break;
        case Peer::Chat:
            update->tlType = TLValue::UpdateChatUserTyping;
            update->chatId = notification.dialogPeer.id();
            break;
        case Peer::Channel:
            // Invalid peer
            break;
        }
        update->userId = notification.fromId;
        // Note: action depends on Layer. Process this to support different layers.
        update->action = Telegram::Utils::toTL(notification.messageAction);
    }
        break;
    case UpdateNotification::Type::ReadInbox:
    case UpdateNotification::Type::ReadOutbox:
    {
        update->tlType = notification.type == UpdateNotification::Type::ReadInbox
                  ? TLValue::UpdateReadHistoryInbox
                  : TLValue::UpdateReadHistoryOutbox;
        update->pts = notification.pts;
        update->ptsCount = 1;
        update->peer = Telegram::Utils::toTLPeer(notification.dialogPeer);
        update->maxId = notification.messageId;
    }
        break;
    case UpdateNotification::Type::UpdateName:
    {
        update->tlType = TLValue::UpdateUserName;
        update->userId = notification.fromId;

        if (!interestingUser || (interestingUser->id() != update->userId)) {
            interestingUser = getAbstractUser(update->userId);
            if (!interestingUser) {
                qCWarning(lcServerUpdates) << CALL_INFO
                                           << "Invalid interesting user" << notification.userId
                                           << "for update" << notification.type;
                return false;
            }
        }

        update->firstName = interestingUser->firstName();
        update->lastName = interestingUser->lastName();
        update->username = interestingUser->userName();
    }
        break;
    case UpdateNotification::Type::UpdateUserStatus:
    {
        update->tlType = TLValue::UpdateUserStatus;
        update->userId = notification.fromId;

        if (!interestingUser || (interestingUser->id() != notification.userId)) {
            interestingUser = getAbstractUser(update->userId);
            if (!interestingUser) {
                qCWarning(lcServerUpdates) << CALL_INFO
                                           << "Invalid interesting user" << notification.userId
                                           << "for update" << notification.type;
                return false;
            }
        }

        Utils::setupTLUserStatus(&update->status, interestingUser, recipient);
    }
        break;
    case UpdateNotification::Type::CreateChat:
    case UpdateNotification::Type::Invalid:
        return false;
    }

    return true;
}

void Server::queueUpdates(const QVector<UpdateNotification> &notifications)
{
    QVector<UpdateNotification> holdedUpdates;
    for (const UpdateNotification &notification : notifications) {
        if (notification.joinWithNext) {
            holdedUpdates.append(notification);
            continue;
        }

        QSet<Peer> interestingPeers;

        TLUpdates updates;
        LocalUser *recipient = getUser(notification.userId);
        if (!recipient) {
            qCWarning(lcServerUpdates) << CALL_INFO << "Invalid user!" << notification.userId;
            continue;
        }

        updates.date = notification.date;

        if (holdedUpdates.isEmpty()) {
            switch (notification.type) {
            case UpdateNotification::Type::EditMessage:
            case UpdateNotification::Type::NewMessage:
            case UpdateNotification::Type::ReadInbox:
            case UpdateNotification::Type::ReadOutbox:
            case UpdateNotification::Type::ChatParticipants:
                updates.tlType = TLValue::Updates;
                updates.updates.resize(1);
                if (!bakeUpdate(&updates.updates[0], notification, &interestingPeers)) {
                    qCWarning(lcServerUpdates) << CALL_INFO << "Unable to prepare update";
                    continue; // Omit the notification
                }
                break;
            case UpdateNotification::Type::MessageAction:
            case UpdateNotification::Type::UpdateName:
            case UpdateNotification::Type::UpdateUserStatus:
                updates.tlType = TLValue::UpdateShort;
                if (!bakeUpdate(&updates.update, notification, &interestingPeers)) {
                    qCWarning(lcServerUpdates) << CALL_INFO << "Unable to prepare update";
                    continue; // Omit the notification
                }

                // bakeUpdate modified the updates.update object inplace
                break;
            case UpdateNotification::Type::CreateChat:
                // This update should never occure in this switch.
                // It is split to ChatParticipants and NewMessage instead.
            case UpdateNotification::Type::Invalid:
                break;
            }
        } else {
            // If holdedUpdates already had something...
            holdedUpdates.append(notification);

            updates.tlType = TLValue::Updates;
            updates.updates.resize(holdedUpdates.count());
            for (int i = 0; i < holdedUpdates.count(); ++i) {
                const UpdateNotification &update = holdedUpdates[i];
                if (!bakeUpdate(&updates.updates[i], update, &interestingPeers)) {
                    qCWarning(lcServerUpdates) << CALL_INFO << "Unable to prepare update";
                    continue;
                }
            }
            holdedUpdates.clear();
        }

        switch (updates.tlType) {
        case TLValue::UpdatesCombined:
        case TLValue::Updates:
            Utils::setupTLPeers(&updates, interestingPeers, this, recipient);
            break;
        default:
            break;
        }

        for (Session *session : recipient->activeSessions()) {
            if (session == notification.excludeSession) {
                continue;
            }
            session->getConnection()->rpcLayer()->sendUpdates(updates);
        }
    }
}

void Server::queueServerUpdates(const QVector<UpdateNotification> &notificationsForServer)
{
    QVector<UpdateNotification> notifications = processServerUpdates(notificationsForServer);
    queueUpdates(notifications);
}

QVector<UpdateNotification> Server::processServerUpdates(const QVector<UpdateNotification> &notificationsForServer)
{
    QVector<UpdateNotification> userNotifications;
    for (const UpdateNotification &notification : notificationsForServer) {
        LocalUser *user = getUser(notification.userId);
        if (!user) {
            qCWarning(lcServerCrossUpdates) << CALL_INFO << "Invalid user!" << notification.userId;
            continue;
        }

        switch (notification.type) {
        case UpdateNotification::Type::CreateChat:
        {
            processCreateChat(notification);

            UpdateNotification participantsUpdate;
            participantsUpdate.type = UpdateNotification::Type::ChatParticipants;
            participantsUpdate.userId = notification.userId;
            participantsUpdate.dialogPeer = notification.dialogPeer;
            participantsUpdate.joinWithNext = true;
            userNotifications << participantsUpdate;
        }
        {
            UpdateNotification userUpdate = notification;
            userUpdate.type = UpdateNotification::Type::NewMessage;
            PostBox *box = user->getPostBox();
            const quint32 newMessageId = box->addMessage(notification.messageDataId);
            messageService()->addMessageReference(notification.messageDataId, box->peer(), newMessageId);
            userUpdate.messageId = newMessageId;
            userUpdate.pts = box->pts();

            user->addNewMessage(userUpdate.dialogPeer, userUpdate.messageId, userUpdate.messageDataId);
            user->bumpDialogUnreadCount(userUpdate.dialogPeer);
            userNotifications << userUpdate;
        }
            break;
        case UpdateNotification::Type::NewMessage: {
            UpdateNotification userUpdate = notification;
            PostBox *box = user->getPostBox();
            const quint32 newMessageId = box->addMessage(userUpdate.messageDataId);
            messageService()->addMessageReference(userUpdate.messageDataId, box->peer(), newMessageId);
            userUpdate.messageId = newMessageId;
            userUpdate.pts = box->pts();

            user->addNewMessage(userUpdate.dialogPeer, userUpdate.messageId, userUpdate.messageDataId);
            user->bumpDialogUnreadCount(userUpdate.dialogPeer);
            userNotifications << userUpdate;
        }
            break;
        case UpdateNotification::Type::ReadOutbox:
            // Notice: this method calls queueUpdates() on its own.
            // TODO: Refactor
            reportLocalMessageRead(user, notification);
            break;
        case UpdateNotification::Type::MessageAction:
        default:
            userNotifications << notification;
            break;
        }
    }

    return userNotifications;
}

void Server::processCreateChat(const UpdateNotification &notification)
{
    quint32 chatId = notification.dialogPeer.id();
    if (getGroupChat(chatId)) {
        // The chat already created
        // Current implementation send one CreateChat notification for each user.
        // (It is planned to have one CreateChat notification for each DC)
        return;
    }
    LocalGroupChat *chat = new LocalGroupChat(chatId, notification.dcId);
    chat->setDate(notification.date);

    const MessageData *messageData = messageService()->getMessage(notification.messageDataId);
    chat->setTitle(messageData->action().title);
    chat->setCreator(messageData->fromId());
    QVector<quint32> invitedMembers = messageData->action().users;
    invitedMembers.removeOne(chat->creatorId());
    chat->inviteMembers(invitedMembers, chat->creatorId(), chat->date());
    m_groups.insert(chatId, chat);
}

void Server::routeUpdates(const QVector<UpdateNotification> &notifications)
{
    for (const UpdateNotification &notification : notifications) {
        AbstractUser *user = getAbstractUser(notification.userId);
        if (user->dcId() == dcId()) {
            queueServerUpdates({notification});
        } else {
            AbstractServerConnection *remoteServerConnection = getRemoteServer(user->dcId());
            AbstractServerApi *remoteApi = remoteServerConnection->api();
            remoteApi->queueServerUpdates({notification});
        }
    }
}

void Server::insertUser(LocalUser *user)
{
    qCDebug(loggingCategoryServerApi) << Q_FUNC_INFO << user << user->phoneNumber() << user->id();
    m_users.insert(user->id(), user);
    m_phoneToUserId.insert(user->phoneNumber(), user->id());
}

void Server::insertGroup(LocalGroupChat *chat)
{
    qCDebug(loggingCategoryServerApi) << "insert group" << chat << chat->id();
    m_groups.insert(chat->id(), chat);
}

GroupChat *Server::getGroupChat(quint32 chatId) const
{
    return m_groups.value(chatId);
}

bool Server::isLocalBox(const PostBox *box) const
{
    if (!box) {
        return false;
    }
    const Peer peer = box->peer();
    if (peer.type() == Peer::Type::User) {
        return getUser(peer.id());
    }

    return false;
}

quint32 Server::generateChatId()
{
    return ++m_localGroupId;
}

PhoneStatus Server::getPhoneStatus(const QString &identifier) const
{
    PhoneStatus result;
    AbstractUser *user = getAbstractUser(identifier);
    if (user) {
        result.online = user->isOnline();
        result.dcId = user->dcId();
    }
    return result;
}

bool Server::identifierIsValid(const QString &identifier) const
{
    const bool result = identifier.length() > 4;
    qCDebug(loggingCategoryServerApi) << "identifierIsValid(" << identifier << "):" << result;
    return result;
}

QString Server::normalizeIdentifier(const QString &identifier) const
{
    if (identifier.startsWith(QLatin1Char('+'))) {
        return identifier.mid(1);
    }
    return identifier;
}

AbstractUser *Server::getAbstractUser(quint32 userId) const
{
    AbstractUser *user = getUser(userId);
    if (!user) {
        user = getRemoteUser(userId);
    }
    return user;
}

AbstractUser *Server::getAbstractUser(const QString &identifier) const
{
    AbstractUser *user = getUser(identifier);
    if (!user) {
        user = getRemoteUser(identifier);
    }
    return user;
}

AbstractUser *Server::getRemoteUser(quint32 userId) const
{
    for (AbstractServerConnection *remoteServer : m_remoteServers) {
        AbstractUser *u = remoteServer->getUser(userId);
        if (u) {
            return u;
        }
    }
    return nullptr;
}

AbstractUser *Server::getRemoteUser(const QString &identifier) const
{
    for (AbstractServerConnection *remoteServer : m_remoteServers) {
        AbstractUser *u = remoteServer->getUser(identifier);
        if (u) {
            return u;
        }
    }
    return nullptr;
}

QVector<PostBox *> Server::getPostBoxes(const Peer &targetPeer, AbstractUser *applicant) const
{
    // Boxes:
    // message to contact
    //    Users (self and recipient (if not self))
    //
    // message to group chat
    //    Users (each member)
    //
    // message to megagroup or broadcast
    //    Channel (the channel)

    QVector<PostBox *> boxes;
    if (targetPeer.type() == Peer::User) {
        AbstractUser *toUser = getAbstractUser(targetPeer.id());
        boxes.append(toUser->getPostBox());
        if (applicant && applicant->id() != targetPeer.id()) {
            boxes.append(applicant->getPostBox());
        }
    }
    if (targetPeer.type() == Peer::Chat) {
        const GroupChat *groupChat = getGroupChat(targetPeer.id());
        for (const quint32 userId : groupChat->memberIds()) {
            boxes.append(getAbstractUser(userId)->getPostBox());
        }
    }

    return boxes;
}

AbstractServerConnection *Server::getRemoteServer(quint32 dcId) const
{
    for (AbstractServerConnection *remoteServer : m_remoteServers) {
        if (remoteServer->dcId() == dcId) {
            return remoteServer;
        }
    }
    return nullptr;
}

} // Server namespace

} // Telegram namespace
