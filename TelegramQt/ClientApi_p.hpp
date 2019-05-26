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

#ifndef TELEGRAMQT_CLIENT_API_P_HPP
#define TELEGRAMQT_CLIENT_API_P_HPP

#include "telegramqt_global.h"
#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class Backend;
class ClientApi;
class DataInternalApi;
class DataStorage;

class ClientApiPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ClientApiPrivate(ClientApi *parent = nullptr);
    static ClientApiPrivate *get(ClientApi *parent);

    Backend *backend() const { return m_backend; }
    void setBackend(Backend *backend);

    DataStorage *dataStorage();
    const DataStorage *dataStorage() const;
    DataInternalApi *dataInternalApi();
    const DataInternalApi *dataInternalApi() const;

protected:
    ClientApi *q_ptr = nullptr;
    Backend *m_backend = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_API_P_HPP
