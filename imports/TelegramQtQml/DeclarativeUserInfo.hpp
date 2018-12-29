#ifndef TELEGRAM_DECLARATIVE_USER_INFO_HPP
#define TELEGRAM_DECLARATIVE_USER_INFO_HPP

#include "DeclarativeClientOperator.hpp"

class CAppInformation;

namespace Telegram {

namespace Client {

class DeclarativeUserInfo : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(quint32 contactId READ contactId WRITE setContactId NOTIFY contactIdChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
public:
    explicit DeclarativeUserInfo(QObject *parent = nullptr);

    quint32 contactId() const { return m_contactId; }
    QString displayName() const { return m_displayName; }

public slots:
    void setContactId(quint32 contactId);

signals:
    void contactIdChanged(quint32 contactId);
    void displayNameChanged(const QString &displayName);

protected:
    void setDisplayName(const QString &displayName);
    void updateDisplayName();

    quint32 m_contactId = 0;
    QString m_displayName;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_USER_INFO_HPP
