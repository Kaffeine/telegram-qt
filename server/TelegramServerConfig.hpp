/*
   Copyright (C) 2019 Alexey Minnekhanov <alexey.min@gmail.com>

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

#ifndef TELEGRAM_SERVER_CONFIG_HPP
#define TELEGRAM_SERVER_CONFIG_HPP

#include "DcConfiguration.hpp"

namespace Telegram {

namespace Server {

class Config
{
public:
    explicit Config(const QString &fileName = QString());

    QString fileName() const { return m_fileName; }
    void setFileName(const QString &fileName);

    static DcConfiguration getDefaultDcConfiguration();
    DcConfiguration serverConfiguration() const { return m_serverConfiguration; }
    void setServerConfiguration(const DcConfiguration &configuration);

    QString privateKeyFile() const { return m_privateKeyFile; }
    void setPrivateKeyFile(const QString &fileName);

    bool load();
    bool save() const;

private:
    QString m_fileName;
    QString m_privateKeyFile;
    DcConfiguration m_serverConfiguration;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_CONFIG_HPP
