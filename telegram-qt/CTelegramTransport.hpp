/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CTELEGRAMTRANSPORT_HPP
#define CTELEGRAMTRANSPORT_HPP

#include <QObject>

#include <QByteArray>
#include <QAbstractSocket>

class CTelegramTransport : public QObject
{
    Q_OBJECT
public:
    CTelegramTransport(QObject *parent = 0) : QObject(parent) { }
    virtual void sendPackage(const QByteArray &package) = 0;
    virtual void connectToHost(const QString &ipAddress, quint32 port) = 0;

    virtual QByteArray getPackage() = 0;

    virtual bool isConnected() const = 0;

    inline QAbstractSocket::SocketError error() const { return m_error; }
    inline QAbstractSocket::SocketState state() const { return m_state; }

    // Method for testing
    virtual QByteArray lastPackage() const = 0;

signals:
    void error(QAbstractSocket::SocketError error);
    void stateChanged(QAbstractSocket::SocketState state);

    void readyRead();

protected:
    void setError(QAbstractSocket::SocketError error);
    void setState(QAbstractSocket::SocketState state);

private:
    QAbstractSocket::SocketError m_error;
    QAbstractSocket::SocketState m_state;

};

inline void CTelegramTransport::setError(QAbstractSocket::SocketError e)
{
    m_error = e;
    emit error(e);
}

inline void CTelegramTransport::setState(QAbstractSocket::SocketState s)
{
    m_state = s;
    emit stateChanged(s);
}

#endif // CTELEGRAMTRANSPORT_HPP
