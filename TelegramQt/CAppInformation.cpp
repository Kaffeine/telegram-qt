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

#include "CAppInformation.hpp"

namespace Telegram {

namespace Client {

/*!
    \class Telegram::Client::AppInformation
    \inmodule TelegramQt
    \ingroup Client
    \brief The AppInformation class provides methods for setup the application-specific Telegram ids.
*/

AppInformation::AppInformation(QObject *parent) :
    QObject(parent),
    m_appId(0),
    m_appHash(QLatin1String("00000000000000000000000000000000")),
    m_langCode(QLatin1String("en"))
{
}

AppInformation::AppInformation(const AppInformation *anotherInfo, QObject *parent) :
    AppInformation(parent)
{
    m_appId = anotherInfo->m_appId;
    m_appHash = anotherInfo->m_appHash;
    m_appVersion = anotherInfo->m_appVersion;

    m_deviceInfo = anotherInfo->m_deviceInfo;
    m_osInfo = anotherInfo->m_osInfo;
    m_langCode = anotherInfo->m_langCode;
}

/*!
    \property AppInformation::appId
    \brief the application identifier as registered in the Telegram network.
    \sa appHash
*/
bool AppInformation::setAppId(quint32 newId)
{
    if (!newId) {
        return false;
    }

    m_appId = newId;
    return true;
}

bool AppInformation::setAppHash(const QString &newHash)
{
    if (newHash.length() != 32) {
        return false;
    }

    m_appHash = newHash;
    return true;
}

bool AppInformation::setAppVersion(const QString &newVersion)
{
    if (newVersion.isEmpty()) {
        return false;
    }

    m_appVersion = newVersion;
    return true;
}

bool AppInformation::setDeviceInfo(const QString &newDeviceInfo)
{
    if (newDeviceInfo.isEmpty()) {
        return false;
    }

    m_deviceInfo = newDeviceInfo;
    return true;
}

bool AppInformation::setOsInfo(const QString &newOsInfo)
{
    if (newOsInfo.isEmpty()) {
        return false;
    }

    m_osInfo = newOsInfo;
    return true;
}

bool AppInformation::setLanguageCode(const QString &newLanguageCode)
{
    if (newLanguageCode.isEmpty()) {
        return false;
    }

    m_langCode = newLanguageCode;
    return true;
}

} // Client namespace

} // Telegram namespace
