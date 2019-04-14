#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "DataStorage.hpp"
#include "DataStorage_p.hpp"
#include "Debug_p.hpp"
#include "DialogList.hpp"
#include "UpdatesLayer.hpp"
#include "Utils.hpp"

#include "Operations/PendingMessages.hpp"
#include "Operations/PendingMessages_p.hpp"

#include <QLoggingCategory>

namespace Telegram {

class PendingOperation;

namespace Client {

static constexpr quint32 c_fetchLimit = 10;
static constexpr quint32 c_dialogsFetchPortion = 20;
static constexpr quint32 c_defaultSyncLimit = 50;

MessagingApiPrivate::MessagingApiPrivate(MessagingApi *parent) :
    ClientApiPrivate(parent),
    m_syncLimit(c_defaultSyncLimit)
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
    DialogState *state = dataInternalApi()->ensureDialogState(sentMessage.peer);
    state->syncedMessageId = messageId;

    m_expectedRandomMessageId = 0;
    emit q->messageSent(sentMessage.peer, randomMessageId, messageId);
}

void MessagingApiPrivate::onMessageReceived(const TLMessage &message)
{
    Q_Q(MessagingApi);

    if (m_syncMode != MessagingApi::NoSync) {
        if (m_syncState == SyncState::NotStarted) {
            // Drop all new messages if sync is needed but not started yet.
            // We'll get those messages later during the sync.
            return;
        }
    }

    const Telegram::Peer peer = Telegram::Utils::getMessageDialogPeer(message, m_backend->dataStorage()->selfUserId());
    if (m_dialogList) {
        m_dialogList->ensurePeers({peer});
    }

    DialogState *state = dataInternalApi()->ensureDialogState(peer);
    if (m_syncState == SyncState::InProgress) {
        if (state->isValid()) {
            if (!state->synced) {
                state->pendingIds.prepend(message.id);
                return;
            }
        } else {
            state->synced = true;
        }
    } else {
        state->synced = true;
    }
    state->syncedMessageId = message.id;

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
    MessagesRpcLayer::PendingMessagesDialogs *rpcOperation = messagesLayer()->getDialogs(0, 0, 0, TLInputPeer(), c_dialogsFetchPortion);
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetDialogsFinished, operation, rpcOperation);
    return operation;
}

PendingMessages *MessagingApiPrivate::getHistory(const Peer peer, const Telegram::Client::MessageFetchOptions &options)
{
    if (!peer.isValid()) {
        return PendingOperation::failOperation<PendingMessages>(QStringLiteral("Invalid peer for getHistory()"), this);
    }
    TLInputPeer inputPeer = dataInternalApi()->toInputPeer(peer);
    PendingMessages *apiOp = new PendingMessages(this);
    PendingMessagesPrivate *priv = PendingMessagesPrivate::get(apiOp);
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

/*!
    \class Telegram::Client::MessagingApi
    \brief Provides an API to work with messages
    \inmodule TelegramQt
    \ingroup Client
 */
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

/*!
    \brief setSyncMode keeps messages in sync across connections.

    The idea is to get messages since last connection (as scrollback) and hold
    new messages until the dialog history is fetched.

    The dialogs state is stored in DataStorage internals and should be saved/loaded
    via appropriate interface. See DataStorage documentation for details.

    \sa InMemoryDataStorage::loadState()
    \sa InMemoryDataStorage::saveState()

    On dialoglist received: {
        foreach dialog {
            if state[dialog] does not exist {
                processNewDialog(dialog)
                continue
            }
            if dialog.topMessage > state[dialog].syncedId {
                request last N messages newer than state[dialog].syncedId
            } else {
                state[dialog].synced = true
            }
        }
    }

    processNewDialog(dialog): {
        add state[dialog]
        request last N messages from the dialog
    }

    onHistoryReceived: {
        onMessageReceived()
    }

    onMessageReceived: {
        if dialog exists but not synced {
            hold the message
            return
        }

        propogate the message to the appropriate channel
        update state[dialog].syncedId
        schedule save()
    }
 */

void MessagingApi::setSyncMode(MessagingApi::SyncMode mode)
{
    Q_D(MessagingApi);
    d->m_syncMode = mode;
}

PendingOperation *MessagingApiPrivate::syncPeers(const PeerList &peers)
{
    if (m_syncState != SyncState::NotStarted) {
        return PendingOperation::failOperation(QLatin1String("Sync is already triggered"), this);
    }
    m_syncState = SyncState::InProgress;

    m_syncOperation = new PendingOperation("SyncOperation", this);
    m_syncJobs = peers.count();

    for (const Telegram::Peer &peer : peers) {
        Telegram::DialogInfo info;
        dataStorage()->getDialogInfo(&info, peer);
        if (pushBackNewOldMessages(peer, {info.lastMessageId()})) {
            --m_syncJobs;
        }
    }

    if (m_syncJobs == 0) {
        m_syncState = SyncState::Finished;
        m_syncOperation->finishLater();
    }

    return m_syncOperation;
}

PendingOperation *MessagingApi::syncPeers(const PeerList &peers)
{
    Q_D(MessagingApi);
    return d->syncPeers(peers);
}

quint32 MessagingApi::syncLimit() const
{
    Q_D(const MessagingApi);
    return d->m_syncLimit;
}

void MessagingApi::setSyncLimit(quint32 perDialogLimit)
{
    Q_D(MessagingApi);
    d->m_syncLimit = perDialogLimit;
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
    Returns PendingMessages with messages sorted from newer (higher message id) to older (lower message id)
*/
PendingMessages *MessagingApi::getHistory(const Telegram::Peer peer, const MessageFetchOptions &options)
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

quint64 MessagingApi::forwardMessage(const Peer peer, const Peer fromPeer, quint32 messageId)
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
    dataInternalApi()->processPinnedDialogs(dialogs.dialogs);
    rpcOperation->deleteLater();

    if (m_dialogList) {
        PeerList receivedPeers;
        for (const TLDialog &dialog : dialogs.dialogs) {
            receivedPeers.append(Utils::toPublicPeer(dialog.peer));
        }

        m_dialogList->ensurePeers(receivedPeers);
    }

    if (static_cast<quint32>(dataInternalApi()->dialogs().count()) < dialogs.count) {
        const TLDialog &lastTlDialog = dialogs.dialogs.last();
        const TLInputPeer inputPeer = dataInternalApi()->toInputPeer(lastTlDialog.peer);
        quint32 date = 0;
        // Iterate over messages to get the last dialog date
        for (const TLMessage &message : dialogs.messages) {
            if ((message.id == lastTlDialog.topMessage) && (message.toId == lastTlDialog.peer)) {
                date = message.date;
                break;
            }
        }

        quint32 excludePinned = 1;
        rpcOperation = messagesLayer()->getDialogs(excludePinned, date, lastTlDialog.topMessage, inputPeer, c_dialogsFetchPortion);
        rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetDialogsFinished, operation, rpcOperation);
        return;
    }
    operation->setFinished();
}

