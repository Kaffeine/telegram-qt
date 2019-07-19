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

#ifndef TELEGRAM_QT_JSON_UTILS_P_HPP
#define TELEGRAM_QT_JSON_UTILS_P_HPP

/* This file contains built-in and Qt types to/from JSON converters */

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace Telegram {

namespace Json {

inline QJsonValue toValue(const quint64 &v)
{
    return QString::number(v);
}

inline QJsonValue toValue(const quint32 &v)
{
    return QJsonValue(static_cast<int>(v));
}

inline QJsonValue toValue(const QString &v)
{
    return QJsonValue(v);
}

inline QJsonValue toValue(const QByteArray &v)
{
    return QJsonValue::fromVariant(QVariant::fromValue(v.toHex()));
}

template <typename Key, typename Value>
inline QJsonValue toValue(Key key, Value value)
{
    QJsonObject result;
    result[QLatin1String("key")] = toValue(key);
    result[QLatin1String("value")] = toValue(value);
    return result;
}

template <typename T>
inline QJsonArray toJsonArray(const T &container)
{
    QJsonArray result;
    for (const auto &value : container) {
        result.append(toValue(value));
    }
    return result;
}

template <typename T>
inline QJsonArray toJsonArray(const QVector<T> &container, QJsonValue (*method)(const T &))
{
    QJsonArray result;
    for (const T &value : container) {
        result.append((*method)(value));
    }
    return result;
}

template <typename T>
inline QJsonArray toJsonArray(const QList<T> &container, QJsonValue (*method)(const T &))
{
    QJsonArray result;
    for (const T &value : container) {
        result.append((*method)(value));
    }
    return result;
}

template <typename T>
inline T fromValue(const QJsonValue &v)
{
    return v.toVariant().value<T>();
}

template <>
inline QByteArray fromValue(const QJsonValue &v)
{
    return QByteArray::fromHex(v.toVariant().toByteArray());
}

template <typename T>
inline T fromValue(const QJsonArray &array)
{
    T result;
    for (const QJsonValue &value : array) {
        result.append(fromValue<decltype (result.takeFirst())>(value));
    }
    return result;
}

template <typename T>
inline void fromValue(T *dest, const QJsonValue &v)
{
    *dest = fromValue<T>(v);
}

template <typename T>
inline void fromValue(T *dest, const QJsonArray &a)
{
    *dest = fromValue<T>(a);
}

} // Json namespace

} // Telegram namespace

#endif // TELEGRAM_QT_JSON_UTILS_P_HPP
