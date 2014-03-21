#include "CTelegramCore.hpp"

//#include <QtNetwork/QTcpSocket>
//#include <QtNetwork/QHostAddress>

#include <QFile>
#include <QBuffer>
#include <QDebug>

#include "CTelegramStream.hpp"

const quint32 CTelegramCore::appId = 0;
const QString CTelegramCore::appHash = QLatin1String("00000000000000000000000000000000");

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
//    m_socket(new QTcpSocket(this)),
    m_enableSendInformation(false)
{
//    connect(m_socket, SIGNAL(connected()), SLOT(whenConnected()));
//    connect(m_socket, SIGNAL(readyRead()), SLOT(acceptData()));
//    connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(stateChanged()));

    SDataCenter testDC;
    testDC.address = "173.240.5.253";
    testDC.port = 443;

    SDataCenter dC;
    dC.address = "173.240.5.1";
    dC.port = 443;

//    connectToDC(testDC);
}

void CTelegramCore::setLogfile(const QString &output)
{
    m_dumpFilename = output;
}

void CTelegramCore::sendCode(const QString &phoneNumber)
{
    qDebug() << Q_FUNC_INFO;
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);

    CTelegramStream stream(&buffer);

    addHeader(&stream);

    stream << AuthSendCode;
    stream << phoneNumber;
    stream << quint32(0); // Zero mean message with numerical code
    stream << appId;
    stream << appHash;
    stream << QLatin1String("en");

    sendPackage(buffer.buffer());
}

void CTelegramCore::whenConnected()
{
    qDebug() << Q_FUNC_INFO;
    emit connected();
}

void CTelegramCore::acceptData()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray accepted;// = m_socket->readAll();

    static int answer = 0;

    QFile packageDump(m_dumpFilename + QString::number(answer++));
    packageDump.open(QIODevice::WriteOnly);

    packageDump.write(accepted.constData(), accepted.size());
}

void CTelegramCore::stateChanged()
{
//    qDebug() << "New socket state: " << m_socket->state();
}

void CTelegramCore::addHeader(CTelegramStream *stream)
{
    *stream << InvokeWithLayer13;
    *stream << InitConnection;
    *stream << appId;

//    if (m_enableSendInformation) {
    *stream << QLatin1String("x86"); // Device
    *stream << QLatin1String("GNU/Linux"); // System
    *stream << QLatin1String("0.01"); // App version
    *stream << QLatin1String("en");
}

void CTelegramCore::sendPackage(const QByteArray &package)
{
    QFile packageDump(m_dumpFilename);
    packageDump.open(QIODevice::WriteOnly);

    packageDump.write(package.constData(), package.size());

//    if (m_socket && m_socket->isOpen())
//        m_socket->write(package.constData(), package.size());
}

void CTelegramCore::connectToDC(const SDataCenter &dc)
{
//    m_socket->connectToHost(dc.address, dc.port);
}

quint64 CTelegramCore::formatTimeStamp(qint64 timeInMs)
{
    static const quint32 maxMsecValue = (1UL << 32) - 1;
    quint64 secs = timeInMs / 1000;

    quint32 msecs = timeInMs % 1000;

    msecs = (maxMsecValue / 1000 * msecs);

    return (secs << 32) + msecs;
}

