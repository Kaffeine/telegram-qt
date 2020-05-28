#ifndef XMPP_GROUP_CHAT_HPP
#define XMPP_GROUP_CHAT_HPP

#include "GroupChat.hpp"

namespace Telegram {

namespace Server {

class XmppLocalChat : public LocalGroupChat
{
public:
    explicit XmppLocalChat(quint32 chatId, quint32 dcId);

    QString getMemberNickname(quint32 userId) const;
    void setMemberNickname(quint32 userId, const QString &nickname);

protected:
    QHash<quint32, QString> m_userIdToNickname;
};

} // Server namespace

} // Telegram namespace

#endif // XMPP_GROUP_CHAT_HPP
