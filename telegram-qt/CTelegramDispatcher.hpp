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

#ifndef CTELEGRAMDISPATCHER_HPP
#define CTELEGRAMDISPATCHER_HPP

#include <QObject>

#include <QMap>
#include <QStringList>

#include "TLTypes.hpp"

class CAppInformation;
class CTelegramConnection;

class CTelegramDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramDispatcher(QObject *parent = 0);

    void setAppInformation(const CAppInformation *newAppInfo);

    QStringList contactList() const { return m_contactList; }

    void initConnection(const QString &address, quint32 port);

    void signIn(const QString &phoneNumber, const QString &authCode);

    void requestPhoneCode(const QString &phoneNumber);
    void requestContactList();
    void requestContactAvatar(const QString &contact);

signals:
    void dcConfigurationObtained();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();
    void contactListChanged();
    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);

protected slots:
    void whenConnectionAuthChanged(int dc, int newState);
    void whenConnectionConfigurationUpdated(int dc);
    void whenConnectionDcIdUpdated(int connectionId, int newDcId);
    void whenPackageRedirected(const QByteArray &data, int dc);
    void whenWantedActiveDcChanged(int dc);

    void whenFileReceived(const TLUploadFile &file, quint32 fileId);

    void setUsers(const QVector<TLUser> &users);

protected:
    void requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId);

private:
    CTelegramConnection *activeConnection() const { return m_connections.value(m_activeDc); }

    CTelegramConnection *createConnection(const TLDcOption &dc);
    CTelegramConnection *establishConnectionToDc(int dc);

    TLDcOption dcInfoById(quint32 dc);

    QString mimeTypeByStorageFileType(TLValue type);

    void setActiveDc(int dc, bool syncWantedDc = true);

    const CAppInformation *m_appInformation;

    int m_activeDc;
    int m_wantedActiveDc;

    QVector<TLDcOption> m_dcConfiguration;
    QMap<int, CTelegramConnection *> m_connections;

    QMap<int, QByteArray> m_delayedPackages; // dc, package data

    QVector<TLUser> m_users;
    QStringList m_contactList;

    QList<quint32> m_requestedFilesMessageIds;

};

#endif // CTELEGRAMDISPATCHER_HPP
