#ifndef TELEGRAM_QT_SERVER_BOT_USER_HPP
#define TELEGRAM_QT_SERVER_BOT_USER_HPP

#include "TelegramServerUser.hpp"

#include <functional>

namespace Telegram {

namespace Server {

class LocalServerApi;

class BotUser : public LocalUser
{
public:
    explicit BotUser(quint32 userId, LocalServerApi *api);

    QString phoneNumber() const override { return QString(); }

    bool isBot() const override { return true; }
    bool isOnline() const override;

    void processInlineQuery(AbstractUser *user, const QString &query);

    void addMessageCallback(const QString &message, std::function<void()> callback);

    void sendMessage(const Peer &peer, const QString &message);

protected:
    void answerInlineQuery();

    LocalServerApi *m_serverApi = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_BOT_USER_HPP
