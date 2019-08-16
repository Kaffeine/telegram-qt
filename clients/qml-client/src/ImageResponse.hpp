#ifndef TELEGRAMQT_IMAGE_RESPONSE_HPP
#define TELEGRAMQT_IMAGE_RESPONSE_HPP

#include <QQuickImageResponse>

namespace Telegram {

namespace Client {

class FileOperation;
class FilesApi;

class ImageResponse : public QQuickImageResponse
{
    Q_OBJECT
public:
    QQuickTextureFactory *textureFactory() const override;

    void processRequest(FilesApi *api, const QString &id, const QSize &requestedSize);

    QString errorString() const override;

public slots:
    void cancel() override;

protected slots:
    void onOperationFinished();

protected:
    QString m_errorString;
    FileOperation *m_operation = nullptr;
    QImage m_image;
    QSize m_requestedSize;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_IMAGE_RESPONSE_HPP
