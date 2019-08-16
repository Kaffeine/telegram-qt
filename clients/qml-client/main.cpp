#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>
#include <QColor>
#include <QPalette>

#include "models/DialogsModel.hpp"
#include "models/MessagesModel.hpp"
#include "src/ImageProvider.hpp"
#include "DeclarativeClientOperator.hpp"

#ifdef QT_WIDGETS_LIB
#include <QApplication>
#endif

#include <QDebug>

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal horizontalPageMargin MEMBER m_horizontalPageMargin CONSTANT)
    Q_PROPERTY(qreal paddingLarge MEMBER m_paddingLarge CONSTANT)
    Q_PROPERTY(qreal paddingMedium MEMBER m_paddingMedium CONSTANT)
    Q_PROPERTY(qreal paddingSmall MEMBER m_paddingSmall CONSTANT)
    Q_PROPERTY(int fontSizeTiny MEMBER m_fontSizeTiny CONSTANT)
    Q_PROPERTY(int fontSizeExtraSmall MEMBER m_fontSizeExtraSmall CONSTANT)
    Q_PROPERTY(int fontSizeSmall MEMBER m_fontSizeSmall CONSTANT)
    Q_PROPERTY(int fontSizeMedium MEMBER m_fontSizeMedium CONSTANT)
    Q_PROPERTY(int fontSizeLarge MEMBER m_fontSizeLarge CONSTANT)
    Q_PROPERTY(QColor primaryColor MEMBER m_primaryColor CONSTANT)
    Q_PROPERTY(QColor secondaryColor MEMBER m_secondaryColor CONSTANT)
    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor CONSTANT)
    Q_PROPERTY(QColor highlightColor MEMBER m_highlightColor CONSTANT)
    Q_PROPERTY(QColor highlightBackgroundColor MEMBER m_highlightBackgroundColor CONSTANT)
    Q_PROPERTY(QColor highlightDimmerColor MEMBER m_highlightDimmerColor CONSTANT)
    Q_PROPERTY(qreal itemSizeExtraSmall  MEMBER m_itemSizeExtraSmall CONSTANT)
    Q_PROPERTY(qreal itemSizeSmall  MEMBER m_itemSizeSmall CONSTANT)
    Q_PROPERTY(qreal itemSizeMedium MEMBER m_itemSizeMedium CONSTANT)
    Q_PROPERTY(qreal itemSizeLarge MEMBER m_itemSizeLarge CONSTANT)
    Q_PROPERTY(qreal itemSizeExtraLarge MEMBER m_itemSizeExtraLarge CONSTANT)

    Q_PROPERTY(qreal iconSizeSmall MEMBER m_iconSizeSmall CONSTANT)

    Q_PROPERTY(qreal buttonWidthSmall MEMBER m_buttonWidthSmall CONSTANT)
    Q_PROPERTY(qreal buttonWidthMedium MEMBER m_buttonWidthMedium CONSTANT)

    Q_PROPERTY(int longDuration MEMBER m_longDuration CONSTANT)

