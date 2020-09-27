#ifndef TELEGRAM_SERVER_CHAT_HPP
#define TELEGRAM_SERVER_CHAT_HPP

#include "TelegramServerUser.hpp"

namespace Telegram {

namespace Server {

class ChatMember
{
public:
    enum class Role {
        Invalid,
        Creator,
        Admin,
        User,
    };
    UserId userId = 0;
    UserId inviterId = 0;
    quint32 date = 0;
    Role role = Role::Invalid;
};

class GroupChat : public MessageRecipient
{
public:
    virtual quint32 id() const { return m_id; }
    virtual QString title() const { return m_title; }

    virtual UserId creatorId() const;
    virtual quint32 date() const { return m_date; }

    virtual quint32 dcId() const { return m_dcId; }
    virtual QVector<ChatMember> members() const { return m_members; }
    QVector<UserId> memberIds() const;

    Peer toPeer() const override { return Peer::fromChatId(id()); }

protected:
    quint32 m_id = 0;
    quint32 m_dcId = 0;
    quint32 m_date = 0;
    QString m_title;
    QVector<ChatMember> m_members;
};

class LocalGroupChat : public GroupChat
{
public:
    explicit LocalGroupChat(quint32 chatId, quint32 dcId);

    void setDate(quint32 date);
    void setTitle(const QString &title);
    void setCreator(UserId creatorId);
    void inviteMembers(const QVector<UserId> &members, UserId inviterId, quint32 date);
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_CHAT_HPP
