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

#include "MessagesOperationFactory.hpp"

#include "ApiUtils.hpp"
#include "RpcOperationFactory_p.hpp"
// TODO: Instead of this include, add a generated cpp with all needed template instances
#include "ServerRpcOperation_p.hpp"

#include "GroupChat.hpp"
#include "IMediaService.hpp"
#include "LocalServerApi.hpp"
#include "RandomGenerator.hpp"
#include "ServerMessageData.hpp"
#include "ServerRpcLayer.hpp"
#include "ServerUtils.hpp"
#include "MessageService.hpp"
#include "TelegramServerUser.hpp"

#include "Debug_p.hpp"
#include "RpcError.hpp"
#include "RpcProcessingContext.hpp"

#include "MTProto/StreamExtraOperators.hpp"
#include "FunctionStreamOperators.hpp"

#include <QLoggingCategory>

constexpr int c_serverHistorySliceLimit = 30;
constexpr int c_serverDialogsSliceLimit = 5;

namespace Telegram {

namespace Server {

// Generated process methods
bool MessagesRpcOperation::processAcceptEncryption(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runAcceptEncryption);
    context.inputStream() >> m_acceptEncryption;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processAddChatUser(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runAddChatUser);
    context.inputStream() >> m_addChatUser;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processCheckChatInvite(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runCheckChatInvite);
    context.inputStream() >> m_checkChatInvite;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processClearAllDrafts(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runClearAllDrafts);
    context.inputStream() >> m_clearAllDrafts;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processClearRecentStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runClearRecentStickers);
    context.inputStream() >> m_clearRecentStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processCreateChat(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runCreateChat);
    context.inputStream() >> m_createChat;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processDeleteChatUser(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runDeleteChatUser);
    context.inputStream() >> m_deleteChatUser;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processDeleteHistory(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runDeleteHistory);
    context.inputStream() >> m_deleteHistory;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processDeleteMessages(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runDeleteMessages);
    context.inputStream() >> m_deleteMessages;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processDiscardEncryption(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runDiscardEncryption);
    context.inputStream() >> m_discardEncryption;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processEditChatAdmin(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runEditChatAdmin);
    context.inputStream() >> m_editChatAdmin;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processEditChatPhoto(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runEditChatPhoto);
    context.inputStream() >> m_editChatPhoto;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processEditChatTitle(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runEditChatTitle);
    context.inputStream() >> m_editChatTitle;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processEditInlineBotMessage(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runEditInlineBotMessage);
    context.inputStream() >> m_editInlineBotMessage;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processEditMessage(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runEditMessage);
    context.inputStream() >> m_editMessage;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processExportChatInvite(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runExportChatInvite);
    context.inputStream() >> m_exportChatInvite;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processFaveSticker(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runFaveSticker);
    context.inputStream() >> m_faveSticker;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processForwardMessages(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runForwardMessages);
    context.inputStream() >> m_forwardMessages;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetAllChats(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetAllChats);
    context.inputStream() >> m_getAllChats;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetAllDrafts(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetAllDrafts);
    context.inputStream() >> m_getAllDrafts;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetAllStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetAllStickers);
    context.inputStream() >> m_getAllStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetArchivedStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetArchivedStickers);
    context.inputStream() >> m_getArchivedStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetAttachedStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetAttachedStickers);
    context.inputStream() >> m_getAttachedStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetBotCallbackAnswer(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetBotCallbackAnswer);
    context.inputStream() >> m_getBotCallbackAnswer;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetChats(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetChats);
    context.inputStream() >> m_getChats;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetCommonChats(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetCommonChats);
    context.inputStream() >> m_getCommonChats;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetDhConfig(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetDhConfig);
    context.inputStream() >> m_getDhConfig;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetDialogUnreadMarks(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetDialogUnreadMarks);
    context.inputStream() >> m_getDialogUnreadMarks;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetDialogs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetDialogs);
    context.inputStream() >> m_getDialogs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetDocumentByHash(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetDocumentByHash);
    context.inputStream() >> m_getDocumentByHash;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetFavedStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetFavedStickers);
    context.inputStream() >> m_getFavedStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetFeaturedStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetFeaturedStickers);
    context.inputStream() >> m_getFeaturedStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetFullChat(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetFullChat);
    context.inputStream() >> m_getFullChat;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetGameHighScores(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetGameHighScores);
    context.inputStream() >> m_getGameHighScores;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetHistory(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetHistory);
    context.inputStream() >> m_getHistory;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetInlineBotResults(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetInlineBotResults);
    context.inputStream() >> m_getInlineBotResults;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetInlineGameHighScores(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetInlineGameHighScores);
    context.inputStream() >> m_getInlineGameHighScores;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetMaskStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetMaskStickers);
    context.inputStream() >> m_getMaskStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetMessageEditData(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetMessageEditData);
    context.inputStream() >> m_getMessageEditData;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetMessages(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetMessages);
    context.inputStream() >> m_getMessages;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetMessagesViews(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetMessagesViews);
    context.inputStream() >> m_getMessagesViews;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetOnlines(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetOnlines);
    context.inputStream() >> m_getOnlines;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetPeerDialogs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetPeerDialogs);
    context.inputStream() >> m_getPeerDialogs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetPeerSettings(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetPeerSettings);
    context.inputStream() >> m_getPeerSettings;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetPinnedDialogs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetPinnedDialogs);
    context.inputStream() >> m_getPinnedDialogs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetPollResults(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetPollResults);
    context.inputStream() >> m_getPollResults;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetRecentLocations(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetRecentLocations);
    context.inputStream() >> m_getRecentLocations;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetRecentStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetRecentStickers);
    context.inputStream() >> m_getRecentStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetSavedGifs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetSavedGifs);
    context.inputStream() >> m_getSavedGifs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetSplitRanges(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetSplitRanges);
    context.inputStream() >> m_getSplitRanges;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetStatsURL(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetStatsURL);
    context.inputStream() >> m_getStatsURL;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetStickerSet(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetStickerSet);
    context.inputStream() >> m_getStickerSet;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetStickers);
    context.inputStream() >> m_getStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetUnreadMentions(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetUnreadMentions);
    context.inputStream() >> m_getUnreadMentions;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetWebPage(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetWebPage);
    context.inputStream() >> m_getWebPage;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processGetWebPagePreview(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runGetWebPagePreview);
    context.inputStream() >> m_getWebPagePreview;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processHideReportSpam(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runHideReportSpam);
    context.inputStream() >> m_hideReportSpam;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processImportChatInvite(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runImportChatInvite);
    context.inputStream() >> m_importChatInvite;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processInstallStickerSet(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runInstallStickerSet);
    context.inputStream() >> m_installStickerSet;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processMarkDialogUnread(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runMarkDialogUnread);
    context.inputStream() >> m_markDialogUnread;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processMigrateChat(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runMigrateChat);
    context.inputStream() >> m_migrateChat;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReadEncryptedHistory(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReadEncryptedHistory);
    context.inputStream() >> m_readEncryptedHistory;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReadFeaturedStickers(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReadFeaturedStickers);
    context.inputStream() >> m_readFeaturedStickers;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReadHistory(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReadHistory);
    context.inputStream() >> m_readHistory;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReadMentions(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReadMentions);
    context.inputStream() >> m_readMentions;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReadMessageContents(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReadMessageContents);
    context.inputStream() >> m_readMessageContents;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReceivedMessages(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReceivedMessages);
    context.inputStream() >> m_receivedMessages;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReceivedQueue(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReceivedQueue);
    context.inputStream() >> m_receivedQueue;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReorderPinnedDialogs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReorderPinnedDialogs);
    context.inputStream() >> m_reorderPinnedDialogs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReorderStickerSets(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReorderStickerSets);
    context.inputStream() >> m_reorderStickerSets;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReport(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReport);
    context.inputStream() >> m_report;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReportEncryptedSpam(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReportEncryptedSpam);
    context.inputStream() >> m_reportEncryptedSpam;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processReportSpam(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runReportSpam);
    context.inputStream() >> m_reportSpam;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processRequestEncryption(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runRequestEncryption);
    context.inputStream() >> m_requestEncryption;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSaveDraft(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSaveDraft);
    context.inputStream() >> m_saveDraft;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSaveGif(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSaveGif);
    context.inputStream() >> m_saveGif;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSaveRecentSticker(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSaveRecentSticker);
    context.inputStream() >> m_saveRecentSticker;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSearch(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSearch);
    context.inputStream() >> m_search;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSearchGifs(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSearchGifs);
    context.inputStream() >> m_searchGifs;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSearchGlobal(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSearchGlobal);
    context.inputStream() >> m_searchGlobal;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSearchStickerSets(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSearchStickerSets);
    context.inputStream() >> m_searchStickerSets;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendEncrypted(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendEncrypted);
    context.inputStream() >> m_sendEncrypted;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendEncryptedFile(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendEncryptedFile);
    context.inputStream() >> m_sendEncryptedFile;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendEncryptedService(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendEncryptedService);
    context.inputStream() >> m_sendEncryptedService;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendInlineBotResult(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendInlineBotResult);
    context.inputStream() >> m_sendInlineBotResult;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendMedia(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendMedia);
    context.inputStream() >> m_sendMedia;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendMessage(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendMessage);
    context.inputStream() >> m_sendMessage;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendMultiMedia(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendMultiMedia);
    context.inputStream() >> m_sendMultiMedia;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendScreenshotNotification(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendScreenshotNotification);
    context.inputStream() >> m_sendScreenshotNotification;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSendVote(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSendVote);
    context.inputStream() >> m_sendVote;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetBotCallbackAnswer(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetBotCallbackAnswer);
    context.inputStream() >> m_setBotCallbackAnswer;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetBotPrecheckoutResults(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetBotPrecheckoutResults);
    context.inputStream() >> m_setBotPrecheckoutResults;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetBotShippingResults(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetBotShippingResults);
    context.inputStream() >> m_setBotShippingResults;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetEncryptedTyping(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetEncryptedTyping);
    context.inputStream() >> m_setEncryptedTyping;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetGameScore(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetGameScore);
    context.inputStream() >> m_setGameScore;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetInlineBotResults(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetInlineBotResults);
    context.inputStream() >> m_setInlineBotResults;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetInlineGameScore(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetInlineGameScore);
    context.inputStream() >> m_setInlineGameScore;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processSetTyping(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runSetTyping);
    context.inputStream() >> m_setTyping;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processStartBot(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runStartBot);
    context.inputStream() >> m_startBot;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processToggleChatAdmins(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runToggleChatAdmins);
    context.inputStream() >> m_toggleChatAdmins;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processToggleDialogPin(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runToggleDialogPin);
    context.inputStream() >> m_toggleDialogPin;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processUninstallStickerSet(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runUninstallStickerSet);
    context.inputStream() >> m_uninstallStickerSet;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processUpdatePinnedMessage(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runUpdatePinnedMessage);
    context.inputStream() >> m_updatePinnedMessage;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processUploadEncryptedFile(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runUploadEncryptedFile);
    context.inputStream() >> m_uploadEncryptedFile;
    return !context.inputStream().error();
}

