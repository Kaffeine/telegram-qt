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
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcHelpCategory, "telegram.client.rpclayer.help", QtWarningMsg)

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
HelpRpcLayer::PendingUpdates *HelpRpcLayer::getAppChangelog(const QString &prevAppVersion)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << prevAppVersion;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetAppChangelog;
    outputStream << prevAppVersion;
    PendingUpdates *op = new PendingUpdates(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpAppUpdate *HelpRpcLayer::getAppUpdate()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetAppUpdate;
    PendingHelpAppUpdate *op = new PendingHelpAppUpdate(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingCdnConfig *HelpRpcLayer::getCdnConfig()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetCdnConfig;
    PendingCdnConfig *op = new PendingCdnConfig(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingConfig *HelpRpcLayer::getConfig()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetConfig;
    PendingConfig *op = new PendingConfig(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpInviteText *HelpRpcLayer::getInviteText()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetInviteText;
    PendingHelpInviteText *op = new PendingHelpInviteText(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingNearestDc *HelpRpcLayer::getNearestDc()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetNearestDc;
    PendingNearestDc *op = new PendingNearestDc(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpRecentMeUrls *HelpRpcLayer::getRecentMeUrls(const QString &referer)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << referer;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetRecentMeUrls;
    outputStream << referer;
    PendingHelpRecentMeUrls *op = new PendingHelpRecentMeUrls(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpSupport *HelpRpcLayer::getSupport()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetSupport;
    PendingHelpSupport *op = new PendingHelpSupport(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpTermsOfService *HelpRpcLayer::getTermsOfService()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetTermsOfService;
    PendingHelpTermsOfService *op = new PendingHelpTermsOfService(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingBool *HelpRpcLayer::saveAppLog(const TLVector<TLInputAppEvent> &events)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << events;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpSaveAppLog;
    outputStream << events;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingBool *HelpRpcLayer::setBotUpdatesStatus(quint32 pendingUpdatesCount, const QString &message)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << pendingUpdatesCount << message;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpSetBotUpdatesStatus;
    outputStream << pendingUpdatesCount;
    outputStream << message;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
