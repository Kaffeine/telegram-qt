#ifndef TELEGRAM_DECLARATIVE_SETTINGS_HPP
#define TELEGRAM_DECLARATIVE_SETTINGS_HPP

#include <qqml.h>

class CTelegramCore;

namespace Telegram {

namespace Client {

class DeclarativeProxySettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
public:
    explicit DeclarativeProxySettings(QObject *parent = nullptr);

    quint16 port() const { return m_port; }
    QString address() const { return m_address; }

public slots:
    void setPort(quint16 port);
    void setAddress(const QString &address);

signals:
    void portChanged(quint16 newPort);
    void addressChanged(const QString &addressChanged);

protected:
    quint16 m_port = 0;
    QString m_address;
};

class DeclarativeSettings : public QObject // TODO: QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(CTelegramCore *client READ client WRITE setClient NOTIFY clientChanged)
    Q_PROPERTY(Telegram::Client::DeclarativeProxySettings *proxy READ proxy CONSTANT)
public:
    explicit DeclarativeSettings(QObject *parent = nullptr);

    CTelegramCore *client() const { return m_client; }
    DeclarativeProxySettings *proxy() const { return m_proxySettings; }

    // TODO: Protect
    void syncSettings();

public slots:
    void setClient(CTelegramCore *client);

signals:
    void clientChanged();

protected:
    DeclarativeProxySettings *m_proxySettings = nullptr;
    CTelegramCore *m_client = nullptr;

private:
    Q_DISABLE_COPY(DeclarativeSettings)
};

} // Client

} // Telegram

QML_DECLARE_TYPE(Telegram::Client::DeclarativeSettings)

#endif // TELEGRAM_DECLARATIVE_SETTINGS_HPP
