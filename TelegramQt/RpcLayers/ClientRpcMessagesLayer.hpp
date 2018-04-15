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
    PendingRpcOperation *createChat(const TLVector<TLInputUser> &users, const QString &title);
    PendingRpcOperation *deleteChatUser(quint32 chatId, const TLInputUser &userId);
    PendingRpcOperation *deleteHistory(const TLInputPeer &peer, quint32 maxId);
    PendingRpcOperation *deleteMessages(const TLVector<quint32> &id);
    PendingRpcOperation *discardEncryption(quint32 chatId);
    PendingRpcOperation *editChatAdmin(quint32 chatId, const TLInputUser &userId, bool isAdmin);
    PendingRpcOperation *editChatPhoto(quint32 chatId, const TLInputChatPhoto &photo);
    PendingRpcOperation *editChatTitle(quint32 chatId, const QString &title);
    PendingRpcOperation *exportChatInvite(quint32 chatId);
    PendingRpcOperation *forwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId);
    PendingRpcOperation *forwardMessages(quint32 flags, const TLInputPeer &fromPeer, const TLVector<quint32> &id, const TLVector<quint64> &randomId, const TLInputPeer &toPeer);
    PendingRpcOperation *getAllStickers(quint32 hash);
    PendingRpcOperation *getChats(const TLVector<quint32> &id);
    PendingRpcOperation *getDhConfig(quint32 version, quint32 randomLength);
    PendingRpcOperation *getDialogs(quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit);
    PendingRpcOperation *getDocumentByHash(const QByteArray &sha256, quint32 size, const QString &mimeType);
    PendingRpcOperation *getFullChat(quint32 chatId);
    PendingRpcOperation *getHistory(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId);
    PendingRpcOperation *getInlineBotResults(const TLInputUser &bot, const QString &query, const QString &offset);
    PendingRpcOperation *getMessages(const TLVector<quint32> &id);
    PendingRpcOperation *getMessagesViews(const TLInputPeer &peer, const TLVector<quint32> &id, bool increment);
    PendingRpcOperation *getSavedGifs(quint32 hash);
    PendingRpcOperation *getStickerSet(const TLInputStickerSet &stickerset);
    PendingRpcOperation *getStickers(const QString &emoticon, const QString &hash);
    PendingRpcOperation *getWebPagePreview(const QString &message);
    PendingRpcOperation *importChatInvite(const QString &hash);
    PendingRpcOperation *installStickerSet(const TLInputStickerSet &stickerset, bool disabled);
    PendingRpcOperation *migrateChat(quint32 chatId);
    PendingRpcOperation *readEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate);
    PendingRpcOperation *readHistory(const TLInputPeer &peer, quint32 maxId);
    PendingRpcOperation *readMessageContents(const TLVector<quint32> &id);
    PendingRpcOperation *receivedMessages(quint32 maxId);
    PendingRpcOperation *receivedQueue(quint32 maxQts);
    PendingRpcOperation *reorderStickerSets(const TLVector<quint64> &order);
    PendingRpcOperation *reportSpam(const TLInputPeer &peer);
    PendingRpcOperation *requestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA);
    PendingRpcOperation *saveGif(const TLInputDocument &id, bool unsave);
    PendingRpcOperation *search(quint32 flags, const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit);
    PendingRpcOperation *searchGifs(const QString &q, quint32 offset);
    PendingRpcOperation *searchGlobal(const QString &q, quint32 offsetDate, const TLInputPeer &offsetPeer, quint32 offsetId, quint32 limit);
    PendingRpcOperation *sendBroadcast(const TLVector<TLInputUser> &contacts, const TLVector<quint64> &randomId, const QString &message, const TLInputMedia &media);
    PendingRpcOperation *sendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingRpcOperation *sendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file);
    PendingRpcOperation *sendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data);
    PendingRpcOperation *sendInlineBotResult(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId, quint64 queryId, const QString &id);
    PendingRpcOperation *sendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup);
    PendingRpcOperation *sendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities);
    PendingRpcOperation *setEncryptedTyping(const TLInputEncryptedChat &peer, bool typing);
    PendingRpcOperation *setInlineBotResults(quint32 flags, quint64 queryId, const TLVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset);
    PendingRpcOperation *setTyping(const TLInputPeer &peer, const TLSendMessageAction &action);
    PendingRpcOperation *startBot(const TLInputUser &bot, const TLInputPeer &peer, quint64 randomId, const QString &startParam);
    PendingRpcOperation *toggleChatAdmins(quint32 chatId, bool enabled);
    PendingRpcOperation *uninstallStickerSet(const TLInputStickerSet &stickerset);
    // End of generated Telegram API declarations
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_CLIENT_RPC_MESSAGES_LAYER_HPP
