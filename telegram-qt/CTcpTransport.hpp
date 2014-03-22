#ifndef CTCPTRANSPORT_HPP
/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#define CTCPTRANSPORT_HPP

#include <QObject>

#include "CTelegramTransport.hpp"

struct SDataCenter {
    QString address;
    quint16 port;
};

class CTcpTransport : public QObject, public CTelegramTransport
{
    Q_OBJECT
public:
    explicit CTcpTransport(QObject *parent = 0);
    void setCore(CTelegramCore *core);
    QByteArray lastPackage() const { return m_lastPackage; }

signals:

public slots:
    void sendPackage(const QByteArray &payload);

private:
    CTelegramCore *m_core;
    quint32 m_packetNumber;

    QByteArray m_lastPackage;

};

#endif // CTCPTRANSPORT_HPP
