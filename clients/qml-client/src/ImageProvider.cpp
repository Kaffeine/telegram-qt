#include "ImageProvider.hpp"
#include "ImageResponse.hpp"

#include "Client.hpp"

namespace Telegram {

namespace Client {

QQuickImageResponse *AsyncImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    FilesApi *filesApi = m_client ? m_client->filesApi() : nullptr;
    Telegram::Client::ImageResponse *response = new Telegram::Client::ImageResponse();
    response->processRequest(filesApi, id, requestedSize);

    return response;
}

void AsyncImageProvider::registerClient(Client *client)
{
    m_client = client;
}

QString AsyncImageProvider::id()
{
    return QStringLiteral("telegram");
}

QUrl AsyncImageProvider::makeUrl(const QString &fileId)
{
    if (fileId.isEmpty()) {
        return QUrl();
    }

    return QUrl(QLatin1String("image://") + id() + QLatin1Char('/') + fileId);
}

} // Client namespace

} // Telegram namespace
