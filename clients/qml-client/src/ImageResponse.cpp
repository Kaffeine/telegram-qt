#include "ImageResponse.hpp"

#include "FilesApi.hpp"
#include "Operations/FileOperation.hpp"

#include <QIODevice>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcClientImageResponse, "qmlclient.image-response", QtWarningMsg)

namespace Telegram {

namespace Client {

QQuickTextureFactory *ImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(m_image);
}

void ImageResponse::processRequest(FilesApi *api, const QString &id, const QSize &requestedSize)
{
    if (!api) {
        m_errorString = QLatin1String("ImageResponse: Unable to process request: FilesApi is "
                                      "not available. Check that ImageProviderWrapper is"
                                      " instantiated and its 'client' property is set.");
        emit finished();
        return;
    }

    m_requestedSize = requestedSize;
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
    m_errorString = QLatin1String("ImageResponse: Unable to process request, because the "
                                  "build-time Qt version is less than 5.10. ");
    emit finished();
#else
    QMetaObject::invokeMethod(api, [&, api, id]() {
        m_operation = api->downloadFile(id);
        qCDebug(lcClientImageResponse) << "Request" << id << "operation:" << m_operation;
        connect(m_operation, &PendingOperation::finished, this, &ImageResponse::onOperationFinished, Qt::QueuedConnection);
    }, Qt::QueuedConnection);
#endif
}

QString ImageResponse::errorString() const
{
    return m_errorString;
}

void ImageResponse::cancel()
{
    m_operation->cancel();
}

void ImageResponse::onOperationFinished()
{
    if (m_operation->isFailed()) {
        qCWarning(lcClientImageResponse) << "Operation failed:" << m_operation->errorDetails();
        m_errorString = m_operation->errorDetails().value(PendingOperation::c_text()).toString();
        emit finished();
        return;
    }

    QByteArray data = m_operation->device()->readAll();
    qCDebug(lcClientImageResponse) << "finished" << m_operation; //data.size() << data.toHex();
    if (!data.isEmpty() && !m_image.loadFromData(data)) {
        qCWarning(lcClientImageResponse) << Q_FUNC_INFO << "Unable to load data";
    }

    if (m_requestedSize.isValid()) {
        m_image = m_image.scaled(m_requestedSize);
    }

    emit finished();
}

} // Client namespace

} // Telegram namespace
