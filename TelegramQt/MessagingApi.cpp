#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "DataStorage.hpp"
#include "DataStorage_p.hpp"
#include "Debug.hpp"
#include "DialogList.hpp"
#include "UpdatesLayer.hpp"
#include "Utils.hpp"

#include "Operations/ClientMessagesOperation.hpp"
#include "Operations/ClientMessagesOperation_p.hpp"

#include <QLoggingCategory>

namespace Telegram {

class PendingOperation;

namespace Client {

MessagingApiPrivate::MessagingApiPrivate(MessagingApi *parent) :
    ClientApiPrivate(parent)
{
}

MessagingApiPrivate *MessagingApiPrivate::get(MessagingApi *parent)
{
    return static_cast<MessagingApiPrivate*>(parent->d);
}

quint64 MessagingApiPrivate::sendMessage(const Peer peer, const QString &message, const MessagingApi::SendOptions &options)
{
    DataInternalApi *dataApi = dataInternalApi();

    quint32 flags = 0;
    if (options.clearDraft()) {
        // flags |= 1 << 1 for noWebpage "true" value
        // flags |= 1 << 5 for silent "true" value
        // flags |= 1 << 6 for background "true" value
        flags |= 1 << 7; // clearDraft
    }

    const TLInputPeer inputPeer = dataApi->toInputPeer(peer);
    const quint64 randomId = dataApi->enqueueMessage(peer, message, options.replyToMessageId());
    MessagesRpcLayer::PendingUpdates *rpcOperation = messagesLayer()->sendMessage(flags, inputPeer, options.replyToMessageId(),
                                                                                  message, randomId, TLReplyMarkup(), {});
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onMessageSendResult, randomId, rpcOperation);
    return randomId;
}

void MessagingApiPrivate::setMessageRead(const Peer peer, quint32 messageId)
{
    DataInternalApi *dataApi = dataInternalApi();
    dataApi->enqueueMessageRead(peer, messageId);

    if (peer.type == Peer::Channel) {
        const TLInputChannel inputChannel = dataApi->toInputChannel(peer.id);
        ChannelsRpcLayer::PendingBool *rpcOperation = channelsLayer()->readHistory(inputChannel, messageId);
        rpcOperation->connectToFinished(this, &MessagingApiPrivate::onReadChannelHistoryFinished,
                                        peer, messageId, rpcOperation);
    } else {
        const TLInputPeer inputPeer = dataApi->toInputPeer(peer);
        MessagesRpcLayer::PendingMessagesAffectedMessages *rpcOperation = messagesLayer()->readHistory(inputPeer, messageId);
        rpcOperation->connectToFinished(this, &MessagingApiPrivate::onReadHistoryFinished,
                                        peer, messageId, rpcOperation);
    }
}

void MessagingApiPrivate::onMessageSendResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation)
{
    TLUpdates result;
    rpcOperation->getResult(&result);
    m_expectedRandomMessageId = randomMessageId;
    backend()->updatesApi()->processUpdates(result);
    if (m_expectedRandomMessageId) {
        qWarning() << Q_FUNC_INFO << "Expected messageId is missing in updates";
    }
    m_expectedRandomMessageId = 0;
}

void MessagingApiPrivate::onSentMessageIdResolved(quint64 randomMessageId, quint32 messageId)
{
    Q_Q(MessagingApi);
    if (randomMessageId && (randomMessageId != m_expectedRandomMessageId)) {
        qWarning() << Q_FUNC_INFO << "Unexpected random message id."
                   << "Actual:" << randomMessageId << "Expected:" << m_expectedRandomMessageId;
        return;
    }
    randomMessageId = m_expectedRandomMessageId;

    if (!messageId) {
        qWarning() << Q_FUNC_INFO << "Message id is missing";
        return;
    }

    const DataInternalApi::SentMessage sentMessage = dataInternalApi()->dequeueMessage(randomMessageId, messageId);
    if (sentMessage.randomId != randomMessageId) {
        qDebug() << "Sent message ID not found in the local queue" << randomMessageId;
        return;
    }
    m_expectedRandomMessageId = 0;
    emit q->messageSent(sentMessage.peer, randomMessageId, messageId);
}

void MessagingApiPrivate::onMessageReceived(const TLMessage &message)
{
    Q_Q(MessagingApi);
    const Telegram::Peer peer = Telegram::Utils::getMessageDialogPeer(message, m_backend->dataStorage()->selfUserId());
    if (m_dialogList) {
        m_dialogList->ensurePeer(peer);
    }
    emit q->messageReceived(peer, message.id);
}

void MessagingApiPrivate::onMessageInboxRead(const Telegram::Peer peer, quint32 messageId)
{
    Q_Q(MessagingApi);
    emit q->messageReadInbox(peer, messageId);
}

void MessagingApiPrivate::onMessageOutboxRead(const Telegram::Peer peer, quint32 messageId)
{
    Q_Q(MessagingApi);
    emit q->messageReadOutbox(peer, messageId);
}

PendingOperation *MessagingApiPrivate::getDialogs()
{
    PendingOperation *operation = new PendingOperation("MessagingApi::getDialogs", this);
    MessagesRpcLayer::PendingMessagesDialogs *rpcOperation = messagesLayer()->getDialogs(0, 0, 0, TLInputPeer(), 5);
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetDialogsFinished, operation, rpcOperation);
    return operation;
}

