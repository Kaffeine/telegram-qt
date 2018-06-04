/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMNAMESPACE_HPP
#define TELEGRAMNAMESPACE_HPP

#include "telegramqt_global.h"

#include <QObject>
#include <QFlags>
#include <QMetaType>

class CTelegramDispatcher;
class CTelegramAuthModule;
class CTelegramMediaModule;

#ifndef Q_ENUM
#define Q_ENUM(x) Q_ENUMS(x)
#endif

class TELEGRAMQT_EXPORT TelegramNamespace : public QObject
{
    Q_OBJECT
public:
    enum ContactStatus {
        ContactStatusUnknown,
        ContactStatusOffline,
        ContactStatusOnline
    };
    Q_ENUM(ContactStatus)

    enum MessageFlag {
        MessageFlagNone      = 0x0,
        MessageFlagRead      = 0x1, // Message was read
        MessageFlagOut       = 0x2, // Message is outgoing
        MessageFlagForwarded = 0x4,
        MessageFlagIsReply   = 0x8,
    };
    Q_ENUM(MessageFlag)
    Q_DECLARE_FLAGS(MessageFlags, MessageFlag)

    enum MessageType {
        MessageTypeUnsupported = 0x00,
        MessageTypeText        = 0x01,
        MessageTypePhoto       = 0x02,
        MessageTypeAudio       = 0x04,
        MessageTypeVideo       = 0x08,
        MessageTypeContact     = 0x10,
        MessageTypeDocument    = 0x20,
        MessageTypeGeo         = 0x40,
        MessageTypeWebPage     = 0x80,
        MessageTypeAll         = 0xff
    };
    Q_ENUM(MessageType)
    Q_DECLARE_FLAGS(MessageTypeFlags, MessageType)

    enum AuthSignError {
        AuthSignErrorUnknown,
        AuthSignErrorAppIdIsInvalid,
        AuthSignErrorPhoneNumberIsInvalid,
        AuthSignErrorPhoneNumberIsOccupied,
        AuthSignErrorPhoneNumberIsUnoccupied,
        AuthSignErrorPhoneCodeIsInvalid,
        AuthSignErrorPhoneCodeIsExpired,
        AuthSignErrorPasswordHashInvalid,
        AuthSignErrorFirstNameIsInvalid,
        AuthSignErrorLastNameIsInvalid
    };
    Q_ENUM(AuthSignError)

    enum UnauthorizedError {
        UnauthorizedUnknownError,
        UnauthorizedErrorKeyUnregistered,
        UnauthorizedErrorKeyInvalid,
        UnauthorizedErrorUserDeactivated,
        UnauthorizedErrorUserSessionRevoked,
        UnauthorizedErrorUserSessionExpired,
        UnauthorizedErrorActiveUserRequired,
        UnauthorizedErrorNeedPermanentKey,
        UnauthorizedSessionPasswordNeeded,
    };
    Q_ENUM(UnauthorizedError)

    enum UserNameStatus {
        UserNameStatusUnknown,
        UserNameStatusIsInvalid,
        UserNameStatusIsOccupied,
        UserNameStatusIsNotModified,
        UserNameStatusCanBeUsed,
        UserNameStatusCanNotBeUsed,
        UserNameStatusResolved,
        UserNameStatusAccepted
    };
    Q_ENUM(UserNameStatus)

    enum ConnectionState {
        ConnectionStateDisconnected,
        ConnectionStateConnecting,
        ConnectionStateConnected,
        ConnectionStateAuthRequired,
        ConnectionStateAuthenticated,
        ConnectionStateReady // Initializated
    };
    Q_ENUM(ConnectionState)

    enum ContactLastOnline {
        ContactLastOnlineUnknown,
        ContactLastOnlineRecently,
        ContactLastOnlineLastWeek,
        ContactLastOnlineLastMonth,
        ContactLastOnlineMask = 0xf
    };

    enum MessageAction {
        MessageActionNone, // Cancel
        MessageActionTyping,
        MessageActionRecordVideo,
        MessageActionRecordAudio,
        MessageActionUploadVideo,
        MessageActionUploadAudio,
        MessageActionUploadPhoto,
        MessageActionUploadDocument,
        MessageActionGeoLocation,
        MessageActionChooseContact
    };
    Q_ENUM(MessageAction)

    static void registerTypes();
};

