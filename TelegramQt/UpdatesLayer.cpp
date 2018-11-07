#include "UpdatesLayer.hpp"

#include "ClientBackend.hpp"
#include "DataStorage.hpp"
#include "MessagingApi.hpp"
#include "MessagingApi_p.hpp"

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
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
                shortMessage.fromId = dataStorage()->internalApi()->selfUserId();
            } else {
                shortMessage.toId.userId = dataStorage()->internalApi()->selfUserId();
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
        qCDebug(c_updatesLoggingCategory) << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        for (int i = 0; i < updates.updates.count(); ++i) {
            processUpdate(updates.updates.at(i));
        }
        break;
    case TLValue::Updates:
        dataStorage()->internalApi()->processData(updates.users);
        dataStorage()->internalApi()->processData(updates.chats);

        if (!updates.updates.isEmpty()) {
            // Official client sorts updates by pts/qts. Wat?!
            // Ok, let's see if there would be unordered updates.
            quint32 pts = updates.updates.first().pts;
            for (int i = 0; i < updates.updates.count(); ++i) {
                if (updates.updates.at(i).pts < pts) {
                    qCCritical(c_updatesLoggingCategory) << "Unordered update!";
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
        qCDebug(c_updatesLoggingCategory) << Q_FUNC_INFO << "UpdateShortSentMessage processing is not implemented yet.";
        break;
    default:
        break;
    }
    return false;
}

bool UpdatesInternalApi::processUpdate(const TLUpdate &update)
{
#ifdef DEVELOPER_BUILD
    qCDebug(c_updatesLoggingCategory) << Q_FUNC_INFO << update;
#endif

    switch (update.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
    {
        dataStorage()->internalApi()->processData(update.message);

        MessagingApiPrivate *messaging = MessagingApiPrivate::get(messagingApi());
        messaging->onMessageReceived(update.message);
    }
        break;
    default:
        break;
    }

    return false;
}

MessagingApi *UpdatesInternalApi::messagingApi()
{
    return m_backend->messagingApi();
}

DataStorage *UpdatesInternalApi::dataStorage()
{
    return m_backend->dataStorage();
}

} // Client namespace

} // Telegram namespace
