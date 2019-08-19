#ifndef TELEGRAMQT_CLIENT_CONNECTION_OPERATION
#define TELEGRAMQT_CLIENT_CONNECTION_OPERATION

#include "../PendingOperation.hpp"

namespace Telegram {

namespace Client {

class Connection;

class ConnectOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit ConnectOperation(QObject *parent = nullptr);

    Connection *connection() const { return m_connection; }
    void setConnection(Connection *connection);

protected:
    void startImplementation() override;

    // The class is private, don't care about ABI
    Connection *m_connection = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_CONNECTION_OPERATION
