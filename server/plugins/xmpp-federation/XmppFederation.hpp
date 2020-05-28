#ifndef XMPP_FEDERATION_HPP
#define XMPP_FEDERATION_HPP

#include "FederalizationApi.hpp"

#include <QHostAddress>

class QXmppServer;
class QXmppStanza;

namespace Telegram {

namespace Server {

class AbstractUser;
class XmppServerExtension;
class XmppUser;
class XmppLocalChat;

class XmppFederalizationApi : public FederalizationApi
{
    Q_OBJECT
public:
    XmppFederalizationApi(QObject *parent = nullptr);
    ~XmppFederalizationApi();

    bool start() override;

    QStringList supportedSchemes() const override;
    PendingVariant *searchContacts(const QString &query, quint32 limit);

    QString domain() const;
    void setDomain(const QString &domain);
    void setListenAddress(const QHostAddress &address);

    AbstractUser *getUser(const QString &jid) const;

    XmppUser *ensureUser(const QString &jid);

    XmppUser *getXmppUser(const QString &jid) const;
    XmppUser *getXmppUser(quint32 userId) const;

    XmppLocalChat *getXmppChat(const QString &jid) const;
    XmppLocalChat *getXmppChat(quint32 chatId) const;

    GroupChat *getTelegramChat(const QString &jid) const;
    GroupChat *getTelegramChat(quint32 chatId) const;
    AbstractUser *getTelegramUser(const QString &jid) const;
    AbstractUser *getTelegramUser(quint32 userId) const;
    QString getUserBareJid(quint32 userId) const;
    QString getBareJid(const Peer &peer) const;
    Peer getPeerFromJid(const QString &jid) const;

    QString getChatMemberJid(const XmppLocalChat *groupChat, quint32 userId) const;
    QString getChatMemberJid(const Peer &groupChat, quint32 userId) const;

    QXmppServer *xmppServer() const { return m_xmppServer; }
    bool sendPacket(const XmppUser *xmppUser, QXmppStanza *packet);

    void sendMessageFromTelegram(quint32 fromUserId, const Peer &targetPeer, const MessageData *messageData);
    void sendMessageFromXmpp(XmppUser *fromUser, const Peer &targetPeer, const QString &message);

    void inviteToMuc(const Peer &mucPeer, const QString &fromJid, const QString &toJid);
    void handleNewXmppChatMember(GroupChat *groupChat,
                                 const QString &joinedUserOwnJid,
                                 const QString &nickname);

    AbstractUser *getAbstractUser(quint32 userId) const override;
    AbstractUser *getAbstractUser(const QString &identifier) const override;

    void insertUser(XmppUser *user);
    QVector<PostBox *> getPostBoxes(const Peer &targetPeer, AbstractUser *applicant = nullptr) const;

    PhoneStatus getPhoneStatus(const QString &identifier) const override { return PhoneStatus(); }
    bool identifierIsValid(const QString &identifier) const override { return false; }
    QString normalizeIdentifier(const QString &identifier) const override { return QString(); }
    void queueServerUpdates(const QVector<UpdateNotification> &notifications) override;

    void addNetworkRequest(const QString &stanzaId, PendingVariant *operation);
    PendingVariant *takeRequest(const QString &stanzaId);

protected:
    void processCreateChat(const UpdateNotification &notification) override;
    LocalGroupChat *createGroupChatObject(quint32 chatId, quint32 dcId) override;

    QXmppServer *m_xmppServer = nullptr;
    XmppServerExtension *m_telegramExtension = nullptr;
    QHostAddress m_listenAddress;

    // Data
    QHash<quint32, XmppUser*> m_xmppUsers; // userId to User
    QHash<quint32, XmppLocalChat *> m_xmppGroups; // groupId to XmppLocalChat

    // Maps for faster lookup
    QHash<QString, quint32> m_jidToUserId;
    QHash<QString, quint32> m_jidToChatId;
    mutable QHash<quint32, QString> m_chatIdToJid;

    QHash<QString, PendingVariant *> m_requests;
};

} // Server

} // Telegram

#endif // XMPP_FEDERATION_HPP
