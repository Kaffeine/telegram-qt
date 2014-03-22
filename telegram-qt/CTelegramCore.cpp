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

#include "CTelegramCore.hpp"

#include <QFile>
#include <QBuffer>
#include <QDebug>

#include <QDateTime>

#include "CTelegramStream.hpp"
#include "CTelegramTransport.hpp"
#include "Utils.hpp"

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_appId(0),
    m_appHash(QLatin1String("00000000000000000000000000000000")),
    m_transport(0)
{
    Utils::randomBytes(m_nonce.data, 16);
}

void CTelegramCore::setAppId(quint32 newId)
{
    m_appId = newId;
}

bool CTelegramCore::setAppHash(const QString &newHash)
{
    if (newHash.length() != 16)
        return false;

    m_appHash = newHash;

    return true;
}

void CTelegramCore::setTransport(CTelegramTransport *newTransport)
{
    m_transport = newTransport;
    m_transport->setCore(this);
}

quint64 CTelegramCore::formatTimeStamp(qint64 timeInMs)
{
    static const quint32 maxMsecValue = (1UL << 32) - 1;
    quint64 secs = timeInMs / 1000;

    quint32 msecs = timeInMs % 1000;

    msecs = maxMsecValue / 1000 * msecs;

    return (secs << 32) + msecs;
}

void CTelegramCore::requestPqAuthorization()
{
    QBuffer output;
    CTelegramStream outputStream(&output);
    output.open(QIODevice::WriteOnly);

    outputStream << quint64(0); // Zero auth for this message
    outputStream << formatClientTimeStamp(QDateTime::currentMSecsSinceEpoch());
    outputStream << quint32(20); // Message is 20 bytes in length
    outputStream << ReqPQ;
    outputStream << m_nonce.parts.little;
    outputStream << m_nonce.parts.big;

    m_transport->sendPackage(output.buffer());
}
