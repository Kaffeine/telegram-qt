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

#include "HelpOperationFactory.hpp"

#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "LocalServerApi.hpp"
#include "ServerRpcLayer.hpp"
#include "TelegramServerUser.hpp"

#include "ApiUtils.hpp"
#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Server {

// Generated process methods
bool HelpRpcOperation::processAcceptTermsOfService(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runAcceptTermsOfService);
    context.inputStream() >> m_acceptTermsOfService;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processEditUserInfo(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runEditUserInfo);
    context.inputStream() >> m_editUserInfo;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetAppChangelog(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetAppChangelog);
    context.inputStream() >> m_getAppChangelog;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetAppConfig(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetAppConfig);
    context.inputStream() >> m_getAppConfig;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetAppUpdate(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetAppUpdate);
    context.inputStream() >> m_getAppUpdate;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetCdnConfig(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetCdnConfig);
    context.inputStream() >> m_getCdnConfig;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetConfig(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetConfig);
    context.inputStream() >> m_getConfig;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetDeepLinkInfo(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetDeepLinkInfo);
    context.inputStream() >> m_getDeepLinkInfo;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetInviteText(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetInviteText);
    context.inputStream() >> m_getInviteText;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetNearestDc(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetNearestDc);
    context.inputStream() >> m_getNearestDc;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetPassportConfig(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetPassportConfig);
    context.inputStream() >> m_getPassportConfig;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetProxyData(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetProxyData);
    context.inputStream() >> m_getProxyData;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetRecentMeUrls(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetRecentMeUrls);
    context.inputStream() >> m_getRecentMeUrls;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetSupport(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetSupport);
    context.inputStream() >> m_getSupport;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetSupportName(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetSupportName);
    context.inputStream() >> m_getSupportName;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetTermsOfServiceUpdate(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetTermsOfServiceUpdate);
    context.inputStream() >> m_getTermsOfServiceUpdate;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processGetUserInfo(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runGetUserInfo);
    context.inputStream() >> m_getUserInfo;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processSaveAppLog(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runSaveAppLog);
    context.inputStream() >> m_saveAppLog;
    return !context.inputStream().error();
}

