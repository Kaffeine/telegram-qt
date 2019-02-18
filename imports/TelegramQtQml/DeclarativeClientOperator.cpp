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

#include "DeclarativeClientOperator.hpp"

#include "DeclarativeClient.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_loggingClientOperator, "telegram.client.qml.clientoperator", QtWarningMsg)

namespace Telegram {

namespace Client {

DeclarativeClientOperator::DeclarativeClientOperator(QObject *parent) :
    QObject(parent)
{
}

void DeclarativeClientOperator::setQmlClient(DeclarativeClient *client)
{
    if (m_qmlClient == client) {
        return;
    }
    m_qmlClient = client;
    emit clientChanged();
}

void DeclarativeClientOperator::syncSettings()
{
    if (m_qmlClient) {
        m_qmlClient->syncSettings();
    } else {
        qCCritical(c_loggingClientOperator).nospace() << this << ": Unable to sync settings (client instance is not set).";
    }
}

Client *DeclarativeClientMixin::client() const
{
    if (m_qmlClient) {
        return m_qmlClient->client();
    }
    qCCritical(c_loggingClientOperator).nospace() << this << ": Client instance is not set";
    return nullptr;
}

} // Client

} // Telegram
