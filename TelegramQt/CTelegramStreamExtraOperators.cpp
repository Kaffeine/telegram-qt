#include "CTelegramStreamExtraOperators.hpp"

#include "CTelegramStream_p.hpp"

template CTelegramStream &CTelegramStream::operator<<(const TLVector<TLDcOption> &v);

// Generated vector write templates instancing
// End of generated vector write templates instancing

// Generated write operators implementation
CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPassword &accountPasswordValue)
{
    stream << accountPasswordValue.tlType;
    switch (accountPasswordValue.tlType) {
    case TLValue::AccountNoPassword:
        stream << accountPasswordValue.newSalt;
        stream << accountPasswordValue.emailUnconfirmedPattern;
        break;
    case TLValue::AccountPassword:
        stream << accountPasswordValue.currentSalt;
        stream << accountPasswordValue.newSalt;
        stream << accountPasswordValue.hint;
        stream << accountPasswordValue.hasRecovery;
        stream << accountPasswordValue.emailUnconfirmedPattern;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPasswordSettings &accountPasswordSettingsValue)
{
    stream << accountPasswordSettingsValue.tlType;
    switch (accountPasswordSettingsValue.tlType) {
    case TLValue::AccountPasswordSettings:
        stream << accountPasswordSettingsValue.email;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountSentChangePhoneCode &accountSentChangePhoneCodeValue)
{
    stream << accountSentChangePhoneCodeValue.tlType;
    switch (accountSentChangePhoneCodeValue.tlType) {
    case TLValue::AccountSentChangePhoneCode:
        stream << accountSentChangePhoneCodeValue.phoneCodeHash;
        stream << accountSentChangePhoneCodeValue.sendCallTimeout;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAudio &audioValue)
{
    stream << audioValue.tlType;
    switch (audioValue.tlType) {
    case TLValue::AudioEmpty:
        stream << audioValue.id;
        break;
    case TLValue::Audio:
        stream << audioValue.id;
        stream << audioValue.accessHash;
        stream << audioValue.date;
        stream << audioValue.duration;
        stream << audioValue.mimeType;
        stream << audioValue.size;
        stream << audioValue.dcId;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthCheckedPhone &authCheckedPhoneValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthExportedAuthorization &authExportedAuthorizationValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthPasswordRecovery &authPasswordRecoveryValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthSentCode &authSentCodeValue)
{
    stream << authSentCodeValue.tlType;
    switch (authSentCodeValue.tlType) {
    case TLValue::AuthSentCode:
    case TLValue::AuthSentAppCode:
        stream << authSentCodeValue.phoneRegistered;
        stream << authSentCodeValue.phoneCodeHash;
        stream << authSentCodeValue.sendCallTimeout;
        stream << authSentCodeValue.isPassword;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthorization &authorizationValue)
{
    stream << authorizationValue.tlType;
    switch (authorizationValue.tlType) {
    case TLValue::Authorization:
        stream << authorizationValue.hash;
        stream << authorizationValue.flags;
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLBotCommand &botCommandValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInfo &botInfoValue)
{
    stream << botInfoValue.tlType;
    switch (botInfoValue.tlType) {
    case TLValue::BotInfoEmpty:
        break;
    case TLValue::BotInfo:
        stream << botInfoValue.userId;
        stream << botInfoValue.version;
        stream << botInfoValue.shareText;
        stream << botInfoValue.description;
        stream << botInfoValue.commands;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelParticipant &channelParticipantValue)
{
    stream << channelParticipantValue.tlType;
    switch (channelParticipantValue.tlType) {
    case TLValue::ChannelParticipant:
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.date;
        break;
    case TLValue::ChannelParticipantSelf:
    case TLValue::ChannelParticipantModerator:
    case TLValue::ChannelParticipantEditor:
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.inviterId;
        stream << channelParticipantValue.date;
        break;
    case TLValue::ChannelParticipantKicked:
        stream << channelParticipantValue.userId;
        stream << channelParticipantValue.kickedBy;
        stream << channelParticipantValue.date;
        break;
    case TLValue::ChannelParticipantCreator:
        stream << channelParticipantValue.userId;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipant &chatParticipantValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLChatParticipants &chatParticipantsValue)
{
    stream << chatParticipantsValue.tlType;
    switch (chatParticipantsValue.tlType) {
    case TLValue::ChatParticipantsForbidden:
        stream << chatParticipantsValue.flags;
        stream << chatParticipantsValue.chatId;
        if (chatParticipantsValue.flags & 1 << 0) {
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContact &contactValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactBlocked &contactBlockedValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactLink &contactLinkValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactSuggested &contactSuggestedValue)
{
    stream << contactSuggestedValue.tlType;
    switch (contactSuggestedValue.tlType) {
    case TLValue::ContactSuggested:
        stream << contactSuggestedValue.userId;
        stream << contactSuggestedValue.mutualContacts;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLDisabledFeature &disabledFeatureValue)
{
    stream << disabledFeatureValue.tlType;
    switch (disabledFeatureValue.tlType) {
    case TLValue::DisabledFeature:
        stream << disabledFeatureValue.feature;
        stream << disabledFeatureValue.description;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedChat &encryptedChatValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedFile &encryptedFileValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLEncryptedMessage &encryptedMessageValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLError &errorValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLExportedChatInvite &exportedChatInviteValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLFileLocation &fileLocationValue)
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
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLGeoPoint &geoPointValue)
{
    stream << geoPointValue.tlType;
    switch (geoPointValue.tlType) {
    case TLValue::GeoPointEmpty:
        break;
    case TLValue::GeoPoint:
        stream << geoPointValue.longitude;
        stream << geoPointValue.latitude;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpAppChangelog &helpAppChangelogValue)
{
    stream << helpAppChangelogValue.tlType;
    switch (helpAppChangelogValue.tlType) {
    case TLValue::HelpAppChangelogEmpty:
        break;
    case TLValue::HelpAppChangelog:
        stream << helpAppChangelogValue.text;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpAppUpdate &helpAppUpdateValue)
{
    stream << helpAppUpdateValue.tlType;
    switch (helpAppUpdateValue.tlType) {
    case TLValue::HelpAppUpdate:
        stream << helpAppUpdateValue.id;
        stream << helpAppUpdateValue.critical;
        stream << helpAppUpdateValue.url;
        stream << helpAppUpdateValue.text;
        break;
    case TLValue::HelpNoAppUpdate:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpInviteText &helpInviteTextValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpTermsOfService &helpTermsOfServiceValue)
{
    stream << helpTermsOfServiceValue.tlType;
    switch (helpTermsOfServiceValue.tlType) {
    case TLValue::HelpTermsOfService:
        stream << helpTermsOfServiceValue.text;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLImportedContact &importedContactValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLInputPeerNotifyEvents &inputPeerNotifyEventsValue)
{
    stream << inputPeerNotifyEventsValue.tlType;
    switch (inputPeerNotifyEventsValue.tlType) {
    case TLValue::InputPeerNotifyEventsEmpty:
    case TLValue::InputPeerNotifyEventsAll:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageGroup &messageGroupValue)
{
    stream << messageGroupValue.tlType;
    switch (messageGroupValue.tlType) {
    case TLValue::MessageGroup:
        stream << messageGroupValue.minId;
        stream << messageGroupValue.maxId;
        stream << messageGroupValue.count;
        stream << messageGroupValue.date;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedHistory &messagesAffectedHistoryValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAffectedMessages &messagesAffectedMessagesValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDhConfig &messagesDhConfigValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSentEncryptedMessage &messagesSentEncryptedMessageValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLNearestDc &nearestDcValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLPeer &peerValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifyEvents &peerNotifyEventsValue)
{
    stream << peerNotifyEventsValue.tlType;
    switch (peerNotifyEventsValue.tlType) {
    case TLValue::PeerNotifyEventsEmpty:
    case TLValue::PeerNotifyEventsAll:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLPeerNotifySettings &peerNotifySettingsValue)
{
    stream << peerNotifySettingsValue.tlType;
    switch (peerNotifySettingsValue.tlType) {
    case TLValue::PeerNotifySettingsEmpty:
        break;
    case TLValue::PeerNotifySettings:
        stream << peerNotifySettingsValue.muteUntil;
        stream << peerNotifySettingsValue.sound;
        stream << peerNotifySettingsValue.showPreviews;
        stream << peerNotifySettingsValue.eventsMask;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotoSize &photoSizeValue)
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
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyKey &privacyKeyValue)
{
    stream << privacyKeyValue.tlType;
    switch (privacyKeyValue.tlType) {
    case TLValue::PrivacyKeyStatusTimestamp:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLPrivacyRule &privacyRuleValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLReceivedNotifyMessage &receivedNotifyMessageValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerPack &stickerPackValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLStorageFileType &storageFileTypeValue)
{
    stream << storageFileTypeValue.tlType;
    switch (storageFileTypeValue.tlType) {
    case TLValue::StorageFileUnknown:
    case TLValue::StorageFileJpeg:
    case TLValue::StorageFileGif:
    case TLValue::StorageFilePng:
    case TLValue::StorageFilePdf:
    case TLValue::StorageFileMp3:
    case TLValue::StorageFileMov:
    case TLValue::StorageFilePartial:
    case TLValue::StorageFileMp4:
    case TLValue::StorageFileWebp:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesState &updatesStateValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLUploadFile &uploadFileValue)
{
    stream << uploadFileValue.tlType;
    switch (uploadFileValue.tlType) {
    case TLValue::UploadFile:
        stream << uploadFileValue.type;
        stream << uploadFileValue.mtime;
        stream << uploadFileValue.bytes;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLUserProfilePhoto &userProfilePhotoValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLUserStatus &userStatusValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLVideo &videoValue)
{
    stream << videoValue.tlType;
    switch (videoValue.tlType) {
    case TLValue::VideoEmpty:
        stream << videoValue.id;
        break;
    case TLValue::Video:
        stream << videoValue.id;
        stream << videoValue.accessHash;
        stream << videoValue.date;
        stream << videoValue.duration;
        stream << videoValue.mimeType;
        stream << videoValue.size;
        stream << videoValue.thumb;
        stream << videoValue.dcId;
        stream << videoValue.w;
        stream << videoValue.h;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLWallPaper &wallPaperValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountAuthorizations &accountAuthorizationsValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineMessage &botInlineMessageValue)
{
    stream << botInlineMessageValue.tlType;
    switch (botInlineMessageValue.tlType) {
    case TLValue::BotInlineMessageMediaAuto:
        stream << botInlineMessageValue.caption;
        break;
    case TLValue::BotInlineMessageText:
        stream << botInlineMessageValue.flags;
        stream << botInlineMessageValue.message;
        if (botInlineMessageValue.flags & 1 << 1) {
            stream << botInlineMessageValue.entities;
        }
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChatPhoto &chatPhotoValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactStatus &contactStatusValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLDcOption &dcOptionValue)
{
    stream << dcOptionValue.tlType;
    switch (dcOptionValue.tlType) {
    case TLValue::DcOption:
        stream << dcOptionValue.flags;
        stream << dcOptionValue.id;
        stream << dcOptionValue.ipAddress;
        stream << dcOptionValue.port;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLDialog &dialogValue)
{
    stream << dialogValue.tlType;
    switch (dialogValue.tlType) {
    case TLValue::Dialog:
        stream << dialogValue.peer;
        stream << dialogValue.topMessage;
        stream << dialogValue.readInboxMaxId;
        stream << dialogValue.unreadCount;
        stream << dialogValue.notifySettings;
        break;
    case TLValue::DialogChannel:
        stream << dialogValue.peer;
        stream << dialogValue.topMessage;
        stream << dialogValue.topImportantMessage;
        stream << dialogValue.readInboxMaxId;
        stream << dialogValue.unreadCount;
        stream << dialogValue.unreadImportantCount;
        stream << dialogValue.notifySettings;
        stream << dialogValue.pts;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLNotifyPeer &notifyPeerValue)
{
    stream << notifyPeerValue.tlType;
    switch (notifyPeerValue.tlType) {
    case TLValue::NotifyPeer:
        stream << notifyPeerValue.peer;
        break;
    case TLValue::NotifyUsers:
    case TLValue::NotifyChats:
    case TLValue::NotifyAll:
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLPhoto &photoValue)
{
    stream << photoValue.tlType;
    switch (photoValue.tlType) {
    case TLValue::PhotoEmpty:
        stream << photoValue.id;
        break;
    case TLValue::Photo:
        stream << photoValue.id;
        stream << photoValue.accessHash;
        stream << photoValue.date;
        stream << photoValue.sizes;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLStickerSet &stickerSetValue)
{
    stream << stickerSetValue.tlType;
    switch (stickerSetValue.tlType) {
    case TLValue::StickerSet:
        stream << stickerSetValue.flags;
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLUser &userValue)
{
    stream << userValue.tlType;
    switch (userValue.tlType) {
    case TLValue::UserEmpty:
        stream << userValue.id;
        break;
    case TLValue::User:
        stream << userValue.flags;
        stream << userValue.id;
        if (userValue.flags & 1 << 0) {
            stream << userValue.accessHash;
        }
        if (userValue.flags & 1 << 1) {
            stream << userValue.firstName;
        }
        if (userValue.flags & 1 << 2) {
            stream << userValue.lastName;
        }
        if (userValue.flags & 1 << 3) {
            stream << userValue.username;
        }
        if (userValue.flags & 1 << 4) {
            stream << userValue.phone;
        }
        if (userValue.flags & 1 << 5) {
            stream << userValue.photo;
        }
        if (userValue.flags & 1 << 6) {
            stream << userValue.status;
        }
        if (userValue.flags & 1 << 14) {
            stream << userValue.botInfoVersion;
        }
        if (userValue.flags & 1 << 18) {
            stream << userValue.restrictionReason;
        }
        if (userValue.flags & 1 << 19) {
            stream << userValue.botInlinePlaceholder;
        }
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLAccountPrivacyRules &accountPrivacyRulesValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLAuthAuthorization &authAuthorizationValue)
{
    stream << authAuthorizationValue.tlType;
    switch (authAuthorizationValue.tlType) {
    case TLValue::AuthAuthorization:
        stream << authAuthorizationValue.user;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelsChannelParticipant &channelsChannelParticipantValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLChannelsChannelParticipants &channelsChannelParticipantsValue)
{
    stream << channelsChannelParticipantsValue.tlType;
    switch (channelsChannelParticipantsValue.tlType) {
    case TLValue::ChannelsChannelParticipants:
        stream << channelsChannelParticipantsValue.count;
        stream << channelsChannelParticipantsValue.participants;
        stream << channelsChannelParticipantsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChat &chatValue)
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
        if (chatValue.flags & 1 << 6) {
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
        stream << chatValue.accessHash;
        stream << chatValue.title;
        if (chatValue.flags & 1 << 6) {
            stream << chatValue.username;
        }
        stream << chatValue.photo;
        stream << chatValue.date;
        stream << chatValue.version;
        if (chatValue.flags & 1 << 9) {
            stream << chatValue.restrictionReason;
        }
        break;
    case TLValue::ChannelForbidden:
        stream << chatValue.id;
        stream << chatValue.accessHash;
        stream << chatValue.title;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChatFull &chatFullValue)
{
    stream << chatFullValue.tlType;
    switch (chatFullValue.tlType) {
    case TLValue::ChatFull:
        stream << chatFullValue.id;
        stream << chatFullValue.participants;
        stream << chatFullValue.chatPhoto;
        stream << chatFullValue.notifySettings;
        stream << chatFullValue.exportedInvite;
        stream << chatFullValue.botInfo;
        break;
    case TLValue::ChannelFull:
        stream << chatFullValue.flags;
        stream << chatFullValue.id;
        stream << chatFullValue.about;
        if (chatFullValue.flags & 1 << 0) {
            stream << chatFullValue.participantsCount;
        }
        if (chatFullValue.flags & 1 << 1) {
            stream << chatFullValue.adminsCount;
        }
        if (chatFullValue.flags & 1 << 2) {
            stream << chatFullValue.kickedCount;
        }
        stream << chatFullValue.readInboxMaxId;
        stream << chatFullValue.unreadCount;
        stream << chatFullValue.unreadImportantCount;
        stream << chatFullValue.chatPhoto;
        stream << chatFullValue.notifySettings;
        stream << chatFullValue.exportedInvite;
        stream << chatFullValue.botInfo;
        if (chatFullValue.flags & 1 << 4) {
            stream << chatFullValue.migratedFromChatId;
        }
        if (chatFullValue.flags & 1 << 4) {
            stream << chatFullValue.migratedFromMaxId;
        }
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLChatInvite &chatInviteValue)
{
    stream << chatInviteValue.tlType;
    switch (chatInviteValue.tlType) {
    case TLValue::ChatInviteAlready:
        stream << chatInviteValue.chat;
        break;
    case TLValue::ChatInvite:
        stream << chatInviteValue.flags;
        stream << chatInviteValue.title;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLConfig &configValue)
{
    stream << configValue.tlType;
    switch (configValue.tlType) {
    case TLValue::Config:
        stream << configValue.date;
        stream << configValue.expires;
        stream << configValue.testMode;
        stream << configValue.thisDc;
        stream << configValue.dcOptions;
        stream << configValue.chatSizeMax;
        stream << configValue.megagroupSizeMax;
        stream << configValue.forwardedCountMax;
        stream << configValue.onlineUpdatePeriodMs;
        stream << configValue.offlineBlurTimeoutMs;
        stream << configValue.offlineIdleTimeoutMs;
        stream << configValue.onlineCloudTimeoutMs;
        stream << configValue.notifyCloudDelayMs;
        stream << configValue.notifyDefaultDelayMs;
        stream << configValue.chatBigSize;
        stream << configValue.pushChatPeriodMs;
        stream << configValue.pushChatLimit;
        stream << configValue.savedGifsLimit;
        stream << configValue.disabledFeatures;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsBlocked &contactsBlockedValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsContacts &contactsContactsValue)
{
    stream << contactsContactsValue.tlType;
    switch (contactsContactsValue.tlType) {
    case TLValue::ContactsContactsNotModified:
        break;
    case TLValue::ContactsContacts:
        stream << contactsContactsValue.contacts;
        stream << contactsContactsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsFound &contactsFoundValue)
{
    stream << contactsFoundValue.tlType;
    switch (contactsFoundValue.tlType) {
    case TLValue::ContactsFound:
        stream << contactsFoundValue.results;
        stream << contactsFoundValue.chats;
        stream << contactsFoundValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsImportedContacts &contactsImportedContactsValue)
{
    stream << contactsImportedContactsValue.tlType;
    switch (contactsImportedContactsValue.tlType) {
    case TLValue::ContactsImportedContacts:
        stream << contactsImportedContactsValue.imported;
        stream << contactsImportedContactsValue.retryContacts;
        stream << contactsImportedContactsValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsLink &contactsLinkValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsResolvedPeer &contactsResolvedPeerValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLContactsSuggested &contactsSuggestedValue)
{
    stream << contactsSuggestedValue.tlType;
    switch (contactsSuggestedValue.tlType) {
    case TLValue::ContactsSuggested:
        stream << contactsSuggestedValue.results;
        stream << contactsSuggestedValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLDocument &documentValue)
{
    stream << documentValue.tlType;
    switch (documentValue.tlType) {
    case TLValue::DocumentEmpty:
        stream << documentValue.id;
        break;
    case TLValue::Document:
        stream << documentValue.id;
        stream << documentValue.accessHash;
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLFoundGif &foundGifValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLHelpSupport &helpSupportValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageAction &messageActionValue)
{
    stream << messageActionValue.tlType;
    switch (messageActionValue.tlType) {
    case TLValue::MessageActionEmpty:
    case TLValue::MessageActionChatDeletePhoto:
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
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesAllStickers &messagesAllStickersValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChatFull &messagesChatFullValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesChats &messagesChatsValue)
{
    stream << messagesChatsValue.tlType;
    switch (messagesChatsValue.tlType) {
    case TLValue::MessagesChats:
        stream << messagesChatsValue.chats;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesFoundGifs &messagesFoundGifsValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesSavedGifs &messagesSavedGifsValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickerSet &messagesStickerSetValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesStickers &messagesStickersValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhoto &photosPhotoValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLPhotosPhotos &photosPhotosValue)
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLUserFull &userFullValue)
{
    stream << userFullValue.tlType;
    switch (userFullValue.tlType) {
    case TLValue::UserFull:
        stream << userFullValue.user;
        stream << userFullValue.link;
        stream << userFullValue.profilePhoto;
        stream << userFullValue.notifySettings;
        stream << userFullValue.blocked;
        stream << userFullValue.botInfo;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLWebPage &webPageValue)
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
        if (webPageValue.flags & 1 << 0) {
            stream << webPageValue.type;
        }
        if (webPageValue.flags & 1 << 1) {
            stream << webPageValue.siteName;
        }
        if (webPageValue.flags & 1 << 2) {
            stream << webPageValue.title;
        }
        if (webPageValue.flags & 1 << 3) {
            stream << webPageValue.description;
        }
        if (webPageValue.flags & 1 << 4) {
            stream << webPageValue.photo;
        }
        if (webPageValue.flags & 1 << 5) {
            stream << webPageValue.embedUrl;
        }
        if (webPageValue.flags & 1 << 5) {
            stream << webPageValue.embedType;
        }
        if (webPageValue.flags & 1 << 6) {
            stream << webPageValue.embedWidth;
        }
        if (webPageValue.flags & 1 << 6) {
            stream << webPageValue.embedHeight;
        }
        if (webPageValue.flags & 1 << 7) {
            stream << webPageValue.duration;
        }
        if (webPageValue.flags & 1 << 8) {
            stream << webPageValue.author;
        }
        if (webPageValue.flags & 1 << 9) {
            stream << webPageValue.document;
        }
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLBotInlineResult &botInlineResultValue)
{
    stream << botInlineResultValue.tlType;
    switch (botInlineResultValue.tlType) {
    case TLValue::BotInlineMediaResultDocument:
        stream << botInlineResultValue.id;
        stream << botInlineResultValue.type;
        stream << botInlineResultValue.document;
        stream << botInlineResultValue.sendMessage;
        break;
    case TLValue::BotInlineMediaResultPhoto:
        stream << botInlineResultValue.id;
        stream << botInlineResultValue.type;
        stream << botInlineResultValue.photo;
        stream << botInlineResultValue.sendMessage;
        break;
    case TLValue::BotInlineResult:
        stream << botInlineResultValue.flags;
        stream << botInlineResultValue.id;
        stream << botInlineResultValue.type;
        if (botInlineResultValue.flags & 1 << 1) {
            stream << botInlineResultValue.title;
        }
        if (botInlineResultValue.flags & 1 << 2) {
            stream << botInlineResultValue.description;
        }
        if (botInlineResultValue.flags & 1 << 3) {
            stream << botInlineResultValue.url;
        }
        if (botInlineResultValue.flags & 1 << 4) {
            stream << botInlineResultValue.thumbUrl;
        }
        if (botInlineResultValue.flags & 1 << 5) {
            stream << botInlineResultValue.contentUrl;
        }
        if (botInlineResultValue.flags & 1 << 5) {
            stream << botInlineResultValue.contentType;
        }
        if (botInlineResultValue.flags & 1 << 6) {
            stream << botInlineResultValue.w;
        }
        if (botInlineResultValue.flags & 1 << 6) {
            stream << botInlineResultValue.h;
        }
        if (botInlineResultValue.flags & 1 << 7) {
            stream << botInlineResultValue.duration;
        }
        stream << botInlineResultValue.sendMessage;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessageMedia &messageMediaValue)
{
    stream << messageMediaValue.tlType;
    switch (messageMediaValue.tlType) {
    case TLValue::MessageMediaEmpty:
    case TLValue::MessageMediaUnsupported:
        break;
    case TLValue::MessageMediaPhoto:
        stream << messageMediaValue.photo;
        stream << messageMediaValue.caption;
        break;
    case TLValue::MessageMediaVideo:
        stream << messageMediaValue.video;
        stream << messageMediaValue.caption;
        break;
    case TLValue::MessageMediaGeo:
        stream << messageMediaValue.geo;
        break;
    case TLValue::MessageMediaContact:
        stream << messageMediaValue.phoneNumber;
        stream << messageMediaValue.firstName;
        stream << messageMediaValue.lastName;
        stream << messageMediaValue.userId;
        break;
    case TLValue::MessageMediaDocument:
        stream << messageMediaValue.document;
        stream << messageMediaValue.caption;
        break;
    case TLValue::MessageMediaAudio:
        stream << messageMediaValue.audio;
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
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesBotResults &messagesBotResultsValue)
{
    stream << messagesBotResultsValue.tlType;
    switch (messagesBotResultsValue.tlType) {
    case TLValue::MessagesBotResults:
        stream << messagesBotResultsValue.flags;
        stream << messagesBotResultsValue.queryId;
        if (messagesBotResultsValue.flags & 1 << 1) {
            stream << messagesBotResultsValue.nextOffset;
        }
        stream << messagesBotResultsValue.results;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessage &messageValue)
{
    stream << messageValue.tlType;
    switch (messageValue.tlType) {
    case TLValue::MessageEmpty:
        stream << messageValue.id;
        break;
    case TLValue::Message:
        stream << messageValue.flags;
        stream << messageValue.id;
        if (messageValue.flags & 1 << 8) {
            stream << messageValue.fromId;
        }
        stream << messageValue.toId;
        if (messageValue.flags & 1 << 2) {
            stream << messageValue.fwdFromId;
        }
        if (messageValue.flags & 1 << 2) {
            stream << messageValue.fwdDate;
        }
        if (messageValue.flags & 1 << 11) {
            stream << messageValue.viaBotId;
        }
        if (messageValue.flags & 1 << 3) {
            stream << messageValue.replyToMsgId;
        }
        stream << messageValue.date;
        stream << messageValue.message;
        if (messageValue.flags & 1 << 9) {
            stream << messageValue.media;
        }
        if (messageValue.flags & 1 << 6) {
            stream << messageValue.replyMarkup;
        }
        if (messageValue.flags & 1 << 7) {
            stream << messageValue.entities;
        }
        if (messageValue.flags & 1 << 10) {
            stream << messageValue.views;
        }
        break;
    case TLValue::MessageService:
        stream << messageValue.flags;
        stream << messageValue.id;
        if (messageValue.flags & 1 << 8) {
            stream << messageValue.fromId;
        }
        stream << messageValue.toId;
        stream << messageValue.date;
        stream << messageValue.action;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesDialogs &messagesDialogsValue)
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
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLMessagesMessages &messagesMessagesValue)
{
    stream << messagesMessagesValue.tlType;
    switch (messagesMessagesValue.tlType) {
    case TLValue::MessagesMessages:
        stream << messagesMessagesValue.messages;
        stream << messagesMessagesValue.chats;
        stream << messagesMessagesValue.users;
        break;
    case TLValue::MessagesMessagesSlice:
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
        if (messagesMessagesValue.flags & 1 << 0) {
            stream << messagesMessagesValue.collapsed;
        }
        stream << messagesMessagesValue.chats;
        stream << messagesMessagesValue.users;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdate &updateValue)
{
    stream << updateValue.tlType;
    switch (updateValue.tlType) {
    case TLValue::UpdateNewMessage:
    case TLValue::UpdateNewChannelMessage:
        stream << updateValue.message;
        stream << updateValue.pts;
        stream << updateValue.ptsCount;
        break;
    case TLValue::UpdateMessageID:
        stream << updateValue.id;
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
    case TLValue::UpdateContactRegistered:
        stream << updateValue.userId;
        stream << updateValue.date;
        break;
    case TLValue::UpdateContactLink:
        stream << updateValue.userId;
        stream << updateValue.myLink;
        stream << updateValue.foreignLink;
        break;
    case TLValue::UpdateNewAuthorization:
        stream << updateValue.authKeyId;
        stream << updateValue.date;
        stream << updateValue.device;
        stream << updateValue.location;
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
        stream << updateValue.type;
        stream << updateValue.stringMessage;
        stream << updateValue.media;
        stream << updateValue.popup;
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
    case TLValue::UpdateChannel:
        stream << updateValue.channelId;
        break;
    case TLValue::UpdateChannelGroup:
        stream << updateValue.channelId;
        stream << updateValue.group;
        break;
    case TLValue::UpdateReadChannelInbox:
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
        stream << updateValue.id;
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
        stream << updateValue.order;
        break;
    case TLValue::UpdateStickerSets:
    case TLValue::UpdateSavedGifs:
        break;
    case TLValue::UpdateBotInlineQuery:
        stream << updateValue.queryId;
        stream << updateValue.userId;
        stream << updateValue.query;
        stream << updateValue.offset;
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdates &updatesValue)
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
        if (updatesValue.flags & 1 << 2) {
            stream << updatesValue.fwdFromId;
        }
        if (updatesValue.flags & 1 << 2) {
            stream << updatesValue.fwdDate;
        }
        if (updatesValue.flags & 1 << 11) {
            stream << updatesValue.viaBotId;
        }
        if (updatesValue.flags & 1 << 3) {
            stream << updatesValue.replyToMsgId;
        }
        if (updatesValue.flags & 1 << 7) {
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
        if (updatesValue.flags & 1 << 2) {
            stream << updatesValue.fwdFromId;
        }
        if (updatesValue.flags & 1 << 2) {
            stream << updatesValue.fwdDate;
        }
        if (updatesValue.flags & 1 << 11) {
            stream << updatesValue.viaBotId;
        }
        if (updatesValue.flags & 1 << 3) {
            stream << updatesValue.replyToMsgId;
        }
        if (updatesValue.flags & 1 << 7) {
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
        if (updatesValue.flags & 1 << 9) {
            stream << updatesValue.media;
        }
        if (updatesValue.flags & 1 << 7) {
            stream << updatesValue.entities;
        }
        break;
    default:
        break;
    }

    return stream;
}

CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesChannelDifference &updatesChannelDifferenceValue)
{
    stream << updatesChannelDifferenceValue.tlType;
    switch (updatesChannelDifferenceValue.tlType) {
    case TLValue::UpdatesChannelDifferenceEmpty:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & 1 << 1) {
            stream << updatesChannelDifferenceValue.timeout;
        }
        break;
    case TLValue::UpdatesChannelDifferenceTooLong:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & 1 << 1) {
            stream << updatesChannelDifferenceValue.timeout;
        }
        stream << updatesChannelDifferenceValue.topMessage;
        stream << updatesChannelDifferenceValue.topImportantMessage;
        stream << updatesChannelDifferenceValue.readInboxMaxId;
        stream << updatesChannelDifferenceValue.unreadCount;
        stream << updatesChannelDifferenceValue.unreadImportantCount;
        stream << updatesChannelDifferenceValue.messages;
        stream << updatesChannelDifferenceValue.chats;
        stream << updatesChannelDifferenceValue.users;
        break;
    case TLValue::UpdatesChannelDifference:
        stream << updatesChannelDifferenceValue.flags;
        stream << updatesChannelDifferenceValue.pts;
        if (updatesChannelDifferenceValue.flags & 1 << 1) {
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

CTelegramStream &operator<<(CTelegramStream &stream, const TLUpdatesDifference &updatesDifferenceValue)
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
    default:
        break;
    }

    return stream;
}
// End of generated write operators implementation
