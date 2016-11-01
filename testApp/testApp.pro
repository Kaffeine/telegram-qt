QT += core gui network
CONFIG += c++11

TEMPLATE = app

INCLUDEPATH += $$PWD/../TelegramQt

LIBS += -lssl -lcrypto -lz
LIBS += -lTelegramQt
LIBS += -L$$OUT_PWD/../TelegramQt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApp
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    CContactModel.cpp \
    CChatInfoModel.cpp \
    CMessageModel.cpp

HEADERS  += MainWindow.hpp \
    CContactModel.hpp \
    CChatInfoModel.hpp \
    CMessageModel.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += CMakeLists.txt
