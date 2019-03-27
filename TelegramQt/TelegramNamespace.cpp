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

#include <QCryptographicHash>
#include <QDateTime>
#include <QMetaType>
#include <QDebug>

static const QLatin1String c_userPrefix = QLatin1String("user");
static const QLatin1String c_chatPrefix = QLatin1String("chat");
static const QLatin1String c_channelPrefix = QLatin1String("channel");

namespace Telegram {

/*!
    \class Telegram::Peer
    \brief Holds an ID of a contact or a group

    \inmodule TelegramQt
 */
QString Peer::toString() const
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

Telegram::Peer Peer::fromString(const QString &string)
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

void Namespace::registerTypes()
{
    static bool registered = false;
    if (registered) {
        return;
    }
    registered = true;

#ifdef DEVELOPER_BUILD
    qInfo() << "TelegramQt Developer build";
#endif
    qInfo().noquote().nospace() << "Initialize TelegramQt v" << Telegram::version()
                                << " (build " << Telegram::buildVersion() << ")";

    qRegisterMetaType<Namespace::ContactStatus>
            ("Telegram::Namespace::ContactStatus");
    qRegisterMetaType<Namespace::MessageFlags>
            ("Telegram::Namespace::MessageFlags");
    qRegisterMetaType<Namespace::MessageType>
            ("Telegram::Namespace::MessageType");
    qRegisterMetaType<Namespace::AuthenticationError>
            ("Telegram::Namespace::AuthenticationError");
    qRegisterMetaType<Namespace::UnauthorizedError>
            ("Telegram::Namespace::UnauthorizedError");
    qRegisterMetaType<Telegram::MessageAction>
            ("Telegram::MessageAction");
    qRegisterMetaType<Telegram::Peer>
            ("Telegram::Peer");
    qRegisterMetaType<Telegram::PeerList>
            ("Telegram::PeerList");
    qRegisterMetaType<Telegram::Client::ConnectionApi::Status>
            ("Telegram::Client::ConnectionApi::Status");
    qRegisterMetaType<Telegram::Client::ConnectionApi::StatusReason>
            ("Telegram::Client::ConnectionApi::StatusReason");
}

Telegram::Peer Namespace::emptyPeer()
{
    return Peer();
}

Telegram::Peer Namespace::peerFromChatId(quint32 id)
{
    return Peer::fromChatId(id);
}

Telegram::Peer Namespace::peerFromChannelId(quint32 id)
{
    return Peer::fromChannelId(id);
}

Telegram::Peer Namespace::peerFromUserId(quint32 id)
{
    return Peer::fromUserId(id);
}

void initialize()
{
    Namespace::registerTypes();
    if (!RandomGenerator::instance()) {
        static RandomGenerator defaultGenerator;
        RandomGenerator::setInstance(&defaultGenerator);
    }
}

MessageMediaInfo::MessageMediaInfo() :
    d(new Private())
{
}

MessageMediaInfo::MessageMediaInfo(const MessageMediaInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

MessageMediaInfo::~MessageMediaInfo()
{
    delete d;
}

MessageMediaInfo &MessageMediaInfo::operator=(const MessageMediaInfo &info)
{
    *d = *info.d;
    return *this;
}

void MessageMediaInfo::setUploadFile(Namespace::MessageType type, const RemoteFile &file)
{
    d->tlType = Utils::toTLValue(type);

    d->m_isUploaded = true;
    const RemoteFile::Private *filePrivate = RemoteFile::Private::get(&file);
    d->m_size = filePrivate->m_size;

    if (!d->m_inputFile) {
        d->m_inputFile = new TLInputFile(filePrivate->getInputFile());
    }
}

bool MessageMediaInfo::getRemoteFileInfo(RemoteFile *file) const
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

Namespace::MessageType MessageMediaInfo::type() const
{
    return Utils::getPublicMessageType(*d);
}

quint32 MessageMediaInfo::size() const
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

quint32 MessageMediaInfo::duration() const
{
    switch (d->tlType) {
    default:
        return 0;
    }
}

bool MessageMediaInfo::setDuration(quint32 duration)
{
    Q_UNUSED(duration)
    switch (d->tlType) {
    default:
        break;
    }
    return false;
}

QString MessageMediaInfo::documentFileName() const
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

bool MessageMediaInfo::setDocumentFileName(const QString &fileName)
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

QString MessageMediaInfo::caption() const
{
    return d->caption;
}

void MessageMediaInfo::setCaption(const QString &caption)
{
    if (!d->m_isUploaded) {
        return;
    }

    d->caption = caption;
}

QByteArray MessageMediaInfo::getCachedPhoto() const
{
    const TLVector<TLPhotoSize> *sizes = nullptr;
    switch (d->tlType) {
    case TLValue::MessageMediaPhoto:
        sizes = &d->photo.sizes;
        break;
    default:
        return QByteArray();
    }
    for (const TLPhotoSize &size : *sizes) {
        if (size.tlType == TLValue::PhotoCachedSize) {
            return size.bytes;
        }
    }
    return QByteArray();
}

QString MessageMediaInfo::mimeType() const
{
    switch (d->tlType) {
    case TLValue::MessageMediaDocument:
        return d->document.mimeType;
    default:
        break;
    }
    return QString();
}

bool MessageMediaInfo::setMimeType(const QString &mimeType)
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

bool MessageMediaInfo::getContactInfo(UserInfo *info) const
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

void MessageMediaInfo::setContactInfo(const UserInfo *info)
{
    const UserInfo::Private *infoPrivate = UserInfo::Private::get(info);
    d->tlType = TLValue::MessageMediaContact;
    d->firstName = infoPrivate->firstName;
    d->lastName = infoPrivate->lastName;
    d->phoneNumber = infoPrivate->phone;
    d->userId = infoPrivate->id;
}

QString MessageMediaInfo::alt() const
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

double MessageMediaInfo::latitude() const
{
    return d->geo.latitude;
}

double MessageMediaInfo::longitude() const
{
    return d->geo.longitude;
}

void MessageMediaInfo::setGeoPoint(double latitude, double longitude)
{
    d->tlType = TLValue::MessageMediaGeo;
    d->geo.tlType = TLValue::GeoPoint;
    d->geo.longitude = longitude;
    d->geo.latitude = latitude;
}

QString MessageMediaInfo::url() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }
    return d->webpage.url;
}

