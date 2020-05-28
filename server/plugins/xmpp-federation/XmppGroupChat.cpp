#include "XmppGroupChat.hpp"

namespace Telegram {

namespace Server {

XmppLocalChat::XmppLocalChat(quint32 chatId, quint32 dcId)
    : LocalGroupChat(chatId, dcId)
{
}

QString XmppLocalChat::getMemberNickname(quint32 userId) const
{
    return m_userIdToNickname.value(userId);
}

void XmppLocalChat::setMemberNickname(quint32 userId, const QString &nickname)
{
    m_userIdToNickname.insert(userId, nickname);
}

} // Server

} // Telegram
