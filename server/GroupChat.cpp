#include "GroupChat.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcServerGroupChat, "telegram.server.groupchat", QtWarningMsg)

namespace Telegram {

namespace Server {

LocalGroupChat::LocalGroupChat(quint32 chatId, quint32 dcId)
{
    m_id = chatId;
    m_dcId = dcId;
}

void LocalGroupChat::setDate(quint32 date)
{
    m_date = date;
}

void LocalGroupChat::setTitle(const QString &title)
{
    m_title = title;
}

void LocalGroupChat::setCreator(quint32 creatorId)
{
    if (!m_members.isEmpty()) {
        qWarning(lcServerGroupChat) << "Invalid setCreator() call for group" << m_id;
        return;
    }
    ChatMember creator;
    creator.userId = creatorId;
    creator.role = ChatMember::Role::Creator;
    m_members.append(creator);
}

void LocalGroupChat::inviteMembers(const QVector<quint32> &members, quint32 inviterId, quint32 date)
{
    for (quint32 userId : members) {
        ChatMember member;
        member.userId = userId;
        member.inviterId = inviterId;
        member.date = date;
        member.role = ChatMember::Role::User;

        m_members.append(member);
    }
}

quint32 GroupChat::creatorId() const
{
    if (m_members.isEmpty()) {
        qWarning(lcServerGroupChat) << "Invalid creatorId() call for group" << m_id;
        return 0;
    }
    return m_members.first().userId;
}

QVector<quint32> GroupChat::memberIds() const
{
    QVector<quint32> ids;
    ids.reserve(m_members.count());
    for (const ChatMember &member : m_members) {
        ids.append(member.userId);
    }

    return ids;
}

} // Server namespace

} // Telegram namespace
