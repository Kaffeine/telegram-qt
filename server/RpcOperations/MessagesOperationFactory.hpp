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
    bool processCreateChat(RpcProcessingContext &context);
    bool processDeleteChatUser(RpcProcessingContext &context);
    bool processDeleteHistory(RpcProcessingContext &context);
    bool processDeleteMessages(RpcProcessingContext &context);
    bool processDiscardEncryption(RpcProcessingContext &context);
    bool processEditChatAdmin(RpcProcessingContext &context);
    bool processEditChatPhoto(RpcProcessingContext &context);
    bool processEditChatTitle(RpcProcessingContext &context);
    bool processExportChatInvite(RpcProcessingContext &context);
    bool processForwardMessage(RpcProcessingContext &context);
    bool processForwardMessages(RpcProcessingContext &context);
    bool processGetAllStickers(RpcProcessingContext &context);
    bool processGetChats(RpcProcessingContext &context);
    bool processGetDhConfig(RpcProcessingContext &context);
    bool processGetDialogs(RpcProcessingContext &context);
    bool processGetDocumentByHash(RpcProcessingContext &context);
    bool processGetFullChat(RpcProcessingContext &context);
    bool processGetHistory(RpcProcessingContext &context);
    bool processGetInlineBotResults(RpcProcessingContext &context);
    bool processGetMessages(RpcProcessingContext &context);
    bool processGetMessagesViews(RpcProcessingContext &context);
    bool processGetSavedGifs(RpcProcessingContext &context);
    bool processGetStickerSet(RpcProcessingContext &context);
    bool processGetStickers(RpcProcessingContext &context);
    bool processGetWebPagePreview(RpcProcessingContext &context);
    bool processImportChatInvite(RpcProcessingContext &context);
    bool processInstallStickerSet(RpcProcessingContext &context);
    bool processMigrateChat(RpcProcessingContext &context);
    bool processReadEncryptedHistory(RpcProcessingContext &context);
    bool processReadHistory(RpcProcessingContext &context);
    bool processReadMessageContents(RpcProcessingContext &context);
    bool processReceivedMessages(RpcProcessingContext &context);
    bool processReceivedQueue(RpcProcessingContext &context);
    bool processReorderStickerSets(RpcProcessingContext &context);
    bool processReportSpam(RpcProcessingContext &context);
    bool processRequestEncryption(RpcProcessingContext &context);
    bool processSaveGif(RpcProcessingContext &context);
    bool processSearch(RpcProcessingContext &context);
    bool processSearchGifs(RpcProcessingContext &context);
    bool processSearchGlobal(RpcProcessingContext &context);
    bool processSendBroadcast(RpcProcessingContext &context);
    bool processSendEncrypted(RpcProcessingContext &context);
    bool processSendEncryptedFile(RpcProcessingContext &context);
    bool processSendEncryptedService(RpcProcessingContext &context);
    bool processSendInlineBotResult(RpcProcessingContext &context);
    bool processSendMedia(RpcProcessingContext &context);
    bool processSendMessage(RpcProcessingContext &context);
    bool processSetEncryptedTyping(RpcProcessingContext &context);
    bool processSetInlineBotResults(RpcProcessingContext &context);
    bool processSetTyping(RpcProcessingContext &context);
    bool processStartBot(RpcProcessingContext &context);
    bool processToggleChatAdmins(RpcProcessingContext &context);
    bool processUninstallStickerSet(RpcProcessingContext &context);
    // End of generated process methods

    // Generated run methods
    void runAcceptEncryption();
    void runAddChatUser();
    void runCheckChatInvite();
    void runCreateChat();
    void runDeleteChatUser();
    void runDeleteHistory();
    void runDeleteMessages();
    void runDiscardEncryption();
    void runEditChatAdmin();
    void runEditChatPhoto();
    void runEditChatTitle();
    void runExportChatInvite();
    void runForwardMessage();
    void runForwardMessages();
    void runGetAllStickers();
    void runGetChats();
    void runGetDhConfig();
    void runGetDialogs();
    void runGetDocumentByHash();
    void runGetFullChat();
    void runGetHistory();
    void runGetInlineBotResults();
    void runGetMessages();
    void runGetMessagesViews();
    void runGetSavedGifs();
    void runGetStickerSet();
    void runGetStickers();
    void runGetWebPagePreview();
    void runImportChatInvite();
    void runInstallStickerSet();
    void runMigrateChat();
    void runReadEncryptedHistory();
    void runReadHistory();
    void runReadMessageContents();
    void runReceivedMessages();
    void runReceivedQueue();
    void runReorderStickerSets();
    void runReportSpam();
    void runRequestEncryption();
    void runSaveGif();
    void runSearch();
    void runSearchGifs();
    void runSearchGlobal();
    void runSendBroadcast();
    void runSendEncrypted();
    void runSendEncryptedFile();
    void runSendEncryptedService();
    void runSendInlineBotResult();
    void runSendMedia();
    void runSendMessage();
    void runSetEncryptedTyping();
    void runSetInlineBotResults();
    void runSetTyping();
    void runStartBot();
    void runToggleChatAdmins();
    void runUninstallStickerSet();
    // End of generated run methods

    void start() override { callMember<>(this, m_runMethod); }

    using RunMethod = void (MessagesRpcOperation::*)();
    using ProcessingMethod = bool (MessagesRpcOperation::*)(RpcProcessingContext &);
    static ProcessingMethod getMethodForRpcFunction(TLValue function);
