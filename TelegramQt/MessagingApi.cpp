#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#include "ClientBackend.hpp"

namespace Telegram {

namespace Client {

MessagingApiPrivate::MessagingApiPrivate(MessagingApi *parent) :
    ClientApiPrivate(parent)
{
}

MessagingApiPrivate *MessagingApiPrivate::get(MessagingApi *parent)
{
    return static_cast<MessagingApiPrivate*>(parent->d);
}

MessagingApi::MessagingApi(QObject *parent) :
    ClientApi(parent)
{
    d = new MessagingApiPrivate(this);
}

MessagesRpcLayer *MessagingApiPrivate::messagesLayer()
{
    return m_backend->messagesLayer();
}

} // Client namespace

} // Telegram namespace
