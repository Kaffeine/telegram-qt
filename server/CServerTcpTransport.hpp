#ifndef CSERVERTCPTRANSPORT_HPP
#define CSERVERTCPTRANSPORT_HPP

#include "../TelegramQt/CTcpTransport.hpp"

QT_FORWARD_DECLARE_CLASS(QTcpSocket)

namespace Telegram {

namespace Server {

class TcpTransport : public CTcpTransport
{
    Q_OBJECT
public:
    explicit TcpTransport(QTcpSocket *socket, QObject *parent = nullptr);
    void connectToHost(const QString &ipAddress, quint16 port) override;

protected:
    void onStateChanged(QAbstractSocket::SocketState newState);

    bool startObfuscatedSession();
    void readEvent() final;

};

} // Server

} // Telegram

#endif // CSERVERTCPTRANSPORT_HPP
