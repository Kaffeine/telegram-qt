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

#ifndef CTELEGRAMCORE_HPP
#define CTELEGRAMCORE_HPP

#include "telegramqt_export.h"

#include <QObject>
#include <QVector>
#include <QStringList>

class CAppInformation;
class CTelegramConnection;
class CTelegramDispatcher;

class TELEGRAMQT_EXPORT CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramCore(QObject *parent = 0);
    ~CTelegramCore();

    inline const CAppInformation *appInfo() { return m_appInfo; }
    void setAppInformation(const CAppInformation *newAppInfo);

    bool initConnection(const QString &address, quint32 port);
    bool restoreConnection(const QString &address, quint32 port, const QByteArray &authKey = QByteArray(), const QByteArray &serverSalt = QByteArray());

    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);

    void requestContactList();

    QByteArray activeAuthKey() const;
    QByteArray activeServerSalt() const;

    QStringList contactList() const;

signals:
    void connected();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();
    void contactListChanged();

protected:
    CTelegramConnection *activeConnection() const;

    CTelegramDispatcher *m_dispatcher;

    const CAppInformation *m_appInfo;

};

#endif // CTELECORE_HPP