void MessagingApiPrivate::onGetHistoryFinished(PendingMessages *operation, MessagesRpcLayer::PendingMessagesMessages *rpcOperation)
{
    TLMessagesMessages messages;
    rpcOperation->getResult(&messages);

    PendingMessagesPrivate *priv = PendingMessagesPrivate::get(operation);

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

void MessagingApiPrivate::onSyncHistoryReceived(PendingMessages *op)
{
    if (pushBackNewOldMessages(op->peer(), op->messages())) {
        --m_syncJobs;
    }
    if (m_syncJobs == 0) {
        m_syncState = SyncState::Finished;
        m_syncOperation->finishLater();
    }

    op->deleteLater();
}

bool MessagingApiPrivate::pushBackNewOldMessages(const Peer &peer, const QVector<quint32> &messages)
{
    Q_Q(MessagingApi);
    DialogState *state = dataInternalApi()->ensureDialogState(peer);

    if (messages.isEmpty()) {
        qDebug() << CALL_INFO << "No messages for" << peer;
    } else {
        qDebug() << CALL_INFO << "Update dialog with" << peer
                 << "from" << state->syncedMessageId
                 << "to" << messages.first()
                 << " - " << messages.last();
    }

    // pendingIds starts with newer and ends with older messages
    for (quint32 messageId : messages) {
        if (messageId > state->syncedMessageId) {
            state->pendingIds.append(messageId);
        } else {
            break;
        }
    }

    const bool allMessagesFetched = messages.isEmpty() // No more messages
            || (messages.last() <= state->syncedMessageId)
            || (messages.last() == 1);
    const bool limitIsReached = m_syncLimit
            && (static_cast<quint32>(state->pendingIds.count()) >= m_syncLimit);

    if (allMessagesFetched || limitIsReached) {
        qDebug() << CALL_INFO << "Dialog sync complete for peer" << peer;
        state->synced = true;

        if (!state->pendingIds.isEmpty()) {
            state->syncedMessageId = state->pendingIds.constFirst();
            emit q->syncMessages(peer, state->pendingIds);
            state->pendingIds.clear();
        }
        return true;
    }

    Telegram::Client::MessageFetchOptions options;
    options.offsetId = state->pendingIds.last();
    if (m_syncLimit) {
        // m_syncLimit > pendingIds.count() because of the limitIsReached check
        options.limit = qMin(m_syncLimit - static_cast<quint32>(state->pendingIds.count()), c_fetchLimit);
    } else {
        options.limit = c_fetchLimit;
    }

    if (state->syncedMessageId > 0) {
        options.minId = state->syncedMessageId - 1;
    }

    qDebug() << CALL_INFO << "Request history for" << peer
             << "offsetId" << options.offsetId
             << "limit" << options.limit
             << "minId" << options.minId
                ;

    Telegram::Client::PendingMessages *historyOp = getHistory(peer, options);
    historyOp->connectToFinished(this, &MessagingApiPrivate::onSyncHistoryReceived, historyOp);

    return false;
}

MessagingApi::SendOptions::SendOptions() :
    m_replyMessageId(0),
    m_clearDraft(true)
{
}

} // Client namespace

} // Telegram namespace
