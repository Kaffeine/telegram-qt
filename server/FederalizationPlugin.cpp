#include "FederalizationPlugin.hpp"
#include <QDebug>

FederalizationPlugin::FederalizationPlugin(QObject *parent)
    : QObject(parent)
{
}

FederalizationPlugin::~FederalizationPlugin()
{
    qWarning() << Q_FUNC_INFO << objectName();
}
