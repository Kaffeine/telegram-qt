#ifndef TELEGRAM_SERVER_NAMESPACE_HPP
#define TELEGRAM_SERVER_NAMESPACE_HPP

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Server {

struct InputPeer : public Telegram::Peer
{
    InputPeer() = default;
    InputPeer(const Telegram::Peer &peer);

    qint64 accessHash = 0;
};

struct ServerSalt
{
    quint64 salt = 0;
    quint32 validSince = 0;
    quint32 validUntil = 0;
};

struct UserDialog
{
    Telegram::Peer peer;
    QString draftText;
    quint32 topMessage = 0;
    quint64 date = 0;
    quint32 readInboxMaxId = 0;
    quint32 readOutboxMaxId = 0;
    quint32 unreadCount = 0;
    quint32 unreadMentionsCount = 0;
    quint32 pts = 0;
};

struct UserContact
{
    quint32 id = 0;
    QString phone;
    QString firstName;
    QString lastName;
};

// Overall file descriptor
struct FileDescriptor
{
    bool isValid() const { return true; }

    // FileLocation:
    quint64 volumeId = 0;
    quint32 localId = 0;
    quint64 secret = 0;
    quint32 dcId = 0;

    // InputFileLocation:
    // quint64 volumeId;
    // quint32 localId;
    // quint64 secret;
    quint64 id = 0;
    quint64 accessHash = 0;

    // InputFile:
    // quint64 id;
    quint32 parts = 0;
    quint32 date = 0;
    quint32 size = 0;
    QString name;
    QString md5Checksum;
    QString mimeType;
};

struct FileData
{
    quint64 fileId = 0;
    QByteArrayList partList;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_NAMESPACE_HPP
