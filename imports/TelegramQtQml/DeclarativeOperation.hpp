#ifndef TELEGRAM_DECLARATIVE_OPERATION_HPP
#define TELEGRAM_DECLARATIVE_OPERATION_HPP

#include <QObject>

#include "../../TelegramQt/TelegramNamespace.hpp"
#include "../../TelegramQt/PendingOperation.hpp"

namespace Telegram {

namespace Client {

class DeclarativeClient;
class DeclarativeSettings;

class DeclarativeOperation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telegram::Client::DeclarativeClient *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(bool succeed READ succeed NOTIFY succeedChanged)
public:
    explicit DeclarativeOperation(QObject *parent = nullptr);

    DeclarativeClient *target() const;
    bool succeed() const;

public slots:
    void start();
    void setTarget(DeclarativeClient *target);

Q_SIGNALS:
    void targetChanged();
    void succeedChanged(bool succeed);

    void started();
    void finished();
    void succeeded();
    void failed(const QVariantHash &details);

protected:
    virtual void startEvent();
    void setPendingOperation(PendingOperation *op);
    void onOperationSucceed(PendingOperation *op);
    void onOperationFailed(PendingOperation *op, const QVariantHash &details);
    void setSucceed(bool succeed);

    DeclarativeClient *m_target;
    bool m_succeed = false;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_OPERATION_HPP
