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

#include "TelegramNamespace.hpp"
#include "TelegramNamespace_p.hpp"

#include "TelegramUtils.hpp"

using namespace TelegramUtils;

#include <QMetaType>
#include <QDebug>

QDebug operator<<(QDebug d, const Telegram::Peer &peer)
{
    switch (peer.type) {
    case Telegram::Peer::User:
        d << "Telegram::Peer(User, " << peer.id << ")";
        break;
    case Telegram::Peer::Chat:
        d << "Telegram::Peer(Chat, " << peer.id << ")";
        break;
    case Telegram::Peer::Channel:
        d << "Telegram::Peer(Channel, " << peer.id << ")";
        break;
    default:
        d << "Telegram::Peer(Invalid:" << peer.type << ", " << peer.id << ")";
        break;
    }
    return d;
}

void TelegramNamespace::registerTypes()
{
    static bool registered = false;
    if (!registered) {

#ifdef DEVELOPER_BUILD
        qDebug() << "TelegramQt Developer build";
#endif

        qRegisterMetaType<TelegramNamespace::ConnectionState>("TelegramNamespace::ConnectionStatus");
        qRegisterMetaType<TelegramNamespace::ContactStatus>("TelegramNamespace::ContactStatus");
        qRegisterMetaType<TelegramNamespace::MessageFlags>("TelegramNamespace::MessageFlags");
        qRegisterMetaType<TelegramNamespace::MessageType>("TelegramNamespace::MessageType");
        qRegisterMetaType<TelegramNamespace::AuthSignError>("TelegramNamespace::AuthSignError");
        qRegisterMetaType<TelegramNamespace::UnauthorizedError>("TelegramNamespace::UnauthorizedError");
        qRegisterMetaType<Telegram::PasswordInfo>("Telegram::PasswordInfo");
        registered = true;
    }
}

Telegram::MessageMediaInfo::MessageMediaInfo() :
    d(new Private())
{
}

