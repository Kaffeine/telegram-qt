#include "CTelegramModule.hpp"
#include "CTelegramDispatcher.hpp"

CTelegramModule::CTelegramModule(QObject *parent) :
    QObject(parent),
    m_dispatcher(nullptr)
{
}

void CTelegramModule::setDispatcher(CTelegramDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
}

void CTelegramModule::clear()
{
}

bool CTelegramModule::setWantedDc(quint32 dcId)
{
    return m_dispatcher->setWantedDc(dcId);
}

CTelegramConnection *CTelegramModule::activeConnection() const
{
    if (!m_dispatcher) {
        return nullptr;
    }
    return m_dispatcher->activeConnection();
}

CTelegramConnection *CTelegramModule::getExtraConnection(quint32 dc)
{
    if (!m_dispatcher) {
        return nullptr;
    }
    return m_dispatcher->getExtraConnection(dc);
}

void CTelegramModule::onConnectionAuthChanged(CTelegramConnection *connection, int newState)
{
    Q_UNUSED(connection)
    Q_UNUSED(newState)
}

void CTelegramModule::onNewConnection(CTelegramConnection *connection)
{
    Q_UNUSED(connection)
}

quint64 CTelegramModule::sendMedia(const Telegram::Peer &peer, const TLInputMedia &media)
{
    return m_dispatcher->sendMedia(peer, media);
}

bool CTelegramModule::getUserInfo(Telegram::UserInfo *userInfo, quint32 userId) const
{
    return m_dispatcher->getUserInfo(userInfo, userId);
}

bool CTelegramModule::getChatInfo(Telegram::ChatInfo *outputChat, const Telegram::Peer &peer) const
{
    return m_dispatcher->getChatInfo(outputChat, peer);
}

bool CTelegramModule::getChatParticipants(QVector<quint32> *participants, quint32 chatId)
{
    return m_dispatcher->getChatParticipants(participants, chatId);
}

const TLUser *CTelegramModule::getUser(quint32 userId) const
{
    return m_dispatcher->getUser(userId);
}

const TLChat *CTelegramModule::getChat(const Telegram::Peer &peer) const
{
    return m_dispatcher->getChat(peer);
}

const TLMessage *CTelegramModule::getMessage(quint32 messageId) const
{
    return m_dispatcher->getMessage(messageId);
}

TLInputPeer CTelegramModule::toInputPeer(const Telegram::Peer &peer) const
{
    return m_dispatcher->toInputPeer(peer);
}

Telegram::Peer CTelegramModule::toPublicPeer(const TLInputPeer &inputPeer) const
{
    return m_dispatcher->toPublicPeer(inputPeer);
}

Telegram::Peer CTelegramModule::toPublicPeer(const TLPeer &peer) const
{
    return m_dispatcher->toPublicPeer(peer);
}

TLInputUser CTelegramModule::toInputUser(quint32 id) const
{
    return m_dispatcher->toInputUser(id);
}
