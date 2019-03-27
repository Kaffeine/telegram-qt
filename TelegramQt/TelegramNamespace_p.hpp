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

class NotificationSettingsData : public QSharedData
{
public:
    using SharedPtr = QSharedDataPointer<NotificationSettingsData>;

    NotificationSettingsData() = default;
    NotificationSettingsData(const NotificationSettingsData &other) :
        QSharedData(other),
        flags(other.flags)
    {
    }

    // Peer notification settings exist independent of dialogs
    enum Flags {
        ShowPreviews = 1 << 0,
        Silent = 1 << 1,
    };
    bool showPreviews() const { return flags & ShowPreviews; }
    bool silent() const { return flags & Silent; }

    static constexpr quint32 c_muteForever = ~quint32(0) >> 1; // 2147483647

    quint32 flags = 0;
    quint32 muteUntil = 0;
    QString sound;

    static const NotificationSettingsData &getDefaultSettingsData();
};

struct UserDialog
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

struct MessageMediaInfo::Private : public TLMessageMedia
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

struct RemoteFile::Private
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

    static const Private *get(const RemoteFile *f) { return f->d; }
    static Private *get(RemoteFile *f) { return f->d; }
    static void set(RemoteFile *f, Private *p) { f->d = p; }

    TLInputFileLocation getInputFileLocation() const;
    bool setInputFileLocation(const TLInputFileLocation *inputFileLocation);

    TLInputFile getInputFile() const;
    bool setInputFile(const TLInputFile *inputFile);

    TLFileLocation getFileLocation() const;
    bool setFileLocation(const TLFileLocation *fileLocation);

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

};

struct UserInfo::Private : public TLUser
{
    static Private *get(UserInfo *info) { return info->d; }
    static const Private *get(const UserInfo *info) { return info->d; }
};

struct ChatInfo::Private : public TLChat
{
    static Private *get(ChatInfo *info) { return info->d; }
};

struct DialogInfo::Private : public UserDialog
{
    static Private *get(DialogInfo *info) { return info->d; }
};

class NotificationSettings::Private : public NotificationSettingsData
{
public:
    static NotificationSettings::DataPtr get(const NotificationSettings *info) { return info->d; }
    static NotificationSettings::DataPtr &get(NotificationSettings *info) { return info->d; }
};

Namespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

} // Telegram namespace

#endif // TELEGRAMNAMESPACE_P_HPP