bool HelpRpcOperation::processSetBotUpdatesStatus(RpcProcessingContext &context)
{
    setRunMethod(&HelpRpcOperation::runSetBotUpdatesStatus);
    context.inputStream() >> m_setBotUpdatesStatus;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void HelpRpcOperation::runAcceptTermsOfService()
{
    // MTProto::Functions::TLHelpAcceptTermsOfService &arguments = m_acceptTermsOfService;
    if (processNotImplementedMethod(TLValue::HelpAcceptTermsOfService)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void HelpRpcOperation::runEditUserInfo()
{
    // MTProto::Functions::TLHelpEditUserInfo &arguments = m_editUserInfo;
    if (processNotImplementedMethod(TLValue::HelpEditUserInfo)) {
        return;
    }
    TLHelpUserInfo result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetAppChangelog()
{
    // MTProto::Functions::TLHelpGetAppChangelog &arguments = m_getAppChangelog;
    if (processNotImplementedMethod(TLValue::HelpGetAppChangelog)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetAppConfig()
{
    if (processNotImplementedMethod(TLValue::HelpGetAppConfig)) {
        return;
    }
    TLJSONValue result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetAppUpdate()
{
    if (processNotImplementedMethod(TLValue::HelpGetAppUpdate)) {
        return;
    }
    TLHelpAppUpdate result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetCdnConfig()
{
    if (processNotImplementedMethod(TLValue::HelpGetCdnConfig)) {
        return;
    }
    TLCdnConfig result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetConfig()
{
    const DcConfiguration dcConfig = api()->serverConfiguration();
    TLConfig result;
    result.flags = TLConfig::PhonecallsEnabled;
    result.date = Telegram::Utils::getCurrentTime();
    result.expires = result.date + 60 * 60;
    result.testMode = dcConfig.testMode;
    result.thisDc = api()->dcId();
    // TODO: fill other fields of result
    // manually copy fields from all DcOption's to TLDcOption's
    for (const DcOption &dcOption : dcConfig.dcOptions) {
        TLDcOption tlDcOption;
        tlDcOption.id = dcOption.id;
        tlDcOption.ipAddress = dcOption.address;
        tlDcOption.port = dcOption.port;
        tlDcOption.flags = dcOption.flags;
        result.dcOptions.append(std::move(tlDcOption));
    }
    result.chatSizeMax = dcConfig.chatSizeMax;
    result.megagroupSizeMax = dcConfig.megagroupSizeMax;
    result.forwardedCountMax = dcConfig.forwardedCountMax;
    result.onlineCloudTimeoutMs = dcConfig.onlineCloudTimeoutMs;
    result.onlineUpdatePeriodMs = dcConfig.onlineUpdatePeriodMs;
    result.offlineBlurTimeoutMs = dcConfig.offlineBlurTimeoutMs;
    result.offlineIdleTimeoutMs = dcConfig.offlineIdleTimeoutMs;
    result.editTimeLimit = dcConfig.editTimeLimit;
    result.meUrlPrefix = dcConfig.meUrlPrefix;

    sendRpcReply(result);
}

void HelpRpcOperation::runGetDeepLinkInfo()
{
    // MTProto::Functions::TLHelpGetDeepLinkInfo &arguments = m_getDeepLinkInfo;
    if (processNotImplementedMethod(TLValue::HelpGetDeepLinkInfo)) {
        return;
    }
    TLHelpDeepLinkInfo result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetInviteText()
{
    if (processNotImplementedMethod(TLValue::HelpGetInviteText)) {
        return;
    }
    TLHelpInviteText result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetNearestDc()
{
    TLNearestDc result;
    result.thisDc = api()->dcId();
    result.nearestDc = 1;
    // ISO 3166-1 alpha-2
    result.country = QStringLiteral("AQ");
    sendRpcReply(result);
}

void HelpRpcOperation::runGetPassportConfig()
{
    // MTProto::Functions::TLHelpGetPassportConfig &arguments = m_getPassportConfig;
    if (processNotImplementedMethod(TLValue::HelpGetPassportConfig)) {
        return;
    }
    TLHelpPassportConfig result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetProxyData()
{
    if (processNotImplementedMethod(TLValue::HelpGetProxyData)) {
        return;
    }
    TLHelpProxyData result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetRecentMeUrls()
{
    // MTProto::Functions::TLHelpGetRecentMeUrls &arguments = m_getRecentMeUrls;
    if (processNotImplementedMethod(TLValue::HelpGetRecentMeUrls)) {
        return;
    }
    TLHelpRecentMeUrls result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetSupport()
{
    if (processNotImplementedMethod(TLValue::HelpGetSupport)) {
        return;
    }
    TLHelpSupport result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetSupportName()
{
    if (processNotImplementedMethod(TLValue::HelpGetSupportName)) {
        return;
    }
    TLHelpSupportName result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetTermsOfServiceUpdate()
{
    if (processNotImplementedMethod(TLValue::HelpGetTermsOfServiceUpdate)) {
        return;
    }
    TLHelpTermsOfServiceUpdate result;
    sendRpcReply(result);
}

void HelpRpcOperation::runGetUserInfo()
{
    // MTProto::Functions::TLHelpGetUserInfo &arguments = m_getUserInfo;
    if (processNotImplementedMethod(TLValue::HelpGetUserInfo)) {
        return;
    }
    TLHelpUserInfo result;
    sendRpcReply(result);
}

void HelpRpcOperation::runSaveAppLog()
{
    // MTProto::Functions::TLHelpSaveAppLog &arguments = m_saveAppLog;
    if (processNotImplementedMethod(TLValue::HelpSaveAppLog)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void HelpRpcOperation::runSetBotUpdatesStatus()
{
    // MTProto::Functions::TLHelpSetBotUpdatesStatus &arguments = m_setBotUpdatesStatus;
    if (processNotImplementedMethod(TLValue::HelpSetBotUpdatesStatus)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}
// End of generated run methods

void HelpRpcOperation::setRunMethod(HelpRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

HelpRpcOperation::ProcessingMethod HelpRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::HelpAcceptTermsOfService:
        return &HelpRpcOperation::processAcceptTermsOfService;
    case TLValue::HelpEditUserInfo:
        return &HelpRpcOperation::processEditUserInfo;
    case TLValue::HelpGetAppChangelog:
        return &HelpRpcOperation::processGetAppChangelog;
    case TLValue::HelpGetAppConfig:
        return &HelpRpcOperation::processGetAppConfig;
    case TLValue::HelpGetAppUpdate:
        return &HelpRpcOperation::processGetAppUpdate;
    case TLValue::HelpGetCdnConfig:
        return &HelpRpcOperation::processGetCdnConfig;
    case TLValue::HelpGetConfig:
        return &HelpRpcOperation::processGetConfig;
    case TLValue::HelpGetDeepLinkInfo:
        return &HelpRpcOperation::processGetDeepLinkInfo;
    case TLValue::HelpGetInviteText:
        return &HelpRpcOperation::processGetInviteText;
    case TLValue::HelpGetNearestDc:
        return &HelpRpcOperation::processGetNearestDc;
    case TLValue::HelpGetPassportConfig:
        return &HelpRpcOperation::processGetPassportConfig;
    case TLValue::HelpGetProxyData:
        return &HelpRpcOperation::processGetProxyData;
    case TLValue::HelpGetRecentMeUrls:
        return &HelpRpcOperation::processGetRecentMeUrls;
    case TLValue::HelpGetSupport:
        return &HelpRpcOperation::processGetSupport;
    case TLValue::HelpGetSupportName:
        return &HelpRpcOperation::processGetSupportName;
    case TLValue::HelpGetTermsOfServiceUpdate:
        return &HelpRpcOperation::processGetTermsOfServiceUpdate;
    case TLValue::HelpGetUserInfo:
        return &HelpRpcOperation::processGetUserInfo;
    case TLValue::HelpSaveAppLog:
        return &HelpRpcOperation::processSaveAppLog;
    case TLValue::HelpSetBotUpdatesStatus:
        return &HelpRpcOperation::processSetBotUpdatesStatus;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *HelpOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<HelpRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
