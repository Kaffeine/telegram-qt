#ifndef TELEGRAM_ACCOUNT_STORAGE_HPP
#define TELEGRAM_ACCOUNT_STORAGE_HPP

#include "TelegramNamespace.hpp"

namespace Telegram {

namespace Client {

class AccountStoragePrivate;

class AccountStorage : public QObject
{
    Q_OBJECT
public:
    explicit AccountStorage(QObject *parent = nullptr);

    bool hasMinimalDataSet() const;

    QString accountIdentifier() const;
    void setAccountIdentifier(const QString &account);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber) const;

    quint64 authId() const;
    void setAuthId(quint64 id);

    QByteArray authKey() const;
    void setAuthKey(const QByteArray &newAuthKey);

    qint32 deltaTime() const;
    void setDeltaTime(const qint32 newDt);

    DcOption dcInfo() const;
    void setDcInfo(const DcOption &newDcInfo);

public slots:
    virtual bool saveData() const { return false; }
    virtual bool loadData() { return false; }

protected:
    AccountStorage(AccountStoragePrivate *dd, QObject *parent = nullptr);
    AccountStoragePrivate *d;
};

class FileAccountStorage : public AccountStorage
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
public:
    explicit FileAccountStorage(QObject *parent = nullptr);

    QString fileName() const;

public slots:
    bool saveData() const override;
    bool loadData() override;

    void setFileName(const QString &fileName);

signals:
    void fileNameChanged(const QString &fileName);

};

//class FileAccountStorage : public AccountStorage
//{
//    Q_OBJECT
//    Q_PROPERTY(QString directory READ directory WRITE setDirectory NOTIFY directoryChanged)
//    Q_PROPERTY(QStringList accounts READ accounts NOTIFY accountsChanged)
//public:

//};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAM_ACCOUNT_STORAGE_HPP
