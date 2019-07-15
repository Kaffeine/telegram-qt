/*
   Copyright (C) 2019 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_SERVER_DATA_IMPORTER_HPP
#define TELEGRAM_QT_SERVER_DATA_IMPORTER_HPP

#include <QString>

namespace Telegram {

namespace Server {

class LocalCluster;
class Server;
class Storage;

class DataImporter
{
public:
    virtual ~DataImporter();

    virtual bool prepare() = 0;

    void saveData();
    void loadData();

    void setTarget(LocalCluster *cluster);

    virtual void exportForServer(Server *server) = 0;
    virtual void importForServer(Server *server) = 0;

protected:
    LocalCluster *m_targetCluster = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_STORAGE_HPP
