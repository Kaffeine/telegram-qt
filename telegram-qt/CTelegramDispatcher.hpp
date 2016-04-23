/*
   Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#ifndef CTELEGRAMDISPATCHER_HPP
#define CTELEGRAMDISPATCHER_HPP

#include <QObject>

#include <QMap>
#include <QMultiMap>
#include <QPair>
#include <QStringList>
#include <QVector>

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class QTimer;
class QCryptographicHash;
class QIODevice;

class CAppInformation;
class CTelegramConnection;

class FileRequestDescriptor
{
public:
    enum Type {
        Invalid,
        Avatar,
        MessageMediaData,
        Upload
    };

    FileRequestDescriptor();

    static FileRequestDescriptor uploadRequest(const QByteArray &data, const QString &fileName, quint32 dc);
    static FileRequestDescriptor avatarRequest(const TLUser *user);
    static FileRequestDescriptor messageMediaDataRequest(const TLMessage &message);

    inline Type type() const { return m_type; }

    inline quint32 dcId() const { return m_dcId; }
    inline bool isValid() const { return m_type != Invalid; }

    inline TLInputFileLocation inputLocation() const { return m_inputLocation; }

    inline quint32 userId() const { return m_userId; }
    inline quint32 messageId() const { return m_messageId; }
    inline quint32 size() const { return m_size; }
    inline quint32 offset() const { return m_offset; }

    inline void setOffset(quint32 newOffset) { m_offset = newOffset; }

    /* Upload stuff */
    inline TLInputFile inputFile() const;
    inline quint32 part() const { return m_part; }
    inline quint32 parts() const;
    inline QByteArray md5Sum() const { return m_md5Sum; }
    inline quint32 fileId() const { return m_fileId; }

    bool isBigFile() const;
    bool finished() const;
    void bumpPart();

    QByteArray data() const;

protected:
    void setupLocation(const TLFileLocation &fileLocation);
    Type m_type;
    quint32 m_userId;
    quint32 m_messageId;
    quint32 m_size;
    quint32 m_offset;
    quint32 m_part;
    QByteArray m_data;
    QByteArray m_md5Sum;
    QString m_fileName;
    quint64 m_fileId;
    QCryptographicHash *m_hash;

    TLInputFileLocation m_inputLocation;
    quint32 m_dcId;

    static const quint32 c_chunkSize;

};

class CTelegramDispatcher : public QObject
{
    Q_OBJECT
public:
    enum InitializationStep {
        StepFirst           = 0,
        StepDcConfiguration = 1 << 0,
        StepSignIn          = 1 << 1,
        StepKnowSelf        = 1 << 2,
        StepContactList     = 1 << 3,
        StepChatInfo        = 1 << 4,
        StepUpdates         = 1 << 5,
        StepDone            = StepUpdates | (StepUpdates - 1)
    };

#if defined(DEVELOPER_BUILD) && QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(InitializationStep)
#endif

    explicit CTelegramDispatcher(QObject *parent = 0);
    ~CTelegramDispatcher();

    static QVector<TelegramNamespace::DcOption> builtInDcs();
    static quint32 defaultPingInterval();

    void setAppInformation(const CAppInformation *newAppInfo);

    static qint32 localTypingRecommendedRepeatInterval();

    inline TelegramNamespace::ConnectionState connectionState() const { return m_connectionState; }

    QString selfPhone() const;

    QStringList contactList() const;
    QVector<quint32> publicChatIdList() const;

    void addContacts(const QStringList &phoneNumbers, bool replace = false);
    void deleteContacts(const QStringList &phoneNumbers);

    QByteArray connectionSecretInfo() const;

    inline quint32 messageReceivingFilterFlags() const { return m_messageReceivingFilterFlags; }
    void setMessageReceivingFilter(TelegramNamespace::MessageFlags flags);
    void setAcceptableMessageTypes(TelegramNamespace::MessageTypeFlags types);
    void setAutoReconnection(bool enable);
    void setPingInterval(quint32 ms, quint32 serverDisconnectionAdditionTime);
    void setMediaDataBufferSize(quint32 size);

    bool initConnection(const QVector<TelegramNamespace::DcOption> &dcs);
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();
    bool logOut();

