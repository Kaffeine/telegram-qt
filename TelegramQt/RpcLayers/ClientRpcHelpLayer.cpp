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
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpDeepLinkInfo *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpInviteText *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpPassportConfig *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpProxyData *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpRecentMeUrls *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpSupport *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpSupportName *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpTermsOfService *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpTermsOfServiceUpdate *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLHelpUserInfo *output);
// End of generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLConfig *output);

HelpRpcLayer::HelpRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
HelpRpcLayer::PendingBool *HelpRpcLayer::acceptTermsOfService(const TLDataJSON &id)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpAcceptTermsOfService;
    outputStream << id;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpUserInfo *HelpRpcLayer::editUserInfo(const TLInputUser &userId, const QString &message, const TLVector<TLMessageEntity> &entities)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << userId << message << entities;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpEditUserInfo;
    outputStream << userId;
    outputStream << message;
    outputStream << entities;
    PendingHelpUserInfo *op = new PendingHelpUserInfo(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

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

HelpRpcLayer::PendingJSONValue *HelpRpcLayer::getAppConfig()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetAppConfig;
    PendingJSONValue *op = new PendingJSONValue(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpAppUpdate *HelpRpcLayer::getAppUpdate(const QString &source)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << source;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetAppUpdate;
    outputStream << source;
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

HelpRpcLayer::PendingHelpDeepLinkInfo *HelpRpcLayer::getDeepLinkInfo(const QString &path)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << path;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetDeepLinkInfo;
    outputStream << path;
    PendingHelpDeepLinkInfo *op = new PendingHelpDeepLinkInfo(this, outputStream.getData());
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

HelpRpcLayer::PendingHelpPassportConfig *HelpRpcLayer::getPassportConfig(quint32 hash)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << hash;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetPassportConfig;
    outputStream << hash;
    PendingHelpPassportConfig *op = new PendingHelpPassportConfig(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpProxyData *HelpRpcLayer::getProxyData()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetProxyData;
    PendingHelpProxyData *op = new PendingHelpProxyData(this, outputStream.getData());
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

HelpRpcLayer::PendingHelpSupportName *HelpRpcLayer::getSupportName()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetSupportName;
    PendingHelpSupportName *op = new PendingHelpSupportName(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpTermsOfServiceUpdate *HelpRpcLayer::getTermsOfServiceUpdate()
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetTermsOfServiceUpdate;
    PendingHelpTermsOfServiceUpdate *op = new PendingHelpTermsOfServiceUpdate(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

HelpRpcLayer::PendingHelpUserInfo *HelpRpcLayer::getUserInfo(const TLInputUser &userId)
{
    qCDebug(c_clientRpcHelpCategory) << Q_FUNC_INFO << userId;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::HelpGetUserInfo;
    outputStream << userId;
    PendingHelpUserInfo *op = new PendingHelpUserInfo(this, outputStream.getData());
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
