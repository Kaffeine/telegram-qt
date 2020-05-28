#include "FederalizationPlugin.hpp"

#include "XmppFederation.hpp"

namespace Telegram {

namespace Server {

class Q_DECL_EXPORT XmppFederalizationPlugin : public FederalizationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FederalizationInterface_iid)
public:
    XmppFederalizationPlugin(QObject *parent = nullptr)
        : FederalizationPlugin(parent)
    {
        setObjectName("XmppFederalizationPlugin");
    }

    FederalizationApi *create() final
    {
        return new XmppFederalizationApi();
    }
};

} // Server

} // Telegram

#include "XmppPlugin.moc"
