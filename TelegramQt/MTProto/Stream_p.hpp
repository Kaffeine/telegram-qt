/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#ifndef TELEGRAM_QT_MTPROTO_STREAM_P_HPP
#define TELEGRAM_QT_MTPROTO_STREAM_P_HPP

#include "Stream.hpp"

namespace Telegram {

namespace MTProto {

template <typename T>
Stream &Stream::operator>>(QVector<T> &v)
{
    QVector<T> result;
    TLValue tlType;

    *this >> tlType;

    if (tlType == TLValue::Vector) {
        quint32 length = 0;
        *this >> length;
        for (quint32 i = 0; i < length; ++i) {
            T value;
            *this >> value;
            result.append(value);
        }
    }

    v = result;
    return *this;
}

template <typename T>
Stream &Stream::operator>>(QVector<T*> &v)
{
    QVector<T*> result;
    TLValue tlType;

    *this >> tlType;

    if (tlType == TLValue::Vector) {
        quint32 length = 0;
        *this >> length;
        for (quint32 i = 0; i < length; ++i) {
            T *value = new T;
            *this >> *value;
            result.append(value);
        }
    }

    qDeleteAll(v);
    v = result;
    return *this;
}

template <typename T>
Stream &Stream::operator<<(const QVector<T> &v)
{
    *this << TLValue::Vector;
    *this << quint32(v.count());

    for (int i = 0; i < v.count(); ++i) {
        *this << v.at(i);
    }

    return *this;
}

template <typename T>
Stream &Stream::operator<<(const QVector<T*> &v)
{
    *this << TLValue::Vector;
    *this << quint32(v.count());

    for (int i = 0; i < v.count(); ++i) {
        *this << *v.at(i);
    }

    return *this;
}

template<typename T>
Stream &Stream::operator<<(const TLPtr<T> &v)
{
    *this << *v;
    return *this;
}

template<typename T>
Stream &Stream::operator>>(TLPtr<T> &v)
{
    *this >> *v;
    return *this;
}

} // MTProto namespace

} // Telegram namespace

#endif // TELEGRAM_QT_MTPROTO_STREAM_P_HPP
