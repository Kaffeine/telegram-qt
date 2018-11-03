#include "ClientApi.hpp"
#include "ClientApi_p.hpp"

namespace Telegram {

namespace Client {

ClientApiPrivate::ClientApiPrivate(ClientApi *parent) :
    QObject(parent),
    q_ptr(parent)
{
}

ClientApiPrivate *ClientApiPrivate::get(ClientApi *parent)
{
    return parent->d;
}

void ClientApiPrivate::setBackend(Backend *backend)
{
    m_backend = backend;
}

ClientApi::ClientApi(QObject *parent) :
    QObject(parent)
{
}

} // Client namespace

} // Telegram namespace
