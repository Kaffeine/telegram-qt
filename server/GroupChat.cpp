#include "GroupChat.hpp"

#include "Debug.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcServerGroupChat, "telegram.server.groupchat", QtWarningMsg)

namespace Telegram {

namespace Server {

LocalGroupChat::LocalGroupChat(const Peer &peer, quint32 dcId)
{
    m_peer = peer;
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

void LocalGroupChat::setCreator(UserId creatorId)
{
    if (!m_members.isEmpty()) {
        qWarning(lcServerGroupChat) << "Invalid setCreator() call for group" << m_peer;
        return;
    }
    ChatMember creator;
    creator.userId = creatorId;
    creator.role = ChatMember::Role::Creator;
    m_members.append(creator);
}

void LocalGroupChat::inviteMembers(const QVector<UserId> &members, UserId inviterId, quint32 date)
{
    QVector<UserId> currentMembers = memberIds();
    for (UserId userId : members) {
        if (currentMembers.contains(userId)) {
            qWarning(lcServerGroupChat) << "Unable to invite an already active member"
                                        << userId << "of group" << m_peer;
            continue;
        }
        ChatMember member;
        member.userId = userId;
        member.inviterId = inviterId;
        member.date = date;
        member.role = ChatMember::Role::User;

        m_members.append(member);
    }
}

UserId GroupChat::creatorId() const
{
    if (m_members.isEmpty()) {
        qWarning(lcServerGroupChat) << "Invalid creatorId() call for group" << m_peer;
        return UserId();
    }
    return m_members.first().userId;
}

QVector<UserId> GroupChat::memberIds() const
{
    QVector<UserId> ids;
    ids.reserve(m_members.count());
    for (const ChatMember &member : m_members) {
        ids.append(member.userId);
    }

    return ids;
}

} // Server namespace

} // Telegram namespace
