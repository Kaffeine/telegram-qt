#include "FederalizationApi.hpp"
#include "MessageService.hpp"

namespace Telegram {

namespace Server {

FederalizationGateway::FederalizationGateway(QObject *parent)
    : AbstractServerConnection(parent)
{
}

QStringList FederalizationGateway::supportedSchemes() const
{
    return m_server->supportedSchemes();
}

quint32 FederalizationGateway::dcId() const
{
    return m_server->dcId();
}

void FederalizationGateway::setApi(FederalizationApi *remoteServer)
{
    m_server = remoteServer;
}

AbstractUser *FederalizationGateway::getUser(const quint32 userId) const
{
    return m_server->getAbstractUser(userId);
}

AbstractUser *FederalizationGateway::getUser(const QString &identifier) const
{
    return m_server->getAbstractUser(identifier);
}

AbstractServerApi *FederalizationGateway::api()
{
    return m_server;
}

QByteArray FederalizationGateway::getForeingUserAuthorization(quint32 userId)
{
    return QByteArray();
}

PendingVariant *FederalizationGateway::searchContacts(const QString &query, quint32 limit)
{
    return m_server->searchContacts(query, limit);
}

FederalizationApi::FederalizationApi(QObject *parent)
    : QObject(parent)
{
}

void FederalizationApi::setDomain(const QString &domain)
{
    m_domain = domain;
}

void FederalizationApi::setListenAddress(const QHostAddress &address)
{
    m_address = address;
}

void FederalizationApi::addServerConnection(AbstractServerConnection *remoteServer)
{
    m_remoteServers.insert(remoteServer);
}

AbstractUser *FederalizationApi::getServerUser(quint32 userId) const
{
    for (AbstractServerConnection *remote : m_remoteServers) {
        AbstractUser *user = remote->getUser(userId);
        if (user) {
            return user;
        }
    }

    return nullptr;
}

AbstractUser *FederalizationApi::getServerUser(const QString &userName) const
{
    for (AbstractServerConnection *remote : m_remoteServers) {
        AbstractUser *user = remote->getUser(userName);
        if (user) {
            return user;
        }
    }

    return nullptr;
}

AbstractServerConnection *FederalizationApi::getServerForPeer(const Peer &peer) const
{
    if (peer.type() != Peer::User) {
        return nullptr;
    }

    for (AbstractServerConnection *remote : m_remoteServers) {
        AbstractUser *user = remote->getUser(peer.id());
        if (user) {
            return remote;
        }
    }

    return nullptr;
}

AbstractServerApi *FederalizationApi::getServerApiForPeer(const Peer &peer) const
{
    AbstractServerConnection *remote = getServerForPeer(peer);
    if (!remote) {
        return nullptr;
    }

    return remote->api();
}

GroupChat *FederalizationApi::getGroupChat(quint32 chatId) const
{
    return m_groups.value(chatId);
}

void FederalizationApi::processCreateChat(const UpdateNotification &notification)
{
    quint32 chatId = notification.dialogPeer.id();
    LocalGroupChat *chat = createGroupChatObject(chatId, notification.dcId);
    chat->setDate(notification.date);

    const MessageData *messageData = messageService()->getMessage(notification.messageDataId);
    chat->setTitle(messageData->action().title);
    chat->setCreator(messageData->fromId());
    chat->inviteMembers(messageData->action().users, chat->creatorId(), chat->date());
    m_groups.insert(chatId, chat);
}

LocalGroupChat *FederalizationApi::createGroupChatObject(quint32 chatId, quint32 dcId)
{
    return new LocalGroupChat(chatId, dcId);
}

} // Server namespace

} // Telegram
