#ifndef TELEGRAM_ACCOUNT_STORAGE_HPP
#define TELEGRAM_ACCOUNT_STORAGE_HPP

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class AccountStoragePrivate;

class TELEGRAMQT_EXPORT AccountStorage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString accountIdentifier READ accountIdentifier WRITE setAccountIdentifier NOTIFY accountIdentifierChanged)
public:
    explicit AccountStorage(QObject *parent = nullptr);
    ~AccountStorage() override;

    bool hasMinimalDataSet() const;

    QString accountIdentifier() const;
    void setAccountIdentifier(const QString &account);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber) const;

    bool invalidateAuthKey(quint64 authId);

    quint64 authId() const;
    void setAuthId(quint64 id);

    QByteArray authKey() const;
    void setAuthKey(const QByteArray &newAuthKey);

    quint64 sessionId() const;
    void setSessionId(quint64 id);

    quint32 contentRelatedMessagesNumber() const;
    void setSessionData(quint64 id, quint32 contentRelatedMessagesNumber);

    qint32 deltaTime() const;
    void setDeltaTime(const qint32 newDt);

    DcOption dcInfo() const;
    void setDcInfo(const DcOption &newDcInfo);

public slots:
    virtual bool saveData() const { return false; }
    virtual bool loadData() { return false; }

    virtual bool sync();

Q_SIGNALS:
    void synced();
    void accountIdentifierChanged(const QString &accountIdentifier);
    void accountInvalidated(const QString &accountIdentifier);

protected:
    AccountStorage(AccountStoragePrivate *dd, QObject *parent = nullptr);
    AccountStoragePrivate *d;
};

class FileAccountStoragePrivate;
class TELEGRAMQT_EXPORT FileAccountStorage : public AccountStorage
{
    Q_OBJECT
    Q_DECLARE_PRIVATE_D(d, FileAccountStorage)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
public:
    explicit FileAccountStorage(QObject *parent = nullptr);

    QString fileName() const;
    QString getLocalFileName() const;
    Q_INVOKABLE bool fileExists() const;

public slots:
    bool saveData() const override;
    bool loadData() override;
    bool clearData();

    bool sync() override;

    void setFileName(const QString &fileName);

Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void fileExistsChanged(bool exists);

};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_ACCOUNT_STORAGE_HPP