Telegram::MessageMediaInfo::MessageMediaInfo(const Telegram::MessageMediaInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

Telegram::MessageMediaInfo::~MessageMediaInfo()
{
    delete d;
}

Telegram::MessageMediaInfo &Telegram::MessageMediaInfo::operator=(const Telegram::MessageMediaInfo &info)
{
    *d = *info.d;
    return *this;
}

void Telegram::MessageMediaInfo::setUploadFile(TelegramNamespace::MessageType type, const RemoteFile &file)
{
    d->tlType = publicMessageTypeToTelegramMessageType(type);

    d->m_isUploaded = true;
    d->m_size = file.d->m_size;

    if (!d->m_inputFile) {
        d->m_inputFile = new TLInputFile(*file.d->m_inputFile);
    }
}

bool Telegram::MessageMediaInfo::getRemoteFileInfo(Telegram::RemoteFile *file) const
{
    TLInputFileLocation inputLocation;

    switch (d->tlType) {
    case TLValue::MessageMediaPhoto:
        if (d->photo.sizes.isEmpty()) {
            return false;
        } else {
            const TLPhotoSize s = d->photo.sizes.last();
            file->d->m_size = s.size;
            file->d->m_type = Telegram::RemoteFile::Download;
            return file->d->setFileLocation(&s.location);
        }
    case TLValue::MessageMediaAudio:
        inputLocation.tlType = TLValue::InputAudioFileLocation;
        inputLocation.id = d->audio.id;
        inputLocation.accessHash = d->audio.accessHash;
        file->d->setInputFileLocation(&inputLocation);
        file->d->m_size = d->audio.size;
        file->d->m_dcId = d->audio.dcId;
        file->d->m_type = Telegram::RemoteFile::Download;
        return true;
    case TLValue::MessageMediaVideo:
        inputLocation.tlType = TLValue::InputVideoFileLocation;
        inputLocation.id = d->video.id;
        inputLocation.accessHash = d->video.accessHash;
        file->d->setInputFileLocation(&inputLocation);
        file->d->m_size = d->video.size;
        file->d->m_dcId = d->video.dcId;
        file->d->m_type = Telegram::RemoteFile::Download;
        return true;
    case TLValue::MessageMediaDocument:
        inputLocation.tlType = TLValue::InputDocumentFileLocation;
        inputLocation.id = d->document.id;
        inputLocation.accessHash = d->document.accessHash;
        file->d->setInputFileLocation(&inputLocation);
        file->d->m_size = d->document.size;
        file->d->m_dcId = d->document.dcId;
        file->d->m_type = Telegram::RemoteFile::Download;
        return true;
    default:
        return false;
    }
}

TelegramNamespace::MessageType Telegram::MessageMediaInfo::type() const
{
    return telegramMessageTypeToPublicMessageType(d->tlType);
}

quint32 Telegram::MessageMediaInfo::size() const
{
    if (d->m_isUploaded) {
        return d->m_size;
    }

    switch (d->tlType) {
    case TLValue::MessageMediaPhoto:
        if (d->photo.sizes.isEmpty()) {
            return 0;
        }
        return d->photo.sizes.last().size;
    case TLValue::MessageMediaAudio:
        return d->audio.size;
    case TLValue::MessageMediaVideo:
        return d->video.size;
    case TLValue::MessageMediaDocument:
        return d->document.size;
    default:
        return 0;
    }
}

quint32 Telegram::MessageMediaInfo::duration() const
{
    switch (d->tlType) {
    case TLValue::MessageMediaAudio:
        return d->audio.duration;
    case TLValue::MessageMediaVideo:
        return d->video.duration;
    default:
        return 0;
    }
}

bool Telegram::MessageMediaInfo::setDuration(quint32 duration)
{
    switch (d->tlType) {
    case TLValue::MessageMediaAudio:
        d->audio.duration = duration;
        return true;
    case TLValue::MessageMediaVideo:
        d->video.duration = duration;
        return true;
    default:
        break;
    }
    return false;
}

QString Telegram::MessageMediaInfo::documentFileName() const
{
    if (d->tlType != TLValue::MessageMediaDocument) {
        return QString();
    }

    foreach (const TLDocumentAttribute &attribute, d->document.attributes) {
        if (attribute.tlType == TLValue::DocumentAttributeFilename) {
            return attribute.fileName;
        }
    }

    return QString();
}

bool Telegram::MessageMediaInfo::setDocumentFileName(const QString &fileName)
{
    if (d->tlType != TLValue::MessageMediaDocument) {
        return false;
    }

    TLDocumentAttribute *nameAttribute = 0;
    for (int i = 0; i < d->document.attributes.count(); ++i) {
        if (d->document.attributes.at(i).tlType == TLValue::DocumentAttributeFilename) {
            nameAttribute = &d->document.attributes[i];
            break;
        }
    }
    if (!nameAttribute) {
        d->document.attributes.append(TLDocumentAttribute());
        nameAttribute = &d->document.attributes.last();
        nameAttribute->tlType = TLValue::DocumentAttributeFilename;
    }

    nameAttribute->fileName = fileName;

    return true;
}

QString Telegram::MessageMediaInfo::caption() const
{
    return d->caption;
}

void Telegram::MessageMediaInfo::setCaption(const QString &caption)
{
    if (!d->m_isUploaded) {
        return;
    }

    d->caption = caption;
}

QString Telegram::MessageMediaInfo::mimeType() const
{
    switch (d->tlType) {
    case TLValue::MessageMediaDocument:
        return d->document.mimeType;
    case TLValue::MessageMediaAudio:
        return d->audio.mimeType;
    default:
        break;
    }
    return QString();
}

bool Telegram::MessageMediaInfo::setMimeType(const QString &mimeType)
{
    switch (d->tlType) {
    case TLValue::MessageMediaDocument:
        d->document.mimeType = mimeType;
        return true;
    case TLValue::MessageMediaAudio:
        d->audio.mimeType = mimeType;
        return true;
    default:
        break;
    }
    return false;
}

bool Telegram::MessageMediaInfo::getContactInfo(Telegram::UserInfo *info) const
{
    if (d->tlType != TLValue::MessageMediaContact) {
        return false;
    }

    *info->d = UserInfo::Private(); // Reset
    info->d->id = d->userId;
    info->d->firstName = d->firstName;
    info->d->lastName = d->lastName;
    info->d->phone = d->phoneNumber;
    return true;
}

void Telegram::MessageMediaInfo::setContactInfo(const Telegram::UserInfo *info)
{
    d->tlType = TLValue::MessageMediaContact;
    d->firstName = info->d->firstName;
    d->lastName = info->d->lastName;
    d->phoneNumber = info->d->phone;
    d->userId = info->d->id;
}

QString Telegram::MessageMediaInfo::alt() const
{
    switch (d->tlType) {
    case TLValue::MessageMediaGeo:
        return QString(QLatin1String("geo:%1,%2")).arg(d->geo.latitude).arg(d->geo.longitude);
    case TLValue::MessageMediaContact:
    {
        QString name = d->firstName + QLatin1Char(' ') + d->lastName;
        name = name.simplified();
        if (!d->phoneNumber.isEmpty()) {
            const QString phone = QStringLiteral("tel:") + d->phoneNumber;
            if (name.isEmpty()) {
                return phone;
            } else {
                return name + QLatin1Char('\n') + phone;
            }
        }
        return QString();
    }
    case TLValue::MessageMediaDocument:
        foreach (const TLDocumentAttribute &attribute, d->document.attributes) {
            if (attribute.tlType == TLValue::DocumentAttributeSticker) {
                return attribute.alt;
            }
        }
        break;
    default:
        break;
    }
    return QString();
}

double Telegram::MessageMediaInfo::latitude() const
{
    return d->geo.latitude;
}

double Telegram::MessageMediaInfo::longitude() const
{
    return d->geo.longitude;
}

void Telegram::MessageMediaInfo::setGeoPoint(double latitude, double longitude)
{
    d->tlType = TLValue::MessageMediaGeo;
    d->geo.tlType = TLValue::GeoPoint;
    d->geo.longitude = longitude;
    d->geo.latitude = latitude;
}

QString Telegram::MessageMediaInfo::url() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }
    return d->webpage.url;
}

