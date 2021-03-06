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

#ifndef TELEGRAM_CLIENT_RPC_MESSAGES_LAYER_HPP
#define TELEGRAM_CLIENT_RPC_MESSAGES_LAYER_HPP

#include "ClientRpcLayerExtension.hpp"

#include "MTProto/TLTypes.hpp"
#include "PendingRpcResult.hpp"

namespace Telegram {

namespace Client {

class PendingRpcOperation;

class MessagesRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit MessagesRpcLayer(QObject *parent = nullptr);

    // Generated Telegram operations using
    using PendingEncryptedChat = PendingRpcResult<TLEncryptedChat *>;
    using PendingUpdates = PendingRpcResult<TLUpdates *>;
    using PendingChatInvite = PendingRpcResult<TLChatInvite *>;
    using PendingBool = PendingRpcResult<TLBool *>;
    using PendingMessagesAffectedHistory = PendingRpcResult<TLMessagesAffectedHistory *>;
    using PendingMessagesAffectedMessages = PendingRpcResult<TLMessagesAffectedMessages *>;
    using PendingExportedChatInvite = PendingRpcResult<TLExportedChatInvite *>;
    using PendingMessagesChats = PendingRpcResult<TLMessagesChats *>;
    using PendingMessagesAllStickers = PendingRpcResult<TLMessagesAllStickers *>;
    using PendingMessagesArchivedStickers = PendingRpcResult<TLMessagesArchivedStickers *>;
    using PendingStickerSetCoveredVector = PendingRpcResult<QVector<TLStickerSetCovered> *>;
    using PendingMessagesBotCallbackAnswer = PendingRpcResult<TLMessagesBotCallbackAnswer *>;
    using PendingMessagesDhConfig = PendingRpcResult<TLMessagesDhConfig *>;
    using PendingMessagesDialogs = PendingRpcResult<TLMessagesDialogs *>;
    using PendingDocument = PendingRpcResult<TLDocument *>;
    using PendingMessagesFavedStickers = PendingRpcResult<TLMessagesFavedStickers *>;
    using PendingMessagesFeaturedStickers = PendingRpcResult<TLMessagesFeaturedStickers *>;
    using PendingMessagesChatFull = PendingRpcResult<TLMessagesChatFull *>;
    using PendingMessagesHighScores = PendingRpcResult<TLMessagesHighScores *>;
    using PendingMessagesMessages = PendingRpcResult<TLMessagesMessages *>;
    using PendingMessagesBotResults = PendingRpcResult<TLMessagesBotResults *>;
    using PendingMessagesMessageEditData = PendingRpcResult<TLMessagesMessageEditData *>;
    using PendingQuint32Vector = PendingRpcResult<QVector<quint32> *>;
    using PendingMessagesPeerDialogs = PendingRpcResult<TLMessagesPeerDialogs *>;
    using PendingPeerSettings = PendingRpcResult<TLPeerSettings *>;
    using PendingMessagesRecentStickers = PendingRpcResult<TLMessagesRecentStickers *>;
    using PendingMessagesSavedGifs = PendingRpcResult<TLMessagesSavedGifs *>;
    using PendingMessagesStickerSet = PendingRpcResult<TLMessagesStickerSet *>;
    using PendingWebPage = PendingRpcResult<TLWebPage *>;
    using PendingMessageMedia = PendingRpcResult<TLMessageMedia *>;
    using PendingMessagesStickerSetInstallResult = PendingRpcResult<TLMessagesStickerSetInstallResult *>;
    using PendingReceivedNotifyMessageVector = PendingRpcResult<QVector<TLReceivedNotifyMessage> *>;
    using PendingQuint64Vector = PendingRpcResult<QVector<quint64> *>;
    using PendingMessagesFoundGifs = PendingRpcResult<TLMessagesFoundGifs *>;
    using PendingMessagesSentEncryptedMessage = PendingRpcResult<TLMessagesSentEncryptedMessage *>;
    // End of generated Telegram operations using