bool MessagesRpcOperation::processUploadMedia(RpcProcessingContext &context)
{
    setRunMethod(&MessagesRpcOperation::runUploadMedia);
    context.inputStream() >> m_uploadMedia;
    return !context.inputStream().error();
}
// End of generated process methods

// Generated run methods
void MessagesRpcOperation::runAcceptEncryption()
{
    // MTProto::Functions::TLMessagesAcceptEncryption &arguments = m_acceptEncryption;
    if (processNotImplementedMethod(TLValue::MessagesAcceptEncryption)) {
        return;
    }
    TLEncryptedChat result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runAddChatUser()
{
    // MTProto::Functions::TLMessagesAddChatUser &arguments = m_addChatUser;
    if (processNotImplementedMethod(TLValue::MessagesAddChatUser)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runCheckChatInvite()
{
    // MTProto::Functions::TLMessagesCheckChatInvite &arguments = m_checkChatInvite;
    if (processNotImplementedMethod(TLValue::MessagesCheckChatInvite)) {
        return;
    }
    TLChatInvite result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runClearAllDrafts()
{
    if (processNotImplementedMethod(TLValue::MessagesClearAllDrafts)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runClearRecentStickers()
{
    // MTProto::Functions::TLMessagesClearRecentStickers &arguments = m_clearRecentStickers;
    if (processNotImplementedMethod(TLValue::MessagesClearRecentStickers)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runCreateChat()
{
    MTProto::Functions::TLMessagesCreateChat &arguments = m_createChat;
    LocalUser *selfUser = layer()->getUser();
    QVector<quint32> members;
    members.reserve(arguments.users.count());
    for (const TLInputUser &inputUser : arguments.users) {
        const AbstractUser *user = api()->getAbstractUser(inputUser, selfUser);
        members.append(user->id());
    }

    const quint32 requestDate = Telegram::Utils::getCurrentTime();

    GroupChat *groupChat = api()->createChat(selfUser, arguments.title, members);
    const Peer targetPeer = groupChat->toPeer();

    Session *excludeSession = layer()->session();
    QVector<UpdateNotification> notifications = api()->announceNewChat(targetPeer, excludeSession);

    QSet<Peer> interestingPeers;

    if (notifications.count() != 2) {
        qCritical() << "Unable to announce a chat";
        sendRpcError(RpcError::UnknownReason);
        return;
    }
    const UpdateNotification &participantsNotification = notifications.constFirst();
    const UpdateNotification &newMessageNotification = notifications.constLast();

    TLUpdate updateMessageId;
    updateMessageId.tlType = TLValue::UpdateMessageID;
    updateMessageId.quint32Id = newMessageNotification.messageId;
    updateMessageId.randomId = RandomGenerator::instance()->generate<quint64>();

    TLUpdate updateChatParticipants;
    api()->bakeUpdate(&updateChatParticipants, participantsNotification, &interestingPeers);

    TLUpdate updateNewMessage;
    api()->bakeUpdate(&updateNewMessage, newMessageNotification, &interestingPeers);

    // Bake updates
    TLUpdates result;
    result.tlType = TLValue::Updates;
    result.date = requestDate;

    Utils::setupTLPeers(&result, interestingPeers, api(), selfUser);
    result.seq = 0; // Sender seq number seems to always equal zero
    result.updates = {
        updateMessageId,
        updateChatParticipants,
        updateNewMessage,
    };
    sendRpcReply(result);
}

void MessagesRpcOperation::runDeleteChatUser()
{
    // MTProto::Functions::TLMessagesDeleteChatUser &arguments = m_deleteChatUser;
    if (processNotImplementedMethod(TLValue::MessagesDeleteChatUser)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runDeleteHistory()
{
    // MTProto::Functions::TLMessagesDeleteHistory &arguments = m_deleteHistory;
    if (processNotImplementedMethod(TLValue::MessagesDeleteHistory)) {
        return;
    }
    TLMessagesAffectedHistory result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runDeleteMessages()
{
    // MTProto::Functions::TLMessagesDeleteMessages &arguments = m_deleteMessages;
    if (processNotImplementedMethod(TLValue::MessagesDeleteMessages)) {
        return;
    }
    TLMessagesAffectedMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runDiscardEncryption()
{
    // MTProto::Functions::TLMessagesDiscardEncryption &arguments = m_discardEncryption;
    if (processNotImplementedMethod(TLValue::MessagesDiscardEncryption)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runEditChatAdmin()
{
    // MTProto::Functions::TLMessagesEditChatAdmin &arguments = m_editChatAdmin;
    if (processNotImplementedMethod(TLValue::MessagesEditChatAdmin)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runEditChatPhoto()
{
    // MTProto::Functions::TLMessagesEditChatPhoto &arguments = m_editChatPhoto;
    if (processNotImplementedMethod(TLValue::MessagesEditChatPhoto)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runEditChatTitle()
{
    // MTProto::Functions::TLMessagesEditChatTitle &arguments = m_editChatTitle;
    if (processNotImplementedMethod(TLValue::MessagesEditChatTitle)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runEditInlineBotMessage()
{
    // MTProto::Functions::TLMessagesEditInlineBotMessage &arguments = m_editInlineBotMessage;
    if (processNotImplementedMethod(TLValue::MessagesEditInlineBotMessage)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runEditMessage()
{
    MTProto::Functions::TLMessagesEditMessage &arguments = m_editMessage;
    const quint32 &messageId = arguments.id;
    LocalUser *selfUser = layer()->getUser();
    MessageRecipient *recipient = api()->getRecipient(arguments.peer, selfUser);

    if (!recipient) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    const QHash<quint32,quint64> messageKeys = selfUser->getPostBox()->getAllMessageKeys();

    const quint64 globalMessageId = messageKeys.value(messageId);
    const MessageData *previousData = globalMessageId
            ? api()->messageService()->getMessage(globalMessageId)
            : nullptr;
    if (!globalMessageId || !previousData) {
        sendRpcError(RpcError::MessageIdInvalid);
        return;
    }

    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    if (requestDate >= previousData->date() + api()->serverConfiguration().editTimeLimit) {
        sendRpcError(RpcError::MessageEditTimeExpired);
        return;
    }

    const MessageContent newContent(arguments.message);
    if (previousData->content() == newContent) {
        sendRpcError(RpcError::MessageNotModified);
        return;
    }

    MessageData *messageData = api()->messageService()->replaceMessageContent(globalMessageId, newContent);

    if (!messageData) {
        sendRpcError(RpcError::MessageIdInvalid);
        return;
    }

    QVector<UpdateNotification> notifications = api()->processMessageEdit(messageData);

    UpdateNotification *selfNotification = nullptr;
    for (UpdateNotification &notification : notifications) {
        if (notification.userId == selfUser->userId()) {
            selfNotification = &notification;
            break;
        }
    }

    selfNotification->excludeSession = layer()->session();

    QSet<Peer> interestingPeers;
    TLUpdate editMessageUpdate;
    api()->bakeUpdate(&editMessageUpdate, *selfNotification, &interestingPeers);

    // Bake updates
    TLUpdates result;
    result.tlType = TLValue::Updates;
    result.date = selfNotification->date;

    Utils::setupTLPeers(&result, interestingPeers, api(), selfUser);
    result.seq = 0; // Sender seq number seems to always equal zero
    result.updates = { editMessageUpdate };
    sendRpcReply(result);

    api()->queueUpdates(notifications);
}

void MessagesRpcOperation::runExportChatInvite()
{
    // MTProto::Functions::TLMessagesExportChatInvite &arguments = m_exportChatInvite;
    if (processNotImplementedMethod(TLValue::MessagesExportChatInvite)) {
        return;
    }
    TLExportedChatInvite result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runFaveSticker()
{
    // MTProto::Functions::TLMessagesFaveSticker &arguments = m_faveSticker;
    if (processNotImplementedMethod(TLValue::MessagesFaveSticker)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runForwardMessages()
{
    // MTProto::Functions::TLMessagesForwardMessages &arguments = m_forwardMessages;
    if (processNotImplementedMethod(TLValue::MessagesForwardMessages)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetAllChats()
{
    // MTProto::Functions::TLMessagesGetAllChats &arguments = m_getAllChats;
    if (processNotImplementedMethod(TLValue::MessagesGetAllChats)) {
        return;
    }
    TLMessagesChats result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetAllDrafts()
{
    if (processNotImplementedMethod(TLValue::MessagesGetAllDrafts)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetAllStickers()
{
    // MTProto::Functions::TLMessagesGetAllStickers &arguments = m_getAllStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetAllStickers)) {
        return;
    }
    TLMessagesAllStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetArchivedStickers()
{
    // MTProto::Functions::TLMessagesGetArchivedStickers &arguments = m_getArchivedStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetArchivedStickers)) {
        return;
    }
    TLMessagesArchivedStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetAttachedStickers()
{
    // MTProto::Functions::TLMessagesGetAttachedStickers &arguments = m_getAttachedStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetAttachedStickers)) {
        return;
    }
    TLVector<TLStickerSetCovered> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetBotCallbackAnswer()
{
    // MTProto::Functions::TLMessagesGetBotCallbackAnswer &arguments = m_getBotCallbackAnswer;
    if (processNotImplementedMethod(TLValue::MessagesGetBotCallbackAnswer)) {
        return;
    }
    TLMessagesBotCallbackAnswer result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetChats()
{
    // MTProto::Functions::TLMessagesGetChats &arguments = m_getChats;
    if (processNotImplementedMethod(TLValue::MessagesGetChats)) {
        return;
    }
    TLMessagesChats result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetCommonChats()
{
    // MTProto::Functions::TLMessagesGetCommonChats &arguments = m_getCommonChats;
    if (processNotImplementedMethod(TLValue::MessagesGetCommonChats)) {
        return;
    }
    TLMessagesChats result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetDhConfig()
{
    // MTProto::Functions::TLMessagesGetDhConfig &arguments = m_getDhConfig;
    if (processNotImplementedMethod(TLValue::MessagesGetDhConfig)) {
        return;
    }
    TLMessagesDhConfig result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetDialogUnreadMarks()
{
    if (processNotImplementedMethod(TLValue::MessagesGetDialogUnreadMarks)) {
        return;
    }
    TLVector<TLDialogPeer> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetDialogs()
{
    MTProto::Functions::TLMessagesGetDialogs &arguments = m_getDialogs;
    TLMessagesDialogs result;
    const LocalUser *selfUser = layer()->getUser();

    const QVector<UserDialog *> dialogs = selfUser->dialogs();
    result.count = static_cast<quint32>(dialogs.count());

    int dialogsToAdd = qMin(c_serverDialogsSliceLimit, dialogs.count());
    if (arguments.limit) {
        int limit = static_cast<int>(arguments.limit);
        if (limit < dialogsToAdd) {
            dialogsToAdd = limit;
        }
    }
    if (dialogsToAdd >= dialogs.count()) {
        result.tlType = TLValue::MessagesDialogs;
    } else {
        result.tlType = TLValue::MessagesDialogsSlice;
    }

    int fromDialogIndex = 0;
    if (arguments.offsetId) {
        Peer offsetPeer = api()->getPeer(arguments.offsetPeer, selfUser);
        const UserDialog *offsetDialog = selfUser->getDialog(offsetPeer);
        if (offsetDialog && (offsetDialog->topMessage == arguments.offsetId)) {
            for (int i = 0; i < dialogs.count(); ++i) {
                if (dialogs.at(i) == offsetDialog) {
                    fromDialogIndex = i + 1;
                    break;
                }
            }
        } else {
            // Peer not found or top message is changed. Fallback to 'date'.
            // If there is no dialog that matches the filter then there is nothing to return.
            fromDialogIndex = dialogs.count();
            for (int i = 0; i < dialogs.count(); ++i) {
                if (dialogs.at(i)->date <= arguments.offsetDate) {
                    fromDialogIndex = i;
                    break;
                }
            }
        }
    }

    QSet<Peer> interestingPeers;

    dialogsToAdd = qMin(dialogsToAdd, dialogs.count() - fromDialogIndex);
    result.dialogs.reserve(dialogsToAdd);

    for (int i = fromDialogIndex; i < dialogs.count(); ++i) {
        if (dialogsToAdd <= 0) {
            break;
        }

        const UserDialog *dialog = dialogs.at(i);

        TLDialog tlDialog;
        tlDialog.peer = Telegram::Utils::toTLPeer(dialog->peer);
        tlDialog.topMessage = dialog->topMessage;
        tlDialog.draft.message = dialog->draftText;
        tlDialog.draft.tlType = dialog->draftText.isEmpty() ? TLValue::DraftMessageEmpty : TLValue::DraftMessage;
        tlDialog.readInboxMaxId = dialog->readInboxMaxId;
        tlDialog.readOutboxMaxId = dialog->readOutboxMaxId;
        tlDialog.unreadCount = dialog->unreadCount;
        tlDialog.unreadMentionsCount = dialog->unreadMentionsCount;
        result.dialogs.append(tlDialog);
        if (dialogsToAdd) {
            --dialogsToAdd;
        }

        const PostBox *box = selfUser->getPostBox();
        quint64 topMessageGlobalId = box->getMessageGlobalId(tlDialog.topMessage);
        const MessageData *messageData = api()->messageService()->getMessage(topMessageGlobalId);

        if (messageData) {
            result.messages.resize(result.messages.size() + 1);
            Utils::setupTLMessage(&result.messages.last(), messageData, tlDialog.topMessage, selfUser);
        }

        interestingPeers.insert(dialog->peer);
    }

    Utils::getInterestingPeers(&interestingPeers, result.messages);
    Utils::setupTLPeers(&result, interestingPeers, api(), selfUser);
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetDocumentByHash()
{
    // MTProto::Functions::TLMessagesGetDocumentByHash &arguments = m_getDocumentByHash;
    if (processNotImplementedMethod(TLValue::MessagesGetDocumentByHash)) {
        return;
    }
    TLDocument result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetFavedStickers()
{
    // MTProto::Functions::TLMessagesGetFavedStickers &arguments = m_getFavedStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetFavedStickers)) {
        return;
    }
    TLMessagesFavedStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetFeaturedStickers()
{
    // MTProto::Functions::TLMessagesGetFeaturedStickers &arguments = m_getFeaturedStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetFeaturedStickers)) {
        return;
    }
    TLMessagesFeaturedStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetFullChat()
{
    MTProto::Functions::TLMessagesGetFullChat &arguments = m_getFullChat;
    LocalUser *selfUser = layer()->getUser();

    const GroupChat *groupChat = api()->getGroupChat(arguments.chatId);
    if (!groupChat) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    QSet<Peer> interestingPeers;
    TLMessagesChatFull result;
    interestingPeers.insert(Peer::fromUserId(groupChat->creatorId()));
    Utils::setupTLChatFull(&result.fullChat, groupChat, selfUser);
    Utils::getInterestingPeers(&interestingPeers, result.fullChat);
    Utils::setupTLPeers(&result, interestingPeers, api(), selfUser);

    sendRpcReply(result);
}

void MessagesRpcOperation::runGetGameHighScores()
{
    // MTProto::Functions::TLMessagesGetGameHighScores &arguments = m_getGameHighScores;
    if (processNotImplementedMethod(TLValue::MessagesGetGameHighScores)) {
        return;
    }
    TLMessagesHighScores result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetHistory()
{
    MTProto::Functions::TLMessagesGetHistory &arguments = m_getHistory;
    switch (arguments.peer.tlType) {
    case TLValue::InputPeerEmpty:
    case TLValue::InputPeerSelf:
    case TLValue::InputPeerUser:
    case TLValue::InputPeerChat:
        break;
    case TLValue::InputPeerChannel:
    default:
        qCritical() << Q_FUNC_INFO << "Not implemented for requested peer" << arguments.peer.tlType;
        processNotImplementedMethod(TLValue::MessagesGetHistory);
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    const LocalUser *selfUser = layer()->getUser();
    const Peer peer = api()->getPeer(arguments.peer, selfUser);
    const QHash<quint32,quint64> messageKeys = selfUser->getPostBox()->getAllMessageKeys();

    if (arguments.hash) {
        qCritical() << Q_FUNC_INFO << "Not implemented for requested arguments" << arguments.peer.tlType;
        processNotImplementedMethod(TLValue::MessagesGetHistory);
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    const int serverLimit = qMin<int>(c_serverHistorySliceLimit, messageKeys.count());
    int maxMessagesToAppend = arguments.limit
            ? qMin<int>(static_cast<int>(arguments.limit), serverLimit)
            : serverLimit;

    TLMessagesMessages result;
    result.messages.reserve(maxMessagesToAppend);

    // from inclusive messageId
    const quint32 fromMessageId = arguments.offsetId
            ? arguments.offsetId - 1
            : selfUser->getPostBox()->lastMessageId();

    // Iterate from newer messages (with bigger id) to older
    for (quint32 messageId = fromMessageId; (messageId != 0) && (maxMessagesToAppend > 0); --messageId) {
        if (arguments.minId) {
            if (messageId <= arguments.minId) {
                break;
            }
        }

        const quint64 globalMessageId = messageKeys.value(messageId);
        if (!globalMessageId) {
            // It's OK to have no message e.g. for deleted entires
            continue;
        }

        const MessageData *messageData = api()->messageService()->getMessage(globalMessageId);

        if (!messageData) {
            // It's OK to have no message e.g. for deleted entires
            continue;
        }

        if (arguments.offsetDate) {
            if (messageData->date() > arguments.offsetDate) {
                continue;
            }
        }

        if (peer.isValid()) {
            if (peer != messageData->getDialogPeer(selfUser->id())) {
                continue;
            }
        }

        if (arguments.addOffset > 0) {
            --arguments.addOffset;
            continue;
        }

        TLMessage message;
        Utils::setupTLMessage(&message, messageData, messageId, selfUser);

        --maxMessagesToAppend;

        if (arguments.maxId) {
            if (messageId >= arguments.maxId) {
                continue;
            }
        }

        result.messages.append(message);
    }

    QSet<Peer> interestingPeers;
    if (peer.isValid()) {
        interestingPeers.insert(peer);
    }
    Utils::getInterestingPeers(&interestingPeers, result.messages);
    Utils::setupTLPeers(&result, interestingPeers, api(), selfUser);
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetInlineBotResults()
{
    // MTProto::Functions::TLMessagesGetInlineBotResults &arguments = m_getInlineBotResults;
    if (processNotImplementedMethod(TLValue::MessagesGetInlineBotResults)) {
        return;
    }
    TLMessagesBotResults result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetInlineGameHighScores()
{
    // MTProto::Functions::TLMessagesGetInlineGameHighScores &arguments = m_getInlineGameHighScores;
    if (processNotImplementedMethod(TLValue::MessagesGetInlineGameHighScores)) {
        return;
    }
    TLMessagesHighScores result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetMaskStickers()
{
    // MTProto::Functions::TLMessagesGetMaskStickers &arguments = m_getMaskStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetMaskStickers)) {
        return;
    }
    TLMessagesAllStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetMessageEditData()
{
    // MTProto::Functions::TLMessagesGetMessageEditData &arguments = m_getMessageEditData;
    if (processNotImplementedMethod(TLValue::MessagesGetMessageEditData)) {
        return;
    }
    TLMessagesMessageEditData result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetMessages()
{
    // MTProto::Functions::TLMessagesGetMessages &arguments = m_getMessages;
    if (processNotImplementedMethod(TLValue::MessagesGetMessages)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetMessagesViews()
{
    // MTProto::Functions::TLMessagesGetMessagesViews &arguments = m_getMessagesViews;
    if (processNotImplementedMethod(TLValue::MessagesGetMessagesViews)) {
        return;
    }
    TLVector<quint32> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetOnlines()
{
    // MTProto::Functions::TLMessagesGetOnlines &arguments = m_getOnlines;
    if (processNotImplementedMethod(TLValue::MessagesGetOnlines)) {
        return;
    }
    TLChatOnlines result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetPeerDialogs()
{
    // MTProto::Functions::TLMessagesGetPeerDialogs &arguments = m_getPeerDialogs;
    if (processNotImplementedMethod(TLValue::MessagesGetPeerDialogs)) {
        return;
    }
    TLMessagesPeerDialogs result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetPeerSettings()
{
    // MTProto::Functions::TLMessagesGetPeerSettings &arguments = m_getPeerSettings;
    if (processNotImplementedMethod(TLValue::MessagesGetPeerSettings)) {
        return;
    }
    TLPeerSettings result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetPinnedDialogs()
{
    if (processNotImplementedMethod(TLValue::MessagesGetPinnedDialogs)) {
        return;
    }

    const LocalUser *selfUser = layer()->getUser();
    TLMessagesPeerDialogs result;
    Utils::setupTLUpdatesState(&result.state, selfUser);
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetPollResults()
{
    // MTProto::Functions::TLMessagesGetPollResults &arguments = m_getPollResults;
    if (processNotImplementedMethod(TLValue::MessagesGetPollResults)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetRecentLocations()
{
    // MTProto::Functions::TLMessagesGetRecentLocations &arguments = m_getRecentLocations;
    if (processNotImplementedMethod(TLValue::MessagesGetRecentLocations)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetRecentStickers()
{
    // MTProto::Functions::TLMessagesGetRecentStickers &arguments = m_getRecentStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetRecentStickers)) {
        return;
    }
    TLMessagesRecentStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetSavedGifs()
{
    // MTProto::Functions::TLMessagesGetSavedGifs &arguments = m_getSavedGifs;
    if (processNotImplementedMethod(TLValue::MessagesGetSavedGifs)) {
        return;
    }
    TLMessagesSavedGifs result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetSplitRanges()
{
    if (processNotImplementedMethod(TLValue::MessagesGetSplitRanges)) {
        return;
    }
    TLVector<TLMessageRange> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetStatsURL()
{
    // MTProto::Functions::TLMessagesGetStatsURL &arguments = m_getStatsURL;
    if (processNotImplementedMethod(TLValue::MessagesGetStatsURL)) {
        return;
    }
    TLStatsURL result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetStickerSet()
{
    // MTProto::Functions::TLMessagesGetStickerSet &arguments = m_getStickerSet;
    if (processNotImplementedMethod(TLValue::MessagesGetStickerSet)) {
        return;
    }
    TLMessagesStickerSet result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetStickers()
{
    // MTProto::Functions::TLMessagesGetStickers &arguments = m_getStickers;
    if (processNotImplementedMethod(TLValue::MessagesGetStickers)) {
        return;
    }
    TLMessagesStickers result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetUnreadMentions()
{
    // MTProto::Functions::TLMessagesGetUnreadMentions &arguments = m_getUnreadMentions;
    if (processNotImplementedMethod(TLValue::MessagesGetUnreadMentions)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetWebPage()
{
    // MTProto::Functions::TLMessagesGetWebPage &arguments = m_getWebPage;
    if (processNotImplementedMethod(TLValue::MessagesGetWebPage)) {
        return;
    }
    TLWebPage result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runGetWebPagePreview()
{
    // MTProto::Functions::TLMessagesGetWebPagePreview &arguments = m_getWebPagePreview;
    if (processNotImplementedMethod(TLValue::MessagesGetWebPagePreview)) {
        return;
    }
    TLMessageMedia result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runHideReportSpam()
{
    // MTProto::Functions::TLMessagesHideReportSpam &arguments = m_hideReportSpam;
    if (processNotImplementedMethod(TLValue::MessagesHideReportSpam)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runImportChatInvite()
{
    // MTProto::Functions::TLMessagesImportChatInvite &arguments = m_importChatInvite;
    if (processNotImplementedMethod(TLValue::MessagesImportChatInvite)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runInstallStickerSet()
{
    // MTProto::Functions::TLMessagesInstallStickerSet &arguments = m_installStickerSet;
    if (processNotImplementedMethod(TLValue::MessagesInstallStickerSet)) {
        return;
    }
    TLMessagesStickerSetInstallResult result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runMarkDialogUnread()
{
    // MTProto::Functions::TLMessagesMarkDialogUnread &arguments = m_markDialogUnread;
    if (processNotImplementedMethod(TLValue::MessagesMarkDialogUnread)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runMigrateChat()
{
    // MTProto::Functions::TLMessagesMigrateChat &arguments = m_migrateChat;
    if (processNotImplementedMethod(TLValue::MessagesMigrateChat)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReadEncryptedHistory()
{
    // MTProto::Functions::TLMessagesReadEncryptedHistory &arguments = m_readEncryptedHistory;
    if (processNotImplementedMethod(TLValue::MessagesReadEncryptedHistory)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReadFeaturedStickers()
{
    // MTProto::Functions::TLMessagesReadFeaturedStickers &arguments = m_readFeaturedStickers;
    if (processNotImplementedMethod(TLValue::MessagesReadFeaturedStickers)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReadHistory()
{
    MTProto::Functions::TLMessagesReadHistory &arguments = m_readHistory;

    LocalUser *selfUser = layer()->getUser();
    Telegram::Peer targetPeer = Telegram::Utils::toPublicPeer(arguments.peer, selfUser->id());
    if (targetPeer.type() == Peer::Channel) {
        // There is channels.readHistory for that
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    UserDialog *selfUserDialog = selfUser->getDialog(targetPeer);
    if (!selfUserDialog) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    const quint32 requestDate = Telegram::Utils::getCurrentTime();
    QVector<quint32> affectedMessages;
    quint32 maxId = qMax(selfUserDialog->topMessage, arguments.maxId);

    UserPostBox *selfUserPostBox = selfUser->getPostBox();
    const QHash<quint32,quint64> messageKeys = selfUserPostBox->getAllMessageKeys();

    for (quint32 messageId = maxId; messageId > selfUserDialog->readInboxMaxId; --messageId) {
        const quint64 globalMessageId = messageKeys.value(messageId);
        if (!globalMessageId) {
            // It's OK to have no message e.g. for deleted entires
            continue;
        }

        const MessageData *messageData = api()->messageService()->getMessage(globalMessageId);
        if (messageData->getDialogPeer(selfUser->id()) != targetPeer) {
            continue;
        }

        affectedMessages.append(messageId);
    }

    if (selfUserDialog->readInboxMaxId >= maxId) {
        TLMessagesAffectedMessages result;
        result.ptsCount = 0;
        result.pts = selfUser->getPostBox()->pts();
        sendRpcReply(result);
        return;
    }

    selfUserDialog->readInboxMaxId = maxId;
    const quint32 readCount = static_cast<quint32>(affectedMessages.count());
    if (selfUserDialog->unreadCount < readCount) {
        // TODO: Print warning (internal error)
        selfUserDialog->unreadCount = 0;
    } else {
        selfUserDialog->unreadCount -= readCount;
    }
    if (selfUserPostBox->unreadCount() < readCount) {
        // TODO: Print warning (internal error)
        selfUserPostBox->setUnreadCount(0);
    } else {
        selfUserPostBox->setUnreadCount(selfUserPostBox->unreadCount() - readCount);
    }

    selfUserPostBox->bumpPts();

    const quint64 globalMessageId = selfUser->getPostBox()->getMessageGlobalId(maxId);
    const MessageData *messageData = api()->messageService()->getMessage(globalMessageId);

    api()->reportMessageRead(messageData);

    TLMessagesAffectedMessages result;
    result.ptsCount = 1;
    result.pts = selfUser->getPostBox()->pts();
    sendRpcReply(result);

    if (selfUser->activeSessions().count() > 1) {
        UpdateNotification readNotification;
        readNotification.userId = selfUser->userId();
        readNotification.type = UpdateNotification::Type::ReadInbox;
        readNotification.date = requestDate;
        readNotification.pts = result.pts;
        readNotification.messageId = maxId;
        readNotification.dialogPeer = targetPeer;
        readNotification.excludeSession = layer()->session();
        api()->queueUpdates({readNotification});
    }
}

void MessagesRpcOperation::runReadMentions()
{
    // MTProto::Functions::TLMessagesReadMentions &arguments = m_readMentions;
    if (processNotImplementedMethod(TLValue::MessagesReadMentions)) {
        return;
    }
    TLMessagesAffectedHistory result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReadMessageContents()
{
    // MTProto::Functions::TLMessagesReadMessageContents &arguments = m_readMessageContents;
    if (processNotImplementedMethod(TLValue::MessagesReadMessageContents)) {
        return;
    }
    TLMessagesAffectedMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReceivedMessages()
{
    // MTProto::Functions::TLMessagesReceivedMessages &arguments = m_receivedMessages;
    if (processNotImplementedMethod(TLValue::MessagesReceivedMessages)) {
        return;
    }
    TLVector<TLReceivedNotifyMessage> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReceivedQueue()
{
    // MTProto::Functions::TLMessagesReceivedQueue &arguments = m_receivedQueue;
    if (processNotImplementedMethod(TLValue::MessagesReceivedQueue)) {
        return;
    }
    TLVector<quint64> result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReorderPinnedDialogs()
{
    // MTProto::Functions::TLMessagesReorderPinnedDialogs &arguments = m_reorderPinnedDialogs;
    if (processNotImplementedMethod(TLValue::MessagesReorderPinnedDialogs)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReorderStickerSets()
{
    // MTProto::Functions::TLMessagesReorderStickerSets &arguments = m_reorderStickerSets;
    if (processNotImplementedMethod(TLValue::MessagesReorderStickerSets)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReport()
{
    // MTProto::Functions::TLMessagesReport &arguments = m_report;
    if (processNotImplementedMethod(TLValue::MessagesReport)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReportEncryptedSpam()
{
    // MTProto::Functions::TLMessagesReportEncryptedSpam &arguments = m_reportEncryptedSpam;
    if (processNotImplementedMethod(TLValue::MessagesReportEncryptedSpam)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runReportSpam()
{
    // MTProto::Functions::TLMessagesReportSpam &arguments = m_reportSpam;
    if (processNotImplementedMethod(TLValue::MessagesReportSpam)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runRequestEncryption()
{
    // MTProto::Functions::TLMessagesRequestEncryption &arguments = m_requestEncryption;
    if (processNotImplementedMethod(TLValue::MessagesRequestEncryption)) {
        return;
    }
    TLEncryptedChat result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSaveDraft()
{
    // MTProto::Functions::TLMessagesSaveDraft &arguments = m_saveDraft;
    if (processNotImplementedMethod(TLValue::MessagesSaveDraft)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSaveGif()
{
    // MTProto::Functions::TLMessagesSaveGif &arguments = m_saveGif;
    if (processNotImplementedMethod(TLValue::MessagesSaveGif)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSaveRecentSticker()
{
    // MTProto::Functions::TLMessagesSaveRecentSticker &arguments = m_saveRecentSticker;
    if (processNotImplementedMethod(TLValue::MessagesSaveRecentSticker)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSearch()
{
    // MTProto::Functions::TLMessagesSearch &arguments = m_search;
    if (processNotImplementedMethod(TLValue::MessagesSearch)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSearchGifs()
{
    // MTProto::Functions::TLMessagesSearchGifs &arguments = m_searchGifs;
    if (processNotImplementedMethod(TLValue::MessagesSearchGifs)) {
        return;
    }
    TLMessagesFoundGifs result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSearchGlobal()
{
    // MTProto::Functions::TLMessagesSearchGlobal &arguments = m_searchGlobal;
    if (processNotImplementedMethod(TLValue::MessagesSearchGlobal)) {
        return;
    }
    TLMessagesMessages result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSearchStickerSets()
{
    // MTProto::Functions::TLMessagesSearchStickerSets &arguments = m_searchStickerSets;
    if (processNotImplementedMethod(TLValue::MessagesSearchStickerSets)) {
        return;
    }
    TLMessagesFoundStickerSets result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendEncrypted()
{
    // MTProto::Functions::TLMessagesSendEncrypted &arguments = m_sendEncrypted;
    if (processNotImplementedMethod(TLValue::MessagesSendEncrypted)) {
        return;
    }
    TLMessagesSentEncryptedMessage result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendEncryptedFile()
{
    // MTProto::Functions::TLMessagesSendEncryptedFile &arguments = m_sendEncryptedFile;
    if (processNotImplementedMethod(TLValue::MessagesSendEncryptedFile)) {
        return;
    }
    TLMessagesSentEncryptedMessage result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendEncryptedService()
{
    // MTProto::Functions::TLMessagesSendEncryptedService &arguments = m_sendEncryptedService;
    if (processNotImplementedMethod(TLValue::MessagesSendEncryptedService)) {
        return;
    }
    TLMessagesSentEncryptedMessage result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendInlineBotResult()
{
    // MTProto::Functions::TLMessagesSendInlineBotResult &arguments = m_sendInlineBotResult;
    if (processNotImplementedMethod(TLValue::MessagesSendInlineBotResult)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendMedia()
{
    MTProto::Functions::TLMessagesSendMedia &arguments = m_sendMedia;

    LocalUser *selfUser = layer()->getUser();
    MessageRecipient *recipient = api()->getRecipient(arguments.peer, selfUser);

    if (!recipient) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    MediaData media;

    switch (arguments.media.tlType) {
    case TLValue::InputMediaContact:
    {
        Telegram::Peer contactPeer = Telegram::Utils::toPublicPeer(arguments.peer, selfUser->id());
        if (!contactPeer.isValid() || (contactPeer.type() != Peer::User)) {
            sendRpcError(RpcError::PeerIdInvalid); // TODO: Check if the error is correct
            return;
        }

        media.type = MediaData::Contact;
        media.contact.phone = arguments.media.phoneNumber;
        media.contact.firstName = arguments.media.firstName;
        media.contact.lastName = arguments.media.lastName;
        media.contact.id = contactPeer.id();
        break;
    }
    case TLValue::InputMediaUploadedPhoto:
    {
        const TLInputFile &inFile = arguments.media.file;
        const UploadDescriptor upload = api()->mediaService()->getUploadedData(inFile.id);
        ImageDescriptor image = api()->mediaService()->processImageFile(upload, inFile.name);
        if (!image.isValid()) {
            sendRpcError(RpcError());
            return;
        }

        media.type = MediaData::Photo;
        media.caption = arguments.media.caption;
        media.image = image;
        break;
    }
    case TLValue::InputMediaUploadedDocument:
    {
        const TLInputFile &inFile = arguments.media.file;
        const UploadDescriptor upload = api()->mediaService()->getUploadedData(inFile.id);
        const FileDescriptor file = api()->mediaService()->saveDocumentFile(upload, inFile.name, arguments.media.mimeType);

        if (!file.isValid()) {
            sendRpcError(RpcError::UnknownReason);
            return;
        }

        media.type = MediaData::Document;
        media.file = file;
        media.mimeType = arguments.media.mimeType;
        media.caption = arguments.media.caption;
        for (const TLDocumentAttribute &attribute : arguments.media.attributes) {
            switch (attribute.tlType) {
            case TLValue::DocumentAttributeFilename:
                media.attributes.append(DocumentAttribute::fromFileName(attribute.fileName));
                break;
            default:
                break;
            }
        }
        break;
    }
    default:
        if (processNotImplementedMethod(TLValue::MessagesSendMedia)) {
            return;
        }
        break;
    }

    MessageData *messageData = api()->messageService()->addMessage(selfUser->id(), recipient->toPeer(), media);
    submitMessageData(messageData, arguments.randomId);
}

void MessagesRpcOperation::runSendMessage()
{
    MTProto::Functions::TLMessagesSendMessage &arguments = m_sendMessage;

    LocalUser *selfUser = layer()->getUser();
    Telegram::Peer targetPeer = api()->getPeer(arguments.peer, selfUser);
    MessageRecipient *recipient = api()->getRecipient(arguments.peer, selfUser);

    if (!recipient) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }
    MessageData *messageData = api()->messageService()->addMessage(selfUser->id(), targetPeer, arguments.message);

    submitMessageData(messageData, arguments.randomId);
}

void MessagesRpcOperation::runSendMultiMedia()
{
    // MTProto::Functions::TLMessagesSendMultiMedia &arguments = m_sendMultiMedia;
    if (processNotImplementedMethod(TLValue::MessagesSendMultiMedia)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendScreenshotNotification()
{
    // MTProto::Functions::TLMessagesSendScreenshotNotification &arguments = m_sendScreenshotNotification;
    if (processNotImplementedMethod(TLValue::MessagesSendScreenshotNotification)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSendVote()
{
    // MTProto::Functions::TLMessagesSendVote &arguments = m_sendVote;
    if (processNotImplementedMethod(TLValue::MessagesSendVote)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetBotCallbackAnswer()
{
    // MTProto::Functions::TLMessagesSetBotCallbackAnswer &arguments = m_setBotCallbackAnswer;
    if (processNotImplementedMethod(TLValue::MessagesSetBotCallbackAnswer)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetBotPrecheckoutResults()
{
    // MTProto::Functions::TLMessagesSetBotPrecheckoutResults &arguments = m_setBotPrecheckoutResults;
    if (processNotImplementedMethod(TLValue::MessagesSetBotPrecheckoutResults)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetBotShippingResults()
{
    // MTProto::Functions::TLMessagesSetBotShippingResults &arguments = m_setBotShippingResults;
    if (processNotImplementedMethod(TLValue::MessagesSetBotShippingResults)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetEncryptedTyping()
{
    // MTProto::Functions::TLMessagesSetEncryptedTyping &arguments = m_setEncryptedTyping;
    if (processNotImplementedMethod(TLValue::MessagesSetEncryptedTyping)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetGameScore()
{
    // MTProto::Functions::TLMessagesSetGameScore &arguments = m_setGameScore;
    if (processNotImplementedMethod(TLValue::MessagesSetGameScore)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetInlineBotResults()
{
    // MTProto::Functions::TLMessagesSetInlineBotResults &arguments = m_setInlineBotResults;
    if (processNotImplementedMethod(TLValue::MessagesSetInlineBotResults)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetInlineGameScore()
{
    // MTProto::Functions::TLMessagesSetInlineGameScore &arguments = m_setInlineGameScore;
    if (processNotImplementedMethod(TLValue::MessagesSetInlineGameScore)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runSetTyping()
{
    MTProto::Functions::TLMessagesSetTyping &arguments = m_setTyping;

    LocalUser *selfUser = layer()->getUser();
    Telegram::Peer targetPeer = Telegram::Utils::toPublicPeer(arguments.peer, selfUser->id());
    MessageRecipient *recipient = api()->getRecipient(arguments.peer, selfUser);

    if (!recipient) {
        sendRpcError(RpcError::PeerIdInvalid);
        return;
    }

    if (!arguments.action.isValid()) {
        // Invalid argument
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    const MessageAction action = Telegram::Utils::toPublic(arguments.action);
    api()->processUserMessageAction(targetPeer, selfUser, action, layer()->session());

    bool result = true;
    sendRpcReply(result);
}

void MessagesRpcOperation::runStartBot()
{
    // MTProto::Functions::TLMessagesStartBot &arguments = m_startBot;
    if (processNotImplementedMethod(TLValue::MessagesStartBot)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runToggleChatAdmins()
{
    // MTProto::Functions::TLMessagesToggleChatAdmins &arguments = m_toggleChatAdmins;
    if (processNotImplementedMethod(TLValue::MessagesToggleChatAdmins)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runToggleDialogPin()
{
    // MTProto::Functions::TLMessagesToggleDialogPin &arguments = m_toggleDialogPin;
    if (processNotImplementedMethod(TLValue::MessagesToggleDialogPin)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runUninstallStickerSet()
{
    // MTProto::Functions::TLMessagesUninstallStickerSet &arguments = m_uninstallStickerSet;
    if (processNotImplementedMethod(TLValue::MessagesUninstallStickerSet)) {
        return;
    }
    bool result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runUpdatePinnedMessage()
{
    // MTProto::Functions::TLMessagesUpdatePinnedMessage &arguments = m_updatePinnedMessage;
    if (processNotImplementedMethod(TLValue::MessagesUpdatePinnedMessage)) {
        return;
    }
    TLUpdates result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runUploadEncryptedFile()
{
    // MTProto::Functions::TLMessagesUploadEncryptedFile &arguments = m_uploadEncryptedFile;
    if (processNotImplementedMethod(TLValue::MessagesUploadEncryptedFile)) {
        return;
    }
    TLEncryptedFile result;
    sendRpcReply(result);
}

void MessagesRpcOperation::runUploadMedia()
{
    // MTProto::Functions::TLMessagesUploadMedia &arguments = m_uploadMedia;
    if (processNotImplementedMethod(TLValue::MessagesUploadMedia)) {
        return;
    }
    TLMessageMedia result;
    sendRpcReply(result);
}
// End of generated run methods

void MessagesRpcOperation::setRunMethod(MessagesRpcOperation::RunMethod method)
{
    m_runMethod = method;
}

void MessagesRpcOperation::submitMessageData(MessageData *messageData, quint64 randomId)
{
    if (!messageData) {
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    LocalUser *fromUser = layer()->getUser();

    Session *excludeSession = layer()->session();
    QVector<UpdateNotification> notifications = api()->processMessage(messageData, excludeSession);

    if (notifications.count() != 1) {
        qCritical() << "Unable to send a message";
        sendRpcError(RpcError::UnknownReason);
        return;
    }

    const UpdateNotification &newMessageNotification = notifications.constFirst();

    TLUpdate updateMessageId;
    updateMessageId.tlType = TLValue::UpdateMessageID;
    updateMessageId.quint32Id = newMessageNotification.messageId;
    updateMessageId.randomId = randomId;

    QSet<Peer> interestingPeers;
    TLUpdate newMessageUpdate;
    api()->bakeUpdate(&newMessageUpdate, newMessageNotification, &interestingPeers);

    // Bake updates
    TLUpdates result;
    result.tlType = TLValue::Updates;
    result.date = newMessageNotification.date;

    Utils::setupTLPeers(&result, interestingPeers, api(), fromUser);
    result.seq = 0; // Sender seq number seems to always equal zero
    result.updates = {
        updateMessageId,
        newMessageUpdate,
        // maybe UpdateReadChannelInbox or UpdateReadHistoryInbox
    };
    sendRpcReply(result);
}

MessagesRpcOperation::ProcessingMethod MessagesRpcOperation::getMethodForRpcFunction(TLValue function)
{
    switch (function) {
    // Generated methodForRpcFunction cases
    case TLValue::MessagesAcceptEncryption:
        return &MessagesRpcOperation::processAcceptEncryption;
    case TLValue::MessagesAddChatUser:
        return &MessagesRpcOperation::processAddChatUser;
    case TLValue::MessagesCheckChatInvite:
        return &MessagesRpcOperation::processCheckChatInvite;
    case TLValue::MessagesClearAllDrafts:
        return &MessagesRpcOperation::processClearAllDrafts;
    case TLValue::MessagesClearRecentStickers:
        return &MessagesRpcOperation::processClearRecentStickers;
    case TLValue::MessagesCreateChat:
        return &MessagesRpcOperation::processCreateChat;
    case TLValue::MessagesDeleteChatUser:
        return &MessagesRpcOperation::processDeleteChatUser;
    case TLValue::MessagesDeleteHistory:
        return &MessagesRpcOperation::processDeleteHistory;
    case TLValue::MessagesDeleteMessages:
        return &MessagesRpcOperation::processDeleteMessages;
    case TLValue::MessagesDiscardEncryption:
        return &MessagesRpcOperation::processDiscardEncryption;
    case TLValue::MessagesEditChatAdmin:
        return &MessagesRpcOperation::processEditChatAdmin;
    case TLValue::MessagesEditChatPhoto:
        return &MessagesRpcOperation::processEditChatPhoto;
    case TLValue::MessagesEditChatTitle:
        return &MessagesRpcOperation::processEditChatTitle;
    case TLValue::MessagesEditInlineBotMessage:
        return &MessagesRpcOperation::processEditInlineBotMessage;
    case TLValue::MessagesEditMessage:
        return &MessagesRpcOperation::processEditMessage;
    case TLValue::MessagesExportChatInvite:
        return &MessagesRpcOperation::processExportChatInvite;
    case TLValue::MessagesFaveSticker:
        return &MessagesRpcOperation::processFaveSticker;
    case TLValue::MessagesForwardMessages:
        return &MessagesRpcOperation::processForwardMessages;
    case TLValue::MessagesGetAllChats:
        return &MessagesRpcOperation::processGetAllChats;
    case TLValue::MessagesGetAllDrafts:
        return &MessagesRpcOperation::processGetAllDrafts;
    case TLValue::MessagesGetAllStickers:
        return &MessagesRpcOperation::processGetAllStickers;
    case TLValue::MessagesGetArchivedStickers:
        return &MessagesRpcOperation::processGetArchivedStickers;
    case TLValue::MessagesGetAttachedStickers:
        return &MessagesRpcOperation::processGetAttachedStickers;
    case TLValue::MessagesGetBotCallbackAnswer:
        return &MessagesRpcOperation::processGetBotCallbackAnswer;
    case TLValue::MessagesGetChats:
        return &MessagesRpcOperation::processGetChats;
    case TLValue::MessagesGetCommonChats:
        return &MessagesRpcOperation::processGetCommonChats;
    case TLValue::MessagesGetDhConfig:
        return &MessagesRpcOperation::processGetDhConfig;
    case TLValue::MessagesGetDialogUnreadMarks:
        return &MessagesRpcOperation::processGetDialogUnreadMarks;
    case TLValue::MessagesGetDialogs:
        return &MessagesRpcOperation::processGetDialogs;
    case TLValue::MessagesGetDocumentByHash:
        return &MessagesRpcOperation::processGetDocumentByHash;
    case TLValue::MessagesGetFavedStickers:
        return &MessagesRpcOperation::processGetFavedStickers;
    case TLValue::MessagesGetFeaturedStickers:
        return &MessagesRpcOperation::processGetFeaturedStickers;
    case TLValue::MessagesGetFullChat:
        return &MessagesRpcOperation::processGetFullChat;
    case TLValue::MessagesGetGameHighScores:
        return &MessagesRpcOperation::processGetGameHighScores;
    case TLValue::MessagesGetHistory:
        return &MessagesRpcOperation::processGetHistory;
    case TLValue::MessagesGetInlineBotResults:
        return &MessagesRpcOperation::processGetInlineBotResults;
    case TLValue::MessagesGetInlineGameHighScores:
        return &MessagesRpcOperation::processGetInlineGameHighScores;
    case TLValue::MessagesGetMaskStickers:
        return &MessagesRpcOperation::processGetMaskStickers;
    case TLValue::MessagesGetMessageEditData:
        return &MessagesRpcOperation::processGetMessageEditData;
    case TLValue::MessagesGetMessages:
        return &MessagesRpcOperation::processGetMessages;
    case TLValue::MessagesGetMessagesViews:
        return &MessagesRpcOperation::processGetMessagesViews;
    case TLValue::MessagesGetOnlines:
        return &MessagesRpcOperation::processGetOnlines;
    case TLValue::MessagesGetPeerDialogs:
        return &MessagesRpcOperation::processGetPeerDialogs;
    case TLValue::MessagesGetPeerSettings:
        return &MessagesRpcOperation::processGetPeerSettings;
    case TLValue::MessagesGetPinnedDialogs:
        return &MessagesRpcOperation::processGetPinnedDialogs;
    case TLValue::MessagesGetPollResults:
        return &MessagesRpcOperation::processGetPollResults;
    case TLValue::MessagesGetRecentLocations:
        return &MessagesRpcOperation::processGetRecentLocations;
    case TLValue::MessagesGetRecentStickers:
        return &MessagesRpcOperation::processGetRecentStickers;
    case TLValue::MessagesGetSavedGifs:
        return &MessagesRpcOperation::processGetSavedGifs;
    case TLValue::MessagesGetSplitRanges:
        return &MessagesRpcOperation::processGetSplitRanges;
    case TLValue::MessagesGetStatsURL:
        return &MessagesRpcOperation::processGetStatsURL;
    case TLValue::MessagesGetStickerSet:
        return &MessagesRpcOperation::processGetStickerSet;
    case TLValue::MessagesGetStickers:
        return &MessagesRpcOperation::processGetStickers;
    case TLValue::MessagesGetUnreadMentions:
        return &MessagesRpcOperation::processGetUnreadMentions;
    case TLValue::MessagesGetWebPage:
        return &MessagesRpcOperation::processGetWebPage;
    case TLValue::MessagesGetWebPagePreview:
        return &MessagesRpcOperation::processGetWebPagePreview;
    case TLValue::MessagesHideReportSpam:
        return &MessagesRpcOperation::processHideReportSpam;
    case TLValue::MessagesImportChatInvite:
        return &MessagesRpcOperation::processImportChatInvite;
    case TLValue::MessagesInstallStickerSet:
        return &MessagesRpcOperation::processInstallStickerSet;
    case TLValue::MessagesMarkDialogUnread:
        return &MessagesRpcOperation::processMarkDialogUnread;
    case TLValue::MessagesMigrateChat:
        return &MessagesRpcOperation::processMigrateChat;
    case TLValue::MessagesReadEncryptedHistory:
        return &MessagesRpcOperation::processReadEncryptedHistory;
    case TLValue::MessagesReadFeaturedStickers:
        return &MessagesRpcOperation::processReadFeaturedStickers;
    case TLValue::MessagesReadHistory:
        return &MessagesRpcOperation::processReadHistory;
    case TLValue::MessagesReadMentions:
        return &MessagesRpcOperation::processReadMentions;
    case TLValue::MessagesReadMessageContents:
        return &MessagesRpcOperation::processReadMessageContents;
    case TLValue::MessagesReceivedMessages:
        return &MessagesRpcOperation::processReceivedMessages;
    case TLValue::MessagesReceivedQueue:
        return &MessagesRpcOperation::processReceivedQueue;
    case TLValue::MessagesReorderPinnedDialogs:
        return &MessagesRpcOperation::processReorderPinnedDialogs;
    case TLValue::MessagesReorderStickerSets:
        return &MessagesRpcOperation::processReorderStickerSets;
    case TLValue::MessagesReport:
        return &MessagesRpcOperation::processReport;
    case TLValue::MessagesReportEncryptedSpam:
        return &MessagesRpcOperation::processReportEncryptedSpam;
    case TLValue::MessagesReportSpam:
        return &MessagesRpcOperation::processReportSpam;
    case TLValue::MessagesRequestEncryption:
        return &MessagesRpcOperation::processRequestEncryption;
    case TLValue::MessagesSaveDraft:
        return &MessagesRpcOperation::processSaveDraft;
    case TLValue::MessagesSaveGif:
        return &MessagesRpcOperation::processSaveGif;
    case TLValue::MessagesSaveRecentSticker:
        return &MessagesRpcOperation::processSaveRecentSticker;
    case TLValue::MessagesSearch:
        return &MessagesRpcOperation::processSearch;
    case TLValue::MessagesSearchGifs:
        return &MessagesRpcOperation::processSearchGifs;
    case TLValue::MessagesSearchGlobal:
        return &MessagesRpcOperation::processSearchGlobal;
    case TLValue::MessagesSearchStickerSets:
        return &MessagesRpcOperation::processSearchStickerSets;
    case TLValue::MessagesSendEncrypted:
        return &MessagesRpcOperation::processSendEncrypted;
    case TLValue::MessagesSendEncryptedFile:
        return &MessagesRpcOperation::processSendEncryptedFile;
    case TLValue::MessagesSendEncryptedService:
        return &MessagesRpcOperation::processSendEncryptedService;
    case TLValue::MessagesSendInlineBotResult:
        return &MessagesRpcOperation::processSendInlineBotResult;
    case TLValue::MessagesSendMedia:
        return &MessagesRpcOperation::processSendMedia;
    case TLValue::MessagesSendMessage:
        return &MessagesRpcOperation::processSendMessage;
    case TLValue::MessagesSendMultiMedia:
        return &MessagesRpcOperation::processSendMultiMedia;
    case TLValue::MessagesSendScreenshotNotification:
        return &MessagesRpcOperation::processSendScreenshotNotification;
    case TLValue::MessagesSendVote:
        return &MessagesRpcOperation::processSendVote;
    case TLValue::MessagesSetBotCallbackAnswer:
        return &MessagesRpcOperation::processSetBotCallbackAnswer;
    case TLValue::MessagesSetBotPrecheckoutResults:
        return &MessagesRpcOperation::processSetBotPrecheckoutResults;
    case TLValue::MessagesSetBotShippingResults:
        return &MessagesRpcOperation::processSetBotShippingResults;
    case TLValue::MessagesSetEncryptedTyping:
        return &MessagesRpcOperation::processSetEncryptedTyping;
    case TLValue::MessagesSetGameScore:
        return &MessagesRpcOperation::processSetGameScore;
    case TLValue::MessagesSetInlineBotResults:
        return &MessagesRpcOperation::processSetInlineBotResults;
    case TLValue::MessagesSetInlineGameScore:
        return &MessagesRpcOperation::processSetInlineGameScore;
    case TLValue::MessagesSetTyping:
        return &MessagesRpcOperation::processSetTyping;
    case TLValue::MessagesStartBot:
        return &MessagesRpcOperation::processStartBot;
    case TLValue::MessagesToggleChatAdmins:
        return &MessagesRpcOperation::processToggleChatAdmins;
    case TLValue::MessagesToggleDialogPin:
        return &MessagesRpcOperation::processToggleDialogPin;
    case TLValue::MessagesUninstallStickerSet:
        return &MessagesRpcOperation::processUninstallStickerSet;
    case TLValue::MessagesUpdatePinnedMessage:
        return &MessagesRpcOperation::processUpdatePinnedMessage;
    case TLValue::MessagesUploadEncryptedFile:
        return &MessagesRpcOperation::processUploadEncryptedFile;
    case TLValue::MessagesUploadMedia:
        return &MessagesRpcOperation::processUploadMedia;
    // End of generated methodForRpcFunction cases
    default:
        return nullptr;
    }
}

RpcOperation *MessagesOperationFactory::processRpcCall(RpcLayer *layer, RpcProcessingContext &context)
{
    return processRpcCallImpl<MessagesRpcOperation>(layer, context);
}

} // Server namespace

} // Telegram namespace
