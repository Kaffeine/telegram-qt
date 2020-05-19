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
#include <QTimer>

Q_LOGGING_CATEGORY(lcMessagingApi, "telegram.client.api.messaging", QtWarningMsg)

namespace Telegram {

class PendingOperation;

namespace Client {

static constexpr quint32 c_fetchLimit = 10;
static constexpr quint32 c_dialogsFetchPortion = 20;
static constexpr quint32 c_defaultSyncLimit = 50;

const char *MessagingApi::messageActionIntervalEnvironmentVariableName()
{
    return MessagingApiPrivate::messageActionIntervalVarName();
}

const char *MessagingApiPrivate::messageActionIntervalVarName()
{
    return "TELEGRAM_MESSAGE_ACTION_DURATION";
}

quint32 MessagingApiPrivate::getMessageRepeatInterval()
{
    if (qEnvironmentVariableIsSet(messageActionIntervalVarName())) {
        int value = qEnvironmentVariableIntValue(messageActionIntervalVarName());
        if (value) {
            return static_cast<quint32>(value);
        }
    }
    return 5000; // 5 seconds
}

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
    Q_Q(MessagingApi);
    DataInternalApi *dataApi = dataInternalApi();

    quint32 flags = 0;
    if (options.isSilent()) {
        flags |= 1 << 5;
    }
    if (options.clearDraft()) {
        // flags |= 1 << 1 for noWebpage "true" value
        // flags |= 1 << 6 for background "true" value
        flags |= 1 << 7; // clearDraft
    }

    const TLInputPeer inputPeer = dataApi->toInputPeer(peer);
    const quint64 randomId = dataApi->enqueueMessage(peer, message, options.replyToMessageId());
    emit q->messageEnqueued(peer, randomId, message, options);

    MessagesRpcLayer::PendingUpdates *rpcOperation = messagesLayer()->sendMessage(flags, inputPeer, options.replyToMessageId(),
                                                                                  message, randomId, TLReplyMarkup(), {});
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onSendMessageResult, randomId, rpcOperation);
    return randomId;
}