    void requestPhoneStatus(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void requestPhoneCode(const QString &phoneNumber);
    void requestContactAvatar(const QString &contact);
    bool requestMessageMediaData(quint32 messageId);
    bool getMessageMediaInfo(TelegramNamespace::MessageMediaInfo *messageInfo, quint32 messageId) const;

    bool requestHistory(const QString &identifier, quint32 offset, quint32 limit);

    quint32 uploadFile(const QByteArray &fileContent, const QString &fileName);
    quint32 uploadFile(QIODevice *source, const QString &fileName);

    quint64 sendMessage(const QString &identifier, const QString &message);
    quint64 sendMedia(const QString &identifier, const TelegramNamespace::MessageMediaInfo &messageInfo);
    quint64 forwardMessage(const QString &identifier, quint32 messageId);

    void setTyping(const QString &identifier, TelegramNamespace::MessageAction publicAction);
    void setMessageRead(const QString &identifier, quint32 messageId);

    quint32 createChat(const QStringList &phones, const QString chatName);
    bool addChatUser(quint32 publicChatId, const QString &contact, quint32 forwardMessages);

    void setOnlineStatus(bool onlineStatus);
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    TelegramNamespace::ContactStatus contactStatus(const QString &phone) const;
    quint32 contactLastOnline(const QString &contact) const;

    QString contactFirstName(const QString &contact) const;
    QString contactLastName(const QString &contact) const;
    QString contactUserName(const QString &contact) const;
    QString contactAvatarToken(const QString &contact) const;

    QString chatTitle(quint32 publicChatId) const;

    bool getChatInfo(TelegramNamespace::GroupChat *outputChat, quint32 publicChatId) const;
    bool getChatParticipants(QStringList *participants, quint32 publicChatId);

signals:
    void connectionStateChanged(TelegramNamespace::ConnectionState status);

    void phoneCodeRequired();
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage);
    void loggedOut(bool result);
    void authorizationErrorReceived();
    void userNameStatusUpdated(const QString &userName, TelegramNamespace::AccountUserNameStatus status);
    void uploadingStatusUpdated(quint32 requestId, quint32 offset, quint32 size);

    void contactListChanged();
    void contactProfileChanged(const QString &contact);
    void phoneStatusReceived(const QString &phone, bool registered);

    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data, const QString &mimeType, TelegramNamespace::MessageType type, quint32 offset, quint32 size);

    void messageReceived(const TelegramNamespace::Message &message);

#ifndef TELEGRAMQT_NO_DEPRECATED
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);
    void messageReceived(const QString &contact, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);
    void chatMessageReceived(quint32 chatId, const QString &contact, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);
#endif

    void contactStatusChanged(const QString &phone, TelegramNamespace::ContactStatus status);
    void contactTypingStatusChanged(const QString &contact, TelegramNamespace::MessageAction action);
    void contactChatTypingStatusChanged(quint32 publicChatId, const QString &phone, TelegramNamespace::MessageAction action);

    void sentMessageStatusChanged(const QString &phone, quint64 randomMessageId, TelegramNamespace::MessageDeliveryStatus status);

    void chatAdded(quint32 publichChatId);
    void chatChanged(quint32 publichChatId);

protected slots:
    void whenConnectionAuthChanged(int newState, quint32 dc);
    void whenConnectionStatusChanged(int newStatus, int reason, quint32 dc);
    void whenDcConfigurationUpdated(quint32 dc);
    void whenConnectionDcIdUpdated(quint32 connectionId, quint32 newDcId);
    void whenPackageRedirected(const QByteArray &data, quint32 dc);
    void whenWantedActiveDcChanged(quint32 dc);

#ifndef TELEGRAMQT_NO_DEPRECATED
    void whenPhoneStatusReceived(const QString &phone, bool registered);
#endif

    void whenFileDataReceived(const TLUploadFile &file, quint32 requestId, quint32 offset);
    void whenFileDataUploaded(quint32 requestId);
    void whenUpdatesReceived(const TLUpdates &updates);
    void whenAuthExportedAuthorizationReceived(quint32 dc, quint32 id, const QByteArray &data);

    void whenUsersReceived(const QVector<TLUser> &users);

    void whenContactListReceived(const QVector<quint32> &contactList);
    void whenContactListChanged(const QVector<quint32> &added, const QVector<quint32> &removed);
    void messageActionTimerTimeout();

    void whenMessageSentInfoReceived(const TLInputPeer &peer, quint64 randomId, quint32 messageId, quint32 pts, quint32 date, quint32 seq);
    void whenMessagesHistoryReceived(const TLMessagesMessages &messages);

    void getDcConfiguration();
    void getContacts();
    void getChatsInfo();
    void getUpdatesState();
    void whenUpdatesStateReceived(const TLUpdatesState &updatesState);

    void getDifference();
    void whenUpdatesDifferenceReceived(const TLUpdatesDifference &updatesDifference);

    void whenMessagesChatsReceived(const QVector<TLChat> &chats);
    void whenMessagesFullChatReceived(const TLChatFull &chat, const QVector<TLChat> &chats, const QVector<TLUser> &users);

