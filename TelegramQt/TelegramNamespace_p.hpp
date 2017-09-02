#ifndef TELEGRAMNAMESPACE_P_HPP
#define TELEGRAMNAMESPACE_P_HPP

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class Telegram::MessageMediaInfo::Private : public TLMessageMedia
{
public:
    Private() :
        m_isUploaded(false),
        m_size(0),
        m_inputFile(0)
    {
    }

    ~Private()
    {
        if (m_inputFile) {
            delete m_inputFile;
        }
    }

    bool m_isUploaded;
    quint32 m_size;
    TLInputFile *m_inputFile;
};

class Telegram::RemoteFile::Private
{
public:
    enum Type {
        InvalidLocation,
        FileLocation,
        EncryptedFileLocation,
        VideoFileLocation,
        AudioFileLocation,
        DocumentFileLocation,
        UploadInputFile,
        UploadInputFileBig,
    };

    Private() :
        m_type(InvalidLocation),
        m_volumeId(0),
        m_localId(0),
        m_secret(0),
        m_dcId(0),
        m_id(0),
        m_accessHash(0),
        m_parts(0),
        m_size(0)
    {
    }

    static const Private *get(const RemoteFile *f) { return f->d; }
    static Private *get(RemoteFile *f) { return f->d; }
    static void set(RemoteFile *f, Private *p) { f->d = p; }

    TLInputFileLocation getInputFileLocation() const;
    bool setInputFileLocation(const TLInputFileLocation *inputFileLocation);

    TLInputFile getInputFile() const;
    bool setInputFile(const TLInputFile *inputFile);

    TLFileLocation getFileLocation() const;
    bool setFileLocation(const TLFileLocation *fileLocation);

    Type m_type;

    // FileLocation:
    quint64 m_volumeId;
    quint32 m_localId;
    quint64 m_secret;
    quint32 m_dcId;

    // InputFileLocation:
//    quint64 m_volumeId;
//    quint32 m_localId;
//    quint64 m_secret;
    quint64 m_id;
    quint64 m_accessHash;

    // InputFile:
//    quint64 m_id;
    quint32 m_parts;
    QString m_name;
    QString m_md5Checksum;

    quint32 m_size;
};

class Telegram::PasswordInfo::Private : public TLAccountPassword { };
class Telegram::UserInfo::Private : public TLUser { };
class Telegram::ChatInfo::Private : public TLChat { };

class Telegram::DialogInfo::Private
{
public:
    Private() :
        muteUntil(0)
    {
    }

    Peer peer;
    quint32 muteUntil;
};

TelegramNamespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

#endif // TELEGRAMNAMESPACE_P_HPP

