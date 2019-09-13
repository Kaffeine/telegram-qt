/*
   Copyright (C) 2019 Alexey Minnekhanov <alexey.min@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "TelegramServerConfig.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcServerConfig, "telegram.server.config", QtDebugMsg)

namespace Telegram {

namespace Server {

namespace ConfigKey {

static const QLatin1String c_privateKeyFile = QLatin1String("privateKeyFile");
static const QLatin1String c_serverConfiguration = QLatin1String("serverConfiguration");
static const QLatin1String c_testMode = QLatin1String("testMode");
static const QLatin1String c_dcOptions = QLatin1String("dcOptions");
static const QLatin1String c_address = QLatin1String("address");
static const QLatin1String c_port = QLatin1String("port");
static const QLatin1String c_id = QLatin1String("id");
static const QLatin1String c_chatSizeMax = QLatin1String("chatSizeMax");
static const QLatin1String c_megagroupSizeMax = QLatin1String("megagroupSizeMax");
static const QLatin1String c_forwardedCountMax = QLatin1String("forwardedCountMax");
static const QLatin1String c_onlineCloudTimeoutMs = QLatin1String("onlineCloudTimeoutMs");
static const QLatin1String c_onlineUpdatePeriodMs = QLatin1String("onlineUpdatePeriodMs");
static const QLatin1String c_offlineBlurTimeoutMs = QLatin1String("offlineBlurTimeoutMs");
static const QLatin1String c_offlineIdleTimeoutMs = QLatin1String("offlineIdleTimeoutMs");
static const QLatin1String c_meUrlPrefix = QLatin1String("meUrlPrefix");

} // ConfigKey namespace

Config::Config(const QString &fileName)
{
    if (fileName.isEmpty()) {
        m_fileName = QStringLiteral("config.json");
    } else {
        m_fileName = fileName;
    }
    m_serverConfiguration = getDefaultDcConfiguration();
    m_privateKeyFile = QStringLiteral("private_key.pem");
}

void Config::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

DcConfiguration Config::getDefaultDcConfiguration()
{
    static DcConfiguration dcConfig;
    if (!dcConfig.isValid()) {
        dcConfig.dcOptions = {
            Telegram::DcOption(QStringLiteral("127.0.0.1"), 10443, 1),
            Telegram::DcOption(QStringLiteral("127.0.0.2"), 10443, 2),
            Telegram::DcOption(QStringLiteral("127.0.0.3"), 10443, 3),
        };

        dcConfig.chatSizeMax = 200;
        dcConfig.megagroupSizeMax = 2000;
        dcConfig.forwardedCountMax = 100;
        dcConfig.onlineCloudTimeoutMs = 300000;
        dcConfig.onlineUpdatePeriodMs = 210000;
        dcConfig.offlineBlurTimeoutMs = 5000;
        dcConfig.offlineIdleTimeoutMs = 30000;
        dcConfig.testMode = false;
    }
    return dcConfig;
}

void Config::setServerConfiguration(const DcConfiguration &configuration)
{
    m_serverConfiguration = configuration;
}

void Config::setPrivateKeyFile(const QString &fileName)
{
    m_privateKeyFile = fileName;
}

bool Config::load()
{
    QFile configFile(m_fileName);
    if (!configFile.open(QIODevice::ReadOnly)) {
        qCWarning(lcServerConfig) << "Failed to open config file:" << m_fileName;
        return false;
    }
    QByteArray configBytes = configFile.readAll();
    configFile.close();

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(configBytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(lcServerConfig) << "Failed to parse config file: " << parseError.errorString();
        return false;
    }

    const QJsonObject root = document.object();
    if (root.isEmpty()) {
        qCWarning(lcServerConfig) << "Failed to parse config file: " << parseError.errorString();
        return false;
    }

    m_serverConfiguration = getDefaultDcConfiguration();
    // read private key setting
    m_privateKeyFile = root[ConfigKey::c_privateKeyFile].toString();

    // read server configuration
    const QJsonObject configObject = root[ConfigKey::c_serverConfiguration].toObject();
    // read dc options
    m_serverConfiguration.dcOptions.clear();
    const QJsonArray dcOptionsArray = configObject[ConfigKey::c_dcOptions].toArray();
    for (const QJsonValue &dcOptionValue : dcOptionsArray) {
        const QJsonObject dcOptionObject = dcOptionValue.toObject();
        DcOption dcOpt;
        dcOpt.address = dcOptionObject[ConfigKey::c_address].toString();
        dcOpt.port = static_cast<quint16>(dcOptionObject[ConfigKey::c_port].toInt());
        dcOpt.id = static_cast<quint32>(dcOptionObject[ConfigKey::c_id].toInt());
        m_serverConfiguration.dcOptions.append(dcOpt);
    }
    m_serverConfiguration.testMode = root[ConfigKey::c_testMode].toBool();
    m_serverConfiguration.chatSizeMax = static_cast<quint32>(configObject[ConfigKey::c_chatSizeMax].toInt());
    m_serverConfiguration.megagroupSizeMax = static_cast<quint32>(configObject[ConfigKey::c_megagroupSizeMax].toInt());
    m_serverConfiguration.forwardedCountMax = static_cast<quint32>(configObject[ConfigKey::c_forwardedCountMax].toInt());
    m_serverConfiguration.onlineCloudTimeoutMs = static_cast<quint32>(configObject[ConfigKey::c_onlineCloudTimeoutMs].toInt());
    m_serverConfiguration.onlineUpdatePeriodMs = static_cast<quint32>(configObject[ConfigKey::c_onlineUpdatePeriodMs].toInt());
    m_serverConfiguration.offlineBlurTimeoutMs = static_cast<quint32>(configObject[ConfigKey::c_offlineBlurTimeoutMs].toInt());
    m_serverConfiguration.offlineIdleTimeoutMs = static_cast<quint32>(configObject[ConfigKey::c_offlineIdleTimeoutMs].toInt());
    m_serverConfiguration.meUrlPrefix = configObject[ConfigKey::c_meUrlPrefix].toString();

    qCInfo(lcServerConfig) << "Loaded config from " << m_fileName;
    return true;
}

bool Config::save() const
{
    QJsonObject root;
    root[ConfigKey::c_privateKeyFile] = m_privateKeyFile;

    QJsonObject configObject;
    QJsonArray dcOptionsArray;
    for (const DcOption &opt: m_serverConfiguration.dcOptions) {
        QJsonObject dcOptionObject;
        dcOptionObject[ConfigKey::c_address] = opt.address;
        dcOptionObject[ConfigKey::c_port] = opt.port;
        dcOptionObject[ConfigKey::c_id] = static_cast<int>(opt.id);
        dcOptionsArray.append(QJsonValue(dcOptionObject));
    }
    configObject[ConfigKey::c_dcOptions] = dcOptionsArray;
    configObject[ConfigKey::c_testMode] = m_serverConfiguration.testMode;
    configObject[ConfigKey::c_chatSizeMax] = QJsonValue::fromVariant(m_serverConfiguration.chatSizeMax);
    configObject[ConfigKey::c_megagroupSizeMax] = QJsonValue::fromVariant(m_serverConfiguration.megagroupSizeMax);
    configObject[ConfigKey::c_forwardedCountMax] = QJsonValue::fromVariant(m_serverConfiguration.forwardedCountMax);
    configObject[ConfigKey::c_onlineCloudTimeoutMs] = QJsonValue::fromVariant(m_serverConfiguration.onlineCloudTimeoutMs);
    configObject[ConfigKey::c_onlineUpdatePeriodMs] = QJsonValue::fromVariant(m_serverConfiguration.onlineUpdatePeriodMs);
    configObject[ConfigKey::c_offlineBlurTimeoutMs] = QJsonValue::fromVariant(m_serverConfiguration.offlineBlurTimeoutMs);
    configObject[ConfigKey::c_offlineIdleTimeoutMs] = QJsonValue::fromVariant(m_serverConfiguration.offlineIdleTimeoutMs);
    configObject[ConfigKey::c_meUrlPrefix] = m_serverConfiguration.meUrlPrefix;
    root[ConfigKey::c_serverConfiguration] = configObject;

    const QByteArray bytes = QJsonDocument(root).toJson(QJsonDocument::Indented);

    QFile f(m_fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        qCWarning(lcServerConfig) << "Failed to open config file:" << m_fileName;
        return false;
    }
    qint64 written = f.write(bytes);
    f.close();

    return written == bytes.size();
}

} // Server namespace

} // Telegram namespace
