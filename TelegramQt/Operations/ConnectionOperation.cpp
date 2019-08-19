#include "ConnectionOperation.hpp"

#include "ClientConnection.hpp"
#include "CTelegramTransport.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcClientConnOperation, "telegram.client.connection.operation", QtWarningMsg)

namespace Telegram {

namespace Client {

/*!
  \fn ConnectOperation *Connection::connectToDc()

  Initiates connection to DC and returns an Operation object.

  This method establish Transport (TCP/UDP/HTTP) level connection.
  Operation is finished on transport (network) error or on DH layer
  connection established.

  \sa BaseTransport::connectToHost()
*/
ConnectOperation::ConnectOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void ConnectOperation::setConnection(Connection *connection)
{
    m_connection = connection;
    if (!connection) {
        setObjectName(QLatin1String("ConnectTo(nullptr)"));
        return;
    }
    const DcOption opt = m_connection->dcOption();
    setObjectName(QStringLiteral("ConnectTo(%1:%2)").arg(opt.address).arg(opt.port));
}

void ConnectOperation::startImplementation()
{
    if (!m_connection) {
        setDelayedFinishedWithError({{ c_text(), QLatin1String("No connection") }});
        return;
    }

    connect(m_connection, &Connection::statusChanged, this,
            [this] (Connection::Status status, Connection::StatusReason reason) {
        if (status == Connection::Status::HasDhKey) {
            setFinished();
        }

        if (status == Connection::Status::Failed) {
            setFinishedWithError({
                                     { c_text(), QLatin1String("connection failed") },
                                     { Connection::c_statusKey(), static_cast<int>(status) },
                                     { Connection::c_statusReasonKey(), static_cast<int>(reason) },
                                 });
        }
    });

    const DcOption opt = m_connection->dcOption();
    qCDebug(lcClientConnOperation) << __func__ << opt.id << opt.address << opt.port;

    BaseTransport *transport = m_connection->transport();

    connect(transport, &BaseTransport::errorOccurred, this,
            [this] (QAbstractSocket::SocketError error, const QString &text) {
        if (isFinished()) {
            return;
        }
        setFinishedWithError({
                                 { QLatin1String("qtError"), error },
                                 { QLatin1String("qtErrorText"), text },
                             });
    });

    m_connection->connectToDc();
}

} // Client

} // Telegram
