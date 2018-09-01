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

#include "ClientRpcMessagesLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "CTelegramStream.hpp"
#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcMessagesCategory, "telegram.client.rpclayer.messages", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAffectedHistory *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAffectedMessages *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAllStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesArchivedStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesBotCallbackAnswer *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesBotResults *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesChatFull *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesChats *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesDhConfig *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesDialogs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFavedStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFeaturedStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFilter *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFoundGifs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesHighScores *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesMessageEditData *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesMessages *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesPeerDialogs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesRecentStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesSavedGifs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesSentEncryptedMessage *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesStickerSet *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesStickerSetInstallResult *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesStickers *output);
// End of generated Telegram API reply template specializations

MessagesRpcLayer::MessagesRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
PendingRpcOperation *MessagesRpcLayer::acceptEncryption(const TLInputEncryptedChat &peer, const QByteArray &gB, quint64 keyFingerprint)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << gB.toHex() << keyFingerprint;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesAcceptEncryption;
    outputStream << peer;
    outputStream << gB;
    outputStream << keyFingerprint;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::addChatUser(quint32 chatId, const TLInputUser &userId, quint32 fwdLimit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << userId << fwdLimit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesAddChatUser;
    outputStream << chatId;
    outputStream << userId;
    outputStream << fwdLimit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::checkChatInvite(const QString &hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesCheckChatInvite;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::clearRecentStickers(quint32 flags)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesClearRecentStickers;
    outputStream << flags;
    // (flags & 1 << 0) stands for attached "true" value
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::createChat(const TLVector<TLInputUser> &users, const QString &title)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << users << title;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesCreateChat;
    outputStream << users;
    outputStream << title;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::deleteChatUser(quint32 chatId, const TLInputUser &userId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << userId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDeleteChatUser;
    outputStream << chatId;
    outputStream << userId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::deleteHistory(quint32 flags, const TLInputPeer &peer, quint32 maxId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDeleteHistory;
    outputStream << flags;
    // (flags & 1 << 0) stands for justClear "true" value
    outputStream << peer;
    outputStream << maxId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::deleteMessages(quint32 flags, const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDeleteMessages;
    outputStream << flags;
    // (flags & 1 << 0) stands for revoke "true" value
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::discardEncryption(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDiscardEncryption;
    outputStream << chatId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::editChatAdmin(quint32 chatId, const TLInputUser &userId, bool isAdmin)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << userId << isAdmin;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesEditChatAdmin;
    outputStream << chatId;
    outputStream << userId;
    outputStream << isAdmin;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::editChatPhoto(quint32 chatId, const TLInputChatPhoto &photo)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << photo;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesEditChatPhoto;
    outputStream << chatId;
    outputStream << photo;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::editChatTitle(quint32 chatId, const QString &title)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << title;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesEditChatTitle;
    outputStream << chatId;
    outputStream << title;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::editInlineBotMessage(quint32 flags, const TLInputBotInlineMessageID &id, const QString &message, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << id << message << replyMarkup << entities << geoPoint;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesEditInlineBotMessage;
    outputStream << flags;
    // (flags & 1 << 1) stands for noWebpage "true" value
    // (flags & 1 << 12) stands for stopGeoLive "true" value
    outputStream << id;
    if (flags & 1 << 11) {
        outputStream << message;
    }
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    if (flags & 1 << 3) {
        outputStream << entities;
    }
    if (flags & 1 << 13) {
        outputStream << geoPoint;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::editMessage(quint32 flags, const TLInputPeer &peer, quint32 id, const QString &message, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities, const TLInputGeoPoint &geoPoint)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << id << message << replyMarkup << entities << geoPoint;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesEditMessage;
    outputStream << flags;
    // (flags & 1 << 1) stands for noWebpage "true" value
    // (flags & 1 << 12) stands for stopGeoLive "true" value
    outputStream << peer;
    outputStream << id;
    if (flags & 1 << 11) {
        outputStream << message;
    }
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    if (flags & 1 << 3) {
        outputStream << entities;
    }
    if (flags & 1 << 13) {
        outputStream << geoPoint;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::exportChatInvite(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesExportChatInvite;
    outputStream << chatId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::faveSticker(const TLInputDocument &id, bool unfave)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id << unfave;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesFaveSticker;
    outputStream << id;
    outputStream << unfave;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::forwardMessage(const TLInputPeer &peer, quint32 id, quint64 randomId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << id << randomId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesForwardMessage;
    outputStream << peer;
    outputStream << id;
    outputStream << randomId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::forwardMessages(quint32 flags, const TLInputPeer &fromPeer, const TLVector<quint32> &id, const TLVector<quint64> &randomId, const TLInputPeer &toPeer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << fromPeer << id << randomId << toPeer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesForwardMessages;
    outputStream << flags;
    // (flags & 1 << 5) stands for silent "true" value
    // (flags & 1 << 6) stands for background "true" value
    // (flags & 1 << 8) stands for withMyScore "true" value
    outputStream << fromPeer;
    outputStream << id;
    outputStream << randomId;
    outputStream << toPeer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getAllChats(const TLVector<quint32> &exceptIds)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << exceptIds;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetAllChats;
    outputStream << exceptIds;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getAllDrafts()
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetAllDrafts;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getAllStickers(quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetAllStickers;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getArchivedStickers(quint32 flags, quint64 offsetId, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << offsetId << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetArchivedStickers;
    outputStream << flags;
    // (flags & 1 << 0) stands for masks "true" value
    outputStream << offsetId;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getAttachedStickers(const TLInputStickeredMedia &media)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << media;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetAttachedStickers;
    outputStream << media;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getBotCallbackAnswer(quint32 flags, const TLInputPeer &peer, quint32 msgId, const QByteArray &data)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << msgId << data.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetBotCallbackAnswer;
    outputStream << flags;
    // (flags & 1 << 1) stands for game "true" value
    outputStream << peer;
    outputStream << msgId;
    if (flags & 1 << 0) {
        outputStream << data;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getChats(const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetChats;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getCommonChats(const TLInputUser &userId, quint32 maxId, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << userId << maxId << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetCommonChats;
    outputStream << userId;
    outputStream << maxId;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getDhConfig(quint32 version, quint32 randomLength)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << version << randomLength;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetDhConfig;
    outputStream << version;
    outputStream << randomLength;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getDialogs(quint32 flags, quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << offsetDate << offsetId << offsetPeer << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetDialogs;
    outputStream << flags;
    // (flags & 1 << 0) stands for excludePinned "true" value
    outputStream << offsetDate;
    outputStream << offsetId;
    outputStream << offsetPeer;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getDocumentByHash(const QByteArray &sha256, quint32 size, const QString &mimeType)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << sha256.toHex() << size << mimeType;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetDocumentByHash;
    outputStream << sha256;
    outputStream << size;
    outputStream << mimeType;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getFavedStickers(quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetFavedStickers;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getFeaturedStickers(quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetFeaturedStickers;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getFullChat(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetFullChat;
    outputStream << chatId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getGameHighScores(const TLInputPeer &peer, quint32 id, const TLInputUser &userId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << id << userId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetGameHighScores;
    outputStream << peer;
    outputStream << id;
    outputStream << userId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getHistory(const TLInputPeer &peer, quint32 offsetId, quint32 offsetDate, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId, quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << offsetId << offsetDate << addOffset << limit << maxId << minId << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetHistory;
    outputStream << peer;
    outputStream << offsetId;
    outputStream << offsetDate;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getInlineBotResults(quint32 flags, const TLInputUser &bot, const TLInputPeer &peer, const TLInputGeoPoint &geoPoint, const QString &query, const QString &offset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << bot << peer << geoPoint << query << offset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetInlineBotResults;
    outputStream << flags;
    outputStream << bot;
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << geoPoint;
    }
    outputStream << query;
    outputStream << offset;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getInlineGameHighScores(const TLInputBotInlineMessageID &id, const TLInputUser &userId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id << userId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetInlineGameHighScores;
    outputStream << id;
    outputStream << userId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getMaskStickers(quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetMaskStickers;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getMessageEditData(const TLInputPeer &peer, quint32 id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetMessageEditData;
    outputStream << peer;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getMessages(const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetMessages;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getMessagesViews(const TLInputPeer &peer, const TLVector<quint32> &id, bool increment)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << id << increment;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetMessagesViews;
    outputStream << peer;
    outputStream << id;
    outputStream << increment;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getPeerDialogs(const TLVector<TLInputPeer> &peers)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peers;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetPeerDialogs;
    outputStream << peers;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getPeerSettings(const TLInputPeer &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetPeerSettings;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getPinnedDialogs()
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetPinnedDialogs;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getRecentLocations(const TLInputPeer &peer, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetRecentLocations;
    outputStream << peer;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getRecentStickers(quint32 flags, quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetRecentStickers;
    outputStream << flags;
    // (flags & 1 << 0) stands for attached "true" value
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getSavedGifs(quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetSavedGifs;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getStickerSet(const TLInputStickerSet &stickerset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << stickerset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetStickerSet;
    outputStream << stickerset;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getUnreadMentions(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << offsetId << addOffset << limit << maxId << minId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetUnreadMentions;
    outputStream << peer;
    outputStream << offsetId;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getWebPage(const QString &url, quint32 hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << url << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetWebPage;
    outputStream << url;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getWebPagePreview(const QString &message)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << message;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetWebPagePreview;
    outputStream << message;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::hideReportSpam(const TLInputPeer &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesHideReportSpam;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::importChatInvite(const QString &hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesImportChatInvite;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::installStickerSet(const TLInputStickerSet &stickerset, bool archived)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << stickerset << archived;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesInstallStickerSet;
    outputStream << stickerset;
    outputStream << archived;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::migrateChat(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesMigrateChat;
    outputStream << chatId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::readEncryptedHistory(const TLInputEncryptedChat &peer, quint32 maxDate)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << maxDate;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadEncryptedHistory;
    outputStream << peer;
    outputStream << maxDate;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::readFeaturedStickers(const TLVector<quint64> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadFeaturedStickers;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::readHistory(const TLInputPeer &peer, quint32 maxId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadHistory;
    outputStream << peer;
    outputStream << maxId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::readMentions(const TLInputPeer &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadMentions;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::readMessageContents(const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadMessageContents;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::receivedMessages(quint32 maxId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReceivedMessages;
    outputStream << maxId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::receivedQueue(quint32 maxQts)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << maxQts;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReceivedQueue;
    outputStream << maxQts;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::reorderPinnedDialogs(quint32 flags, const TLVector<TLInputPeer> &order)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << order;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReorderPinnedDialogs;
    outputStream << flags;
    // (flags & 1 << 0) stands for force "true" value
    outputStream << order;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::reorderStickerSets(quint32 flags, const TLVector<quint64> &order)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << order;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReorderStickerSets;
    outputStream << flags;
    // (flags & 1 << 0) stands for masks "true" value
    outputStream << order;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::reportEncryptedSpam(const TLInputEncryptedChat &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReportEncryptedSpam;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::reportSpam(const TLInputPeer &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReportSpam;
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::requestEncryption(const TLInputUser &userId, quint32 randomId, const QByteArray &gA)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << userId << randomId << gA.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesRequestEncryption;
    outputStream << userId;
    outputStream << randomId;
    outputStream << gA;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::saveDraft(quint32 flags, quint32 replyToMsgId, const TLInputPeer &peer, const QString &message, const TLVector<TLMessageEntity> &entities)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << replyToMsgId << peer << message << entities;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSaveDraft;
    outputStream << flags;
    // (flags & 1 << 1) stands for noWebpage "true" value
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << peer;
    outputStream << message;
    if (flags & 1 << 3) {
        outputStream << entities;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::saveGif(const TLInputDocument &id, bool unsave)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id << unsave;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSaveGif;
    outputStream << id;
    outputStream << unsave;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::saveRecentSticker(quint32 flags, const TLInputDocument &id, bool unsave)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << id << unsave;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSaveRecentSticker;
    outputStream << flags;
    // (flags & 1 << 0) stands for attached "true" value
    outputStream << id;
    outputStream << unsave;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::search(quint32 flags, const TLInputPeer &peer, const QString &q, const TLInputUser &fromId, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << q << fromId << filter << minDate << maxDate << offsetId << addOffset << limit << maxId << minId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSearch;
    outputStream << flags;
    outputStream << peer;
    outputStream << q;
    if (flags & 1 << 0) {
        outputStream << fromId;
    }
    outputStream << filter;
    outputStream << minDate;
    outputStream << maxDate;
    outputStream << offsetId;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::searchGifs(const QString &q, quint32 offset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << q << offset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSearchGifs;
    outputStream << q;
    outputStream << offset;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::searchGlobal(const QString &q, quint32 offsetDate, const TLInputPeer &offsetPeer, quint32 offsetId, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << q << offsetDate << offsetPeer << offsetId << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSearchGlobal;
    outputStream << q;
    outputStream << offsetDate;
    outputStream << offsetPeer;
    outputStream << offsetId;
    outputStream << limit;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendEncrypted(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << randomId << data.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendEncrypted;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendEncryptedFile(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data, const TLInputEncryptedFile &file)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << randomId << data.toHex() << file;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendEncryptedFile;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    outputStream << file;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendEncryptedService(const TLInputEncryptedChat &peer, quint64 randomId, const QByteArray &data)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << randomId << data.toHex();
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendEncryptedService;
    outputStream << peer;
    outputStream << randomId;
    outputStream << data;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendInlineBotResult(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId, quint64 queryId, const QString &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << replyToMsgId << randomId << queryId << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendInlineBotResult;
    outputStream << flags;
    // (flags & 1 << 5) stands for silent "true" value
    // (flags & 1 << 6) stands for background "true" value
    // (flags & 1 << 7) stands for clearDraft "true" value
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << randomId;
    outputStream << queryId;
    outputStream << id;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendMedia(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const TLInputMedia &media, quint64 randomId, const TLReplyMarkup &replyMarkup)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << replyToMsgId << media << randomId << replyMarkup;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendMedia;
    outputStream << flags;
    // (flags & 1 << 5) stands for silent "true" value
    // (flags & 1 << 6) stands for background "true" value
    // (flags & 1 << 7) stands for clearDraft "true" value
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << media;
    outputStream << randomId;
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendMessage(quint32 flags, const TLInputPeer &peer, quint32 replyToMsgId, const QString &message, quint64 randomId, const TLReplyMarkup &replyMarkup, const TLVector<TLMessageEntity> &entities)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << replyToMsgId << message << randomId << replyMarkup << entities;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendMessage;
    outputStream << flags;
    // (flags & 1 << 1) stands for noWebpage "true" value
    // (flags & 1 << 5) stands for silent "true" value
    // (flags & 1 << 6) stands for background "true" value
    // (flags & 1 << 7) stands for clearDraft "true" value
    outputStream << peer;
    if (flags & 1 << 0) {
        outputStream << replyToMsgId;
    }
    outputStream << message;
    outputStream << randomId;
    if (flags & 1 << 2) {
        outputStream << replyMarkup;
    }
    if (flags & 1 << 3) {
        outputStream << entities;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::sendScreenshotNotification(const TLInputPeer &peer, quint32 replyToMsgId, quint64 randomId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << replyToMsgId << randomId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendScreenshotNotification;
    outputStream << peer;
    outputStream << replyToMsgId;
    outputStream << randomId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setBotCallbackAnswer(quint32 flags, quint64 queryId, const QString &message, const QString &url, quint32 cacheTime)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << queryId << message << url << cacheTime;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetBotCallbackAnswer;
    outputStream << flags;
    // (flags & 1 << 1) stands for alert "true" value
    outputStream << queryId;
    if (flags & 1 << 0) {
        outputStream << message;
    }
    if (flags & 1 << 2) {
        outputStream << url;
    }
    outputStream << cacheTime;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setBotPrecheckoutResults(quint32 flags, quint64 queryId, const QString &error)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << queryId << error;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetBotPrecheckoutResults;
    outputStream << flags;
    // (flags & 1 << 1) stands for success "true" value
    outputStream << queryId;
    if (flags & 1 << 0) {
        outputStream << error;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setBotShippingResults(quint32 flags, quint64 queryId, const QString &error, const TLVector<TLShippingOption> &shippingOptions)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << queryId << error << shippingOptions;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetBotShippingResults;
    outputStream << flags;
    outputStream << queryId;
    if (flags & 1 << 0) {
        outputStream << error;
    }
    if (flags & 1 << 1) {
        outputStream << shippingOptions;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setEncryptedTyping(const TLInputEncryptedChat &peer, bool typing)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << typing;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetEncryptedTyping;
    outputStream << peer;
    outputStream << typing;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setGameScore(quint32 flags, const TLInputPeer &peer, quint32 id, const TLInputUser &userId, quint32 score)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << id << userId << score;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetGameScore;
    outputStream << flags;
    // (flags & 1 << 0) stands for editMessage "true" value
    // (flags & 1 << 1) stands for force "true" value
    outputStream << peer;
    outputStream << id;
    outputStream << userId;
    outputStream << score;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setInlineBotResults(quint32 flags, quint64 queryId, const TLVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset, const TLInlineBotSwitchPM &switchPm)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << queryId << results << cacheTime << nextOffset << switchPm;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetInlineBotResults;
    outputStream << flags;
    // (flags & 1 << 0) stands for gallery "true" value
    // (flags & 1 << 1) stands for isPrivate "true" value
    outputStream << queryId;
    outputStream << results;
    outputStream << cacheTime;
    if (flags & 1 << 2) {
        outputStream << nextOffset;
    }
    if (flags & 1 << 3) {
        outputStream << switchPm;
    }
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setInlineGameScore(quint32 flags, const TLInputBotInlineMessageID &id, const TLInputUser &userId, quint32 score)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << id << userId << score;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetInlineGameScore;
    outputStream << flags;
    // (flags & 1 << 0) stands for editMessage "true" value
    // (flags & 1 << 1) stands for force "true" value
    outputStream << id;
    outputStream << userId;
    outputStream << score;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setTyping(const TLInputPeer &peer, const TLSendMessageAction &action)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << action;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetTyping;
    outputStream << peer;
    outputStream << action;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::startBot(const TLInputUser &bot, const TLInputPeer &peer, quint64 randomId, const QString &startParam)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << bot << peer << randomId << startParam;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesStartBot;
    outputStream << bot;
    outputStream << peer;
    outputStream << randomId;
    outputStream << startParam;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::toggleChatAdmins(quint32 chatId, bool enabled)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId << enabled;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesToggleChatAdmins;
    outputStream << chatId;
    outputStream << enabled;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::toggleDialogPin(quint32 flags, const TLInputPeer &peer)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesToggleDialogPin;
    outputStream << flags;
    // (flags & 1 << 0) stands for pinned "true" value
    outputStream << peer;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::uninstallStickerSet(const TLInputStickerSet &stickerset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << stickerset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesUninstallStickerSet;
    outputStream << stickerset;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::uploadMedia(const TLInputPeer &peer, const TLInputMedia &media)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << media;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesUploadMedia;
    outputStream << peer;
    outputStream << media;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
