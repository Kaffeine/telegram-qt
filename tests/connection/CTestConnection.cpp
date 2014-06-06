#include "CTestConnection.hpp"

CTestConnection::CTestConnection(QObject *parent) :
    CTelegramConnection(0, parent)
{
}

void CTestConnection::setClientNonce(TLNumber128 newClientNonce)
{
    m_clientNonce = newClientNonce;
}

void CTestConnection::setServerNonce(TLNumber128 newServerNonce)
{
    m_serverNonce = newServerNonce;
}

void CTestConnection::setNewNonce(TLNumber256 newNewNonce)
{
    m_newNonce = newNewNonce;
}

void CTestConnection::setAuthKey(const QByteArray &newKey)
{
    m_authKey = newKey;
}

void CTestConnection::setGA(const QByteArray &newGA)
{
    m_gA = newGA;
}

void CTestConnection::setPrime(const QByteArray &newPrime)
{
    m_dhPrime = newPrime;
}

void CTestConnection::setB(const QByteArray &newB)
{
    m_b = newB;
}

SAesKey CTestConnection::testGenerateClientToServerAesKey(const QByteArray &messageKey) const
{
    return generateClientToServerAesKey(messageKey);
}
