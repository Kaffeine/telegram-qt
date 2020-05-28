#include "FederalizationPlugin.hpp"
#include <QDebug>

namespace Telegram {

namespace Server {

class Q_DECL_EXPORT DummyFederationPlugin : public FederalizationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FederalizationInterface_iid)
public:
    DummyFederationPlugin(QObject *parent = nullptr)
        : FederalizationPlugin(parent)
    {
        setObjectName("DummyFederationPlugin");
    }

    FederalizationApi *create() final { return nullptr; }
};

} // Server

} // Telegram

#include "DummyFederationPlugin.moc"
