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

#ifndef TELEGRAMQT_DATA_STORAGE_HPP
#define TELEGRAMQT_DATA_STORAGE_HPP

#include <QObject>

#include "DcConfiguration.hpp"

namespace Telegram {

namespace Client {

class DataStoragePrivate;

class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);

    DcConfiguration serverConfiguration() const;
    void setServerConfiguration(const DcConfiguration &configuration);

protected:
    DataStorage(DataStoragePrivate *d, QObject *parent);
    DataStoragePrivate *d_ptr;
    Q_DECLARE_PRIVATE(DataStorage)

};

class InMemoryDataStorage : public DataStorage
{
    Q_OBJECT
public:
    explicit InMemoryDataStorage(QObject *parent = nullptr);

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_DATA_STORAGE_HPP
