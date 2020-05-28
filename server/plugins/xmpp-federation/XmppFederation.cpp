#include "XmppFederation.hpp"

#include <QVariantMap>
#include <QHostAddress>
#include <QSslKey>

#include <QXmppDiscoveryIq.h>
#include <QXmppPingIq.h>
#include <QXmppMessage.h>
#include <QXmppServer.h>
#include <QXmppUtils.h>

#include "XmppGroupChat.hpp"
#include "XmppServerExtension.hpp"
#include "XmppUser.hpp"

#include "ApiUtils.hpp"

#include "GroupChat.hpp"
#include "MessageService.hpp"
#include "PendingVariant.hpp"
#include "ServerApi.hpp"
#include <QDomElement>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcServerXmpp, "telegram.server.cross.xmpp", QtDebugMsg)

static const QString c_xmpp = QLatin1String("xmpp");

namespace Telegram {

namespace Server {

XmppFederalizationApi::XmppFederalizationApi(QObject *parent)
    : FederalizationApi(parent)
    , m_xmppServer(new QXmppServer(this))
{
    QXmppLogger *logger = new QXmppLogger();
    logger->setLoggingType(QXmppLogger::StdoutLogging);
    m_xmppServer->setLogger(logger);

    m_telegramExtension = new XmppServerExtension(this);
    m_xmppServer->addExtension(m_telegramExtension);
}

XmppFederalizationApi::~XmppFederalizationApi()
{
    delete m_xmppServer;
}

bool XmppFederalizationApi::start()
{
    bool started = false;
    quint16 port = 5269;
    if (m_listenAddress.isNull()) {
        started = m_xmppServer->listenForServers();
    } else {
        started = m_xmppServer->listenForServers(m_listenAddress, port);
    }

    if (started) {
        qCInfo(lcServerXmpp).nospace().noquote() << "Start XMPP Gateway (DC " << dcId() << ") "
                                                 << "(listening " << m_listenAddress.toString()
                                                 << ":" <<port << ")";
    } else {
        qCWarning(lcServerXmpp) << "Unable to start XMPP Gateway on"
                                << m_listenAddress.toString();
    }

    return started;
}

QStringList XmppFederalizationApi::supportedSchemes() const
{
    return { c_xmpp };
}

bool isCompleteJid(const QString &jid)
{
    if (jid.indexOf(QLatin1Char('@')) < 0) {
        return false;
    }

    QString contactDomain = QXmppUtils::jidToDomain(jid);
    if (contactDomain.count(QLatin1Char('.')) < 1) {
        return false;
    }

//    // We work only with IP addresses for now.
//    if (!contactDomain.at(contactDomain.length() - 1).isDigit()) {
//        return false;
//    }

    return true;
}

PendingVariant *XmppFederalizationApi::searchContacts(const QString &query, quint32 limit)
{
    Q_UNUSED(limit)

    if (!query.startsWith(QLatin1String("xmpp:"))) {
        QString text = QLatin1String("Invalid search request");
        return PendingOperation::failOperation<PendingVariant>(text, this);
    }

    QString jid = query.section(QLatin1Char(':'), 1);
    if (!isCompleteJid(jid)) {
        QString text = QLatin1String("Incomplete JID");
        return PendingOperation::failOperation<PendingVariant>(text, this);
    }

    // QString requestId = m_telegramExtension->discoverUser(jid);
    QString requestId = m_telegramExtension->pingUser(jid);
    if (requestId.isEmpty()) {
        QString text = QLatin1String("Unknown error (unable to send request)");
        return PendingOperation::failOperation<PendingVariant>(text, this);
    }

    PendingVariant *op = new PendingVariant(this);
    m_requests.insert(requestId, op);

    return op;
}

QString XmppFederalizationApi::domain() const
{
    return m_xmppServer->domain();
}

void XmppFederalizationApi::setDomain(const QString &domain)
{
    m_xmppServer->setDomain(domain);
}

void XmppFederalizationApi::setListenAddress(const QHostAddress &address)
{
    m_listenAddress = address;
}

AbstractUser *XmppFederalizationApi::getUser(const QString &jid) const
{
    XmppUser *user = getXmppUser(jid);
    if (user) {
        return user;
    }

    return getTelegramUser(jid);
}

XmppUser *XmppFederalizationApi::ensureUser(const QString &jid)
{
    const QString bareJid = QXmppUtils::jidToBareJid(jid);
    quint32 userId = m_jidToUserId.value(bareJid);

    XmppUser *user = nullptr;

    if (userId) {
        user = m_xmppUsers.value(userId);
    } else {
        user = new XmppUser();
        user->setJid(bareJid);
        user->setDcId(dcId());
        insertUser(user);
    }

    user->addResource(QXmppUtils::jidToResource(jid));

    return user;
}

XmppUser *XmppFederalizationApi::getXmppUser(const QString &jid) const
{
    const QString bareJid = QXmppUtils::jidToBareJid(jid);
    quint32 userId = m_jidToUserId.value(bareJid);
    return m_xmppUsers.value(userId);
}

XmppUser *XmppFederalizationApi::getXmppUser(quint32 userId) const
{
    return m_xmppUsers.value(userId);
}

XmppLocalChat *XmppFederalizationApi::getXmppChat(const QString &jid) const
{
    const QString bareJid = QXmppUtils::jidToBareJid(jid);
    quint32 chatId = m_jidToChatId.value(bareJid);
    return getXmppChat(chatId);
}

XmppLocalChat *XmppFederalizationApi::getXmppChat(quint32 chatId) const
{
    return m_xmppGroups.value(chatId);
}

GroupChat *XmppFederalizationApi::getTelegramChat(const QString &jid) const
{
    const QString bareJid = QXmppUtils::jidToBareJid(jid);
    quint32 chatId = m_jidToChatId.value(bareJid);
    return getTelegramChat(chatId);
}

GroupChat *XmppFederalizationApi::getTelegramChat(quint32 chatId) const
{
    return getGroupChat(chatId);
}

AbstractUser *XmppFederalizationApi::getTelegramUser(const QString &jid) const
{
    const QString userName = QXmppUtils::jidToUser(jid);
    AbstractUser *user = getServerUser(userName);
    if (!user) {
        qWarning() << "User" << userName << "Not found on the Telegram side";
    }
    return user;
}

AbstractUser *XmppFederalizationApi::getTelegramUser(quint32 userId) const
{
    return getServerUser(userId);
}

QString XmppFederalizationApi::getUserBareJid(quint32 userId) const
{
    const XmppUser *localUser = getXmppUser(userId);
    if (localUser) {
        return localUser->jid();
    }
    AbstractUser *telegramUser = getTelegramUser(userId);
    if (telegramUser) {
        QString userPart = telegramUser->phoneNumber();
        QString domainPart = domain();
        return QStringLiteral("%1@%2").arg(userPart, domainPart);
    }

    qWarning(lcServerXmpp) << "User not found" << userId;
    return QString();
}

QString XmppFederalizationApi::getBareJid(const Peer &peer) const
{
    if (peer.type() == Peer::User) {
        return getUserBareJid(peer.id());
    } else if (peer.type() == Peer::Chat) {
        if (!m_chatIdToJid.contains(peer.id())) {
            if (getTelegramChat(peer.id())) {
                QString chatPart = peer.toString();
                QString domainPart = domain();
                m_chatIdToJid.insert(peer.id(), QStringLiteral("%1@%2").arg(chatPart, domainPart));
            }
        }
        return m_chatIdToJid.value(peer.id());
    }

    return QString();
}

Peer XmppFederalizationApi::getPeerFromJid(const QString &jid) const
{
    AbstractUser *user = getUser(jid);
    if (user) {
        return user->toPeer();
    }

    if (m_jidToChatId.contains(jid)) {
        return Peer::fromChatId(m_jidToChatId.value(jid));
    }

    return Peer();
}

QString XmppFederalizationApi::getChatMemberJid(const XmppLocalChat *groupChat, quint32 userId) const
{
    const QString mucJid = getBareJid(groupChat->toPeer());
    const QString memberNickname = groupChat->getMemberNickname(userId);

    return mucJid + QLatin1Char('/') + memberNickname;
}

QString XmppFederalizationApi::getChatMemberJid(const Peer &groupChat, quint32 userId) const
{
    const XmppLocalChat *chat = m_xmppGroups.value(groupChat.id());
    return getChatMemberJid(chat, userId);
}

bool XmppFederalizationApi::sendPacket(const XmppUser *xmppUser, QXmppStanza *packet)
{
    bool result = true;

    for (const QString &resource : xmppUser->activeResources()) {
        packet->setTo(xmppUser->jid() + QLatin1Char('/') + resource);
        if (!xmppServer()->sendPacket(*packet)) {
            result = false;
        }
    }

    return result;
}

void XmppFederalizationApi::sendMessageFromTelegram(quint32 fromUserId, const Peer &targetPeer, const MessageData *messageData)
{
    if (!fromUserId) {
        return;
    }

    const QString toJid = getBareJid(targetPeer);

    QXmppMessage message;
    message.setId(QStringLiteral("msg%1").arg(messageData->globalId()));
    message.setBody(messageData->content().text());

    if (targetPeer.type() == Peer::User) {
        // Direct message
        QString xmppFrom = getUserBareJid(fromUserId);

        message.setTo(toJid);
        message.setFrom(xmppFrom);

        xmppServer()->sendPacket(message);
    } else {
        // MUC message
        const XmppLocalChat *groupChat = getXmppChat(targetPeer.id());
        QString xmppFrom = getChatMemberJid(groupChat, fromUserId);

        message.setType(QXmppMessage::GroupChat);
        message.setFrom(xmppFrom);

        for (const quint32 memberId : groupChat->memberIds()) {
            const XmppUser *xmppMember = getXmppUser(memberId);
            if (!xmppMember) {
                continue;
            }

            sendPacket(xmppMember, &message);
        }
    }
}

void XmppFederalizationApi::sendMessageFromXmpp(XmppUser *fromUser, const Peer &targetPeer, const QString &message)
{
    const quint32 fromUserId = fromUser->id();
    const MessageData *messageData = messageService()->addMessage(fromUserId,
                                                                  targetPeer,
                                                                  message);
    const quint32 requestDate = Telegram::Utils::getCurrentTime();


    // Bake a Telegram message
    UpdateNotification notification;
    notification.type = UpdateNotification::Type::NewMessage;
    notification.date = requestDate;
    notification.messageDataId = messageData->globalId();

    if (targetPeer.type() == Peer::User) {
        // Direct message
        notification.dialogPeer = fromUser->toPeer();
        notification.userId = targetPeer.id();

        AbstractServerApi *remoteApi = getServerApiForPeer(targetPeer);
        if (!remoteApi) {
            qCWarning(lcServerXmpp) << "Unable to delivery from xmpp to " << targetPeer.toString()
                                    << "(no remote API)";

            // TODO: Reply to the sender with an error.
            return;
        }
        remoteApi->queueServerUpdates({notification});
    } else {
        // MUC message
        const GroupChat *groupChat = getGroupChat(targetPeer.id());
        const QString xmppFrom = getChatMemberJid(targetPeer, fromUserId);

        // Bake XMPP message
        QXmppMessage message;
        message.setId(QStringLiteral("msg%1").arg(messageData->globalId()));
        message.setBody(messageData->content().text());
        message.setType(QXmppMessage::GroupChat);
        message.setFrom(xmppFrom);

        // Bake Telegram message
        notification.dialogPeer = targetPeer;

        for (const quint32 memberId : groupChat->memberIds()) {
            const XmppUser *xmppMember = getXmppUser(memberId);
            if (xmppMember) {
                sendPacket(xmppMember, &message);
            } else {
                notification.userId = memberId;

                AbstractServerApi *remoteApi = getServerApiForPeer(Peer::fromUserId(memberId));
                if (!remoteApi) {
                    continue;
                }
                remoteApi->queueServerUpdates({notification});
            }
        }
    }
}

void XmppFederalizationApi::inviteToMuc(const Peer &mucPeer, const QString &fromJid, const QString &toJid)
{
    const QString mucJid = getBareJid(mucPeer);

    // XEP-0249: Direct MUC Invitations
    QXmppMessage message(mucJid, toJid);
    message.setType(QXmppMessage::Type::Normal);
    message.setMucInvitationJid(mucJid);

    qCDebug(lcServerXmpp) << "inviteToMuc" << mucJid << "user" << toJid;

    xmppServer()->sendPacket(message);

    // https://github.com/psi-im/psi/blob/85eef3b47d3cc2a9b7b942c1548da71c4c77a0a1/src/psiaccount.cpp#L2782

    // what came:
    // <message type="chat"
    //     from="123456789@192.168.1.183"
    //     to="test1@127.0.0.3">
    // <x xmlns="jabber:x:conference"
    //     jid="chat1@192.168.1.183"/>
    // </message>


    // RECEIVED <message to="test1@127.0.0.3" from="123456789@192.168.1.183" type="chat"><x xmlns="jabber:x:conference" jid="chat1@192.168.1.183"/></message>
    // SENT <message to="test1@127.0.0.3" type="chat" from="123456789@192.168.1.183"><x xmlns="jabber:x:conference" jid="chat1@192.168.1.183"/></message>

    // RECEIVED <message from="123456789@192.168.1.183" to="test1@127.0.0.3">
    // <x xmlns="jabber:x:conference" jid="chat1@192.168.1.183"/>
    // </message>
    // WARNING Received a stanza from unexpected JID 123456789@192.168.1.183

    // PSI works with:

    // <message from="admins@conference.phost.local" to="kaffeine@phost.local" id="aadda">
    //
    // <x xmlns="http://jabber.org/protocol/muc#user">
    // <invite from="admins@conference.phost.local/negative">
    // <reason/>
    // </invite>
    // </x>
    // <x xmlns="jabber:x:conference" jid="admins@conference.phost.local"/>
    // <body>admins@conference.phost.local/negative invited you to the room admins@conference.phost.local</body>
    // </message>


    // message from conference to the user out of conf
    //
    // <x http://jabber.org/protocol/muc#user" (ns_muc_user)
    // body seems to be optional
}

void XmppFederalizationApi::handleNewXmppChatMember(GroupChat *groupChat, const QString &joinedUserOwnJid, const QString &nickname)
{
    const XmppUser *fromUser = ensureUser(joinedUserOwnJid);

    XmppLocalChat *xmppChat = m_xmppGroups.value(groupChat->id());
    if (!xmppChat) {
        // TODO
        return;
    }

    xmppChat->setMemberNickname(fromUser->userId(), nickname);
}

AbstractUser *XmppFederalizationApi::getAbstractUser(quint32 userId) const
{
    return getXmppUser(userId);
}

AbstractUser *XmppFederalizationApi::getAbstractUser(const QString &identifier) const
{
    return getXmppUser(identifier);
}

void XmppFederalizationApi::insertUser(XmppUser *user)
{
    qInfo(lcServerXmpp) << __func__ << user->userId() << user->jid();
    m_xmppUsers.insert(user->userId(), user);
    m_jidToUserId.insert(user->jid(), user->userId());
}

QVector<PostBox *> XmppFederalizationApi::getPostBoxes(const Peer &targetPeer, AbstractUser *applicant) const
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
        AbstractUser *toUser = getTelegramUser(targetPeer.id());
        boxes.append(toUser->getPostBox());
        if (applicant && applicant->id() != targetPeer.id()) {
            boxes.append(applicant->getPostBox());
        }
    }
    if (targetPeer.type() == Peer::Chat) {
        const GroupChat *groupChat = getTelegramChat(targetPeer.id());
        for (const quint32 userId : groupChat->memberIds()) {
            AbstractUser *telegramParticipant = getTelegramUser(userId);
            if (telegramParticipant) {
                boxes.append(telegramParticipant->getPostBox());
            }
        }
    }

