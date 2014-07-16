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

#include <QDebug>

#include "CAppInformation.hpp"
#include "CTelegramConnection.hpp"
#include "CTelegramDispatcher.hpp"

CTelegramCore::CTelegramCore(QObject *parent) :
    QObject(parent),
    m_dispatcher(new CTelegramDispatcher(this)),
    m_appInfo(0)
{
    connect(m_dispatcher, SIGNAL(dcConfigurationObtained()), SIGNAL(connected()));
    connect(m_dispatcher, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(m_dispatcher, SIGNAL(phoneCodeIsInvalid()), SIGNAL(phoneCodeIsInvalid()));
    connect(m_dispatcher, SIGNAL(authenticated()), SIGNAL(authenticated()));
    connect(m_dispatcher, SIGNAL(contactListChanged()), SIGNAL(contactListChanged()));
}

CTelegramCore::~CTelegramCore()
{
    delete m_appInfo;
}

void CTelegramCore::setAppInformation(const CAppInformation *newAppInfo)
{
    if (!newAppInfo) {
        return;
    }

    m_appInfo = new CAppInformation(newAppInfo);
}

bool CTelegramCore::initConnection(const QString &address, quint32 port)
{
    if (!m_appInfo || !m_appInfo->isValid()) {
        qDebug() << "CTelegramCore: Can not init connection: App information is null or is not valid.";
        return false;
    }

    m_dispatcher->setAppInformation(m_appInfo);
    m_dispatcher->initConnection(address, port);

    return true;
}

bool CTelegramCore::restoreConnection(const QString &address, quint32 port, const QByteArray &authKey, const QByteArray &serverSalt)
{
    Q_UNUSED(address)
    Q_UNUSED(port)
    Q_UNUSED(authKey)
    Q_UNUSED(serverSalt)

    qDebug() << Q_FUNC_INFO << "not implemented";

    return false;
}

void CTelegramCore::requestPhoneCode(const QString &phoneNumber)
{
    if (!activeConnection()) {
        qDebug() << "Can't request phone code: there is no active connection.";
        return;
    }

//    if (m_dcConfiguration.isEmpty()) {
//        qDebug() << "Can't request phone code: DC Configuration is unknown.";
//        return;
//    }

    activeConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramCore::signIn(const QString &phoneNumber, const QString &authCode)
{
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramCore::requestContactList()
{
    m_dispatcher->requestContactList();
}

QByteArray CTelegramCore::activeAuthKey() const
{
    if (!activeConnection()) {
        return QByteArray();
    }

    return activeConnection()->authKey();
}

QByteArray CTelegramCore::activeServerSalt() const
{
    if (!activeConnection()) {
        return QByteArray();
    }

    return activeConnection()->serverSaltArray();
}

QStringList CTelegramCore::contactList() const
{
    return m_dispatcher->contactList();
}

CTelegramConnection *CTelegramCore::activeConnection() const
{
    return m_dispatcher->activeConnection();
}
