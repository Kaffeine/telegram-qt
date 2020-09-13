#ifndef TELEGRAM_SERVER_TCP_TRANSPORT_HPP
#define TELEGRAM_SERVER_TCP_TRANSPORT_HPP

#include "BaseTcpTransport.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpSocket)

namespace Telegram {

namespace Server {

class TcpTransport : public BaseTcpTransport
{
    Q_OBJECT
public:
    explicit TcpTransport(QTcpSocket *socket, QObject *parent = nullptr);
    ~TcpTransport() override;

    void connectToHost(const QString &ipAddress, quint16 port) override;

protected:
    void onStateChanged(QAbstractSocket::SocketState newState);

    bool startObfuscatedSession();
    void readEvent() final;

};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_TCP_TRANSPORT_HPP
