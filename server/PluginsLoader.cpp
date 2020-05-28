#include "PluginsLoader.hpp"

#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QtPlugin>

#include "AuthorizationProviderPlugin.hpp"
#include "FederalizationPlugin.hpp"

#include <QPluginLoader>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcConnectionCategory, "telegram.server.pluginsLoader", QtInfoMsg)

// Include the generated file with Q_IMPORT_PLUGIN declarations
#include "PluginsLoader_StaticList.cpp"

namespace Telegram {

namespace Server {

static QStringList PluginPaths;

void PluginsLoader::setPluginsPaths(const QStringList &paths)
{
    PluginPaths = paths;
}

QVector<FederalizationPlugin *> PluginsLoader::federalizationPlugins()
{
    QVector<FederalizationPlugin *> plugins;
    const QObjectList staticInstances = QPluginLoader::staticInstances();
    QObjectList dynamicInstances;
    for (const QString &path : PluginPaths) {
        QDir pluginsDir(path);
        const QStringList pluginFiles = pluginsDir.entryList(QDir::Files);
        for (const QString &fileName : pluginFiles) {
            QString filePath = pluginsDir.absoluteFilePath(fileName);
            QPluginLoader loader(filePath);
            QObject *plugin = loader.instance();
            if (plugin) {
                dynamicInstances << plugin;
            } else {
                qCWarning(lcConnectionCategory) << loader.errorString();
            }
        }
    }

    for (QObject *plugin : staticInstances) {
        FederalizationPlugin *federalization = qobject_cast<FederalizationPlugin *>(plugin);
        if (federalization) {
            qCInfo(lcConnectionCategory) << "Add static FederalizationPlugin" << plugin;
            plugins << federalization;
        }
    }
    for (QObject *plugin : dynamicInstances) {
        // Note: qobject_cast doesn't work as long as TelegramServer library is static, because
        //       FederalizationPlugin instance from every plugin has its own static meta object
        //       address, which is different from the one linked into the server itself.
        FederalizationPlugin *federalization = qobject_cast<FederalizationPlugin *>(plugin);
        if (federalization) {
            qCInfo(lcConnectionCategory) << "Add dynamic FederalizationPlugin" << plugin;
            plugins << federalization;
        }
    }

    return plugins;
}

QVector<AuthProviderPlugin *> PluginsLoader::authorizationPlugins()
{
    return { };
}

QVector<FederalizationApi *> PluginsLoader::federalizationApis()
{
    QVector<FederalizationApi *> apis;
    const QVector<FederalizationPlugin *> plugins = federalizationPlugins();
    for (FederalizationPlugin *plugin : plugins) {
        FederalizationApi *api = plugin->create();
        if (!api) {
            continue;
        }
        apis << api;
    }

    return apis;
}

} // Server namespace

} // Telegram namespace
