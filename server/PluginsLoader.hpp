#ifndef TELEGRAM_QT_SERVER_PLUGINS_LOADER_HPP
#define TELEGRAM_QT_SERVER_PLUGINS_LOADER_HPP

#include <QStringList>
#include <QVector>

class AuthProviderPlugin;
class FederalizationPlugin;

namespace Telegram {

namespace Server {

class FederalizationApi;

namespace Authorization {

class Provider;

} // Authorization

class Q_DECL_EXPORT PluginsLoader
{
public:
    static void setPluginsPaths(const QStringList &paths);

    static QVector<FederalizationPlugin *> federalizationPlugins();
    static QVector<AuthProviderPlugin *> authorizationPlugins();

    static QVector<FederalizationApi *> federalizationApis();
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_PLUGINS_LOADER_HPP
