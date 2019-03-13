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

Q_LOGGING_CATEGORY(loggingCategoryConfig, "telegram.server.config", QtDebugMsg)

namespace Telegram {

namespace Server {

namespace ConfigKey {

static const QLatin1String c_privateKeyFile = QLatin1String("privateKeyFile");
static const QLatin1String c_serverConfiguration = QLatin1String("serverConfiguration");
static const QLatin1String c_dcOptions = QLatin1String("dcOptions");
static const QLatin1String c_address = QLatin1String("address");
static const QLatin1String c_port = QLatin1String("port");
static const QLatin1String c_id = QLatin1String("id");

} // ConfigKey namespace

Config::Config(const QString &fileName)
{
    if (fileName.isEmpty()) {
        m_fileName = QStringLiteral("config.json");
    } else {
        m_fileName = fileName;
    }

    // default config
    m_serverConfiguration.dcOptions = {
        Telegram::DcOption(QStringLiteral("127.0.0.1"), 11441, 1),
        Telegram::DcOption(QStringLiteral("127.0.0.2"), 11442, 2),
        Telegram::DcOption(QStringLiteral("127.0.0.3"), 11443, 3),
    };
    m_privateKeyFile = QStringLiteral("private_key.pem");
}

void Config::setFileName(const QString &fileName)
{
    m_fileName = fileName;
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
    QByteArray bytes;
    QFile f(m_fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qCWarning(loggingCategoryConfig) << "Failed to open config file:" << m_fileName;
        return false;
    }
    bytes = f.readAll();
    f.close();

    QJsonParseError jErr;
    const QJsonDocument doc = QJsonDocument::fromJson(bytes, &jErr);
    if (jErr.error != QJsonParseError::NoError) {
        qCWarning(loggingCategoryConfig) << "Failed to parse config file: " << jErr.errorString();
        qCWarning(loggingCategoryConfig) << "Using default config.";
        return false;
    }

    const QJsonObject obj = doc.object();
    if (obj.isEmpty()) {
        qCWarning(loggingCategoryConfig) << "Failed to parse config file: " << jErr.errorString();
        qCWarning(loggingCategoryConfig) << "Using default config.";
        return false;
    }

    // read private key setting
    m_privateKeyFile = obj[ConfigKey::c_privateKeyFile].toString();

    // read server configuration
    const QJsonObject &jserverConfig = obj[ConfigKey::c_serverConfiguration].toObject();
    // read dc options
    m_serverConfiguration.dcOptions.clear();
    const QJsonArray &jdcConfigArr = jserverConfig[ConfigKey::c_dcOptions].toArray();
    for (const QJsonValue &jval : jdcConfigArr) {
        const QJsonObject &jobj = jval.toObject();
        DcOption dcOpt;
        dcOpt.address = jobj[ConfigKey::c_address].toString();
        dcOpt.port = static_cast<quint16>(jobj[ConfigKey::c_port].toInt());
        dcOpt.id = static_cast<quint32>(jobj[ConfigKey::c_id].toInt());
        m_serverConfiguration.dcOptions.append(dcOpt);
    }

    qCInfo(loggingCategoryConfig) << "Loaded config from " << m_fileName;
    return true;
}

bool Config::save() const
{
    QJsonObject jobj;
    jobj[ConfigKey::c_privateKeyFile] = m_privateKeyFile;

    QJsonObject jserverConfiguration;
    QJsonArray jdcArr;
    for (const DcOption &opt: m_serverConfiguration.dcOptions) {
        QJsonObject jdcOpt;
        jdcOpt[ConfigKey::c_address] = opt.address;
        jdcOpt[ConfigKey::c_port] = opt.port;
        jdcOpt[ConfigKey::c_id] = static_cast<int>(opt.id);
        jdcArr.append(QJsonValue(jdcOpt));
    }
    jserverConfiguration[ConfigKey::c_dcOptions] = jdcArr;
    jobj[ConfigKey::c_serverConfiguration] = jserverConfiguration;

    const QByteArray bytes = QJsonDocument(jobj).toJson(QJsonDocument::Indented);

    QFile f(m_fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        qCWarning(loggingCategoryConfig) << "Failed to open config file:" << m_fileName;
        return false;
    }
    qint64 written = f.write(bytes);
    f.close();

    return written == bytes.size();
}

} // Server namespace

} // Telegram namespace
