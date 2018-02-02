QT += core network
CONFIG += c++11

TEMPLATE = app

INCLUDEPATH += $$PWD/../TelegramQt

LIBS += -lssl -lcrypto -lz
LIBS += -L$$OUT_PWD/../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}

TARGET = testApp

SOURCES = main.cpp
include(server.pri)

#OTHER_FILES += CMakeLists.txt
