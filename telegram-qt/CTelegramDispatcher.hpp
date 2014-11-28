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
#include <QPair>
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
    enum InitializationState {
        InitNone,
        InitGetDcConfiguration,
        InitGetSelf,
        InitGetContactList,
        InitCheckUpdates,
        InitDone
    };

    explicit CTelegramDispatcher(QObject *parent = 0);

    void setAppInformation(const CAppInformation *newAppInfo);

    bool isAuthenticated();
    QString selfPhone() const { return m_selfPhone; }

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
    void requestContactAvatar(const QString &contact);

    quint64 sendMessageToContact(const QString &phone, const QString &message);
    quint64 sendMessageToChat(quint32 publicChatId, const QString &message);

    quint32 createChat(const QStringList &phones, const QString chatName);

    void setTyping(const QString &phone, bool typingStatus);
    void setChatTyping(quint32 publicChatId, bool typingStatus);

    void setMessageRead(const QString &phone, quint32 messageId);

    void setOnlineStatus(bool onlineStatus);

    TelegramNamespace::ContactStatus contactStatus(const QString &phone) const;

    QString contactFirstName(const QString &phone) const;
    QString contactLastName(const QString &phone) const;

    QStringList chatParticipants(quint32 publicChatId) const;

signals:
    void dcConfigurationObtained();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();
    void contactListChanged();
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);
    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);
    void messageReceived(const QString &phone, const QString &message, quint32 messageId);
    void chatMessageReceived(quint32 chatId, const QString &phone, const QString &message);
    void contactStatusChanged(const QString &phone, TelegramNamespace::ContactStatus status);
    void contactTypingStatusChanged(const QString &phone, bool typingStatus);
    void contactChatTypingStatusChanged(quint32 publicChatId, const QString &phone, bool typingStatus);

    void sentMessageStatusChanged(const QString &phone, quint64 randomMessageId, TelegramNamespace::MessageDeliveryStatus status);

    void chatAdded(quint32 publichChatId);
    void chatChanged(quint32 publichChatId);
    void initializated();

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
    void whenUserTypingTimerTimeout();

    void whenStatedMessageReceived(const TLMessagesStatedMessage &statedMessage, quint64 messageId);
    void whenMessageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq);

    void getDcConfiguration();
    void getSelfUser();
    void getContacts();

    void getState();
    void whenUpdatesStateReceived(const TLUpdatesState &updatesState);

    void getDifference();
    void whenUpdatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

protected:
    void requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId);
    void processUpdate(const TLUpdate &update);

    void processMessageReceived(quint32 messageId, quint32 fromId, const QString &message);
    void processChatMessageReceived(quint32 messageId, quint32 chatId, quint32 fromId, const QString &message);

    void setFullChat(const TLChatFull &newChat);

    void initConnectionSharedFinal(int activeDc = 0);

private:
    TLInputPeer publicChatIdToInputPeer(quint32 publicChatId) const;
    TLInputPeer phoneNumberToInputPeer(const QString &phoneNumber) const;
    TLInputUser phoneNumberToInputUser(const QString &phoneNumber) const;
    QString userIdToIdentifier(const quint32 id) const;
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
    void ensureUpdateState(quint32 pts = 0, quint32 seq = 0, quint32 date = 0);

    void checkStateAndCallGetDifference();

    void continueInitialization();

    const CAppInformation *m_appInformation;

    InitializationState m_initState;

    int m_activeDc;
    int m_wantedActiveDc;

    QVector<TLDcOption> m_dcConfiguration;
    QMap<int, CTelegramConnection *> m_connections;

    TLUpdatesState m_updatesState; // Current application update state (may be older than actual server-side message box state)
    TLUpdatesState m_actualState; // State reported by server as actual
    bool m_updatesStateIsLocked; // True if we are (going to) getting updatesDifference.

    QMap<int, QByteArray> m_delayedPackages; // dc, package data
    QMap<quint32, TLUser*> m_users;

    QMap<quint32, QPair<QString, quint64> >m_messagesMap; // message id to phone and big_random message id

    quint32 m_selfUserId;
    QString m_selfPhone;

    QStringList m_contactList;

    QList<quint32> m_requestedFilesMessageIds;

    QTimer *m_typingUpdateTimer;
    QMap<quint32, int> m_userTypingMap; // user id, typing time (ms)
    QMap<QPair<quint32, quint32>, int> m_userChatTypingMap; // <public chat id, user id>, typing time (ms)
    QMap<QString, int> m_localTypingMap; // phone, typing time (ms)
    QMap<quint32, int> m_localChatTypingMap; // public chat id, typing time (ms)

    QMap<quint32, quint32> m_chatIdMap; // Public chat id to internal telegram chat id map
    QMap<quint64, quint32> m_temporaryChatIdMap; // API Call id to public chat id map

    QMap<quint32, QPair<TLChat, TLChatFull> >m_chatInfo; // Internal telegram chat id to ChatFull map

};

#endif // CTELEGRAMDISPATCHER_HPP
