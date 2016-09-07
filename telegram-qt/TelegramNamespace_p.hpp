#ifndef TELEGRAMNAMESPACE_P_HPP
#define TELEGRAMNAMESPACE_P_HPP

#include "TLTypes.hpp"
#include "TelegramNamespace.hpp"

class TelegramNamespace::MessageMediaInfo::Private : public TLMessageMedia
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

class TelegramNamespace::UploadInfo::Private : public TLInputFile
{
public:
    quint32 m_size;
};

class TelegramNamespace::RemoteFile::Private : public TLInputFileLocation
{
public:
    Private() :
        m_size(0),
        m_dcId(0)
    {
    }

    void setInputFileLocation(const TLInputFileLocation &inputFileLocation)
    {
        TLInputFileLocation *thisLocation = this;
        *thisLocation = inputFileLocation;
    }

    bool setFileLocation(const TLFileLocation *fileLocation)
    {
        if (fileLocation->tlType != TLValue::FileLocation) {
            m_dcId = 0;
            return false;
        }
        tlType = TLValue::InputFileLocation;
        volumeId = fileLocation->volumeId;
        localId = fileLocation->localId;
        secret = fileLocation->secret;
        m_dcId = fileLocation->dcId;
        return true;
    }

    quint32 m_size;
    quint32 m_dcId;
};

class TelegramNamespace::PasswordInfo::Private : public TLAccountPassword { };
class TelegramNamespace::UserInfo::Private : public TLUser { };

TelegramNamespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

#endif // TELEGRAMNAMESPACE_P_HPP

