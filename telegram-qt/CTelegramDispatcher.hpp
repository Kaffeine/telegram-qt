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
#include "TelegramNamespace.hpp"

class QTimer;

class CAppInformation;
class CTelegramConnection;

class CTelegramDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramDispatcher(QObject *parent = 0);

    void setAppInformation(const CAppInformation *newAppInfo);

    bool isAuthenticated();

    QStringList contactList() const { return m_contactList; }

    void addContacts(const QStringList &phoneNumbers, bool replace = false);
    void deleteContacts(const QStringList &phoneNumbers);

    QByteArray connectionSecretInfo() const;

    void initConnection(const QString &address, quint32 port);
    bool restoreConnection(const QByteArray &secret);

    void requestPhoneStatus(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void requestPhoneCode(const QString &phoneNumber);
    void requestContactList();
    void requestContactAvatar(const QString &contact);

    void sendMessageToContact(const QString &phone, const QString &message);
    void setTyping(const QString &phone, bool typingStatus);

    void setOnlineStatus(bool onlineStatus);

    TelegramNamespace::ContactStatus contactStatus(const QString &phone) const;

    QString contactFirstName(const QString &phone) const;
    QString contactLastName(const QString &phone) const;

signals:
    void dcConfigurationObtained();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();
    void contactListChanged();
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);
    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);
    void messageReceived(const QString &phone, const QString &message);
    void contactStatusChanged(const QString &phone, TelegramNamespace::ContactStatus status);
    void contactTypingStatusChanged(const QString &phone, bool typingStatus);

protected slots:
    void whenSelfPhoneReceived(const QString &phone);
    void whenConnectionAuthChanged(int dc, int newState);
    void whenConnectionConfigurationUpdated(int dc);
    void whenConnectionDcIdUpdated(int connectionId, int newDcId);
    void whenPackageRedirected(const QByteArray &data, int dc);
    void whenWantedActiveDcChanged(int dc);

    void whenFileReceived(const TLUploadFile &file, quint32 fileId);
    void whenUpdatesReceived(const TLUpdates &updates);

    void whenUsersReceived(const QVector<TLUser> &users);

    void whenContactListReceived(const QStringList &contactList);
    void whenContactListChanged(const QStringList &added, const QStringList &removed);
    void whenUserTypingTimeout();

protected:
    void requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId);
    void processUpdate(const TLUpdate &update);

private:
    TLInputPeer phoneNumberToInputPeer(const QString &phoneNumber) const;
    TLInputUser phoneNumberToInputUser(const QString &phoneNumber) const;
    QString userIdToPhoneNumber(const quint32 id) const;
    quint32 phoneNumberToUserId(const QString &phoneNumber) const;
    TLUser *phoneNumberToUser(const QString &phoneNumber) const;

    TelegramNamespace::ContactStatus decodeContactStatus(TLValue status) const;

    CTelegramConnection *activeConnection() const { return m_connections.value(m_activeDc); }

    CTelegramConnection *createConnection(const TLDcOption &dc);
    CTelegramConnection *establishConnectionToDc(int dc);

    TLDcOption dcInfoById(quint32 dc);

    QString mimeTypeByStorageFileType(TLValue type);

    void setActiveDc(int dc, bool syncWantedDc = true);

    void ensureTypingUpdateTimer(int interval);

    const CAppInformation *m_appInformation;

    int m_activeDc;
    int m_wantedActiveDc;

    QVector<TLDcOption> m_dcConfiguration;
    QMap<int, CTelegramConnection *> m_connections;

    QMap<int, QByteArray> m_delayedPackages; // dc, package data
    QMap<quint32, TLUser*> m_users;

    QString m_selfPhone;

    QStringList m_contactList;

    QList<quint32> m_requestedFilesMessageIds;

    QTimer *m_typingUpdateTimer;
    QMap<quint32, int> m_userTypingMap; // user id, typing time
    QMap<QString, int> m_localTypingMap; // phone, typing time

};

#endif // CTELEGRAMDISPATCHER_HPP