void MessagingApiPrivate::setMessageRead(const Peer peer, quint32 messageId)
{
    DataInternalApi *dataApi = dataInternalApi();
    dataApi->enqueueMessageRead(peer, messageId);

    if (peer.type() == Peer::Channel) {
        const TLInputChannel inputChannel = dataApi->toInputChannel(peer.id());
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

void MessagingApiPrivate::setMessageAction(const Peer peer, const MessageAction &action)
{
    if (!peer.isValid()) {
        qCWarning(lcMessagingApi) << __func__ << "Invalid peer";
        return;
    }
    TLInputPeer inputPeer = dataInternalApi()->toInputPeer(peer);
    TLSendMessageAction act = Telegram::Utils::toTL(action);

    messagesLayer()->setTyping(inputPeer, act);
}

void MessagingApiPrivate::processMessageAction(const Peer peer, quint32 userId, const MessageAction &action)
{
    Q_Q(MessagingApi);
    const int index = UserMessageAction::findInVector(m_currentMessageActions, peer, userId);
    if (action.type == MessageAction::None) {
        if (index >= 0) {
            m_currentMessageActions.removeAt(index);
        }

        emit q->messageActionChanged(peer, userId, action);
        return;
    }

    if (!m_messageActionTimer) {
        m_messageActionTimer = new QTimer(this);
        m_messageActionTimer->setSingleShot(true);
        connect(m_messageActionTimer, &QTimer::timeout, this, &MessagingApiPrivate::onMessageActionTimerTimeout);
    }

    UserMessageAction *storedAction = nullptr;
    if (index >= 0) {
        storedAction = &m_currentMessageActions[index];
        if ((storedAction->type == action.type) && (storedAction->progress == action.progress)) {
            // No changes
            storedAction->remainingTime = static_cast<int>(MessagingApi::messageActionValidPeriod());
            return;
        }
    } else {
        m_currentMessageActions.append(UserMessageAction(peer, userId));
        storedAction = &m_currentMessageActions.last();
    }

    storedAction->type = action.type;
    storedAction->progress = action.progress;
    storedAction->remainingTime = static_cast<int>(MessagingApi::messageActionValidPeriod());

    if (!m_messageActionTimer->isActive()) {
        m_messageActionTimer->start(storedAction->remainingTime);
    }

    emit q->messageActionChanged(peer, userId, action);
}

void MessagingApiPrivate::onChatCreatedResult(MessagesRpcLayer::PendingUpdates *rpcOperation)
{
    TLUpdates result;
    rpcOperation->getResult(&result);

    backend()->updatesApi()->processUpdates(result);
}

void MessagingApiPrivate::onSendMessageResult(quint64 randomMessageId, MessagesRpcLayer::PendingUpdates *rpcOperation)
{
    TLUpdates result;
    rpcOperation->getResult(&result);
    m_expectedRandomMessageId = randomMessageId;
    backend()->updatesApi()->processUpdates(result);
    if (m_expectedRandomMessageId) {
        // onShortSentMessage() was not called
        qCWarning(lcMessagingApi) << __func__
                                  << "The expected messageId was not processed during updates";
    }
    m_expectedRandomMessageId = 0;
}

void MessagingApiPrivate::onShortSentMessage(quint32 messageId)
{
    if (!m_expectedRandomMessageId) {
        qCWarning(lcMessagingApi) << __func__ << "Unexpected message" << messageId;
        return;
    }
    onSentMessageIdResolved(m_expectedRandomMessageId, messageId);
    m_expectedRandomMessageId = 0;
}

void MessagingApiPrivate::onSentMessageIdResolved(quint64 randomMessageId, quint32 messageId)
{
    Q_Q(MessagingApi);
    if (!randomMessageId) {
        qCWarning(lcMessagingApi) << __func__ << "Message randomId is missing";
        return;
    }

    if (!messageId) {
        qCWarning(lcMessagingApi) << __func__ << "Message id is missing";
        return;
    }

    const DataInternalApi::SentMessage sentMessage = dataInternalApi()->dequeueMessage(randomMessageId, messageId);
    if (sentMessage.randomId != randomMessageId) {
        qCDebug(lcMessagingApi) << "Sent message ID not found in the local queue" << randomMessageId;
        return;
    }
    // TODO: Check the correctess
    DialogState *state = ensureDialogSyncState(sentMessage.peer);
    state->syncedMessageId = messageId;

    emit q->messageSent(sentMessage.peer, randomMessageId, messageId);
}

void MessagingApiPrivate::onMessageReceived(const TLMessage &message)
{
    Q_Q(MessagingApi);
    const Telegram::Peer peer = Telegram::Utils::getMessageDialogPeer(message, m_backend->dataStorage()->selfUserId());

    if (m_dialogList) {
        m_dialogList->ensurePeers({peer});
    }

    if (m_syncMode != MessagingApi::NoSync) {
        if (syncAndFilterMessage(peer, message.id)) {
            return;
        }
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

void MessagingApiPrivate::onUserActionChanged(quint32 userId, const TLSendMessageAction &action)
{
    processMessageAction(Peer::fromUserId(userId), userId, Utils::toPublic(action));
}

void MessagingApiPrivate::onChatUserActionChanged(const Peer peer, quint32 userId, const TLSendMessageAction &action)
{
    processMessageAction(peer, userId, Utils::toPublic(action));
}

PendingOperation *MessagingApiPrivate::getDialogs()
{
    PendingOperation *operation = new PendingOperation(this);
    operation->setOperationName("MessagingApi::getDialogs");
    MessagesRpcLayer::PendingMessagesDialogs *rpcOperation = messagesLayer()->getDialogs(0, 0, 0, TLInputPeer(), c_dialogsFetchPortion);
    dataInternalApi()->clearPinnedDialogs();
    rpcOperation->connectToFinished(this, &MessagingApiPrivate::onGetDialogsFinished, operation, rpcOperation);
    return operation;
}

PendingMessages *MessagingApiPrivate::getHistory(const Peer peer, const MessageFetchOptions &options)
{
    if (!peer.isValid()) {
        return PendingOperation::failOperation<PendingMessages>(QLatin1String("Invalid peer for getHistory()"), this);
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

PendingOperation *MessagingApiPrivate::createChat(const QString &title, const QVector<quint32> &contacts)
{
    TLVector<TLInputUser> users;
    for (quint32 userId : contacts) {
        TLInputUser inputUser = dataInternalApi()->toInputUser(userId);
        if (inputUser.tlType == TLValue::InputUserEmpty) {
            const QString text = QLatin1String("Invalid contact for createChat()");
            return PendingOperation::failOperation<PendingOperation>(text, this);
        }
        users.append(inputUser);
    }

    //const QString text = QLatin1String("Not implemented");
    //return PendingOperation::failOperation<PendingOperation>(text, this);

    MessagesRpcLayer::PendingUpdates *rpcOp = messagesLayer()->createChat(users, title);
    rpcOp->connectToFinished(this, &MessagingApiPrivate::onChatCreatedResult, rpcOp);
    return rpcOp;
}

/*!
    \class Telegram::Client::MessagingApi
    \brief Provides an API to work with messages
    \inmodule TelegramQt
    \ingroup Client

    \section1 Message synchronization

    The idea is to store the top message id of each dialog and use them to get messages since
    the last connection. New messages received during the synchronization are held until
    the history is fetched.

    \note The dialogs state is stored in DataStorage internals and should be saved/loaded
    via appropriate interface. See DataStorage documentation for details.

    The synchronization process is expected to go as follows:

    \list
        \li The initial (internal) state is "sync not started".
        \li The application sets synchorization mode to ManualSync.
        \li The application uses DataStorage API to load the previous synchorization state.
            The state includes the top message ID for each dialog.
        \li The application initiates the connection and waits until the ConnectionApi::status
            becomes ConnectionApi::StatusReady.
        \li The application can optionaly get DialogList or ContactList.
        \li The application connects to MessagingApi::syncMessagesReceived() signal to receive the
            per peer list of messages added since the last synchronization.
        \li The application calls MessagingApi::syncPeers() the list of the interesting peers as
            argument. The typical use-case is to pass all peers from the DialogList or ContactList.
        \li The internal state become "sync started" on syncPeers() called.
        \li For each peer the MessagingApi marks the "dialog sync state" as "not synchronized".
        \li For each peer the MessagingApi processes the top dialog message via the internal sync
            API call.
        \li On each call the API decides to either initiate further fetching or mark the dialog as
            synced.
        \li For each further fetching result the MessagingAPI makes the same internal sync API call.
        \li For each synced dialog the MessagingAPI emits MessagingApi::syncMessagesReceived()
            signal with the synced \c peer and the list of the synced messages.
        \li If a new message received during the synchronization then if the dialog was asked for
            synchronization (in other words: if the syncPeers() argument contains the new message
            peer) and was not synced yet, then the MessagingAPI inserts the new message into the
            list of messages received during the peer synchronization (so the message will be listed
            in the MessagingApi::syncMessagesReceived() signal arguments).
            The message will trigger the usual messageReceived() in all other cases.
        \li The sync is done once all requested dialogs synced.
        \li The internal state become "sync finished".
    \endlist

    The internal sync API processes fetched messages as the follows:
    \list
        \li For each feed the API picks up all messages newer than the loaded dialog top message ID
            and adds them to the dialog pending IDs list.
        \li If there are no messages or the oldest message ID equals 1 or the oldest message ID is
            less or equal to the the previously completed (loaded) dialog sync ID, then the dialog
            considered as "fetched".
        \li If the syncLimit is set and the dialog pending IDs list has more than syncLimit
            elements, then the dialog fetch limit considered as exceeded.
        \li If the dialog is fetched or the fetch limit exceeded, then the dialog considered as
            "synchronized".
        \li The MessagingApi emits syncMessagesReceived() signal on dialog synchronized and clears
            the dialog pending messages.
    \endlist

    \sa MessagingApi::syncLimit()
    \sa InMemoryDataStorage::loadState()
    \sa InMemoryDataStorage::saveState()
 */
MessagingApi::MessagingApi(QObject *parent) :
    ClientApi(parent)
{
    d = new MessagingApiPrivate(this);

    // Wire up the deprecated signals
    connect(this, &MessagingApi::syncMessagesReceived, this, &MessagingApi::syncMessages);
}

/*!
    Returns the lifetime of message action status.

    The documentation says that the status is valid for 6 seconds.

    \sa https://core.telegram.org/constructor/updateUserTyping
*/
quint32 MessagingApi::messageActionValidPeriod()
{
    static quint32 period = messageActionRepeatInterval() / 5 * 6;
    return period;
}

/*!
    Returns the recommended interval of message action repeat calls.

    The documentation recommendeds to repeat the status every 5 seconds.

    \sa https://core.telegram.org/method/messages.setTyping
*/
quint32 MessagingApi::messageActionRepeatInterval()
{
    static quint32 period = MessagingApiPrivate::getMessageRepeatInterval();
    return period;
}

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
    qCDebug(lcMessagingApi) << __func__ << "Sync started for peers" << peers;
    m_syncState = SyncState::InProgress;

    m_syncOperation = new PendingOperation(this);
    m_syncOperation->setOperationName("SyncOperation");
    m_syncJobs = peers.count();

    for (const Telegram::Peer &peer : peers) {
        Telegram::DialogInfo info;
        dataStorage()->getDialogInfo(&info, peer);
        processNewSyncMessages(peer, {info.lastMessageId()});
    }

    checkIfSyncFinished();

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

quint32 MessagingApi::selfUserId() const
{
    Q_D(const MessagingApi);
    return d->dataStorage()->selfUserId();
}

DialogList *MessagingApi::getDialogList()
{
    Q_D(MessagingApi);

    if (!d->m_dialogList) {
        d->m_dialogList = new DialogList(this);
    }
    return d->m_dialogList;
}

bool MessagingApi::getDialogInfo(DialogInfo *info, const Peer &peer) const
{
    Q_D(const MessagingApi);
    return d->dataStorage()->getDialogInfo(info, peer);
}

Namespace::ChatType MessagingApi::getChatType(const Peer &peer) const
{
    Q_D(const MessagingApi);
    return d->dataStorage()->getChatType(peer);
}

/*!
    Returns PendingMessages with messages sorted from newer (higher message id) to older (lower message id)
*/
PendingMessages *MessagingApi::getHistory(const Telegram::Peer peer, const MessageFetchOptions &options)
{
    Q_D(MessagingApi);
    return d->getHistory(peer, options);
}

PendingOperation *MessagingApi::createChat(const QString &title, const QVector<quint32> &contacts)
{
    Q_D(MessagingApi);
    return d->createChat(title, contacts);
}

bool MessagingApi::getMessage(Message *message, const Peer &peer, quint32 messageId)
{
    Q_D(MessagingApi);
    return d->dataStorage()->getMessage(message, peer, messageId);
}

bool MessagingApi::getMessageMediaInfo(MessageMediaInfo *info, const Peer &peer, quint32 messageId)
{
    Q_D(MessagingApi);
    return d->dataStorage()->getMessageMediaInfo(info, peer, messageId);
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

void MessagingApi::setMessageAction(const Peer peer, const Telegram::MessageAction &action)
{
    Q_D(MessagingApi);
    return d->setMessageAction(peer, action);
}

void MessagingApi::readHistory(const Peer peer, quint32 messageId)
{
    Q_D(MessagingApi);
    return d->setMessageRead(peer, messageId);
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
        qCWarning(lcMessagingApi) << __func__ << this << peer << messageId << "failed" << rpcOperation->errorDetails();
        return;
    }

    TLMessagesAffectedMessages result;
    rpcOperation->getResult(&result);
    onHistoryReadSucceeded(peer, messageId);
}

void MessagingApiPrivate::onReadChannelHistoryFinished(const Peer peer, quint32 messageId, ChannelsRpcLayer::PendingBool *rpcOperation)
{
    if (!rpcOperation->isSucceeded()) {
        qCWarning(lcMessagingApi) << __func__ << this << peer << messageId << "failed" << rpcOperation->errorDetails();
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

void MessagingApiPrivate::processNewSyncMessages(const Peer &peer, const QVector<quint32> &messages)
{
    DialogState *state = ensureDialogSyncState(peer);

    if (messages.isEmpty()) {
        qCDebug(lcMessagingApi) << __func__ << "No messages for" << peer;
    } else {
        qCDebug(lcMessagingApi) << __func__ << "Update dialog with" << peer
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

    if (limitIsReached) {
        qCDebug(lcMessagingApi) << __func__ << "Limit reached for peer" << peer;
    }

    if (allMessagesFetched || limitIsReached) {
        onPeerSyncFinished(peer, state);
        return;
    }

    syncMorePeerMessages(peer, state);
}

void MessagingApiPrivate::syncMorePeerMessages(const Peer &peer, const DialogState *state)
{
    MessageFetchOptions options;
    if (!state->pendingIds.isEmpty()) {
        options.offsetId = state->pendingIds.last();
    }

    if (m_syncLimit) {
        // m_syncLimit > pendingIds.count() because of the limitIsReached check
        options.limit = qMin(m_syncLimit - static_cast<quint32>(state->pendingIds.count()), c_fetchLimit);
    } else {
        options.limit = c_fetchLimit;
    }

    if (state->syncedMessageId > 0) {
        options.minId = state->syncedMessageId - 1;
    }

    qCDebug(lcMessagingApi) << __func__ << "Request history for" << peer
             << "offsetId" << options.offsetId
             << "limit" << options.limit
             << "minId" << options.minId
                ;

    PendingMessages *historyOp = getHistory(peer, options);
    historyOp->connectToFinished(this, &MessagingApiPrivate::onSyncHistoryReceived, historyOp);
}

void MessagingApiPrivate::checkIfSyncFinished()
{
    if (m_syncJobs == 0) {
        qCDebug(lcMessagingApi) << __func__ << "Sync finished";
        m_syncState = SyncState::Finished;
        m_syncOperation->finishLater();
    }
}

void MessagingApiPrivate::onPeerSyncFinished(const Peer &peer, DialogState *state)
{
    Q_Q(MessagingApi);

    qCDebug(lcMessagingApi) << __func__ << "Sync complete for peer" << peer;
    state->synced = true;

    if (!state->pendingIds.isEmpty()) {
        state->syncedMessageId = state->pendingIds.constFirst();
        emit q->syncMessagesReceived(peer, state->pendingIds);
        state->pendingIds.clear();
    }

    --m_syncJobs;
}

// Returns true if the message should be filtered out
bool MessagingApiPrivate::syncAndFilterMessage(const Peer &peer, quint32 messageId)
{
    if (m_syncMode == MessagingApi::NoSync) {
        return false;
    }

    qCDebug(lcMessagingApi) << __func__ << "Examine message"  << messageId << "in dialog" << peer;

    // Sync is required...
    if (m_syncState == SyncState::NotStarted) {
        // but not started yet.
        qCDebug(lcMessagingApi) << "Drop message" << messageId << "in dialog"
                                << peer << "(sync not started yet)";
        // Drop all new messages; we'll get those messages later during the sync.
        return true;
    }

    DialogState *state = ensureDialogSyncState(peer);
    if (!state->isValid()) {
        // This is a new dialog and the sync is either InProgress or Finished.
        // Maybe we would like to fetch all messages, but just process the dialog as synced for now.
        qCDebug(lcMessagingApi) << __func__ << "mark" << peer << "as synced";
        state->synced = true;
    }

    if (!state->synced) {
        // SyncState is InProgress and the dialog sync is not finished yet.
        qCDebug(lcMessagingApi) << __func__ << "prepend message" << messageId << "for peer" << peer;
        state->pendingIds.prepend(messageId);
        return true;
    }

    const quint32 previousSyncedMessageId = state->syncedMessageId;
    state->syncedMessageId = messageId;
    qCDebug(lcMessagingApi) << __func__ << "change syncedMessageId from" << previousSyncedMessageId
                            << "to" << messageId << "for peer" << peer;
    return false;
}

DialogState *MessagingApiPrivate::ensureDialogSyncState(const Peer &peer)
{
    QHash<Peer, DialogState> *dialogStates = dataInternalApi()->dialogStates();
    QHash<Peer, DialogState> &statesRef = *dialogStates;

    if (!statesRef.contains(peer)) {
        qDebug() << CALL_INFO << "New dialog" << peer;
        statesRef.insert(peer, DialogState());
    }
    return &statesRef[peer];
}

void MessagingApiPrivate::onSyncHistoryReceived(PendingMessages *op)
{
    op->deleteLater();

    processNewSyncMessages(op->peer(), op->messages());
    checkIfSyncFinished();
}

void MessagingApiPrivate::onMessageActionTimerTimeout()
{
    Q_Q(MessagingApi);
    int minTime = static_cast<int>(MessagingApi::messageActionValidPeriod());

    for (int i = m_currentMessageActions.count() - 1; i >= 0; --i) {
        UserMessageAction *action = &m_currentMessageActions[i];
        int remainingTime = action->remainingTime - m_messageActionTimer->interval();
        if (remainingTime < 15) { // Consider 15 ms as an acceptable deviation
            const Peer peer = action->peer;
            const quint32 userId = action->userId;
            m_currentMessageActions.remove(i);

            emit q->messageActionChanged(peer, userId, Telegram::MessageAction::None);
        } else {
            m_currentMessageActions[i].remainingTime = remainingTime;
            if (minTime > remainingTime) {
                minTime = remainingTime;
            }
        }
    }

    if (!m_currentMessageActions.isEmpty()) {
        m_messageActionTimer->start(minTime);
    }
}

MessagingApi::SendOptions::SendOptions() :
    m_clearDraft(true)
{
}

} // Client namespace

} // Telegram namespace