QString MessageMediaInfo::displayUrl() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }
    return d->webpage.displayUrl;
}

QString MessageMediaInfo::siteName() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.siteName;
}

QString MessageMediaInfo::title() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.title;
}

QString MessageMediaInfo::description() const
{
    if (d->tlType != TLValue::MessageMediaWebPage) {
        return QString();
    }

    return d->webpage.description;
}

TLInputFileLocation RemoteFile::Private::getInputFileLocation() const
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

bool RemoteFile::Private::setInputFileLocation(const TLInputFileLocation *inputFileLocation)
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

TLInputFile RemoteFile::Private::getInputFile() const
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

bool RemoteFile::Private::setInputFile(const TLInputFile *inputFile)
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

TLFileLocation RemoteFile::Private::getFileLocation() const
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

bool RemoteFile::Private::setFileLocation(const TLFileLocation *fileLocation)
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

RemoteFile::RemoteFile():
    d(new Private())
{
}

RemoteFile::RemoteFile(const RemoteFile &file) :
    d(new Private)
{
    *d = *file.d;
}

RemoteFile::~RemoteFile()
{
    delete d;
}

RemoteFile &RemoteFile::operator=(const RemoteFile &file)
{
    *d = *file.d;
    return *this;
}

RemoteFile::Type RemoteFile::type() const
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

bool RemoteFile::isValid() const
{
    return d && (d->m_type != Private::InvalidLocation);
}

QString RemoteFile::getUniqueId() const
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

RemoteFile RemoteFile::fromUniqueId(const QString &uniqueId)
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

QString RemoteFile::fileName() const
{
    return d->m_name;
}

