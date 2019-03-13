#include "DeclarativeChatInfo.hpp"

#include "DataStorage.hpp"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(c_qmlLoggingCategory)

namespace Telegram {

namespace Client {

DeclarativeChatInfo::DeclarativeChatInfo(QObject *parent) :
    DeclarativeClientOperator(parent)
{
}

void DeclarativeChatInfo::setPeer(const Peer &peer)
{
    if (m_peer == peer) {
        return;
    }
    m_peer = peer;
    emit peerChanged();

    updateInfo();
}

void DeclarativeChatInfo::setDisplayName(const QString &displayName)
{
    if (m_displayName == displayName) {
        return;
    }
    m_displayName = displayName;
    emit displayNameChanged(displayName);
}

void DeclarativeChatInfo::updateInfo()
{
    if (!client()) {
        qCWarning(c_qmlLoggingCategory) << this << "Client not set!";
        return;
    }
    if (!m_peer.isValid() || (m_peer.type == Peer::User)) {
        setDisplayName(QString());
        return;
    }
    ChatInfo info;
    dataStorage()->getChatInfo(&info, m_peer);
    setDisplayName(info.title());
}

} // Client

} // Telegram
