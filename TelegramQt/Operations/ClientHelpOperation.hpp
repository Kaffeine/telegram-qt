#ifndef TELEGRAMQT_CLIENT_HELP_OPERATION
#define TELEGRAMQT_CLIENT_HELP_OPERATION

#include "PendingOperation.hpp"
#include "TelegramNamespace.hpp"

namespace Telegram {

class PendingRpcOperation;

namespace Client {

class Backend;
class HelpRpcLayer;

class HelpOperation : public PendingOperation
{
    Q_OBJECT
public:
    explicit HelpOperation(QObject *parent = nullptr);
    void setBackend(Backend *backend);

    using RunMethod = PendingOperation *(HelpOperation::*)();

    void setRunMethod(RunMethod method);

public slots:
    void start() override;

    PendingOperation *requestDcConfig();

Q_SIGNALS:
protected:
    HelpRpcLayer *helpLayer() const;

    Backend *m_backend = nullptr;
    RunMethod m_runMethod = nullptr;

protected:
    // Implementation:
    void onGetDcCondigurationFinished(PendingRpcOperation *operation);
};

} // Client

} // Telegram

#endif // TELEGRAMQT_CLIENT_HELP_OPERATION
