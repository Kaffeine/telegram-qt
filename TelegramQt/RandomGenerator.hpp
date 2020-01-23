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

#ifndef TELEGRAM_RANDOM_GENERATOR_HPP
#define TELEGRAM_RANDOM_GENERATOR_HPP

#include "telegramqt_global.h"

#include <QByteArray>

namespace Telegram {

class TELEGRAMQT_INTERNAL_EXPORT RandomGenerator
{
public:
    virtual ~RandomGenerator() = default;
    virtual int generate(void *buffer, int count);

    QByteArray generate(int count)
    {
        QByteArray randBytes(count, Qt::Uninitialized);
        generate(&randBytes);
        return randBytes;
    }

    int generate(QByteArray *array)
    {
        return generate(array->data(), array->size());
    }

    template<typename T>
    int generate(T *number)
    {
        return generate(number, sizeof(T));
    }

    template <typename T>
    T generate()
    {
        T result;
        generate(&result);
        return result;
    }

    static bool hasInstance();
    static RandomGenerator *instance(); // Returns the currently active instance
    static RandomGenerator *setInstance(RandomGenerator *instance);
};

class TELEGRAMQT_INTERNAL_EXPORT DeterministicGenerator : public RandomGenerator
{
public:
    DeterministicGenerator();

    using RandomGenerator::generate;

    int generate(void *buffer, int count) override;

    QByteArray initializationData() const { return m_initializationData; }
    void setInitializationData(const QByteArray &data);

protected:
    void regenerate();

    QByteArray m_initializationData;
    QByteArray m_generatedData;
    quint8 m_offset = 0;

};

class TELEGRAMQT_INTERNAL_EXPORT RandomGeneratorSetter
{
public:
    explicit RandomGeneratorSetter(RandomGenerator *generator);
    ~RandomGeneratorSetter();

private:
    RandomGenerator *m_previousGenerator = nullptr;
};

} // Telegram namespace

#endif // TELEGRAM_RANDOM_GENERATOR_HPP
