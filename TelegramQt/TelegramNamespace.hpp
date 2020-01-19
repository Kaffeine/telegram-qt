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

#include "Peer.hpp"

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

using PeerList = QVector<Peer>;
using MessageIdList = QVector<quint32>;

struct TELEGRAMQT_EXPORT MessageAction
{
    Q_GADGET
    Q_PROPERTY(Telegram::MessageAction::Type type MEMBER type)
    Q_PROPERTY(quint32 progress MEMBER progress)
public:
    enum Type {
        None, // Cancel
        Typing,
        RecordVideo,
        RecordAudio,
        UploadVideo,
        UploadAudio,
        UploadPhoto,
        UploadDocument,
        UploadRoundVideo,
        GeoLocation,
        ChooseContact
    };
    Q_ENUM(Type)

    MessageAction() = default;
    // The constructor is implicit "on purpose"
    MessageAction(Type t)
        : type(t)
    {
    }

    Type type = None;
    quint32 progress = 0;
};

class TELEGRAMQT_EXPORT Namespace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(QString buildVersion READ buildVersion CONSTANT)
public:
    enum ContactStatus {
        ContactStatusUnknown,
        ContactStatusOffline,
        ContactStatusOnline
    };
    Q_ENUM(ContactStatus)

    enum MessageFlag {
        MessageFlagNone      = 0x0,
        MessageFlagOut       = 0x1, // Message is outgoing
        MessageFlagForwarded = 0x2,
        MessageFlagIsReply   = 0x4,
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

    enum ChatType {
        ChatTypeInvalid,
        ChatTypeSelfChat,
        ChatTypeDialog,
        ChatTypeGroup,
        ChatTypeMegaGroup,
        ChatTypeBroadcast,
    };
    Q_ENUM(ChatType)

    enum AuthenticationError {
        AuthenticationErrorUnknown,
        AuthenticationErrorAppIdInvalid,
        AuthenticationErrorPhoneNumberInvalid,
        AuthenticationErrorPhoneNumberOccupied,
        AuthenticationErrorPhoneNumberUnoccupied,
        AuthenticationErrorPhoneCodeInvalid,
        AuthenticationErrorPhoneCodeExpired,
        AuthenticationErrorPasswordHashInvalid,
        AuthenticationErrorFirstNameInvalid,
        AuthenticationErrorLastNameInvalid,
    };
    Q_ENUM(AuthenticationError)

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

    static QString version() { return Telegram::version(); }
    static QString buildVersion() { return Telegram::buildVersion(); }

    static void registerTypes();
    Q_INVOKABLE static Telegram::Peer emptyPeer();
    Q_INVOKABLE static Telegram::Peer peerFromChatId(quint32 id);
    Q_INVOKABLE static Telegram::Peer peerFromChannelId(quint32 id);
    Q_INVOKABLE static Telegram::Peer peerFromUserId(quint32 id);
};

TELEGRAMQT_EXPORT void initialize();

class UserInfo;
class FileInfo;
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
    Message();
    Message(const Message &message);
    ~Message();

    Peer peer() const;
    quint32 id() const;
    Namespace::MessageType type() const;
    Namespace::MessageFlags flags() const;

    quint32 fromUserId() const;
    QString text() const;
    quint32 timestamp() const;

    quint32 forwardTimestamp() const;
    Peer forwardFromPeer() const;
    quint32 forwardFromMessageId() const;

    struct Private;

protected:
    Private *d;
};

class TELEGRAMQT_EXPORT MessageMediaInfo
{
public:
    MessageMediaInfo();
    MessageMediaInfo(const MessageMediaInfo &info);
    ~MessageMediaInfo();

    MessageMediaInfo &operator=(const MessageMediaInfo &info);

    void setUploadFile(Namespace::MessageType type, const FileInfo &file);

    bool getRemoteFileInfo(FileInfo *file) const;

    Namespace::MessageType type() const;

    quint32 size() const;

    quint32 duration() const;
    bool setDuration(quint32 duration);

    QString documentFileName() const;
    bool setDocumentFileName(const QString &fileName);

    // Photo, Video
    QString caption() const;
    void setCaption(const QString &caption);

