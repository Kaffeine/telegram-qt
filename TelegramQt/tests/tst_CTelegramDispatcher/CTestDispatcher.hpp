/*
   Copyright (C) 2015-2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef CTESTDISPATCHER_HPP
#define CTESTDISPATCHER_HPP

#include "CTelegramDispatcher.hpp"

class CTestDispatcher : public CTelegramDispatcher
{
    Q_OBJECT
public:
    explicit CTestDispatcher(QObject *parent = 0);

    void testProcessUpdate(const TLUpdate &update);
    void testSetDcConfiguration(const QVector<TLDcOption> newDcConfiguration);
    QVector<TLDcOption> testGetDcConfiguration() const { return m_dcConfiguration; }

};

#endif // CTESTDISPATCHER_HPP
