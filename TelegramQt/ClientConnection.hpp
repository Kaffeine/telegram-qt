
#ifndef TELEGRAM_CLIENT_CONNECTION_HPP
#define TELEGRAM_CLIENT_CONNECTION_HPP

#include "Connection.hpp"
#include "PendingOperation.hpp"

#include "TLTypes.hpp"

struct TLDcOption;

namespace Telegram {

namespace Client {

class RpcLayer;

class Connection : public Telegram::BaseConnection
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    TLDcOption dcOption() const { return m_dcOption; }
    void setDcOption(const TLDcOption &dcOption);
    void setDcOption(const DcOption &dcOption);

    RpcLayer *rpcLayer();

public slots:
    PendingOperation *connectToDc();
//    void disconnectFromDc();

protected slots:
    void onClientDhStateChanged();

protected:
    TLDcOption m_dcOption;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_CONNECTION_HPP
