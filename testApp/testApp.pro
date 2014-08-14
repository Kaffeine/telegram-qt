#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T18:29:28
#
#-------------------------------------------------

QT       += core gui network

TEMPLATE = app

INCLUDEPATH += $$PWD/../telegram-qt

LIBS += -lTelegramQt
LIBS += -lssl
LIBS += -L$$OUT_PWD/../telegram-qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApp
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    CContactModel.cpp \
    CMessagingModel.cpp

HEADERS  += MainWindow.hpp \
    CContactModel.hpp \
    CMessagingModel.hpp

FORMS    += MainWindow.ui
