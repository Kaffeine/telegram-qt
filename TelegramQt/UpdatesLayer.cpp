#include "UpdatesLayer.hpp"

#include "ClientBackend.hpp"

#include "TLTypesDebug.hpp"

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
    qCDebug(c_updatesLoggingCategory) << "updates:" << updates;

    switch (updates.tlType) {
    case TLValue::UpdatesTooLong:
    case TLValue::UpdateShortMessage:
    case TLValue::UpdateShortChatMessage:
    case TLValue::UpdateShort:
    case TLValue::UpdatesCombined:
    case TLValue::Updates:
    case TLValue::UpdateShortSentMessage:
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
    default:
        break;
    }

    return false;
}

} // Client namespace

} // Telegram namespace
