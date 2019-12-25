#ifndef TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP

#include "PendingOperation_p.hpp"
#include "FileOperation.hpp"
#include "FileRequestDescriptor.hpp"

#include <QVector>

QT_FORWARD_DECLARE_CLASS(QBuffer)

namespace Telegram {

namespace Client {

class FileOperationPrivate : public PendingOperationPrivate
{
    Q_GADGET
public:
    Q_DECLARE_PUBLIC(FileOperation)

    enum class TransferStatus {
        Invalid,
        WaitingForConnection,
        WaitingForAuthorization,
        WaitingForItsTurn,
        TransferringBytes,
        Finished,
    };
    Q_ENUM(TransferStatus)

    explicit FileOperationPrivate(PendingOperation *parent);
    ~FileOperationPrivate() override;

    static FileOperationPrivate *get(FileOperation *parent);

    quint32 dcId() const { return m_descriptor.dcId(); }

    QIODevice *device() const { return m_device; }
    void ensureDeviceIsSet(QIODevice *device = nullptr);
    void prepareForDownload();
    void finalizeDownload();

    FileRequestDescriptor m_descriptor;
    FileInfo *m_fileInfo = nullptr;
    quint32 m_totalTransferredBytes = 0;
    TransferStatus m_transferStatus = TransferStatus::Invalid;
    PendingOperation *m_childOperation = nullptr;

private:
    QIODevice *m_device = nullptr;
    QBuffer *m_ownBuffer = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP
