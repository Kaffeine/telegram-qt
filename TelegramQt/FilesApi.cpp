#include "FilesApi_p.hpp"

#include "ApiUtils.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ConnectionApi_p.hpp"
#include "DataStorage_p.hpp"
#include "Debug_p.hpp"
#include "Operations/ConnectionOperation.hpp"
#include "Operations/FileOperation_p.hpp"
#include "RpcLayers/ClientRpcUploadLayer.hpp"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFilesApi, "telegram.client.api.files", QtWarningMsg)

namespace Telegram {

namespace Client {

FilesApiPrivate::FilesApiPrivate(FilesApi *parent) :
    ClientApiPrivate(parent)
{
}

FilesApiPrivate *FilesApiPrivate::get(FilesApi *parent)
{
    return reinterpret_cast<FilesApiPrivate*>(parent->d);
}

FileOperation *FilesApiPrivate::downloadFile(const QString &fileId, QIODevice *output)
{
    return PendingOperation::failOperation<FileOperation>
            (QLatin1String("Not implemented"), this);
}

FileOperation *FilesApiPrivate::downloadFile(const FileInfo *file, QIODevice *output)
{
    if (!file->isValid()) {
        return PendingOperation::failOperation<FileOperation>
                (QLatin1String("Invalid FileInfo for getFile()"), this);
    }

    return PendingOperation::failOperation<FileOperation>
            (QLatin1String("Not implemented"), this);
}

FileOperation *FilesApiPrivate::uploadFile(const QByteArray &fileContent, const QString &fileName)
{
    return PendingOperation::failOperation<FileOperation>
            (QLatin1String("Not implemented"), this);
}

FileOperation *FilesApiPrivate::uploadFile(QIODevice *source, const QString &fileName)
{
    return PendingOperation::failOperation<FileOperation>
            (QLatin1String("Not implemented"), this);
}

/*!
    \class Telegram::Client::FilesApi
    \brief Provides an API to work download and upload files.

    \inmodule TelegramQt
    \ingroup Client
*/
FilesApi::FilesApi(QObject *parent) :
    ClientApi(parent)
{
    d = new FilesApiPrivate(this);
}

FileOperation *FilesApi::downloadFile(const QString &fileId, QIODevice *output)
{
    Q_D(FilesApi);
    return d->downloadFile(fileId, output);
}

FileOperation *FilesApi::downloadFile(const FileInfo *file, QIODevice *output)
{
    Q_D(FilesApi);
    return d->downloadFile(file, output);
}

FileOperation *FilesApi::uploadFile(const QByteArray &data, const QString &fileName)
{
    Q_D(FilesApi);
    return d->uploadFile(data, fileName);
}

FileOperation *FilesApi::uploadFile(QIODevice *input, const QString &fileName)
{
    Q_D(FilesApi);
    return d->uploadFile(input, fileName);
}

} // Client namespace

} // Telegram namespace
