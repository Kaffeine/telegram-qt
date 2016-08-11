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
        registered = true;
    }
}

TelegramNamespace::MessageMediaInfo::MessageMediaInfo() : d(new Private())
{

}

TelegramNamespace::MessageType TelegramNamespace::MessageMediaInfo::type() const
{
    return telegramMessageTypeToPublicMessageType(d->tlType);
}

QString TelegramNamespace::MessageMediaInfo::caption() const
{
    return d->caption;
}

QString TelegramNamespace::MessageMediaInfo::mimeType() const
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

QString TelegramNamespace::MessageMediaInfo::alt() const
{
    switch (d->tlType) {
    case TLValue::MessageMediaGeo:
        return QString(QLatin1String("geo:%1,%2")).arg(d->geo.latitude).arg(d->geo.longitude);
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

double TelegramNamespace::MessageMediaInfo::latitude() const
{
    return d->geo.latitude;
}

double TelegramNamespace::MessageMediaInfo::longitude() const
{
    return d->geo.longitude;
}

void TelegramNamespace::MessageMediaInfo::setGeoPoint(double latitude, double longitude)
{
    d->tlType = TLValue::MessageMediaGeo;
    d->geo.tlType = TLValue::GeoPoint;
    d->geo.longitude = longitude;
    d->geo.latitude = latitude;
}

TelegramNamespace::UserInfo::UserInfo() : d(new Private())
{
}

quint32 TelegramNamespace::UserInfo::id() const
{
    return d->id;
}

QString TelegramNamespace::UserInfo::firstName() const
{
    return d->firstName;
}

QString TelegramNamespace::UserInfo::lastName() const
{
    return d->lastName;
}

QString TelegramNamespace::UserInfo::userName() const
{
    return d->username;
}

QString TelegramNamespace::UserInfo::phone() const
{
    return d->phone;
}

TelegramNamespace::ContactStatus TelegramNamespace::UserInfo::status() const
{
    return getApiContactStatus(d->status.tlType);
}

quint32 TelegramNamespace::UserInfo::wasOnline() const
{
    return getApiContactLastOnline(d->status);
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

TelegramNamespace::PasswordInfo::PasswordInfo() :
    d(new Private())
{
}

TelegramNamespace::PasswordInfo::PasswordInfo(const TelegramNamespace::PasswordInfo &otherData) :
    d(new Private())
{
    *d = *otherData.d;
}

TelegramNamespace::PasswordInfo &TelegramNamespace::PasswordInfo::operator=(const TelegramNamespace::PasswordInfo &otherData)
{
    *d = *otherData.d;
    return *this;
}

QByteArray TelegramNamespace::PasswordInfo::newSalt()
{
    return d->newSalt;
}

QString TelegramNamespace::PasswordInfo::emailUnconfirmedPattern()
{
    return d->emailUnconfirmedPattern;
}

QByteArray TelegramNamespace::PasswordInfo::currentSalt()
{
    return d->currentSalt;
}

QString TelegramNamespace::PasswordInfo::hint()
{
    return d->hint;
}

bool TelegramNamespace::PasswordInfo::hasRecovery()
{
    return d->hasRecovery;
}
