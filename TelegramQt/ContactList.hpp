#ifndef TELEGRAMQT_CONTACT_LIST_HPP
#define TELEGRAMQT_CONTACT_LIST_HPP

#include "ReadyObject.hpp"
#include "TelegramNamespace.hpp"
#include <QVector>

namespace Telegram {

namespace Client {

class ContactsApi;

class TELEGRAMQT_EXPORT ContactList : public QObject, public ReadyObject
{
    Q_OBJECT
public:
    explicit ContactList(ContactsApi *backend);

    Telegram::PeerList peers() const { return m_peers; }

    bool isReady() const override;
    PendingOperation *becomeReady() override;

Q_SIGNALS:
    void listChanged(const Telegram::PeerList &added, const Telegram::PeerList &removed);

protected:
    void onFinished();
    PendingOperation *m_readyOperation = nullptr;
    Telegram::PeerList m_peers;
    ContactsApi *m_backend;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CONTACT_LIST_HPP
