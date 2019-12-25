#ifndef TELEGRAMQT_CLIENT_FILE_OPERATION
#define TELEGRAMQT_CLIENT_FILE_OPERATION

#include "../PendingOperation.hpp"
#include "../TelegramNamespace.hpp"

QT_FORWARD_DECLARE_CLASS(QIODevice)

namespace Telegram {

namespace Client {

class FileOperationPrivate;

class TELEGRAMQT_EXPORT FileOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit FileOperation(QObject *parent = nullptr);

    const FileInfo *fileInfo();
    QIODevice *device() const;

    quint32 bytesTransferred() const;

public slots:
    void cancel();

signals:
    void canceled(FileOperation *operation);

protected:
    Q_DECLARE_PRIVATE_D(d, FileOperation)
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CLIENT_FILE_OPERATION
