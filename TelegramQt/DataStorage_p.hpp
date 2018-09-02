/*
   Copyright (C) 2018 Alexander Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAMQT_DATA_STORAGE_P_HPP
#define TELEGRAMQT_DATA_STORAGE_P_HPP

#include "DataStorage.hpp"

namespace Telegram {

namespace Client {

class DataStoragePrivate
{
public:
    DcConfiguration m_serverConfig;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_P_HPP
