#include "ApiUtils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Utils {

Telegram::Peer toPublicPeer(const TLInputPeer &inputPeer, quint32 selfId)
{
    switch (inputPeer.tlType) {
    case TLValue::InputPeerSelf:
        return Telegram::Peer::fromUserId(selfId);
    case TLValue::InputPeerUser:
        return Telegram::Peer::fromUserId(inputPeer.userId);
    case TLValue::InputPeerChat:
        return Telegram::Peer::fromChatId(inputPeer.chatId);
    case TLValue::InputPeerChannel:
        return Telegram::Peer::fromChannelId(inputPeer.channelId);
    case TLValue::InputPeerEmpty:
    default:
        return Telegram::Peer();
    }
}

Telegram::Peer toPublicPeer(const TLPeer &peer)
{
    switch (peer.tlType) {
    case TLValue::PeerChat:
        return Telegram::Peer::fromChatId(peer.chatId);
    case TLValue::PeerChannel:
        return Telegram::Peer::fromChannelId(peer.channelId);
    case TLValue::PeerUser:
        return Telegram::Peer::fromUserId(peer.userId);
    default:
        return Telegram::Peer();
    }
}

Telegram::Peer toPublicPeer(const TLUser &user)
{
    if (!user.isValid() || !user.id) {
        return Telegram::Peer();
    }
    return Telegram::Peer(user.id, Telegram::Peer::User);
}

Telegram::Peer toPublicPeer(const TLChat *chat)
{
    switch(chat->tlType) {
    case TLValue::Chat:
    case TLValue::ChatForbidden:
        return Telegram::Peer::fromChatId(chat->id);
    case TLValue::Channel:
    case TLValue::ChannelForbidden:
        return Telegram::Peer::fromChannelId(chat->id);
    default:
        return Telegram::Peer();
    }
}

TLPeer toTLPeer(const Telegram::Peer &peer)
{
    TLPeer result;
    switch (peer.type) {
    case Telegram::Peer::Chat:
        result.tlType = TLValue::PeerChat;
        result.chatId = peer.id;
        break;
    case Telegram::Peer::Channel:
        result.tlType = TLValue::PeerChannel;
        result.channelId = peer.id;
        break;
    case Telegram::Peer::User:
        result.tlType = TLValue::PeerUser;
        result.userId = peer.id;
        break;
    }
    return result;
}

Telegram::Peer getMessagePeer(const TLMessage &message, quint32 selfId)
{
    switch (message.toId.tlType) {
    case TLValue::PeerUser:
        if (message.fromId == selfId) {
            return Telegram::Peer::fromUserId(message.toId.userId);
        } else {
            return Telegram::Peer::fromUserId(message.fromId);
        }
    case TLValue::PeerChat:
        return Telegram::Peer::fromChatId(message.toId.chatId);
    case TLValue::PeerChannel:
        return Telegram::Peer::fromChannelId(message.toId.channelId);
    default:
        return Telegram::Peer();
    }
}

} // Utils namespace

} // Telegram namespace
