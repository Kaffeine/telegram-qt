#ifndef TELEGRAM_DECLARATIVE_CHAT_INFO_HPP
#define TELEGRAM_DECLARATIVE_CHAT_INFO_HPP

#include "DeclarativeClientOperator.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class TELEGRAMQT_QML_EXPORT DeclarativeChatInfo : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(Namespace::ChatType chatType READ chatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
public:
    explicit DeclarativeChatInfo(QObject *parent = nullptr);

    Telegram::Peer peer() const { return m_peer; }
    Namespace::ChatType chatType() const { return m_chatType; }
    QString displayName() const { return m_displayName; }

public slots:
    void setPeer(const Telegram::Peer &peer);

signals:
    void peerChanged();
    void chatTypeChanged();
    void displayNameChanged(const QString &displayName);

protected:
    void setDisplayName(const QString &displayName);
    void setChatType(Namespace::ChatType chatType);
    void updateInfo();

    Telegram::Peer m_peer;
    Namespace::ChatType m_chatType = Namespace::ChatTypeInvalid;
    QString m_displayName;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_CHAT_INFO_HPP
