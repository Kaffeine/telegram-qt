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

#ifndef MESSAGES_OPERATION_FACTORY_HPP
#define MESSAGES_OPERATION_FACTORY_HPP

#include "RpcOperationFactory.hpp"
#include "ServerRpcOperation.hpp"

#include <QObject>

namespace Telegram {

namespace Server {

class MessageData;

class MessagesRpcOperation : public RpcOperation
{
    Q_OBJECT
    Q_DISABLE_COPY(MessagesRpcOperation)
public:
    explicit MessagesRpcOperation(RpcLayer *rpcLayer) : RpcOperation(rpcLayer) { }

    // Generated process methods
    bool processAcceptEncryption(RpcProcessingContext &context);
    bool processAddChatUser(RpcProcessingContext &context);
    bool processCheckChatInvite(RpcProcessingContext &context);
    bool processClearAllDrafts(RpcProcessingContext &context);
    bool processClearRecentStickers(RpcProcessingContext &context);
    bool processCreateChat(RpcProcessingContext &context);
    bool processDeleteChatUser(RpcProcessingContext &context);
    bool processDeleteHistory(RpcProcessingContext &context);
    bool processDeleteMessages(RpcProcessingContext &context);
    bool processDiscardEncryption(RpcProcessingContext &context);
    bool processEditChatAdmin(RpcProcessingContext &context);
    bool processEditChatPhoto(RpcProcessingContext &context);
    bool processEditChatTitle(RpcProcessingContext &context);
    bool processEditInlineBotMessage(RpcProcessingContext &context);
    bool processEditMessage(RpcProcessingContext &context);
    bool processExportChatInvite(RpcProcessingContext &context);
    bool processFaveSticker(RpcProcessingContext &context);
    bool processForwardMessages(RpcProcessingContext &context);
    bool processGetAllChats(RpcProcessingContext &context);
    bool processGetAllDrafts(RpcProcessingContext &context);
    bool processGetAllStickers(RpcProcessingContext &context);
    bool processGetArchivedStickers(RpcProcessingContext &context);
    bool processGetAttachedStickers(RpcProcessingContext &context);
    bool processGetBotCallbackAnswer(RpcProcessingContext &context);
    bool processGetChats(RpcProcessingContext &context);
    bool processGetCommonChats(RpcProcessingContext &context);
    bool processGetDhConfig(RpcProcessingContext &context);
    bool processGetDialogUnreadMarks(RpcProcessingContext &context);
    bool processGetDialogs(RpcProcessingContext &context);
    bool processGetDocumentByHash(RpcProcessingContext &context);
    bool processGetFavedStickers(RpcProcessingContext &context);
    bool processGetFeaturedStickers(RpcProcessingContext &context);
    bool processGetFullChat(RpcProcessingContext &context);
    bool processGetGameHighScores(RpcProcessingContext &context);
    bool processGetHistory(RpcProcessingContext &context);
    bool processGetInlineBotResults(RpcProcessingContext &context);
    bool processGetInlineGameHighScores(RpcProcessingContext &context);
    bool processGetMaskStickers(RpcProcessingContext &context);
    bool processGetMessageEditData(RpcProcessingContext &context);
    bool processGetMessages(RpcProcessingContext &context);
    bool processGetMessagesViews(RpcProcessingContext &context);
    bool processGetOnlines(RpcProcessingContext &context);
    bool processGetPeerDialogs(RpcProcessingContext &context);
    bool processGetPeerSettings(RpcProcessingContext &context);
    bool processGetPinnedDialogs(RpcProcessingContext &context);
    bool processGetPollResults(RpcProcessingContext &context);
    bool processGetRecentLocations(RpcProcessingContext &context);
    bool processGetRecentStickers(RpcProcessingContext &context);
    bool processGetSavedGifs(RpcProcessingContext &context);
    bool processGetSplitRanges(RpcProcessingContext &context);
    bool processGetStatsURL(RpcProcessingContext &context);
    bool processGetStickerSet(RpcProcessingContext &context);
    bool processGetStickers(RpcProcessingContext &context);
    bool processGetUnreadMentions(RpcProcessingContext &context);
    bool processGetWebPage(RpcProcessingContext &context);
    bool processGetWebPagePreview(RpcProcessingContext &context);
    bool processHideReportSpam(RpcProcessingContext &context);
    bool processImportChatInvite(RpcProcessingContext &context);
    bool processInstallStickerSet(RpcProcessingContext &context);
    bool processMarkDialogUnread(RpcProcessingContext &context);
    bool processMigrateChat(RpcProcessingContext &context);
    bool processReadEncryptedHistory(RpcProcessingContext &context);
    bool processReadFeaturedStickers(RpcProcessingContext &context);
    bool processReadHistory(RpcProcessingContext &context);
    bool processReadMentions(RpcProcessingContext &context);
    bool processReadMessageContents(RpcProcessingContext &context);
    bool processReceivedMessages(RpcProcessingContext &context);
    bool processReceivedQueue(RpcProcessingContext &context);
    bool processReorderPinnedDialogs(RpcProcessingContext &context);
    bool processReorderStickerSets(RpcProcessingContext &context);
    bool processReport(RpcProcessingContext &context);
    bool processReportEncryptedSpam(RpcProcessingContext &context);
    bool processReportSpam(RpcProcessingContext &context);
    bool processRequestEncryption(RpcProcessingContext &context);
    bool processSaveDraft(RpcProcessingContext &context);
    bool processSaveGif(RpcProcessingContext &context);
    bool processSaveRecentSticker(RpcProcessingContext &context);
    bool processSearch(RpcProcessingContext &context);
    bool processSearchGifs(RpcProcessingContext &context);
    bool processSearchGlobal(RpcProcessingContext &context);
    bool processSearchStickerSets(RpcProcessingContext &context);
    bool processSendEncrypted(RpcProcessingContext &context);
    bool processSendEncryptedFile(RpcProcessingContext &context);
    bool processSendEncryptedService(RpcProcessingContext &context);
    bool processSendInlineBotResult(RpcProcessingContext &context);
    bool processSendMedia(RpcProcessingContext &context);
    bool processSendMessage(RpcProcessingContext &context);
    bool processSendMultiMedia(RpcProcessingContext &context);
    bool processSendScreenshotNotification(RpcProcessingContext &context);
    bool processSendVote(RpcProcessingContext &context);
    bool processSetBotCallbackAnswer(RpcProcessingContext &context);
    bool processSetBotPrecheckoutResults(RpcProcessingContext &context);
    bool processSetBotShippingResults(RpcProcessingContext &context);
    bool processSetEncryptedTyping(RpcProcessingContext &context);
    bool processSetGameScore(RpcProcessingContext &context);
    bool processSetInlineBotResults(RpcProcessingContext &context);
    bool processSetInlineGameScore(RpcProcessingContext &context);
    bool processSetTyping(RpcProcessingContext &context);
    bool processStartBot(RpcProcessingContext &context);
    bool processToggleChatAdmins(RpcProcessingContext &context);
    bool processToggleDialogPin(RpcProcessingContext &context);
    bool processUninstallStickerSet(RpcProcessingContext &context);
    bool processUpdatePinnedMessage(RpcProcessingContext &context);
    bool processUploadEncryptedFile(RpcProcessingContext &context);
    bool processUploadMedia(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAcceptEncryption();
    void runAddChatUser();
    void runCheckChatInvite();
    void runClearAllDrafts();
    void runClearRecentStickers();
    void runCreateChat();
    void runDeleteChatUser();
    void runDeleteHistory();
    void runDeleteMessages();
    void runDiscardEncryption();
    void runEditChatAdmin();
    void runEditChatPhoto();
    void runEditChatTitle();
    void runEditInlineBotMessage();
    void runEditMessage();
    void runExportChatInvite();
    void runFaveSticker();
    void runForwardMessages();
    void runGetAllChats();
    void runGetAllDrafts();
    void runGetAllStickers();
    void runGetArchivedStickers();
    void runGetAttachedStickers();
    void runGetBotCallbackAnswer();
    void runGetChats();
    void runGetCommonChats();
    void runGetDhConfig();
    void runGetDialogUnreadMarks();
    void runGetDialogs();
    void runGetDocumentByHash();
    void runGetFavedStickers();
    void runGetFeaturedStickers();
    void runGetFullChat();
    void runGetGameHighScores();
    void runGetHistory();
    void runGetInlineBotResults();
    void runGetInlineGameHighScores();
    void runGetMaskStickers();
    void runGetMessageEditData();
    void runGetMessages();
    void runGetMessagesViews();
    void runGetOnlines();
    void runGetPeerDialogs();
    void runGetPeerSettings();
    void runGetPinnedDialogs();
    void runGetPollResults();
    void runGetRecentLocations();
    void runGetRecentStickers();
    void runGetSavedGifs();
    void runGetSplitRanges();
    void runGetStatsURL();
    void runGetStickerSet();
    void runGetStickers();
    void runGetUnreadMentions();
    void runGetWebPage();
    void runGetWebPagePreview();
    void runHideReportSpam();
    void runImportChatInvite();
    void runInstallStickerSet();
    void runMarkDialogUnread();
    void runMigrateChat();
    void runReadEncryptedHistory();
    void runReadFeaturedStickers();
    void runReadHistory();
    void runReadMentions();
    void runReadMessageContents();
    void runReceivedMessages();
    void runReceivedQueue();
    void runReorderPinnedDialogs();
    void runReorderStickerSets();
    void runReport();
    void runReportEncryptedSpam();
    void runReportSpam();
    void runRequestEncryption();
    void runSaveDraft();
    void runSaveGif();
    void runSaveRecentSticker();
    void runSearch();
    void runSearchGifs();
    void runSearchGlobal();
    void runSearchStickerSets();
    void runSendEncrypted();
    void runSendEncryptedFile();
    void runSendEncryptedService();
    void runSendInlineBotResult();
    void runSendMedia();
    void runSendMessage();
    void runSendMultiMedia();
    void runSendScreenshotNotification();
    void runSendVote();
    void runSetBotCallbackAnswer();
    void runSetBotPrecheckoutResults();
    void runSetBotShippingResults();
    void runSetEncryptedTyping();
    void runSetGameScore();
    void runSetInlineBotResults();
    void runSetInlineGameScore();
    void runSetTyping();
    void runStartBot();
    void runToggleChatAdmins();
    void runToggleDialogPin();
    void runUninstallStickerSet();
    void runUpdatePinnedMessage();
    void runUploadEncryptedFile();
    void runUploadMedia();
    // End of generated run methods

    using RunMethod = void (MessagesRpcOperation::*)();
    using ProcessingMethod = bool (MessagesRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    void editMessageData(MessageData *messageData, quint64 randomId);
    void submitMessageData(MessageData *messageData, quint64 randomId);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    MTProto::Functions::TLMessagesAcceptEncryption m_acceptEncryption;
    MTProto::Functions::TLMessagesAddChatUser m_addChatUser;
    MTProto::Functions::TLMessagesCheckChatInvite m_checkChatInvite;
    MTProto::Functions::TLMessagesClearAllDrafts m_clearAllDrafts;
    MTProto::Functions::TLMessagesClearRecentStickers m_clearRecentStickers;
    MTProto::Functions::TLMessagesCreateChat m_createChat;
    MTProto::Functions::TLMessagesDeleteChatUser m_deleteChatUser;
    MTProto::Functions::TLMessagesDeleteHistory m_deleteHistory;
    MTProto::Functions::TLMessagesDeleteMessages m_deleteMessages;
    MTProto::Functions::TLMessagesDiscardEncryption m_discardEncryption;
    MTProto::Functions::TLMessagesEditChatAdmin m_editChatAdmin;
    MTProto::Functions::TLMessagesEditChatPhoto m_editChatPhoto;
    MTProto::Functions::TLMessagesEditChatTitle m_editChatTitle;
    MTProto::Functions::TLMessagesEditInlineBotMessage m_editInlineBotMessage;
    MTProto::Functions::TLMessagesEditMessage m_editMessage;
    MTProto::Functions::TLMessagesExportChatInvite m_exportChatInvite;
    MTProto::Functions::TLMessagesFaveSticker m_faveSticker;
    MTProto::Functions::TLMessagesForwardMessages m_forwardMessages;
    MTProto::Functions::TLMessagesGetAllChats m_getAllChats;
    MTProto::Functions::TLMessagesGetAllDrafts m_getAllDrafts;
    MTProto::Functions::TLMessagesGetAllStickers m_getAllStickers;
    MTProto::Functions::TLMessagesGetArchivedStickers m_getArchivedStickers;
    MTProto::Functions::TLMessagesGetAttachedStickers m_getAttachedStickers;
    MTProto::Functions::TLMessagesGetBotCallbackAnswer m_getBotCallbackAnswer;
    MTProto::Functions::TLMessagesGetChats m_getChats;
    MTProto::Functions::TLMessagesGetCommonChats m_getCommonChats;
    MTProto::Functions::TLMessagesGetDhConfig m_getDhConfig;
    MTProto::Functions::TLMessagesGetDialogUnreadMarks m_getDialogUnreadMarks;
    MTProto::Functions::TLMessagesGetDialogs m_getDialogs;
    MTProto::Functions::TLMessagesGetDocumentByHash m_getDocumentByHash;
    MTProto::Functions::TLMessagesGetFavedStickers m_getFavedStickers;
    MTProto::Functions::TLMessagesGetFeaturedStickers m_getFeaturedStickers;
    MTProto::Functions::TLMessagesGetFullChat m_getFullChat;
    MTProto::Functions::TLMessagesGetGameHighScores m_getGameHighScores;
    MTProto::Functions::TLMessagesGetHistory m_getHistory;
    MTProto::Functions::TLMessagesGetInlineBotResults m_getInlineBotResults;
    MTProto::Functions::TLMessagesGetInlineGameHighScores m_getInlineGameHighScores;
    MTProto::Functions::TLMessagesGetMaskStickers m_getMaskStickers;
    MTProto::Functions::TLMessagesGetMessageEditData m_getMessageEditData;
    MTProto::Functions::TLMessagesGetMessages m_getMessages;
    MTProto::Functions::TLMessagesGetMessagesViews m_getMessagesViews;
    MTProto::Functions::TLMessagesGetOnlines m_getOnlines;
    MTProto::Functions::TLMessagesGetPeerDialogs m_getPeerDialogs;
    MTProto::Functions::TLMessagesGetPeerSettings m_getPeerSettings;
    MTProto::Functions::TLMessagesGetPinnedDialogs m_getPinnedDialogs;
    MTProto::Functions::TLMessagesGetPollResults m_getPollResults;
    MTProto::Functions::TLMessagesGetRecentLocations m_getRecentLocations;
    MTProto::Functions::TLMessagesGetRecentStickers m_getRecentStickers;
    MTProto::Functions::TLMessagesGetSavedGifs m_getSavedGifs;
    MTProto::Functions::TLMessagesGetSplitRanges m_getSplitRanges;
    MTProto::Functions::TLMessagesGetStatsURL m_getStatsURL;
    MTProto::Functions::TLMessagesGetStickerSet m_getStickerSet;
    MTProto::Functions::TLMessagesGetStickers m_getStickers;
    MTProto::Functions::TLMessagesGetUnreadMentions m_getUnreadMentions;
    MTProto::Functions::TLMessagesGetWebPage m_getWebPage;
    MTProto::Functions::TLMessagesGetWebPagePreview m_getWebPagePreview;
    MTProto::Functions::TLMessagesHideReportSpam m_hideReportSpam;
    MTProto::Functions::TLMessagesImportChatInvite m_importChatInvite;
    MTProto::Functions::TLMessagesInstallStickerSet m_installStickerSet;
    MTProto::Functions::TLMessagesMarkDialogUnread m_markDialogUnread;
    MTProto::Functions::TLMessagesMigrateChat m_migrateChat;
    MTProto::Functions::TLMessagesReadEncryptedHistory m_readEncryptedHistory;
    MTProto::Functions::TLMessagesReadFeaturedStickers m_readFeaturedStickers;
    MTProto::Functions::TLMessagesReadHistory m_readHistory;
    MTProto::Functions::TLMessagesReadMentions m_readMentions;
    MTProto::Functions::TLMessagesReadMessageContents m_readMessageContents;
    MTProto::Functions::TLMessagesReceivedMessages m_receivedMessages;
    MTProto::Functions::TLMessagesReceivedQueue m_receivedQueue;
    MTProto::Functions::TLMessagesReorderPinnedDialogs m_reorderPinnedDialogs;
    MTProto::Functions::TLMessagesReorderStickerSets m_reorderStickerSets;
    MTProto::Functions::TLMessagesReport m_report;
    MTProto::Functions::TLMessagesReportEncryptedSpam m_reportEncryptedSpam;
    MTProto::Functions::TLMessagesReportSpam m_reportSpam;
    MTProto::Functions::TLMessagesRequestEncryption m_requestEncryption;
    MTProto::Functions::TLMessagesSaveDraft m_saveDraft;
    MTProto::Functions::TLMessagesSaveGif m_saveGif;
    MTProto::Functions::TLMessagesSaveRecentSticker m_saveRecentSticker;
    MTProto::Functions::TLMessagesSearch m_search;
    MTProto::Functions::TLMessagesSearchGifs m_searchGifs;
    MTProto::Functions::TLMessagesSearchGlobal m_searchGlobal;
    MTProto::Functions::TLMessagesSearchStickerSets m_searchStickerSets;
    MTProto::Functions::TLMessagesSendEncrypted m_sendEncrypted;
    MTProto::Functions::TLMessagesSendEncryptedFile m_sendEncryptedFile;
    MTProto::Functions::TLMessagesSendEncryptedService m_sendEncryptedService;
    MTProto::Functions::TLMessagesSendInlineBotResult m_sendInlineBotResult;
    MTProto::Functions::TLMessagesSendMedia m_sendMedia;
    MTProto::Functions::TLMessagesSendMessage m_sendMessage;
    MTProto::Functions::TLMessagesSendMultiMedia m_sendMultiMedia;
    MTProto::Functions::TLMessagesSendScreenshotNotification m_sendScreenshotNotification;
    MTProto::Functions::TLMessagesSendVote m_sendVote;
    MTProto::Functions::TLMessagesSetBotCallbackAnswer m_setBotCallbackAnswer;
    MTProto::Functions::TLMessagesSetBotPrecheckoutResults m_setBotPrecheckoutResults;
    MTProto::Functions::TLMessagesSetBotShippingResults m_setBotShippingResults;
    MTProto::Functions::TLMessagesSetEncryptedTyping m_setEncryptedTyping;
    MTProto::Functions::TLMessagesSetGameScore m_setGameScore;
    MTProto::Functions::TLMessagesSetInlineBotResults m_setInlineBotResults;
    MTProto::Functions::TLMessagesSetInlineGameScore m_setInlineGameScore;
    MTProto::Functions::TLMessagesSetTyping m_setTyping;
    MTProto::Functions::TLMessagesStartBot m_startBot;
    MTProto::Functions::TLMessagesToggleChatAdmins m_toggleChatAdmins;
    MTProto::Functions::TLMessagesToggleDialogPin m_toggleDialogPin;
    MTProto::Functions::TLMessagesUninstallStickerSet m_uninstallStickerSet;
    MTProto::Functions::TLMessagesUpdatePinnedMessage m_updatePinnedMessage;
    MTProto::Functions::TLMessagesUploadEncryptedFile m_uploadEncryptedFile;
    MTProto::Functions::TLMessagesUploadMedia m_uploadMedia;
    // End of generated RPC members
};

class MessagesOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server namespace

} // Telegram namespace

#endif // MESSAGES_OPERATION_FACTORY_HPP
