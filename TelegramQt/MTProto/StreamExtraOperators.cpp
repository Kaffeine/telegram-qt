#include "StreamExtraOperators.hpp"

#include "Stream_p.hpp"

namespace Telegram {

namespace MTProto {

template Stream &Stream::operator<<(const TLVector<TLDcOption> &v);
template Stream &Stream::operator<<(const TLVector<TLCdnFileHash> &v);
template Stream &Stream::operator<<(const TLVector<TLLangPackString> &v);
template Stream &Stream::operator<<(const TLVector<TLStickerSetCovered> &v);
template Stream &Stream::operator<<(const TLVector<TLUser> &v);

// Generated vector write templates instancing
// End of generated vector write templates instancing

// Generated write operators implementation
Stream &operator<<(Stream &stream, const TLAccountSentEmailCode &accountSentEmailCodeValue)
{
    stream << accountSentEmailCodeValue.tlType;
    switch (accountSentEmailCodeValue.tlType) {
    case TLValue::AccountSentEmailCode:
        stream << accountSentEmailCodeValue.emailPattern;
        stream << accountSentEmailCodeValue.length;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountTakeout &accountTakeoutValue)
{
    stream << accountTakeoutValue.tlType;
    switch (accountTakeoutValue.tlType) {
    case TLValue::AccountTakeout:
        stream << accountTakeoutValue.id;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountTmpPassword &accountTmpPasswordValue)
{
    stream << accountTmpPasswordValue.tlType;
    switch (accountTmpPasswordValue.tlType) {
    case TLValue::AccountTmpPassword:
        stream << accountTmpPasswordValue.tmpPassword;
        stream << accountTmpPasswordValue.validUntil;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthCheckedPhone &authCheckedPhoneValue)
{
    stream << authCheckedPhoneValue.tlType;
    switch (authCheckedPhoneValue.tlType) {
    case TLValue::AuthCheckedPhone:
        stream << authCheckedPhoneValue.phoneRegistered;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthCodeType &authCodeTypeValue)
{
    stream << authCodeTypeValue.tlType;
    switch (authCodeTypeValue.tlType) {
    case TLValue::AuthCodeTypeSms:
    case TLValue::AuthCodeTypeCall:
    case TLValue::AuthCodeTypeFlashCall:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthExportedAuthorization &authExportedAuthorizationValue)
{
    stream << authExportedAuthorizationValue.tlType;
    switch (authExportedAuthorizationValue.tlType) {
    case TLValue::AuthExportedAuthorization:
        stream << authExportedAuthorizationValue.id;
        stream << authExportedAuthorizationValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthPasswordRecovery &authPasswordRecoveryValue)
{
    stream << authPasswordRecoveryValue.tlType;
    switch (authPasswordRecoveryValue.tlType) {
    case TLValue::AuthPasswordRecovery:
        stream << authPasswordRecoveryValue.emailPattern;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthSentCodeType &authSentCodeTypeValue)
{
    stream << authSentCodeTypeValue.tlType;
    switch (authSentCodeTypeValue.tlType) {
    case TLValue::AuthSentCodeTypeApp:
    case TLValue::AuthSentCodeTypeSms:
    case TLValue::AuthSentCodeTypeCall:
        stream << authSentCodeTypeValue.length;
        break;
    case TLValue::AuthSentCodeTypeFlashCall:
        stream << authSentCodeTypeValue.pattern;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLBadMsgNotification &badMsgNotificationValue)
{
    stream << badMsgNotificationValue.tlType;
    switch (badMsgNotificationValue.tlType) {
    case TLValue::BadMsgNotification:
        stream << badMsgNotificationValue.badMsgId;
        stream << badMsgNotificationValue.badMsgSeqno;
        stream << badMsgNotificationValue.errorCode;
        break;
    case TLValue::BadServerSalt:
        stream << badMsgNotificationValue.badMsgId;
        stream << badMsgNotificationValue.badMsgSeqno;
        stream << badMsgNotificationValue.errorCode;
        stream << badMsgNotificationValue.newServerSalt;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLBotCommand &botCommandValue)
{
    stream << botCommandValue.tlType;
    switch (botCommandValue.tlType) {
    case TLValue::BotCommand:
        stream << botCommandValue.command;
        stream << botCommandValue.description;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLBotInfo &botInfoValue)
{
    stream << botInfoValue.tlType;
    switch (botInfoValue.tlType) {
    case TLValue::BotInfo:
        stream << botInfoValue.userId;
        stream << botInfoValue.description;
        stream << botInfoValue.commands;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLCdnPublicKey &cdnPublicKeyValue)
{
    stream << cdnPublicKeyValue.tlType;
    switch (cdnPublicKeyValue.tlType) {
    case TLValue::CdnPublicKey:
        stream << cdnPublicKeyValue.dcId;
        stream << cdnPublicKeyValue.publicKey;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatOnlines &chatOnlinesValue)
{
    stream << chatOnlinesValue.tlType;
    switch (chatOnlinesValue.tlType) {
    case TLValue::ChatOnlines:
        stream << chatOnlinesValue.onlines;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatParticipant &chatParticipantValue)
{
    stream << chatParticipantValue.tlType;
    switch (chatParticipantValue.tlType) {
    case TLValue::ChatParticipant:
    case TLValue::ChatParticipantAdmin:
        stream << chatParticipantValue.userId;
        stream << chatParticipantValue.inviterId;
        stream << chatParticipantValue.date;
        break;
    case TLValue::ChatParticipantCreator:
        stream << chatParticipantValue.userId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatParticipants &chatParticipantsValue)
{
    stream << chatParticipantsValue.tlType;
    switch (chatParticipantsValue.tlType) {
    case TLValue::ChatParticipantsForbidden:
        stream << chatParticipantsValue.flags;
        stream << chatParticipantsValue.chatId;
        if (chatParticipantsValue.flags & TLChatParticipants::SelfParticipant) {
            stream << chatParticipantsValue.selfParticipant;
        }
        break;
    case TLValue::ChatParticipants:
        stream << chatParticipantsValue.chatId;
        stream << chatParticipantsValue.participants;
        stream << chatParticipantsValue.version;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLClientDHInnerData &clientDHInnerDataValue)
{
    stream << clientDHInnerDataValue.tlType;
    switch (clientDHInnerDataValue.tlType) {
    case TLValue::ClientDHInnerData:
        stream << clientDHInnerDataValue.nonce;
        stream << clientDHInnerDataValue.serverNonce;
        stream << clientDHInnerDataValue.retryId;
        stream << clientDHInnerDataValue.gB;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContact &contactValue)
{
    stream << contactValue.tlType;
    switch (contactValue.tlType) {
    case TLValue::Contact:
        stream << contactValue.userId;
        stream << contactValue.mutual;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactBlocked &contactBlockedValue)
{
    stream << contactBlockedValue.tlType;
    switch (contactBlockedValue.tlType) {
    case TLValue::ContactBlocked:
        stream << contactBlockedValue.userId;
        stream << contactBlockedValue.date;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactLink &contactLinkValue)
{
    stream << contactLinkValue.tlType;
    switch (contactLinkValue.tlType) {
    case TLValue::ContactLinkUnknown:
    case TLValue::ContactLinkNone:
    case TLValue::ContactLinkHasPhone:
    case TLValue::ContactLinkContact:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDestroyAuthKeyRes &destroyAuthKeyResValue)
{
    stream << destroyAuthKeyResValue.tlType;
    switch (destroyAuthKeyResValue.tlType) {
    case TLValue::DestroyAuthKeyOk:
    case TLValue::DestroyAuthKeyNone:
    case TLValue::DestroyAuthKeyFail:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDestroySessionRes &destroySessionResValue)
{
    stream << destroySessionResValue.tlType;
    switch (destroySessionResValue.tlType) {
    case TLValue::DestroySessionOk:
    case TLValue::DestroySessionNone:
        stream << destroySessionResValue.sessionId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLEncryptedChat &encryptedChatValue)
{
    stream << encryptedChatValue.tlType;
    switch (encryptedChatValue.tlType) {
    case TLValue::EncryptedChatEmpty:
    case TLValue::EncryptedChatDiscarded:
        stream << encryptedChatValue.id;
        break;
    case TLValue::EncryptedChatWaiting:
        stream << encryptedChatValue.id;
        stream << encryptedChatValue.accessHash;
        stream << encryptedChatValue.date;
        stream << encryptedChatValue.adminId;
        stream << encryptedChatValue.participantId;
        break;
    case TLValue::EncryptedChatRequested:
        stream << encryptedChatValue.id;
        stream << encryptedChatValue.accessHash;
        stream << encryptedChatValue.date;
        stream << encryptedChatValue.adminId;
        stream << encryptedChatValue.participantId;
        stream << encryptedChatValue.gA;
        break;
    case TLValue::EncryptedChat:
        stream << encryptedChatValue.id;
        stream << encryptedChatValue.accessHash;
        stream << encryptedChatValue.date;
        stream << encryptedChatValue.adminId;
        stream << encryptedChatValue.participantId;
        stream << encryptedChatValue.gAOrB;
        stream << encryptedChatValue.keyFingerprint;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLEncryptedFile &encryptedFileValue)
{
    stream << encryptedFileValue.tlType;
    switch (encryptedFileValue.tlType) {
    case TLValue::EncryptedFileEmpty:
        break;
    case TLValue::EncryptedFile:
        stream << encryptedFileValue.id;
        stream << encryptedFileValue.accessHash;
        stream << encryptedFileValue.size;
        stream << encryptedFileValue.dcId;
        stream << encryptedFileValue.keyFingerprint;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLEncryptedMessage &encryptedMessageValue)
{
    stream << encryptedMessageValue.tlType;
    switch (encryptedMessageValue.tlType) {
    case TLValue::EncryptedMessage:
        stream << encryptedMessageValue.randomId;
        stream << encryptedMessageValue.chatId;
        stream << encryptedMessageValue.date;
        stream << encryptedMessageValue.bytes;
        stream << encryptedMessageValue.file;
        break;
    case TLValue::EncryptedMessageService:
        stream << encryptedMessageValue.randomId;
        stream << encryptedMessageValue.chatId;
        stream << encryptedMessageValue.date;
        stream << encryptedMessageValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLError &errorValue)
{
    stream << errorValue.tlType;
    switch (errorValue.tlType) {
    case TLValue::Error:
        stream << errorValue.code;
        stream << errorValue.text;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLExportedChatInvite &exportedChatInviteValue)
{
    stream << exportedChatInviteValue.tlType;
    switch (exportedChatInviteValue.tlType) {
    case TLValue::ChatInviteEmpty:
        break;
    case TLValue::ChatInviteExported:
        stream << exportedChatInviteValue.link;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLExportedMessageLink &exportedMessageLinkValue)
{
    stream << exportedMessageLinkValue.tlType;
    switch (exportedMessageLinkValue.tlType) {
    case TLValue::ExportedMessageLink:
        stream << exportedMessageLinkValue.link;
        stream << exportedMessageLinkValue.html;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLFileHash &fileHashValue)
{
    stream << fileHashValue.tlType;
    switch (fileHashValue.tlType) {
    case TLValue::FileHash:
        stream << fileHashValue.offset;
        stream << fileHashValue.limit;
        stream << fileHashValue.hash;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLFileLocation &fileLocationValue)
{
    stream << fileLocationValue.tlType;
    switch (fileLocationValue.tlType) {
    case TLValue::FileLocationUnavailable:
        stream << fileLocationValue.volumeId;
        stream << fileLocationValue.localId;
        stream << fileLocationValue.secret;
        break;
    case TLValue::FileLocation:
        stream << fileLocationValue.dcId;
        stream << fileLocationValue.volumeId;
        stream << fileLocationValue.localId;
        stream << fileLocationValue.secret;
        stream << fileLocationValue.fileReference;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLFutureSalt &futureSaltValue)
{
    stream << futureSaltValue.tlType;
    switch (futureSaltValue.tlType) {
    case TLValue::FutureSalt:
        stream << futureSaltValue.validSince;
        stream << futureSaltValue.validUntil;
        stream << futureSaltValue.salt;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLFutureSalts &futureSaltsValue)
{
    stream << futureSaltsValue.tlType;
    switch (futureSaltsValue.tlType) {
    case TLValue::FutureSalts:
        stream << futureSaltsValue.reqMsgId;
        stream << futureSaltsValue.now;
        stream << futureSaltsValue.salts;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLGeoPoint &geoPointValue)
{
    stream << geoPointValue.tlType;
    switch (geoPointValue.tlType) {
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
        stream << geoPointValue.longitude;
        stream << geoPointValue.latitude;
        stream << geoPointValue.accessHash;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpInviteText &helpInviteTextValue)
{
    stream << helpInviteTextValue.tlType;
    switch (helpInviteTextValue.tlType) {
    case TLValue::HelpInviteText:
        stream << helpInviteTextValue.message;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpPassportConfig &helpPassportConfigValue)
{
    stream << helpPassportConfigValue.tlType;
    switch (helpPassportConfigValue.tlType) {
    case TLValue::HelpPassportConfigNotModified:
        break;
    case TLValue::HelpPassportConfig:
        stream << helpPassportConfigValue.hash;
        stream << helpPassportConfigValue.countriesLangs;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpSupportName &helpSupportNameValue)
{
    stream << helpSupportNameValue.tlType;
    switch (helpSupportNameValue.tlType) {
    case TLValue::HelpSupportName:
        stream << helpSupportNameValue.name;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHighScore &highScoreValue)
{
    stream << highScoreValue.tlType;
    switch (highScoreValue.tlType) {
    case TLValue::HighScore:
        stream << highScoreValue.pos;
        stream << highScoreValue.userId;
        stream << highScoreValue.score;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHttpWait &httpWaitValue)
{
    stream << httpWaitValue.tlType;
    switch (httpWaitValue.tlType) {
    case TLValue::HttpWait:
        stream << httpWaitValue.maxDelay;
        stream << httpWaitValue.waitAfter;
        stream << httpWaitValue.maxWait;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLImportedContact &importedContactValue)
{
    stream << importedContactValue.tlType;
    switch (importedContactValue.tlType) {
    case TLValue::ImportedContact:
        stream << importedContactValue.userId;
        stream << importedContactValue.clientId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLInputClientProxy &inputClientProxyValue)
{
    stream << inputClientProxyValue.tlType;
    switch (inputClientProxyValue.tlType) {
    case TLValue::InputClientProxy:
        stream << inputClientProxyValue.address;
        stream << inputClientProxyValue.port;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLIpPort &ipPortValue)
{
    stream << ipPortValue.tlType;
    switch (ipPortValue.tlType) {
    case TLValue::IpPort:
        stream << ipPortValue.ipv4;
        stream << ipPortValue.port;
        break;
    case TLValue::IpPortSecret:
        stream << ipPortValue.ipv4;
        stream << ipPortValue.port;
        stream << ipPortValue.secret;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLLangPackString &langPackStringValue)
{
    stream << langPackStringValue.tlType;
    switch (langPackStringValue.tlType) {
    case TLValue::LangPackString:
        stream << langPackStringValue.key;
        stream << langPackStringValue.value;
        break;
    case TLValue::LangPackStringPluralized:
        stream << langPackStringValue.flags;
        stream << langPackStringValue.key;
        if (langPackStringValue.flags & TLLangPackString::ZeroValue) {
            stream << langPackStringValue.zeroValue;
        }
        if (langPackStringValue.flags & TLLangPackString::OneValue) {
            stream << langPackStringValue.oneValue;
        }
        if (langPackStringValue.flags & TLLangPackString::TwoValue) {
            stream << langPackStringValue.twoValue;
        }
        if (langPackStringValue.flags & TLLangPackString::FewValue) {
            stream << langPackStringValue.fewValue;
        }
        if (langPackStringValue.flags & TLLangPackString::ManyValue) {
            stream << langPackStringValue.manyValue;
        }
        stream << langPackStringValue.otherValue;
        break;
    case TLValue::LangPackStringDeleted:
        stream << langPackStringValue.key;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesAffectedHistory &messagesAffectedHistoryValue)
{
    stream << messagesAffectedHistoryValue.tlType;
    switch (messagesAffectedHistoryValue.tlType) {
    case TLValue::MessagesAffectedHistory:
        stream << messagesAffectedHistoryValue.pts;
        stream << messagesAffectedHistoryValue.ptsCount;
        stream << messagesAffectedHistoryValue.offset;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesAffectedMessages &messagesAffectedMessagesValue)
{
    stream << messagesAffectedMessagesValue.tlType;
    switch (messagesAffectedMessagesValue.tlType) {
    case TLValue::MessagesAffectedMessages:
        stream << messagesAffectedMessagesValue.pts;
        stream << messagesAffectedMessagesValue.ptsCount;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesDhConfig &messagesDhConfigValue)
{
    stream << messagesDhConfigValue.tlType;
    switch (messagesDhConfigValue.tlType) {
    case TLValue::MessagesDhConfigNotModified:
        stream << messagesDhConfigValue.random;
        break;
    case TLValue::MessagesDhConfig:
        stream << messagesDhConfigValue.g;
        stream << messagesDhConfigValue.p;
        stream << messagesDhConfigValue.version;
        stream << messagesDhConfigValue.random;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue)
{
    stream << messagesSentEncryptedMessageValue.tlType;
    switch (messagesSentEncryptedMessageValue.tlType) {
    case TLValue::MessagesSentEncryptedMessage:
        stream << messagesSentEncryptedMessageValue.date;
        break;
    case TLValue::MessagesSentEncryptedFile:
        stream << messagesSentEncryptedMessageValue.date;
        stream << messagesSentEncryptedMessageValue.file;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgDetailedInfo &msgDetailedInfoValue)
{
    stream << msgDetailedInfoValue.tlType;
    switch (msgDetailedInfoValue.tlType) {
    case TLValue::MsgDetailedInfo:
        stream << msgDetailedInfoValue.msgId;
        stream << msgDetailedInfoValue.answerMsgId;
        stream << msgDetailedInfoValue.bytes;
        stream << msgDetailedInfoValue.status;
        break;
    case TLValue::MsgNewDetailedInfo:
        stream << msgDetailedInfoValue.answerMsgId;
        stream << msgDetailedInfoValue.bytes;
        stream << msgDetailedInfoValue.status;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgResendReq &msgResendReqValue)
{
    stream << msgResendReqValue.tlType;
    switch (msgResendReqValue.tlType) {
    case TLValue::MsgResendReq:
        stream << msgResendReqValue.msgIds;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgsAck &msgsAckValue)
{
    stream << msgsAckValue.tlType;
    switch (msgsAckValue.tlType) {
    case TLValue::MsgsAck:
        stream << msgsAckValue.msgIds;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgsAllInfo &msgsAllInfoValue)
{
    stream << msgsAllInfoValue.tlType;
    switch (msgsAllInfoValue.tlType) {
    case TLValue::MsgsAllInfo:
        stream << msgsAllInfoValue.msgIds;
        stream << msgsAllInfoValue.info;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgsStateInfo &msgsStateInfoValue)
{
    stream << msgsStateInfoValue.tlType;
    switch (msgsStateInfoValue.tlType) {
    case TLValue::MsgsStateInfo:
        stream << msgsStateInfoValue.reqMsgId;
        stream << msgsStateInfoValue.info;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMsgsStateReq &msgsStateReqValue)
{
    stream << msgsStateReqValue.tlType;
    switch (msgsStateReqValue.tlType) {
    case TLValue::MsgsStateReq:
        stream << msgsStateReqValue.msgIds;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLNearestDc &nearestDcValue)
{
    stream << nearestDcValue.tlType;
    switch (nearestDcValue.tlType) {
    case TLValue::NearestDc:
        stream << nearestDcValue.country;
        stream << nearestDcValue.thisDc;
        stream << nearestDcValue.nearestDc;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLNewSession &newSessionValue)
{
    stream << newSessionValue.tlType;
    switch (newSessionValue.tlType) {
    case TLValue::NewSessionCreated:
        stream << newSessionValue.firstMsgId;
        stream << newSessionValue.uniqueId;
        stream << newSessionValue.serverSalt;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPQInnerData &pQInnerDataValue)
{
    stream << pQInnerDataValue.tlType;
    switch (pQInnerDataValue.tlType) {
    case TLValue::PQInnerData:
        stream << pQInnerDataValue.pq;
        stream << pQInnerDataValue.p;
        stream << pQInnerDataValue.q;
        stream << pQInnerDataValue.nonce;
        stream << pQInnerDataValue.serverNonce;
        stream << pQInnerDataValue.newNonce;
        break;
    case TLValue::PQInnerDataDc:
        stream << pQInnerDataValue.pq;
        stream << pQInnerDataValue.p;
        stream << pQInnerDataValue.q;
        stream << pQInnerDataValue.nonce;
        stream << pQInnerDataValue.serverNonce;
        stream << pQInnerDataValue.newNonce;
        stream << pQInnerDataValue.dc;
        break;
    case TLValue::PQInnerDataTemp:
        stream << pQInnerDataValue.pq;
        stream << pQInnerDataValue.p;
        stream << pQInnerDataValue.q;
        stream << pQInnerDataValue.nonce;
        stream << pQInnerDataValue.serverNonce;
        stream << pQInnerDataValue.newNonce;
        stream << pQInnerDataValue.expiresIn;
        break;
    case TLValue::PQInnerDataTempDc:
        stream << pQInnerDataValue.pq;
        stream << pQInnerDataValue.p;
        stream << pQInnerDataValue.q;
        stream << pQInnerDataValue.nonce;
        stream << pQInnerDataValue.serverNonce;
        stream << pQInnerDataValue.newNonce;
        stream << pQInnerDataValue.dc;
        stream << pQInnerDataValue.expiresIn;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageCaption &pageCaptionValue)
{
    stream << pageCaptionValue.tlType;
    switch (pageCaptionValue.tlType) {
    case TLValue::PageCaption:
        stream << *pageCaptionValue.text;
        stream << *pageCaptionValue.credit;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageListItem &pageListItemValue)
{
    stream << pageListItemValue.tlType;
    switch (pageListItemValue.tlType) {
    case TLValue::PageListItemText:
        stream << *pageListItemValue.text;
        break;
    case TLValue::PageListItemBlocks:
        stream << pageListItemValue.blocks;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageListOrderedItem &pageListOrderedItemValue)
{
    stream << pageListOrderedItemValue.tlType;
    switch (pageListOrderedItemValue.tlType) {
    case TLValue::PageListOrderedItemText:
        stream << pageListOrderedItemValue.num;
        stream << *pageListOrderedItemValue.text;
        break;
    case TLValue::PageListOrderedItemBlocks:
        stream << pageListOrderedItemValue.num;
        stream << pageListOrderedItemValue.blocks;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageRelatedArticle &pageRelatedArticleValue)
{
    stream << pageRelatedArticleValue.tlType;
    switch (pageRelatedArticleValue.tlType) {
    case TLValue::PageRelatedArticle:
        stream << pageRelatedArticleValue.flags;
        stream << pageRelatedArticleValue.url;
        stream << pageRelatedArticleValue.webpageId;
        if (pageRelatedArticleValue.flags & TLPageRelatedArticle::Title) {
            stream << pageRelatedArticleValue.title;
        }
        if (pageRelatedArticleValue.flags & TLPageRelatedArticle::Description) {
            stream << pageRelatedArticleValue.description;
        }
        if (pageRelatedArticleValue.flags & TLPageRelatedArticle::PhotoId) {
            stream << pageRelatedArticleValue.photoId;
        }
        if (pageRelatedArticleValue.flags & TLPageRelatedArticle::Author) {
            stream << pageRelatedArticleValue.author;
        }
        if (pageRelatedArticleValue.flags & TLPageRelatedArticle::PublishedDate) {
            stream << pageRelatedArticleValue.publishedDate;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentCharge &paymentChargeValue)
{
    stream << paymentChargeValue.tlType;
    switch (paymentChargeValue.tlType) {
    case TLValue::PaymentCharge:
        stream << paymentChargeValue.id;
        stream << paymentChargeValue.providerChargeId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentSavedCredentials &paymentSavedCredentialsValue)
{
    stream << paymentSavedCredentialsValue.tlType;
    switch (paymentSavedCredentialsValue.tlType) {
    case TLValue::PaymentSavedCredentialsCard:
        stream << paymentSavedCredentialsValue.id;
        stream << paymentSavedCredentialsValue.title;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPeer &peerValue)
{
    stream << peerValue.tlType;
    switch (peerValue.tlType) {
    case TLValue::PeerUser:
        stream << peerValue.userId;
        break;
    case TLValue::PeerChat:
        stream << peerValue.chatId;
        break;
    case TLValue::PeerChannel:
        stream << peerValue.channelId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPeerNotifySettings &peerNotifySettingsValue)
{
    stream << peerNotifySettingsValue.tlType;
    switch (peerNotifySettingsValue.tlType) {
    case TLValue::PeerNotifySettings:
        stream << peerNotifySettingsValue.flags;
        if (peerNotifySettingsValue.flags & TLPeerNotifySettings::ShowPreviews) {
            stream << peerNotifySettingsValue.showPreviews;
        }
        if (peerNotifySettingsValue.flags & TLPeerNotifySettings::Silent) {
            stream << peerNotifySettingsValue.silent;
        }
        if (peerNotifySettingsValue.flags & TLPeerNotifySettings::MuteUntil) {
            stream << peerNotifySettingsValue.muteUntil;
        }
        if (peerNotifySettingsValue.flags & TLPeerNotifySettings::Sound) {
            stream << peerNotifySettingsValue.sound;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhoneConnection &phoneConnectionValue)
{
    stream << phoneConnectionValue.tlType;
    switch (phoneConnectionValue.tlType) {
    case TLValue::PhoneConnection:
        stream << phoneConnectionValue.id;
        stream << phoneConnectionValue.ip;
        stream << phoneConnectionValue.ipv6;
        stream << phoneConnectionValue.port;
        stream << phoneConnectionValue.peerTag;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhotoSize &photoSizeValue)
{
    stream << photoSizeValue.tlType;
    switch (photoSizeValue.tlType) {
    case TLValue::PhotoSizeEmpty:
        stream << photoSizeValue.type;
        break;
    case TLValue::PhotoSize:
        stream << photoSizeValue.type;
        stream << photoSizeValue.location;
        stream << photoSizeValue.w;
        stream << photoSizeValue.h;
        stream << photoSizeValue.size;
        break;
    case TLValue::PhotoCachedSize:
        stream << photoSizeValue.type;
        stream << photoSizeValue.location;
        stream << photoSizeValue.w;
        stream << photoSizeValue.h;
        stream << photoSizeValue.bytes;
        break;
    case TLValue::PhotoStrippedSize:
        stream << photoSizeValue.type;
        stream << photoSizeValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPong &pongValue)
{
    stream << pongValue.tlType;
    switch (pongValue.tlType) {
    case TLValue::Pong:
        stream << pongValue.msgId;
        stream << pongValue.pingId;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPopularContact &popularContactValue)
{
    stream << popularContactValue.tlType;
    switch (popularContactValue.tlType) {
    case TLValue::PopularContact:
        stream << popularContactValue.clientId;
        stream << popularContactValue.importers;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPrivacyKey &privacyKeyValue)
{
    stream << privacyKeyValue.tlType;
    switch (privacyKeyValue.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
    case TLValue::PrivacyKeyChatInvite:
    case TLValue::PrivacyKeyPhoneCall:
    case TLValue::PrivacyKeyPhoneP2P:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPrivacyRule &privacyRuleValue)
{
    stream << privacyRuleValue.tlType;
    switch (privacyRuleValue.tlType) {
    case TLValue::PrivacyValueAllowContacts:
    case TLValue::PrivacyValueAllowAll:
    case TLValue::PrivacyValueDisallowContacts:
    case TLValue::PrivacyValueDisallowAll:
        break;
    case TLValue::PrivacyValueAllowUsers:
    case TLValue::PrivacyValueDisallowUsers:
        stream << privacyRuleValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLReceivedNotifyMessage &receivedNotifyMessageValue)
{
    stream << receivedNotifyMessageValue.tlType;
    switch (receivedNotifyMessageValue.tlType) {
    case TLValue::ReceivedNotifyMessage:
        stream << receivedNotifyMessageValue.id;
        stream << receivedNotifyMessageValue.flags;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLResPQ &resPQValue)
{
    stream << resPQValue.tlType;
    switch (resPQValue.tlType) {
    case TLValue::ResPQ:
        stream << resPQValue.nonce;
        stream << resPQValue.serverNonce;
        stream << resPQValue.pq;
        stream << resPQValue.serverPublicKeyFingerprints;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLRichText &richTextValue)
{
    stream << richTextValue.tlType;
    switch (richTextValue.tlType) {
    case TLValue::TextEmpty:
        break;
    case TLValue::TextPlain:
        stream << richTextValue.stringText;
        break;
    case TLValue::TextBold:
    case TLValue::TextItalic:
    case TLValue::TextUnderline:
    case TLValue::TextStrike:
    case TLValue::TextFixed:
    case TLValue::TextSubscript:
    case TLValue::TextSuperscript:
    case TLValue::TextMarked:
        stream << *richTextValue.richText;
        break;
    case TLValue::TextUrl:
        stream << *richTextValue.richText;
        stream << richTextValue.url;
        stream << richTextValue.webpageId;
        break;
    case TLValue::TextEmail:
        stream << *richTextValue.richText;
        stream << richTextValue.email;
        break;
    case TLValue::TextConcat:
        stream << richTextValue.texts;
        break;
    case TLValue::TextPhone:
        stream << *richTextValue.richText;
        stream << richTextValue.phone;
        break;
    case TLValue::TextImage:
        stream << richTextValue.documentId;
        stream << richTextValue.w;
        stream << richTextValue.h;
        break;
    case TLValue::TextAnchor:
        stream << *richTextValue.richText;
        stream << richTextValue.name;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLRpcDropAnswer &rpcDropAnswerValue)
{
    stream << rpcDropAnswerValue.tlType;
    switch (rpcDropAnswerValue.tlType) {
    case TLValue::RpcAnswerUnknown:
    case TLValue::RpcAnswerDroppedRunning:
        break;
    case TLValue::RpcAnswerDropped:
        stream << rpcDropAnswerValue.msgId;
        stream << rpcDropAnswerValue.seqNo;
        stream << rpcDropAnswerValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLRpcError &rpcErrorValue)
{
    stream << rpcErrorValue.tlType;
    switch (rpcErrorValue.tlType) {
    case TLValue::RpcError:
        stream << rpcErrorValue.errorCode;
        stream << rpcErrorValue.errorMessage;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLSavedContact &savedContactValue)
{
    stream << savedContactValue.tlType;
    switch (savedContactValue.tlType) {
    case TLValue::SavedPhoneContact:
        stream << savedContactValue.phone;
        stream << savedContactValue.firstName;
        stream << savedContactValue.lastName;
        stream << savedContactValue.date;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLSecureFile &secureFileValue)
{
    stream << secureFileValue.tlType;
    switch (secureFileValue.tlType) {
    case TLValue::SecureFileEmpty:
        break;
    case TLValue::SecureFile:
        stream << secureFileValue.id;
        stream << secureFileValue.accessHash;
        stream << secureFileValue.size;
        stream << secureFileValue.dcId;
        stream << secureFileValue.date;
        stream << secureFileValue.fileHash;
        stream << secureFileValue.secret;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLServerDHInnerData &serverDHInnerDataValue)
{
    stream << serverDHInnerDataValue.tlType;
    switch (serverDHInnerDataValue.tlType) {
    case TLValue::ServerDHInnerData:
        stream << serverDHInnerDataValue.nonce;
        stream << serverDHInnerDataValue.serverNonce;
        stream << serverDHInnerDataValue.g;
        stream << serverDHInnerDataValue.dhPrime;
        stream << serverDHInnerDataValue.gA;
        stream << serverDHInnerDataValue.serverTime;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLServerDHParams &serverDHParamsValue)
{
    stream << serverDHParamsValue.tlType;
    switch (serverDHParamsValue.tlType) {
    case TLValue::ServerDHParamsFail:
        stream << serverDHParamsValue.nonce;
        stream << serverDHParamsValue.serverNonce;
        stream << serverDHParamsValue.newNonceHash;
        break;
    case TLValue::ServerDHParamsOk:
        stream << serverDHParamsValue.nonce;
        stream << serverDHParamsValue.serverNonce;
        stream << serverDHParamsValue.encryptedAnswer;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLSetClientDHParamsAnswer &setClientDHParamsAnswerValue)
{
    stream << setClientDHParamsAnswerValue.tlType;
    switch (setClientDHParamsAnswerValue.tlType) {
    case TLValue::DhGenOk:
        stream << setClientDHParamsAnswerValue.nonce;
        stream << setClientDHParamsAnswerValue.serverNonce;
        stream << setClientDHParamsAnswerValue.newNonceHash1;
        break;
    case TLValue::DhGenRetry:
        stream << setClientDHParamsAnswerValue.nonce;
        stream << setClientDHParamsAnswerValue.serverNonce;
        stream << setClientDHParamsAnswerValue.newNonceHash2;
        break;
    case TLValue::DhGenFail:
        stream << setClientDHParamsAnswerValue.nonce;
        stream << setClientDHParamsAnswerValue.serverNonce;
        stream << setClientDHParamsAnswerValue.newNonceHash3;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLStatsURL &statsURLValue)
{
    stream << statsURLValue.tlType;
    switch (statsURLValue.tlType) {
    case TLValue::StatsURL:
        stream << statsURLValue.url;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLStickerPack &stickerPackValue)
{
    stream << stickerPackValue.tlType;
    switch (stickerPackValue.tlType) {
    case TLValue::StickerPack:
        stream << stickerPackValue.emoticon;
        stream << stickerPackValue.documents;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLStorageFileType &storageFileTypeValue)
{
    stream << storageFileTypeValue.tlType;
    switch (storageFileTypeValue.tlType) {
    case TLValue::StorageFileUnknown:
    case TLValue::StorageFilePartial:
    case TLValue::StorageFileJpeg:
    case TLValue::StorageFileGif:
    case TLValue::StorageFilePng:
    case TLValue::StorageFilePdf:
    case TLValue::StorageFileMp3:
    case TLValue::StorageFileMov:
    case TLValue::StorageFileMp4:
    case TLValue::StorageFileWebp:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLTopPeer &topPeerValue)
{
    stream << topPeerValue.tlType;
    switch (topPeerValue.tlType) {
    case TLValue::TopPeer:
        stream << topPeerValue.peer;
        stream << topPeerValue.rating;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLTopPeerCategoryPeers &topPeerCategoryPeersValue)
{
    stream << topPeerCategoryPeersValue.tlType;
    switch (topPeerCategoryPeersValue.tlType) {
    case TLValue::TopPeerCategoryPeers:
        stream << topPeerCategoryPeersValue.category;
        stream << topPeerCategoryPeersValue.count;
        stream << topPeerCategoryPeersValue.peers;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUpdatesState &updatesStateValue)
{
    stream << updatesStateValue.tlType;
    switch (updatesStateValue.tlType) {
    case TLValue::UpdatesState:
        stream << updatesStateValue.pts;
        stream << updatesStateValue.qts;
        stream << updatesStateValue.date;
        stream << updatesStateValue.seq;
        stream << updatesStateValue.unreadCount;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUploadCdnFile &uploadCdnFileValue)
{
    stream << uploadCdnFileValue.tlType;
    switch (uploadCdnFileValue.tlType) {
    case TLValue::UploadCdnFileReuploadNeeded:
        stream << uploadCdnFileValue.requestToken;
        break;
    case TLValue::UploadCdnFile:
        stream << uploadCdnFileValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUploadFile &uploadFileValue)
{
    stream << uploadFileValue.tlType;
    switch (uploadFileValue.tlType) {
    case TLValue::UploadFile:
        stream << uploadFileValue.type;
        stream << uploadFileValue.mtime;
        stream << uploadFileValue.bytes;
        break;
    case TLValue::UploadFileCdnRedirect:
        stream << uploadFileValue.dcId;
        stream << uploadFileValue.fileToken;
        stream << uploadFileValue.encryptionKey;
        stream << uploadFileValue.encryptionIv;
        stream << uploadFileValue.fileHashes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUploadWebFile &uploadWebFileValue)
{
    stream << uploadWebFileValue.tlType;
    switch (uploadWebFileValue.tlType) {
    case TLValue::UploadWebFile:
        stream << uploadWebFileValue.size;
        stream << uploadWebFileValue.mimeType;
        stream << uploadWebFileValue.fileType;
        stream << uploadWebFileValue.mtime;
        stream << uploadWebFileValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUserProfilePhoto &userProfilePhotoValue)
{
    stream << userProfilePhotoValue.tlType;
    switch (userProfilePhotoValue.tlType) {
    case TLValue::UserProfilePhotoEmpty:
        break;
    case TLValue::UserProfilePhoto:
        stream << userProfilePhotoValue.photoId;
        stream << userProfilePhotoValue.photoSmall;
        stream << userProfilePhotoValue.photoBig;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUserStatus &userStatusValue)
{
    stream << userStatusValue.tlType;
    switch (userStatusValue.tlType) {
    case TLValue::UserStatusEmpty:
    case TLValue::UserStatusRecently:
    case TLValue::UserStatusLastWeek:
    case TLValue::UserStatusLastMonth:
        break;
    case TLValue::UserStatusOnline:
        stream << userStatusValue.expires;
        break;
    case TLValue::UserStatusOffline:
        stream << userStatusValue.wasOnline;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLWallPaper &wallPaperValue)
{
    stream << wallPaperValue.tlType;
    switch (wallPaperValue.tlType) {
    case TLValue::WallPaper:
        stream << wallPaperValue.id;
        stream << wallPaperValue.title;
        stream << wallPaperValue.sizes;
        stream << wallPaperValue.color;
        break;
    case TLValue::WallPaperSolid:
        stream << wallPaperValue.id;
        stream << wallPaperValue.title;
        stream << wallPaperValue.bgColor;
        stream << wallPaperValue.color;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLWebAuthorization &webAuthorizationValue)
{
    stream << webAuthorizationValue.tlType;
    switch (webAuthorizationValue.tlType) {
    case TLValue::WebAuthorization:
        stream << webAuthorizationValue.hash;
        stream << webAuthorizationValue.botId;
        stream << webAuthorizationValue.domain;
        stream << webAuthorizationValue.browser;
        stream << webAuthorizationValue.platform;
        stream << webAuthorizationValue.dateCreated;
        stream << webAuthorizationValue.dateActive;
        stream << webAuthorizationValue.ip;
        stream << webAuthorizationValue.region;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccessPointRule &accessPointRuleValue)
{
    stream << accessPointRuleValue.tlType;
    switch (accessPointRuleValue.tlType) {
    case TLValue::AccessPointRule:
        stream << accessPointRuleValue.phonePrefixRules;
        stream << accessPointRuleValue.dcId;
        stream << accessPointRuleValue.ips;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountPassword &accountPasswordValue)
{
    stream << accountPasswordValue.tlType;
    switch (accountPasswordValue.tlType) {
    case TLValue::AccountPassword:
        stream << accountPasswordValue.flags;
        if (accountPasswordValue.flags & TLAccountPassword::CurrentAlgo) {
            stream << accountPasswordValue.currentAlgo;
        }
        if (accountPasswordValue.flags & TLAccountPassword::SrpB) {
            stream << accountPasswordValue.srpB;
        }
        if (accountPasswordValue.flags & TLAccountPassword::SrpId) {
            stream << accountPasswordValue.srpId;
        }
        if (accountPasswordValue.flags & TLAccountPassword::Hint) {
            stream << accountPasswordValue.hint;
        }
        if (accountPasswordValue.flags & TLAccountPassword::EmailUnconfirmedPattern) {
            stream << accountPasswordValue.emailUnconfirmedPattern;
        }
        stream << accountPasswordValue.newAlgo;
        stream << accountPasswordValue.newSecureAlgo;
        stream << accountPasswordValue.secureRandom;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountPasswordSettings &accountPasswordSettingsValue)
{
    stream << accountPasswordSettingsValue.tlType;
    switch (accountPasswordSettingsValue.tlType) {
    case TLValue::AccountPasswordSettings:
        stream << accountPasswordSettingsValue.flags;
        if (accountPasswordSettingsValue.flags & TLAccountPasswordSettings::Email) {
            stream << accountPasswordSettingsValue.email;
        }
        if (accountPasswordSettingsValue.flags & TLAccountPasswordSettings::SecureSettings) {
            stream << accountPasswordSettingsValue.secureSettings;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthorization &authorizationValue)
{
    stream << authorizationValue.tlType;
    switch (authorizationValue.tlType) {
    case TLValue::Authorization:
        stream << authorizationValue.flags;
        stream << authorizationValue.hash;
        stream << authorizationValue.deviceModel;
        stream << authorizationValue.platform;
        stream << authorizationValue.systemVersion;
        stream << authorizationValue.apiId;
        stream << authorizationValue.appName;
        stream << authorizationValue.appVersion;
        stream << authorizationValue.dateCreated;
        stream << authorizationValue.dateActive;
        stream << authorizationValue.ip;
        stream << authorizationValue.country;
        stream << authorizationValue.region;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLCdnConfig &cdnConfigValue)
{
    stream << cdnConfigValue.tlType;
    switch (cdnConfigValue.tlType) {
    case TLValue::CdnConfig:
        stream << cdnConfigValue.publicKeys;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelParticipant &channelParticipantValue)
{
    stream << channelParticipantValue.tlType;
    switch (channelParticipantValue.tlType) {
    case TLValue::ChannelParticipant:
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.date;
        break;
    case TLValue::ChannelParticipantSelf:
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.inviterId;
        stream << channelParticipantValue.date;
        break;
    case TLValue::ChannelParticipantCreator:
        stream << channelParticipantValue.userId;
        break;
    case TLValue::ChannelParticipantAdmin:
        stream << channelParticipantValue.flags;
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.inviterId;
        stream << channelParticipantValue.promotedBy;
        stream << channelParticipantValue.date;
        stream << channelParticipantValue.adminRights;
        break;
    case TLValue::ChannelParticipantBanned:
        stream << channelParticipantValue.flags;
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.kickedBy;
        stream << channelParticipantValue.date;
        stream << channelParticipantValue.bannedRights;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatPhoto &chatPhotoValue)
{
    stream << chatPhotoValue.tlType;
    switch (chatPhotoValue.tlType) {
    case TLValue::ChatPhotoEmpty:
        break;
    case TLValue::ChatPhoto:
        stream << chatPhotoValue.photoSmall;
        stream << chatPhotoValue.photoBig;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactStatus &contactStatusValue)
{
    stream << contactStatusValue.tlType;
    switch (contactStatusValue.tlType) {
    case TLValue::ContactStatus:
        stream << contactStatusValue.userId;
        stream << contactStatusValue.status;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDcOption &dcOptionValue)
{
    stream << dcOptionValue.tlType;
    switch (dcOptionValue.tlType) {
    case TLValue::DcOption:
        stream << dcOptionValue.flags;
        stream << dcOptionValue.id;
        stream << dcOptionValue.ipAddress;
        stream << dcOptionValue.port;
        if (dcOptionValue.flags & TLDcOption::Secret) {
            stream << dcOptionValue.secret;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDialogPeer &dialogPeerValue)
{
    stream << dialogPeerValue.tlType;
    switch (dialogPeerValue.tlType) {
    case TLValue::DialogPeer:
        stream << dialogPeerValue.peer;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDraftMessage &draftMessageValue)
{
    stream << draftMessageValue.tlType;
    switch (draftMessageValue.tlType) {
    case TLValue::DraftMessageEmpty:
        stream << draftMessageValue.flags;
        if (draftMessageValue.flags & TLDraftMessage::Date) {
            stream << draftMessageValue.date;
        }
        break;
    case TLValue::DraftMessage:
        stream << draftMessageValue.flags;
        if (draftMessageValue.flags & TLDraftMessage::ReplyToMsgId) {
            stream << draftMessageValue.replyToMsgId;
        }
        stream << draftMessageValue.message;
        if (draftMessageValue.flags & TLDraftMessage::Entities) {
            stream << draftMessageValue.entities;
        }
        stream << draftMessageValue.date;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpConfigSimple &helpConfigSimpleValue)
{
    stream << helpConfigSimpleValue.tlType;
    switch (helpConfigSimpleValue.tlType) {
    case TLValue::HelpConfigSimple:
        stream << helpConfigSimpleValue.date;
        stream << helpConfigSimpleValue.expires;
        stream << helpConfigSimpleValue.rules;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpDeepLinkInfo &helpDeepLinkInfoValue)
{
    stream << helpDeepLinkInfoValue.tlType;
    switch (helpDeepLinkInfoValue.tlType) {
    case TLValue::HelpDeepLinkInfoEmpty:
        break;
    case TLValue::HelpDeepLinkInfo:
        stream << helpDeepLinkInfoValue.flags;
        stream << helpDeepLinkInfoValue.message;
        if (helpDeepLinkInfoValue.flags & TLHelpDeepLinkInfo::Entities) {
            stream << helpDeepLinkInfoValue.entities;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpTermsOfService &helpTermsOfServiceValue)
{
    stream << helpTermsOfServiceValue.tlType;
    switch (helpTermsOfServiceValue.tlType) {
    case TLValue::HelpTermsOfService:
        stream << helpTermsOfServiceValue.flags;
        stream << helpTermsOfServiceValue.id;
        stream << helpTermsOfServiceValue.text;
        stream << helpTermsOfServiceValue.entities;
        if (helpTermsOfServiceValue.flags & TLHelpTermsOfService::MinAgeConfirm) {
            stream << helpTermsOfServiceValue.minAgeConfirm;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpTermsOfServiceUpdate &helpTermsOfServiceUpdateValue)
{
    stream << helpTermsOfServiceUpdateValue.tlType;
    switch (helpTermsOfServiceUpdateValue.tlType) {
    case TLValue::HelpTermsOfServiceUpdateEmpty:
        stream << helpTermsOfServiceUpdateValue.expires;
        break;
    case TLValue::HelpTermsOfServiceUpdate:
        stream << helpTermsOfServiceUpdateValue.expires;
        stream << helpTermsOfServiceUpdateValue.termsOfService;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpUserInfo &helpUserInfoValue)
{
    stream << helpUserInfoValue.tlType;
    switch (helpUserInfoValue.tlType) {
    case TLValue::HelpUserInfoEmpty:
        break;
    case TLValue::HelpUserInfo:
        stream << helpUserInfoValue.message;
        stream << helpUserInfoValue.entities;
        stream << helpUserInfoValue.author;
        stream << helpUserInfoValue.date;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLLangPackDifference &langPackDifferenceValue)
{
    stream << langPackDifferenceValue.tlType;
    switch (langPackDifferenceValue.tlType) {
    case TLValue::LangPackDifference:
        stream << langPackDifferenceValue.langCode;
        stream << langPackDifferenceValue.fromVersion;
        stream << langPackDifferenceValue.version;
        stream << langPackDifferenceValue.strings;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLLangPackLanguage &langPackLanguageValue)
{
    stream << langPackLanguageValue.tlType;
    switch (langPackLanguageValue.tlType) {
    case TLValue::LangPackLanguage:
        stream << langPackLanguageValue.flags;
        stream << langPackLanguageValue.name;
        stream << langPackLanguageValue.nativeName;
        stream << langPackLanguageValue.langCode;
        if (langPackLanguageValue.flags & TLLangPackLanguage::BaseLangCode) {
            stream << langPackLanguageValue.baseLangCode;
        }
        stream << langPackLanguageValue.pluralCode;
        stream << langPackLanguageValue.stringsCount;
        stream << langPackLanguageValue.translatedCount;
        stream << langPackLanguageValue.translationsUrl;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessageFwdHeader &messageFwdHeaderValue)
{
    stream << messageFwdHeaderValue.tlType;
    switch (messageFwdHeaderValue.tlType) {
    case TLValue::MessageFwdHeader:
        stream << messageFwdHeaderValue.flags;
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::FromId) {
            stream << messageFwdHeaderValue.fromId;
        }
        stream << messageFwdHeaderValue.date;
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::ChannelId) {
            stream << messageFwdHeaderValue.channelId;
        }
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::ChannelPost) {
            stream << messageFwdHeaderValue.channelPost;
        }
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::PostAuthor) {
            stream << messageFwdHeaderValue.postAuthor;
        }
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::SavedFromPeer) {
            stream << messageFwdHeaderValue.savedFromPeer;
        }
        if (messageFwdHeaderValue.flags & TLMessageFwdHeader::SavedFromMsgId) {
            stream << messageFwdHeaderValue.savedFromMsgId;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesBotCallbackAnswer &messagesBotCallbackAnswerValue)
{
    stream << messagesBotCallbackAnswerValue.tlType;
    switch (messagesBotCallbackAnswerValue.tlType) {
    case TLValue::MessagesBotCallbackAnswer:
        stream << messagesBotCallbackAnswerValue.flags;
        if (messagesBotCallbackAnswerValue.flags & TLMessagesBotCallbackAnswer::Message) {
            stream << messagesBotCallbackAnswerValue.message;
        }
        if (messagesBotCallbackAnswerValue.flags & TLMessagesBotCallbackAnswer::Url) {
            stream << messagesBotCallbackAnswerValue.url;
        }
        stream << messagesBotCallbackAnswerValue.cacheTime;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesMessageEditData &messagesMessageEditDataValue)
{
    stream << messagesMessageEditDataValue.tlType;
    switch (messagesMessageEditDataValue.tlType) {
    case TLValue::MessagesMessageEditData:
        stream << messagesMessageEditDataValue.flags;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLNotifyPeer &notifyPeerValue)
{
    stream << notifyPeerValue.tlType;
    switch (notifyPeerValue.tlType) {
    case TLValue::NotifyPeer:
        stream << notifyPeerValue.peer;
        break;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyBroadcasts:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageTableCell &pageTableCellValue)
{
    stream << pageTableCellValue.tlType;
    switch (pageTableCellValue.tlType) {
    case TLValue::PageTableCell:
        stream << pageTableCellValue.flags;
        if (pageTableCellValue.flags & TLPageTableCell::Text) {
            stream << pageTableCellValue.text;
        }
        if (pageTableCellValue.flags & TLPageTableCell::Colspan) {
            stream << pageTableCellValue.colspan;
        }
        if (pageTableCellValue.flags & TLPageTableCell::Rowspan) {
            stream << pageTableCellValue.rowspan;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageTableRow &pageTableRowValue)
{
    stream << pageTableRowValue.tlType;
    switch (pageTableRowValue.tlType) {
    case TLValue::PageTableRow:
        stream << pageTableRowValue.cells;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentsSavedInfo &paymentsSavedInfoValue)
{
    stream << paymentsSavedInfoValue.tlType;
    switch (paymentsSavedInfoValue.tlType) {
    case TLValue::PaymentsSavedInfo:
        stream << paymentsSavedInfoValue.flags;
        if (paymentsSavedInfoValue.flags & TLPaymentsSavedInfo::SavedInfo) {
            stream << paymentsSavedInfoValue.savedInfo;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentsValidatedRequestedInfo &paymentsValidatedRequestedInfoValue)
{
    stream << paymentsValidatedRequestedInfoValue.tlType;
    switch (paymentsValidatedRequestedInfoValue.tlType) {
    case TLValue::PaymentsValidatedRequestedInfo:
        stream << paymentsValidatedRequestedInfoValue.flags;
        if (paymentsValidatedRequestedInfoValue.flags & TLPaymentsValidatedRequestedInfo::Id) {
            stream << paymentsValidatedRequestedInfoValue.id;
        }
        if (paymentsValidatedRequestedInfoValue.flags & TLPaymentsValidatedRequestedInfo::ShippingOptions) {
            stream << paymentsValidatedRequestedInfoValue.shippingOptions;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPeerSettings &peerSettingsValue)
{
    stream << peerSettingsValue.tlType;
    switch (peerSettingsValue.tlType) {
    case TLValue::PeerSettings:
        stream << peerSettingsValue.flags;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhoto &photoValue)
{
    stream << photoValue.tlType;
    switch (photoValue.tlType) {
    case TLValue::PhotoEmpty:
        stream << photoValue.id;
        break;
    case TLValue::Photo:
        stream << photoValue.flags;
        stream << photoValue.id;
        stream << photoValue.accessHash;
        stream << photoValue.fileReference;
        stream << photoValue.date;
        stream << photoValue.sizes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPollAnswerVoters &pollAnswerVotersValue)
{
    stream << pollAnswerVotersValue.tlType;
    switch (pollAnswerVotersValue.tlType) {
    case TLValue::PollAnswerVoters:
        stream << pollAnswerVotersValue.flags;
        stream << pollAnswerVotersValue.option;
        stream << pollAnswerVotersValue.voters;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPollResults &pollResultsValue)
{
    stream << pollResultsValue.tlType;
    switch (pollResultsValue.tlType) {
    case TLValue::PollResults:
        stream << pollResultsValue.flags;
        if (pollResultsValue.flags & TLPollResults::Results) {
            stream << pollResultsValue.results;
        }
        if (pollResultsValue.flags & TLPollResults::TotalVoters) {
            stream << pollResultsValue.totalVoters;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLSecureRequiredType &secureRequiredTypeValue)
{
    stream << secureRequiredTypeValue.tlType;
    switch (secureRequiredTypeValue.tlType) {
    case TLValue::SecureRequiredType:
        stream << secureRequiredTypeValue.flags;
        stream << secureRequiredTypeValue.type;
        break;
    case TLValue::SecureRequiredTypeOneOf:
        stream << secureRequiredTypeValue.types;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLSecureValue &secureValueValue)
{
    stream << secureValueValue.tlType;
    switch (secureValueValue.tlType) {
    case TLValue::SecureValue:
        stream << secureValueValue.flags;
        stream << secureValueValue.type;
        if (secureValueValue.flags & TLSecureValue::Data) {
            stream << secureValueValue.data;
        }
        if (secureValueValue.flags & TLSecureValue::FrontSide) {
            stream << secureValueValue.frontSide;
        }
        if (secureValueValue.flags & TLSecureValue::ReverseSide) {
            stream << secureValueValue.reverseSide;
        }
        if (secureValueValue.flags & TLSecureValue::Selfie) {
            stream << secureValueValue.selfie;
        }
        if (secureValueValue.flags & TLSecureValue::Translation) {
            stream << secureValueValue.translation;
        }
        if (secureValueValue.flags & TLSecureValue::Files) {
            stream << secureValueValue.files;
        }
        if (secureValueValue.flags & TLSecureValue::PlainData) {
            stream << secureValueValue.plainData;
        }
        stream << secureValueValue.hash;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLStickerSet &stickerSetValue)
{
    stream << stickerSetValue.tlType;
    switch (stickerSetValue.tlType) {
    case TLValue::StickerSet:
        stream << stickerSetValue.flags;
        if (stickerSetValue.flags & TLStickerSet::InstalledDate) {
            stream << stickerSetValue.installedDate;
        }
        stream << stickerSetValue.id;
        stream << stickerSetValue.accessHash;
        stream << stickerSetValue.title;
        stream << stickerSetValue.shortName;
        stream << stickerSetValue.count;
        stream << stickerSetValue.hash;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUser &userValue)
{
    stream << userValue.tlType;
    switch (userValue.tlType) {
    case TLValue::UserEmpty:
        stream << userValue.id;
        break;
    case TLValue::User:
        stream << userValue.flags;
        stream << userValue.id;
        if (userValue.flags & TLUser::AccessHash) {
            stream << userValue.accessHash;
        }
        if (userValue.flags & TLUser::FirstName) {
            stream << userValue.firstName;
        }
        if (userValue.flags & TLUser::LastName) {
            stream << userValue.lastName;
        }
        if (userValue.flags & TLUser::Username) {
            stream << userValue.username;
        }
        if (userValue.flags & TLUser::Phone) {
            stream << userValue.phone;
        }
        if (userValue.flags & TLUser::Photo) {
            stream << userValue.photo;
        }
        if (userValue.flags & TLUser::Status) {
            stream << userValue.status;
        }
        if (userValue.flags & TLUser::BotInfoVersion) {
            stream << userValue.botInfoVersion;
        }
        if (userValue.flags & TLUser::RestrictionReason) {
            stream << userValue.restrictionReason;
        }
        if (userValue.flags & TLUser::BotInlinePlaceholder) {
            stream << userValue.botInlinePlaceholder;
        }
        if (userValue.flags & TLUser::LangCode) {
            stream << userValue.langCode;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLWebDocument &webDocumentValue)
{
    stream << webDocumentValue.tlType;
    switch (webDocumentValue.tlType) {
    case TLValue::WebDocument:
        stream << webDocumentValue.url;
        stream << webDocumentValue.accessHash;
        stream << webDocumentValue.size;
        stream << webDocumentValue.mimeType;
        stream << webDocumentValue.attributes;
        break;
    case TLValue::WebDocumentNoProxy:
        stream << webDocumentValue.url;
        stream << webDocumentValue.size;
        stream << webDocumentValue.mimeType;
        stream << webDocumentValue.attributes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountAuthorizationForm &accountAuthorizationFormValue)
{
    stream << accountAuthorizationFormValue.tlType;
    switch (accountAuthorizationFormValue.tlType) {
    case TLValue::AccountAuthorizationForm:
        stream << accountAuthorizationFormValue.flags;
        stream << accountAuthorizationFormValue.requiredTypes;
        stream << accountAuthorizationFormValue.values;
        stream << accountAuthorizationFormValue.errors;
        stream << accountAuthorizationFormValue.users;
        if (accountAuthorizationFormValue.flags & TLAccountAuthorizationForm::PrivacyPolicyUrl) {
            stream << accountAuthorizationFormValue.privacyPolicyUrl;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountAuthorizations &accountAuthorizationsValue)
{
    stream << accountAuthorizationsValue.tlType;
    switch (accountAuthorizationsValue.tlType) {
    case TLValue::AccountAuthorizations:
        stream << accountAuthorizationsValue.authorizations;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountPrivacyRules &accountPrivacyRulesValue)
{
    stream << accountPrivacyRulesValue.tlType;
    switch (accountPrivacyRulesValue.tlType) {
    case TLValue::AccountPrivacyRules:
        stream << accountPrivacyRulesValue.rules;
        stream << accountPrivacyRulesValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAccountWebAuthorizations &accountWebAuthorizationsValue)
{
    stream << accountWebAuthorizationsValue.tlType;
    switch (accountWebAuthorizationsValue.tlType) {
    case TLValue::AccountWebAuthorizations:
        stream << accountWebAuthorizationsValue.authorizations;
        stream << accountWebAuthorizationsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthAuthorization &authAuthorizationValue)
{
    stream << authAuthorizationValue.tlType;
    switch (authAuthorizationValue.tlType) {
    case TLValue::AuthAuthorization:
        stream << authAuthorizationValue.flags;
        if (authAuthorizationValue.flags & TLAuthAuthorization::TmpSessions) {
            stream << authAuthorizationValue.tmpSessions;
        }
        stream << authAuthorizationValue.user;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLAuthSentCode &authSentCodeValue)
{
    stream << authSentCodeValue.tlType;
    switch (authSentCodeValue.tlType) {
    case TLValue::AuthSentCode:
        stream << authSentCodeValue.flags;
        stream << authSentCodeValue.type;
        stream << authSentCodeValue.phoneCodeHash;
        if (authSentCodeValue.flags & TLAuthSentCode::NextType) {
            stream << authSentCodeValue.nextType;
        }
        if (authSentCodeValue.flags & TLAuthSentCode::Timeout) {
            stream << authSentCodeValue.timeout;
        }
        if (authSentCodeValue.flags & TLAuthSentCode::TermsOfService) {
            stream << authSentCodeValue.termsOfService;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLBotInlineMessage &botInlineMessageValue)
{
    stream << botInlineMessageValue.tlType;
    switch (botInlineMessageValue.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
    case TLValue::BotInlineMessageText:
        stream << botInlineMessageValue.flags;
        stream << botInlineMessageValue.message;
        if (botInlineMessageValue.flags & TLBotInlineMessage::Entities) {
            stream << botInlineMessageValue.entities;
        }
        if (botInlineMessageValue.flags & TLBotInlineMessage::ReplyMarkup) {
            stream << botInlineMessageValue.replyMarkup;
        }
        break;
    case TLValue::BotInlineMessageMediaGeo:
        stream << botInlineMessageValue.flags;
        stream << botInlineMessageValue.geo;
        stream << botInlineMessageValue.period;
        if (botInlineMessageValue.flags & TLBotInlineMessage::ReplyMarkup) {
            stream << botInlineMessageValue.replyMarkup;
        }
        break;
    case TLValue::BotInlineMessageMediaVenue:
        stream << botInlineMessageValue.flags;
        stream << botInlineMessageValue.geo;
        stream << botInlineMessageValue.title;
        stream << botInlineMessageValue.address;
        stream << botInlineMessageValue.provider;
        stream << botInlineMessageValue.venueId;
        stream << botInlineMessageValue.venueType;
        if (botInlineMessageValue.flags & TLBotInlineMessage::ReplyMarkup) {
            stream << botInlineMessageValue.replyMarkup;
        }
        break;
    case TLValue::BotInlineMessageMediaContact:
        stream << botInlineMessageValue.flags;
        stream << botInlineMessageValue.phoneNumber;
        stream << botInlineMessageValue.firstName;
        stream << botInlineMessageValue.lastName;
        stream << botInlineMessageValue.vcard;
        if (botInlineMessageValue.flags & TLBotInlineMessage::ReplyMarkup) {
            stream << botInlineMessageValue.replyMarkup;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelsChannelParticipant &channelsChannelParticipantValue)
{
    stream << channelsChannelParticipantValue.tlType;
    switch (channelsChannelParticipantValue.tlType) {
    case TLValue::ChannelsChannelParticipant:
        stream << channelsChannelParticipantValue.participant;
        stream << channelsChannelParticipantValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelsChannelParticipants &channelsChannelParticipantsValue)
{
    stream << channelsChannelParticipantsValue.tlType;
    switch (channelsChannelParticipantsValue.tlType) {
    case TLValue::ChannelsChannelParticipants:
        stream << channelsChannelParticipantsValue.count;
        stream << channelsChannelParticipantsValue.participants;
        stream << channelsChannelParticipantsValue.users;
        break;
    case TLValue::ChannelsChannelParticipantsNotModified:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChat &chatValue)
{
    stream << chatValue.tlType;
    switch (chatValue.tlType) {
    case TLValue::ChatEmpty:
        stream << chatValue.id;
        break;
    case TLValue::Chat:
        stream << chatValue.flags;
        stream << chatValue.id;
        stream << chatValue.title;
        stream << chatValue.photo;
        stream << chatValue.participantsCount;
        stream << chatValue.date;
        stream << chatValue.version;
        if (chatValue.flags & TLChat::MigratedTo) {
            stream << chatValue.migratedTo;
        }
        break;
    case TLValue::ChatForbidden:
        stream << chatValue.id;
        stream << chatValue.title;
        break;
    case TLValue::Channel:
        stream << chatValue.flags;
        stream << chatValue.id;
        if (chatValue.flags & TLChat::AccessHash) {
            stream << chatValue.accessHash;
        }
        stream << chatValue.title;
        if (chatValue.flags & TLChat::Username) {
            stream << chatValue.username;
        }
        stream << chatValue.photo;
        stream << chatValue.date;
        stream << chatValue.version;
        if (chatValue.flags & TLChat::RestrictionReason) {
            stream << chatValue.restrictionReason;
        }
        if (chatValue.flags & TLChat::AdminRights) {
            stream << chatValue.adminRights;
        }
        if (chatValue.flags & TLChat::BannedRights) {
            stream << chatValue.bannedRights;
        }
        if (chatValue.flags & TLChat::ParticipantsCount) {
            stream << chatValue.participantsCount;
        }
        break;
    case TLValue::ChannelForbidden:
        stream << chatValue.flags;
        stream << chatValue.id;
        stream << chatValue.accessHash;
        stream << chatValue.title;
        if (chatValue.flags & TLChat::UntilDate) {
            stream << chatValue.untilDate;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatFull &chatFullValue)
{
    stream << chatFullValue.tlType;
    switch (chatFullValue.tlType) {
    case TLValue::ChatFull:
        stream << chatFullValue.flags;
        stream << chatFullValue.id;
        stream << chatFullValue.participants;
        if (chatFullValue.flags & TLChatFull::ChatPhoto) {
            stream << chatFullValue.chatPhoto;
        }
        stream << chatFullValue.notifySettings;
        stream << chatFullValue.exportedInvite;
        if (chatFullValue.flags & TLChatFull::BotInfo) {
            stream << chatFullValue.botInfo;
        }
        if (chatFullValue.flags & TLChatFull::PinnedMsgId6) {
            stream << chatFullValue.pinnedMsgId;
        }
        break;
    case TLValue::ChannelFull:
        stream << chatFullValue.flags;
        stream << chatFullValue.id;
        stream << chatFullValue.about;
        if (chatFullValue.flags & TLChatFull::ParticipantsCount) {
            stream << chatFullValue.participantsCount;
        }
        if (chatFullValue.flags & TLChatFull::AdminsCount) {
            stream << chatFullValue.adminsCount;
        }
        if (chatFullValue.flags & TLChatFull::KickedCount) {
            stream << chatFullValue.kickedCount;
        }
        if (chatFullValue.flags & TLChatFull::BannedCount) {
            stream << chatFullValue.bannedCount;
        }
        if (chatFullValue.flags & TLChatFull::OnlineCount) {
            stream << chatFullValue.onlineCount;
        }
        stream << chatFullValue.readInboxMaxId;
        stream << chatFullValue.readOutboxMaxId;
        stream << chatFullValue.unreadCount;
        stream << chatFullValue.chatPhoto;
        stream << chatFullValue.notifySettings;
        stream << chatFullValue.exportedInvite;
        stream << chatFullValue.botInfo;
        if (chatFullValue.flags & TLChatFull::MigratedFromChatId) {
            stream << chatFullValue.migratedFromChatId;
        }
        if (chatFullValue.flags & TLChatFull::MigratedFromMaxId) {
            stream << chatFullValue.migratedFromMaxId;
        }
        if (chatFullValue.flags & TLChatFull::PinnedMsgId5) {
            stream << chatFullValue.pinnedMsgId;
        }
        if (chatFullValue.flags & TLChatFull::Stickerset) {
            stream << chatFullValue.stickerset;
        }
        if (chatFullValue.flags & TLChatFull::AvailableMinId) {
            stream << chatFullValue.availableMinId;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChatInvite &chatInviteValue)
{
    stream << chatInviteValue.tlType;
    switch (chatInviteValue.tlType) {
    case TLValue::ChatInviteAlready:
        stream << chatInviteValue.chat;
        break;
    case TLValue::ChatInvite:
        stream << chatInviteValue.flags;
        stream << chatInviteValue.title;
        stream << chatInviteValue.photo;
        stream << chatInviteValue.participantsCount;
        if (chatInviteValue.flags & TLChatInvite::Participants) {
            stream << chatInviteValue.participants;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLConfig &configValue)
{
    stream << configValue.tlType;
    switch (configValue.tlType) {
    case TLValue::Config:
        stream << configValue.flags;
        stream << configValue.date;
        stream << configValue.expires;
        stream << configValue.testMode;
        stream << configValue.thisDc;
        stream << configValue.dcOptions;
        stream << configValue.dcTxtDomainName;
        stream << configValue.chatSizeMax;
        stream << configValue.megagroupSizeMax;
        stream << configValue.forwardedCountMax;
        stream << configValue.onlineUpdatePeriodMs;
        stream << configValue.offlineBlurTimeoutMs;
        stream << configValue.offlineIdleTimeoutMs;
        stream << configValue.onlineCloudTimeoutMs;
        stream << configValue.notifyCloudDelayMs;
        stream << configValue.notifyDefaultDelayMs;
        stream << configValue.pushChatPeriodMs;
        stream << configValue.pushChatLimit;
        stream << configValue.savedGifsLimit;
        stream << configValue.editTimeLimit;
        stream << configValue.revokeTimeLimit;
        stream << configValue.revokePmTimeLimit;
        stream << configValue.ratingEDecay;
        stream << configValue.stickersRecentLimit;
        stream << configValue.stickersFavedLimit;
        stream << configValue.channelsReadMediaPeriod;
        if (configValue.flags & TLConfig::TmpSessions) {
            stream << configValue.tmpSessions;
        }
        stream << configValue.pinnedDialogsCountMax;
        stream << configValue.callReceiveTimeoutMs;
        stream << configValue.callRingTimeoutMs;
        stream << configValue.callConnectTimeoutMs;
        stream << configValue.callPacketTimeoutMs;
        stream << configValue.meUrlPrefix;
        if (configValue.flags & TLConfig::AutoupdateUrlPrefix) {
            stream << configValue.autoupdateUrlPrefix;
        }
        if (configValue.flags & TLConfig::GifSearchUsername) {
            stream << configValue.gifSearchUsername;
        }
        if (configValue.flags & TLConfig::VenueSearchUsername) {
            stream << configValue.venueSearchUsername;
        }
        if (configValue.flags & TLConfig::ImgSearchUsername) {
            stream << configValue.imgSearchUsername;
        }
        if (configValue.flags & TLConfig::StaticMapsProvider) {
            stream << configValue.staticMapsProvider;
        }
        stream << configValue.captionLengthMax;
        stream << configValue.messageLengthMax;
        stream << configValue.webfileDcId;
        if (configValue.flags & TLConfig::SuggestedLangCode) {
            stream << configValue.suggestedLangCode;
        }
        if (configValue.flags & TLConfig::LangPackVersion) {
            stream << configValue.langPackVersion;
        }
        if (configValue.flags & TLConfig::BaseLangPackVersion) {
            stream << configValue.baseLangPackVersion;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsBlocked &contactsBlockedValue)
{
    stream << contactsBlockedValue.tlType;
    switch (contactsBlockedValue.tlType) {
    case TLValue::ContactsBlocked:
        stream << contactsBlockedValue.blocked;
        stream << contactsBlockedValue.users;
        break;
    case TLValue::ContactsBlockedSlice:
        stream << contactsBlockedValue.count;
        stream << contactsBlockedValue.blocked;
        stream << contactsBlockedValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsContacts &contactsContactsValue)
{
    stream << contactsContactsValue.tlType;
    switch (contactsContactsValue.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        stream << contactsContactsValue.contacts;
        stream << contactsContactsValue.savedCount;
        stream << contactsContactsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsFound &contactsFoundValue)
{
    stream << contactsFoundValue.tlType;
    switch (contactsFoundValue.tlType) {
    case TLValue::ContactsFound:
        stream << contactsFoundValue.myResults;
        stream << contactsFoundValue.results;
        stream << contactsFoundValue.chats;
        stream << contactsFoundValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsImportedContacts &contactsImportedContactsValue)
{
    stream << contactsImportedContactsValue.tlType;
    switch (contactsImportedContactsValue.tlType) {
    case TLValue::ContactsImportedContacts:
        stream << contactsImportedContactsValue.imported;
        stream << contactsImportedContactsValue.popularInvites;
        stream << contactsImportedContactsValue.retryContacts;
        stream << contactsImportedContactsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsLink &contactsLinkValue)
{
    stream << contactsLinkValue.tlType;
    switch (contactsLinkValue.tlType) {
    case TLValue::ContactsLink:
        stream << contactsLinkValue.myLink;
        stream << contactsLinkValue.foreignLink;
        stream << contactsLinkValue.user;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsResolvedPeer &contactsResolvedPeerValue)
{
    stream << contactsResolvedPeerValue.tlType;
    switch (contactsResolvedPeerValue.tlType) {
    case TLValue::ContactsResolvedPeer:
        stream << contactsResolvedPeerValue.peer;
        stream << contactsResolvedPeerValue.chats;
        stream << contactsResolvedPeerValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLContactsTopPeers &contactsTopPeersValue)
{
    stream << contactsTopPeersValue.tlType;
    switch (contactsTopPeersValue.tlType) {
    case TLValue::ContactsTopPeersNotModified:
    case TLValue::ContactsTopPeersDisabled:
        break;
    case TLValue::ContactsTopPeers:
        stream << contactsTopPeersValue.categories;
        stream << contactsTopPeersValue.chats;
        stream << contactsTopPeersValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDialog &dialogValue)
{
    stream << dialogValue.tlType;
    switch (dialogValue.tlType) {
    case TLValue::Dialog:
        stream << dialogValue.flags;
        stream << dialogValue.peer;
        stream << dialogValue.topMessage;
        stream << dialogValue.readInboxMaxId;
        stream << dialogValue.readOutboxMaxId;
        stream << dialogValue.unreadCount;
        stream << dialogValue.unreadMentionsCount;
        stream << dialogValue.notifySettings;
        if (dialogValue.flags & TLDialog::Pts) {
            stream << dialogValue.pts;
        }
        if (dialogValue.flags & TLDialog::Draft) {
            stream << dialogValue.draft;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLDocument &documentValue)
{
    stream << documentValue.tlType;
    switch (documentValue.tlType) {
    case TLValue::DocumentEmpty:
        stream << documentValue.id;
        break;
    case TLValue::Document:
        stream << documentValue.id;
        stream << documentValue.accessHash;
        stream << documentValue.fileReference;
        stream << documentValue.date;
        stream << documentValue.mimeType;
        stream << documentValue.size;
        stream << documentValue.thumb;
        stream << documentValue.dcId;
        stream << documentValue.attributes;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLFoundGif &foundGifValue)
{
    stream << foundGifValue.tlType;
    switch (foundGifValue.tlType) {
    case TLValue::FoundGif:
        stream << foundGifValue.url;
        stream << foundGifValue.thumbUrl;
        stream << foundGifValue.contentUrl;
        stream << foundGifValue.contentType;
        stream << foundGifValue.w;
        stream << foundGifValue.h;
        break;
    case TLValue::FoundGifCached:
        stream << foundGifValue.url;
        stream << foundGifValue.photo;
        stream << foundGifValue.document;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLGame &gameValue)
{
    stream << gameValue.tlType;
    switch (gameValue.tlType) {
    case TLValue::Game:
        stream << gameValue.flags;
        stream << gameValue.id;
        stream << gameValue.accessHash;
        stream << gameValue.shortName;
        stream << gameValue.title;
        stream << gameValue.description;
        stream << gameValue.photo;
        if (gameValue.flags & TLGame::Document) {
            stream << gameValue.document;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpAppUpdate &helpAppUpdateValue)
{
    stream << helpAppUpdateValue.tlType;
    switch (helpAppUpdateValue.tlType) {
    case TLValue::HelpAppUpdate:
        stream << helpAppUpdateValue.flags;
        stream << helpAppUpdateValue.id;
        stream << helpAppUpdateValue.version;
        stream << helpAppUpdateValue.text;
        stream << helpAppUpdateValue.entities;
        if (helpAppUpdateValue.flags & TLHelpAppUpdate::Document) {
            stream << helpAppUpdateValue.document;
        }
        if (helpAppUpdateValue.flags & TLHelpAppUpdate::Url) {
            stream << helpAppUpdateValue.url;
        }
        break;
    case TLValue::HelpNoAppUpdate:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpProxyData &helpProxyDataValue)
{
    stream << helpProxyDataValue.tlType;
    switch (helpProxyDataValue.tlType) {
    case TLValue::HelpProxyDataEmpty:
        stream << helpProxyDataValue.expires;
        break;
    case TLValue::HelpProxyDataPromo:
        stream << helpProxyDataValue.expires;
        stream << helpProxyDataValue.peer;
        stream << helpProxyDataValue.chats;
        stream << helpProxyDataValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpSupport &helpSupportValue)
{
    stream << helpSupportValue.tlType;
    switch (helpSupportValue.tlType) {
    case TLValue::HelpSupport:
        stream << helpSupportValue.phoneNumber;
        stream << helpSupportValue.user;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessageAction &messageActionValue)
{
    stream << messageActionValue.tlType;
    switch (messageActionValue.tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
    case TLValue::MessageActionPinMessage:
    case TLValue::MessageActionHistoryClear:
    case TLValue::MessageActionScreenshotTaken:
    case TLValue::MessageActionContactSignUp:
        break;
    case TLValue::MessageActionChatCreate:
        stream << messageActionValue.title;
        stream << messageActionValue.users;
        break;
    case TLValue::MessageActionChatEditTitle:
    case TLValue::MessageActionChannelCreate:
        stream << messageActionValue.title;
        break;
    case TLValue::MessageActionChatEditPhoto:
        stream << messageActionValue.photo;
        break;
    case TLValue::MessageActionChatAddUser:
        stream << messageActionValue.users;
        break;
    case TLValue::MessageActionChatDeleteUser:
        stream << messageActionValue.userId;
        break;
    case TLValue::MessageActionChatJoinedByLink:
        stream << messageActionValue.inviterId;
        break;
    case TLValue::MessageActionChatMigrateTo:
        stream << messageActionValue.channelId;
        break;
    case TLValue::MessageActionChannelMigrateFrom:
        stream << messageActionValue.title;
        stream << messageActionValue.chatId;
        break;
    case TLValue::MessageActionGameScore:
        stream << messageActionValue.gameId;
        stream << messageActionValue.score;
        break;
    case TLValue::MessageActionPaymentSentMe:
        stream << messageActionValue.flags;
        stream << messageActionValue.currency;
        stream << messageActionValue.totalAmount;
        stream << messageActionValue.payload;
        if (messageActionValue.flags & TLMessageAction::Info) {
            stream << messageActionValue.info;
        }
        if (messageActionValue.flags & TLMessageAction::ShippingOptionId) {
            stream << messageActionValue.shippingOptionId;
        }
        stream << messageActionValue.charge;
        break;
    case TLValue::MessageActionPaymentSent:
        stream << messageActionValue.currency;
        stream << messageActionValue.totalAmount;
        break;
    case TLValue::MessageActionPhoneCall:
        stream << messageActionValue.flags;
        stream << messageActionValue.callId;
        if (messageActionValue.flags & TLMessageAction::Reason) {
            stream << messageActionValue.reason;
        }
        if (messageActionValue.flags & TLMessageAction::Duration) {
            stream << messageActionValue.duration;
        }
        break;
    case TLValue::MessageActionCustomAction:
        stream << messageActionValue.message;
        break;
    case TLValue::MessageActionBotAllowed:
        stream << messageActionValue.domain;
        break;
    case TLValue::MessageActionSecureValuesSentMe:
        stream << messageActionValue.values;
        stream << messageActionValue.credentials;
        break;
    case TLValue::MessageActionSecureValuesSent:
        stream << messageActionValue.types;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesAllStickers &messagesAllStickersValue)
{
    stream << messagesAllStickersValue.tlType;
    switch (messagesAllStickersValue.tlType) {
    case TLValue::MessagesAllStickersNotModified:
        break;
    case TLValue::MessagesAllStickers:
        stream << messagesAllStickersValue.hash;
        stream << messagesAllStickersValue.sets;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesChatFull &messagesChatFullValue)
{
    stream << messagesChatFullValue.tlType;
    switch (messagesChatFullValue.tlType) {
    case TLValue::MessagesChatFull:
        stream << messagesChatFullValue.fullChat;
        stream << messagesChatFullValue.chats;
        stream << messagesChatFullValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesChats &messagesChatsValue)
{
    stream << messagesChatsValue.tlType;
    switch (messagesChatsValue.tlType) {
    case TLValue::MessagesChats:
        stream << messagesChatsValue.chats;
        break;
    case TLValue::MessagesChatsSlice:
        stream << messagesChatsValue.count;
        stream << messagesChatsValue.chats;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesFavedStickers &messagesFavedStickersValue)
{
    stream << messagesFavedStickersValue.tlType;
    switch (messagesFavedStickersValue.tlType) {
    case TLValue::MessagesFavedStickersNotModified:
        break;
    case TLValue::MessagesFavedStickers:
        stream << messagesFavedStickersValue.hash;
        stream << messagesFavedStickersValue.packs;
        stream << messagesFavedStickersValue.stickers;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesFoundGifs &messagesFoundGifsValue)
{
    stream << messagesFoundGifsValue.tlType;
    switch (messagesFoundGifsValue.tlType) {
    case TLValue::MessagesFoundGifs:
        stream << messagesFoundGifsValue.nextOffset;
        stream << messagesFoundGifsValue.results;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesHighScores &messagesHighScoresValue)
{
    stream << messagesHighScoresValue.tlType;
    switch (messagesHighScoresValue.tlType) {
    case TLValue::MessagesHighScores:
        stream << messagesHighScoresValue.scores;
        stream << messagesHighScoresValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesRecentStickers &messagesRecentStickersValue)
{
    stream << messagesRecentStickersValue.tlType;
    switch (messagesRecentStickersValue.tlType) {
    case TLValue::MessagesRecentStickersNotModified:
        break;
    case TLValue::MessagesRecentStickers:
        stream << messagesRecentStickersValue.hash;
        stream << messagesRecentStickersValue.packs;
        stream << messagesRecentStickersValue.stickers;
        stream << messagesRecentStickersValue.dates;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesSavedGifs &messagesSavedGifsValue)
{
    stream << messagesSavedGifsValue.tlType;
    switch (messagesSavedGifsValue.tlType) {
    case TLValue::MessagesSavedGifsNotModified:
        break;
    case TLValue::MessagesSavedGifs:
        stream << messagesSavedGifsValue.hash;
        stream << messagesSavedGifsValue.gifs;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesStickerSet &messagesStickerSetValue)
{
    stream << messagesStickerSetValue.tlType;
    switch (messagesStickerSetValue.tlType) {
    case TLValue::MessagesStickerSet:
        stream << messagesStickerSetValue.set;
        stream << messagesStickerSetValue.packs;
        stream << messagesStickerSetValue.documents;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesStickers &messagesStickersValue)
{
    stream << messagesStickersValue.tlType;
    switch (messagesStickersValue.tlType) {
    case TLValue::MessagesStickersNotModified:
        break;
    case TLValue::MessagesStickers:
        stream << messagesStickersValue.hash;
        stream << messagesStickersValue.stickers;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPage &pageValue)
{
    stream << pageValue.tlType;
    switch (pageValue.tlType) {
    case TLValue::Page:
        stream << pageValue.flags;
        stream << pageValue.url;
        stream << pageValue.blocks;
        stream << pageValue.photos;
        stream << pageValue.documents;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPageBlock &pageBlockValue)
{
    stream << pageBlockValue.tlType;
    switch (pageBlockValue.tlType) {
    case TLValue::PageBlockUnsupported:
    case TLValue::PageBlockDivider:
        break;
    case TLValue::PageBlockTitle:
    case TLValue::PageBlockSubtitle:
    case TLValue::PageBlockHeader:
    case TLValue::PageBlockSubheader:
    case TLValue::PageBlockParagraph:
    case TLValue::PageBlockFooter:
    case TLValue::PageBlockKicker:
        stream << *pageBlockValue.text;
        break;
    case TLValue::PageBlockAuthorDate:
        stream << *pageBlockValue.richTextAuthor;
        stream << pageBlockValue.publishedDate;
        break;
    case TLValue::PageBlockPreformatted:
        stream << *pageBlockValue.text;
        stream << pageBlockValue.language;
        break;
    case TLValue::PageBlockAnchor:
        stream << pageBlockValue.name;
        break;
    case TLValue::PageBlockList:
        stream << pageBlockValue.pageListItemItemsVector;
        break;
    case TLValue::PageBlockBlockquote:
    case TLValue::PageBlockPullquote:
        stream << *pageBlockValue.text;
        stream << *pageBlockValue.richTextCaption;
        break;
    case TLValue::PageBlockPhoto:
        stream << pageBlockValue.flags;
        stream << pageBlockValue.photoId;
        stream << pageBlockValue.pageCaption;
        if (pageBlockValue.flags & TLPageBlock::Url0) {
            stream << pageBlockValue.url;
        }
        if (pageBlockValue.flags & TLPageBlock::WebpageId) {
            stream << pageBlockValue.webpageId;
        }
        break;
    case TLValue::PageBlockVideo:
        stream << pageBlockValue.flags;
        stream << pageBlockValue.videoId;
        stream << pageBlockValue.pageCaption;
        break;
    case TLValue::PageBlockCover:
        stream << *pageBlockValue.cover;
        break;
    case TLValue::PageBlockEmbed:
        stream << pageBlockValue.flags;
        if (pageBlockValue.flags & TLPageBlock::Url1) {
            stream << pageBlockValue.url;
        }
        if (pageBlockValue.flags & TLPageBlock::Html) {
            stream << pageBlockValue.html;
        }
        if (pageBlockValue.flags & TLPageBlock::PosterPhotoId) {
            stream << pageBlockValue.posterPhotoId;
        }
        if (pageBlockValue.flags & TLPageBlock::W) {
            stream << pageBlockValue.w;
        }
        if (pageBlockValue.flags & TLPageBlock::H) {
            stream << pageBlockValue.h;
        }
        stream << pageBlockValue.pageCaption;
        break;
    case TLValue::PageBlockEmbedPost:
        stream << pageBlockValue.url;
        stream << pageBlockValue.webpageId;
        stream << pageBlockValue.authorPhotoId;
        stream << pageBlockValue.stringAuthor;
        stream << pageBlockValue.date;
        stream << pageBlockValue.blocks;
        stream << pageBlockValue.pageCaption;
        break;
    case TLValue::PageBlockCollage:
    case TLValue::PageBlockSlideshow:
        stream << pageBlockValue.pageBlockItemsVector;
        stream << pageBlockValue.pageCaption;
        break;
    case TLValue::PageBlockChannel:
        stream << pageBlockValue.channel;
        break;
    case TLValue::PageBlockAudio:
        stream << pageBlockValue.audioId;
        stream << pageBlockValue.pageCaption;
        break;
    case TLValue::PageBlockTable:
        stream << pageBlockValue.flags;
        stream << *pageBlockValue.title;
        stream << pageBlockValue.rows;
        break;
    case TLValue::PageBlockOrderedList:
        stream << pageBlockValue.pageListOrderedItemItemsVector;
        break;
    case TLValue::PageBlockDetails:
        stream << pageBlockValue.flags;
        stream << pageBlockValue.blocks;
        stream << *pageBlockValue.title;
        break;
    case TLValue::PageBlockRelatedArticles:
        stream << *pageBlockValue.title;
        stream << pageBlockValue.articles;
        break;
    case TLValue::PageBlockMap:
        stream << pageBlockValue.geo;
        stream << pageBlockValue.zoom;
        stream << pageBlockValue.w;
        stream << pageBlockValue.h;
        stream << pageBlockValue.pageCaption;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentsPaymentForm &paymentsPaymentFormValue)
{
    stream << paymentsPaymentFormValue.tlType;
    switch (paymentsPaymentFormValue.tlType) {
    case TLValue::PaymentsPaymentForm:
        stream << paymentsPaymentFormValue.flags;
        stream << paymentsPaymentFormValue.botId;
        stream << paymentsPaymentFormValue.invoice;
        stream << paymentsPaymentFormValue.providerId;
        stream << paymentsPaymentFormValue.url;
        if (paymentsPaymentFormValue.flags & TLPaymentsPaymentForm::NativeProvider) {
            stream << paymentsPaymentFormValue.nativeProvider;
        }
        if (paymentsPaymentFormValue.flags & TLPaymentsPaymentForm::NativeParams) {
            stream << paymentsPaymentFormValue.nativeParams;
        }
        if (paymentsPaymentFormValue.flags & TLPaymentsPaymentForm::SavedInfo) {
            stream << paymentsPaymentFormValue.savedInfo;
        }
        if (paymentsPaymentFormValue.flags & TLPaymentsPaymentForm::SavedCredentials) {
            stream << paymentsPaymentFormValue.savedCredentials;
        }
        stream << paymentsPaymentFormValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentsPaymentReceipt &paymentsPaymentReceiptValue)
{
    stream << paymentsPaymentReceiptValue.tlType;
    switch (paymentsPaymentReceiptValue.tlType) {
    case TLValue::PaymentsPaymentReceipt:
        stream << paymentsPaymentReceiptValue.flags;
        stream << paymentsPaymentReceiptValue.date;
        stream << paymentsPaymentReceiptValue.botId;
        stream << paymentsPaymentReceiptValue.invoice;
        stream << paymentsPaymentReceiptValue.providerId;
        if (paymentsPaymentReceiptValue.flags & TLPaymentsPaymentReceipt::Info) {
            stream << paymentsPaymentReceiptValue.info;
        }
        if (paymentsPaymentReceiptValue.flags & TLPaymentsPaymentReceipt::Shipping) {
            stream << paymentsPaymentReceiptValue.shipping;
        }
        stream << paymentsPaymentReceiptValue.currency;
        stream << paymentsPaymentReceiptValue.totalAmount;
        stream << paymentsPaymentReceiptValue.credentialsTitle;
        stream << paymentsPaymentReceiptValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhoneCall &phoneCallValue)
{
    stream << phoneCallValue.tlType;
    switch (phoneCallValue.tlType) {
    case TLValue::PhoneCallEmpty:
        stream << phoneCallValue.id;
        break;
    case TLValue::PhoneCallWaiting:
        stream << phoneCallValue.flags;
        stream << phoneCallValue.id;
        stream << phoneCallValue.accessHash;
        stream << phoneCallValue.date;
        stream << phoneCallValue.adminId;
        stream << phoneCallValue.participantId;
        stream << phoneCallValue.protocol;
        if (phoneCallValue.flags & TLPhoneCall::ReceiveDate) {
            stream << phoneCallValue.receiveDate;
        }
        break;
    case TLValue::PhoneCallRequested:
        stream << phoneCallValue.id;
        stream << phoneCallValue.accessHash;
        stream << phoneCallValue.date;
        stream << phoneCallValue.adminId;
        stream << phoneCallValue.participantId;
        stream << phoneCallValue.gAHash;
        stream << phoneCallValue.protocol;
        break;
    case TLValue::PhoneCallAccepted:
        stream << phoneCallValue.id;
        stream << phoneCallValue.accessHash;
        stream << phoneCallValue.date;
        stream << phoneCallValue.adminId;
        stream << phoneCallValue.participantId;
        stream << phoneCallValue.gB;
        stream << phoneCallValue.protocol;
        break;
    case TLValue::PhoneCall:
        stream << phoneCallValue.flags;
        stream << phoneCallValue.id;
        stream << phoneCallValue.accessHash;
        stream << phoneCallValue.date;
        stream << phoneCallValue.adminId;
        stream << phoneCallValue.participantId;
        stream << phoneCallValue.gAOrB;
        stream << phoneCallValue.keyFingerprint;
        stream << phoneCallValue.protocol;
        stream << phoneCallValue.connection;
        stream << phoneCallValue.alternativeConnections;
        stream << phoneCallValue.startDate;
        break;
    case TLValue::PhoneCallDiscarded:
        stream << phoneCallValue.flags;
        stream << phoneCallValue.id;
        if (phoneCallValue.flags & TLPhoneCall::Reason) {
            stream << phoneCallValue.reason;
        }
        if (phoneCallValue.flags & TLPhoneCall::Duration) {
            stream << phoneCallValue.duration;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhonePhoneCall &phonePhoneCallValue)
{
    stream << phonePhoneCallValue.tlType;
    switch (phonePhoneCallValue.tlType) {
    case TLValue::PhonePhoneCall:
        stream << phonePhoneCallValue.phoneCall;
        stream << phonePhoneCallValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhotosPhoto &photosPhotoValue)
{
    stream << photosPhotoValue.tlType;
    switch (photosPhotoValue.tlType) {
    case TLValue::PhotosPhoto:
        stream << photosPhotoValue.photo;
        stream << photosPhotoValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPhotosPhotos &photosPhotosValue)
{
    stream << photosPhotosValue.tlType;
    switch (photosPhotosValue.tlType) {
    case TLValue::PhotosPhotos:
        stream << photosPhotosValue.photos;
        stream << photosPhotosValue.users;
        break;
    case TLValue::PhotosPhotosSlice:
        stream << photosPhotosValue.count;
        stream << photosPhotosValue.photos;
        stream << photosPhotosValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLStickerSetCovered &stickerSetCoveredValue)
{
    stream << stickerSetCoveredValue.tlType;
    switch (stickerSetCoveredValue.tlType) {
    case TLValue::StickerSetCovered:
        stream << stickerSetCoveredValue.set;
        stream << stickerSetCoveredValue.cover;
        break;
    case TLValue::StickerSetMultiCovered:
        stream << stickerSetCoveredValue.set;
        stream << stickerSetCoveredValue.covers;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUserFull &userFullValue)
{
    stream << userFullValue.tlType;
    switch (userFullValue.tlType) {
    case TLValue::UserFull:
        stream << userFullValue.flags;
        stream << userFullValue.user;
        if (userFullValue.flags & TLUserFull::About) {
            stream << userFullValue.about;
        }
        stream << userFullValue.link;
        if (userFullValue.flags & TLUserFull::ProfilePhoto) {
            stream << userFullValue.profilePhoto;
        }
        stream << userFullValue.notifySettings;
        if (userFullValue.flags & TLUserFull::BotInfo) {
            stream << userFullValue.botInfo;
        }
        if (userFullValue.flags & TLUserFull::PinnedMsgId) {
            stream << userFullValue.pinnedMsgId;
        }
        stream << userFullValue.commonChatsCount;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLWebPage &webPageValue)
{
    stream << webPageValue.tlType;
    switch (webPageValue.tlType) {
    case TLValue::WebPageEmpty:
        stream << webPageValue.id;
        break;
    case TLValue::WebPagePending:
        stream << webPageValue.id;
        stream << webPageValue.date;
        break;
    case TLValue::WebPage:
        stream << webPageValue.flags;
        stream << webPageValue.id;
        stream << webPageValue.url;
        stream << webPageValue.displayUrl;
        stream << webPageValue.hash;
        if (webPageValue.flags & TLWebPage::Type) {
            stream << webPageValue.type;
        }
        if (webPageValue.flags & TLWebPage::SiteName) {
            stream << webPageValue.siteName;
        }
        if (webPageValue.flags & TLWebPage::Title) {
            stream << webPageValue.title;
        }
        if (webPageValue.flags & TLWebPage::Description) {
            stream << webPageValue.description;
        }
        if (webPageValue.flags & TLWebPage::Photo) {
            stream << webPageValue.photo;
        }
        if (webPageValue.flags & TLWebPage::EmbedUrl) {
            stream << webPageValue.embedUrl;
        }
        if (webPageValue.flags & TLWebPage::EmbedType) {
            stream << webPageValue.embedType;
        }
        if (webPageValue.flags & TLWebPage::EmbedWidth) {
            stream << webPageValue.embedWidth;
        }
        if (webPageValue.flags & TLWebPage::EmbedHeight) {
            stream << webPageValue.embedHeight;
        }
        if (webPageValue.flags & TLWebPage::Duration) {
            stream << webPageValue.duration;
        }
        if (webPageValue.flags & TLWebPage::Author) {
            stream << webPageValue.author;
        }
        if (webPageValue.flags & TLWebPage::Document) {
            stream << webPageValue.document;
        }
        if (webPageValue.flags & TLWebPage::CachedPage) {
            stream << webPageValue.cachedPage;
        }
        break;
    case TLValue::WebPageNotModified:
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLBotInlineResult &botInlineResultValue)
{
    stream << botInlineResultValue.tlType;
    switch (botInlineResultValue.tlType) {
    case TLValue::BotInlineResult:
        stream << botInlineResultValue.flags;
        stream << botInlineResultValue.id;
        stream << botInlineResultValue.type;
        if (botInlineResultValue.flags & TLBotInlineResult::Title1) {
            stream << botInlineResultValue.title;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Description2) {
            stream << botInlineResultValue.description;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Url) {
            stream << botInlineResultValue.url;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Thumb) {
            stream << botInlineResultValue.thumb;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Content) {
            stream << botInlineResultValue.content;
        }
        stream << botInlineResultValue.sendMessage;
        break;
    case TLValue::BotInlineMediaResult:
        stream << botInlineResultValue.flags;
        stream << botInlineResultValue.id;
        stream << botInlineResultValue.type;
        if (botInlineResultValue.flags & TLBotInlineResult::Photo) {
            stream << botInlineResultValue.photo;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Document) {
            stream << botInlineResultValue.document;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Title2) {
            stream << botInlineResultValue.title;
        }
        if (botInlineResultValue.flags & TLBotInlineResult::Description3) {
            stream << botInlineResultValue.description;
        }
        stream << botInlineResultValue.sendMessage;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessageMedia &messageMediaValue)
{
    stream << messageMediaValue.tlType;
    switch (messageMediaValue.tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        break;
    case TLValue::MessageMediaPhoto:
        stream << messageMediaValue.flags;
        if (messageMediaValue.flags & TLMessageMedia::Photo) {
            stream << messageMediaValue.photo;
        }
        if (messageMediaValue.flags & TLMessageMedia::TtlSeconds) {
            stream << messageMediaValue.ttlSeconds;
        }
        break;
    case TLValue::MessageMediaGeo:
        stream << messageMediaValue.geo;
        break;
    case TLValue::MessageMediaContact:
        stream << messageMediaValue.phoneNumber;
        stream << messageMediaValue.firstName;
        stream << messageMediaValue.lastName;
        stream << messageMediaValue.vcard;
        stream << messageMediaValue.userId;
        break;
    case TLValue::MessageMediaDocument:
        stream << messageMediaValue.flags;
        if (messageMediaValue.flags & TLMessageMedia::Document) {
            stream << messageMediaValue.document;
        }
        if (messageMediaValue.flags & TLMessageMedia::TtlSeconds) {
            stream << messageMediaValue.ttlSeconds;
        }
        break;
    case TLValue::MessageMediaWebPage:
        stream << messageMediaValue.webpage;
        break;
    case TLValue::MessageMediaVenue:
        stream << messageMediaValue.geo;
        stream << messageMediaValue.title;
        stream << messageMediaValue.address;
        stream << messageMediaValue.provider;
        stream << messageMediaValue.venueId;
        stream << messageMediaValue.venueType;
        break;
    case TLValue::MessageMediaGame:
        stream << messageMediaValue.game;
        break;
    case TLValue::MessageMediaInvoice:
        stream << messageMediaValue.flags;
        stream << messageMediaValue.title;
        stream << messageMediaValue.description;
        if (messageMediaValue.flags & TLMessageMedia::WebDocumentPhoto) {
            stream << messageMediaValue.webDocumentPhoto;
        }
        if (messageMediaValue.flags & TLMessageMedia::ReceiptMsgId) {
            stream << messageMediaValue.receiptMsgId;
        }
        stream << messageMediaValue.currency;
        stream << messageMediaValue.totalAmount;
        stream << messageMediaValue.startParam;
        break;
    case TLValue::MessageMediaGeoLive:
        stream << messageMediaValue.geo;
        stream << messageMediaValue.period;
        break;
    case TLValue::MessageMediaPoll:
        stream << messageMediaValue.poll;
        stream << messageMediaValue.results;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesArchivedStickers &messagesArchivedStickersValue)
{
    stream << messagesArchivedStickersValue.tlType;
    switch (messagesArchivedStickersValue.tlType) {
    case TLValue::MessagesArchivedStickers:
        stream << messagesArchivedStickersValue.count;
        stream << messagesArchivedStickersValue.sets;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesBotResults &messagesBotResultsValue)
{
    stream << messagesBotResultsValue.tlType;
    switch (messagesBotResultsValue.tlType) {
    case TLValue::MessagesBotResults:
        stream << messagesBotResultsValue.flags;
        stream << messagesBotResultsValue.queryId;
        if (messagesBotResultsValue.flags & TLMessagesBotResults::NextOffset) {
            stream << messagesBotResultsValue.nextOffset;
        }
        if (messagesBotResultsValue.flags & TLMessagesBotResults::SwitchPm) {
            stream << messagesBotResultsValue.switchPm;
        }
        stream << messagesBotResultsValue.results;
        stream << messagesBotResultsValue.cacheTime;
        stream << messagesBotResultsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesFeaturedStickers &messagesFeaturedStickersValue)
{
    stream << messagesFeaturedStickersValue.tlType;
    switch (messagesFeaturedStickersValue.tlType) {
    case TLValue::MessagesFeaturedStickersNotModified:
        break;
    case TLValue::MessagesFeaturedStickers:
        stream << messagesFeaturedStickersValue.hash;
        stream << messagesFeaturedStickersValue.sets;
        stream << messagesFeaturedStickersValue.unread;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesFoundStickerSets &messagesFoundStickerSetsValue)
{
    stream << messagesFoundStickerSetsValue.tlType;
    switch (messagesFoundStickerSetsValue.tlType) {
    case TLValue::MessagesFoundStickerSetsNotModified:
        break;
    case TLValue::MessagesFoundStickerSets:
        stream << messagesFoundStickerSetsValue.hash;
        stream << messagesFoundStickerSetsValue.sets;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesStickerSetInstallResult &messagesStickerSetInstallResultValue)
{
    stream << messagesStickerSetInstallResultValue.tlType;
    switch (messagesStickerSetInstallResultValue.tlType) {
    case TLValue::MessagesStickerSetInstallResultSuccess:
        break;
    case TLValue::MessagesStickerSetInstallResultArchive:
        stream << messagesStickerSetInstallResultValue.sets;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLRecentMeUrl &recentMeUrlValue)
{
    stream << recentMeUrlValue.tlType;
    switch (recentMeUrlValue.tlType) {
    case TLValue::RecentMeUrlUnknown:
        stream << recentMeUrlValue.url;
        break;
    case TLValue::RecentMeUrlUser:
        stream << recentMeUrlValue.url;
        stream << recentMeUrlValue.userId;
        break;
    case TLValue::RecentMeUrlChat:
        stream << recentMeUrlValue.url;
        stream << recentMeUrlValue.chatId;
        break;
    case TLValue::RecentMeUrlChatInvite:
        stream << recentMeUrlValue.url;
        stream << recentMeUrlValue.chatInvite;
        break;
    case TLValue::RecentMeUrlStickerSet:
        stream << recentMeUrlValue.url;
        stream << recentMeUrlValue.set;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLHelpRecentMeUrls &helpRecentMeUrlsValue)
{
    stream << helpRecentMeUrlsValue.tlType;
    switch (helpRecentMeUrlsValue.tlType) {
    case TLValue::HelpRecentMeUrls:
        stream << helpRecentMeUrlsValue.urls;
        stream << helpRecentMeUrlsValue.chats;
        stream << helpRecentMeUrlsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessage &messageValue)
{
    stream << messageValue.tlType;
    switch (messageValue.tlType) {
    case TLValue::MessageEmpty:
        stream << messageValue.id;
        break;
    case TLValue::Message:
        stream << messageValue.flags;
        stream << messageValue.id;
        if (messageValue.flags & TLMessage::FromId) {
            stream << messageValue.fromId;
        }
        stream << messageValue.toId;
        if (messageValue.flags & TLMessage::FwdFrom) {
            stream << messageValue.fwdFrom;
        }
        if (messageValue.flags & TLMessage::ViaBotId) {
            stream << messageValue.viaBotId;
        }
        if (messageValue.flags & TLMessage::ReplyToMsgId) {
            stream << messageValue.replyToMsgId;
        }
        stream << messageValue.date;
        stream << messageValue.message;
        if (messageValue.flags & TLMessage::Media) {
            stream << messageValue.media;
        }
        if (messageValue.flags & TLMessage::ReplyMarkup) {
            stream << messageValue.replyMarkup;
        }
        if (messageValue.flags & TLMessage::Entities) {
            stream << messageValue.entities;
        }
        if (messageValue.flags & TLMessage::Views) {
            stream << messageValue.views;
        }
        if (messageValue.flags & TLMessage::EditDate) {
            stream << messageValue.editDate;
        }
        if (messageValue.flags & TLMessage::PostAuthor) {
            stream << messageValue.postAuthor;
        }
        if (messageValue.flags & TLMessage::GroupedId) {
            stream << messageValue.groupedId;
        }
        break;
    case TLValue::MessageService:
        stream << messageValue.flags;
        stream << messageValue.id;
        if (messageValue.flags & TLMessage::FromId) {
            stream << messageValue.fromId;
        }
        stream << messageValue.toId;
        if (messageValue.flags & TLMessage::ReplyToMsgId) {
            stream << messageValue.replyToMsgId;
        }
        stream << messageValue.date;
        stream << messageValue.action;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesDialogs &messagesDialogsValue)
{
    stream << messagesDialogsValue.tlType;
    switch (messagesDialogsValue.tlType) {
    case TLValue::MessagesDialogs:
        stream << messagesDialogsValue.dialogs;
        stream << messagesDialogsValue.messages;
        stream << messagesDialogsValue.chats;
        stream << messagesDialogsValue.users;
        break;
    case TLValue::MessagesDialogsSlice:
        stream << messagesDialogsValue.count;
        stream << messagesDialogsValue.dialogs;
        stream << messagesDialogsValue.messages;
        stream << messagesDialogsValue.chats;
        stream << messagesDialogsValue.users;
        break;
    case TLValue::MessagesDialogsNotModified:
        stream << messagesDialogsValue.count;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesMessages &messagesMessagesValue)
{
    stream << messagesMessagesValue.tlType;
    switch (messagesMessagesValue.tlType) {
    case TLValue::MessagesMessages:
        stream << messagesMessagesValue.messages;
        stream << messagesMessagesValue.chats;
        stream << messagesMessagesValue.users;
        break;
    case TLValue::MessagesMessagesSlice:
        stream << messagesMessagesValue.flags;
        stream << messagesMessagesValue.count;
        stream << messagesMessagesValue.messages;
        stream << messagesMessagesValue.chats;
        stream << messagesMessagesValue.users;
        break;
    case TLValue::MessagesChannelMessages:
        stream << messagesMessagesValue.flags;
        stream << messagesMessagesValue.pts;
        stream << messagesMessagesValue.count;
        stream << messagesMessagesValue.messages;
        stream << messagesMessagesValue.chats;
        stream << messagesMessagesValue.users;
        break;
    case TLValue::MessagesMessagesNotModified:
        stream << messagesMessagesValue.count;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLMessagesPeerDialogs &messagesPeerDialogsValue)
{
    stream << messagesPeerDialogsValue.tlType;
    switch (messagesPeerDialogsValue.tlType) {
    case TLValue::MessagesPeerDialogs:
        stream << messagesPeerDialogsValue.dialogs;
        stream << messagesPeerDialogsValue.messages;
        stream << messagesPeerDialogsValue.chats;
        stream << messagesPeerDialogsValue.users;
        stream << messagesPeerDialogsValue.state;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUpdate &updateValue)
{
    stream << updateValue.tlType;
    switch (updateValue.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
    case TLValue::UpdateEditChannelMessage:
    case TLValue::UpdateEditMessage:
        stream << updateValue.message;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateMessageID:
        stream << updateValue.quint32Id;
        stream << updateValue.randomId;
        break;
    case TLValue::UpdateDeleteMessages:
    case TLValue::UpdateReadMessagesContents:
        stream << updateValue.messages;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateUserTyping:
        stream << updateValue.userId;
        stream << updateValue.action;
        break;
    case TLValue::UpdateChatUserTyping:
        stream << updateValue.chatId;
        stream << updateValue.userId;
        stream << updateValue.action;
        break;
    case TLValue::UpdateChatParticipants:
        stream << updateValue.participants;
        break;
    case TLValue::UpdateUserStatus:
        stream << updateValue.userId;
        stream << updateValue.status;
        break;
    case TLValue::UpdateUserName:
        stream << updateValue.userId;
        stream << updateValue.firstName;
        stream << updateValue.lastName;
        stream << updateValue.username;
        break;
    case TLValue::UpdateUserPhoto:
        stream << updateValue.userId;
        stream << updateValue.date;
        stream << updateValue.photo;
        stream << updateValue.previous;
        break;
    case TLValue::UpdateContactLink:
        stream << updateValue.userId;
        stream << updateValue.myLink;
        stream << updateValue.foreignLink;
        break;
    case TLValue::UpdateNewEncryptedMessage:
        stream << updateValue.encryptedMessage;
        stream << updateValue.qts;
        break;
    case TLValue::UpdateEncryptedChatTyping:
        stream << updateValue.chatId;
        break;
    case TLValue::UpdateEncryption:
        stream << updateValue.chat;
        stream << updateValue.date;
        break;
    case TLValue::UpdateEncryptedMessagesRead:
        stream << updateValue.chatId;
        stream << updateValue.maxDate;
        stream << updateValue.date;
        break;
    case TLValue::UpdateChatParticipantAdd:
        stream << updateValue.chatId;
        stream << updateValue.userId;
        stream << updateValue.inviterId;
        stream << updateValue.date;
        stream << updateValue.version;
        break;
    case TLValue::UpdateChatParticipantDelete:
        stream << updateValue.chatId;
        stream << updateValue.userId;
        stream << updateValue.version;
        break;
    case TLValue::UpdateDcOptions:
        stream << updateValue.dcOptions;
        break;
    case TLValue::UpdateUserBlocked:
        stream << updateValue.userId;
        stream << updateValue.blocked;
        break;
    case TLValue::UpdateNotifySettings:
        stream << updateValue.notifyPeer;
        stream << updateValue.notifySettings;
        break;
    case TLValue::UpdateServiceNotification:
        stream << updateValue.flags;
        if (updateValue.flags & TLUpdate::InboxDate) {
            stream << updateValue.inboxDate;
        }
        stream << updateValue.type;
        stream << updateValue.stringMessage;
        stream << updateValue.media;
        stream << updateValue.entities;
        break;
    case TLValue::UpdatePrivacy:
        stream << updateValue.key;
        stream << updateValue.rules;
        break;
    case TLValue::UpdateUserPhone:
        stream << updateValue.userId;
        stream << updateValue.phone;
        break;
    case TLValue::UpdateReadHistoryInbox:
    case TLValue::UpdateReadHistoryOutbox:
        stream << updateValue.peer;
        stream << updateValue.maxId;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateWebPage:
        stream << updateValue.webpage;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateChannelTooLong:
        stream << updateValue.flags;
        stream << updateValue.channelId;
        if (updateValue.flags & TLUpdate::Pts) {
            stream << updateValue.pts;
        }
        break;
    case TLValue::UpdateChannel:
        stream << updateValue.channelId;
        break;
    case TLValue::UpdateReadChannelInbox:
    case TLValue::UpdateReadChannelOutbox:
        stream << updateValue.channelId;
        stream << updateValue.maxId;
        break;
    case TLValue::UpdateDeleteChannelMessages:
        stream << updateValue.channelId;
        stream << updateValue.messages;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateChannelMessageViews:
        stream << updateValue.channelId;
        stream << updateValue.quint32Id;
        stream << updateValue.views;
        break;
    case TLValue::UpdateChatAdmins:
        stream << updateValue.chatId;
        stream << updateValue.enabled;
        stream << updateValue.version;
        break;
    case TLValue::UpdateChatParticipantAdmin:
        stream << updateValue.chatId;
        stream << updateValue.userId;
        stream << updateValue.isAdmin;
        stream << updateValue.version;
        break;
    case TLValue::UpdateNewStickerSet:
        stream << updateValue.stickerset;
        break;
    case TLValue::UpdateStickerSetsOrder:
        stream << updateValue.flags;
        stream << updateValue.quint64OrderVector;
        break;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
    case TLValue::UpdateReadFeaturedStickers:
    case TLValue::UpdateRecentStickers:
    case TLValue::UpdateConfig:
    case TLValue::UpdatePtsChanged:
    case TLValue::UpdateFavedStickers:
    case TLValue::UpdateContactsReset:
        break;
    case TLValue::UpdateBotInlineQuery:
        stream << updateValue.flags;
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.query;
        if (updateValue.flags & TLUpdate::Geo) {
            stream << updateValue.geo;
        }
        stream << updateValue.offset;
        break;
    case TLValue::UpdateBotInlineSend:
        stream << updateValue.flags;
        stream << updateValue.userId;
        stream << updateValue.query;
        if (updateValue.flags & TLUpdate::Geo) {
            stream << updateValue.geo;
        }
        stream << updateValue.stringId;
        if (updateValue.flags & TLUpdate::InputBotInlineMessageIDMsgId) {
            stream << updateValue.inputBotInlineMessageIDMsgId;
        }
        break;
    case TLValue::UpdateChannelPinnedMessage:
        stream << updateValue.channelId;
        stream << updateValue.quint32Id;
        break;
    case TLValue::UpdateBotCallbackQuery:
        stream << updateValue.flags;
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.peer;
        stream << updateValue.msgId;
        stream << updateValue.chatInstance;
        if (updateValue.flags & TLUpdate::ByteArrayData) {
            stream << updateValue.byteArrayData;
        }
        if (updateValue.flags & TLUpdate::GameShortName) {
            stream << updateValue.gameShortName;
        }
        break;
    case TLValue::UpdateInlineBotCallbackQuery:
        stream << updateValue.flags;
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.inputBotInlineMessageIDMsgId;
        stream << updateValue.chatInstance;
        if (updateValue.flags & TLUpdate::ByteArrayData) {
            stream << updateValue.byteArrayData;
        }
        if (updateValue.flags & TLUpdate::GameShortName) {
            stream << updateValue.gameShortName;
        }
        break;
    case TLValue::UpdateDraftMessage:
        stream << updateValue.peer;
        stream << updateValue.draft;
        break;
    case TLValue::UpdateChannelWebPage:
        stream << updateValue.channelId;
        stream << updateValue.webpage;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateDialogPinned:
    case TLValue::UpdateDialogUnreadMark:
        stream << updateValue.flags;
        stream << updateValue.dialogPeer;
        break;
    case TLValue::UpdatePinnedDialogs:
        stream << updateValue.flags;
        if (updateValue.flags & TLUpdate::DialogPeerOrderVector) {
            stream << updateValue.dialogPeerOrderVector;
        }
        break;
    case TLValue::UpdateBotWebhookJSON:
        stream << updateValue.jSONData;
        break;
    case TLValue::UpdateBotWebhookJSONQuery:
        stream << updateValue.queryId;
        stream << updateValue.jSONData;
        stream << updateValue.timeout;
        break;
    case TLValue::UpdateBotShippingQuery:
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.payload;
        stream << updateValue.shippingAddress;
        break;
    case TLValue::UpdateBotPrecheckoutQuery:
        stream << updateValue.flags;
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.payload;
        if (updateValue.flags & TLUpdate::Info) {
            stream << updateValue.info;
        }
        if (updateValue.flags & TLUpdate::ShippingOptionId) {
            stream << updateValue.shippingOptionId;
        }
        stream << updateValue.currency;
        stream << updateValue.totalAmount;
        break;
    case TLValue::UpdatePhoneCall:
        stream << updateValue.phoneCall;
        break;
    case TLValue::UpdateLangPackTooLong:
        stream << updateValue.langCode;
        break;
    case TLValue::UpdateLangPack:
        stream << updateValue.difference;
        break;
    case TLValue::UpdateChannelReadMessagesContents:
        stream << updateValue.channelId;
        stream << updateValue.messages;
        break;
    case TLValue::UpdateChannelAvailableMessages:
        stream << updateValue.channelId;
        stream << updateValue.availableMinId;
        break;
    case TLValue::UpdateUserPinnedMessage:
        stream << updateValue.userId;
        stream << updateValue.quint32Id;
        break;
    case TLValue::UpdateChatPinnedMessage:
        stream << updateValue.chatId;
        stream << updateValue.quint32Id;
        break;
    case TLValue::UpdateMessagePoll:
        stream << updateValue.flags;
        stream << updateValue.pollId;
        if (updateValue.flags & TLUpdate::Poll) {
            stream << updateValue.poll;
        }
        stream << updateValue.results;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUpdates &updatesValue)
{
    stream << updatesValue.tlType;
    switch (updatesValue.tlType) {
    case TLValue::UpdatesTooLong:
        break;
    case TLValue::UpdateShortMessage:
        stream << updatesValue.flags;
        stream << updatesValue.id;
        stream << updatesValue.userId;
        stream << updatesValue.message;
        stream << updatesValue.pts;
        stream << updatesValue.ptsCount;
        stream << updatesValue.date;
        if (updatesValue.flags & TLUpdates::FwdFrom) {
            stream << updatesValue.fwdFrom;
        }
        if (updatesValue.flags & TLUpdates::ViaBotId) {
            stream << updatesValue.viaBotId;
        }
        if (updatesValue.flags & TLUpdates::ReplyToMsgId) {
            stream << updatesValue.replyToMsgId;
        }
        if (updatesValue.flags & TLUpdates::Entities) {
            stream << updatesValue.entities;
        }
        break;
    case TLValue::UpdateShortChatMessage:
        stream << updatesValue.flags;
        stream << updatesValue.id;
        stream << updatesValue.fromId;
        stream << updatesValue.chatId;
        stream << updatesValue.message;
        stream << updatesValue.pts;
        stream << updatesValue.ptsCount;
        stream << updatesValue.date;
        if (updatesValue.flags & TLUpdates::FwdFrom) {
            stream << updatesValue.fwdFrom;
        }
        if (updatesValue.flags & TLUpdates::ViaBotId) {
            stream << updatesValue.viaBotId;
        }
        if (updatesValue.flags & TLUpdates::ReplyToMsgId) {
            stream << updatesValue.replyToMsgId;
        }
        if (updatesValue.flags & TLUpdates::Entities) {
            stream << updatesValue.entities;
        }
        break;
    case TLValue::UpdateShort:
        stream << updatesValue.update;
        stream << updatesValue.date;
        break;
    case TLValue::UpdatesCombined:
        stream << updatesValue.updates;
        stream << updatesValue.users;
        stream << updatesValue.chats;
        stream << updatesValue.date;
        stream << updatesValue.seqStart;
        stream << updatesValue.seq;
        break;
    case TLValue::Updates:
        stream << updatesValue.updates;
        stream << updatesValue.users;
        stream << updatesValue.chats;
        stream << updatesValue.date;
        stream << updatesValue.seq;
        break;
    case TLValue::UpdateShortSentMessage:
        stream << updatesValue.flags;
        stream << updatesValue.id;
        stream << updatesValue.pts;
        stream << updatesValue.ptsCount;
        stream << updatesValue.date;
        if (updatesValue.flags & TLUpdates::Media) {
            stream << updatesValue.media;
        }
        if (updatesValue.flags & TLUpdates::Entities) {
            stream << updatesValue.entities;
        }
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUpdatesChannelDifference &updatesChannelDifferenceValue)
{
    stream << updatesChannelDifferenceValue.tlType;
    switch (updatesChannelDifferenceValue.tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & TLUpdatesChannelDifference::Timeout) {
            stream << updatesChannelDifferenceValue.timeout;
        }
        break;
    case TLValue::UpdatesChannelDifferenceTooLong:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & TLUpdatesChannelDifference::Timeout) {
            stream << updatesChannelDifferenceValue.timeout;
        }
        stream << updatesChannelDifferenceValue.topMessage;
        stream << updatesChannelDifferenceValue.readInboxMaxId;
        stream << updatesChannelDifferenceValue.readOutboxMaxId;
        stream << updatesChannelDifferenceValue.unreadCount;
        stream << updatesChannelDifferenceValue.unreadMentionsCount;
        stream << updatesChannelDifferenceValue.messages;
        stream << updatesChannelDifferenceValue.chats;
        stream << updatesChannelDifferenceValue.users;
        break;
    case TLValue::UpdatesChannelDifference:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & TLUpdatesChannelDifference::Timeout) {
            stream << updatesChannelDifferenceValue.timeout;
        }
        stream << updatesChannelDifferenceValue.newMessages;
        stream << updatesChannelDifferenceValue.otherUpdates;
        stream << updatesChannelDifferenceValue.chats;
        stream << updatesChannelDifferenceValue.users;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLUpdatesDifference &updatesDifferenceValue)
{
    stream << updatesDifferenceValue.tlType;
    switch (updatesDifferenceValue.tlType) {
    case TLValue::UpdatesDifferenceEmpty:
        stream << updatesDifferenceValue.date;
        stream << updatesDifferenceValue.seq;
        break;
    case TLValue::UpdatesDifference:
        stream << updatesDifferenceValue.newMessages;
        stream << updatesDifferenceValue.newEncryptedMessages;
        stream << updatesDifferenceValue.otherUpdates;
        stream << updatesDifferenceValue.chats;
        stream << updatesDifferenceValue.users;
        stream << updatesDifferenceValue.state;
        break;
    case TLValue::UpdatesDifferenceSlice:
        stream << updatesDifferenceValue.newMessages;
        stream << updatesDifferenceValue.newEncryptedMessages;
        stream << updatesDifferenceValue.otherUpdates;
        stream << updatesDifferenceValue.chats;
        stream << updatesDifferenceValue.users;
        stream << updatesDifferenceValue.intermediateState;
        break;
    case TLValue::UpdatesDifferenceTooLong:
        stream << updatesDifferenceValue.pts;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelAdminLogEventAction &channelAdminLogEventActionValue)
{
    stream << channelAdminLogEventActionValue.tlType;
    switch (channelAdminLogEventActionValue.tlType) {
    case TLValue::ChannelAdminLogEventActionChangeTitle:
    case TLValue::ChannelAdminLogEventActionChangeAbout:
    case TLValue::ChannelAdminLogEventActionChangeUsername:
        stream << channelAdminLogEventActionValue.prevValue;
        stream << channelAdminLogEventActionValue.stringNewValue;
        break;
    case TLValue::ChannelAdminLogEventActionChangePhoto:
        stream << channelAdminLogEventActionValue.prevPhoto;
        stream << channelAdminLogEventActionValue.newPhoto;
        break;
    case TLValue::ChannelAdminLogEventActionToggleInvites:
    case TLValue::ChannelAdminLogEventActionToggleSignatures:
    case TLValue::ChannelAdminLogEventActionTogglePreHistoryHidden:
        stream << channelAdminLogEventActionValue.boolNewValue;
        break;
    case TLValue::ChannelAdminLogEventActionUpdatePinned:
    case TLValue::ChannelAdminLogEventActionDeleteMessage:
        stream << channelAdminLogEventActionValue.message;
        break;
    case TLValue::ChannelAdminLogEventActionEditMessage:
        stream << channelAdminLogEventActionValue.prevMessage;
        stream << channelAdminLogEventActionValue.newMessage;
        break;
    case TLValue::ChannelAdminLogEventActionParticipantJoin:
    case TLValue::ChannelAdminLogEventActionParticipantLeave:
        break;
    case TLValue::ChannelAdminLogEventActionParticipantInvite:
        stream << channelAdminLogEventActionValue.participant;
        break;
    case TLValue::ChannelAdminLogEventActionParticipantToggleBan:
    case TLValue::ChannelAdminLogEventActionParticipantToggleAdmin:
        stream << channelAdminLogEventActionValue.prevParticipant;
        stream << channelAdminLogEventActionValue.newParticipant;
        break;
    case TLValue::ChannelAdminLogEventActionChangeStickerSet:
        stream << channelAdminLogEventActionValue.prevStickerset;
        stream << channelAdminLogEventActionValue.newStickerset;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLPaymentsPaymentResult &paymentsPaymentResultValue)
{
    stream << paymentsPaymentResultValue.tlType;
    switch (paymentsPaymentResultValue.tlType) {
    case TLValue::PaymentsPaymentResult:
        stream << paymentsPaymentResultValue.updates;
        break;
    case TLValue::PaymentsPaymentVerficationNeeded:
        stream << paymentsPaymentResultValue.url;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelAdminLogEvent &channelAdminLogEventValue)
{
    stream << channelAdminLogEventValue.tlType;
    switch (channelAdminLogEventValue.tlType) {
    case TLValue::ChannelAdminLogEvent:
        stream << channelAdminLogEventValue.id;
        stream << channelAdminLogEventValue.date;
        stream << channelAdminLogEventValue.userId;
        stream << channelAdminLogEventValue.action;
        break;
    default:
        break;
    }

    return stream;
}

Stream &operator<<(Stream &stream, const TLChannelsAdminLogResults &channelsAdminLogResultsValue)
{
    stream << channelsAdminLogResultsValue.tlType;
    switch (channelsAdminLogResultsValue.tlType) {
    case TLValue::ChannelsAdminLogResults:
        stream << channelsAdminLogResultsValue.events;
        stream << channelsAdminLogResultsValue.chats;
        stream << channelsAdminLogResultsValue.users;
        break;
    default:
        break;
    }

    return stream;
}
// End of generated write operators implementation

} // MTProto namespace

} // Telegram namespace
