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

class TelegramNamespace::RemoteFile::Private
{
public:
    Private() :
        m_inputFileLocation(0),
        m_size(0),
        m_dcId(0)
    {
    }

    Private(const Private &p) :
        m_inputFileLocation(0),
        m_size(p.m_size),
        m_dcId(p.m_dcId)
    {
        setInputFileLocation(p.m_inputFileLocation);
    }

    ~Private()
    {
        if (m_inputFileLocation) {
            delete m_inputFileLocation;
        }
    }

    Private &operator=(const Private &p)
    {
        setInputFileLocation(p.m_inputFileLocation);
        m_size = p.m_size;
        m_dcId = p.m_dcId;

        return *this;
    }

    void setInputFileLocation(const TLInputFileLocation *inputFileLocation)
    {
        if (inputFileLocation) {
            if (!m_inputFileLocation) {
                m_inputFileLocation = new TLInputFileLocation;
            }
            *m_inputFileLocation = *inputFileLocation;
        } else {
            if (m_inputFileLocation) {
                delete m_inputFileLocation;
                m_inputFileLocation = 0;
            }
        }
    }

    bool setFileLocation(const TLFileLocation *fileLocation)
    {
        if (fileLocation->tlType != TLValue::FileLocation) {
            m_dcId = 0;
            return false;
        }
        TLInputFileLocation inputFileLocation;
        inputFileLocation.tlType = TLValue::InputFileLocation;
        inputFileLocation.volumeId = fileLocation->volumeId;
        inputFileLocation.localId = fileLocation->localId;
        inputFileLocation.secret = fileLocation->secret;
        setInputFileLocation(&inputFileLocation);
        m_dcId = fileLocation->dcId;
        return true;
    }

    TLInputFileLocation *m_inputFileLocation;
    quint32 m_size;
    quint32 m_dcId;
};

class TelegramNamespace::PasswordInfo::Private : public TLAccountPassword { };
class TelegramNamespace::UserInfo::Private : public TLUser { };

TelegramNamespace::ContactStatus getApiContactStatus(TLValue status);
quint32 getApiContactLastOnline(const TLUserStatus &status);

#endif // TELEGRAMNAMESPACE_P_HPP

