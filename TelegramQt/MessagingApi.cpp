#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "DataStorage.hpp"
#include "DataStorage_p.hpp"
#include "DialogList.hpp"
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
    const DataInternalApi *dataApi = DataInternalApi::get(dataStorage());

    int flags = 0;
    if (options.clearDraft()) {
        // flags |= 1 << 1 for noWebpage "true" value
        // flags |= 1 << 5 for silent "true" value
        // flags |= 1 << 6 for background "true" value
        flags |= 1 << 7; // clearDraft
    }

    const TLInputPeer inputPeer = dataApi->toInputPeer(peer);
    const quint64 randomId = Utils::randomBytes<quint64>();
    MessagesRpcLayer::PendingUpdates *rpcOperation = messagesLayer()->sendMessage(flags, inputPeer, options.replyToMessageId(),
                                                                                  message, randomId, TLReplyMarkup(), {});
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onMessageSendResult, randomId, rpcOperation);
    return randomId;
}

void MessagingApiPrivate::onMessageSendResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation)
{
    Q_Q(MessagingApi);
    TLUpdates result;
    rpcOperation->getResult(&result);

    for (const TLUpdate &u : result.updates) {
        if (u.tlType == TLValue::UpdateMessageID) {
            if (u.randomId == randomMessageId) {
                emit q->messageSent(randomMessageId, u.quint32Id);
                return;
            }
        }
    }

    qWarning() << Q_FUNC_INFO << "Expected message id update is missing";
}

void MessagingApiPrivate::onMessageReceived(const TLMessage &message)
{
    Q_Q(MessagingApi);
    const Telegram::Peer peer = Telegram::Utils::getMessagePeer(message, dataStorage()->selfUserId());
    if (m_dialogList) {
        m_dialogList->ensurePeer(peer);
    }
    emit q->messageReceived(peer, message.id);
}

PendingOperation *MessagingApiPrivate::getDialogs()
{
    PendingOperation *operation = new PendingOperation(this);
    MessagesRpcLayer::PendingMessagesDialogs *rpcOperation = messagesLayer()->getDialogs(0, 0, 0, TLInputPeer(), 5);
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetDialogsFinished, operation, rpcOperation);
    return operation;
}

MessagesOperation *MessagingApiPrivate::getHistory(const Peer peer, quint32 limit)
{
    if (!peer.isValid()) {
        return PendingOperation::failOperation<MessagesOperation>(QStringLiteral("Invalid peer for getHistory()"), this);
    }
    TLInputPeer p = DataInternalApi::get(dataStorage())->toInputPeer(peer);
    MessagesOperation *operation = new MessagesOperation(this);
    MessagesRpcLayer::PendingMessagesMessages *rpcOperation = messagesLayer()->getHistory(p, 0, 0, 0, limit, 0, 0, 0);
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetHistoryFinished, operation, rpcOperation);
    return operation;
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
MessagesOperation *MessagingApi::getHistory(const Telegram::Peer peer, quint32 limit)
{
    Q_D(MessagingApi);
    return d->getHistory(peer, limit);
}

void MessagingApi::setDraftMessage(const Peer peer, const QString &text)
{

}

quint64 MessagingApi::sendMessage(const Peer peer, const QString &message, const SendOptions &options)
{
    Q_D(MessagingApi);
    return d->sendMessage(peer, message, options);
}

void MessagingApi::setMessageAction(const Peer peer, TelegramNamespace::MessageAction action)
{

}

void MessagingApi::setMessageRead(const Peer peer, quint32 messageId)
{

}

DataStorage *MessagingApiPrivate::dataStorage()
{
    return m_backend->dataStorage();
}

MessagesRpcLayer *MessagingApiPrivate::messagesLayer()
{
    return m_backend->messagesLayer();
}

void MessagingApiPrivate::onGetDialogsFinished(PendingOperation *operation, MessagesRpcLayer::PendingMessagesDialogs *rpcOperation)
{
    TLMessagesDialogs dialogs;
    rpcOperation->getResult(&dialogs);
    DataInternalApi::get(dataStorage())->processData(dialogs);
    operation->setFinished();
}

void MessagingApiPrivate::onGetHistoryFinished(MessagesOperation *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation)
{
    TLMessagesMessages messages;
    rpcOperation->getResult(&messages);

    MessagesOperationPrivate *priv = MessagesOperationPrivate::get(operation);

    DataInternalApi::get(dataStorage())->processData(messages);

    priv->m_messages.reserve(messages.messages.count());
    for (const TLMessage &m : messages.messages) {
        priv->m_messages.append(m.id);
    }
    operation->setFinished();
}

MessagingApi::SendOptions::SendOptions() :
    m_replyMessageId(0),
    m_clearDraft(true)
{
}

} // Client namespace

} // Telegram namespace