    return boxes;
}

void XmppFederalizationApi::queueServerUpdates(const QVector<UpdateNotification> &notifications)
{
    for (const UpdateNotification &notification : notifications) {
        switch (notification.type) {
        case UpdateNotification::Type::CreateChat: {
            processCreateChat(notification);
            const MessageData *messageData = messageService()->getMessage(notification.messageDataId);
            QString from = getUserBareJid(messageData->fromId());
            for (const quint32 invitedId : messageData->action().users) {
                XmppUser *invitedXmppUser = getXmppUser(invitedId);
                if (!invitedXmppUser) {
                    continue;
                }
                inviteToMuc(notification.dialogPeer, from, invitedXmppUser->jid());
            }
        }
            break;
        case UpdateNotification::Type::NewMessage: {
            const MessageData *messageData = messageService()->getMessage(notification.messageDataId);
            const Peer peer = messageData->getDialogPeer(messageData->fromId());
            sendMessageFromTelegram(messageData->fromId(), peer, messageData);
        }
            break;
        default:
            qWarning(lcServerXmpp) << __func__ << "Not implemented:" << notification.type;
            break;
        }
    }
}

void XmppFederalizationApi::addNetworkRequest(const QString &stanzaId, PendingVariant *operation)
{
    m_requests.insert(stanzaId, operation);
}

PendingVariant *XmppFederalizationApi::takeRequest(const QString &stanzaId)
{
    return m_requests.take(stanzaId);
}

void XmppFederalizationApi::processCreateChat(const UpdateNotification &notification)
{
    FederalizationApi::processCreateChat(notification);

    const quint32 chatId = notification.dialogPeer.id();
    const QString jid = getBareJid(Peer::fromChatId(chatId));
    m_jidToChatId.insert(jid, chatId);

    XmppLocalChat *chat = m_xmppGroups.value(chatId);
    for (const quint32 userId : chat->memberIds()) {
        AbstractUser *member = getTelegramUser(userId);
        if (!member) {
            qCWarning(lcServerXmpp) << "Unable to process group chat" << chatId
                                    << "member" << userId;
            continue;
        }
        chat->setMemberNickname(member->id(), member->userName());
    }
}

LocalGroupChat *XmppFederalizationApi::createGroupChatObject(quint32 chatId, quint32 dcId)
{
    XmppLocalChat *chat = new XmppLocalChat(chatId, dcId);
    m_xmppGroups.insert(chatId, chat);
    return chat;
}

} // Server

} // Telegram
