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

#include "TelegramNamespace.hpp"
#include "TelegramNamespace_p.hpp"

#include "ApiUtils.hpp"
#include "RandomGenerator.hpp"
#include "Utils.hpp"

#include "ConnectionApi.hpp"

#include <QDateTime>
#include <QMetaType>
#include <QDebug>

static const QLatin1String c_userPrefix = QLatin1String("user");
static const QLatin1String c_chatPrefix = QLatin1String("chat");
static const QLatin1String c_channelPrefix = QLatin1String("channel");

QString Telegram::Peer::toString() const
{
    switch (type) {
    case User:
        return c_userPrefix + QString::number(id);
    case Chat:
        return c_chatPrefix + QString::number(id);
    case Channel:
        return c_channelPrefix + QString::number(id);
    }
    Q_UNREACHABLE();
    return QString();
}

Telegram::Peer Telegram::Peer::fromString(const QString &string)
{
    // Possible schemes: user1234, chat1234, channel1234
    if (string.length() < 5) {
        return Peer();
    }
    bool ok = true;
    switch (string.at(0).toLatin1()) {
    case 'u': // user
        if (string.startsWith(c_userPrefix)) {
            uint userId = string.midRef(c_userPrefix.size()).toUInt(&ok);
            if (ok) {
                return Peer::fromUserId(userId);
            }
        }
        break;
    case 'c': // chat or channel
        if (string.at(3).toLatin1() == 't') {
            if (string.startsWith(c_chatPrefix)) {
                uint chatId = string.midRef(c_chatPrefix.size()).toUInt(&ok);
                if (ok) {
                    return Peer::fromChatId(chatId);
                }
            }
        } else {
            if (string.startsWith(c_channelPrefix)) {
                uint channelId = string.midRef(c_channelPrefix.size()).toUInt(&ok);
                if (ok) {
                    return Peer::fromChannelId(channelId);
                }
            }
        }
        break;
    default:
        break;
    }
    return Peer();
}

void TelegramNamespace::registerTypes()
{
    static bool registered = false;
    if (!registered) {

#ifdef DEVELOPER_BUILD
        qInfo() << "TelegramQt Developer build";
#endif
        qInfo().noquote().nospace() << "Initialize TelegramQt v" << Telegram::version() << " (hash " << Telegram::buildVersion() << ")";

        qRegisterMetaType<TelegramNamespace::ContactStatus>("TelegramNamespace::ContactStatus");
        qRegisterMetaType<TelegramNamespace::MessageFlags>("TelegramNamespace::MessageFlags");
        qRegisterMetaType<TelegramNamespace::MessageType>("TelegramNamespace::MessageType");
        qRegisterMetaType<TelegramNamespace::AuthSignError>("TelegramNamespace::AuthSignError");
        qRegisterMetaType<TelegramNamespace::UnauthorizedError>("TelegramNamespace::UnauthorizedError");
        qRegisterMetaType<Telegram::Peer>("Telegram::Peer");
        qRegisterMetaType<Telegram::PeerList>("Telegram::PeerList");
        qRegisterMetaType<Telegram::Client::ConnectionApi::Status>("Telegram::Client::ConnectionApi::Status");
        qRegisterMetaType<Telegram::Client::ConnectionApi::StatusReason>("Telegram::Client::ConnectionApi::StatusReason");
        registered = true;
    }
}

Telegram::Peer TelegramNamespace::emptyPeer()
{
    return Telegram::Peer();
}

Telegram::Peer TelegramNamespace::peerFromChatId(quint32 id)
{
    return Telegram::Peer::fromChatId(id);
}

Telegram::Peer TelegramNamespace::peerFromChannelId(quint32 id)
{
    return Telegram::Peer::fromChannelId(id);
}

Telegram::Peer TelegramNamespace::peerFromUserId(quint32 id)
{
    return Telegram::Peer::fromUserId(id);
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
    d->tlType = Telegram::Utils::toTLValue(type);

    d->m_isUploaded = true;
    const RemoteFile::Private *filePrivate = RemoteFile::Private::get(&file);
    d->m_size = filePrivate->m_size;

    if (!d->m_inputFile) {
        d->m_inputFile = new TLInputFile(filePrivate->getInputFile());
    }
}

