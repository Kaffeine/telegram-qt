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
#include "TLTypes.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class MessagesRpcLayer : public BaseRpcLayerExtension
{
    Q_OBJECT
public:
    explicit MessagesRpcLayer(QObject *parent = nullptr);

    // Generated Telegram API declarations
    PendingRpcOperation *acceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint);
    PendingRpcOperation *addChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit);
    PendingRpcOperation *checkChatInvite(const QString &hash);
    PendingRpcOperation *clearRecentStickers(quint32 flags);
    PendingRpcOperation *createChat(const TLVector<TLInputUser> &users, const QString &title);
    PendingRpcOperation *deleteChatUser(quint32 chatId, const TLInputUser &userId);
    PendingRpcOperation *deleteHistory(quint32 flags, const TLInputPeer &peer, quint32 maxId);
    PendingRpcOperation *deleteMessages(quint32 flags, const TLVector<quint32> &id);
    PendingRpcOperation *discardEncryption(quint32 chatId);
    PendingRpcOperation *editChatAdmin(quint32 chatId, const TLInputUser &userId, bool isAdmin);
    PendingRpcOperation *editChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    PendingRpcOperation *editChatTitle(quint32 chatId, const QString &title);
    PendingRpcOperation *editInlineBotMessage(quint32 flags, const TLInputBotInlineMessageID &id, const QString &message, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint);
    PendingRpcOperation *editMessage(quint32 flags, const TLInputPeer &peer, quint32 id, const QString &message, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint);
    PendingRpcOperation *exportChatInvite(quint32 chatId);
    PendingRpcOperation *faveSticker(const TLInputDocument &id, bool unfave);
    PendingRpcOperation *forwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    PendingRpcOperation *forwardMessages(quint32 flags, const TLInputPeer &fromPeer, const TLVector<quint32> &id, const TLVector<quint64> &randomId, const TLInputPeer &toPeer);
    PendingRpcOperation *getAllChats(const TLVector<quint32> &exceptIds);
    PendingRpcOperation *getAllDrafts();
    PendingRpcOperation *getAllStickers(quint32 hash);
    PendingRpcOperation *getArchivedStickers(quint32 flags, quint64 offsetId, quint32 limit);
    PendingRpcOperation *getAttachedStickers(const TLInputStickeredMedia &media);
    PendingRpcOperation *getBotCallbackAnswer(quint32 flags, const TLInputPeer &peer, quint32 msgId, const QByteArray &data);
    PendingRpcOperation *getChats(const TLVector<quint32> &id);
    PendingRpcOperation *getCommonChats(const TLInputUser &userId, quint32 maxId, quint32 limit);
    PendingRpcOperation *getDhConfig(quint32 version, quint32 randomLength);
    PendingRpcOperation *getDialogs(quint32 flags, quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    PendingRpcOperation *getDocumentByHash(const QByteArray &sha256, quint32 size, const QString &mimeType);
    PendingRpcOperation *getFavedStickers(quint32 hash);
    PendingRpcOperation *getFeaturedStickers(quint32 hash);
    PendingRpcOperation *getFullChat(quint32 chatId);
    PendingRpcOperation *getGameHighScores(const TLInputPeer &peer, quint32 id, const TLInputUser &userId);
    PendingRpcOperation *getHistory(const TLInputPeer &peer, quint32 offsetId, quint32 offsetDate, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId, quint32 hash);
    PendingRpcOperation *getInlineBotResults(quint32 flags, const TLInputUser &bot, const TLInputPeer &peer, const TLInputGeoPoint &geoPoint, const QString &query, const QString &offset);
    PendingRpcOperation *getInlineGameHighScores(const TLInputBotInlineMessageID &id, const TLInputUser &userId);
    PendingRpcOperation *getMaskStickers(quint32 hash);
    PendingRpcOperation *getMessageEditData(const TLInputPeer &peer, quint32 id);
    PendingRpcOperation *getMessages(const TLVector<quint32> &id);
    PendingRpcOperation *getMessagesViews(const TLInputPeer &peer, const TLVector<quint32> &id, bool increment);
    PendingRpcOperation *getPeerDialogs(const TLVector<TLInputPeer> &peers);
    PendingRpcOperation *getPeerSettings(const TLInputPeer &peer);
    PendingRpcOperation *getPinnedDialogs();
    PendingRpcOperation *getRecentLocations(const TLInputPeer &peer, quint32 limit);
    PendingRpcOperation *getRecentStickers(quint32 flags, quint32 hash);
    PendingRpcOperation *getSavedGifs(quint32 hash);
    PendingRpcOperation *getStickerSet(const TLInputStickerSet &stickerset);
    PendingRpcOperation *getUnreadMentions(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingRpcOperation *getWebPage(const QString &url, quint32 hash);
    PendingRpcOperation *getWebPagePreview(const QString &message);
    PendingRpcOperation *hideReportSpam(const TLInputPeer &peer);
    PendingRpcOperation *importChatInvite(const QString &hash);
    PendingRpcOperation *installStickerSet(const TLInputStickerSet &stickerset, bool archived);
    PendingRpcOperation *migrateChat(quint32 chatId);
    PendingRpcOperation *readEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    PendingRpcOperation *readFeaturedStickers(const TLVector<quint64> &id);
    PendingRpcOperation *readHistory(const TLInputPeer &peer, quint32 maxId);
    PendingRpcOperation *readMentions(const TLInputPeer &peer);
    PendingRpcOperation *readMessageContents(const TLVector<quint32> &id);
    PendingRpcOperation *receivedMessages(quint32 maxId);
    PendingRpcOperation *receivedQueue(quint32 maxQts);
    PendingRpcOperation *reorderPinnedDialogs(quint32 flags, const TLVector<TLInputPeer> &order);
    PendingRpcOperation *reorderStickerSets(quint32 flags, const TLVector<quint64> &order);
    PendingRpcOperation *reportEncryptedSpam(const TLInputEncryptedChat &peer);
    PendingRpcOperation *reportSpam(const TLInputPeer &peer);
    PendingRpcOperation *requestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    PendingRpcOperation *saveDraft(quint32 flags, quint32 replyToMsgId, const TLInputPeer &peer, const QString &message, const TLVector<TLMessageEntity> &entities);
    PendingRpcOperation *saveGif(const TLInputDocument &id, bool unsave);
    PendingRpcOperation *saveRecentSticker(quint32 flags, const TLInputDocument &id, bool unsave);
    PendingRpcOperation *search(quint32 flags, const TLInputPeer &peer, const QString &q, const TLInputUser &fromId, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingRpcOperation *searchGifs(const QString &q, quint32 offset);
    PendingRpcOperation *searchGlobal(const QString &q, quint32 offsetDate, const TLInputPeer &offsetPeer, quint32 offsetId, quint32 limit);
    PendingRpcOperation *sendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingRpcOperation *sendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    PendingRpcOperation *sendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingRpcOperation *sendInlineBotResult(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId, quint64 queryId, const QString &id);
    PendingRpcOperation *sendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup);
    PendingRpcOperation *sendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities);
    PendingRpcOperation *sendScreenshotNotification(const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId);
    PendingRpcOperation *setBotCallbackAnswer(quint32 flags, quint64 queryId, const QString &message, const QString &url, quint32 cacheTime);
    PendingRpcOperation *setBotPrecheckoutResults(quint32 flags, quint64 queryId, const QString &error);
    PendingRpcOperation *setBotShippingResults(quint32 flags, quint64 queryId, const QString &error, const TLVector<TLShippingOption> &shippingOptions);
    PendingRpcOperation *setEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    PendingRpcOperation *setGameScore(quint32 flags, const TLInputPeer &peer, quint32 id, const TLInputUser &userId, quint32 score);
    PendingRpcOperation *setInlineBotResults(quint32 flags, quint64 queryId, const TLVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset, const TLInlineBotSwitchPM &switchPm);
    PendingRpcOperation *setInlineGameScore(quint32 flags, const TLInputBotInlineMessageID &id, const TLInputUser &userId, quint32 score);
    PendingRpcOperation *setTyping(const TLInputPeer &peer, const TLSendMessageAction &action);
    PendingRpcOperation *startBot(const TLInputUser &bot, const TLInputPeer &peer, quint64 randomId, const QString &startParam);
    PendingRpcOperation *toggleChatAdmins(quint32 chatId, bool enabled);
    PendingRpcOperation *toggleDialogPin(quint32 flags, const TLInputPeer &peer);
    PendingRpcOperation *uninstallStickerSet(const TLInputStickerSet &stickerset);
    PendingRpcOperation *uploadMedia(const TLInputPeer &peer, const TLInputMedia &media);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_MESSAGES_LAYER_HPP
