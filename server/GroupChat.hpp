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
    UserId userId;
    UserId inviterId;
    quint32 date = 0;
    Role role = Role::Invalid;
};

class GroupChat : public MessageRecipient
{
public:
    Peer peer() const { return m_peer; }
    virtual QString title() const { return m_title; }

    virtual UserId creatorId() const;
    virtual quint32 date() const { return m_date; }

    virtual quint32 dcId() const { return m_dcId; }
    virtual QVector<ChatMember> members() const { return m_members; }
    QVector<UserId> memberIds() const;

    Peer toPeer() const final { return peer(); }

protected:
    Peer m_peer;
    quint32 m_dcId = 0;
    quint32 m_date = 0;
    QString m_title;
    QVector<ChatMember> m_members;
};

class LocalGroupChat : public GroupChat
{
public:
    explicit LocalGroupChat(const Peer &peer, quint32 dcId);

    void setDate(quint32 date);
    void setTitle(const QString &title);
    void setCreator(UserId creatorId);
    void inviteMembers(const QVector<UserId> &members, UserId inviterId, quint32 date);
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_CHAT_HPP
