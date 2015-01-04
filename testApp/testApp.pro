#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T18:29:28
#
#-------------------------------------------------

QT       += core gui network

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
    LIBS += -L$$OUT_PWD/../telegram-qt
    LIBS += -lssl
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApp
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    CContactModel.cpp \
    CMessagingModel.cpp \
    CChatInfoModel.cpp

HEADERS  += MainWindow.hpp \
    CContactModel.hpp \
    CMessagingModel.hpp \
    CChatInfoModel.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
