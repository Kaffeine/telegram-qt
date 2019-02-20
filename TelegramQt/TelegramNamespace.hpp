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
#include <QVector>

#ifndef Q_ENUM
#define Q_ENUM(x) Q_ENUMS(x)
#endif

namespace Telegram {

TELEGRAMQT_EXPORT QString version();
TELEGRAMQT_EXPORT QString buildVersion();

struct TELEGRAMQT_EXPORT Peer
{
    Q_GADGET
    Q_PROPERTY(Telegram::Peer::Type type MEMBER type)
    Q_PROPERTY(quint32 id MEMBER id)
public:
    enum Type {
        User,
        Chat,
        Channel,
    };
    Q_ENUM(Type)

    Peer(quint32 id = 0, Type t = User) : type(t), id(id)
    {
    }

    Type type = User;
    quint32 id = 0;

    Q_INVOKABLE bool isValid() const { return id; }

    bool operator==(const Peer &p) const
    {
        return (p.id == id) && (p.type == type);
    }

    bool operator!=(const Peer &p) const
    {
        return (p.id != id) || (p.type != type);
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

    QString toString() const;
    static Peer fromString(const QString &string);
};

using PeerList = QVector<Peer>;

inline uint qHash(const Peer &key, uint seed)
{
    return ::qHash(static_cast<ulong>(key.id | (static_cast<quint64>(key.type) << (sizeof(key.id) * 8))), seed);
}

} // Telegram namespace

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
        MessageTypeUnsupported = 0x0000,
        MessageTypeText        = 0x0001,
        MessageTypePhoto       = 0x0002,
        MessageTypeAudio       = 0x0004,
        MessageTypeVideo       = 0x0008,
        MessageTypeContact     = 0x0010,
        MessageTypeDocument    = 0x0020,
        MessageTypeGeo         = 0x0040,
        MessageTypeWebPage     = 0x0080,
        MessageTypeSticker     = 0x0100,
        MessageTypeAnimation   = 0x0200,
        MessageTypeAll         = 0xffff,
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
    Q_INVOKABLE static Telegram::Peer emptyPeer();
    Q_INVOKABLE static Telegram::Peer peerFromChatId(quint32 id);
    Q_INVOKABLE static Telegram::Peer peerFromChannelId(quint32 id);
    Q_INVOKABLE static Telegram::Peer peerFromUserId(quint32 id);
};

namespace Telegram {

TELEGRAMQT_EXPORT void initialize();

class UserInfo;
class RemoteFile;
class MessageMediaInfo;

enum class PeerPictureSize {
    Small,
    Big,
};

struct TELEGRAMQT_EXPORT DcOption
{
    enum Flags {
        Ipv6 = 1 << 0,
        MediaOnly = 1 << 1,
        TcpOnly = 1 << 2,
        Cdn = 1 << 3,
        IsStatic = 1 << 4,
    };

    DcOption() = default;
    DcOption(const QString &a, quint16 p, quint32 dcId = 0) : address(a), id(dcId), port(p) { }
    bool operator==(const DcOption &option) const;
    bool isValid() const { return id && port && !address.isEmpty(); }

    QString address;
    quint32 id = 0;
    quint16 port = 0;
    quint16 flags = 0;
};

inline bool DcOption::operator==(const DcOption &option) const
{
    return (option.id == id) && (option.port == port) && (option.address == address) && (option.flags == flags);
}

struct TELEGRAMQT_EXPORT Message
{
    Message() = default;
    const Peer peer() const { return m_peer; }
    void setPeer(const Peer &peer) { m_peer = peer; }

    const Peer forwardFromPeer() const { return m_forwardPeer; }
    void setForwardFromPeer(const Peer &peer) { m_forwardPeer = peer; }

    QString text;
    quint32 id = 0;
    quint32 fromId = 0; // Telegram user id
    quint32 timestamp = 0;
    quint32 fwdTimestamp = 0;
    quint32 forwardContactId = 0;
    quint32 replyToMessageId = 0;
    TelegramNamespace::MessageType type = TelegramNamespace::MessageTypeUnsupported;
    TelegramNamespace::MessageFlags flags = TelegramNamespace::MessageFlagNone;

private:
    Peer m_peer;
    Peer m_forwardPeer;
};

class TELEGRAMQT_EXPORT MessageMediaInfo
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

    struct Private;

protected:
    Private *d;
};

class TELEGRAMQT_EXPORT RemoteFile
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

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT DialogInfo
{
public:
    DialogInfo();
    DialogInfo(const DialogInfo &info);
    virtual ~DialogInfo();

    DialogInfo &operator=(const DialogInfo &info);

    quint32 unreadCount() const;
    QString draft() const;
    quint32 lastMessageId() const;
    quint32 readInboxMaxId() const;
    quint32 readOutboxMaxId() const;

    Peer peer() const;
    quint32 muteUntil() const;
    bool isStillMuted() const;

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT UserInfo
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

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT ChatInfo
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

    struct Private;
protected:
    Private *d;
};

namespace Utils
{

quint64 maskNumber(quint64 number);
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

TELEGRAMQT_EXPORT QVector<quint32> toIdList(const Telegram::PeerList &peerList);

} // Utils namespace

} // Telegram namespace

Q_DECLARE_METATYPE(Telegram::Peer)
Q_DECLARE_METATYPE(Telegram::Peer::Type)
Q_DECLARE_METATYPE(Telegram::PeerList)
Q_DECLARE_METATYPE(Telegram::DcOption)
Q_DECLARE_METATYPE(Telegram::Message)
Q_DECLARE_METATYPE(Telegram::ChatInfo)
Q_DECLARE_METATYPE(Telegram::RemoteFile)
Q_DECLARE_METATYPE(Telegram::UserInfo)

Q_DECLARE_TYPEINFO(Telegram::DcOption, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::Message, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::ChatInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::RemoteFile, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::UserInfo, Q_MOVABLE_TYPE);

Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(TelegramNamespace::MessageTypeFlags)

#endif // TELEGRAMNAMESPACE_HPP