bool Telegram::MessageMediaInfo::getRemoteFileInfo(Telegram::RemoteFile *file) const
{
    TLInputFileLocation inputLocation;

    RemoteFile::Private *filePrivate = RemoteFile::Private::get(file);
    switch (d->tlType) {
    case TLValue::MessageMediaPhoto:
        if (d->photo.sizes.isEmpty()) {
            return false;
        } else {
            const TLPhotoSize s = d->photo.sizes.last();
            filePrivate->m_size = s.size;
            return filePrivate->setFileLocation(&s.location);
        }
    case TLValue::MessageMediaDocument:
        inputLocation.tlType = TLValue::InputDocumentFileLocation;
        inputLocation.id = d->document.id;
        inputLocation.accessHash = d->document.accessHash;
        filePrivate->setInputFileLocation(&inputLocation);
        filePrivate->m_size = d->document.size;
        filePrivate->m_dcId = d->document.dcId;
        return true;
    default:
        return false;
    }
}

TelegramNamespace::MessageType Telegram::MessageMediaInfo::type() const
{
    return Telegram::Utils::getPublicMessageType(*d);
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
    case TLValue::MessageMediaDocument:
        return d->document.size;
    default:
        return 0;
    }
}

quint32 Telegram::MessageMediaInfo::duration() const
{
    switch (d->tlType) {
    default:
        return 0;
    }
}

