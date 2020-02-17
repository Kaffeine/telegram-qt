#ifndef TELEGRAM_SERVER_NAMESPACE_HPP
#define TELEGRAM_SERVER_NAMESPACE_HPP

#include "TelegramNamespace_p.hpp"

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

struct UserContact
{
    bool operator==(const UserContact &another) const;
    bool operator!=(const UserContact &another) const;

    quint32 id = 0;
    QString phone;
    QString firstName;
    QString lastName;
};

// Overall file descriptor
class FileDescriptor
{
public:
    bool isValid() const { return true; }

    bool operator==(const FileDescriptor &another) const;
    bool operator!=(const FileDescriptor &another) const;

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

struct UploadDescriptor
{
    quint64 fileId = 0;
    QByteArrayList partList;
};

struct ImageSizeDescriptor
{
    static constexpr int Small = 90;   // S
    static constexpr int Medium = 320; // M
    static constexpr int Large = 800;  // X
    static constexpr int Max = 1280;   // Y. Check that 1280 is the actual limit

    static const QVector<int> Sizes;

    bool operator==(const ImageSizeDescriptor &another) const;

    int sizeType;
    FileDescriptor fileDescriptor;
    quint32 w = 0;
    quint32 h = 0;
    quint32 size = 0;
    QByteArray bytes;
};

struct ImageDescriptor
{
    bool isValid() const { return id && !sizes.isEmpty(); }
    bool operator==(const ImageDescriptor &another) const;
    bool operator!=(const ImageDescriptor &another) const;

    quint64 id = 0;
    quint64 accessHash = 0;
    quint32 flags = 0;
    quint32 date = 0;

    QVector<ImageSizeDescriptor> sizes;
};

struct PeerImage
{
    bool operator==(const PeerImage &another) const;

    quint64 id = 0;
    FileDescriptor small;
    FileDescriptor big;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_SERVER_NAMESPACE_HPP
