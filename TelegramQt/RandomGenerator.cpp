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

#include "RandomGenerator.hpp"

#include <QCryptographicHash>

#include <openssl/rand.h>

namespace Telegram {

static RandomGenerator *s_randomGenerator = nullptr;

int RandomGenerator::generate(void *buffer, int count)
{
    return RAND_bytes(static_cast<unsigned char *>(buffer), count);
}

bool RandomGenerator::hasInstance()
{
    return s_randomGenerator;
}

RandomGenerator *RandomGenerator::instance()
{
    Q_ASSERT_X(s_randomGenerator, "RandomGenerator", "RandomGenerator is not set."
                                        " Ensure that Telegram::initialize() was called.");
    return s_randomGenerator;
}

RandomGenerator *RandomGenerator::setInstance(RandomGenerator *instance)
{
    RandomGenerator *previousGenerator = s_randomGenerator;
    s_randomGenerator = instance;
    return previousGenerator;
}

DeterministicGenerator::DeterministicGenerator() :
    RandomGenerator(),
    m_initializationData(QByteArrayLiteral("default"))
{
}

int DeterministicGenerator::generate(void *buffer, int count)
{
    int processedBytes = 0;
    char *dest = static_cast<char *>(buffer);
    while (processedBytes < count) {
        if (m_offset == m_generatedData.size()) {
            regenerate();
        }
        const int available = m_generatedData.size() - m_offset;
        const int bytesToCopy = qMin<int>(count - processedBytes, available);
        memcpy(dest + processedBytes, m_generatedData.constData() + m_offset, static_cast<size_t>(bytesToCopy));
        processedBytes += bytesToCopy;
        m_offset += bytesToCopy;
    }
    return count;
}

void DeterministicGenerator::setInitializationData(const QByteArray &data)
{
    m_initializationData = data;
}

void DeterministicGenerator::regenerate()
{
    if (m_generatedData.isEmpty()) {
        m_generatedData = m_initializationData;
    }
    m_generatedData = QCryptographicHash::hash(m_generatedData, QCryptographicHash::Sha512);
    m_offset = 0;
}

RandomGeneratorSetter::RandomGeneratorSetter(RandomGenerator *generator)
{
    m_previousGenerator = RandomGenerator::setInstance(generator);
}

RandomGeneratorSetter::~RandomGeneratorSetter()
{
    RandomGenerator::setInstance(m_previousGenerator);
}

} // Telegram
