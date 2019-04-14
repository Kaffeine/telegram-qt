#ifndef TELEGRAMQT_DIALOG_LIST_HPP
#define TELEGRAMQT_DIALOG_LIST_HPP

#include "ReadyObject.hpp"
#include "TelegramNamespace.hpp"
#include <QVector>

namespace Telegram {

namespace Client {

class MessagingApi;

class TELEGRAMQT_EXPORT DialogList : public QObject, public ReadyObject
{
    Q_OBJECT
public:
    explicit DialogList(MessagingApi *backend);

    Telegram::PeerList peers() const { return m_peers; }

    bool isReady() const override;
    PendingOperation *becomeReady() override;

Q_SIGNALS:
    void listChanged(const Telegram::PeerList &added, const Telegram::PeerList &removed);

    // Internal API
public:
    void ensurePeers(const Telegram::PeerList &peers);

protected:
    void onFinished();
    PendingOperation *m_readyOperation = nullptr;
    Telegram::PeerList m_peers;
    MessagingApi *m_backend;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DIALOG_LIST_HPP
