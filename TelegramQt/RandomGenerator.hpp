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

class RandomGenerator
{
public:
    virtual ~RandomGenerator() = default;
    virtual int generate(void *buffer, int count);

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

    static RandomGenerator *instance(); // Returns the currently active instance
    static RandomGenerator *setInstance(RandomGenerator *instance);
};

class DeterministicGenerator : public RandomGenerator
{
public:
    using RandomGenerator::generate;

    int generate(void *buffer, int count) override;

protected:
    void regenerate();

    QByteArray m_generatedData;
    quint8 m_offset = 0;

};

class RandomGeneratorSetter
{
public:
    RandomGeneratorSetter(RandomGenerator *generator)
    {
        m_previousGenerator = RandomGenerator::setInstance(generator);
    }

    ~RandomGeneratorSetter()
    {
        RandomGenerator::setInstance(m_previousGenerator);
    }
private:
    RandomGenerator *m_previousGenerator;
};

} // Telegram

#endif // TELEGRAM_RANDOM_GENERATOR_HPP
