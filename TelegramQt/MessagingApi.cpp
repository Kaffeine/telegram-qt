#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "DataStorage.hpp"
#include "DataStorage_p.hpp"
#include "DialogList.hpp"
#include "Utils.hpp"

#include "Operations/ClientMessagesOperation.hpp"

#include <QLoggingCategory>

const int s_userTypingActionPeriod = 6000; // 6 sec
const int s_localTypingDuration = 5000; // 5 sec
const int s_localTypingRecommendedRepeatInterval = 400; // (s_userTypingActionPeriod - s_localTypingDuration) / 2. Minus 100 ms for insurance.

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
    const DataInternalApi *dataApi = dataStorage()->internalApi();

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
    connect(rpcOperation, &PendingOperation::finished, this,
            [this, randomId, rpcOperation]() { this->onMessageSendResult(randomId, rpcOperation); }
    );

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
    connect(rpcOperation, &PendingOperation::finished, this,
            [this, operation, rpcOperation]() { this->onGetDialogsFinished(operation, rpcOperation); }
    );
    return operation;
}

MessagingApi::MessagingApi(QObject *parent) :
    ClientApi(parent)
{
    d = new MessagingApiPrivate(this);
}

quint32 MessagingApi::localTypingRecommendedRepeatInterval()
{
    return s_localTypingRecommendedRepeatInterval;
}

DialogList *MessagingApi::getDialogList()
{
    Q_D(MessagingApi);

    if (!d->m_dialogList) {
        d->m_dialogList = new DialogList(this);
    }
    return d->m_dialogList;
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
    dataStorage()->internalApi()->processData(dialogs);
    operation->setFinished();
}

MessagingApi::SendOptions::SendOptions() :
    m_replyMessageId(0),
    m_clearDraft(true)
{
}

} // Client namespace

} // Telegram namespace
