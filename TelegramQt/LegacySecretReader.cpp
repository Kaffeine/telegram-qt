#include "LegacySecretReader.hpp"

#include "RawStream.hpp"
#include "Utils.hpp"

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

const quint32 secretFormatVersion = 4;
//Format v4:
//quint32 secretFormatVersion
//qint32 deltaTime

//DC {
//    quint32 id
//    QByteArray ipAddress
//    quint32 port
//}

//QByteArray authKey
//quint64 authId
//quint64 serverSalt

//UpdatesState {
//    quint32 pts
//    quint32 qts
//    quint32 date
//}

//quint32 dialogsCount
//Dialog (N = dialogsCount) {
//    quint8 type (one of DialogType (DialogTypeDialog or DialogTypeChannel))
//    Peer {
//        quint8 type (one of Telegram::Peer::{User, Chat, Channel})
//        quint32 id
//    }
//    quint32 readInboxMaxId
//    quint32 unreadCount
//    type == DialogTypeChannel ? {
//        quint32 pts
//    }
//}

static const quint32 s_legacyDcInfoTlType = 0x2ec2a43cu; // Scheme23_DcOption
static const quint32 s_legacyVectorTlType = 0x1cb5c415u; // Scheme23_Vector;

bool LegacySecretReader::loadFromData(const QByteArray &data)
{
    isValid = setSecretInfo(data);
    return isValid;
}

bool LegacySecretReader::setSecretInfo(const QByteArray &secret)
{
    RawStreamEx inputStream(secret);
    quint32 format;
    inputStream >> format;

    if (format > secretFormatVersion) {
        qWarning() << Q_FUNC_INFO << "Unknown format version" << format;
        return false;
    } else {
        qDebug() << Q_FUNC_INFO << "Format version:" << format;
    }

    inputStream >> deltaTime;

    if (format < 4) {
        quint32 legacyDcInfoTlType;
        inputStream >> legacyDcInfoTlType;

        if (legacyDcInfoTlType != s_legacyDcInfoTlType) {
            qWarning() << Q_FUNC_INFO << "Unexpected dataversion" << format;
            return false;
        }
    }

    quint32 dcId = 0;
    inputStream >> dcId;
    if (format < 4) {
        QByteArray legacyDcHostName;
        inputStream >> legacyDcHostName;
    }
    QByteArray dcIpAddress;
    inputStream >> dcIpAddress;
    quint32 dcPort = 0;
    inputStream >> dcPort;

    if (format < 3) {
        QByteArray legacySelfPhone;
        inputStream >> legacySelfPhone;
        phoneNumber = QString::fromLatin1(legacySelfPhone);
    }

    inputStream >> authKey;

    if (authKey.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Empty auth key data.";
        return false;
    }

    inputStream >> authId;
    quint64 serverSalt;
    inputStream >> serverSalt;

    const quint64 expectedAuthId = Utils::getFingerprints(authKey, Utils::Lower64Bits);
    if (authId != expectedAuthId) {
        qDebug() << Q_FUNC_INFO << "The auth key data is not valid.";
        return false;
    }

    if (inputStream.error()) {
        qWarning() << Q_FUNC_INFO << "Read error occurred.";
        return false;
    }

    if (format >= 1) {
        quint32 pts = 0;
        quint32 qts = 0;
        quint32 date = 0;
        inputStream >> pts;
        inputStream >> qts;
        inputStream >> date;
    }
//    if (format >= 4) {
//        quint32 dialogsCount = 0;
//        inputStream >> dialogsCount;
//        QHash<Telegram::Peer,TLDialog> dialogs;
//        dialogs.reserve(dialogsCount + 5);
//        for (quint32 i = 0; i < dialogsCount; ++i) {
//            TLDialog dialog;
//            quint8 dialogType = 0;
//            inputStream >> dialogType;

//            switch (dialogType) {
//            case DialogTypeDialog:
//                dialog.tlType = TLValue::Dialog;
//                break;
//            case DialogTypeChannel:
//                dialog.tlType = TLValue::DialogChannel;
//                break;
//            default:
//                qWarning() << Q_FUNC_INFO << "Read invalid dialog type";
//                return false;
//                break;
//            }

//            quint8 peerType = 0;
//            quint32 peerId = 0;
//            inputStream >> peerType >> peerId;
//            Telegram::Peer peer(peerId, static_cast<Telegram::Peer::Type>(peerType));
//            if (!peer.isValid()) {
//                qWarning() << "Session data contains invalid peer";
//                return false;
//            }
//            dialog.peer = toTLPeer(peer);
//            inputStream >> dialog.readInboxMaxId;
//            inputStream >> dialog.unreadCount;

//            if (dialogType == DialogTypeChannel) {
//                inputStream >> dialog.pts;
//            }
//            dialogs.insert(peer, dialog);
//        }
//        // Do not apply loaded dialogs, because we can not clean them up properly on dialogs received
//    } else if (format >= 2) {
//        quint32 legacyVectorTlType;
//        quint32 chatIdsVectorSize = 0;

//        inputStream >> legacyVectorTlType;
//        inputStream >> chatIdsVectorSize;
//        if (legacyVectorTlType != s_legacyVectorTlType) {
//            qWarning() << "Unexpected type value";
//            return false;
//        }

//        m_chatIds.resize(chatIdsVectorSize);

//        for (int i = 0; i < m_chatIds.count(); ++i) {
//            inputStream >> m_chatIds[i];
//        }
//    }
    return true;
}


} // Client

} // Telegram
