#include "BotUser.hpp"

#include "MessageService.hpp"
#include "ServerApi.hpp"

namespace Telegram {

namespace Server {

BotUser::BotUser(quint32 userId, LocalServerApi *api)
    : m_serverApi(api)
{
    setUserId(userId);
}

bool BotUser::isOnline() const
{
    return true;
}

void BotUser::processInlineQuery(AbstractUser *user, const QString &query)
{

}

void BotUser::addMessageCallback(const QString &message, std::function<void ()> callback)
{

}

void BotUser::sendMessage(const Peer &peer, const QString &message)
{
    MessageData *messageData = m_serverApi->messageService()->addMessage(userId(), peer, message);
    QVector<UpdateNotification> notifications = m_serverApi->processMessage(messageData);
    m_serverApi->queueUpdates(notifications);
}

void BotUser::answerInlineQuery()
{

}

} // Server namespace

} // Telegram namespace