protected:
    void setConnectionState(TelegramNamespace::ConnectionState state);

    quint32 requestFile(const FileRequestDescriptor &descriptor);
    void processFileRequestForConnection(CTelegramConnection *connection, quint32 requestId);
    void processUpdate(const TLUpdate &update);

    void processMessageReceived(const TLMessage &message);

    void updateChat(const TLChat &newChat);
    void updateFullChat(const TLChatFull &newChat);

    void initConnectionSharedClear();
    void initConnectionSharedFinal(quint32 activeDc = 0);

    void getUser(quint32 id);
    void getInitialUsers();

    bool filterReceivedMessage(quint32 messageFlags) const;

    quint32 publicChatIdToChatId(quint32 publicChatId) const;
    TLInputPeer publicChatIdToInputPeer(quint32 publicChatId) const;
    TLInputPeer identifierToInputPeer(const QString &identifier) const;
    TLInputUser phoneNumberToInputUser(const QString &phoneNumber) const;
    QString userIdToIdentifier(const quint32 id) const;
    QString chatIdToIdentifier(const quint32 id) const;
    QString peerToIdentifier(const TLPeer &peer) const;
    quint32 identifierToUserId(const QString &identifier) const;
    TLUser *identifierToUser(const QString &identifier) const;

    QString userAvatarToken(const TLUser *user) const;

    TelegramNamespace::ContactStatus decodeContactStatus(TLValue status) const;

    inline CTelegramConnection *activeConnection() const { return m_connections.value(m_activeDc); }
    CTelegramConnection *getConnection(quint32 dc);

    CTelegramConnection *createConnection();
    void ensureSignedConnection(CTelegramConnection *connection);

    TLDcOption dcInfoById(quint32 dc) const;

    void setActiveDc(quint32 dc);

    void ensureTypingUpdateTimer(int interval);
    void ensureUpdateState(quint32 pts = 0, quint32 seq = 0, quint32 date = 0);

    void checkStateAndCallGetDifference();
    void tryNextDcAddress();

    void continueInitialization(InitializationStep justDone);

    quint32 telegramChatIdToPublicId(quint32 telegramChatId) const;
    quint32 insertTelegramChatId(quint32 telegramChatId);
    bool havePublicChatId(quint32 publicChatId) const;

    TelegramNamespace::MessageFlags getPublicMessageFlags(const TLMessage &message);

    struct TypingStatus {
        TypingStatus() : chatId(0), userId(0),
            typingTime(0), action(TelegramNamespace::MessageActionNone) { }

        quint32 chatId;
        quint32 userId;
        int typingTime; // (ms)
        TelegramNamespace::MessageAction action;

        static int indexForUser(const QVector<TypingStatus> &statusVector, quint32 userId) {
            for (int i = 0; i < statusVector.count(); ++i) {
                if (statusVector.at(i).chatId) {
                    continue;
                }

                if (statusVector.at(i).userId == userId) {
                    return i;
                }
            }

            return -1;
        }

        static int indexForChatAndUser(const QVector<TypingStatus> &statusVector, quint32 chatId, quint32 userId = 0) {
            for (int i = 0; i < statusVector.count(); ++i) {
                if ((statusVector.at(i).chatId == chatId) && (statusVector.at(i).userId == userId)) {
                    return i;
                }
            }

            return -1;
        }
    };

    TelegramNamespace::ConnectionState m_connectionState;

    const CAppInformation *m_appInformation;

    quint32 m_messageReceivingFilterFlags;
    quint32 m_acceptableMessageTypes;
    bool m_autoReconnectionEnabled;
    quint32 m_pingInterval;
    quint32 m_pingServerAdditionDisconnectionTime;
    quint32 m_mediaDataBufferSize;

    quint32 m_initializationState; // InitializationStep flags
    quint32 m_requestedSteps; // InitializationStep flags

    quint32 m_activeDc;
    quint32 m_wantedActiveDc;
    int m_autoConnectionDcIndex;

    QVector<TelegramNamespace::DcOption> m_connectionAddresses;
    QVector<TLDcOption> m_dcConfiguration;
    QMap<quint32, CTelegramConnection *> m_connections;

    TLUpdatesState m_updatesState; // Current application update state (may be older than actual server-side message box state)
    TLUpdatesState m_actualState; // State reported by server as actual
    bool m_updatesStateIsLocked; // True if we are (going to) getting updatesDifference.
    bool m_emitOnlyIncomingUnreadMessages;

    QMap<quint32, QPair<quint32,QByteArray> > m_exportedAuthentications; // dc, <id, auth data>
    QMap<quint32, QByteArray> m_delayedPackages; // dc, package data
    QMap<quint32, TLUser*> m_users;

    QMap<quint32, QPair<QString, quint64> >m_messagesMap; // message id to phone and big_random message id

    QMap<quint32, TLMessage> m_knownMediaMessages; // message id, message

    quint32 m_selfUserId;

    QVector<quint32> m_contactList;

    // fileId is program-specific handler, not related to Telegram.
    QMap<quint32, FileRequestDescriptor> m_requestedFileDescriptors; // fileId, file request descriptor
    quint32 m_fileRequestCounter;

    QTimer *m_typingUpdateTimer;
    QVector<TypingStatus> m_contactsMessageActions;
    QVector<TypingStatus> m_localMessageActions;

    TLVector<quint32> m_chatIds; // Telegram chat ids vector. Index is "public chat id".
    QMap<quint64, quint32> m_temporaryChatIdMap; // RPC message (request) id to public chat id map

    QMap<quint32, TLChat> m_chatInfo; // Telegram chat id to Chat map
    QMap<quint32, TLChatFull> m_chatFullInfo; // Telegram chat id to ChatFull map

};

#endif // CTELEGRAMDISPATCHER_HPP
