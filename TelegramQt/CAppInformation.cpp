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

CAppInformation::CAppInformation(QObject *parent) :
    QObject(parent),
    m_appId(0),
    m_appHash(QLatin1String("00000000000000000000000000000000")),
    m_langCode(QLatin1String("en"))
{
}

CAppInformation::CAppInformation(const CAppInformation *anotherInfo, QObject *parent) :
    CAppInformation(parent)
{
    m_appId = anotherInfo->m_appId;
    m_appHash = anotherInfo->m_appHash;
    m_appVersion = anotherInfo->m_appVersion;

    m_deviceInfo = anotherInfo->m_deviceInfo;
    m_osInfo = anotherInfo->m_osInfo;
    m_langCode = anotherInfo->m_langCode;
}

bool CAppInformation::setAppId(quint32 newId)
{
    if (!newId) {
        return false;
    }

    m_appId = newId;

    return true;
}

bool CAppInformation::setAppHash(const QString &newHash)
{
    if (newHash.length() != 32) {
        return false;
    }

    m_appHash = newHash;

    return true;
}

bool CAppInformation::setAppVersion(const QString &newVersion)
{
    if (newVersion.isEmpty()) {
        return false;
    }

    m_appVersion = newVersion;

    return true;
}

bool CAppInformation::setDeviceInfo(const QString &newDeviceInfo)
{
    if (newDeviceInfo.isEmpty()) {
        return false;
    }

    m_deviceInfo = newDeviceInfo;

    return true;
}

bool CAppInformation::setOsInfo(const QString &newOsInfo)
{
    if (newOsInfo.isEmpty()) {
        return false;
    }

    m_osInfo = newOsInfo;

    return true;
}

bool CAppInformation::setLanguageCode(const QString &newLanguageCode)
{
    if (newLanguageCode.isEmpty()) {
        return false;
    }

    m_langCode = newLanguageCode;

    return true;
}
