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
#include <QTimer>

Q_LOGGING_CATEGORY(lcFilesApi, "telegram.client.api.files", QtWarningMsg)

namespace Telegram {

namespace Client {

FilesApiPrivate::FilesApiPrivate(FilesApi *parent) :
    ClientApiPrivate(parent)
{
    m_uploadLayer = new UploadRpcLayer(this);

    if (lcFilesApi().isDebugEnabled()) {
        m_monitorTimer = new QTimer(this);
        m_monitorTimer->setInterval(5000);
        m_monitorTimer->setSingleShot(false);
        connect(m_monitorTimer, &QTimer::timeout, this, &FilesApiPrivate::dumpCurrentState);
        m_monitorTimer->start();
    }
}

FilesApiPrivate *FilesApiPrivate::get(FilesApi *parent)
{
    return reinterpret_cast<FilesApiPrivate*>(parent->d);
}

/* Download FileOperation does not fail on network errors.
 * FileOperation fails if:
 * - the file location is not valid. E.g.
 *   - if we has no such DC in DC Configuration or
 *   - the server returns InvalidLocation or similar error
 */
FileOperation *FilesApiPrivate::downloadFile(const QString &fileId, QIODevice *output)
{
    const FileInfo::Private info = FileInfo::Private::fromFileId(fileId);
    if (!info.isValid()) {
        return PendingOperation::failOperation<FileOperation>
                (QLatin1String("Invalid RemoteFile for getFile()"), this);
    }

    FileInfo *file = new FileInfo();
    FileInfo::Private *filePriv = FileInfo::Private::get(file);
    *filePriv = info;

    const FileRequestDescriptor descriptor = FileRequestDescriptor::downloadRequest(info.dcId(), info.getInputFileLocation(), info.size());
    FileOperation *operation = addFileRequest(descriptor, output);
    FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
    privOperation->m_fileInfo = file;
    return operation;
}

FileOperation *FilesApiPrivate::downloadFile(const FileInfo *file, QIODevice *output)
{
    if (!file->isValid()) {
        return PendingOperation::failOperation<FileOperation>
                (QLatin1String("Invalid FileInfo for getFile()"), this);
    }

    const FileInfo::Private *filePriv = FileInfo::Private::get(file);
    const FileRequestDescriptor descriptor = FileRequestDescriptor::downloadRequest(filePriv->dcId(), filePriv->getInputFileLocation(), filePriv->size());
    FileOperation *operation = addFileRequest(descriptor, output);
    FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
    privOperation->m_fileInfo = new FileInfo(*file);
    return operation;
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

FileOperation *FilesApiPrivate::addFileRequest(const FileRequestDescriptor &descriptor, QIODevice *device)
{
    if (descriptor.type() == FileRequestDescriptor::Download) {
        qCDebug(lcFilesApi) << __func__ << descriptor.dcId() << descriptor.inputLocation().tlType;
    } else if (descriptor.type() == FileRequestDescriptor::Upload) {
        qCDebug(lcFilesApi) << __func__ << descriptor.dcId() << descriptor.fileId();
    }

    if (!descriptor.isValid()) {
        qCDebug(lcFilesApi) << __func__ << "Invalid descriptor";
        return PendingOperation::failOperation<FileOperation>
                (QLatin1String("Unable to addFileRequest(): Invalid FileRequestDescriptor"), this);
    }

    FileOperation *operation = new FileOperation(this);
    FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
    privOperation->m_descriptor = descriptor;
    privOperation->ensureDeviceIsSet(device);
    m_fileRequests.enqueue(operation);

    if (!m_currentOperation) {
        processNextRequest();
    }

    return operation;
}

void FilesApiPrivate::dumpCurrentState() const
{
    if (m_currentOperation) {
        qCInfo(lcFilesApi) << "Current operation:" << m_currentOperation;
        const FileOperationPrivate *privOperation = FileOperationPrivate::get(m_currentOperation);
        qCInfo(lcFilesApi) << "  Child:" << privOperation->m_childOperation;
        qCInfo(lcFilesApi) << "  Status:" << privOperation->m_transferStatus;
    } else {
        qCInfo(lcFilesApi) << "No current operation";
    }
    if (m_fileRequests.isEmpty()) {
        qCInfo(lcFilesApi) << "No file requests in queue";
    } else {
        qCInfo(lcFilesApi) << m_fileRequests.count() << "requests in queue";
    }
}

void FilesApiPrivate::processNextRequest()
{
    if (m_fileRequests.isEmpty()) {
        m_currentOperation = nullptr;
        return;
    }

    m_currentOperation = m_fileRequests.dequeue();
    connect(m_currentOperation, &FileOperation::finished,
            this, &FilesApiPrivate::onFileOperationFinished);

    qCDebug(lcFilesApi) << __func__ << "Current operation:" << m_currentOperation;
    FileOperationPrivate *privOperation = FileOperationPrivate::get(m_currentOperation);
    privOperation->prepareForDownload();

    processCurrentRequest();
}

void FilesApiPrivate::processCurrentRequest()
{
    qCDebug(lcFilesApi) << __func__;
    FileOperationPrivate *privOperation = FileOperationPrivate::get(m_currentOperation);
    ConnectOperation *connectionOperation = ensureConnection(privOperation->dcId());
    privOperation->m_childOperation = connectionOperation;

    if (connectionOperation->isFinished()) {
        onConnectOperationFinished(connectionOperation);
    } else {
        connectionOperation->connectToFinished(this, &FilesApiPrivate::onConnectOperationFinished,
                                     connectionOperation);
    }
}

bool FilesApiPrivate::isConnectionNeeded(quint32 dcId) const
{
    if (m_currentOperation) {
        const FileOperationPrivate *privOperation = FileOperationPrivate::get(m_currentOperation);
        if (privOperation->dcId() == dcId) {
            return true;
        }
    }

// Wanted to parallel operations:
//    for (const FileOperation *operation : m_fileRequests) {
//        const FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
//        if (privOperation->dcId() == dcId) {
//            return true;
//        }
//    }

    return false;
}

ConnectOperation *FilesApiPrivate::ensureConnection(quint32 dcId)
{
    ConnectionApiPrivate *privConnectionApi = ConnectionApiPrivate::get(backend()->connectionApi());
    const ConnectionSpec spec(dcId, ConnectionSpec::RequestFlag::MediaOnly);
    return privConnectionApi->connectToExtraDc(spec);
}

void FilesApiPrivate::processFileRequestForConnection(FileOperation *operation, Connection *connection)
{
    FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
    privOperation->m_transferStatus = FileOperationPrivate::TransferStatus::TransferringBytes;
    const FileRequestDescriptor &descriptor = privOperation->m_descriptor;
    UploadRpcLayer::PendingUploadFile *rpcOperation = nullptr;
    rpcOperation = uploadLayer()->getFile(descriptor.inputLocation(), descriptor.offset(), descriptor.chunkSize());
    qCDebug(lcFilesApi) << __func__ << operation << connection->dcOption().id << rpcOperation;
    privOperation->m_childOperation = rpcOperation;
    connection->rpcLayer()->sendRpc(rpcOperation);
    rpcOperation->connectToFinished(this, &FilesApiPrivate::onGetFileResult, operation, rpcOperation);
}

void FilesApiPrivate::onGetFileResult(FileOperation *operation, UploadRpcLayer::PendingUploadFile *rpcOperation)
{
    qCDebug(lcFilesApi) << __func__ << operation;
    TLUploadFile result;
    if (rpcOperation->isFailed()) {
        qCWarning(lcFilesApi) << __func__ << "failed" << rpcOperation->errorDetails();
        if (rpcOperation->errorDetails().contains(Connection::c_statusKey())) {
            // The operation failed due to connection lost
            // Schedule full retry
            if (m_currentOperation == operation) {
                // We can work only with one queue ATM
                QMetaObject::invokeMethod(this, "processCurrentRequest", Qt::QueuedConnection); // Invoke after return
                return;
            } else {
                qCCritical(lcFilesApi) << __func__ << "Unprocessed failed operation" << operation << rpcOperation;
            }
        }

        operation->setFinishedWithError(rpcOperation->errorDetails());
        return;
    }
    rpcOperation->getResult(&result);

    FileOperationPrivate *privOperation = FileOperationPrivate::get(operation);
    static const QVector<TLValue> badTypes = {
        TLValue::StorageFileUnknown,
        TLValue::StorageFilePartial,
    };
    if (result.type.isValid() && !badTypes.contains(result.type.tlType)) {
        // has type!
        const QString typeStr = Utils::mimeTypeByStorageFileType(result.type.tlType);
        if (!typeStr.isEmpty()) {
            FileInfo *fileInfo = privOperation->m_fileInfo;
            FileInfo::Private::get(fileInfo)->setMimeType(typeStr);
        }
    }
    operation->device()->write(result.bytes);

    FileRequestDescriptor &descriptor = privOperation->m_descriptor;
    const quint32 totalBytesDownloaded = descriptor.offset() + result.bytes.size();
    privOperation->m_totalTransferredBytes = totalBytesDownloaded;

#ifdef DEVELOPER_BUILD
    qCDebug(lcFilesApi).nospace() << operation
                                  << " download progress: "
                                  << totalBytesDownloaded << '/' << descriptor.size();
#endif // DEVELOPER_BUILD

    bool finished = false;
    if (descriptor.size()) {
        if (result.bytes.isEmpty()) {
            static const QString text = QLatin1String("Invalid download: zero bytes received");
            operation->setFinishedWithTextError(text);
            qCWarning(lcFilesApi) << __func__ << text;
            return;
        }

        finished = totalBytesDownloaded == descriptor.size();
    } else {
        finished = result.bytes.isEmpty() || (result.bytes.size() % 1024);
    }

    if (finished) {
        descriptor.setSize(totalBytesDownloaded);
    }

    if (finished) {
        privOperation->m_transferStatus = FileOperationPrivate::TransferStatus::Finished;
        privOperation->finalizeDownload();
        operation->setFinished();
        return;
    }

    descriptor.setOffset(totalBytesDownloaded);

    Connection *connection = Connection::fromOperation(rpcOperation);
    processFileRequestForConnection(operation, connection);
}

void FilesApiPrivate::onOperationCanceled(PendingOperation *operation)
{
    // TODO
}

void FilesApiPrivate::onConnectOperationFinished(ConnectOperation *operation)
{
    Connection *connection = operation->connection();
    qCDebug(lcFilesApi) << __func__ << operation << operation->errorDetails() << connection;

    if (!m_currentOperation) {
        return;
    }

    FileOperationPrivate *privOperation = FileOperationPrivate::get(m_currentOperation);
    if (privOperation->m_childOperation != operation) {
        qCWarning(lcFilesApi) << __func__ << "Unexpected connection operation" << operation
                              << "for" << m_currentOperation;
        return;
    }

    if (connection->dcOption().id != privOperation->dcId()) {
        qCWarning(lcFilesApi) << "Invalid operation dcOption";
        return;
    }

    privOperation->m_childOperation = nullptr;
    if (operation->isFailed()) {
        qCDebug(lcFilesApi) << __func__ << m_currentOperation
                            << "failed due to connection" << operation->errorDetails();

        privOperation->m_transferStatus = FileOperationPrivate::TransferStatus::Finished;
        m_currentOperation->setFinishedWithError(operation->errorDetails());
        return;
    }

    privOperation->m_transferStatus = FileOperationPrivate::TransferStatus::WaitingForAuthorization;

    connect(connection, &Connection::statusChanged, this, &FilesApiPrivate::onConnectionStatusChanged, Qt::UniqueConnection);
    processConnectionStatus(connection);
}

void FilesApiPrivate::onFileOperationFinished(PendingOperation *operation)
{
    if (operation != m_currentOperation) {
        return;
    }
    m_currentOperation = nullptr;
    processNextRequest();
}

void FilesApiPrivate::onConnectionStatusChanged()
{
    processConnectionStatus(qobject_cast<Connection *>(sender()));
}

void FilesApiPrivate::processConnectionStatus(Connection *connection)
{
    if (!connection) {
        // Invalid call
        return;
    }

    if (!m_currentOperation) {
        return;
    }

    qCDebug(lcFilesApi) << __func__ << connection << connection->status();

    const bool mediaConnection = connection->dcOption().flags & DcOption::MediaOnly;
    if (!mediaConnection) {
        qCDebug(lcFilesApi) << __func__ << "not media";
        return;
    }
    quint32 dcId = connection->dcOption().id;
    if (!isConnectionNeeded(dcId)) {
        qCDebug(lcFilesApi) << __func__ << "dc not needed";
        return;
    }
    // DC needed.

    switch (connection->status()) {
    case Connection::Status::Signed:
        processFileRequestForConnection(m_currentOperation, connection);
        break;
    case Connection::Status::Disconnected:
        ensureConnection(dcId);
        break;
    default:
        break;
    }
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
