/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "SendPackageHelper.hpp"
#include "Utils.hpp"

namespace Telegram {

void BaseSendPackageHelper::setServerSalt(const quint64 salt)
{
    m_serverSalt = salt;
}

void BaseSendPackageHelper::setAuthKey(const QByteArray &authKey)
{
    if (authKey.isEmpty()) {
        m_authKey.clear();
        m_authId = 0;
    } else {
        m_authKey = authKey;
        m_authId = Utils::getFingerprints(authKey, Utils::Lower64Bits);
    }
}

} // Telegram namespace
