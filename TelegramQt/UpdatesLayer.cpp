#include "UpdatesLayer.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "ContactsApi_p.hpp"
#include "DataStorage.hpp"
#include "DataStorage_p.hpp"
#include "MessagingApi_p.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_updatesLoggingCategory, "telegram.client.updates", QtWarningMsg)

namespace Telegram {

namespace Client {

UpdatesInternalApi::UpdatesInternalApi(QObject *parent) :
    QObject(parent)
{
}

void UpdatesInternalApi::setBackend(Backend *backend)
{
    m_backend = backend;
}

bool UpdatesInternalApi::processUpdates(const TLUpdates &updates)
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_updatesLoggingCategory) << "updates:" << updates;
#else
    qCDebug(c_updatesLoggingCategory) << "updates:" << updates.tlType << updates.updates.count();
#endif

    DataInternalApi *internal = dataInternalApi();

    switch (updates.tlType) {
    case TLValue::UpdatesTooLong:
        qCDebug(c_updatesLoggingCategory) << "Updates too long!";
        break;
    case TLValue::UpdateShortMessage:
    case TLValue::UpdateShortChatMessage:
    {
        // Reconstruct full update from this short update.
        TLUpdate update;

        if (update.message.toId.channelId) {
            update.tlType = TLValue::UpdateNewChannelMessage;
        } else {
            update.tlType = TLValue::UpdateNewMessage;
        }
        update.pts = updates.pts;
        update.ptsCount = updates.ptsCount;
        TLMessage &shortMessage = update.message;
        shortMessage.tlType = TLValue::Message;
        shortMessage.id = updates.id;
        shortMessage.flags = updates.flags;
        shortMessage.message = updates.message;
        shortMessage.date = updates.date;
        shortMessage.media.tlType = TLValue::MessageMediaEmpty;
        shortMessage.fwdFrom = updates.fwdFrom;
        shortMessage.replyToMsgId = updates.replyToMsgId;

        if (updates.tlType == TLValue::UpdateShortMessage) {
            shortMessage.toId.tlType = TLValue::PeerUser;

            if (shortMessage.out()) {
                shortMessage.toId.userId = updates.userId;
                shortMessage.fromId = internal->selfUserId();
            } else {
                shortMessage.toId.userId = internal->selfUserId();
                shortMessage.fromId = updates.userId;
            }
        } else {
            shortMessage.toId.tlType = TLValue::PeerChat;
            shortMessage.toId.chatId = updates.chatId;

            shortMessage.fromId = updates.fromId;
        }

        processUpdate(update);
    }
        break;
    case TLValue::UpdateShort:
        processUpdate(updates.update);
        break;
    case TLValue::UpdatesCombined:
        internal->processData(updates.users);
        internal->processData(updates.chats);
        qCDebug(c_updatesLoggingCategory) << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        for (int i = 0; i < updates.updates.count(); ++i) {
            processUpdate(updates.updates.at(i));
        }
        break;
    case TLValue::Updates:
        internal->processData(updates.users);
        internal->processData(updates.chats);

        if (!updates.updates.isEmpty()) {
            // Official client sorts updates by pts/qts. Wat?!
            // Ok, let's see if there would be unordered updates.
            quint32 pts = updates.updates.first().pts;
            for (int i = 0; i < updates.updates.count(); ++i) {
                const quint32 updatePts = updates.updates.at(i).pts;
                if (updatePts == 0) {
                    continue;
                }
                if (updatePts < pts) {
                    qCDebug(c_updatesLoggingCategory) << "Unordered update!";
                    //Q_ASSERT(0);
                }
                pts = updates.updates.at(i).pts;
            }

            // Initial implementation
            for (int i = 0; i < updates.updates.count(); ++i) {
                processUpdate(updates.updates.at(i));
            }
        }
        break;
    case TLValue::UpdateShortSentMessage:
    {
        messagingApi()->onShortSentMessage(updates.id);
        // TODO: Check that the follow state update is the right thing to do.
        // This fixes scenario: "send sendMessage" -> "receive UpdateShortSentMessage" -> "receive UpdateReadHistoryOutbox with update.pts == m_updatesState.pts + 2"
        // setUpdateState(m_updatesState.pts + 1, 0, 0);
        return true;
    }
        break;
    default:
        break;
    }
    return false;
}

bool UpdatesInternalApi::processUpdate(const TLUpdate &update)
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_updatesLoggingCategory) << __func__ << update.tlType;
#endif
    switch (update.tlType) {
    case TLValue::UpdateMessageID:
        messagingApi()->onSentMessageIdResolved(update.randomId, update.quint32Id);
        return true;
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
        if (dataInternalApi()->processNewMessage(update.message, update.pts)) {
            messagingApi()->onMessageReceived(update.message);
        }
        return true;
    case TLValue::UpdateReadHistoryInbox:
        processReadInbox(Utils::toPublicPeer(update.peer), update.maxId);
        return true;
    case TLValue::UpdateReadHistoryOutbox:
        processReadOutbox(Utils::toPublicPeer(update.peer), update.maxId);
        return true;
    case TLValue::UpdateReadChannelInbox:
        processReadInbox(Peer::fromChannelId(update.channelId), update.maxId);
        return true;
    case TLValue::UpdateReadChannelOutbox:
        processReadOutbox(Peer::fromChannelId(update.channelId), update.maxId);
        return true;
    case TLValue::UpdateUserStatus:
        contactsApi()->onUserStatusChanged(update.userId, update.status);
        return true;
    case TLValue::UpdateUserTyping:
        messagingApi()->onUserActionChanged(update.userId, update.action);
        return true;
    case TLValue::UpdateChatUserTyping:
        messagingApi()->onChatUserActionChanged(Peer::fromChatId(update.chatId), update.userId, update.action);
        return true;
    case TLValue::UpdateUserPhoto:
        contactsApi()->onUserPhotoChanged(update.userId, update.photo);
        return true;
    default:
        break;
    }

#ifdef DEVELOPER_BUILD
    qCWarning(c_updatesLoggingCategory) << __func__ << "update" << update << "is ignored";
#endif
    return false;
}

void UpdatesInternalApi::processReadInbox(const Telegram::Peer peer, quint32 maxId)
{
    if (dataInternalApi()->updateInboxRead(peer, maxId)) {
        messagingApi()->onMessageInboxRead(peer, maxId);
    }
}

void UpdatesInternalApi::processReadOutbox(const Telegram::Peer peer, quint32 maxId)
{
    if (dataInternalApi()->updateOutboxRead(peer, maxId)) {
        messagingApi()->onMessageOutboxRead(peer, maxId);
    }
}

MessagingApiPrivate *UpdatesInternalApi::messagingApi()
{
    return MessagingApiPrivate::get(m_backend->messagingApi());
}

ContactsApiPrivate *UpdatesInternalApi::contactsApi()
{
    return ContactsApiPrivate::get(m_backend->contactsApi());
}

DataStorage *UpdatesInternalApi::dataStorage()
{
    return m_backend->dataStorage();
}

DataInternalApi *UpdatesInternalApi::dataInternalApi()
{
    return DataInternalApi::get(dataStorage());
}

} // Client namespace

} // Telegram namespace
