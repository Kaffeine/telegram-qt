#ifndef TELEGRAM_DECLARATIVE_USER_INFO_HPP
#define TELEGRAM_DECLARATIVE_USER_INFO_HPP

#include "DeclarativeClientOperator.hpp"

class CAppInformation;

namespace Telegram {

namespace Client {

class TELEGRAMQT_QML_EXPORT DeclarativeUserInfo : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(quint32 userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
public:
    explicit DeclarativeUserInfo(QObject *parent = nullptr);

    quint32 userId() const { return m_userId; }
    QString displayName() const { return m_displayName; }

public slots:
    void setUserId(quint32 userId);

signals:
    void userIdChanged(quint32 userId);
    void displayNameChanged(const QString &displayName);

protected:
    void setDisplayName(const QString &displayName);
    void updateDisplayName();

    quint32 m_userId = 0;
    QString m_displayName;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_USER_INFO_HPP
