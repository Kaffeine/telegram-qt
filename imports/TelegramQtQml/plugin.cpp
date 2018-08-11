#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QTimer>

#include "../../TelegramQt/CTelegramCore.hpp"
#include "../../TelegramQt/CAppInformation.hpp"

class AccountSecretHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool credentialDataExists READ credentialDataExists NOTIFY credentialDataExistsChanged)
    Q_PROPERTY(QString secretDirectory READ secretDirectory WRITE setSecretDirectory NOTIFY secretDirectoryChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(Format format READ format WRITE setFormat NOTIFY formatChanged)
public:
    enum Format {
        FormatBinary,
        FormatHex
    };
    Q_ENUM(Format)
//    enum CredentialDataState {
//        CredentialDataStateUnknown, // Phone number is not set
//        CredentialDataNotReadable,
//        CredentialDataExists,
//        CredentialDataIsReadOnly,
//    };

    AccountSecretHelper(QObject *parent = nullptr) :
        QObject(parent),
        m_credentialDataExists(false),
        m_format(FormatBinary)
    {
        connect(this, &AccountSecretHelper::phoneNumberChanged, this, &AccountSecretHelper::updateCredentialDataExist, Qt::QueuedConnection);
    }

    bool credentialDataExists() const { return m_credentialDataExists; }
    QString secretDirectory() const { return m_secretDirectory; }
    QString phoneNumber() const { return m_phoneNumber; }
    Format format() const { return m_format; }

public slots:
    void setSecretDirectory(const QString &newDirectory)
    {
        if (m_secretDirectory == newDirectory) {
            return;
        }
        m_secretDirectory = newDirectory;
        emit secretDirectoryChanged(newDirectory);
    }

    void setPhoneNumber(const QString &newPhoneNumber)
    {
        if (m_phoneNumber == newPhoneNumber) {
            return;
        }
        m_phoneNumber = newPhoneNumber;
        emit phoneNumberChanged(newPhoneNumber);
    }

    void setFormat(Format newFormat)
    {
        if (m_format == newFormat) {
            return;
        }
        m_format = newFormat;
        emit formatChanged(newFormat);
    }

    bool saveCredentialsData(const QByteArray &data)
    {
        if (data.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Makes no sense to write empty secret data";
            return false;
        }
        if (m_phoneNumber.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Phone number is empty" << m_phoneNumber;
            return false;
        }

        const QString fileName = m_secretDirectory + QLatin1Char('/') + m_phoneNumber;
        qDebug() << Q_FUNC_INFO << "dest filename:" << fileName;
        QDir().mkpath(m_secretDirectory);
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << Q_FUNC_INFO << "Unable to open file" << fileName;
            return false;
        }

        QByteArray rawData;
        switch (m_format) {
        case FormatBinary:
            rawData = data;
            break;
        case FormatHex:
            rawData = data.toHex();
            break;
        default:
            break;
        }

        file.write(rawData);
        file.waitForBytesWritten(10);

        QTimer::singleShot(0, this, &AccountSecretHelper::updateCredentialDataExist);
        return true;
    }

    bool removeCredentialsData()
    {
        if (m_phoneNumber.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Phone number is empty" << m_phoneNumber;
            return false;
        }

        const QString fileName = m_secretDirectory + QLatin1Char('/') + m_phoneNumber;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite)) {
            qWarning() << Q_FUNC_INFO << "Unable to open file" << fileName;
            return false;
        }

        const auto existsDataSize = file.size();
        while (file.pos() < existsDataSize) {
            auto r = qrand();
            file.write(reinterpret_cast<const char *>(&r), sizeof(r));
        }
        QTimer::singleShot(0, this, &AccountSecretHelper::updateCredentialDataExist);
        return file.remove();
    }

signals:
    void credentialDataExistsChanged(bool exist);
    void secretDirectoryChanged(QString newDirectory);
    void phoneNumberChanged(QString newPhoneNumber);
    void formatChanged(Format newFormat);

protected:
    void setCredentialDataExists(bool exist)
    {
        if (m_credentialDataExists == exist) {
            return;
        }
        m_credentialDataExists = exist;
        emit credentialDataExistsChanged(exist);
    }

    bool isCredentialDataReallyExist() const
    {
        if (m_phoneNumber.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Phone number is empty" << m_phoneNumber;
            return false;
        }

        QString fileName;
        if (m_secretDirectory.isEmpty()) {
            fileName = m_phoneNumber;
        } else {
            fileName = m_secretDirectory + QLatin1Char('/') + m_phoneNumber;
        }
        qDebug() << Q_FUNC_INFO << "Filename:" << fileName;

        // TODO: Check if the file is readable and do something if it is not.
        return QFile::exists(fileName);
    }

    void updateCredentialDataExist()
    {
        const bool exists = isCredentialDataReallyExist();
        qDebug() << Q_FUNC_INFO << exists;
        setCredentialDataExists(exists);
    }

private:
    bool m_credentialDataExists;
    QString m_secretDirectory;
    QString m_phoneNumber;
    Format m_format;

};

class TelegramQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    TelegramQmlPlugin(QObject *parent = nullptr) :
        QQmlExtensionPlugin(parent)
    {
        qRegisterMetaType<AccountSecretHelper::Format>("AccountSecretHelper::Format");
    }

    void registerTypes(const char *uri) override
    {
        Q_ASSERT(QByteArray(uri) == QByteArray("TelegramQt"));
        qmlRegisterUncreatableType<TelegramNamespace>(uri, 1, 0, "TelegramNamespace", tr("The class is a namespace actually"));
        qmlRegisterType<CTelegramCore>(uri, 1, 0, "TelegramCore");
        qmlRegisterType<CAppInformation>(uri, 1, 0, "AppInformation");
        qmlRegisterType<AccountSecretHelper>(uri, 1, 0, "AccountSecretHelper");
    }
};

#include "plugin.moc"