    QByteArray getCachedPhoto() const;

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

class TELEGRAMQT_EXPORT FileInfo
{
public:
    enum Type {
        Undefined,
        Download,
        Upload
    };
    FileInfo();
    FileInfo(const FileInfo &file);
    ~FileInfo();

    FileInfo &operator=(const FileInfo &file);

    Type type() const;

    bool isValid() const;
    QString getFileId() const;

    QString fileName() const;
    quint32 size() const;
    QString md5Sum() const;
    QString mimeType() const;

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT PeerInfo
{
public:
    virtual Peer peer() const = 0;
    virtual bool getPeerPicture(FileInfo *file, PeerPictureSize size) const = 0;
    virtual QString displayName() const = 0;
};

class TELEGRAMQT_EXPORT DialogInfo
{
public:
    DialogInfo();
    DialogInfo(const DialogInfo &info);
    virtual ~DialogInfo();

    DialogInfo &operator=(const DialogInfo &info);

    Peer peer() const;

    bool isPinned() const;
    quint32 unreadCount() const;
    QString draft() const;
    quint32 lastMessageId() const;
    quint32 readInboxMaxId() const;
    quint32 readOutboxMaxId() const;

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT UserInfo : public PeerInfo
{
public:
    UserInfo();
    UserInfo(const UserInfo &info);
    ~UserInfo();

    UserInfo &operator=(const UserInfo &info);

    Peer peer() const final;
    QString displayName() const final;
    bool getPeerPicture(FileInfo *file, PeerPictureSize size) const final;

    QString getBestDisplayName() const;

    quint32 id() const;
    QString firstName() const;
    QString lastName() const;
    QString userName() const;
    QString phone() const;
    Namespace::ContactStatus status() const;
    quint32 wasOnline() const;
    bool isBot() const;
    bool isSelf() const;
    bool isContact() const;
    bool isMutualContact() const;
    bool isDeleted() const;

    quint32 botVersion() const;
    // See TelegramNamespace::ContactLastOnline enum and a documentation for the contactLastOnline() method in the cpp file.

    struct Private;
protected:
    Private *d;
};

class TELEGRAMQT_EXPORT ChatInfo : public PeerInfo
{
public:
    ChatInfo();
    ChatInfo(const ChatInfo &info);
    ~ChatInfo();

    ChatInfo &operator=(const ChatInfo &info);

    Peer peer() const final;
    QString displayName() const final;
    bool getPeerPicture(FileInfo *file, PeerPictureSize size) const final;

    QString title() const;
    quint32 participantsCount() const;
    quint32 date() const;
    bool left() const;
    bool broadcast() const;
    Peer migratedTo() const;

    struct Private;
protected:
    Private *d;
};

namespace Utils
{

TELEGRAMQT_EXPORT quint64 maskNumber(quint64 number);
TELEGRAMQT_EXPORT QString maskString(const QString &string);
TELEGRAMQT_EXPORT QByteArray maskByteArray(const QByteArray &data);
TELEGRAMQT_EXPORT QString maskPhoneNumber(const QString &identifier);
TELEGRAMQT_EXPORT QStringList maskPhoneNumber(const QStringList &list);

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

Q_DECLARE_METATYPE(Telegram::MessageAction)
Q_DECLARE_METATYPE(Telegram::Peer)
Q_DECLARE_METATYPE(Telegram::Peer::Type)
Q_DECLARE_METATYPE(Telegram::PeerList)
Q_DECLARE_METATYPE(Telegram::DcOption)
Q_DECLARE_METATYPE(Telegram::Message)
Q_DECLARE_METATYPE(Telegram::ChatInfo)
Q_DECLARE_METATYPE(Telegram::FileInfo)
Q_DECLARE_METATYPE(Telegram::UserInfo)

Q_DECLARE_TYPEINFO(Telegram::MessageAction, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::DcOption, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::Message, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::ChatInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::FileInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::DialogInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(Telegram::UserInfo, Q_MOVABLE_TYPE);

Q_DECLARE_OPERATORS_FOR_FLAGS(Telegram::Namespace::MessageFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(Telegram::Namespace::MessageTypeFlags)

#endif // TELEGRAMNAMESPACE_HPP
