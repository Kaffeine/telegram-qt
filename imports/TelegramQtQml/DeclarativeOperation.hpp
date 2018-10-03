#ifndef TELEGRAM_DECLARATIVE_OPERATION_HPP
#define TELEGRAM_DECLARATIVE_OPERATION_HPP

#include "DeclarativeClientOperator.hpp"

#include "../../TelegramQt/TelegramNamespace.hpp"
#include "../../TelegramQt/PendingOperation.hpp"

namespace Telegram {

namespace Client {

class DeclarativeClient;
class DeclarativeSettings;

class DeclarativeOperation : public DeclarativeClientOperator
{
    Q_OBJECT
    Q_PROPERTY(bool succeeded READ isSucceeded NOTIFY succeededChanged)
public:
    explicit DeclarativeOperation(QObject *parent = nullptr);

    bool isSucceeded() const;

public slots:
    void start();

Q_SIGNALS:
    void started();
    void finished(bool succeeded);
    void succeededChanged();
    void failed(const QVariantHash &details);

protected:
    virtual void startEvent();
    void setPendingOperation(PendingOperation *op);
    void onOperationFinished(PendingOperation *operation);

    PendingOperation *m_operation = nullptr;
};

} // Client

} // Telegram

#endif // TELEGRAM_DECLARATIVE_OPERATION_HPP