namespace Telegram {

void initialize();

struct RsaKey {
    QByteArray modulus;
    QByteArray exponent;
    QByteArray secretExponent;
    quint64 fingerprint;

    RsaKey() :
        fingerprint(0)
    {
    }

    RsaKey(const QByteArray &initialModulus, const QByteArray &initialExponent, const quint64 initialFingersprint = 0) :
        modulus(initialModulus), exponent(initialExponent), fingerprint(initialFingersprint)
    {
    }

    RsaKey &operator=(const RsaKey &otherKey)
    {
        modulus = otherKey.modulus;
        exponent = otherKey.exponent;
        secretExponent = otherKey.secretExponent;
        fingerprint = otherKey.fingerprint;
        return *this;
    }

    void updateFingersprint();
    bool isValid() const;

    void loadFromFile(const QString &fileName);

    static RsaKey fromFile(const QString &fileName);
};

class UserInfo;
class RemoteFile;
class MessageMediaInfo;

enum class PeerPictureSize {
    Small,
    Big,
};

struct Peer
{
    enum Type {
        User,
        Chat,
        Channel,
    };

    Peer(quint32 id = 0, Type t = User) : type(t), id(id)
    {
    }

    Type type;
    quint32 id;

    bool isValid() const { return id; }

    bool operator==(const Peer &p) const
    {
        return (p.type == type) && (p.id == id);
    }

    static Peer fromUserId(quint32 id)
    {
        return Peer(id, User);
    }

    static Peer fromChatId(quint32 id)
    {
        return Peer(id, Chat);
    }

    static Peer fromChannelId(quint32 id)
    {
        return Peer(id, Channel);
    }
};

struct DcOption
{
    DcOption() : port(0) { }
    DcOption(const QString &a, quint32 p) : address(a), port(p) { }
    QString address;
    quint32 port;
};

class PasswordInfo
{
    Q_GADGET
    Q_PROPERTY(QByteArray newSalt READ newSalt)
    Q_PROPERTY(QString emailUnconfirmedPattern READ emailUnconfirmedPattern)
    Q_PROPERTY(QByteArray currentSalt READ currentSalt)
    Q_PROPERTY(QString hint READ hint)
    Q_PROPERTY(bool hasRecovery READ hasRecovery)
public:
    PasswordInfo();
    PasswordInfo(const PasswordInfo &otherData);
    ~PasswordInfo();

    PasswordInfo &operator=(const PasswordInfo &otherData);

    QByteArray newSalt();
    QString emailUnconfirmedPattern();
    QByteArray currentSalt();
    QString hint();
    bool hasRecovery();

protected:
    friend class ::CTelegramAuthModule;
    class Private;

    Private *d;
};

struct Message
{
    Message() :
        replyToMessageId(0),
        forwardContactId(0),
        id(0),
        timestamp(0),
        fwdTimestamp(0),
        type(TelegramNamespace::MessageTypeUnsupported),
        flags(TelegramNamespace::MessageFlagNone)
    {

    }

    quint32 fromId; // Telegram user id

    const Peer peer() const { return m_peer; }
    void setPeer(const Peer &peer) { m_peer = peer; }

    const Peer forwardFromPeer() const { return m_forwardPeer; }
    void setForwardFromPeer(const Peer &peer) { m_forwardPeer = peer; }

    quint32 replyToMessageId;
    quint32 forwardContactId;
    QString text;
    quint32 id;
    quint32 timestamp;
    quint32 fwdTimestamp;
    TelegramNamespace::MessageType type;
    TelegramNamespace::MessageFlags flags;

private:
    Peer m_peer;
    Peer m_forwardPeer;
};

class MessageMediaInfo
{
public:
    MessageMediaInfo();
    MessageMediaInfo(const MessageMediaInfo &info);
    ~MessageMediaInfo();

    MessageMediaInfo &operator=(const MessageMediaInfo &info);

    void setUploadFile(TelegramNamespace::MessageType type, const RemoteFile &file);

    bool getRemoteFileInfo(RemoteFile *file) const;

    TelegramNamespace::MessageType type() const;

    quint32 size() const;

    quint32 duration() const;
    bool setDuration(quint32 duration);

    QString documentFileName() const;
    bool setDocumentFileName(const QString &fileName);

    // Photo, Video
    QString caption() const;
    void setCaption(const QString &caption);

