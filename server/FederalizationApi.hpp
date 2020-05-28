#ifndef FEDERALIZATION_SERVER_API
#define FEDERALIZATION_SERVER_API

#include "ServerApi.hpp"
#include "RemoteServerConnection.hpp"

#include <QHostAddress>
#include <QSet>

namespace Telegram {

namespace Server {

class FederalizationApi : public QObject, public AbstractServerApi
{
    Q_OBJECT
public:
    explicit FederalizationApi(QObject *parent = nullptr);
    ~FederalizationApi() = default;

    virtual bool start() = 0;

    virtual QStringList supportedSchemes() const = 0;
    virtual PendingVariant *searchContacts(const QString &query, quint32 limit) = 0;

    quint32 dcId() const final { return m_dcId; }
    void setDcId(quint32 id) { m_dcId = id; }

    QString domain() const { return m_domain; }
    virtual void setDomain(const QString &domain);
    virtual void setListenAddress(const QHostAddress &address);

    MessageService *messageService() const override { return m_messageService; }
    void setMessageService(MessageService *messageService) { m_messageService = messageService; }
    IMediaService *mediaService() const override { return nullptr; }

    void addServerConnection(AbstractServerConnection *remoteServer);

    AbstractUser *getServerUser(quint32 userId) const;
    AbstractUser *getServerUser(const QString &userName) const;
    AbstractServerConnection *getServerForPeer(const Peer &peer) const;
    AbstractServerApi *getServerApiForPeer(const Peer &peer) const;

    GroupChat *getGroupChat(quint32 chatId) const override;

protected:
    virtual void processCreateChat(const UpdateNotification &notification);
    virtual LocalGroupChat *createGroupChatObject(quint32 chatId, quint32 dcId);

private:
    quint32 m_dcId = 0;
    QString m_domain;
    QHostAddress m_address;
    QSet<AbstractServerConnection*> m_remoteServers;
    MessageService *m_messageService = nullptr;
    QHash<quint32, LocalGroupChat *> m_groups; // groupId to GroupChat
};

class FederalizationGateway : public AbstractServerConnection
{
    Q_OBJECT
public:
    explicit FederalizationGateway(QObject *parent = nullptr);

    QStringList supportedSchemes() const override;
    quint32 dcId() const override;

    void setApi(FederalizationApi *remoteServer);

    AbstractUser *getUser(const quint32 userId) const override;
    AbstractUser *getUser(const QString &identifier) const override;
    AbstractServerApi *api();

    QByteArray getForeingUserAuthorization(quint32 userId);
    PendingVariant *searchContacts(const QString &query, quint32 limit) override;

protected:
    FederalizationApi *m_server = nullptr;
};

} // Server namespace

} // Telegram

#endif // FEDERALIZATION_SERVER_API
