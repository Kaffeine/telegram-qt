#include "FileOperation_p.hpp"

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
}

FileOperationPrivate *FileOperationPrivate::get(FileOperation *parent)
{
    return static_cast<FileOperationPrivate*>(parent->d);
}

} // Client namespace

} // Telegram namespace
