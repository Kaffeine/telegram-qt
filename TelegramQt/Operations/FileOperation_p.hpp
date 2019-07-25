#ifndef TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP
#define TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP

#include "PendingOperation_p.hpp"
#include "FileOperation.hpp"
#include "FileRequestDescriptor.hpp"

#include <QVector>

namespace Telegram {

namespace Client {

class FileOperationPrivate : public PendingOperationPrivate
{
public:
    Q_DECLARE_PUBLIC(FileOperation)

    explicit FileOperationPrivate(PendingOperation *parent);
    ~FileOperationPrivate() override;

    static FileOperationPrivate *get(FileOperation *parent);

    quint32 dcId() const { return m_descriptor.dcId(); }

    FileRequestDescriptor m_descriptor;
    QIODevice *m_device = nullptr;
    FileInfo *m_fileInfo = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_FILE_OPERATION_PRIVATE_HPP
