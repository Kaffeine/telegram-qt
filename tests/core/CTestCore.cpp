#include "CTestCore.hpp"

CTestCore::CTestCore(QObject *parent) :
    CTelegramCore(parent)
{
}

void CTestCore::setClientNonce(TLNumber128 newClientNonce)
{
    m_clientNonce = newClientNonce;
}

void CTestCore::setServerNonce(TLNumber128 newServerNonce)
{
    m_serverNonce = newServerNonce;
}

void CTestCore::setNewNonce(TLNumber256 newNewNonce)
{
    m_newNonce = newNewNonce;
}

void CTestCore::setAuthKey(const QByteArray &newKey)
{
    m_authKey = newKey;
}

void CTestCore::setGA(const QByteArray &newGA)
{
    m_gA = newGA;
}

void CTestCore::setPrime(const QByteArray &newPrime)
{
    m_dhPrime = newPrime;
}

void CTestCore::setB(const QByteArray &newB)
{
    m_b = newB;
}

SAesKey CTestCore::testGenerateClientToServerAesKey(const QByteArray &messageKey) const
{
    return generateClientToServerAesKey(messageKey);
}
