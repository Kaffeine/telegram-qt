#ifndef TEST_SERVER_UTILS_HPP
#define TEST_SERVER_UTILS_HPP

#include "IMediaService.hpp"
#include "LocalCluster.hpp"
#include "RandomGenerator.hpp"
#include "ServerApi.hpp"
#include "TelegramServerUser.hpp"
#include "TestUserData.hpp"

#include <QBuffer>
#include <QDebug>
#include <QImage>

Telegram::Server::LocalUser *tryAddUser(Telegram::Server::LocalCluster *cluster, const UserData &data)
{
    Telegram::Server::LocalUser *u = cluster->addUser(data.phoneNumber, data.dcId);
    if (!u) {
        qCritical() << "Unable to add a user";
        return nullptr;
    }
    u->setFirstName(data.firstName);
    u->setLastName(data.lastName);
    if (!data.passwordHash.isEmpty()) {
        u->setPassword(data.passwordSalt, data.passwordHash);
    } else {
        u->setPlainPassword(data.password);
    }
    return u;
}

Telegram::Server::ImageDescriptor uploadUserImage(Telegram::Server::AbstractServerApi *server)
{
    QByteArray pictureData;
    {
        const QRgb colorCode = Telegram::RandomGenerator::instance()->generate<QRgb>() & RGB_MASK;
        QImage image = QImage(48, 48, QImage::Format_RGB32);
        image.fill(QColor(colorCode));
        QBuffer buffer(&pictureData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
    }

    quint64 fileId;
    Telegram::RandomGenerator::instance()->generate(&fileId);
    QString pictureFileName = QLatin1String("my_profile.png");
    quint32 filePartId = 0;

    Telegram::Server::IMediaService *mediaService = server->mediaService();
    mediaService->uploadFilePart(fileId, filePartId, pictureData);
    const Telegram::Server::UploadDescriptor desc = mediaService->getUploadedData(fileId);
    return mediaService->processImageFile(desc, pictureFileName);
}

#endif // TEST_SERVER_UTILS_HPP