quint32 RemoteFile::size() const
{
    return d->m_size;
}

QString RemoteFile::md5Sum() const
{
    return d->m_md5Checksum;
}

DialogInfo::DialogInfo() :
    d(new Private())
{
}

DialogInfo::DialogInfo(const DialogInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

DialogInfo::~DialogInfo()
{
    delete d;
}

DialogInfo &DialogInfo::operator=(const DialogInfo &info)
{
    *d = *info.d;
    return *this;
}

quint32 DialogInfo::unreadCount() const
{
    return d->unreadCount;
}

QString DialogInfo::draft() const
{
    return d->draftText;
}

quint32 DialogInfo::lastMessageId() const
{
    return d->topMessage;
}

quint32 DialogInfo::readInboxMaxId() const
{
    return d->readInboxMaxId;
}

quint32 DialogInfo::readOutboxMaxId() const
{
    return d->readOutboxMaxId;
}

Peer DialogInfo::peer() const
{
    return d->peer;
}

UserInfo::UserInfo() :
    d(new Private())
{
}

UserInfo::UserInfo(const UserInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

UserInfo::~UserInfo()
{
    delete d;
}

UserInfo &UserInfo::operator=(const UserInfo &info)
{
    *d = *info.d;
    return *this;
}

QString UserInfo::getBestDisplayName() const
{
    QString name;
    if (!firstName().isEmpty()) {
        name = firstName();
    }
    if (!lastName().isEmpty()) {
        if (!name.isEmpty()) {
            name += QLatin1Char(' ') + lastName();
        } else {
            name = lastName();
        }
    }
    if (!name.simplified().isEmpty()) {
        return name;
    }
    if (!userName().isEmpty()) {
        return userName();
    }
    if (!phone().isEmpty()) {
        return phone();
    }
    return name;
}

quint32 UserInfo::id() const
{
    return d->id;
}

QString UserInfo::firstName() const
{
    return d->firstName;
}

QString UserInfo::lastName() const
{
    return d->lastName;
}

QString UserInfo::userName() const
{
    return d->username;
}

QString UserInfo::phone() const
{
    return d->phone;
}

Namespace::ContactStatus UserInfo::status() const
{
    return getApiContactStatus(d->status.tlType);
}

/*!
  Return seconds since epoch for last online time.

  If user is online, this method return time when online expires,
  return the time, when contact was online otherwise.

  Depending on the contact privacy, the method can return some special values:

  Telegram::Namespace::ContactLastOnlineUnknown - User last online time is not known.
  Telegram::Namespace::ContactLastOnlineRecently - User hides exact online time, but was online recently.
  Telegram::Namespace::ContactLastOnlineLastWeek - User hides exact online time, but was online last week.
  Telegram::Namespace::ContactLastOnlineLastMonth - User hides exact online time, but was online last month.

  The Telegram::Namespace::ContactLastOnlineMask can be used to determine if there is special value:
  if ((contactLastOnline(contact) & Telegram::Namespace::ContactLastOnlineMask) == contactLastOnline(contact)) {
      qDebug() << "Special value";
  } else {
      qDebug() << "Seconds since epoch";
  }
*/
quint32 UserInfo::wasOnline() const
{
    return getApiContactLastOnline(d->status);
}

bool UserInfo::isBot() const
{
    return d->bot();
}

bool UserInfo::isSelf() const
{
    return d->self();
}

bool UserInfo::isContact() const
{
    return d->contact();
}

bool UserInfo::isMutualContact() const
{
    return d->mutualContact();
}

bool UserInfo::isDeleted() const
{
    return d->deleted();
}

quint32 UserInfo::botVersion() const
{
    return d->botInfoVersion;
}

bool UserInfo::getPeerPicture(RemoteFile *file, PeerPictureSize size) const
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

ChatInfo::ChatInfo() :
    d(new Private())
{

}

ChatInfo::ChatInfo(const ChatInfo &info) :
    d(new Private())
{
    *d = *info.d;
}

ChatInfo::~ChatInfo()
{
    delete d;
}

ChatInfo &ChatInfo::operator=(const ChatInfo &info)
{
    *d = *info.d;
    return *this;
}

Peer ChatInfo::peer() const
{
    switch(d->tlType) {
    case TLValue::Chat:
    case TLValue::ChatForbidden:
        return Peer(d->id, Peer::Chat);
    case TLValue::Channel:
    case TLValue::ChannelForbidden:
        return Peer(d->id, Peer::Channel);
    default:
        break;
    }
    return Peer();
}

QString ChatInfo::title() const
{
    return d->title;
}

quint32 ChatInfo::participantsCount() const
{
    return d->participantsCount;
}

quint32 ChatInfo::date() const
{
    return d->date;
}

bool ChatInfo::left() const
{
    return d->left();
}

bool ChatInfo::broadcast() const
{
    return d->broadcast();
}

Peer ChatInfo::migratedTo() const
{
    if (d->migratedTo.tlType == TLValue::InputChannelEmpty) {
        return Peer();
    }
    return Peer(d->migratedTo.channelId, Peer::Channel);
}

bool ChatInfo::getPeerPicture(RemoteFile *file, PeerPictureSize size) const
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

Namespace::ContactStatus getApiContactStatus(TLValue status)
{
    switch (status) {
    default:
    case TLValue::UserStatusEmpty:
        return Namespace::ContactStatusUnknown;
    case TLValue::UserStatusOnline:
        return Namespace::ContactStatusOnline;
    case TLValue::UserStatusOffline:
        return Namespace::ContactStatusOffline;
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
        return Namespace::ContactLastOnlineRecently;
    case TLValue::UserStatusLastWeek:
        return Namespace::ContactLastOnlineLastWeek;
    case TLValue::UserStatusLastMonth:
        return Namespace::ContactLastOnlineLastMonth;
    default:
        return Namespace::ContactLastOnlineUnknown;
    }
}

quint64 Utils::maskNumber(quint64 number)
{
    quint64 leftPart = number >> 32;
    quint64 rightPart = number & 0xffffffff;
    quint64 result = leftPart ^ rightPart;
    leftPart = (result & 0xffff0000) << 32;
    rightPart = result & 0x0000ffff;
    result = (leftPart | rightPart);
    return result;
}

// Encode in shell: echo -n <string>telegram-qt | sha256sum | cut -c1-8
QString Utils::maskString(const QString &string)
{
    return QString::fromLatin1(maskByteArray(string.toUtf8()));
}

QByteArray Utils::maskByteArray(const QByteArray &array)
{
    if (array.isEmpty()) {
        return QByteArray();
    }
    QByteArray data;
    if (array.length() < 10) {
        data = array + QByteArrayLiteral("telegram-qt");
    } else {
        data = array;
    }
    data = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return QByteArrayLiteral("<val_") + data.left(4).toHex() + QByteArrayLiteral(">");
}

QString Utils::maskPhoneNumber(const QString &identifier)
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

QStringList Utils::maskPhoneNumber(const QStringList &list)
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

QVector<quint32> Utils::toIdList(const PeerList &peerList)
{
    QVector<quint32> idList;
    idList.reserve(peerList.size());
    for (const Peer &peer : peerList) {
        idList.append(peer.id);
    }
    return idList;
}

const NotificationSettingsData &NotificationSettingsData::getDefaultSettingsData()
{
    static const NotificationSettingsData settings;
    return settings;
}

NotificationSettings::NotificationSettings() :
    d(new Private())
{
}

NotificationSettings::~NotificationSettings()
{
    // The out-of-line destructor is needed to deinitialize the d-ptr
}

quint32 NotificationSettings::flags() const
{
    return d ? d->flags : 0;
}

QString NotificationSettings::sound() const
{
    return d ? d->sound : QString();
}

quint32 NotificationSettings::muteUntil() const
{
    return d->muteUntil;
}

bool NotificationSettings::isMutedForever() const
{
    return muteUntil() == NotificationSettingsData::c_muteForever;
}

} // Telegram namespace
