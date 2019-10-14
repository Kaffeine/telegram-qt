#include "AccountStorage.hpp"

#include "Debug_p.hpp"
#include "LegacySecretReader.hpp"
#include "RawStream.hpp"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLoggingCategory>
#include <QUrl>

Q_LOGGING_CATEGORY(c_clientAccountStorage, "telegram.client.account", QtWarningMsg)

namespace Telegram {

namespace Client {

class AccountStoragePrivate
{
    Q_DECLARE_PUBLIC(AccountStorage)
public:
    explicit AccountStoragePrivate(AccountStorage *q) :
        q_ptr(q)
    {
    }

    AccountStorage *q_ptr = nullptr;
    QString m_accountIdentifier;
    QString m_phoneNumber;
    QByteArray m_authKey;
    quint64 m_authId = 0;
    quint64 m_sessionId = 0;
    quint32 m_contentRelatedMessagesNumber = 0;
    qint32 m_deltaTime = 0;
    DcOption m_dcInfo;

    static constexpr quint32 c_formatVersion = 1;
    static const QByteArray c_signature;
};

const QByteArray AccountStoragePrivate::c_signature = "TelegramQt_account";

/*!
    \class Telegram::Client::AccountStorage
    \brief The AccountStorage class provides a basic interface for account
           data management
    \inmodule TelegramQt
    \ingroup Client

    When subclassing AccountStorage you need to save at least authKey and
    dcInfo. It is highly recommended to also store deltaTime and authId.
    On authentication succeeded the storage can get phone number and some
    extra data from server to setup data storage and decrypt local cache.

    \sa DataStorage
*/

AccountStorage::AccountStorage(QObject *parent) :
    AccountStorage(new AccountStoragePrivate(this), parent)
{
}

AccountStorage::~AccountStorage()
{
    delete d;
}

bool AccountStorage::hasMinimalDataSet() const
{
    return !d->m_dcInfo.address.isEmpty() && !d->m_authKey.isEmpty() && sessionId();
}

QString AccountStorage::accountIdentifier() const
{
    return d->m_accountIdentifier;
}

void AccountStorage::setAccountIdentifier(const QString &account)
{
    if (d->m_accountIdentifier == account) {
        return;
    }
    d->m_accountIdentifier = account;
    emit accountIdentifierChanged(account);
}

QString AccountStorage::phoneNumber() const
{
    return d->m_phoneNumber;
}

void AccountStorage::setPhoneNumber(const QString &phoneNumber) const
{
    d->m_phoneNumber = phoneNumber;
}

bool AccountStorage::invalidateAuthKey(quint64 authId)
{
    const bool hasKey = d->m_authId == authId;
    qCWarning(c_clientAccountStorage) << CALL_INFO << "Invalidate auth key"
                                      << hex << showbase << authId
                                      << "(" << hasKey << ")";
    if (!hasKey) {
        return false;
    }
    d->m_authId = 0;
    d->m_authKey.clear();
    d->m_sessionId = 0;
    d->m_contentRelatedMessagesNumber = 0;
    emit accountInvalidated(d->m_accountIdentifier);
    return true;
}

quint64 AccountStorage::authId() const
{
    return d->m_authId;
}

void AccountStorage::setAuthId(quint64 id)
{
    d->m_authId = id;
}

QByteArray AccountStorage::authKey() const
{
    return d->m_authKey;
}

void AccountStorage::setAuthKey(const QByteArray &newAuthKey)
{
    d->m_authKey = newAuthKey;
}

quint64 AccountStorage::sessionId() const
{
    return d->m_sessionId;
}

void AccountStorage::setSessionId(quint64 id)
{
    d->m_sessionId = id;
}

quint32 AccountStorage::contentRelatedMessagesNumber() const
{
    return d->m_contentRelatedMessagesNumber;
}

void AccountStorage::setSessionData(quint64 id, quint32 contentRelatedMessagesNumber)
{
    d->m_sessionId = id;
    d->m_contentRelatedMessagesNumber = contentRelatedMessagesNumber;
}

qint32 AccountStorage::deltaTime() const
{
    return d->m_deltaTime;
}

void AccountStorage::setDeltaTime(const qint32 newDt)
{
    d->m_deltaTime = newDt;
}

DcOption AccountStorage::dcInfo() const
{
    return d->m_dcInfo;
}

void AccountStorage::setDcInfo(const DcOption &newDcInfo)
{
    d->m_dcInfo = newDcInfo;
}

bool AccountStorage::sync()
{
    emit synced();
    return true;
}

AccountStorage::AccountStorage(AccountStoragePrivate *dd, QObject *parent) :
    QObject(parent),
    d(dd)
{
}

class FileAccountStoragePrivate : public AccountStoragePrivate
{
    Q_DECLARE_PUBLIC(FileAccountStorage)
public:
    explicit FileAccountStoragePrivate(FileAccountStorage *q) :
        AccountStoragePrivate(q)
    {
    }

