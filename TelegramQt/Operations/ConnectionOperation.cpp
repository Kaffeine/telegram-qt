#include "ConnectionOperation.hpp"

#include "ClientConnection.hpp"

namespace Telegram {

namespace Client {

ConnectOperation::ConnectOperation(Connection *connection) :
    PendingOperation(connection),
    m_connection(connection)
{
}

} // Client

} // Telegram
