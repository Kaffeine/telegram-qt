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
    Private() :
        m_inputFileLocation(0),
        m_inputFile(0),
        m_size(0),
        m_dcId(0),
        m_type(RemoteFile::Undefined)
    {
    }

    Private(const Private &p) :
        m_inputFileLocation(0),
        m_inputFile(0),
        m_size(p.m_size),
        m_dcId(p.m_dcId),
        m_type(RemoteFile::Undefined)
    {
        setInputFileLocation(p.m_inputFileLocation);
        setInputFile(p.m_inputFile);
    }

    ~Private()
    {
        if (m_inputFileLocation) {
            delete m_inputFileLocation;
        }
        if (m_inputFile) {
            delete m_inputFile;
        }
    }

    Private &operator=(const Private &p)
    {
        setInputFileLocation(p.m_inputFileLocation);
        setInputFile(p.m_inputFile);
        m_size = p.m_size;
        m_dcId = p.m_dcId;
        m_type = p.m_type;

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

    void setInputFile(const TLInputFile *inputFile)
    {
        if (inputFile) {
            if (!m_inputFile) {
                m_inputFile = new TLInputFile;
            }
            *m_inputFile = *inputFile;
        } else {
            if (m_inputFile) {
                delete m_inputFile;
                m_inputFile = 0;
            }
        }
    }

    bool setFileLocation(const TLFileLocation *fileLocation)
    {
        if (fileLocation->tlType != TLValue::FileLocation) {
            m_dcId = 0;
            m_type = RemoteFile::Undefined;
            return false;
        }
        TLInputFileLocation inputFileLocation;
        inputFileLocation.tlType = TLValue::InputFileLocation;
        inputFileLocation.volumeId = fileLocation->volumeId;
        inputFileLocation.localId = fileLocation->localId;
        inputFileLocation.secret = fileLocation->secret;
        setInputFileLocation(&inputFileLocation);
        m_dcId = fileLocation->dcId;
        m_type = RemoteFile::Download;
        return true;
    }

    TLInputFileLocation *m_inputFileLocation;
    TLInputFile *m_inputFile;
    quint32 m_size;
    quint32 m_dcId;
    RemoteFile::Type m_type;
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