bool Telegram::MessageMediaInfo::setDuration(quint32 duration)
{
    Q_UNUSED(duration)
    switch (d->tlType) {
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

    for (const TLDocumentAttribute &attribute : d->document.attributes) {
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

    TLDocumentAttribute *nameAttribute = nullptr;
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

    UserInfo::Private *infoPrivate = UserInfo::Private::get(info);
    *infoPrivate = UserInfo::Private(); // Reset
    infoPrivate->id = d->userId;
    infoPrivate->firstName = d->firstName;
    infoPrivate->lastName = d->lastName;
    infoPrivate->phone = d->phoneNumber;
    return true;
}

void Telegram::MessageMediaInfo::setContactInfo(const Telegram::UserInfo *info)
{
    const UserInfo::Private *infoPrivate = UserInfo::Private::get(info);
    d->tlType = TLValue::MessageMediaContact;
    d->firstName = infoPrivate->firstName;
    d->lastName = infoPrivate->lastName;
    d->phoneNumber = infoPrivate->phone;
    d->userId = infoPrivate->id;
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
        for (const TLDocumentAttribute &attribute : d->document.attributes) {
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

TLInputFileLocation Telegram::RemoteFile::Private::getInputFileLocation() const
{
    TLInputFileLocation result;
    switch (m_type) {
    case FileLocation:
        result.tlType = TLValue::InputFileLocation;
        break;
    case EncryptedFileLocation:
        result.tlType = TLValue::InputEncryptedFileLocation;
        break;
    case DocumentFileLocation:
        result.tlType = TLValue::InputDocumentFileLocation;
        break;
    default:
        return TLInputFileLocation();
    }

    result.volumeId   = m_volumeId;
    result.localId    = m_localId;
    result.secret     = m_secret;
    result.id         = m_id;
    result.accessHash = m_accessHash;
    return result;
}

bool Telegram::RemoteFile::Private::setInputFileLocation(const TLInputFileLocation *inputFileLocation)
{
    switch (inputFileLocation->tlType) {
    case TLValue::InputFileLocation:
        m_type = FileLocation;
        break;
    case TLValue::InputEncryptedFileLocation:
        m_type = EncryptedFileLocation;
        break;
    case TLValue::InputDocumentFileLocation:
        m_type = DocumentFileLocation;
        break;
    default:
        m_type = InvalidLocation;
        return false;
    }

    m_volumeId   = inputFileLocation->volumeId;
    m_localId    = inputFileLocation->localId;
    m_secret     = inputFileLocation->secret;
    m_id         = inputFileLocation->id;
    m_accessHash = inputFileLocation->accessHash;
    return true;
}

TLInputFile Telegram::RemoteFile::Private::getInputFile() const
{
    TLInputFile result;
    switch (m_type) {
    case UploadInputFile:
        result.tlType = TLValue::InputFile;
        break;
    case UploadInputFileBig:
        result.tlType = TLValue::InputFileBig;
        break;
    default:
        return result;
    }
    result.id = m_id;
    result.parts = m_parts;
    result.name = m_name;
    result.md5Checksum = m_md5Checksum;
    return result;
}

bool Telegram::RemoteFile::Private::setInputFile(const TLInputFile *inputFile)
{
    switch (inputFile->tlType) {
    case TLValue::InputFile:
        m_type = UploadInputFile;
        break;
    case TLValue::InputFileBig:
        m_type = UploadInputFileBig;
        break;
    default:
        m_type = InvalidLocation;
        return false;
    }

    m_id          = inputFile->id;
    m_parts       = inputFile->parts;
    m_name        = inputFile->name;
    m_md5Checksum = inputFile->md5Checksum;
    return true;
}

TLFileLocation Telegram::RemoteFile::Private::getFileLocation() const
{
    switch (m_type) {
    case FileLocation:
        break;
    default:
        return TLFileLocation();
    }

    TLFileLocation result;
    result.tlType = TLValue::FileLocation;
    result.volumeId = m_volumeId;
    result.localId  = m_localId;
    result.secret   = m_secret;
    result.dcId     = m_dcId;
    return result;
}

bool Telegram::RemoteFile::Private::setFileLocation(const TLFileLocation *fileLocation)
{
    switch (fileLocation->tlType) {
    case TLValue::FileLocation:
        m_type = FileLocation;
        break;
    case TLValue::FileLocationUnavailable:
    default:
        m_type = InvalidLocation;
        return false;
    }

    m_volumeId   = fileLocation->volumeId;
    m_localId    = fileLocation->localId;
    m_secret     = fileLocation->secret;
    m_dcId       = fileLocation->dcId;
    return true;
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
    switch (d->m_type) {
    case Private::InvalidLocation:
        return Undefined;
    case Private::FileLocation:
    case Private::EncryptedFileLocation:
    case Private::VideoFileLocation:
    case Private::AudioFileLocation:
    case Private::DocumentFileLocation:
        return Download;
    case Private::UploadInputFile:
    case Private::UploadInputFileBig:
        return Upload;
    }
    return Undefined;
}

bool Telegram::RemoteFile::isValid() const
{
    return d && (d->m_type != Private::InvalidLocation);
}

QString Telegram::RemoteFile::getUniqueId() const
{
    if (!isValid()) {
        return QString();
    }
    const quint8 type = d->m_type;
    switch (d->m_type) {
    case Private::FileLocation:
        return QString(QLatin1String("%1%2%3%4%5%6"))
                .arg(type, sizeof(type) * 2, 16, QLatin1Char('0'))
                .arg(d->m_dcId, sizeof(d->m_dcId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_size, sizeof(d->m_size) * 2, 16, QLatin1Char('0'))
                .arg(d->m_volumeId, sizeof(d->m_volumeId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_secret, sizeof(d->m_secret) * 2, 16, QLatin1Char('0'))
                .arg(d->m_localId, sizeof(d->m_localId) * 2, 16, QLatin1Char('0'))
                ;
    case Private::EncryptedFileLocation:
    case Private::VideoFileLocation:
    case Private::AudioFileLocation:
    case Private::DocumentFileLocation:
        return QString(QLatin1String("%1%2%3%4%5"))
                .arg(type, sizeof(type) * 2, 16, QLatin1Char('0'))
                .arg(d->m_dcId, sizeof(d->m_dcId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_size, sizeof(d->m_size) * 2, 16, QLatin1Char('0'))
                .arg(d->m_id, sizeof(d->m_id) * 2, 16, QLatin1Char('0'))
                .arg(d->m_accessHash, sizeof(d->m_accessHash) * 2, 16, QLatin1Char('0'))
                ;
    case Private::UploadInputFile:
    case Private::UploadInputFileBig:
        return QString(QLatin1String("%1%2%3%4%5%6%7"))
                .arg(type, sizeof(type) * 2, 16, QLatin1Char('0'))
                .arg(d->m_dcId, sizeof(d->m_dcId) * 2, 16, QLatin1Char('0'))
                .arg(d->m_size, sizeof(d->m_size) * 2, 16, QLatin1Char('0'))
                .arg(d->m_id, sizeof(d->m_id) * 2, 16, QLatin1Char('0'))
                .arg(d->m_parts, sizeof(d->m_parts) * 2, 16, QLatin1Char('0'))
                .arg(d->m_md5Checksum, d->m_name)
                ;
    case Private::InvalidLocation:
        break;
    }
    return QString();
}

Telegram::RemoteFile Telegram::RemoteFile::fromUniqueId(const QString &uniqueId)
{
    uint remoteFileType = Private::InvalidLocation;
    bool ok;
    remoteFileType = uniqueId.midRef(0, 2).toUInt(&ok, 16);
    if (!ok) {
        return RemoteFile();
    }
    RemoteFile result;
    result.d->m_type = static_cast<Private::Type>(remoteFileType);
    result.d->m_dcId = uniqueId.midRef(2, 8).toULong(&ok, 16); // 32 bits
    if (!ok) {
        return RemoteFile();
    }
    result.d->m_size = uniqueId.midRef(10, 8).toULongLong(&ok, 16); // 32 bits
    if (!ok) {
        return RemoteFile();
    }

    switch (result.d->m_type) {
    case Private::FileLocation:
        result.d->m_volumeId = uniqueId.midRef(18, 16).toULongLong(&ok, 16); // 64 bits
        if (!ok) {
            return RemoteFile();
        }
        result.d->m_secret = uniqueId.midRef(34, 16).toULongLong(&ok, 16); // 64 bits
        if (!ok) {
            return RemoteFile();
        }
        result.d->m_localId = uniqueId.midRef(50, 8).toULong(&ok, 16); // 32 bits
        if (!ok) {
            return RemoteFile();
        }
        break;
    case Private::EncryptedFileLocation:
    case Private::VideoFileLocation:
    case Private::AudioFileLocation:
    case Private::DocumentFileLocation:
        result.d->m_id = uniqueId.midRef(18, 16).toULongLong(&ok, 16); // 64 bits
        if (!ok) {
            return RemoteFile();
        }
        result.d->m_accessHash = uniqueId.midRef(34, 16).toULongLong(&ok, 16); // 64 bits
        if (!ok) {
            return RemoteFile();
        }
        break;
    case Private::InvalidLocation:
    default:
        return RemoteFile();
    }
    return result;
}

QString Telegram::RemoteFile::fileName() const
{
    return d->m_name;
}

quint32 Telegram::RemoteFile::size() const
{
    return d->m_size;
}

QString Telegram::RemoteFile::md5Sum() const
{
    return d->m_md5Checksum;
}

Telegram::DialogInfo::DialogInfo() :
    d(new Private())
{
}

Telegram::DialogInfo::DialogInfo(const Telegram::DialogInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

Telegram::DialogInfo::~DialogInfo()
{
    delete d;
}

Telegram::DialogInfo &Telegram::DialogInfo::operator=(const Telegram::DialogInfo &info)
{
    *d = *info.d;
    return *this;
}

quint32 Telegram::DialogInfo::unreadCount() const
{
    return d->unreadCount;
}

QString Telegram::DialogInfo::draft() const
{
    return d->draft.message;
}

quint32 Telegram::DialogInfo::lastMessageId() const
{
    return d->topMessage;
}

quint32 Telegram::DialogInfo::readInboxMaxId() const
{
    return d->readInboxMaxId;
}

quint32 Telegram::DialogInfo::readOutboxMaxId() const
{
    return d->readOutboxMaxId;
}

Telegram::Peer Telegram::DialogInfo::peer() const
{
    return Telegram::Utils::toPublicPeer(d->peer);
}

quint32 Telegram::DialogInfo::muteUntil() const
{
    return d->notifySettings.muteUntil;
}

bool Telegram::DialogInfo::isStillMuted() const
{
    return false;
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

/*! \fn quint32 Telegram::UserInfo::wasOnline() const
  Return seconds since epoch for last online time.

  If user is online, this method return time when online expires,
  return the time, when contact was online otherwise.

  Depending on the contact privacy, the method can return some special values:

  TelegramNamespace::ContactLastOnlineUnknown - User last online time is not known.
  TelegramNamespace::ContactLastOnlineRecently - User hides exact online time, but was online recently.
  TelegramNamespace::ContactLastOnlineLastWeek - User hides exact online time, but was online last week.
  TelegramNamespace::ContactLastOnlineLastMonth - User hides exact online time, but was online last month.

  The TelegramNamespace::ContactLastOnlineMask can be used to determine if there is special value:
  if ((contactLastOnline(contact) & TelegramNamespace::ContactLastOnlineMask) == contactLastOnline(contact)) {
      qDebug() << "Special value";
  } else {
      qDebug() << "Seconds since epoch";
  }
*/
quint32 Telegram::UserInfo::wasOnline() const
{
    return getApiContactLastOnline(d->status);
}

bool Telegram::UserInfo::isBot() const
{
    return d->bot();
}

bool Telegram::UserInfo::isSelf() const
{
    return d->self();
}

bool Telegram::UserInfo::isContact() const
{
    return d->contact();
}

bool Telegram::UserInfo::isMutualContact() const
{
    return d->mutualContact();
}

bool Telegram::UserInfo::isDeleted() const
{
    return d->deleted();
}

quint32 Telegram::UserInfo::botVersion() const
{
    return d->botInfoVersion;
}

bool Telegram::UserInfo::getPeerPicture(Telegram::RemoteFile *file, PeerPictureSize size) const
{
    RemoteFile::Private *filePrivate = RemoteFile::Private::get(file);
    switch (size) {
    case PeerPictureSize::Big:
        return filePrivate->setFileLocation(&d->photo.photoBig);
    case PeerPictureSize::Small:
        return filePrivate->setFileLocation(&d->photo.photoSmall);
    }
    Q_UNREACHABLE();
    return false;
}

Telegram::ChatInfo::ChatInfo() :
    d(new Private())
{

}

Telegram::ChatInfo::ChatInfo(const Telegram::ChatInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

Telegram::ChatInfo::~ChatInfo()
{
    delete d;
}

Telegram::ChatInfo &Telegram::ChatInfo::operator=(const Telegram::ChatInfo &info)
{
    *d = *info.d;
    return *this;
}

Telegram::Peer Telegram::ChatInfo::peer() const
{
    switch(d->tlType) {
    case TLValue::Chat:
    case TLValue::ChatForbidden:
        return Telegram::Peer(d->id, Telegram::Peer::Chat);
    case TLValue::Channel:
    case TLValue::ChannelForbidden:
        return Telegram::Peer(d->id, Telegram::Peer::Channel);
    default:
        break;
    }
    return Telegram::Peer();
}

QString Telegram::ChatInfo::title() const
{
    return d->title;
}

quint32 Telegram::ChatInfo::participantsCount() const
{
    return d->participantsCount;
}

quint32 Telegram::ChatInfo::date() const
{
    return d->date;
}

bool Telegram::ChatInfo::left() const
{
    return d->left();
}

bool Telegram::ChatInfo::broadcast() const
{
    return d->broadcast();
}

Telegram::Peer Telegram::ChatInfo::migratedTo() const
{
    if (d->migratedTo.tlType == TLValue::InputChannelEmpty) {
        return Peer();
    }
    return Peer(d->migratedTo.channelId, Peer::Channel);
}

bool Telegram::ChatInfo::getPeerPicture(Telegram::RemoteFile *file, Telegram::PeerPictureSize size) const
{
    RemoteFile::Private *filePrivate = RemoteFile::Private::get(file);
    switch (size) {
    case PeerPictureSize::Big:
        return filePrivate->setFileLocation(&d->photo.photoBig);
    case PeerPictureSize::Small:
        return filePrivate->setFileLocation(&d->photo.photoSmall);
    }
    Q_UNREACHABLE();
    return false;
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

quint64 Telegram::Utils::maskNumber(quint64 number)
{
    quint64 leftPart = number >> 32;
    quint64 rightPart = number & 0xffffffff;
    quint64 result = leftPart ^ rightPart;
    leftPart = (result & 0xffff0000) << 32;
    rightPart = result & 0x0000ffff;
    result = (leftPart | rightPart);
    qDebug() << bin << result;
    return result;
}

QString Telegram::Utils::maskPhoneNumber(const QString &identifier)
{
    if (identifier.isEmpty()) {
        return QString();
    }
    // We don't want to mask "numbers" like unknown777000, so lets check if phoneNumber is consist of digits only.
    for (const QChar c : identifier.mid(1)) {
        if (!c.isDigit()) {
            return identifier;
        }
    }
    // Expected something like: 55xxxxxxxx (hidden).
    return identifier.mid(0, identifier.size() / 4) + QString(identifier.size() - identifier.size() / 4, QLatin1Char('x')); // + QLatin1String(" (hidden)");
}

QStringList Telegram::Utils::maskPhoneNumber(const QStringList &list)
{
    if (list.count() == 1) {
        return QStringList() << maskPhoneNumber(list.first());
    }
    QStringList result;
    const int listDigits = QString::number(list.count()).size();
    for (const QString &number : list) {
        if (number.length() >= 5 + listDigits) {
            QString masked = QString(QLatin1String("%1xx%2%3"))
                    .arg(number.mid(0, 2))
                    .arg(list.indexOf(number), listDigits, 10, QLatin1Char('0'))
                    .arg(QString(number.length() - 4 - listDigits, QLatin1Char('x')));
            result.append(masked);
        } else { // fallback
            result.append(maskPhoneNumber(number) + QLatin1String(" (fallback)"));
        }
    }
    return result;
}

void Telegram::initialize()
{
    TelegramNamespace::registerTypes();
    if (!RandomGenerator::instance()) {
        static RandomGenerator defaultGenerator;
        RandomGenerator::setInstance(&defaultGenerator);
    }
}
