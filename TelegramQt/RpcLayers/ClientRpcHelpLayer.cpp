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

#include "ClientRpcHelpLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcHelpCategory, "telegram.client.rpclayer.help", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpAppUpdate *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpConfigSimple *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpInviteText *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpRecentMeUrls *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpSupport *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpTermsOfService *output);
// End of generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLConfig *output);

HelpRpcLayer::HelpRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *HelpRpcLayer::getAppChangelog(const QString &prevAppVersion)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << prevAppVersion;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetAppChangelog;
    outputStream << prevAppVersion;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getAppUpdate()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetAppUpdate;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getCdnConfig()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetCdnConfig;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getConfig()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetConfig;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getInviteText()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetInviteText;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getNearestDc()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetNearestDc;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getRecentMeUrls(const QString &referer)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << referer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetRecentMeUrls;
    outputStream << referer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getSupport()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetSupport;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::getTermsOfService()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpGetTermsOfService;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::saveAppLog(const TLVector<TLInputAppEvent> &events)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << events;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpSaveAppLog;
    outputStream << events;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *HelpRpcLayer::setBotUpdatesStatus(quint32 pendingUpdatesCount, const QString &message)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << pendingUpdatesCount << message;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::HelpSetBotUpdatesStatus;
    outputStream << pendingUpdatesCount;
    outputStream << message;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
