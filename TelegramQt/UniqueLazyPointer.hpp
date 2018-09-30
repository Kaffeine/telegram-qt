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

#ifndef TELEGRAM_QT_UNIQUE_LAZY_POINTER_HPP
#define TELEGRAM_QT_UNIQUE_LAZY_POINTER_HPP

namespace Telegram {

template<typename TL>
struct UniqueLazyPointer
{
    constexpr UniqueLazyPointer() = default;
    constexpr UniqueLazyPointer(TL *newData) : data(newData) { }

    UniqueLazyPointer(const UniqueLazyPointer &ptr)
    {
        if (ptr.data) {
            data = new TL(*ptr.data);
        }
    }
    UniqueLazyPointer(UniqueLazyPointer &&ptr)
    {
        if (ptr.data) {
            data = ptr.data;
            ptr.data = nullptr;
        }
    }

    ~UniqueLazyPointer() { delete data; }

    UniqueLazyPointer &operator=(const UniqueLazyPointer &ptr)
    {
        if (ptr.data) {
            if (data) {
                *data = *ptr.data;
            } else {
                data = new TL(*ptr.data);
            }
        } else {
            clear();
        }
        return *this;
    }

    UniqueLazyPointer &operator=(UniqueLazyPointer &&ptr)
    {
        if (ptr.data) {
            if (data) {
                delete data;
            }
            data = ptr.data;
            ptr.data = nullptr;
        } else {
            clear();
        }
        return *this;
    }

    constexpr operator bool() const { return data; }
    constexpr bool isNull() const { return !data; }

    const TL &operator*() const
    {
        Q_ASSERT(data);
        return *data;
    }

    TL &operator*()
    {
        if (!data) {
            data = new TL;
        }
        return *data;
    }
    const TL *operator->() const
    {
        Q_ASSERT(data);
        return data;
    }
    TL *operator->()
    {
        if (!data) {
            data = new TL;
        }
        return data;
    }

protected:
    TL *data = nullptr;

    void clear()
    {
        delete data;
        data = nullptr;
    }
};

} // Telegram namespace

#endif // TELEGRAM_QT_UNIQUE_LAZY_POINTER_HPP
