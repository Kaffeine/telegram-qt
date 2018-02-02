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
#include "PendingOperation.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcMessagesCategory, "telegram.client.rpclayer.messages", QtDebugMsg)

namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAffectedHistory *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAffectedMessages *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesAllStickers *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesBotResults *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesChatFull *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesChats *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesDhConfig *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesDialogs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFilter *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesFoundGifs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesMessages *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesSavedGifs *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesSentEncryptedMessage *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLMessagesStickerSet *output);
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

PendingRpcOperation *MessagesRpcLayer::deleteHistory(const TLInputPeer &peer, quint32 maxId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDeleteHistory;
    outputStream << peer;
    outputStream << maxId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::deleteMessages(const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesDeleteMessages;
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

PendingRpcOperation *MessagesRpcLayer::exportChatInvite(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesExportChatInvite;
    outputStream << chatId;
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
    // (flags & 1 << 4) stands for broadcast "true" value
    outputStream << fromPeer;
    outputStream << id;
    outputStream << randomId;
    outputStream << toPeer;
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

PendingRpcOperation *MessagesRpcLayer::getChats(const TLVector<quint32> &id)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetChats;
    outputStream << id;
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

PendingRpcOperation *MessagesRpcLayer::getDialogs(quint32 offsetDate, quint32 offsetId, const TLInputPeer &offsetPeer, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << offsetDate << offsetId << offsetPeer << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetDialogs;
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

PendingRpcOperation *MessagesRpcLayer::getFullChat(quint32 chatId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << chatId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetFullChat;
    outputStream << chatId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getHistory(const TLInputPeer &peer, quint32 offsetId, quint32 addOffset, quint32 limit, quint32 maxId, quint32 minId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << offsetId << addOffset << limit << maxId << minId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetHistory;
    outputStream << peer;
    outputStream << offsetId;
    outputStream << addOffset;
    outputStream << limit;
    outputStream << maxId;
    outputStream << minId;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::getInlineBotResults(const TLInputUser &bot, const QString &query, const QString &offset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << bot << query << offset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetInlineBotResults;
    outputStream << bot;
    outputStream << query;
    outputStream << offset;
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

PendingRpcOperation *MessagesRpcLayer::getStickers(const QString &emoticon, const QString &hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << emoticon << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesGetStickers;
    outputStream << emoticon;
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

PendingRpcOperation *MessagesRpcLayer::importChatInvite(const QString &hash)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << hash;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesImportChatInvite;
    outputStream << hash;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::installStickerSet(const TLInputStickerSet &stickerset, bool disabled)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << stickerset << disabled;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesInstallStickerSet;
    outputStream << stickerset;
    outputStream << disabled;
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

PendingRpcOperation *MessagesRpcLayer::readHistory(const TLInputPeer &peer, quint32 maxId)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << maxId;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReadHistory;
    outputStream << peer;
    outputStream << maxId;
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

PendingRpcOperation *MessagesRpcLayer::reorderStickerSets(const TLVector<quint64> &order)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << order;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesReorderStickerSets;
    outputStream << order;
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

PendingRpcOperation *MessagesRpcLayer::saveGif(const TLInputDocument &id, bool unsave)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << id << unsave;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSaveGif;
    outputStream << id;
    outputStream << unsave;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::search(quint32 flags, const TLInputPeer &peer, const QString &q, const TLMessagesFilter &filter, quint32 minDate, quint32 maxDate, quint32 offset, quint32 maxId, quint32 limit)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << peer << q << filter << minDate << maxDate << offset << maxId << limit;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSearch;
    outputStream << flags;
    // (flags & 1 << 0) stands for importantOnly "true" value
    outputStream << peer;
    outputStream << q;
    outputStream << filter;
    outputStream << minDate;
    outputStream << maxDate;
    outputStream << offset;
    outputStream << maxId;
    outputStream << limit;
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

PendingRpcOperation *MessagesRpcLayer::sendBroadcast(const TLVector<TLInputUser> &contacts, const TLVector<quint64> &randomId, const QString &message, const TLInputMedia &media)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << contacts << randomId << message << media;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSendBroadcast;
    outputStream << contacts;
    outputStream << randomId;
    outputStream << message;
    outputStream << media;
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
    // (flags & 1 << 4) stands for broadcast "true" value
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
    // (flags & 1 << 4) stands for broadcast "true" value
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
    // (flags & 1 << 4) stands for broadcast "true" value
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

PendingRpcOperation *MessagesRpcLayer::setEncryptedTyping(const TLInputEncryptedChat &peer, bool typing)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << peer << typing;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesSetEncryptedTyping;
    outputStream << peer;
    outputStream << typing;
    return sendEncryptedPackage(outputStream.getData());
}

PendingRpcOperation *MessagesRpcLayer::setInlineBotResults(quint32 flags, quint64 queryId, const TLVector<TLInputBotInlineResult> &results, quint32 cacheTime, const QString &nextOffset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << flags << queryId << results << cacheTime << nextOffset;
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

PendingRpcOperation *MessagesRpcLayer::uninstallStickerSet(const TLInputStickerSet &stickerset)
{
    qCDebug(c_clientRpcMessagesCategory) << Q_FUNC_INFO << stickerset;
    CTelegramStream outputStream(CTelegramStream::WriteOnly);
    outputStream << TLValue::MessagesUninstallStickerSet;
    outputStream << stickerset;
    return sendEncryptedPackage(outputStream.getData());
}
// End of generated Telegram API definitions

} // Client namespace

} // Telegram namespace
