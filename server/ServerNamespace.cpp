#include "ServerNamespace.hpp"

namespace Telegram {

namespace Server {

bool UserContact::operator==(const UserContact &another) const
{
    if (!(id == another.id)
            || !(phone == another.phone)
            || !(firstName == another.firstName)
            || !(lastName == another.lastName)) {
        return false;
    }

    return true;
}

bool UserContact::operator!=(const UserContact &another) const
{
    return !(*this == another);
}

bool FileDescriptor::operator==(const FileDescriptor &another) const
{
    if ((volumeId != another.volumeId)
            || (localId != another.localId)
            || (secret != another.secret)
            || (dcId != another.dcId)) {
        return false;
    }

    if ((id != another.id) || (accessHash != another.accessHash)) {
        return false;
    }

    if ((parts != another.parts)
            || (date != another.date)
            || (size != another.size)
            || (name != another.name)
            || (md5Checksum != another.md5Checksum)
            || (mimeType != another.mimeType)) {
        return false;
    }

    return true;
}

bool FileDescriptor::operator!=(const FileDescriptor &another) const
{
    return !(*this == another);
}

bool ImageSizeDescriptor::operator==(const ImageSizeDescriptor &another) const
{
    if ((sizeType != another.sizeType)
            || !(fileDescriptor == another.fileDescriptor)
            || (w != another.w)
            || (h != another.h)
            || (size != another.size)
            || (bytes != another.bytes)) {
        return false;
    }

    return true;
}

bool ImageDescriptor::operator==(const ImageDescriptor &another) const
{
    if ((id != another.id)
            || !(sizes == another.sizes)
            || (accessHash != another.accessHash)
            || (flags != another.flags)
            || (date != another.date)) {
        return false;
    }

    return true;
}

bool ImageDescriptor::operator!=(const ImageDescriptor &another) const
{
    return !(*this == another);
}

bool PeerImage::operator==(const PeerImage &another) const
{
    if (!(id == another.id)
            || !(small == another.small)
            || !(big == another.big)) {
        return false;
    }

    return true;
}

} // Server namespace

} // Telegram namespace