QString Telegram::MessageMediaInfo::displayUrl() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }
    return d->webpage.displayUrl;
}

QString Telegram::MessageMediaInfo::siteName() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.siteName;
}

QString Telegram::MessageMediaInfo::title() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.title;
}

QString Telegram::MessageMediaInfo::description() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.description;
}

Telegram::RemoteFile::RemoteFile():
    d(new Private())
{
}

Telegram::RemoteFile::RemoteFile(const Telegram::RemoteFile &file) :
    d(new Private)
{
    *d = *file.d;
}

Telegram::RemoteFile::~RemoteFile()
{
    delete d;
}

Telegram::RemoteFile &Telegram::RemoteFile::operator=(const Telegram::RemoteFile &file)
{
    *d = *file.d;
    return *this;
}

Telegram::RemoteFile::Type Telegram::RemoteFile::type() const
{
    return d->m_type;
}

bool Telegram::RemoteFile::isValid() const
{
    if (!d || !d->m_inputFileLocation || d->m_type == RemoteFile::Undefined) {
        return false;
    }

    switch (d->m_inputFileLocation->tlType) {
    case TLValue::InputFileLocation:
    case TLValue::InputVideoFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputAudioFileLocation:
    case TLValue::InputDocumentFileLocation:
        return true;
    default:
        return false;
    }
}