protected:
    void setRunMethod(RunMethod method);

    RunMethod m_runMethod = nullptr;

    // Generated RPC members
    TLFunctions::TLMessagesAcceptEncryption m_acceptEncryption;
    TLFunctions::TLMessagesAddChatUser m_addChatUser;
    TLFunctions::TLMessagesCheckChatInvite m_checkChatInvite;
    TLFunctions::TLMessagesCreateChat m_createChat;
    TLFunctions::TLMessagesDeleteChatUser m_deleteChatUser;
    TLFunctions::TLMessagesDeleteHistory m_deleteHistory;
    TLFunctions::TLMessagesDeleteMessages m_deleteMessages;
    TLFunctions::TLMessagesDiscardEncryption m_discardEncryption;
    TLFunctions::TLMessagesEditChatAdmin m_editChatAdmin;
    TLFunctions::TLMessagesEditChatPhoto m_editChatPhoto;
    TLFunctions::TLMessagesEditChatTitle m_editChatTitle;
    TLFunctions::TLMessagesExportChatInvite m_exportChatInvite;
    TLFunctions::TLMessagesForwardMessage m_forwardMessage;
    TLFunctions::TLMessagesForwardMessages m_forwardMessages;
    TLFunctions::TLMessagesGetAllStickers m_getAllStickers;
    TLFunctions::TLMessagesGetChats m_getChats;
    TLFunctions::TLMessagesGetDhConfig m_getDhConfig;
    TLFunctions::TLMessagesGetDialogs m_getDialogs;
    TLFunctions::TLMessagesGetDocumentByHash m_getDocumentByHash;
    TLFunctions::TLMessagesGetFullChat m_getFullChat;
    TLFunctions::TLMessagesGetHistory m_getHistory;
    TLFunctions::TLMessagesGetInlineBotResults m_getInlineBotResults;
    TLFunctions::TLMessagesGetMessages m_getMessages;
    TLFunctions::TLMessagesGetMessagesViews m_getMessagesViews;
    TLFunctions::TLMessagesGetSavedGifs m_getSavedGifs;
    TLFunctions::TLMessagesGetStickerSet m_getStickerSet;
    TLFunctions::TLMessagesGetStickers m_getStickers;
    TLFunctions::TLMessagesGetWebPagePreview m_getWebPagePreview;
    TLFunctions::TLMessagesImportChatInvite m_importChatInvite;
    TLFunctions::TLMessagesInstallStickerSet m_installStickerSet;
    TLFunctions::TLMessagesMigrateChat m_migrateChat;
    TLFunctions::TLMessagesReadEncryptedHistory m_readEncryptedHistory;
    TLFunctions::TLMessagesReadHistory m_readHistory;
    TLFunctions::TLMessagesReadMessageContents m_readMessageContents;
    TLFunctions::TLMessagesReceivedMessages m_receivedMessages;
    TLFunctions::TLMessagesReceivedQueue m_receivedQueue;
    TLFunctions::TLMessagesReorderStickerSets m_reorderStickerSets;
    TLFunctions::TLMessagesReportSpam m_reportSpam;
    TLFunctions::TLMessagesRequestEncryption m_requestEncryption;
    TLFunctions::TLMessagesSaveGif m_saveGif;
    TLFunctions::TLMessagesSearch m_search;
    TLFunctions::TLMessagesSearchGifs m_searchGifs;
    TLFunctions::TLMessagesSearchGlobal m_searchGlobal;
    TLFunctions::TLMessagesSendBroadcast m_sendBroadcast;
    TLFunctions::TLMessagesSendEncrypted m_sendEncrypted;
    TLFunctions::TLMessagesSendEncryptedFile m_sendEncryptedFile;
    TLFunctions::TLMessagesSendEncryptedService m_sendEncryptedService;
    TLFunctions::TLMessagesSendInlineBotResult m_sendInlineBotResult;
    TLFunctions::TLMessagesSendMedia m_sendMedia;
    TLFunctions::TLMessagesSendMessage m_sendMessage;
    TLFunctions::TLMessagesSetEncryptedTyping m_setEncryptedTyping;
    TLFunctions::TLMessagesSetInlineBotResults m_setInlineBotResults;
    TLFunctions::TLMessagesSetTyping m_setTyping;
    TLFunctions::TLMessagesStartBot m_startBot;
    TLFunctions::TLMessagesToggleChatAdmins m_toggleChatAdmins;
    TLFunctions::TLMessagesUninstallStickerSet m_uninstallStickerSet;
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
