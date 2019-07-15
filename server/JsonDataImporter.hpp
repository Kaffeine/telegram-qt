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

#ifndef TELEGRAM_QT_SERVER_JSON_DATA_IMPORTER_HPP
#define TELEGRAM_QT_SERVER_JSON_DATA_IMPORTER_HPP

#include "DataImporter.hpp"

namespace Telegram {

namespace Server {

class JsonDataImporter : public DataImporter
{
public:
    void setBaseDirectory(const QString &directory);

    bool prepare() override;

    void exportForServer(Server *server) override;
    void importForServer(Server *server) override;

protected:
    QString m_baseDirectory;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_JSON_DATA_IMPORTER_HPP
