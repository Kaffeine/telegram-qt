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
    Q_PROPERTY(bool succeeded READ isSucceeded NOTIFY succeededChanged)
public:
    explicit DeclarativeOperation(QObject *parent = nullptr);

    DeclarativeClient *target() const;
    bool isSucceeded() const;

public slots:
    void start();
    void setTarget(DeclarativeClient *target);

Q_SIGNALS:
    void targetChanged();

    void started();
    void finished(bool succeeded);
    void succeededChanged();
    void failed(const QVariantHash &details);

protected:
    virtual void startEvent();
    void setPendingOperation(PendingOperation *op);
    void onOperationFinished(PendingOperation *operation);

    DeclarativeClient *m_target = nullptr;
    PendingOperation *m_operation = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_OPERATION_HPP