    QString m_fileName;
};

FileAccountStorage::FileAccountStorage(QObject *parent) :
    AccountStorage(new FileAccountStoragePrivate(this), parent)
{
}

QString FileAccountStorage::fileName() const
{
    Q_D(const FileAccountStorage);
    return d->m_fileName;
}

QString FileAccountStorage::getLocalFileName() const
{
    Q_D(const FileAccountStorage);
    if (d->m_fileName.isEmpty()) {
        return QString();
    }
    const QUrl fileUrl = QUrl::fromUserInput(d->m_fileName);
    if (!fileUrl.isLocalFile()) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "The file is not a local file"
                                          << d->m_fileName;
        return QString();
    }
    return fileUrl.toLocalFile();
}

bool FileAccountStorage::fileExists() const
{
    QFileInfo file(getLocalFileName());
    return file.isReadable();
}

bool FileAccountStorage::saveData() const
{
    Q_D(const FileAccountStorage);
    const QString localFileName = getLocalFileName();
    if (localFileName.isEmpty()) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Invalid fileName"
                                          << d->m_fileName;
        return false;
    }
    const QFileInfo fileInfo(localFileName);
    if (!QDir().mkpath(fileInfo.absolutePath())) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Unable to create output directory"
                                          << fileInfo.absolutePath();
        return false;
    }

    QFile file(localFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Unable to open file" << fileName();
        return false;
    }
    RawStreamEx stream(&file);
    stream.writeBytes(AccountStoragePrivate::c_signature);
    stream << AccountStoragePrivate::c_formatVersion;
    stream << d->m_deltaTime;
    stream << d->m_dcInfo.id;
    stream << d->m_dcInfo.address.toLatin1();
    stream << d->m_dcInfo.port;
    stream << d->m_authKey;
    stream << d->m_authId;
    stream << d->m_sessionId;
    stream << d->m_contentRelatedMessagesNumber;
    qCDebug(c_clientAccountStorage) << CALL_INFO
                                    << "Saved key"
                                    << QString::number(authId(), 0x10);
    return true;
}

bool FileAccountStorage::loadData()
{
    Q_D(FileAccountStorage);
    const QString localFileName = getLocalFileName();
    if (localFileName.isEmpty()) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Invalid fileName" << d->m_fileName;
        return false;
    }
    QFile file(localFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Unable to open file" << d->m_fileName;
        return false;
    }
    RawStreamEx stream(&file);
    QByteArray signature = stream.readBytes(AccountStoragePrivate::c_signature.size());
    if (signature != AccountStoragePrivate::c_signature) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "The file is not a Telegram secret file"
                                             " (unknown signature)";
        return false;
    }
    quint32 format = 0;
    stream >> format;
    if (format > AccountStoragePrivate::c_formatVersion) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "The file format version is unknown"
                                          << format;
        return false;
    }
    stream >> d->m_deltaTime;
    stream >> d->m_dcInfo.id;
    QByteArray address;
    stream >> address;
    d->m_dcInfo.address = QString::fromLatin1(address);
    stream >> d->m_dcInfo.port;
    stream >> d->m_authKey;
    stream >> d->m_authId;
    stream >> d->m_sessionId;
    stream >> d->m_contentRelatedMessagesNumber;

    qCDebug(c_clientAccountStorage) << CALL_INFO
                                    << "Loaded key" << QString::number(authId(), 0x10);
    return !stream.error();
}

bool FileAccountStorage::clearData()
{
    Q_D(const FileAccountStorage);
    if (d->m_fileName.isEmpty()) {
        qCDebug(c_clientAccountStorage) << CALL_INFO
                                        << "File name is not set";
        return false;
    }
    const QString localFileName = getLocalFileName();
    if (localFileName.isEmpty()) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Invalid fileName" << d->m_fileName;
        return false;
    }
    const QFileInfo fileInfo(localFileName);
    if (!fileInfo.exists()) {
        qCDebug(c_clientAccountStorage) << CALL_INFO
                                        << "The file does not exist";
        // Not an error
        return true;
    }

    if (!QFile::remove(fileInfo.absoluteFilePath())) {
        qCWarning(c_clientAccountStorage) << CALL_INFO
                                          << "Unable to delete file"
                                          << fileInfo.absoluteFilePath();
        return false;
    }
    return true;
}

bool FileAccountStorage::sync()
{
    saveData();
    return AccountStorage::sync();
}

void FileAccountStorage::setFileName(const QString &fileName)
{
    Q_D(FileAccountStorage);
    if (d->m_fileName == fileName) {
        return;
    }
    d->m_fileName = fileName;
    emit fileNameChanged(fileName);
}

} // Client

} // Telegram
