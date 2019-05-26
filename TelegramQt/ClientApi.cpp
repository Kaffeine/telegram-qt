#include "ClientApi.hpp"
#include "ClientApi_p.hpp"

#include "ClientBackend.hpp"
#include "DataStorage_p.hpp"

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

DataStorage *ClientApiPrivate::dataStorage()
{
    return m_backend->dataStorage();
}

const DataStorage *ClientApiPrivate::dataStorage() const
{
    return m_backend->dataStorage();
}

DataInternalApi *ClientApiPrivate::dataInternalApi()
{
    return DataInternalApi::get(m_backend->dataStorage());
}

const DataInternalApi *ClientApiPrivate::dataInternalApi() const
{
    return DataInternalApi::get(m_backend->dataStorage());
}

ClientApi::ClientApi(QObject *parent) :
    QObject(parent)
{
}

} // Client namespace

} // Telegram namespace