    // Generated Telegram API declarations
    PendingEncryptedChat *acceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint);
    PendingUpdates *addChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit);
    PendingChatInvite *checkChatInvite(const QString &hash);
    PendingBool *clearRecentStickers(quint32 flags);
    PendingUpdates *createChat(const QVector<TLInputUser> &users, const QString &title);
    PendingUpdates *deleteChatUser(quint32 chatId, const TLInputUser &userId);
    PendingMessagesAffectedHistory *deleteHistory(quint32 flags, const TLInputPeer &peer, quint32 maxId);
    PendingMessagesAffectedMessages *deleteMessages(quint32 flags, const QVector<quint32> &id);
    PendingBool *discardEncryption(quint32 chatId);
    PendingBool *editChatAdmin(quint32 chatId, const TLInputUser &userId, bool isAdmin);
    PendingUpdates *editChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    PendingUpdates *editChatTitle(quint32 chatId, const QString &title);
    PendingBool *editInlineBotMessage(quint32 flags, const TLInputBotInlineMessageID &id, const QString &message, const TLReplyMarkup &replyMarkup, const QVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint);
    PendingUpdates *editMessage(quint32 flags, const TLInputPeer &peer, quint32 id, const QString &message, const TLReplyMarkup &replyMarkup, const QVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint);
    PendingExportedChatInvite *exportChatInvite(quint32 chatId);
    PendingBool *faveSticker(const TLInputDocument &id, bool unfave);
    PendingUpdates *forwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    PendingUpdates *forwardMessages(quint32 flags, const TLInputPeer &fromPeer, const QVector<quint32> &id, const QVector<quint64> &randomId, const TLInputPeer &toPeer);
    PendingMessagesChats *getAllChats(const QVector<quint32> &exceptIds);
    PendingUpdates *getAllDrafts();
    PendingMessagesAllStickers *getAllStickers(quint32 hash);
    PendingMessagesArchivedStickers *getArchivedStickers(quint32 flags, quint64 offsetId, quint32 limit);
    PendingStickerSetCoveredVector *getAttachedStickers(const TLInputStickeredMedia &media);
    PendingMessagesBotCallbackAnswer *getBotCallbackAnswer(quint32 flags, const TLInputPeer &peer, quint32 msgId, const QByteArray &data);
    PendingMessagesChats *getChats(const QVector<quint32> &id);
    PendingMessagesChats *getCommonChats(const TLInputUser &userId, quint32 maxId, quint32 limit);
    PendingMessagesDhConfig *getDhConfig(quint32 version, quint32 randomLength);
    PendingMessagesDialogs *getDialogs(quint32 flags, quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    PendingDocument *getDocumentByHash(const QByteArray &sha256, quint32 size, const QString &mimeType);
    PendingMessagesFavedStickers *getFavedStickers(quint32 hash);
    PendingMessagesFeaturedStickers *getFeaturedStickers(quint32 hash);
    PendingMessagesChatFull *getFullChat(quint32 chatId);
    PendingMessagesHighScores *getGameHighScores(const TLInputPeer &peer, quint32 id, const TLInputUser &userId);
    PendingMessagesMessages *getHistory(const TLInputPeer &peer, quint32 offsetId, quint32 offsetDate, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId, quint32 hash);
    PendingMessagesBotResults *getInlineBotResults(quint32 flags, const TLInputUser &bot, const TLInputPeer &peer, const TLInputGeoPoint &geoPoint, const QString &query, const QString &offset);
    PendingMessagesHighScores *getInlineGameHighScores(const TLInputBotInlineMessageID &id, const TLInputUser &userId);
    PendingMessagesAllStickers *getMaskStickers(quint32 hash);
    PendingMessagesMessageEditData *getMessageEditData(const TLInputPeer &peer, quint32 id);
    PendingMessagesMessages *getMessages(const QVector<quint32> &id);
    PendingQuint32Vector *getMessagesViews(const TLInputPeer &peer, const QVector<quint32> &id, bool increment);
    PendingMessagesPeerDialogs *getPeerDialogs(const QVector<TLInputPeer> &peers);
    PendingPeerSettings *getPeerSettings(const TLInputPeer &peer);
    PendingMessagesPeerDialogs *getPinnedDialogs();
    PendingMessagesMessages *getRecentLocations(const TLInputPeer &peer, quint32 limit);
    PendingMessagesRecentStickers *getRecentStickers(quint32 flags, quint32 hash);
    PendingMessagesSavedGifs *getSavedGifs(quint32 hash);
    PendingMessagesStickerSet *getStickerSet(const TLInputStickerSet &stickerset);
    PendingMessagesMessages *getUnreadMentions(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingWebPage *getWebPage(const QString &url, quint32 hash);
    PendingMessageMedia *getWebPagePreview(const QString &message);
    PendingBool *hideReportSpam(const TLInputPeer &peer);
    PendingUpdates *importChatInvite(const QString &hash);
    PendingMessagesStickerSetInstallResult *installStickerSet(const TLInputStickerSet &stickerset, bool archived);
    PendingUpdates *migrateChat(quint32 chatId);
    PendingBool *readEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    PendingBool *readFeaturedStickers(const QVector<quint64> &id);
    PendingMessagesAffectedMessages *readHistory(const TLInputPeer &peer, quint32 maxId);
    PendingMessagesAffectedHistory *readMentions(const TLInputPeer &peer);
    PendingMessagesAffectedMessages *readMessageContents(const QVector<quint32> &id);
    PendingReceivedNotifyMessageVector *receivedMessages(quint32 maxId);
    PendingQuint64Vector *receivedQueue(quint32 maxQts);
    PendingBool *reorderPinnedDialogs(quint32 flags, const QVector<TLInputPeer> &order);
    PendingBool *reorderStickerSets(quint32 flags, const QVector<quint64> &order);
    PendingBool *reportEncryptedSpam(const TLInputEncryptedChat &peer);
    PendingBool *reportSpam(const TLInputPeer &peer);
    PendingEncryptedChat *requestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    PendingBool *saveDraft(quint32 flags, quint32 replyToMsgId, const TLInputPeer &peer, const QString &message, const QVector<TLMessageEntity> &entities);
    PendingBool *saveGif(const TLInputDocument &id, bool unsave);
    PendingBool *saveRecentSticker(quint32 flags, const TLInputDocument &id, bool unsave);
    PendingMessagesMessages *search(quint32 flags, const TLInputPeer &peer, const QString &q, const TLInputUser &fromId, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingMessagesFoundGifs *searchGifs(const QString &q, quint32 offset);
    PendingMessagesMessages *searchGlobal(const QString &q, quint32 offsetDate, const TLInputPeer &offsetPeer, quint32 offsetId, quint32 limit);
    PendingMessagesSentEncryptedMessage *sendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingMessagesSentEncryptedMessage *sendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    PendingMessagesSentEncryptedMessage *sendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingUpdates *sendInlineBotResult(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId, quint64 queryId, const QString &id);
    PendingUpdates *sendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup);
    PendingUpdates *sendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const QVector<TLMessageEntity> &entities);
    PendingUpdates *sendScreenshotNotification(const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId);
    PendingBool *setBotCallbackAnswer(quint32 flags, quint64 queryId, const QString &message, const QString &url, quint32 cacheTime);
    PendingBool *setBotPrecheckoutResults(quint32 flags, quint64 queryId, const QString &error);
    PendingBool *setBotShippingResults(quint32 flags, quint64 queryId, const QString &error, const QVector<TLShippingOption> &shippingOptions);
    PendingBool *setEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    PendingUpdates *setGameScore(quint32 flags, const TLInputPeer &peer, quint32 id, const TLInputUser &userId, quint32 score);
    PendingBool *setInlineBotResults(quint32 flags, quint64 queryId, const QVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset, const TLInlineBotSwitchPM &switchPm);
    PendingBool *setInlineGameScore(quint32 flags, const TLInputBotInlineMessageID &id, const TLInputUser &userId, quint32 score);
    PendingBool *setTyping(const TLInputPeer &peer, const TLSendMessageAction &action);
    PendingUpdates *startBot(const TLInputUser &bot, const TLInputPeer &peer, quint64 randomId, const QString &startParam);
    PendingUpdates *toggleChatAdmins(quint32 chatId, bool enabled);
    PendingBool *toggleDialogPin(quint32 flags, const TLInputPeer &peer);
    PendingBool *uninstallStickerSet(const TLInputStickerSet &stickerset);
    PendingMessageMedia *uploadMedia(const TLInputPeer &peer, const TLInputMedia &media);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_MESSAGES_LAYER_HPP
