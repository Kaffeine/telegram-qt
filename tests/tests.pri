
QT += core network testlib
TEMPLATE = app

INCLUDEPATH += $$PWD/../telegram-qt

LIBS += -lTelegramQt

win32 {
    CONFIG(debug) {
        LIBS += -L$$PWD/../bin/debug
        LIBS += -lssleay32MDd -llibeay32MDd
        DESTDIR = $$PWD/../bin/debug
    } else {
        LIBS += -L$$PWD/../bin/release
        LIBS += -lssleay32MD -llibeay32MD
        DESTDIR = $$PWD/../bin/release
    }
    LIBS += -lUser32 -lAdvapi32 -lGdi32
} else {
    LIBS += -L$$OUT_PWD/../../telegram-qt
    LIBS += -lssl
}