QString Telegram::RemoteFile::getUniqueId() const
{
    if (!d || !d->m_dcId) {
        return QString();
    }

    if (!d->m_inputFileLocation) {
        return QString();
    }

    switch (d->m_inputFileLocation->tlType) {
    case TLValue::InputFileLocation:
        return QString(QLatin1String("%1%2%3"))
                .arg(d->m_dcId, sizeof(d->m_dcId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_inputFileLocation->volumeId, sizeof(d->m_inputFileLocation->volumeId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_inputFileLocation->localId, sizeof(d->m_inputFileLocation->localId) * 2, 16, QLatin1Char('0'));
    case TLValue::InputVideoFileLocation:
    case TLValue::InputEncryptedFileLocation:
    case TLValue::InputAudioFileLocation:
    case TLValue::InputDocumentFileLocation:
        return QString(QLatin1String("%1%2%3"))
                .arg(d->m_dcId, sizeof(d->m_dcId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_inputFileLocation->id, sizeof(d->m_inputFileLocation->id) * 2, 16, QLatin1Char('0'))
                .arg(d->m_inputFileLocation->accessHash, sizeof(d->m_inputFileLocation->accessHash) * 2, 16, QLatin1Char('0'));
    default:
        return QString();
    }
}

QString Telegram::RemoteFile::fileName() const
{
    if (!d->m_inputFile) {
        return QString();
    }
    return d->m_inputFile->name;
}

quint32 Telegram::RemoteFile::size() const
{
    return d->m_size;
}

QString Telegram::RemoteFile::md5Sum() const
{
    if (!d->m_inputFile) {
        return QString();
    }
    return d->m_inputFile->md5Checksum;
}

Telegram::UserInfo::UserInfo() :
    d(new Private())
{
}

Telegram::UserInfo::UserInfo(const Telegram::UserInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

Telegram::UserInfo::~UserInfo()
{
    delete d;
}

Telegram::UserInfo &Telegram::UserInfo::operator=(const Telegram::UserInfo &info)
{
    *d = *info.d;
    return *this;
}

quint32 Telegram::UserInfo::id() const
{
    return d->id;
}

QString Telegram::UserInfo::firstName() const
{
    return d->firstName;
}

QString Telegram::UserInfo::lastName() const
{
    return d->lastName;
}

QString Telegram::UserInfo::userName() const
{
    return d->username;
}

QString Telegram::UserInfo::phone() const
{
    return d->phone;
}

TelegramNamespace::ContactStatus Telegram::UserInfo::status() const
{
    return getApiContactStatus(d->status.tlType);
}

quint32 Telegram::UserInfo::wasOnline() const
{
    return getApiContactLastOnline(d->status);
}

bool Telegram::UserInfo::getPeerPicture(Telegram::RemoteFile *file, PeerPictureSize size) const
{
    switch (size) {
    case PeerPictureSize::Big:
        return file->d->setFileLocation(&d->photo.photoBig);
    case PeerPictureSize::Small:
        return file->d->setFileLocation(&d->photo.photoSmall);
    default:
        return false;
    }
}

TelegramNamespace::ContactStatus getApiContactStatus(TLValue status)
{
    switch (status) {
    default:
    case TLValue::UserStatusEmpty:
        return TelegramNamespace::ContactStatusUnknown;
    case TLValue::UserStatusOnline:
        return TelegramNamespace::ContactStatusOnline;
    case TLValue::UserStatusOffline:
        return TelegramNamespace::ContactStatusOffline;
    }
}

quint32 getApiContactLastOnline(const TLUserStatus &status)
{
    switch (status.tlType) {
    case TLValue::UserStatusOnline:
        return status.expires;
    case TLValue::UserStatusOffline:
        return status.wasOnline;
    case TLValue::UserStatusRecently:
        return TelegramNamespace::ContactLastOnlineRecently;
    case TLValue::UserStatusLastWeek:
        return TelegramNamespace::ContactLastOnlineLastWeek;
    case TLValue::UserStatusLastMonth:
        return TelegramNamespace::ContactLastOnlineLastMonth;
    default:
        return TelegramNamespace::ContactLastOnlineUnknown;
    }
}

Telegram::PasswordInfo::PasswordInfo() :
    d(new Private())
{
}

Telegram::PasswordInfo::PasswordInfo(const Telegram::PasswordInfo &otherData) :
    d(new Private())
{
    *d = *otherData.d;
}

Telegram::PasswordInfo::~PasswordInfo()
{
    delete d;
}

Telegram::PasswordInfo &Telegram::PasswordInfo::operator=(const Telegram::PasswordInfo &otherData)
{
    *d = *otherData.d;
    return *this;
}

QByteArray Telegram::PasswordInfo::newSalt()
{
    return d->newSalt;
}

QString Telegram::PasswordInfo::emailUnconfirmedPattern()
{
    return d->emailUnconfirmedPattern;
}

QByteArray Telegram::PasswordInfo::currentSalt()
{
    return d->currentSalt;
}

QString Telegram::PasswordInfo::hint()
{
    return d->hint;
}

bool Telegram::PasswordInfo::hasRecovery()
{
    return d->hasRecovery;
}