public:
    explicit Theme(QObject *parent = nullptr) :
        QObject(parent),
        m_fontSizeTiny(20),
        m_fontSizeExtraSmall(24),
        m_fontSizeSmall(28),
        m_fontSizeMedium(32),
        m_fontSizeLarge(40),
        m_fontSizeExtraLarge(50),
        m_fontSizeHuge(64),
        m_fontSizeTinyBase(20),
        m_fontSizeExtraSmallBase(24),
        m_fontSizeSmallBase(28),
        m_fontSizeMediumBase(32),
        m_fontSizeLargeBase(40),
        m_fontSizeExtraLargeBase(50),
        m_fontSizeHugeBase(64),
        m_itemSizeExtraSmall(70),
        m_itemSizeSmall(80),
        m_itemSizeMedium(100),
        m_itemSizeLarge(110),
        m_itemSizeExtraLarge(135),
        m_itemSizeHuge(180),
        m_iconSizeExtraSmall(24),
        m_iconSizeSmall(32),
        m_iconSizeSmallPlus(48),
        m_iconSizeMedium(64),
        m_iconSizeLarge(96),
        m_iconSizeExtraLarge(128),
        m_iconSizeLauncher(86),
        m_buttonWidthSmall(234),
        m_buttonWidthMedium(292),
        m_buttonWidthLarge(444),
        m_coverSizeSmall(148, 237),
        m_coverSizeLarge(234, 374),
        m_paddingSmall(6),
        m_paddingMedium(12),
        m_paddingLarge(24),
        m_horizontalPageMargin(m_paddingLarge),
        m_flickDeceleration(1500),
        m_maximumFlickVelocity(5000),
        m_pageStackIndicatorWidth(37),
        m_highlightBackgroundOpacity(0.3),
        m_longDuration(800)
    {
        const QPalette pal = QGuiApplication::palette();
//        const QMetaEnum colorEnum = QMetaEnum::fromType<QPalette::ColorRole>();
//        for (int i = 0; i < colorEnum.keyCount(); ++i) {
//            qDebug() << colorEnum.key(i) << pal.color((QPalette::ColorRole)colorEnum.value(i)).name();
//        }
        m_highlightColor = pal.color(QPalette::Highlight);
        m_highlightDimmerColor = QStringLiteral("#bdc3c7");
        m_backgroundColor = pal.color(QPalette::AlternateBase);
        m_highlightBackgroundColor = pal.color(QPalette::Highlight);
    }

    QString m_fontFamilyHeading;
    QString m_fontFamily;
    QStringList m_launcherIconDirectories;
    int m_fontSizeTiny;
    int m_fontSizeExtraSmall;
    int m_fontSizeSmall;
    int m_fontSizeMedium;
    int m_fontSizeLarge;
    int m_fontSizeExtraLarge;
    int m_fontSizeHuge;
    int m_fontSizeTinyBase;
    int m_fontSizeExtraSmallBase;
    int m_fontSizeSmallBase;
    int m_fontSizeMediumBase;
    int m_fontSizeLargeBase;
    int m_fontSizeExtraLargeBase;
    int m_fontSizeHugeBase;
    qreal m_itemSizeExtraSmall;
    qreal m_itemSizeSmall;
    qreal m_itemSizeMedium;
    qreal m_itemSizeLarge;
    qreal m_itemSizeExtraLarge;
    qreal m_itemSizeHuge;
    qreal m_iconSizeExtraSmall;
    qreal m_iconSizeSmall;
    qreal m_iconSizeSmallPlus;
    qreal m_iconSizeMedium;
    qreal m_iconSizeLarge;
    qreal m_iconSizeExtraLarge;
    qreal m_iconSizeLauncher;
    qreal m_buttonWidthSmall;
    qreal m_buttonWidthMedium;
    qreal m_buttonWidthLarge;
    QSize m_coverSizeSmall;
    QSize m_coverSizeLarge;
    qreal m_paddingSmall;
    qreal m_paddingMedium;
    qreal m_paddingLarge;
    qreal m_horizontalPageMargin;
    qreal m_flickDeceleration;
    qreal m_maximumFlickVelocity;
    float m_pageStackIndicatorWidth;
    float m_highlightBackgroundOpacity;
    qreal m_pixelRatio;
    qreal m_webviewCustomLayoutWidthScalingFactor;
    int m_minimumPressHighlightTime;
    QColor m_highlightColor;
    QColor m_primaryColor;
    QColor m_secondaryColor;
    QColor m_secondaryHighlightColor;
    QColor m_backgroundColor;
    QColor m_highlightBackgroundColor;
    QColor m_highlightDimmerColor;
    int m_longDuration;
};

// Second, define the singleton type provider function (callback).
static QObject *theme_type_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Theme *theme = new Theme();
    return theme;
}

class ImageProviderWrapper : public Telegram::Client::DeclarativeClientOperator
{
    Q_OBJECT
public:
    explicit ImageProviderWrapper(QObject *parent = nullptr);

    void registerClient();
};

ImageProviderWrapper::ImageProviderWrapper(QObject *parent)
    : Telegram::Client::DeclarativeClientOperator(parent)
{
    connect(this, &ImageProviderWrapper::clientChanged,
            this, &ImageProviderWrapper::registerClient);
}

void ImageProviderWrapper::registerClient()
{
    QQmlEngine *engine = qmlEngine(this);
    if (!engine) {
        return;
    }

    QQmlImageProviderBase *baseProvider = engine->imageProvider(Telegram::Client::AsyncImageProvider::id());
    Telegram::Client::AsyncImageProvider *provider = static_cast<Telegram::Client::AsyncImageProvider*>(baseProvider);
    provider->registerClient(client());

    qDebug() << Q_FUNC_INFO << "Client registered for image provider" << provider;
}

#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("TelegramQt");
    app.setApplicationVersion(QStringLiteral("0.2"));
    QQuickStyle::setStyle("Material");

    qmlRegisterType<Telegram::Client::DialogsModel>("Client", 1, 0, "DialogsModel");
    qmlRegisterType<Telegram::Client::MessagesModel>("Client", 1, 0, "MessagesModel");
    qmlRegisterType<ImageProviderWrapper>("Client", 1, 0, "ImageProviderWrapper");
    qmlRegisterUncreatableType<Telegram::Client::Event>("Client", 1, 0, "Event", QStringLiteral("Event can be created only from C++"));

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [](QObject *object) {
        if (object) {
            return;
        }
        qCritical() << "Unable to instantiate the root component.";
        qCritical() << "Ensure that the application is installed correctly and double check"
                       " that QML2_IMPORT_PATH environment variable is set to the correct"
                       " installation directory with TelegramQt inside.";
        qCritical() << "If you built the project from CMake then ensure that you did\n"
                       "    cmake --build <your_build_directory> --target install\n"
                       "and also follow the hint about QML2_IMPORT_PATH from CMake"
                       " configure output.";

        exit(1);
    });

    qmlRegisterSingletonType<Theme>("TelegramQtTheme", 1, 0, "Theme", theme_type_provider);
    Telegram::Client::AsyncImageProvider *imageProvider = new Telegram::Client::AsyncImageProvider();
    engine.addImageProvider(imageProvider->id(), imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

#include "main.moc"