MessagesOperation *MessagingApiPrivate::getHistory(const Peer peer, const Telegram::Client::MessageFetchOptions &options)
{
    if (!peer.isValid()) {
        return PendingOperation::failOperation<MessagesOperation>(QStringLiteral("Invalid peer for getHistory()"), this);
    }
    TLInputPeer inputPeer = dataInternalApi()->toInputPeer(peer);
    MessagesOperation *apiOp = new MessagesOperation(this);
    MessagesOperationPrivate *priv = MessagesOperationPrivate::get(apiOp);
    priv->m_peer = peer;
    priv->m_fetchOptions = options;
    MessagesRpcLayer::PendingMessagesMessages *rpcOp = messagesLayer()->getHistory(inputPeer,
                                                                                   options.offsetId,
                                                                                   options.offsetDate,
                                                                                   options.addOffset,
                                                                                   options.limit,
                                                                                   options.maxId,
                                                                                   options.minId,
                                                                                   options.hash);
    rpcOp->connectToFinished(this, &MessagingApiPrivate::onGetHistoryFinished, apiOp, rpcOp);
    return apiOp;
}

MessagingApi::MessagingApi(QObject *parent) :
    ClientApi(parent)
{
    d = new MessagingApiPrivate(this);
}

/*!
    Returns the lifetime of message action status.

    The documentation says that the status is valid for 6 seconds.

    \sa https://core.telegram.org/constructor/updateUserTyping
*/
quint32 MessagingApi::messageActionValidPeriod()
{
    return 6000; // 6 seconds
}

/*!
    Returns the recommended interval of message action repeat calls.

    The documentation recommendeds to repeat the status every 5 seconds.

    \sa https://core.telegram.org/method/messages.setTyping
*/
quint32 MessagingApi::messageActionRepeatInterval()
{
    return 5000; // 5 seconds
}

DialogList *MessagingApi::getDialogList()
{
    Q_D(MessagingApi);

    if (!d->m_dialogList) {
        d->m_dialogList = new DialogList(this);
    }
    return d->m_dialogList;
}

/*!
    Returns pending MessagesOperation with messages sorted from newer (higher message id) to older (lower message id)
*/
MessagesOperation *MessagingApi::getHistory(const Telegram::Peer peer, const Telegram::Client::MessageFetchOptions &options)
{
    Q_D(MessagingApi);
    return d->getHistory(peer, options);
}

void MessagingApi::setDraftMessage(const Peer peer, const QString &text)
{

}

quint64 MessagingApi::sendMessage(const Peer peer, const QString &message, const SendOptions &options)
{
    Q_D(MessagingApi);
    return d->sendMessage(peer, message, options);
}

quint64 Telegram::Client::MessagingApi::forwardMessage(const Telegram::Peer peer, const Telegram::Peer fromPeer, quint32 messageId)
{
    return 0;
}

void MessagingApi::setMessageAction(const Peer peer, TelegramNamespace::MessageAction action)
{

}

void MessagingApi::readHistory(const Peer peer, quint32 messageId)
{
    Q_D(MessagingApi);
    return d->setMessageRead(peer, messageId);
}

DataStorage *MessagingApiPrivate::dataStorage()
{
    return m_backend->dataStorage();
}

DataInternalApi *MessagingApiPrivate::dataInternalApi()
{
    return DataInternalApi::get(m_backend->dataStorage());
}

MessagesRpcLayer *MessagingApiPrivate::messagesLayer()
{
    return m_backend->messagesLayer();
}

ChannelsRpcLayer *MessagingApiPrivate::channelsLayer()
{
    return m_backend->channelsLayer();
}

void MessagingApiPrivate::onGetDialogsFinished(PendingOperation *operation, MessagesRpcLayer::PendingMessagesDialogs *rpcOperation)
{
    TLMessagesDialogs dialogs;
    rpcOperation->getResult(&dialogs);
    dataInternalApi()->processData(dialogs);
    operation->setFinished();
}

void MessagingApiPrivate::onGetHistoryFinished(MessagesOperation *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation)
{
    TLMessagesMessages messages;
    rpcOperation->getResult(&messages);

    MessagesOperationPrivate *priv = MessagesOperationPrivate::get(operation);

    dataInternalApi()->processData(messages);

    priv->m_messages.reserve(messages.messages.count());
    for (const TLMessage &m : messages.messages) {
        priv->m_messages.append(m.id);
    }
    operation->setFinished();
}

void MessagingApiPrivate::onReadHistoryFinished(const Peer peer, quint32 messageId, MessagesRpcLayer::PendingMessagesAffectedMessages *rpcOperation)
{
    if (!rpcOperation->isSucceeded()) {
        qWarning() << Q_FUNC_INFO << this << peer << messageId << "failed" << rpcOperation->errorDetails();
        return;
    }

    TLMessagesAffectedMessages result;
    rpcOperation->getResult(&result);
    onHistoryReadSucceeded(peer, messageId);
}

void MessagingApiPrivate::onReadChannelHistoryFinished(const Peer peer, quint32 messageId, ChannelsRpcLayer::PendingBool *rpcOperation)
{
    if (!rpcOperation->isSucceeded()) {
        qWarning() << Q_FUNC_INFO << this << peer << messageId << "failed" << rpcOperation->errorDetails();
        return;
    }

    TLBool result;
    rpcOperation->getResult(&result);
    onHistoryReadSucceeded(peer, messageId);
}

void MessagingApiPrivate::onHistoryReadSucceeded(const Peer peer, quint32 messageId)
{
    Q_Q(MessagingApi);
    dataInternalApi()->dequeueMessageRead(peer, messageId);

    emit q->messageReadInbox(peer, messageId);
}

MessagingApi::SendOptions::SendOptions() :
    m_replyMessageId(0),
    m_clearDraft(true)
{
}

} // Client namespace

} // Telegram namespace
