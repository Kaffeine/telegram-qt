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
    bool processForwardMessage(RpcProcessingContext &context);
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
    bool processGetPeerDialogs(RpcProcessingContext &context);
    bool processGetPeerSettings(RpcProcessingContext &context);
    bool processGetPinnedDialogs(RpcProcessingContext &context);
    bool processGetRecentLocations(RpcProcessingContext &context);
    bool processGetRecentStickers(RpcProcessingContext &context);
    bool processGetSavedGifs(RpcProcessingContext &context);
    bool processGetStickerSet(RpcProcessingContext &context);
    bool processGetUnreadMentions(RpcProcessingContext &context);
    bool processGetWebPage(RpcProcessingContext &context);
    bool processGetWebPagePreview(RpcProcessingContext &context);
    bool processHideReportSpam(RpcProcessingContext &context);
    bool processImportChatInvite(RpcProcessingContext &context);
    bool processInstallStickerSet(RpcProcessingContext &context);
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
    bool processReportEncryptedSpam(RpcProcessingContext &context);
    bool processReportSpam(RpcProcessingContext &context);
    bool processRequestEncryption(RpcProcessingContext &context);
    bool processSaveDraft(RpcProcessingContext &context);
    bool processSaveGif(RpcProcessingContext &context);
    bool processSaveRecentSticker(RpcProcessingContext &context);
    bool processSearch(RpcProcessingContext &context);
    bool processSearchGifs(RpcProcessingContext &context);
    bool processSearchGlobal(RpcProcessingContext &context);
    bool processSendEncrypted(RpcProcessingContext &context);
    bool processSendEncryptedFile(RpcProcessingContext &context);
    bool processSendEncryptedService(RpcProcessingContext &context);
    bool processSendInlineBotResult(RpcProcessingContext &context);
    bool processSendMedia(RpcProcessingContext &context);
    bool processSendMessage(RpcProcessingContext &context);
    bool processSendScreenshotNotification(RpcProcessingContext &context);
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
    bool processUploadMedia(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAcceptEncryption();
    void runAddChatUser();
    void runCheckChatInvite();
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
    void runForwardMessage();
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
    void runGetPeerDialogs();
    void runGetPeerSettings();
    void runGetPinnedDialogs();
    void runGetRecentLocations();
    void runGetRecentStickers();
    void runGetSavedGifs();
    void runGetStickerSet();
    void runGetUnreadMentions();
    void runGetWebPage();
    void runGetWebPagePreview();
    void runHideReportSpam();
    void runImportChatInvite();
    void runInstallStickerSet();
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
    void runReportEncryptedSpam();
    void runReportSpam();
    void runRequestEncryption();
    void runSaveDraft();
    void runSaveGif();
    void runSaveRecentSticker();
    void runSearch();
    void runSearchGifs();
    void runSearchGlobal();
    void runSendEncrypted();
    void runSendEncryptedFile();
    void runSendEncryptedService();
    void runSendInlineBotResult();
    void runSendMedia();
    void runSendMessage();
    void runSendScreenshotNotification();
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
    void runUploadMedia();
    // End of generated run methods

    using RunMethod = void (MessagesRpcOperation::*)();
    using ProcessingMethod = bool (MessagesRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);

protected:
    void startImplementation() override { callMember<>(this, m_runMethod); }

    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLMessagesAcceptEncryption m_acceptEncryption;
    TLFunctions::TLMessagesAddChatUser m_addChatUser;
    TLFunctions::TLMessagesCheckChatInvite m_checkChatInvite;
    TLFunctions::TLMessagesClearRecentStickers m_clearRecentStickers;
    TLFunctions::TLMessagesCreateChat m_createChat;
    TLFunctions::TLMessagesDeleteChatUser m_deleteChatUser;
    TLFunctions::TLMessagesDeleteHistory m_deleteHistory;
    TLFunctions::TLMessagesDeleteMessages m_deleteMessages;
    TLFunctions::TLMessagesDiscardEncryption m_discardEncryption;
    TLFunctions::TLMessagesEditChatAdmin m_editChatAdmin;
    TLFunctions::TLMessagesEditChatPhoto m_editChatPhoto;
    TLFunctions::TLMessagesEditChatTitle m_editChatTitle;
    TLFunctions::TLMessagesEditInlineBotMessage m_editInlineBotMessage;
    TLFunctions::TLMessagesEditMessage m_editMessage;
    TLFunctions::TLMessagesExportChatInvite m_exportChatInvite;
    TLFunctions::TLMessagesFaveSticker m_faveSticker;
    TLFunctions::TLMessagesForwardMessage m_forwardMessage;
    TLFunctions::TLMessagesForwardMessages m_forwardMessages;
    TLFunctions::TLMessagesGetAllChats m_getAllChats;
    TLFunctions::TLMessagesGetAllDrafts m_getAllDrafts;
    TLFunctions::TLMessagesGetAllStickers m_getAllStickers;
    TLFunctions::TLMessagesGetArchivedStickers m_getArchivedStickers;
    TLFunctions::TLMessagesGetAttachedStickers m_getAttachedStickers;
    TLFunctions::TLMessagesGetBotCallbackAnswer m_getBotCallbackAnswer;
    TLFunctions::TLMessagesGetChats m_getChats;
    TLFunctions::TLMessagesGetCommonChats m_getCommonChats;
    TLFunctions::TLMessagesGetDhConfig m_getDhConfig;
    TLFunctions::TLMessagesGetDialogs m_getDialogs;
    TLFunctions::TLMessagesGetDocumentByHash m_getDocumentByHash;
    TLFunctions::TLMessagesGetFavedStickers m_getFavedStickers;
    TLFunctions::TLMessagesGetFeaturedStickers m_getFeaturedStickers;
    TLFunctions::TLMessagesGetFullChat m_getFullChat;
    TLFunctions::TLMessagesGetGameHighScores m_getGameHighScores;
    TLFunctions::TLMessagesGetHistory m_getHistory;
    TLFunctions::TLMessagesGetInlineBotResults m_getInlineBotResults;
    TLFunctions::TLMessagesGetInlineGameHighScores m_getInlineGameHighScores;
    TLFunctions::TLMessagesGetMaskStickers m_getMaskStickers;
    TLFunctions::TLMessagesGetMessageEditData m_getMessageEditData;
    TLFunctions::TLMessagesGetMessages m_getMessages;
    TLFunctions::TLMessagesGetMessagesViews m_getMessagesViews;
    TLFunctions::TLMessagesGetPeerDialogs m_getPeerDialogs;
    TLFunctions::TLMessagesGetPeerSettings m_getPeerSettings;
    TLFunctions::TLMessagesGetPinnedDialogs m_getPinnedDialogs;
    TLFunctions::TLMessagesGetRecentLocations m_getRecentLocations;
    TLFunctions::TLMessagesGetRecentStickers m_getRecentStickers;
    TLFunctions::TLMessagesGetSavedGifs m_getSavedGifs;
    TLFunctions::TLMessagesGetStickerSet m_getStickerSet;
    TLFunctions::TLMessagesGetUnreadMentions m_getUnreadMentions;
    TLFunctions::TLMessagesGetWebPage m_getWebPage;
    TLFunctions::TLMessagesGetWebPagePreview m_getWebPagePreview;
    TLFunctions::TLMessagesHideReportSpam m_hideReportSpam;
    TLFunctions::TLMessagesImportChatInvite m_importChatInvite;
    TLFunctions::TLMessagesInstallStickerSet m_installStickerSet;
    TLFunctions::TLMessagesMigrateChat m_migrateChat;
    TLFunctions::TLMessagesReadEncryptedHistory m_readEncryptedHistory;
    TLFunctions::TLMessagesReadFeaturedStickers m_readFeaturedStickers;
    TLFunctions::TLMessagesReadHistory m_readHistory;
    TLFunctions::TLMessagesReadMentions m_readMentions;
    TLFunctions::TLMessagesReadMessageContents m_readMessageContents;
    TLFunctions::TLMessagesReceivedMessages m_receivedMessages;
    TLFunctions::TLMessagesReceivedQueue m_receivedQueue;
    TLFunctions::TLMessagesReorderPinnedDialogs m_reorderPinnedDialogs;
    TLFunctions::TLMessagesReorderStickerSets m_reorderStickerSets;
    TLFunctions::TLMessagesReportEncryptedSpam m_reportEncryptedSpam;
    TLFunctions::TLMessagesReportSpam m_reportSpam;
    TLFunctions::TLMessagesRequestEncryption m_requestEncryption;
    TLFunctions::TLMessagesSaveDraft m_saveDraft;
    TLFunctions::TLMessagesSaveGif m_saveGif;
    TLFunctions::TLMessagesSaveRecentSticker m_saveRecentSticker;
    TLFunctions::TLMessagesSearch m_search;
    TLFunctions::TLMessagesSearchGifs m_searchGifs;
    TLFunctions::TLMessagesSearchGlobal m_searchGlobal;
    TLFunctions::TLMessagesSendEncrypted m_sendEncrypted;
    TLFunctions::TLMessagesSendEncryptedFile m_sendEncryptedFile;
    TLFunctions::TLMessagesSendEncryptedService m_sendEncryptedService;
    TLFunctions::TLMessagesSendInlineBotResult m_sendInlineBotResult;
    TLFunctions::TLMessagesSendMedia m_sendMedia;
    TLFunctions::TLMessagesSendMessage m_sendMessage;
    TLFunctions::TLMessagesSendScreenshotNotification m_sendScreenshotNotification;
    TLFunctions::TLMessagesSetBotCallbackAnswer m_setBotCallbackAnswer;
    TLFunctions::TLMessagesSetBotPrecheckoutResults m_setBotPrecheckoutResults;
    TLFunctions::TLMessagesSetBotShippingResults m_setBotShippingResults;
    TLFunctions::TLMessagesSetEncryptedTyping m_setEncryptedTyping;
    TLFunctions::TLMessagesSetGameScore m_setGameScore;
    TLFunctions::TLMessagesSetInlineBotResults m_setInlineBotResults;
    TLFunctions::TLMessagesSetInlineGameScore m_setInlineGameScore;
    TLFunctions::TLMessagesSetTyping m_setTyping;
    TLFunctions::TLMessagesStartBot m_startBot;
    TLFunctions::TLMessagesToggleChatAdmins m_toggleChatAdmins;
    TLFunctions::TLMessagesToggleDialogPin m_toggleDialogPin;
    TLFunctions::TLMessagesUninstallStickerSet m_uninstallStickerSet;
    TLFunctions::TLMessagesUploadMedia m_uploadMedia;
    // End of generated RPC members
};

class MessagesOperationFactory : public RpcOperationFactory
{
public:
    RpcOperation *processRpcCall(RpcLayer *layer, RpcProcessingContext &context) override;
};

} // Server

} // Telegram

#endif // MESSAGES_OPERATION_FACTORY_HPP
