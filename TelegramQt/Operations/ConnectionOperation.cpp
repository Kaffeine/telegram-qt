#include "ConnectionOperation.hpp"

#include "ClientConnection.hpp"
#include "CTelegramTransport.hpp"

namespace Telegram {

namespace Client {

ConnectOperation::ConnectOperation(Connection *connection) :
    PendingOperation(connection),
    m_connection(connection)
{
    const DcOption opt = m_connection->dcOption();
    setObjectName(QStringLiteral("ConnectTo(%1:%2)").arg(opt.address).arg(opt.port));

    connect(connection->transport(), &CTelegramTransport::errorOccurred, this,
            [this] (QAbstractSocket::SocketError error, const QString &text) {
        setFinishedWithError({
                                 { QStringLiteral("qtError"), error },
                                 { QStringLiteral("qtErrorText"), text },
                             });
    });

    connect(m_connection, &Connection::statusChanged, this,
            [this] (Connection::Status status, Connection::StatusReason reason) {
        Q_UNUSED(reason)

        if (status == Connection::Status::HasDhKey) {
            setFinished();
        }
    });
}

void ConnectOperation::start()
{
    const DcOption opt = m_connection->dcOption();
    m_connection->transport()->connectToHost(opt.address, opt.port);
}

} // Client

} // Telegram
