#ifndef FILETRANSFERMANAGER_HPP
#define FILETRANSFERMANAGER_HPP

#include <QObject>
#include <QHash>

#include <TelegramQt/TelegramNamespace>

class CTelegramCore;
class CFileManager;

struct FileInfo
{
    FileInfo() :
        m_size(0),
        m_complete(false)
    {
    }

    FileInfo(const FileInfo &fileInfo) :
        FileInfo()
    {
        m_data = fileInfo.m_data;
        m_mimeType = fileInfo.m_mimeType;
        m_size= fileInfo.m_size;
        m_complete = fileInfo.m_complete;
    }

    bool isComplete() const { return m_complete; }
    QByteArray data() const { return m_data; }
    QString mimeType() const { return m_mimeType; }
    int size() const { return m_size; }

    // FileManager interface:
    void setMimeType(const QString &type);
    void setSize(int newSize)
    {
        m_size = newSize;
    }

    void addData(const QByteArray &newData);
    void completeDownload(const Telegram::RemoteFile &result);

private:
    QByteArray m_data;
    QString m_mimeType;
    int m_size;
    bool m_complete;

};

class CFileManager : public QObject
{
    Q_OBJECT
public:
    explicit CFileManager(CTelegramCore *backend, QObject *parent = nullptr);

    QString requestFile(const Telegram::RemoteFile &file);
    QString requestPeerPicture(const Telegram::Peer &peer, Telegram::PeerPictureSize size = Telegram::PeerPictureSize::Small);

    const FileInfo *getFileInfo(const QString &uniqueId);
    QByteArray getData(const QString &uniqueId) const;
    bool getPeerPictureFileInfo(const Telegram::Peer &peer, Telegram::RemoteFile *file, Telegram::PeerPictureSize size = Telegram::PeerPictureSize::Small) const;

signals:
    void requestComplete(const QString &uniqueId);

protected slots:
    void onFilePartReceived(quint32 requestId, const QByteArray &data, const QString &mimeType, quint32 offset, quint32 totalSize);
    void onFileRequestFinished(quint32 requestId, const Telegram::RemoteFile &requestResult);

protected:
    QString unqueuePendingRequest();

    CTelegramCore *m_backend;
    QHash<QString,FileInfo> m_files; // UniqueId to file info
    QHash<quint32,QString> m_requestToStringId; // Request number to UniqueId

    QHash<QString,Telegram::RemoteFile> m_pendingRequests;

};

#endif // FILETRANSFERMANAGER_HPP
