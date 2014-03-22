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

#include "CTcpTransport.hpp"

#include <QDebug>

CTcpTransport::CTcpTransport(QObject *parent) :
    QObject(parent)
{
//    SDataCenter testDC;
//    testDC.address = "173.240.5.253";
//    testDC.port = 443;

//    SDataCenter dC;
//    dC.address = "173.240.5.1";
//    dC.port = 443;
    //    connectToDC(testDC);
}

void CTcpTransport::setCore(CTelegramCore *core)
{
    m_core = core;
}

void CTcpTransport::sendPackage(const QByteArray &payload)
{
    // quint32 length (included length itself + packet number + crc32 + payload // Length MUST be divisible by 4
    // quint32 packet number
    // quint32 CRC32 (length, quint32 packet number, payload)
    // Payload

    // Abridged version:
    // quint8: 0xef
    // DataLength / 4 < 0x7f ?
    //      (quint8: Packet length / 4) :
    //      (quint8: 0x7f, quint24: Packet length / 4)
    // Payload

    QByteArray package;
    package.append(char(0xef));
    quint32 length = 0;
    length += payload.length();

    package.append(char(length / 4));
    package.append(payload);

    m_lastPackage = package;
}
