#ifndef TELEGRAM_DECLARATIVE_PEER_INFO_HPP
#define TELEGRAM_DECLARATIVE_PEER_INFO_HPP

#include "DeclarativeClientOperator.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class TELEGRAMQT_QML_EXPORT DeclarativePeerInfo : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(quint32 userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(Namespace::ChatType chatType READ chatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString pictureFileId READ pictureFileId NOTIFY pictureFileIdChanged)
public:
    explicit DeclarativePeerInfo(QObject *parent = nullptr);

    Telegram::Peer peer() const { return m_peer; }
    quint32 userId() const;
    Namespace::ChatType chatType() const { return m_chatType; }
    QString displayName() const { return m_displayName; }
    QString pictureFileId() const { return m_pictureFileId; }

public slots:
    void setPeer(const Telegram::Peer &peer);
    void setUserId(quint32 userId);

signals:
    void peerChanged();
    void userIdChanged();
    void chatTypeChanged();
    void displayNameChanged(const QString &displayName);
    void pictureFileIdChanged();

protected:
    void setDisplayName(const QString &displayName);
    void setChatType(Namespace::ChatType chatType);
    void setPictureFileId(const QString &fileId);
    void updateInfo();
    void updateInfo(const PeerInfo *info);

    Telegram::Peer m_peer;
    Namespace::ChatType m_chatType = Namespace::ChatTypeInvalid;
    QString m_displayName;
    QString m_pictureFileId;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_CHAT_INFO_HPP
