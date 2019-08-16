#ifndef TELEGRAMQT_IMAGE_PROVIDER_HPP
#define TELEGRAMQT_IMAGE_PROVIDER_HPP

#include <QQuickImageProvider>

namespace Telegram {

namespace Client {

class Client;

class AsyncImageProvider : public QQuickAsyncImageProvider
{
public:
    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &requestedSize) override;

    void registerClient(Client *client);

    static QString id();

    static QUrl makeUrl(const QString &fileId);

protected:
    Client *m_client = nullptr;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_IMAGE_PROVIDER_HPP
