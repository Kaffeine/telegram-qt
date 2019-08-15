#include "DeclarativeDialogsModel.hpp"

#include "Client.hpp"
#include "DataStorage_p.hpp"
#include "Debug.hpp"
#include "MessagingApi.hpp"
#include "DialogList.hpp"
#include "PendingOperation.hpp"

#include "DeclarativeClient.hpp"
#include "TelegramNamespace_p.hpp"

#include <QDateTime>

#include <QDebug>

namespace Telegram {

namespace Client {

static const int UserRoleOffset = Qt::UserRole + 1;

DeclarativeDialogsModel::DeclarativeDialogsModel(QObject *parent) :
    DialogsModel(parent)
{
}

QHash<int, QByteArray> DeclarativeDialogsModel::roleNames() const
{
    static const QHash<int, QByteArray> extraRoles {
        { UserRoleOffset + static_cast<int>(Role::Peer), "peer" },
        { UserRoleOffset + static_cast<int>(Role::DisplayName), "displayName" },
        { UserRoleOffset + static_cast<int>(Role::ChatType), "chatType" },
        { UserRoleOffset + static_cast<int>(Role::IsPinned), "isPinned" },
        { UserRoleOffset + static_cast<int>(Role::UnreadMessageCount), "unreadMessageCount" },
        { UserRoleOffset + static_cast<int>(Role::LastMessage), "lastMessage" },
        { UserRoleOffset + static_cast<int>(Role::FormattedLastMessage), "formattedLastMessage" },
        { UserRoleOffset + static_cast<int>(Role::MuteUntil), "muteUntil" },
        { UserRoleOffset + static_cast<int>(Role::MuteUntilDate), "muteUntilDate" },
    };

    return extraRoles;
}

void DeclarativeDialogsModel::setQmlClient(DeclarativeClient *target)
{
    m_qmlClient = target;
    setClient(DeclarativeClientMixin::client());
    emit clientChanged();
}

DialogsModel::Role DeclarativeDialogsModel::indexToRole(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    if (role >= UserRoleOffset) {
        return intToRole(role - UserRoleOffset);
    }
    return Role::Invalid;
}

int DeclarativeDialogsModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 1;
}

} // Client namespace

} // Telegram namespace
