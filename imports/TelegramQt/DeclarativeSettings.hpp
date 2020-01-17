#ifndef TELEGRAM_DECLARATIVE_SETTINGS_HPP
#define TELEGRAM_DECLARATIVE_SETTINGS_HPP

#include "telegramqt_qml_global.h"

#include "ClientSettings.hpp"

#include <QQmlListProperty>
#include <qqml.h>
#include <QVector>

namespace Telegram {

namespace Client {

class DeclarativeRsaKey;

class TELEGRAMQT_QML_EXPORT DeclarativeServerOption : public QObject, public DcOption
{
    Q_OBJECT
    Q_PROPERTY(QString address MEMBER address NOTIFY addressChanged)
    Q_PROPERTY(quint32 port MEMBER port NOTIFY portChanged)
public:
    explicit DeclarativeServerOption(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

Q_SIGNALS:
    void addressChanged();
    void portChanged();

private:
    Q_DISABLE_COPY(DeclarativeServerOption)
};

class TELEGRAMQT_QML_EXPORT DeclarativeProxySettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
public:
    explicit DeclarativeProxySettings(QObject *parent = nullptr);

    quint16 port() const { return m_port; }
    QString address() const { return m_address; }
    QString user() const { return m_user; }
    QString password() const { return m_password; }

public slots:
    void setPort(quint16 port);
    void setAddress(const QString &address);
    void setUser(const QString &user);
    void setPassword(const QString &password);

signals:
    void portChanged(quint16 newPort);
    void addressChanged(const QString &addressChanged);
    void userChanged(const QString &userChanged);
    void passwordChanged(const QString &passwordChanged);

protected:
    quint16 m_port = 0;
    QString m_address;
    QString m_user;
    QString m_password;
};

class TELEGRAMQT_QML_EXPORT DeclarativeSettings : public Settings // TODO: QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Telegram::Client::DeclarativeServerOption> serverOptions
               READ serverOptions NOTIFY serverOptionsChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeRsaKey *serverKey READ serverKey WRITE setServerKey NOTIFY serverKeyChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeProxySettings *proxy READ proxy CONSTANT)
public:
    explicit DeclarativeSettings(QObject *parent = nullptr);
    QQmlListProperty<DeclarativeServerOption> serverOptions();

    DeclarativeRsaKey *serverKey() const { return m_serverKey; }
    DeclarativeProxySettings *proxy() const { return m_proxySettings; }

    void appendServerOption(DeclarativeServerOption *option);
    int serverOptionCount() const { return m_options.count(); }
    DeclarativeServerOption *getServerOption(int index) const { return m_options.at(index); }
    void clearServerOptions();

    // TODO: Protect
    void syncSettings();
public slots:
    void setServerKey(DeclarativeRsaKey *serverKey);

signals:
    void serverKeyChanged();
    void serverOptionsChanged();

protected:
    static void appendServerOption(QQmlListProperty<DeclarativeServerOption> *list, DeclarativeServerOption *option);
    static int serverOptionCount(QQmlListProperty<DeclarativeServerOption> *list);
    static DeclarativeServerOption *getServerOption(QQmlListProperty<DeclarativeServerOption> *list, int index);
    static void clearServerOptions(QQmlListProperty<DeclarativeServerOption> *list);

    QVector<DeclarativeServerOption*> m_options;
    DeclarativeRsaKey *m_serverKey = nullptr;
    DeclarativeProxySettings *m_proxySettings = nullptr;

private:
    Q_DISABLE_COPY(DeclarativeSettings)
};

} // Client

} // Telegram

QML_DECLARE_TYPE(Telegram::Client::DeclarativeServerOption)
//QML_DECLARE_TYPE(Telegram::Client::DeclarativeSettings)

#endif // TELEGRAM_DECLARATIVE_SETTINGS_HPP
