#include "FileOperation_p.hpp"

#include <QBuffer>

namespace Telegram {

namespace Client {

/*!
    \class Telegram::Client::FileOperation
    \inmodule TelegramQt
    \ingroup Client
 */
FileOperation::FileOperation(QObject *parent) :
    PendingOperation(new FileOperationPrivate(this), parent)
{
}

const FileInfo *FileOperation::fileInfo()
{
    Q_D(const FileOperation);
    static const FileInfo invalidInfo;
    return d->m_fileInfo ? d->m_fileInfo : &invalidInfo;
}

QIODevice *FileOperation::device() const
{
    Q_D(const FileOperation);
    return d->m_device;
}

quint32 FileOperation::bytesTransferred() const
{
    Q_D(const FileOperation);
    return d->m_totalTransferredBytes;
}

void FileOperation::cancel()
{
    emit canceled(this);
}

FileOperationPrivate::FileOperationPrivate(PendingOperation *parent)
    : PendingOperationPrivate(parent)
{
}

FileOperationPrivate::~FileOperationPrivate()
{
    delete m_fileInfo;
    m_fileInfo = nullptr;

    if (m_ownBuffer) {
        delete m_ownBuffer;
        m_ownBuffer = nullptr;
    }
}

FileOperationPrivate *FileOperationPrivate::get(FileOperation *parent)
{
    return static_cast<FileOperationPrivate*>(parent->d);
}

void FileOperationPrivate::ensureDeviceIsSet(QIODevice *device)
{
    if (!device) {
        m_ownBuffer = new QBuffer(q_ptr);
        device = m_ownBuffer;
    }
    m_device = device;
}

void FileOperationPrivate::prepareForDownload()
{
    if (m_ownBuffer) {
        m_ownBuffer->open(QIODevice::WriteOnly);
    }
    m_totalTransferredBytes = 0;
}

void FileOperationPrivate::finalizeDownload()
{
    if (m_ownBuffer) {
        m_ownBuffer->close();
        m_ownBuffer->open(QIODevice::ReadOnly);
    }
}

} // Client namespace

} // Telegram namespace
