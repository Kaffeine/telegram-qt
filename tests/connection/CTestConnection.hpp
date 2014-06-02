#ifndef CTESTCONNECTION_HPP
#define CTESTCONNECTION_HPP

#include "CTelegramConnection.hpp"

class CTestConnection : public CTelegramConnection
{
    Q_OBJECT
public:
    explicit CTestConnection(QObject *parent = 0);

    inline CTelegramTransport *transport() const { return m_transport; }

    void setClientNonce(TLNumber128 newClientNonce);
    void setServerNonce(TLNumber128 newServerNonce);
    void setNewNonce(TLNumber256 newNewNonce);
    void setAuthKey(const QByteArray &newKey);
    void setGA(const QByteArray &newGA);
    void setPrime(const QByteArray &newPrime);
    void setB(const QByteArray &newB);

    SAesKey testGenerateClientToServerAesKey(const QByteArray &messageKey) const;
};

#endif // CTESTCONNECTION_HPP
