/*
    Copyright (C) 2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

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

quint64 CTestConnection::testNewMessageId()
{
    return newMessageId();
}
