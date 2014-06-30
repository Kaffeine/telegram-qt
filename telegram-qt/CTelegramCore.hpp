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
#include <QMap>
#include <QVector>

#include "SDcInfo.hpp"

class CAppInformation;
class CTelegramConnection;

class TELEGRAMQT_EXPORT CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramCore(QObject *parent = 0);
    ~CTelegramCore();

    inline const CAppInformation *appInfo() { return m_appInfo; }
    void setAppInformation(const CAppInformation *newAppInfo);

    bool initialConnection(const QString &address, quint32 port);
    bool initialConnection(const QString &address, quint32 port, const QByteArray &authKey, const QByteArray &serverSalt);

    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void getContacts();

    QByteArray activeAuthKey() const;
    QByteArray activeServerSalt() const;

signals:
    void dcConfigurationObtained();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();

protected slots:
    void whenConnectionAuthChanged(int dc, int newState);
    void whenConnectionConfigurationUpdated(int dc);
    void whenConnectionDcIdUpdated(int connectionId, int newDcId);
    void whenPackageRedirected(const QByteArray &data, int dc);
    void whenWantedActiveDcChanged(int dc);

protected:
    void setActiveDc(int dc, bool syncWantedDc = true);

    CTelegramConnection *activeConnection() const { return m_connections.value(m_activeDc); }
    CTelegramConnection *createConnection(const SDcInfo &dc);
    CTelegramConnection *establishConnectionToDc(int dc);

    SDcInfo infoById(quint32 id) const;

    const CAppInformation *m_appInfo;

    int m_activeDc;

    QMap<int, CTelegramConnection *> m_connections;

    QMap<int, QByteArray> m_delayedPackages; // dc, package data

    QVector<SDcInfo> m_dcConfiguration;

    int m_wantedActiveDc;
};

#endif // CTELECORE_HPP
