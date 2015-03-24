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
    quint64 testNewMessageId();

};

#endif // CTESTCONNECTION_HPP