    // Valid for Document and Audio
    QString mimeType() const;
    bool setMimeType(const QString &mimeType);

    // Contact
    bool getContactInfo(UserInfo *info) const;
    void setContactInfo(const UserInfo *info);

    // Valid for GeoPoint and Document/Sticker
    QString alt() const;

    // GeoPoint
    double latitude() const;
    double longitude() const;
    void setGeoPoint(double latitude, double longitude);

    QString url() const;
    QString displayUrl() const;
    QString siteName() const;
    QString title() const;
    QString description() const;

protected:
    friend class ::CTelegramDispatcher;
    friend class ::CTelegramMediaModule;
    class Private;

    Private *d;
};

class RemoteFile
{
public:
    enum Type {
        Undefined,
        Download,
        Upload
    };
    RemoteFile();
    RemoteFile(const RemoteFile &file);
    ~RemoteFile();

    RemoteFile &operator=(const RemoteFile &file);

    Type type() const;

    bool isValid() const;
    QString getUniqueId() const;
    static RemoteFile fromUniqueId(const QString &uniqueId);

    QString fileName() const;
    quint32 size() const;
    QString md5Sum() const;

protected:
    friend class ::CTelegramMediaModule;
    friend class UserInfo;
    friend class ChatInfo;
    friend class MessageMediaInfo;
    class Private;

    Private *d;
};

class DialogInfo
{
public:
    DialogInfo();
    DialogInfo(const DialogInfo &info);
    virtual ~DialogInfo();

    DialogInfo &operator=(const DialogInfo &info);

    Peer peer() const;
    quint32 muteUntil() const;
    bool isStillMuted() const;

protected:
    friend class ::CTelegramDispatcher;
    class Private;

    Private *d;
};

class UserInfo
{
public:
    UserInfo();
    UserInfo(const UserInfo &info);
    ~UserInfo();

    UserInfo &operator=(const UserInfo &info);

    quint32 id() const;
    QString firstName() const;
    QString lastName() const;
    QString userName() const;
    QString phone() const;
    TelegramNamespace::ContactStatus status() const;
    quint32 wasOnline() const;
    bool isBot() const;
    bool isSelf() const;
    bool isContact() const;
    bool isMutualContact() const;
    bool isDeleted() const;

    quint32 botVersion() const;
    bool getPeerPicture(RemoteFile *file, PeerPictureSize size = PeerPictureSize::Small) const;

    // See TelegramNamespace::ContactLastOnline enum and a documentation for the contactLastOnline() method in the cpp file.

protected:
    friend class ::CTelegramDispatcher;
    friend class MessageMediaInfo;
    class Private;

    Private *d;
};

class ChatInfo
{
public:
    ChatInfo();
    ChatInfo(const ChatInfo &info);
    ~ChatInfo();

    ChatInfo &operator=(const ChatInfo &info);

    Peer peer() const;

    QString title() const;
    quint32 participantsCount() const;
    quint32 date() const;
    bool left() const;
    bool broadcast() const;
    Peer migratedTo() const;

    bool getPeerPicture(RemoteFile *file, PeerPictureSize size = PeerPictureSize::Small) const;

protected:
    friend class ::CTelegramDispatcher;
    friend class MessageMediaInfo;
    class Private;

    Private *d;
};

namespace Utils
{

QString maskPhoneNumber(const QString &identifier);
QStringList maskPhoneNumber(const QStringList &list);

template <typename T>
T maskPhoneNumber(T container, const QString &key)
{
    if (container.contains(key)) {
        container.insert(key, maskPhoneNumber(container.value(key).toString()));
    }
    return container;
}

} // Utils namespace

} // Telegram namespace

Q_DECLARE_METATYPE(Telegram::Peer)
Q_DECLARE_METATYPE(Telegram::DcOption)
Q_DECLARE_METATYPE(Telegram::Message)
Q_DECLARE_METATYPE(Telegram::ChatInfo)
Q_DECLARE_METATYPE(Telegram::RemoteFile)
Q_DECLARE_METATYPE(Telegram::UserInfo)
Q_DECLARE_METATYPE(Telegram::PasswordInfo)

Q_DECLARE_TYPEINFO(Telegram::DcOption, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::Message, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::ChatInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::RemoteFile, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::UserInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::PasswordInfo, Q_MOVABLE_TYPE);

Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageTypeFlags)

#endif // TELEGRAMNAMESPACE_HPP
