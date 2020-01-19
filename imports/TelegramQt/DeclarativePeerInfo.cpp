#include "DeclarativePeerInfo.hpp"

#include "DataStorage.hpp"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(c_qmlLoggingCategory)

namespace Telegram {

namespace Client {

DeclarativePeerInfo::DeclarativePeerInfo(QObject *parent) :
    DeclarativeClientOperator(parent)
{
}

void DeclarativePeerInfo::setPeer(const Peer &peer)
{
    if (m_peer == peer) {
        return;
    }
    const Peer previousPeer = m_peer;
    m_peer = peer;
    emit peerChanged();

    if ((previousPeer.type() == Peer::User) || (peer.type() == Peer::User)) {
        emit userIdChanged();
    }

    updateInfo();
}

quint32 DeclarativePeerInfo::userId() const
{
    if (m_peer.type() != Peer::User) {
        return 0;
    }
    return m_peer.id();
}

void DeclarativePeerInfo::setUserId(quint32 userId)
{
    setPeer(Peer::fromUserId(userId));
}

void DeclarativePeerInfo::setDisplayName(const QString &displayName)
{
    if (m_displayName == displayName) {
        return;
    }
    m_displayName = displayName;
    emit displayNameChanged(displayName);
}

void DeclarativePeerInfo::setChatType(Namespace::ChatType chatType)
{
    if (m_chatType == chatType) {
        return;
    }
    m_chatType = chatType;
    emit chatTypeChanged();
}

void DeclarativePeerInfo::setPictureFileId(const QString &fileId)
{
    if (m_pictureFileId == fileId) {
        return;
    }
    m_pictureFileId = fileId;
    emit pictureFileIdChanged();
}

void DeclarativePeerInfo::updateInfo()
{
    if (!client()) {
        qCWarning(c_qmlLoggingCategory) << this << "Client not set!";
        return;
    }
    if (!m_peer.isValid()) {
        setChatType(Namespace::ChatTypeInvalid);
        setDisplayName(QString());
        return;
    }

    if (m_peer.type() == Peer::User) {
        UserInfo info;
        dataStorage()->getUserInfo(&info, m_peer.id());
        setChatType(Namespace::ChatTypeInvalid);
        updateInfo(&info);
    } else {
        ChatInfo info;
        dataStorage()->getChatInfo(&info, m_peer);
        setChatType(dataStorage()->getChatType(m_peer));
        updateInfo(&info);
    }
}

void DeclarativePeerInfo::updateInfo(const PeerInfo *info)
{
    FileInfo file;
    info->getPeerPicture(&file, PeerPictureSize::Small);
    setDisplayName(info->displayName());
    setPictureFileId(file.getFileId());
}

} // Client

} // Telegram
