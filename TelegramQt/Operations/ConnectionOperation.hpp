#ifndef TELEGRAMQT_CLIENT_CONNECTION_OPERATION
#define TELEGRAMQT_CLIENT_CONNECTION_OPERATION

#include "PendingOperation.hpp"

namespace Telegram {

namespace Client {

class Connection;

class ConnectOperation : public PendingOperation
{
public:
    explicit ConnectOperation(Connection *connection = nullptr);
    Connection *connection() const { return m_connection; }
protected:
    Connection *m_connection = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_CONNECTION_OPERATION
