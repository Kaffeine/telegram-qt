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

#include "ClientRpcUsersLayer.hpp"
#include "ClientRpcLayerExtension_p.hpp"
#include "MTProto/Stream.hpp"
#include "MTProto/TLTypesDebug.hpp"
#include "Debug_p.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(c_clientRpcUsersCategory, "telegram.client.rpclayer.users", QtWarningMsg)

#include "PendingRpcOperation.hpp"


namespace Telegram {

namespace Client {

// Generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUser *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUserFull *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUserProfilePhoto *output);
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLUserStatus *output);
// End of generated Telegram API reply template specializations
template bool BaseRpcLayerExtension::processReply(PendingRpcOperation *operation, TLVector<TLUser> *output);

UsersRpcLayer::UsersRpcLayer(QObject *parent) :
    BaseRpcLayerExtension(parent)
{
}

// Generated Telegram API definitions
UsersRpcLayer::PendingUserFull *UsersRpcLayer::getFullUser(const TLInputUser &id)
{
    qCDebug(c_clientRpcUsersCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UsersGetFullUser;
    outputStream << id;
    PendingUserFull *op = new PendingUserFull(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UsersRpcLayer::PendingUserVector *UsersRpcLayer::getUsers(const TLVector<TLInputUser> &id)
{
    qCDebug(c_clientRpcUsersCategory) << Q_FUNC_INFO << id;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UsersGetUsers;
    outputStream << id;
    PendingUserVector *op = new PendingUserVector(this, outputStream.getData());
    processRpcCall(op);
    return op;
}

UsersRpcLayer::PendingBool *UsersRpcLayer::setSecureValueErrors(const TLInputUser &id, const TLVector<TLSecureValueError> &errors)
{
    qCDebug(c_clientRpcUsersCategory) << Q_FUNC_INFO << id << errors;
    MTProto::Stream outputStream(MTProto::Stream::WriteOnly);
    outputStream << TLValue::UsersSetSecureValueErrors;
    outputStream << id;
    outputStream << errors;
    PendingBool *op = new PendingBool(this, outputStream.getData());
    processRpcCall(op);
    return op;
}
// End of generated Telegram API definitions


//processGetFullUser()
//{
//    if (!operation->isSucceeded()) {
//        setDelayedFinishedWithError(operation->errorDetails());
//        return;
//    }
//    TLUserFull result;
//    authLayer()->processReply(operation, &result);
//    qDebug() << Q_FUNC_INFO << result.tlType << result.phoneCodeHash;
//    if (result.isValid()) {
//        m_authCodeHash = result.phoneCodeHash;
//        emit authCodeRequired();
//    }
//}

} // Client namespace

} // Telegram namespace
