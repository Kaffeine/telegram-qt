#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QTimer>

#include "../../TelegramQt/AccountStorage.hpp"
#include "../../TelegramQt/Client.hpp"
#include "../../TelegramQt/CTelegramCore.hpp"
#include "../../TelegramQt/CAppInformation.hpp"

#include "DeclarativeClient.hpp"
#include "DeclarativeAuthOperation.hpp"
#include "DeclarativeSettings.hpp"

class AccountSecretHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool accountDataExists READ accountDataExists NOTIFY credentialDataExistsChanged)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory NOTIFY directoryChanged)
    Q_PROPERTY(QString account READ account WRITE setAccount NOTIFY accountChanged)
    Q_PROPERTY(QStringList accounts READ accounts NOTIFY accountsChanged)
    Q_PROPERTY(Format format READ format WRITE setFormat NOTIFY formatChanged)
public:
    enum Format {
        FormatBinary,
        FormatHex
    };
    Q_ENUM(Format)

    AccountSecretHelper(QObject *parent = nullptr) :
        QObject(parent),
        m_credentialDataExists(false),
        m_format(FormatBinary)
    {
        connect(this, &AccountSecretHelper::directoryChanged, this, &AccountSecretHelper::updateAccounts);
        connect(this, &AccountSecretHelper::accountChanged, this, &AccountSecretHelper::updateCredentialDataExist, Qt::QueuedConnection);
    }

    bool accountDataExists() const { return m_credentialDataExists; }
    QString directory() const { return m_directory; }
    QString account() const { return m_accountIdentifier; }
    QStringList accounts() const { return m_accounts; }
    Format format() const { return m_format; }

public slots:
    void setDirectory(const QString &newDirectory)
    {
        if (m_directory == newDirectory) {
            return;
        }
        m_directory = newDirectory;
        emit directoryChanged(newDirectory);
    }

    void setAccount(const QString &newAccount)
    {
        if (m_accountIdentifier == newAccount) {
            return;
        }
        m_accountIdentifier = newAccount;
        emit accountChanged(newAccount);
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
        if (m_accountIdentifier.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Phone number is empty" << m_accountIdentifier;
            return false;
        }

        const QString fileName = m_directory + QLatin1Char('/') + m_accountIdentifier;
        qDebug() << Q_FUNC_INFO << "dest filename:" << fileName;
        QDir().mkpath(m_directory);
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
        if (m_accountIdentifier.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "Phone number is empty" << m_accountIdentifier;
            return false;
        }

        const QString fileName = m_directory + QLatin1Char('/') + m_accountIdentifier;
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
    void directoryChanged(QString newDirectory);
    void accountChanged(QString account);
    void accountsChanged(QStringList accounts);
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
        if (m_accountIdentifier.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Account identifier is empty" << m_accountIdentifier;
            return false;
        }

        QString fileName;
        if (!m_directory.isEmpty()) {
            fileName = m_directory + QLatin1Char('/');
        }
        fileName += m_accountIdentifier;
        return QFileInfo::exists(fileName);
    }

    void updateCredentialDataExist()
    {
        const bool exists = isCredentialDataReallyExist();
        qDebug() << Q_FUNC_INFO << exists;
        setCredentialDataExists(exists);
    }

    void updateAccounts()
    {
        const QUrl u(m_directory);
        const QDir d(u.toLocalFile());
        setAccounts(d.entryList(QDir::Files, QDir::Time));
    }

    void setAccounts(const QStringList &accounts)
    {
        if (m_accounts == accounts) {
            return;
        }
        m_accounts = accounts;
        emit accountsChanged(accounts);
    }

private:
    bool m_credentialDataExists;
    QString m_directory;
    QString m_accountIdentifier;
    QStringList m_accounts;
    Format m_format;
};

class MessageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
public:
    explicit MessageModel(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

    enum MessageType {
        MessageTypeText,
        MessageTypePhoto,
        MessageTypeAudio,
        MessageTypeVideo,
        MessageTypeContact,
        MessageTypeDocument,
        MessageTypeGeo,
        MessageTypeWebPage,
        MessageTypeNewDay,
        MessageTypeServiceAction,
    };
    Q_ENUM(MessageType)

    Telegram::Peer peer() const { return m_peer; }

public slots:
    void setPeer(const Telegram::Peer peer)
    {
        if (m_peer == peer) {
            return;
        }
        m_peer = peer;
        emit peerChanged(peer);
    }

signals:
    void peerChanged(Telegram::Peer peer);

protected:
    Telegram::Peer m_peer;
};

class MessageSender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
//    Q_PROPERTY(Telegram::Client::DeclarativeClient *target READ target WRITE setTarget NOTIFY targetChanged)
//    Q_PROPERTY(Telegram::MessageReference messageRef)
public:
    explicit MessageSender(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

    Telegram::Peer peer() const { return m_peer; }
    void setPeer(const Telegram::Peer peer)
    {
        if (m_peer == peer) {
            return;
        }
        m_peer = peer;
        // TODO: Monitor the peer dialog draft changed signal
        emit peerChanged(peer);
    }

public slots:
    void setText(const QString &text)
    {
        m_text = text;
    }
    void setGeoPoint(double latitude, double longitude)
    {
        qWarning() << Q_FUNC_INFO << latitude << longitude;
    }
    void setContact()
    {

    }
    void setMedia()
    {

    }
    void setWebUrl()
    {

    }
    void setSticker()
    {

    }

    void sendMessage()
    {
        emit messageSent(m_text, m_peer);
    }

signals:
    void peerChanged(Telegram::Peer peer);
    void messageSent(const QString &message, const Telegram::Peer peer);
//    void draftChanged(const QString &message, const Telegram::Peer peer);

protected:
    Telegram::Peer m_peer;
    QString m_text;
};

static QObject *telegram_namespace_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    TelegramNamespace *ns = new TelegramNamespace;
    return ns;
}

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
        TelegramNamespace::registerTypes();
        qmlRegisterSingletonType<TelegramNamespace>(uri, 1, 0, "Namespace", &telegram_namespace_provider);
        qmlRegisterType<CTelegramCore>(uri, 1, 0, "TelegramCore");
        qmlRegisterType<CAppInformation>(uri, 1, 0, "AppInformation");
        qmlRegisterType<AccountSecretHelper>(uri, 1, 0, "AccountSecretHelper");
        qmlRegisterType<Telegram::Client::DeclarativeAuthOperation>(uri, 1, 0, "AuthOperation");
        qmlRegisterType<Telegram::Client::DeclarativeClient>(uri, 1, 0, "Client");
        qmlRegisterType<Telegram::Client::DeclarativeServerOption>(uri, 1, 0, "ServerOption");
        qmlRegisterType<Telegram::Client::DeclarativeProxySettings>(uri, 1, 0, "ProxySettings");
        qmlRegisterType<Telegram::Client::DeclarativeSettings>(uri, 1, 0, "Settings");
        qmlRegisterType<Telegram::Client::DeclarativeRsaKey>(uri, 1, 0, "RsaKey");
        qmlRegisterUncreatableType<Telegram::Client::AccountStorage>(uri, 1, 0, "AccountStorage", QStringLiteral("AccountStorage is an abstract type"));
        qmlRegisterType<Telegram::Client::FileAccountStorage>(uri, 1, 0, "FileAccountStorage");
        qmlRegisterType<MessageModel>(uri, 1, 0, "MessageModel");
        qmlRegisterType<MessageSender>(uri, 1, 0, "MessageSender");
    }
};

#include "plugin.moc"
