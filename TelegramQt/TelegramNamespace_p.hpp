/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMNAMESPACE_P_HPP
#define TELEGRAMNAMESPACE_P_HPP

#include "MTProto/TLTypes.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

struct TELEGRAMQT_INTERNAL_EXPORT UserDialog
{
    using Flags = TLDialog::Flags;
    Telegram::Peer peer;
    QString draftText;
    quint32 topMessage = 0;
    quint64 date = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 unreadMentionsCount = 0;
    quint32 pts = 0;
    quint32 flags = 0;
};

// The parent Message class is marked as exportable, so we have to explicitly hide the private structs.
struct TELEGRAMQT_INTERNAL_EXPORT Message::Private
{
    static const Private *get(const Message *info) { return info->d; }
    static Private *get(Message *info) { return info->d; }

    void reset();
    void setForwardFromUser(quint32 userId);
    void setForwardFromChannel(quint32 channelId, quint32 messageId, const QString &postAuthor);

    void setReplyToMessageId(quint32 messageId);

    QString text;
    quint32 id = 0;
    quint32 fromId = 0; // Telegram user id
    quint32 timestamp = 0;
    quint32 forwardTimestamp = 0;
    quint32 replyToMessageId = 0;
    Namespace::MessageType type = Namespace::MessageTypeUnsupported;
    Namespace::MessageFlags flags = Namespace::MessageFlagNone;

    Peer peer;
    QString forwardPostAuthor;
    Peer forwardFromPeer;
    quint32 forwardFromMessageId = 0;
};

struct TELEGRAMQT_INTERNAL_EXPORT MessageMediaInfo::Private : public TLMessageMedia
{
public:
    static const Private *get(const MessageMediaInfo *info) { return info->d; }
    static Private *get(MessageMediaInfo *info) { return info->d; }

    Private() = default;

    ~Private()
    {
        delete m_inputFile;
    }

    void operator=(const TLMessageMedia &mediaInfo)
    {
        m_isUploaded = false;
        m_size = 0;
        m_inputFile = nullptr;

        TLMessageMedia *thisInfo = this;
        *thisInfo = mediaInfo;
    }

    bool m_isUploaded = false;
    quint32 m_size = 0;
    TLInputFile *m_inputFile = nullptr;
};

struct TELEGRAMQT_INTERNAL_EXPORT FileInfo::Private
{
public:
    enum Type {
        InvalidLocation,
        FileLocation,
        EncryptedFileLocation,
        VideoFileLocation,
        AudioFileLocation,
        DocumentFileLocation,
        UploadInputFile,
        UploadInputFileBig,
    };

    Private() = default;
    static Private fromFileId(const QString &fileId);

    static const Private *get(const FileInfo *f) { return f->d; }
    static Private *get(FileInfo *f) { return f->d; }
    static void set(FileInfo *f, Private *p) { f->d = p; }

    bool isValid() const;

    TLInputFileLocation getInputFileLocation() const;
    bool setInputFileLocation(const TLInputFileLocation *inputFileLocation);

    TLInputFile getInputFile() const;
    bool setInputFile(const TLInputFile *inputFile);

    TLFileLocation getFileLocation() const;
    bool setFileLocation(const TLFileLocation *fileLocation);

    quint32 dcId() const { return m_dcId; }
    quint32 size() const { return m_size; }

    void setMimeType(const QString &mimeType);

    Type m_type = InvalidLocation;

    // FileLocation:
    quint64 m_volumeId = 0;
    quint32 m_localId = 0;
    quint64 m_secret = 0;
    quint32 m_dcId = 0;

    // InputFileLocation:
//    quint64 m_volumeId;
//    quint32 m_localId;
//    quint64 m_secret;
    quint64 m_id = 0;
    quint64 m_accessHash = 0;

    // InputFile:
//    quint64 m_id;
    quint32 m_parts = 0;
    quint32 m_size = 0;
    QString m_name;
    QString m_md5Checksum;
    QString m_mimeType;

};

struct TELEGRAMQT_INTERNAL_EXPORT UserInfo::Private : public TLUser
{
    static Private *get(UserInfo *info) { return info->d; }
    static const Private *get(const UserInfo *info) { return info->d; }
};

struct TELEGRAMQT_INTERNAL_EXPORT ChatInfo::Private : public TLChat
{
    static Private *get(ChatInfo *info) { return info->d; }
};

struct TELEGRAMQT_INTERNAL_EXPORT DialogInfo::Private : public UserDialog
{
    static Private *get(DialogInfo *info) { return info->d; }
};

Namespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

} // Telegram namespace

#endif // TELEGRAMNAMESPACE_P_HPP
