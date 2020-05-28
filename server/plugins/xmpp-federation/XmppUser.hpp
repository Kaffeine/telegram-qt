#ifndef TELEGRAM_XMPP_USER_HPP
#define TELEGRAM_XMPP_USER_HPP

#include "TelegramServerUser.hpp"

#include <QSet>

namespace Telegram {

namespace Server {

class XmppUser : public AbstractUser
{
public:
    quint32 userId() const { return m_userId; }
    quint32 id() const override { return m_userId; }

    quint32 dcId() const override { return m_dcId; }
    void setDcId(quint32 dcId);

    QString jid() const { return m_jid; }
    void setJid(const QString &jid);

    QString phoneNumber() const override { return QString(); }
    QString userName() const override { return QString(); }
    QString firstName() const override { return m_jid; }
    QString lastName() const override { return QString(); }
    quint32 onlineTimestamp() const override { return 0; }
    bool isOnline() const override { return false; }
    UserPostBox *getPostBox() override { return &m_box; }
    const UserPostBox *getPostBox() const override { return &m_box; }
    QVector<ImageDescriptor> getImages() const override { return {}; }
    ImageDescriptor getCurrentImage() const override { return {}; }
    QVector<quint32> contactList() const override { return { }; }

    void addResource(const QString &resource);
    QSet<QString> activeResources() const { return m_resources; }

protected:
    QString m_jid;
    quint32 m_userId = 0;
    quint32 m_dcId = 0;

    UserPostBox m_box;
    QSet<QString> m_resources;
};

} // Server

} // Telegram

#endif // TELEGRAM_XMPP_USER_HPP
