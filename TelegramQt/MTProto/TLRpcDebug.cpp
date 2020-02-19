/*
   Copyright (C) 2017 Alexandr Akulich <akulichalexander@gmail.com>

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

#include "TLRpcDebug.hpp"

#include "TLTypesDebug.hpp"
#include "Debug_p.hpp"
#include "telegramqt_macros.h"

#include "Stream.hpp"

using namespace Telegram::Debug;

namespace Telegram {

namespace MTProto {

void dumpRpc(Stream &stream)
{
    TLValue request;
    stream >> request;

    QDebug d = qDebug();
    d.nospace();

    switch (request) {
    case TLValue::MsgContainer: {
        quint32 itemsCount;
        stream >> itemsCount;

        qDebug() << request << "items" << itemsCount;
        for (quint32 i = 0; i < itemsCount; ++i) {
            quint64 id;
            stream >> id;
            //todo: ack
            quint32 seqNo;
            stream >> seqNo;
            quint32 size;
            stream >> size;

            const QByteArray data = stream.readBytes(size);
            Stream innerStream(data);
            dumpRpc(innerStream);
        }
        break;
    }
    case TLValue::InvokeWithLayer: {
        quint32 layer = 0;
        stream >> layer;
        qDebug() << request << "layer" << layer;
        dumpRpc(stream);
        break;
    }
    case TLValue::InitConnection: {
        quint32 appId;
        QString deviceInfo;
        QString osInfo;
        QString appVersion;
        QString languageCode;
        stream >> appId;
        stream >> deviceInfo;
        stream >> osInfo;
        stream >> appVersion;
        stream >> languageCode;

        qDebug() << request << "appId" << appId << "deviceInfo" << deviceInfo;
        dumpRpc(stream);
        break;
    }
    // Generated RPC debug cases
    case TLValue::AccountAcceptAuthorization:
        d << "AccountAcceptAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 botId;
        stream >> botId;
        d << spacer.innerSpaces() << "botId: " << botId << TELEGRAMQT_ENDL;
        QString scope;
        stream >> scope;
        d << spacer.innerSpaces() << "scope: " << scope << TELEGRAMQT_ENDL;
        QString publicKey;
        stream >> publicKey;
        d << spacer.innerSpaces() << "publicKey: " << publicKey << TELEGRAMQT_ENDL;
        QVector<TLSecureValueHash> valueHashes;
        stream >> valueHashes;
        d << spacer.innerSpaces() << "valueHashes: " << valueHashes << TELEGRAMQT_ENDL;
        TLSecureCredentialsEncrypted credentials;
        stream >> credentials;
        d << spacer.innerSpaces() << "credentials: " << credentials << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountCancelPasswordEmail:
        d << "AccountCancelPasswordEmail(";
        d << ")";
        break;
    case TLValue::AccountChangePhone:
        d << "AccountChangePhone(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountCheckUsername:
        d << "AccountCheckUsername(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountConfirmPasswordEmail:
        d << "AccountConfirmPasswordEmail(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString code;
        stream >> code;
        d << spacer.innerSpaces() << "code: " << code << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountConfirmPhone:
        d << "AccountConfirmPhone(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountDeleteAccount:
        d << "AccountDeleteAccount(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountDeleteSecureValue:
        d << "AccountDeleteSecureValue(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLSecureValueType> types;
        stream >> types;
        d << spacer.innerSpaces() << "types: " << types << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountFinishTakeoutSession:
        d << "AccountFinishTakeoutSession(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetAccountTTL:
        d << "AccountGetAccountTTL(";
        d << ")";
        break;
    case TLValue::AccountGetAllSecureValues:
        d << "AccountGetAllSecureValues(";
        d << ")";
        break;
    case TLValue::AccountGetAuthorizationForm:
        d << "AccountGetAuthorizationForm(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 botId;
        stream >> botId;
        d << spacer.innerSpaces() << "botId: " << botId << TELEGRAMQT_ENDL;
        QString scope;
        stream >> scope;
        d << spacer.innerSpaces() << "scope: " << scope << TELEGRAMQT_ENDL;
        QString publicKey;
        stream >> publicKey;
        d << spacer.innerSpaces() << "publicKey: " << publicKey << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetAuthorizations:
        d << "AccountGetAuthorizations(";
        d << ")";
        break;
    case TLValue::AccountGetContactSignUpNotification:
        d << "AccountGetContactSignUpNotification(";
        d << ")";
        break;
    case TLValue::AccountGetNotifyExceptions:
        d << "AccountGetNotifyExceptions(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetNotifySettings:
        d << "AccountGetNotifySettings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputNotifyPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetPassword:
        d << "AccountGetPassword(";
        d << ")";
        break;
    case TLValue::AccountGetPasswordSettings:
        d << "AccountGetPasswordSettings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputCheckPasswordSRP password;
        stream >> password;
        d << spacer.innerSpaces() << "password: " << password << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetPrivacy:
        d << "AccountGetPrivacy(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPrivacyKey key;
        stream >> key;
        d << spacer.innerSpaces() << "key: " << key << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetSecureValue:
        d << "AccountGetSecureValue(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLSecureValueType> types;
        stream >> types;
        d << spacer.innerSpaces() << "types: " << types << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetTmpPassword:
        d << "AccountGetTmpPassword(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputCheckPasswordSRP password;
        stream >> password;
        d << spacer.innerSpaces() << "password: " << password << TELEGRAMQT_ENDL;
        quint32 period;
        stream >> period;
        d << spacer.innerSpaces() << "period: " << period << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountGetWallPapers:
        d << "AccountGetWallPapers(";
        d << ")";
        break;
    case TLValue::AccountGetWebAuthorizations:
        d << "AccountGetWebAuthorizations(";
        d << ")";
        break;
    case TLValue::AccountInitTakeoutSession:
        d << "AccountInitTakeoutSession(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountRegisterDevice:
        d << "AccountRegisterDevice(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 tokenType;
        stream >> tokenType;
        d << spacer.innerSpaces() << "tokenType: " << tokenType << TELEGRAMQT_ENDL;
        QString token;
        stream >> token;
        d << spacer.innerSpaces() << "token: " << token << TELEGRAMQT_ENDL;
        bool appSandbox;
        stream >> appSandbox;
        d << spacer.innerSpaces() << "appSandbox: " << appSandbox << TELEGRAMQT_ENDL;
        QByteArray secret;
        stream >> secret;
        d << spacer.innerSpaces() << "secret: " << secret.toHex() << TELEGRAMQT_ENDL;
        QVector<quint32> otherUids;
        stream >> otherUids;
        d << spacer.innerSpaces() << "otherUids: " << otherUids << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountReportPeer:
        d << "AccountReportPeer(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLReportReason reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountResendPasswordEmail:
        d << "AccountResendPasswordEmail(";
        d << ")";
        break;
    case TLValue::AccountResetAuthorization:
        d << "AccountResetAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountResetNotifySettings:
        d << "AccountResetNotifySettings(";
        d << ")";
        break;
    case TLValue::AccountResetWebAuthorization:
        d << "AccountResetWebAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountResetWebAuthorizations:
        d << "AccountResetWebAuthorizations(";
        d << ")";
        break;
    case TLValue::AccountSaveSecureValue:
        d << "AccountSaveSecureValue(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputSecureValue value;
        stream >> value;
        d << spacer.innerSpaces() << "value: " << value << TELEGRAMQT_ENDL;
        quint64 secureSecretId;
        stream >> secureSecretId;
        d << spacer.innerSpaces() << "secureSecretId: " << secureSecretId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSendChangePhoneCode:
        d << "AccountSendChangePhoneCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSendConfirmPhoneCode:
        d << "AccountSendConfirmPhoneCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSendVerifyEmailCode:
        d << "AccountSendVerifyEmailCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString email;
        stream >> email;
        d << spacer.innerSpaces() << "email: " << email << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSendVerifyPhoneCode:
        d << "AccountSendVerifyPhoneCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSetAccountTTL:
        d << "AccountSetAccountTTL(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLAccountDaysTTL ttl;
        stream >> ttl;
        d << spacer.innerSpaces() << "ttl: " << ttl << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSetContactSignUpNotification:
        d << "AccountSetContactSignUpNotification(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        bool silent;
        stream >> silent;
        d << spacer.innerSpaces() << "silent: " << silent << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountSetPrivacy:
        d << "AccountSetPrivacy(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPrivacyKey key;
        stream >> key;
        d << spacer.innerSpaces() << "key: " << key << TELEGRAMQT_ENDL;
        QVector<TLInputPrivacyRule> rules;
        stream >> rules;
        d << spacer.innerSpaces() << "rules: " << rules << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUnregisterDevice:
        d << "AccountUnregisterDevice(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 tokenType;
        stream >> tokenType;
        d << spacer.innerSpaces() << "tokenType: " << tokenType << TELEGRAMQT_ENDL;
        QString token;
        stream >> token;
        d << spacer.innerSpaces() << "token: " << token << TELEGRAMQT_ENDL;
        QVector<quint32> otherUids;
        stream >> otherUids;
        d << spacer.innerSpaces() << "otherUids: " << otherUids << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateDeviceLocked:
        d << "AccountUpdateDeviceLocked(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 period;
        stream >> period;
        d << spacer.innerSpaces() << "period: " << period << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateNotifySettings:
        d << "AccountUpdateNotifySettings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputNotifyPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLInputPeerNotifySettings settings;
        stream >> settings;
        d << spacer.innerSpaces() << "settings: " << settings << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdatePasswordSettings:
        d << "AccountUpdatePasswordSettings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputCheckPasswordSRP password;
        stream >> password;
        d << spacer.innerSpaces() << "password: " << password << TELEGRAMQT_ENDL;
        TLAccountPasswordInputSettings newSettings;
        stream >> newSettings;
        d << spacer.innerSpaces() << "newSettings: " << newSettings << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateProfile:
        d << "AccountUpdateProfile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateStatus:
        d << "AccountUpdateStatus(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        bool offline;
        stream >> offline;
        d << spacer.innerSpaces() << "offline: " << offline << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountUpdateUsername:
        d << "AccountUpdateUsername(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountVerifyEmail:
        d << "AccountVerifyEmail(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString email;
        stream >> email;
        d << spacer.innerSpaces() << "email: " << email << TELEGRAMQT_ENDL;
        QString code;
        stream >> code;
        d << spacer.innerSpaces() << "code: " << code << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AccountVerifyPhone:
        d << "AccountVerifyPhone(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthBindTempAuthKey:
        d << "AuthBindTempAuthKey(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 permAuthKeyId;
        stream >> permAuthKeyId;
        d << spacer.innerSpaces() << "permAuthKeyId: " << permAuthKeyId << TELEGRAMQT_ENDL;
        quint64 nonce;
        stream >> nonce;
        d << spacer.innerSpaces() << "nonce: " << nonce << TELEGRAMQT_ENDL;
        quint32 expiresAt;
        stream >> expiresAt;
        d << spacer.innerSpaces() << "expiresAt: " << expiresAt << TELEGRAMQT_ENDL;
        QByteArray encryptedMessage;
        stream >> encryptedMessage;
        d << spacer.innerSpaces() << "encryptedMessage: " << encryptedMessage.toHex() << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthCancelCode:
        d << "AuthCancelCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthCheckPassword:
        d << "AuthCheckPassword(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputCheckPasswordSRP password;
        stream >> password;
        d << spacer.innerSpaces() << "password: " << password << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthDropTempAuthKeys:
        d << "AuthDropTempAuthKeys(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<quint64> exceptAuthKeys;
        stream >> exceptAuthKeys;
        d << spacer.innerSpaces() << "exceptAuthKeys: " << exceptAuthKeys << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthExportAuthorization:
        d << "AuthExportAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 dcId;
        stream >> dcId;
        d << spacer.innerSpaces() << "dcId: " << dcId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthImportAuthorization:
        d << "AuthImportAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthImportBotAuthorization:
        d << "AuthImportBotAuthorization(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 apiId;
        stream >> apiId;
        d << spacer.innerSpaces() << "apiId: " << apiId << TELEGRAMQT_ENDL;
        QString apiHash;
        stream >> apiHash;
        d << spacer.innerSpaces() << "apiHash: " << apiHash << TELEGRAMQT_ENDL;
        QString botAuthToken;
        stream >> botAuthToken;
        d << spacer.innerSpaces() << "botAuthToken: " << botAuthToken << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthLogOut:
        d << "AuthLogOut(";
        d << ")";
        break;
    case TLValue::AuthRecoverPassword:
        d << "AuthRecoverPassword(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString code;
        stream >> code;
        d << spacer.innerSpaces() << "code: " << code << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthRequestPasswordRecovery:
        d << "AuthRequestPasswordRecovery(";
        d << ")";
        break;
    case TLValue::AuthResendCode:
        d << "AuthResendCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthResetAuthorizations:
        d << "AuthResetAuthorizations(";
        d << ")";
        break;
    case TLValue::AuthSendCode:
        d << "AuthSendCode(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        quint32 apiId;
        stream >> apiId;
        d << spacer.innerSpaces() << "apiId: " << apiId << TELEGRAMQT_ENDL;
        QString apiHash;
        stream >> apiHash;
        d << spacer.innerSpaces() << "apiHash: " << apiHash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthSignIn:
        d << "AuthSignIn(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::AuthSignUp:
        d << "AuthSignUp(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString phoneNumber;
        stream >> phoneNumber;
        d << spacer.innerSpaces() << "phoneNumber: " << phoneNumber << TELEGRAMQT_ENDL;
        QString phoneCodeHash;
        stream >> phoneCodeHash;
        d << spacer.innerSpaces() << "phoneCodeHash: " << phoneCodeHash << TELEGRAMQT_ENDL;
        QString phoneCode;
        stream >> phoneCode;
        d << spacer.innerSpaces() << "phoneCode: " << phoneCode << TELEGRAMQT_ENDL;
        QString firstName;
        stream >> firstName;
        d << spacer.innerSpaces() << "firstName: " << firstName << TELEGRAMQT_ENDL;
        QString lastName;
        stream >> lastName;
        d << spacer.innerSpaces() << "lastName: " << lastName << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::BotsAnswerWebhookJSONQuery:
        d << "BotsAnswerWebhookJSONQuery(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
        TLDataJSON data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::BotsSendCustomRequest:
        d << "BotsSendCustomRequest(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString customMethod;
        stream >> customMethod;
        d << spacer.innerSpaces() << "customMethod: " << customMethod << TELEGRAMQT_ENDL;
        TLDataJSON params;
        stream >> params;
        d << spacer.innerSpaces() << "params: " << params << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsCheckUsername:
        d << "ChannelsCheckUsername(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsCreateChannel:
        d << "ChannelsCreateChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << TELEGRAMQT_ENDL;
        QString about;
        stream >> about;
        d << spacer.innerSpaces() << "about: " << about << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteChannel:
        d << "ChannelsDeleteChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteHistory:
        d << "ChannelsDeleteHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteMessages:
        d << "ChannelsDeleteMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsDeleteUserHistory:
        d << "ChannelsDeleteUserHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditAbout:
        d << "ChannelsEditAbout(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QString about;
        stream >> about;
        d << spacer.innerSpaces() << "about: " << about << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditAdmin:
        d << "ChannelsEditAdmin(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        TLChannelAdminRights adminRights;
        stream >> adminRights;
        d << spacer.innerSpaces() << "adminRights: " << adminRights << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditBanned:
        d << "ChannelsEditBanned(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        TLChannelBannedRights bannedRights;
        stream >> bannedRights;
        d << spacer.innerSpaces() << "bannedRights: " << bannedRights << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditPhoto:
        d << "ChannelsEditPhoto(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputChatPhoto photo;
        stream >> photo;
        d << spacer.innerSpaces() << "photo: " << photo << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsEditTitle:
        d << "ChannelsEditTitle(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsExportInvite:
        d << "ChannelsExportInvite(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsExportMessageLink:
        d << "ChannelsExportMessageLink(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        bool grouped;
        stream >> grouped;
        d << spacer.innerSpaces() << "grouped: " << grouped << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetAdminLog:
        d << "ChannelsGetAdminLog(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        quint64 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint64 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetAdminedPublicChannels:
        d << "ChannelsGetAdminedPublicChannels(";
        d << ")";
        break;
    case TLValue::ChannelsGetChannels:
        d << "ChannelsGetChannels(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputChannel> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetFullChannel:
        d << "ChannelsGetFullChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetLeftChannels:
        d << "ChannelsGetLeftChannels(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetMessages:
        d << "ChannelsGetMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QVector<TLInputMessage> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetParticipant:
        d << "ChannelsGetParticipant(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsGetParticipants:
        d << "ChannelsGetParticipants(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLChannelParticipantsFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsInviteToChannel:
        d << "ChannelsInviteToChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QVector<TLInputUser> users;
        stream >> users;
        d << spacer.innerSpaces() << "users: " << users << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsJoinChannel:
        d << "ChannelsJoinChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsLeaveChannel:
        d << "ChannelsLeaveChannel(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsReadHistory:
        d << "ChannelsReadHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsReadMessageContents:
        d << "ChannelsReadMessageContents(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsReportSpam:
        d << "ChannelsReportSpam(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsSetStickers:
        d << "ChannelsSetStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsToggleInvites:
        d << "ChannelsToggleInvites(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsTogglePreHistoryHidden:
        d << "ChannelsTogglePreHistoryHidden(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsToggleSignatures:
        d << "ChannelsToggleSignatures(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ChannelsUpdateUsername:
        d << "ChannelsUpdateUsername(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsBlock:
        d << "ContactsBlock(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsDeleteByPhones:
        d << "ContactsDeleteByPhones(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<QString> phones;
        stream >> phones;
        d << spacer.innerSpaces() << "phones: " << phones << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsDeleteContact:
        d << "ContactsDeleteContact(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsDeleteContacts:
        d << "ContactsDeleteContacts(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputUser> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsGetBlocked:
        d << "ContactsGetBlocked(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsGetContactIDs:
        d << "ContactsGetContactIDs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsGetContacts:
        d << "ContactsGetContacts(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsGetSaved:
        d << "ContactsGetSaved(";
        d << ")";
        break;
    case TLValue::ContactsGetStatuses:
        d << "ContactsGetStatuses(";
        d << ")";
        break;
    case TLValue::ContactsGetTopPeers:
        d << "ContactsGetTopPeers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsImportContacts:
        d << "ContactsImportContacts(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputContact> contacts;
        stream >> contacts;
        d << spacer.innerSpaces() << "contacts: " << contacts << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsResetSaved:
        d << "ContactsResetSaved(";
        d << ")";
        break;
    case TLValue::ContactsResetTopPeerRating:
        d << "ContactsResetTopPeerRating(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLTopPeerCategory category;
        stream >> category;
        d << spacer.innerSpaces() << "category: " << category << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsResolveUsername:
        d << "ContactsResolveUsername(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString username;
        stream >> username;
        d << spacer.innerSpaces() << "username: " << username << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsSearch:
        d << "ContactsSearch(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsToggleTopPeers:
        d << "ContactsToggleTopPeers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::ContactsUnblock:
        d << "ContactsUnblock(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpAcceptTermsOfService:
        d << "HelpAcceptTermsOfService(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLDataJSON id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpEditUserInfo:
        d << "HelpEditUserInfo(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
        QVector<TLMessageEntity> entities;
        stream >> entities;
        d << spacer.innerSpaces() << "entities: " << entities << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetAppChangelog:
        d << "HelpGetAppChangelog(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString prevAppVersion;
        stream >> prevAppVersion;
        d << spacer.innerSpaces() << "prevAppVersion: " << prevAppVersion << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetAppConfig:
        d << "HelpGetAppConfig(";
        d << ")";
        break;
    case TLValue::HelpGetAppUpdate:
        d << "HelpGetAppUpdate(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString source;
        stream >> source;
        d << spacer.innerSpaces() << "source: " << source << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetCdnConfig:
        d << "HelpGetCdnConfig(";
        d << ")";
        break;
    case TLValue::HelpGetConfig:
        d << "HelpGetConfig(";
        d << ")";
        break;
    case TLValue::HelpGetDeepLinkInfo:
        d << "HelpGetDeepLinkInfo(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString path;
        stream >> path;
        d << spacer.innerSpaces() << "path: " << path << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetInviteText:
        d << "HelpGetInviteText(";
        d << ")";
        break;
    case TLValue::HelpGetNearestDc:
        d << "HelpGetNearestDc(";
        d << ")";
        break;
    case TLValue::HelpGetPassportConfig:
        d << "HelpGetPassportConfig(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetProxyData:
        d << "HelpGetProxyData(";
        d << ")";
        break;
    case TLValue::HelpGetRecentMeUrls:
        d << "HelpGetRecentMeUrls(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString referer;
        stream >> referer;
        d << spacer.innerSpaces() << "referer: " << referer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpGetSupport:
        d << "HelpGetSupport(";
        d << ")";
        break;
    case TLValue::HelpGetSupportName:
        d << "HelpGetSupportName(";
        d << ")";
        break;
    case TLValue::HelpGetTermsOfServiceUpdate:
        d << "HelpGetTermsOfServiceUpdate(";
        d << ")";
        break;
    case TLValue::HelpGetUserInfo:
        d << "HelpGetUserInfo(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpSaveAppLog:
        d << "HelpSaveAppLog(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputAppEvent> events;
        stream >> events;
        d << spacer.innerSpaces() << "events: " << events << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::HelpSetBotUpdatesStatus:
        d << "HelpSetBotUpdatesStatus(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 pendingUpdatesCount;
        stream >> pendingUpdatesCount;
        d << spacer.innerSpaces() << "pendingUpdatesCount: " << pendingUpdatesCount << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::LangpackGetDifference:
        d << "LangpackGetDifference(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << TELEGRAMQT_ENDL;
        quint32 fromVersion;
        stream >> fromVersion;
        d << spacer.innerSpaces() << "fromVersion: " << fromVersion << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::LangpackGetLangPack:
        d << "LangpackGetLangPack(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString langPack;
        stream >> langPack;
        d << spacer.innerSpaces() << "langPack: " << langPack << TELEGRAMQT_ENDL;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::LangpackGetLanguage:
        d << "LangpackGetLanguage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString langPack;
        stream >> langPack;
        d << spacer.innerSpaces() << "langPack: " << langPack << TELEGRAMQT_ENDL;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::LangpackGetLanguages:
        d << "LangpackGetLanguages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString langPack;
        stream >> langPack;
        d << spacer.innerSpaces() << "langPack: " << langPack << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::LangpackGetStrings:
        d << "LangpackGetStrings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString langPack;
        stream >> langPack;
        d << spacer.innerSpaces() << "langPack: " << langPack << TELEGRAMQT_ENDL;
        QString langCode;
        stream >> langCode;
        d << spacer.innerSpaces() << "langCode: " << langCode << TELEGRAMQT_ENDL;
        QVector<QString> keys;
        stream >> keys;
        d << spacer.innerSpaces() << "keys: " << keys << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesAcceptEncryption:
        d << "MessagesAcceptEncryption(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QByteArray gB;
        stream >> gB;
        d << spacer.innerSpaces() << "gB: " << gB.toHex() << TELEGRAMQT_ENDL;
        quint64 keyFingerprint;
        stream >> keyFingerprint;
        d << spacer.innerSpaces() << "keyFingerprint: " << keyFingerprint << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesAddChatUser:
        d << "MessagesAddChatUser(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 fwdLimit;
        stream >> fwdLimit;
        d << spacer.innerSpaces() << "fwdLimit: " << fwdLimit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesCheckChatInvite:
        d << "MessagesCheckChatInvite(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesClearAllDrafts:
        d << "MessagesClearAllDrafts(";
        d << ")";
        break;
    case TLValue::MessagesClearRecentStickers:
        d << "MessagesClearRecentStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesCreateChat:
        d << "MessagesCreateChat(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputUser> users;
        stream >> users;
        d << spacer.innerSpaces() << "users: " << users << TELEGRAMQT_ENDL;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteChatUser:
        d << "MessagesDeleteChatUser(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteHistory:
        d << "MessagesDeleteHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesDeleteMessages:
        d << "MessagesDeleteMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesDiscardEncryption:
        d << "MessagesDiscardEncryption(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatAdmin:
        d << "MessagesEditChatAdmin(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        bool isAdmin;
        stream >> isAdmin;
        d << spacer.innerSpaces() << "isAdmin: " << isAdmin << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatPhoto:
        d << "MessagesEditChatPhoto(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        TLInputChatPhoto photo;
        stream >> photo;
        d << spacer.innerSpaces() << "photo: " << photo << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesEditChatTitle:
        d << "MessagesEditChatTitle(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesEditInlineBotMessage:
        d << "MessagesEditInlineBotMessage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesEditMessage:
        d << "MessagesEditMessage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesExportChatInvite:
        d << "MessagesExportChatInvite(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesFaveSticker:
        d << "MessagesFaveSticker(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        bool unfave;
        stream >> unfave;
        d << spacer.innerSpaces() << "unfave: " << unfave << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesForwardMessages:
        d << "MessagesForwardMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer fromPeer;
        stream >> fromPeer;
        d << spacer.innerSpaces() << "fromPeer: " << fromPeer << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        QVector<quint64> randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        TLInputPeer toPeer;
        stream >> toPeer;
        d << spacer.innerSpaces() << "toPeer: " << toPeer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAllChats:
        d << "MessagesGetAllChats(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<quint32> exceptIds;
        stream >> exceptIds;
        d << spacer.innerSpaces() << "exceptIds: " << exceptIds << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAllDrafts:
        d << "MessagesGetAllDrafts(";
        d << ")";
        break;
    case TLValue::MessagesGetAllStickers:
        d << "MessagesGetAllStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetArchivedStickers:
        d << "MessagesGetArchivedStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint64 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetAttachedStickers:
        d << "MessagesGetAttachedStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputStickeredMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetBotCallbackAnswer:
        d << "MessagesGetBotCallbackAnswer(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetChats:
        d << "MessagesGetChats(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetCommonChats:
        d << "MessagesGetCommonChats(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDhConfig:
        d << "MessagesGetDhConfig(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 version;
        stream >> version;
        d << spacer.innerSpaces() << "version: " << version << TELEGRAMQT_ENDL;
        quint32 randomLength;
        stream >> randomLength;
        d << spacer.innerSpaces() << "randomLength: " << randomLength << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDialogUnreadMarks:
        d << "MessagesGetDialogUnreadMarks(";
        d << ")";
        break;
    case TLValue::MessagesGetDialogs:
        d << "MessagesGetDialogs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << TELEGRAMQT_ENDL;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        d << spacer.innerSpaces() << "offsetPeer: " << offsetPeer << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetDocumentByHash:
        d << "MessagesGetDocumentByHash(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QByteArray sha256;
        stream >> sha256;
        d << spacer.innerSpaces() << "sha256: " << sha256.toHex() << TELEGRAMQT_ENDL;
        quint32 size;
        stream >> size;
        d << spacer.innerSpaces() << "size: " << size << TELEGRAMQT_ENDL;
        QString mimeType;
        stream >> mimeType;
        d << spacer.innerSpaces() << "mimeType: " << mimeType << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFavedStickers:
        d << "MessagesGetFavedStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFeaturedStickers:
        d << "MessagesGetFeaturedStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetFullChat:
        d << "MessagesGetFullChat(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetGameHighScores:
        d << "MessagesGetGameHighScores(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetHistory:
        d << "MessagesGetHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << TELEGRAMQT_ENDL;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetInlineBotResults:
        d << "MessagesGetInlineBotResults(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputUser bot;
        stream >> bot;
        d << spacer.innerSpaces() << "bot: " << bot << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QString query;
        stream >> query;
        d << spacer.innerSpaces() << "query: " << query << TELEGRAMQT_ENDL;
        QString offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetInlineGameHighScores:
        d << "MessagesGetInlineGameHighScores(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMaskStickers:
        d << "MessagesGetMaskStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessageEditData:
        d << "MessagesGetMessageEditData(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessages:
        d << "MessagesGetMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputMessage> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetMessagesViews:
        d << "MessagesGetMessagesViews(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        bool increment;
        stream >> increment;
        d << spacer.innerSpaces() << "increment: " << increment << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetOnlines:
        d << "MessagesGetOnlines(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPeerDialogs:
        d << "MessagesGetPeerDialogs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputDialogPeer> peers;
        stream >> peers;
        d << spacer.innerSpaces() << "peers: " << peers << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPeerSettings:
        d << "MessagesGetPeerSettings(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetPinnedDialogs:
        d << "MessagesGetPinnedDialogs(";
        d << ")";
        break;
    case TLValue::MessagesGetPollResults:
        d << "MessagesGetPollResults(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetRecentLocations:
        d << "MessagesGetRecentLocations(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetRecentStickers:
        d << "MessagesGetRecentStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetSavedGifs:
        d << "MessagesGetSavedGifs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetSplitRanges:
        d << "MessagesGetSplitRanges(";
        d << ")";
        break;
    case TLValue::MessagesGetStatsURL:
        d << "MessagesGetStatsURL(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetStickerSet:
        d << "MessagesGetStickerSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetStickers:
        d << "MessagesGetStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString emoticon;
        stream >> emoticon;
        d << spacer.innerSpaces() << "emoticon: " << emoticon << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetUnreadMentions:
        d << "MessagesGetUnreadMentions(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetWebPage:
        d << "MessagesGetWebPage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString url;
        stream >> url;
        d << spacer.innerSpaces() << "url: " << url << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesGetWebPagePreview:
        d << "MessagesGetWebPagePreview(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesHideReportSpam:
        d << "MessagesHideReportSpam(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesImportChatInvite:
        d << "MessagesImportChatInvite(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesInstallStickerSet:
        d << "MessagesInstallStickerSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << TELEGRAMQT_ENDL;
        bool archived;
        stream >> archived;
        d << spacer.innerSpaces() << "archived: " << archived << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesMarkDialogUnread:
        d << "MessagesMarkDialogUnread(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputDialogPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesMigrateChat:
        d << "MessagesMigrateChat(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReadEncryptedHistory:
        d << "MessagesReadEncryptedHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 maxDate;
        stream >> maxDate;
        d << spacer.innerSpaces() << "maxDate: " << maxDate << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReadFeaturedStickers:
        d << "MessagesReadFeaturedStickers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<quint64> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReadHistory:
        d << "MessagesReadHistory(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReadMentions:
        d << "MessagesReadMentions(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReadMessageContents:
        d << "MessagesReadMessageContents(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReceivedMessages:
        d << "MessagesReceivedMessages(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReceivedQueue:
        d << "MessagesReceivedQueue(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 maxQts;
        stream >> maxQts;
        d << spacer.innerSpaces() << "maxQts: " << maxQts << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReorderPinnedDialogs:
        d << "MessagesReorderPinnedDialogs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QVector<TLInputDialogPeer> order;
        stream >> order;
        d << spacer.innerSpaces() << "order: " << order << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReorderStickerSets:
        d << "MessagesReorderStickerSets(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QVector<quint64> order;
        stream >> order;
        d << spacer.innerSpaces() << "order: " << order << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReport:
        d << "MessagesReport(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QVector<quint32> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        TLReportReason reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReportEncryptedSpam:
        d << "MessagesReportEncryptedSpam(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesReportSpam:
        d << "MessagesReportSpam(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesRequestEncryption:
        d << "MessagesRequestEncryption(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QByteArray gA;
        stream >> gA;
        d << spacer.innerSpaces() << "gA: " << gA.toHex() << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveDraft:
        d << "MessagesSaveDraft(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveGif:
        d << "MessagesSaveGif(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        bool unsave;
        stream >> unsave;
        d << spacer.innerSpaces() << "unsave: " << unsave << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSaveRecentSticker:
        d << "MessagesSaveRecentSticker(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputDocument id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        bool unsave;
        stream >> unsave;
        d << spacer.innerSpaces() << "unsave: " << unsave << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSearch:
        d << "MessagesSearch(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        TLMessagesFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << TELEGRAMQT_ENDL;
        quint32 minDate;
        stream >> minDate;
        d << spacer.innerSpaces() << "minDate: " << minDate << TELEGRAMQT_ENDL;
        quint32 maxDate;
        stream >> maxDate;
        d << spacer.innerSpaces() << "maxDate: " << maxDate << TELEGRAMQT_ENDL;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        quint32 addOffset;
        stream >> addOffset;
        d << spacer.innerSpaces() << "addOffset: " << addOffset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
        quint32 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint32 minId;
        stream >> minId;
        d << spacer.innerSpaces() << "minId: " << minId << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSearchGifs:
        d << "MessagesSearchGifs(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSearchGlobal:
        d << "MessagesSearchGlobal(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        quint32 offsetDate;
        stream >> offsetDate;
        d << spacer.innerSpaces() << "offsetDate: " << offsetDate << TELEGRAMQT_ENDL;
        TLInputPeer offsetPeer;
        stream >> offsetPeer;
        d << spacer.innerSpaces() << "offsetPeer: " << offsetPeer << TELEGRAMQT_ENDL;
        quint32 offsetId;
        stream >> offsetId;
        d << spacer.innerSpaces() << "offsetId: " << offsetId << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSearchStickerSets:
        d << "MessagesSearchStickerSets(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        QString q;
        stream >> q;
        d << spacer.innerSpaces() << "q: " << q << TELEGRAMQT_ENDL;
        quint32 hash;
        stream >> hash;
        d << spacer.innerSpaces() << "hash: " << hash << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncrypted:
        d << "MessagesSendEncrypted(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncryptedFile:
        d << "MessagesSendEncryptedFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << TELEGRAMQT_ENDL;
        TLInputEncryptedFile file;
        stream >> file;
        d << spacer.innerSpaces() << "file: " << file << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendEncryptedService:
        d << "MessagesSendEncryptedService(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QByteArray data;
        stream >> data;
        d << spacer.innerSpaces() << "data: " << data.toHex() << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendInlineBotResult:
        d << "MessagesSendInlineBotResult(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
        QString id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendMedia:
        d << "MessagesSendMedia(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLInputMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendMessage:
        d << "MessagesSendMessage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QString message;
        stream >> message;
        d << spacer.innerSpaces() << "message: " << message << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendMultiMedia:
        d << "MessagesSendMultiMedia(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QVector<TLInputSingleMedia> multiMedia;
        stream >> multiMedia;
        d << spacer.innerSpaces() << "multiMedia: " << multiMedia << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendScreenshotNotification:
        d << "MessagesSendScreenshotNotification(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 replyToMsgId;
        stream >> replyToMsgId;
        d << spacer.innerSpaces() << "replyToMsgId: " << replyToMsgId << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSendVote:
        d << "MessagesSendVote(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
        QVector<QByteArray> options;
        stream >> options;
        d << spacer.innerSpaces() << "options: " << options << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotCallbackAnswer:
        d << "MessagesSetBotCallbackAnswer(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
        quint32 cacheTime;
        stream >> cacheTime;
        d << spacer.innerSpaces() << "cacheTime: " << cacheTime << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotPrecheckoutResults:
        d << "MessagesSetBotPrecheckoutResults(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetBotShippingResults:
        d << "MessagesSetBotShippingResults(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetEncryptedTyping:
        d << "MessagesSetEncryptedTyping(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        bool typing;
        stream >> typing;
        d << spacer.innerSpaces() << "typing: " << typing << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetGameScore:
        d << "MessagesSetGameScore(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 score;
        stream >> score;
        d << spacer.innerSpaces() << "score: " << score << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetInlineBotResults:
        d << "MessagesSetInlineBotResults(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint64 queryId;
        stream >> queryId;
        d << spacer.innerSpaces() << "queryId: " << queryId << TELEGRAMQT_ENDL;
        QVector<TLInputBotInlineResult> results;
        stream >> results;
        d << spacer.innerSpaces() << "results: " << results << TELEGRAMQT_ENDL;
        quint32 cacheTime;
        stream >> cacheTime;
        d << spacer.innerSpaces() << "cacheTime: " << cacheTime << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetInlineGameScore:
        d << "MessagesSetInlineGameScore(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputBotInlineMessageID id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 score;
        stream >> score;
        d << spacer.innerSpaces() << "score: " << score << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesSetTyping:
        d << "MessagesSetTyping(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLSendMessageAction action;
        stream >> action;
        d << spacer.innerSpaces() << "action: " << action << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesStartBot:
        d << "MessagesStartBot(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser bot;
        stream >> bot;
        d << spacer.innerSpaces() << "bot: " << bot << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint64 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QString startParam;
        stream >> startParam;
        d << spacer.innerSpaces() << "startParam: " << startParam << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesToggleChatAdmins:
        d << "MessagesToggleChatAdmins(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 chatId;
        stream >> chatId;
        d << spacer.innerSpaces() << "chatId: " << chatId << TELEGRAMQT_ENDL;
        bool enabled;
        stream >> enabled;
        d << spacer.innerSpaces() << "enabled: " << enabled << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesToggleDialogPin:
        d << "MessagesToggleDialogPin(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputDialogPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesUninstallStickerSet:
        d << "MessagesUninstallStickerSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesUpdatePinnedMessage:
        d << "MessagesUpdatePinnedMessage(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesUploadEncryptedFile:
        d << "MessagesUploadEncryptedFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputEncryptedChat peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLInputEncryptedFile file;
        stream >> file;
        d << spacer.innerSpaces() << "file: " << file << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::MessagesUploadMedia:
        d << "MessagesUploadMedia(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPeer peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLInputMedia media;
        stream >> media;
        d << spacer.innerSpaces() << "media: " << media << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PaymentsClearSavedInfo:
        d << "PaymentsClearSavedInfo(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetPaymentForm:
        d << "PaymentsGetPaymentForm(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetPaymentReceipt:
        d << "PaymentsGetPaymentReceipt(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PaymentsGetSavedInfo:
        d << "PaymentsGetSavedInfo(";
        d << ")";
        break;
    case TLValue::PaymentsSendPaymentForm:
        d << "PaymentsSendPaymentForm(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
        TLInputPaymentCredentials credentials;
        stream >> credentials;
        d << spacer.innerSpaces() << "credentials: " << credentials << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PaymentsValidateRequestedInfo:
        d << "PaymentsValidateRequestedInfo(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 msgId;
        stream >> msgId;
        d << spacer.innerSpaces() << "msgId: " << msgId << TELEGRAMQT_ENDL;
        TLPaymentRequestedInfo info;
        stream >> info;
        d << spacer.innerSpaces() << "info: " << info << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneAcceptCall:
        d << "PhoneAcceptCall(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QByteArray gB;
        stream >> gB;
        d << spacer.innerSpaces() << "gB: " << gB.toHex() << TELEGRAMQT_ENDL;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneConfirmCall:
        d << "PhoneConfirmCall(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        QByteArray gA;
        stream >> gA;
        d << spacer.innerSpaces() << "gA: " << gA.toHex() << TELEGRAMQT_ENDL;
        quint64 keyFingerprint;
        stream >> keyFingerprint;
        d << spacer.innerSpaces() << "keyFingerprint: " << keyFingerprint << TELEGRAMQT_ENDL;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneDiscardCall:
        d << "PhoneDiscardCall(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 duration;
        stream >> duration;
        d << spacer.innerSpaces() << "duration: " << duration << TELEGRAMQT_ENDL;
        TLPhoneCallDiscardReason reason;
        stream >> reason;
        d << spacer.innerSpaces() << "reason: " << reason << TELEGRAMQT_ENDL;
        quint64 connectionId;
        stream >> connectionId;
        d << spacer.innerSpaces() << "connectionId: " << connectionId << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneGetCallConfig:
        d << "PhoneGetCallConfig(";
        d << ")";
        break;
    case TLValue::PhoneReceivedCall:
        d << "PhoneReceivedCall(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneRequestCall:
        d << "PhoneRequestCall(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 randomId;
        stream >> randomId;
        d << spacer.innerSpaces() << "randomId: " << randomId << TELEGRAMQT_ENDL;
        QByteArray gAHash;
        stream >> gAHash;
        d << spacer.innerSpaces() << "gAHash: " << gAHash.toHex() << TELEGRAMQT_ENDL;
        TLPhoneCallProtocol protocol;
        stream >> protocol;
        d << spacer.innerSpaces() << "protocol: " << protocol << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneSaveCallDebug:
        d << "PhoneSaveCallDebug(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        TLDataJSON debug;
        stream >> debug;
        d << spacer.innerSpaces() << "debug: " << debug << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhoneSetCallRating:
        d << "PhoneSetCallRating(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoneCall peer;
        stream >> peer;
        d << spacer.innerSpaces() << "peer: " << peer << TELEGRAMQT_ENDL;
        quint32 rating;
        stream >> rating;
        d << spacer.innerSpaces() << "rating: " << rating << TELEGRAMQT_ENDL;
        QString comment;
        stream >> comment;
        d << spacer.innerSpaces() << "comment: " << comment << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhotosDeletePhotos:
        d << "PhotosDeletePhotos(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputPhoto> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhotosGetUserPhotos:
        d << "PhotosGetUserPhotos(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint64 maxId;
        stream >> maxId;
        d << spacer.innerSpaces() << "maxId: " << maxId << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhotosUpdateProfilePhoto:
        d << "PhotosUpdateProfilePhoto(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputPhoto id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::PhotosUploadProfilePhoto:
        d << "PhotosUploadProfilePhoto(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputFile file;
        stream >> file;
        d << spacer.innerSpaces() << "file: " << file << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::StickersAddStickerToSet:
        d << "StickersAddStickerToSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputStickerSet stickerset;
        stream >> stickerset;
        d << spacer.innerSpaces() << "stickerset: " << stickerset << TELEGRAMQT_ENDL;
        TLInputStickerSetItem sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::StickersChangeStickerPosition:
        d << "StickersChangeStickerPosition(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputDocument sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << TELEGRAMQT_ENDL;
        quint32 position;
        stream >> position;
        d << spacer.innerSpaces() << "position: " << position << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::StickersCreateStickerSet:
        d << "StickersCreateStickerSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputUser userId;
        stream >> userId;
        d << spacer.innerSpaces() << "userId: " << userId << TELEGRAMQT_ENDL;
        QString title;
        stream >> title;
        d << spacer.innerSpaces() << "title: " << title << TELEGRAMQT_ENDL;
        QString shortName;
        stream >> shortName;
        d << spacer.innerSpaces() << "shortName: " << shortName << TELEGRAMQT_ENDL;
        QVector<TLInputStickerSetItem> stickers;
        stream >> stickers;
        d << spacer.innerSpaces() << "stickers: " << stickers << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::StickersRemoveStickerFromSet:
        d << "StickersRemoveStickerFromSet(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputDocument sticker;
        stream >> sticker;
        d << spacer.innerSpaces() << "sticker: " << sticker << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetChannelDifference:
        d << "UpdatesGetChannelDifference(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        TLInputChannel channel;
        stream >> channel;
        d << spacer.innerSpaces() << "channel: " << channel << TELEGRAMQT_ENDL;
        TLChannelMessagesFilter filter;
        stream >> filter;
        d << spacer.innerSpaces() << "filter: " << filter << TELEGRAMQT_ENDL;
        quint32 pts;
        stream >> pts;
        d << spacer.innerSpaces() << "pts: " << pts << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetDifference:
        d << "UpdatesGetDifference(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint32 flags;
        stream >> flags;
        d << spacer.innerSpaces() << "flags: " << flags << TELEGRAMQT_ENDL;
        quint32 pts;
        stream >> pts;
        d << spacer.innerSpaces() << "pts: " << pts << TELEGRAMQT_ENDL;
        quint32 date;
        stream >> date;
        d << spacer.innerSpaces() << "date: " << date << TELEGRAMQT_ENDL;
        quint32 qts;
        stream >> qts;
        d << spacer.innerSpaces() << "qts: " << qts << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UpdatesGetState:
        d << "UpdatesGetState(";
        d << ")";
        break;
    case TLValue::UploadGetCdnFile:
        d << "UploadGetCdnFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadGetCdnFileHashes:
        d << "UploadGetCdnFileHashes(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadGetFile:
        d << "UploadGetFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputFileLocation location;
        stream >> location;
        d << spacer.innerSpaces() << "location: " << location << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadGetFileHashes:
        d << "UploadGetFileHashes(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputFileLocation location;
        stream >> location;
        d << spacer.innerSpaces() << "location: " << location << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadGetWebFile:
        d << "UploadGetWebFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputWebFileLocation location;
        stream >> location;
        d << spacer.innerSpaces() << "location: " << location << TELEGRAMQT_ENDL;
        quint32 offset;
        stream >> offset;
        d << spacer.innerSpaces() << "offset: " << offset << TELEGRAMQT_ENDL;
        quint32 limit;
        stream >> limit;
        d << spacer.innerSpaces() << "limit: " << limit << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadReuploadCdnFile:
        d << "UploadReuploadCdnFile(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QByteArray fileToken;
        stream >> fileToken;
        d << spacer.innerSpaces() << "fileToken: " << fileToken.toHex() << TELEGRAMQT_ENDL;
        QByteArray requestToken;
        stream >> requestToken;
        d << spacer.innerSpaces() << "requestToken: " << requestToken.toHex() << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadSaveBigFilePart:
        d << "UploadSaveBigFilePart(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 fileId;
        stream >> fileId;
        d << spacer.innerSpaces() << "fileId: " << fileId << TELEGRAMQT_ENDL;
        quint32 filePart;
        stream >> filePart;
        d << spacer.innerSpaces() << "filePart: " << filePart << TELEGRAMQT_ENDL;
        quint32 fileTotalParts;
        stream >> fileTotalParts;
        d << spacer.innerSpaces() << "fileTotalParts: " << fileTotalParts << TELEGRAMQT_ENDL;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UploadSaveFilePart:
        d << "UploadSaveFilePart(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        quint64 fileId;
        stream >> fileId;
        d << spacer.innerSpaces() << "fileId: " << fileId << TELEGRAMQT_ENDL;
        quint32 filePart;
        stream >> filePart;
        d << spacer.innerSpaces() << "filePart: " << filePart << TELEGRAMQT_ENDL;
        QByteArray bytes;
        stream >> bytes;
        d << spacer.innerSpaces() << "bytes: " << printBytes(bytes) << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UsersGetFullUser:
        d << "UsersGetFullUser(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UsersGetUsers:
        d << "UsersGetUsers(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        QVector<TLInputUser> id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    case TLValue::UsersSetSecureValueErrors:
        d << "UsersSetSecureValueErrors(";
    {
        d << TELEGRAMQT_ENDL;
        Spacer spacer;
        TLInputUser id;
        stream >> id;
        d << spacer.innerSpaces() << "id: " << id << TELEGRAMQT_ENDL;
        QVector<TLSecureValueError> errors;
        stream >> errors;
        d << spacer.innerSpaces() << "errors: " << errors << TELEGRAMQT_ENDL;
    }
        d << ")";
        break;
    // End of generated RPC debug cases
    default:
        qDebug() << "Unknown data" << request;
        break;
    }
}

} // MTProto namespace

} // Telegram namespace
